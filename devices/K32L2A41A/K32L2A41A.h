/*
** ###################################################################
**     Processors:          K32L2A41VLH1A
**                          K32L2A41VLL1A
**
**     Compilers:           Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    K32L2AxRM, Rev. 1, 12/2019
**     Version:             rev. 1.0, 2019-10-30
**     Build:               b191218
**
**     Abstract:
**         CMSIS Peripheral Access Layer for K32L2A41A
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2019 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2019-10-30)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file K32L2A41A.h
 * @version 1.0
 * @date 2019-10-30
 * @brief CMSIS Peripheral Access Layer for K32L2A41A
 *
 * CMSIS Peripheral Access Layer for K32L2A41A
 */

#ifndef _K32L2A41A_H_
#define _K32L2A41A_H_ /**< Symbol preventing repeated inclusion */

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
#define NUMBER_OF_INT_VECTORS 80 /**< Number of interrupts in the Vector table */

typedef enum IRQn
{
    /* Auxiliary constants */
    NotAvail_IRQn = -128, /**< Not available device specific interrupt */

    /* Core interrupts */
    NonMaskableInt_IRQn = -14, /**< Non Maskable Interrupt */
    HardFault_IRQn      = -13, /**< Cortex-M0 SV Hard Fault Interrupt */
    SVCall_IRQn         = -5,  /**< Cortex-M0 SV Call Interrupt */
    PendSV_IRQn         = -2,  /**< Cortex-M0 Pend SV Interrupt */
    SysTick_IRQn        = -1,  /**< Cortex-M0 System Tick Interrupt */

    /* Device specific interrupts */
    DMA0_04_IRQn         = 0,  /**< DMA0 channel 0/4 transfer complete */
    DMA0_15_IRQn         = 1,  /**< DMA0 channel 1/5 transfer complete */
    DMA0_26_IRQn         = 2,  /**< DMA0 channel 2/6 transfer complete */
    DMA0_37_IRQn         = 3,  /**< DMA0 channel 3/7 transfer complete */
    CTI0_DMA0_Error_IRQn = 4,  /**< CTI0 or DMA0 error */
    FLEXIO0_IRQn         = 5,  /**< FLEXIO0 */
    TPM0_IRQn            = 6,  /**< TPM0 single interrupt vector for all sources */
    TPM1_IRQn            = 7,  /**< TPM1 single interrupt vector for all sources */
    TPM2_IRQn            = 8,  /**< TPM2 single interrupt vector for all sources */
    LPIT0_IRQn           = 9,  /**< LPIT0 interrupt */
    LPSPI0_IRQn          = 10, /**< LPSPI0 single interrupt vector for all sources */
    LPSPI1_IRQn          = 11, /**< LPSPI1 single interrupt vector for all sources */
    LPUART0_IRQn         = 12, /**< LPUART0 status and error */
    LPUART1_IRQn         = 13, /**< LPUART1 status and error */
    LPI2C0_IRQn          = 14, /**< LPI2C0 interrupt */
    LPI2C1_IRQn          = 15, /**< LPI2C1 interrupt */
    Reserved32_IRQn      = 16, /**< Reserved interrupt */
    PORTA_IRQn           = 17, /**< PORTA Pin detect */
    PORTB_IRQn           = 18, /**< PORTB Pin detect */
    PORTC_IRQn           = 19, /**< PORTC Pin detect */
    PORTD_IRQn           = 20, /**< PORTD Pin detect */
    PORTE_IRQn           = 21, /**< PORTE Pin detect */
    LLWU_IRQn            = 22, /**< Low leakage wakeup  */
    Reserved39_IRQn      = 23, /**< Reserved interrupt */
    USB0_IRQn            = 24, /**< USB0 interrupt */
    ADC0_IRQn            = 25, /**< ADC0 interrupt */
    LPTMR0_IRQn          = 26, /**< LPTMR0 interrupt */
    RTC_Seconds_IRQn     = 27, /**< RTC seconds */
    INTMUX0_0_IRQn       = 28, /**< INTMUX0 channel 0 interrupt */
    INTMUX0_1_IRQn       = 29, /**< INTMUX0 channel 1 interrupt */
    INTMUX0_2_IRQn       = 30, /**< INTMUX0 channel 2 interrupt */
    INTMUX0_3_IRQn       = 31, /**< INTMUX0 channel 3 interrupt */
    LPTMR1_IRQn          = 32, /**< LPTMR1 interrupt  (INTMUX source IRQ0) */
    Reserved49_IRQn      = 33, /**< Reserved interrupt */
    Reserved50_IRQn      = 34, /**< Reserved interrupt */
    Reserved51_IRQn      = 35, /**< Reserved interrupt */
    LPSPI2_IRQn          = 36, /**< LPSPI2 single interrupt vector for all sources (INTMUX source IRQ4) */
    LPUART2_IRQn         = 37, /**< LPUART2 status and error (INTMUX source IRQ5) */
    EMVSIM0_IRQn         = 38, /**< EMVSIM0 interrupt (INTMUX source IRQ6) */
    LPI2C2_IRQn          = 39, /**< LPI2C2 interrupt (INTMUX source IRQ7) */
    TSI0_IRQn            = 40, /**< TSI0 interrupt (INTMUX source IRQ8) */
    PMC_IRQn             = 41, /**< PMC interrupt (INTMUX source IRQ9) */
    FTFA_IRQn            = 42, /**< FTFA interrupt (INTMUX source IRQ10) */
    SCG_IRQn             = 43, /**< SCG interrupt (INTMUX source IRQ11) */
    WDOG0_IRQn           = 44, /**< WDOG0 interrupt (INTMUX source IRQ12) */
    DAC0_IRQn            = 45, /**< DAC0 interrupt (INTMUX source IRQ13) */
    TRNG_IRQn            = 46, /**< TRNG interrupt (INTMUX source IRQ14) */
    RCM_IRQn             = 47, /**< RCM interrupt (INTMUX source IRQ15) */
    CMP0_IRQn            = 48, /**< CMP0 interrupt (INTMUX source IRQ16) */
    CMP1_IRQn            = 49, /**< CMP1 interrupt (INTMUX source IRQ17) */
    RTC_IRQn             = 50, /**< RTC Alarm interrupt (INTMUX source IRQ18) */
    Reserved67_IRQn      = 51, /**< Reserved interrupt */
    Reserved68_IRQn      = 52, /**< Reserved interrupt */
    Reserved69_IRQn      = 53, /**< Reserved interrupt */
    Reserved70_IRQn      = 54, /**< Reserved interrupt */
    Reserved71_IRQn      = 55, /**< Reserved interrupt */
    Reserved72_IRQn      = 56, /**< Reserved interrupt */
    Reserved73_IRQn      = 57, /**< Reserved interrupt */
    Reserved74_IRQn      = 58, /**< Reserved interrupt */
    Reserved75_IRQn      = 59, /**< Reserved interrupt */
    Reserved76_IRQn      = 60, /**< Reserved interrupt */
    Reserved77_IRQn      = 61, /**< Reserved interrupt */
    Reserved78_IRQn      = 62, /**< Reserved interrupt */
    Reserved79_IRQn      = 63  /**< Reserved interrupt */
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

#define __CM0PLUS_REV 0x0000     /**< Core revision r0p0 */
#define __MPU_PRESENT 1          /**< Defines if an MPU is present or not */
#define __VTOR_PRESENT 1         /**< Defines if VTOR is present or not */
#define __NVIC_PRIO_BITS 2       /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig 0 /**< Vendor specific implementation of SysTickConfig is defined */

#include "core_cm0plus.h"     /* Core Peripheral Access Layer */
#include "system_K32L2A41A.h" /* Device specific configuration file */

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
    kDmaRequestMux0Disable         = 0 | 0x100U,  /**< DMAMUX TriggerDisabled */
    kDmaRequestMux0FlexIO0Channel0 = 1 | 0x100U,  /**< FLEXIO0 Channel 0 */
    kDmaRequestMux0FlexIO0Channel1 = 2 | 0x100U,  /**< FLEXIO0 Channel 1 */
    kDmaRequestMux0FlexIO0Channel2 = 3 | 0x100U,  /**< FLEXIO0 Channel 2 */
    kDmaRequestMux0FlexIO0Channel3 = 4 | 0x100U,  /**< FLEXIO0 Channel 3 */
    kDmaRequestMux0FlexIO0Channel4 = 5 | 0x100U,  /**< FLEXIO0 Channel 4 */
    kDmaRequestMux0FlexIO0Channel5 = 6 | 0x100U,  /**< FLEXIO0 Channel 5 */
    kDmaRequestMux0FlexIO0Channel6 = 7 | 0x100U,  /**< FLEXIO0 Channel 6 */
    kDmaRequestMux0FlexIO0Channel7 = 8 | 0x100U,  /**< FLEXIO0 Channel 7 */
    kDmaRequestMux0LPI2C0Rx        = 9 | 0x100U,  /**< LPI2C0 Receive */
    kDmaRequestMux0LPI2C0Tx        = 10 | 0x100U, /**< LPI2C0 Transmit */
    kDmaRequestMux0LPI2C1Rx        = 11 | 0x100U, /**< LPI2C1 Receive */
    kDmaRequestMux0LPI2C1Tx        = 12 | 0x100U, /**< LPI2C1 Transmit */
    kDmaRequestMux0LPI2C2Rx        = 13 | 0x100U, /**< LPI2C2 Receive */
    kDmaRequestMux0LPI2C2Tx        = 14 | 0x100U, /**< LPI2C2 Transmit */
    kDmaRequestMux0LPUART0Rx       = 15 | 0x100U, /**< LPUART0 Receive */
    kDmaRequestMux0LPUART0Tx       = 16 | 0x100U, /**< LPUART0 Transmit */
    kDmaRequestMux0LPUART1Rx       = 17 | 0x100U, /**< LPUART1 Receive */
    kDmaRequestMux0LPUART1Tx       = 18 | 0x100U, /**< LPUART1 Transmit */
    kDmaRequestMux0LPUART2Rx       = 19 | 0x100U, /**< LPUART2 Receive */
    kDmaRequestMux0LPUART2Tx       = 20 | 0x100U, /**< LPUART2 Transmit */
    kDmaRequestMux0LPSPI0Rx        = 21 | 0x100U, /**< LPSPI0 Receive */
    kDmaRequestMux0LPSPI0Tx        = 22 | 0x100U, /**< LPSPI0 Transmit */
    kDmaRequestMux0LPSPI1Rx        = 23 | 0x100U, /**< LPSPI1 Receive */
    kDmaRequestMux0LPSPI1Tx        = 24 | 0x100U, /**< LPSPI1 Transmit */
    kDmaRequestMux0LPSPI2Rx        = 25 | 0x100U, /**< LPSPI2 Receive */
    kDmaRequestMux0LPSPI2Tx        = 26 | 0x100U, /**< LPSPI2 Transmit */
    kDmaRequestMux0TPM0Channel0    = 27 | 0x100U, /**< TPM0 C0V Transmit */
    kDmaRequestMux0TPM0Channel1    = 28 | 0x100U, /**< TPM0 C1V Transmit */
    kDmaRequestMux0TPM0Channel2    = 29 | 0x100U, /**< TPM0 C2V Transmit */
    kDmaRequestMux0TPM0Channel3    = 30 | 0x100U, /**< TPM0 C3V Transmit */
    kDmaRequestMux0TPM0Channel4    = 31 | 0x100U, /**< TPM0 C4V Transmit */
    kDmaRequestMux0TPM0Channel5    = 32 | 0x100U, /**< TPM0 C5V Transmit */
    kDmaRequestMux0Reserved33      = 33 | 0x100U, /**< Reserved33 */
    kDmaRequestMux0Reserved34      = 34 | 0x100U, /**< Reserved34 */
    kDmaRequestMux0TPM0Overflow    = 35 | 0x100U, /**< TPM0 */
    kDmaRequestMux0TPM1Channel0    = 36 | 0x100U, /**< TPM1 C0V Transmit */
    kDmaRequestMux0TPM1Channel1    = 37 | 0x100U, /**< TPM1 C1V Transmit */
    kDmaRequestMux0TPM1Overflow    = 38 | 0x100U, /**< TPM1 */
    kDmaRequestMux0TPM2Channel0    = 39 | 0x100U, /**< TPM2 C0V Transmit */
    kDmaRequestMux0TPM2Channel1    = 40 | 0x100U, /**< TPM2 C1V Transmit */
    kDmaRequestMux0TPM2Overflow    = 41 | 0x100U, /**< TPM2 */
    kDmaRequestMux0Reserved42      = 42 | 0x100U, /**< Reserved42 */
    kDmaRequestMux0EMVSIM0Rx       = 43 | 0x100U, /**< EMVSIM0 Receive */
    kDmaRequestMux0EMVSIM0Tx       = 44 | 0x100U, /**< EMVSIM0 Transmit */
    kDmaRequestMux0Reserved45      = 45 | 0x100U, /**< Reserved45 */
    kDmaRequestMux0Reserved46      = 46 | 0x100U, /**< Reserved46 */
    kDmaRequestMux0PortA           = 47 | 0x100U, /**< PTA */
    kDmaRequestMux0PortB           = 48 | 0x100U, /**< PTB */
    kDmaRequestMux0PortC           = 49 | 0x100U, /**< PTC */
    kDmaRequestMux0PortD           = 50 | 0x100U, /**< PTD */
    kDmaRequestMux0PortE           = 51 | 0x100U, /**< PTE */
    kDmaRequestMux0ADC0            = 52 | 0x100U, /**< ADC0 */
    kDmaRequestMux0Reserved53      = 53 | 0x100U, /**< Reserved53 */
    kDmaRequestMux0DAC0            = 54 | 0x100U, /**< DAC0 */
    kDmaRequestMux0Reserved55      = 55 | 0x100U, /**< Reserved55 */
    kDmaRequestMux0CMP0            = 56 | 0x100U, /**< CMP0 */
    kDmaRequestMux0CMP1            = 57 | 0x100U, /**< CMP1 */
    kDmaRequestMux0Reserved58      = 58 | 0x100U, /**< Reserved58 */
    kDmaRequestMux0Reserved59      = 59 | 0x100U, /**< Reserved59 */
    kDmaRequestMux0TSI0            = 60 | 0x100U, /**< TSI0 */
    kDmaRequestMux0LPTMR0          = 61 | 0x100U, /**< LPTMR0 */
    kDmaRequestMux0LPTMR1          = 62 | 0x100U, /**< LPTMR1 */
    kDmaRequestMux0AlwaysOn63      = 63 | 0x100U, /**< DMAMUX Always Enabled slot */
} dma_request_source_t;

/* @} */

/*!
 * @addtogroup trgmux_source
 * @{ */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*!
 * @brief Structure for the TRGMUX source
 *
 * Defines the structure for the TRGMUX source collections.
 */
typedef enum _trgmux_source
{
    kTRGMUX_SourceDisabled          = 0U,  /**< Trigger function is disabled */
    kTRGMUX_SourcePortPin           = 1U,  /**< Port pin trigger intput is selected */
    kTRGMUX_SourceFlexIOTimer0      = 2U,  /**< FlexIO Timer 0 input is selected */
    kTRGMUX_SourceFlexIOTimer1      = 3U,  /**< FlexIO Timer 1 input is selected */
    kTRGMUX_SourceFlexIOTimer2      = 4U,  /**< FlexIO Timer 2 input is selected */
    kTRGMUX_SourceFlexIOTimer3      = 5U,  /**< FlexIO Timer 3 input is selected */
    kTRGMUX_SourceFlexIOTimer4      = 6U,  /**< FlexIO Timer 4 input is selected */
    kTRGMUX_SourceFlexIOTimer5      = 7U,  /**< FlexIO Timer 5 input is selected */
    kTRGMUX_SourceFlexIOTimer6      = 8U,  /**< FlexIO Timer 6 input is selected */
    kTRGMUX_SourceFlexIOTimer7      = 9U,  /**< FlexIO Timer 7 input is selected */
    kTRGMUX_SourceTpm0Overflow      = 10U, /**< TPM0 Overflow is selected */
    kTRGMUX_SourceTpm0Ch0           = 11U, /**< TPM0 Channel 0 is selected */
    kTRGMUX_SourceTpm0Ch1           = 12U, /**< TPM0 Channel 1 is selected */
    kTRGMUX_SourceTpm1Overflow      = 13U, /**< TPM1 Overflow is selected */
    kTRGMUX_SourceTpm1Ch0           = 14U, /**< TPM1 Channel 0 is selected */
    kTRGMUX_SourceTpm1Ch1           = 15U, /**< TPM1 Channel 1 is selected */
    kTRGMUX_SourceLpit1Ch0          = 16U, /**< LPIT1 Channel 0 is selected */
    kTRGMUX_SourceLpit1Ch1          = 17U, /**< LPIT1 Channel 1 is selected */
    kTRGMUX_SourceLpit1Ch2          = 18U, /**< LPIT1 Channel 2 is selected */
    kTRGMUX_SourceLpit1Ch3          = 19U, /**< LPIT1 Channel 3 is selected */
    kTRGMUX_SourceLpuart0RxData     = 20U, /**< LPUART0 RX Data is selected */
    kTRGMUX_SourceLpuart0TxData     = 21U, /**< LPUART0 TX Data is selected */
    kTRGMUX_SourceLpuart0RxIdle     = 22U, /**< LPUART0 RX Idle is selected */
    kTRGMUX_SourceLpuart1RxData     = 23U, /**< LPUART1 RX Data is selected */
    kTRGMUX_SourceLpuart1TxData     = 24U, /**< LPUART1 TX Data is selected */
    kTRGMUX_SourceLpuart1RxIdle     = 25U, /**< LPUART1 RX Idle is selected */
    kTRGMUX_SourceLpi2c0MasterStop  = 26U, /**< LPI2C0 Master STOP is selected */
    kTRGMUX_SourceLpi2c0SlaveStop   = 27U, /**< LPI2C0 Slave STOP is selected */
    kTRGMUX_SourceLpi2c1MasterStop  = 28U, /**< LPI2C1 Master STOP is selected */
    kTRGMUX_SourceLpi2c1SlaveStop   = 29U, /**< LPI2C1 Slave STOP is selected */
    kTRGMUX_SourceLpspi0Frame       = 30U, /**< LPSPI0 Frame is selected */
    kTRGMUX_SourceLpspi0RxData      = 31U, /**< LPSPI0 RX Data is selected */
    kTRGMUX_SourceLpspi1Frame       = 32U, /**< LPSPI1 Frame is selected */
    kTRGMUX_SourceLpspi1RxData      = 33U, /**< LPSPI1 RX Data is selected */
    kTRGMUX_SourceRtcSecCount       = 34U, /**< RTC Seconds Counter is selected */
    kTRGMUX_SourceRtcAlarm          = 35U, /**< RTC Alarm is selected */
    kTRGMUX_SourceLptmr0Trg         = 36U, /**< LPTMR0 Trigger is selected */
    kTRGMUX_SourceLptmr1Trg         = 37U, /**< LPTMR1 Trigger is selected */
    kTRGMUX_SourceCmp0Output        = 38U, /**< CMP0 Output is selected */
    kTRGMUX_SourceCmp1Output        = 39U, /**< CMP1 Output is selected */
    kTRGMUX_SourceAdc0ConvAComplete = 40U, /**< ADC0 Conversion A Complete is selected */
    kTRGMUX_SourceAdc0ConvBComplete = 41U, /**< ADC0 Conversion B Complete is selected */
    kTRGMUX_SourcePortAPinTrg       = 42U, /**< Port A Pin Trigger is selected */
    kTRGMUX_SourcePortBPinTrg       = 43U, /**< Port B Pin Trigger is selected */
    kTRGMUX_SourcePortCPinTrg       = 44U, /**< Port C Pin Trigger is selected */
    kTRGMUX_SourcePortDPinTrg       = 45U, /**< Port D Pin Trigger is selected */
    kTRGMUX_SourcePortEPinTrg       = 46U, /**< Port E Pin Trigger is selected */
    kTRGMUX_SourceTpm2Overflow      = 47U, /**< TPM2 Overflow is selected */
    kTRGMUX_SourceTpm2Ch0           = 48U, /**< TPM2 Channel 0 is selected */
    kTRGMUX_SourceTpm2Ch1           = 49U, /**< TPM2 Channel 1 is selected */
    kTRGMUX_SourceLpit0Ch0          = 50U, /**< LPIT0 Channel 0 is selected */
    kTRGMUX_SourceLpit0Ch1          = 51U, /**< LPIT0 Channel 1 is selected */
    kTRGMUX_SourceLpit0Ch2          = 52U, /**< LPIT0 Channel 2 is selected */
    kTRGMUX_SourceLpit0Ch3          = 53U, /**< LPIT0 Channel 3 is selected */
    kTRGMUX_SourceUsbSof            = 54U, /**< USB Start-of-Frame is selected */
    kTRGMUX_SourceLpuart2RxData     = 55U, /**< LPUART2 RX Data is selected */
    kTRGMUX_SourceLpuart2TxData     = 56U, /**< LPUART2 TX Data is selected */
    kTRGMUX_SourceLpuart2RxIdle     = 57U, /**< LPUART2 RX Idle is selected */
    kTRGMUX_SourceLpi2c2MasterStop  = 58U, /**< LPI2C2 Master STOP is selected */
    kTRGMUX_SourceLpi2c2SlaveStop   = 59U, /**< LPI2C2 Slave STOP is selected */
    kTRGMUX_SourceLpspi2Frame       = 60U, /**< LPSPI2 Frame is selected */
    kTRGMUX_SourceLpspi2RxData      = 61U, /**< LPSPI2 RX Data is selected */
    kTRGMUX_SourceI2c0TxFrameSync   = 62U, /**< I2C0 TX Frame Sync is selected */
    kTRGMUX_SourceI2c0RxFrameSync   = 63U, /**< I2C0 RX Frame Sync is selected */
} trgmux_source_t;

/*!
 * @brief Structure for the TRGMUX device
 *
 * Defines the structure for the TRGMUX device collections.
 */
typedef enum _trgmux_device
{
    kTRGMUX_Trgmux0Dmamux0 = 0U,  /**< DMAMUX0 device trigger input */
    kTRGMUX_Trgmux0Lpit0   = 1U,  /**< LPIT0 device trigger input */
    kTRGMUX_Trgmux0Tpm2    = 2U,  /**< TPM2 device trigger input */
    kTRGMUX_Trgmux1Tpm0    = 2U,  /**< TPM0 device trigger input */
    kTRGMUX_Trgmux0Adc0    = 4U,  /**< ADC0 device trigger input */
    kTRGMUX_Trgmux1Flexio  = 4U,  /**< FLEXIO device trigger input */
    kTRGMUX_Trgmux0Lpuart2 = 5U,  /**< LPUART2 device trigger input */
    kTRGMUX_Trgmux1Lpuart0 = 5U,  /**< LPUART0 device trigger input */
    kTRGMUX_Trgmux0Lpi2c2  = 7U,  /**< LPI2C2 device trigger input */
    kTRGMUX_Trgmux1Lpi2c0  = 7U,  /**< LPI2C0 device trigger input */
    kTRGMUX_Trgmux0Lpspi2  = 9U,  /**< LPSPI2 device trigger input */
    kTRGMUX_Trgmux1Lpspi0  = 9U,  /**< LPSPI0 device trigger input */
    kTRGMUX_Trgmux0Cmp0    = 11U, /**< CMP0 device trigger input */
    kTRGMUX_Trgmux0Cmp1    = 12U, /**< CMP1 device trigger input */
    kTRGMUX_Trgmux0Dac0    = 13U, /**< DAC0 device trigger input */
    kTRGMUX_Trgmux1Tpm1    = 3U,  /**< TPM1 device trigger input */
    kTRGMUX_Trgmux1Lpuart1 = 6U,  /**< LPUART1 device trigger input */
    kTRGMUX_Trgmux1Lpi2c1  = 8U,  /**< LPI2C1 device trigger input */
    kTRGMUX_Trgmux1Lpspi1  = 10U, /**< LPSPI1 device trigger input */
} trgmux_device_t;

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
#elif defined(__CWCC__)
#pragma push
#pragma cpp_extensions on
#elif defined(__GNUC__)
/* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma language = extended
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
typedef struct
{
    __IO uint32_t SC1[2]; /**< ADC Status and Control Registers 1, array offset: 0x0, array step: 0x4 */
    __IO uint32_t CFG1;   /**< ADC Configuration Register 1, offset: 0x8 */
    __IO uint32_t CFG2;   /**< ADC Configuration Register 2, offset: 0xC */
    __I uint32_t R[2];    /**< ADC Data Result Register, array offset: 0x10, array step: 0x4 */
    __IO uint32_t CV1;    /**< Compare Value Registers, offset: 0x18 */
    __IO uint32_t CV2;    /**< Compare Value Registers, offset: 0x1C */
    __IO uint32_t SC2;    /**< Status and Control Register 2, offset: 0x20 */
    __IO uint32_t SC3;    /**< Status and Control Register 3, offset: 0x24 */
    __IO uint32_t OFS;    /**< ADC Offset Correction Register, offset: 0x28 */
    __IO uint32_t PG;     /**< ADC Plus-Side Gain Register, offset: 0x2C */
    __IO uint32_t MG;     /**< ADC Minus-Side Gain Register, offset: 0x30 */
    __IO uint32_t CLPD;   /**< ADC Plus-Side General Calibration Value Register, offset: 0x34 */
    __IO uint32_t CLPS;   /**< ADC Plus-Side General Calibration Value Register, offset: 0x38 */
    __IO uint32_t CLP4;   /**< ADC Plus-Side General Calibration Value Register, offset: 0x3C */
    __IO uint32_t CLP3;   /**< ADC Plus-Side General Calibration Value Register, offset: 0x40 */
    __IO uint32_t CLP2;   /**< ADC Plus-Side General Calibration Value Register, offset: 0x44 */
    __IO uint32_t CLP1;   /**< ADC Plus-Side General Calibration Value Register, offset: 0x48 */
    __IO uint32_t CLP0;   /**< ADC Plus-Side General Calibration Value Register, offset: 0x4C */
    uint8_t RESERVED_0[4];
    __IO uint32_t CLMD; /**< ADC Minus-Side General Calibration Value Register, offset: 0x54 */
    __IO uint32_t CLMS; /**< ADC Minus-Side General Calibration Value Register, offset: 0x58 */
    __IO uint32_t CLM4; /**< ADC Minus-Side General Calibration Value Register, offset: 0x5C */
    __IO uint32_t CLM3; /**< ADC Minus-Side General Calibration Value Register, offset: 0x60 */
    __IO uint32_t CLM2; /**< ADC Minus-Side General Calibration Value Register, offset: 0x64 */
    __IO uint32_t CLM1; /**< ADC Minus-Side General Calibration Value Register, offset: 0x68 */
    __IO uint32_t CLM0; /**< ADC Minus-Side General Calibration Value Register, offset: 0x6C */
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
#define ADC_SC1_ADCH_MASK (0x1FU)
#define ADC_SC1_ADCH_SHIFT (0U)
/*! ADCH - Input channel select
 *  0b00000..When DIFF=0, DADP0 is selected as input; when DIFF=1, DAD0 is selected as input.
 *  0b00001..When DIFF=0, DADP1 is selected as input; when DIFF=1, DAD1 is selected as input.
 *  0b00010..When DIFF=0, DADP2 is selected as input; when DIFF=1, DAD2 is selected as input.
 *  0b00011..When DIFF=0, DADP3 is selected as input; when DIFF=1, DAD3 is selected as input.
 *  0b00100..When DIFF=0, AD4 is selected as input; when DIFF=1, it is reserved.
 *  0b00101..When DIFF=0, AD5 is selected as input; when DIFF=1, it is reserved.
 *  0b00110..When DIFF=0, AD6 is selected as input; when DIFF=1, it is reserved.
 *  0b00111..When DIFF=0, AD7 is selected as input; when DIFF=1, it is reserved.
 *  0b01000..When DIFF=0, AD8 is selected as input; when DIFF=1, it is reserved.
 *  0b01001..When DIFF=0, AD9 is selected as input; when DIFF=1, it is reserved.
 *  0b01010..When DIFF=0, AD10 is selected as input; when DIFF=1, it is reserved.
 *  0b01011..When DIFF=0, AD11 is selected as input; when DIFF=1, it is reserved.
 *  0b01100..When DIFF=0, AD12 is selected as input; when DIFF=1, it is reserved.
 *  0b01101..When DIFF=0, AD13 is selected as input; when DIFF=1, it is reserved.
 *  0b01110..When DIFF=0, AD14 is selected as input; when DIFF=1, it is reserved.
 *  0b01111..When DIFF=0, AD15 is selected as input; when DIFF=1, it is reserved.
 *  0b10000..When DIFF=0, AD16 is selected as input; when DIFF=1, it is reserved.
 *  0b10001..When DIFF=0, AD17 is selected as input; when DIFF=1, it is reserved.
 *  0b10010..When DIFF=0, AD18 is selected as input; when DIFF=1, it is reserved.
 *  0b10011..When DIFF=0, AD19 is selected as input; when DIFF=1, it is reserved.
 *  0b10100..When DIFF=0, AD20 is selected as input; when DIFF=1, it is reserved.
 *  0b10101..When DIFF=0, AD21 is selected as input; when DIFF=1, it is reserved.
 *  0b10110..When DIFF=0, AD22 is selected as input; when DIFF=1, it is reserved.
 *  0b10111..When DIFF=0, AD23 is selected as input; when DIFF=1, it is reserved.
 *  0b11000..Reserved.
 *  0b11001..Reserved.
 *  0b11010..When DIFF=0, Temp Sensor (single-ended) is selected as input; when DIFF=1, Temp Sensor (differential) is
 * selected as input. 0b11011..When DIFF=0, Bandgap (single-ended) is selected as input; when DIFF=1, Bandgap
 * (differential) is selected as input. 0b11100..Reserved. 0b11101..When DIFF=0,VREFSH is selected as input; when
 * DIFF=1, -VREFSH (differential) is selected as input. Voltage reference selected is determined by SC2[REFSEL].
 *  0b11110..When DIFF=0,VREFSL is selected as input; when DIFF=1, it is reserved. Voltage reference selected is
 * determined by SC2[REFSEL]. 0b11111..Module is disabled.
 */
#define ADC_SC1_ADCH(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC1_ADCH_SHIFT)) & ADC_SC1_ADCH_MASK)
#define ADC_SC1_DIFF_MASK (0x20U)
#define ADC_SC1_DIFF_SHIFT (5U)
/*! DIFF - Differential Mode Enable
 *  0b0..Single-ended conversions and input channels are selected.
 *  0b1..Differential conversions and input channels are selected.
 */
#define ADC_SC1_DIFF(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC1_DIFF_SHIFT)) & ADC_SC1_DIFF_MASK)
#define ADC_SC1_AIEN_MASK (0x40U)
#define ADC_SC1_AIEN_SHIFT (6U)
/*! AIEN - Interrupt Enable
 *  0b0..Conversion complete interrupt is disabled.
 *  0b1..Conversion complete interrupt is enabled.
 */
#define ADC_SC1_AIEN(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC1_AIEN_SHIFT)) & ADC_SC1_AIEN_MASK)
#define ADC_SC1_COCO_MASK (0x80U)
#define ADC_SC1_COCO_SHIFT (7U)
/*! COCO - Conversion Complete Flag
 *  0b0..Conversion is not completed.
 *  0b1..Conversion is completed.
 */
#define ADC_SC1_COCO(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC1_COCO_SHIFT)) & ADC_SC1_COCO_MASK)
/*! @} */

/* The count of ADC_SC1 */
#define ADC_SC1_COUNT (2U)

/*! @name CFG1 - ADC Configuration Register 1 */
/*! @{ */
#define ADC_CFG1_ADICLK_MASK (0x3U)
#define ADC_CFG1_ADICLK_SHIFT (0U)
/*! ADICLK - Input Clock Select
 *  0b00..Bus clock
 *  0b01..Bus clock divided by 2(BUSCLK/2)
 *  0b10..Alternate clock (ALTCLK)
 *  0b11..Asynchronous clock (ADACK)
 */
#define ADC_CFG1_ADICLK(x) (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADICLK_SHIFT)) & ADC_CFG1_ADICLK_MASK)
#define ADC_CFG1_MODE_MASK (0xCU)
#define ADC_CFG1_MODE_SHIFT (2U)
/*! MODE - Conversion mode selection
 *  0b00..When DIFF=0:It is single-ended 8-bit conversion; when DIFF=1, it is differential 9-bit conversion with 2's
 * complement output. 0b01..When DIFF=0:It is single-ended 12-bit conversion ; when DIFF=1, it is differential 13-bit
 * conversion with 2's complement output. 0b10..When DIFF=0:It is single-ended 10-bit conversion. ; when DIFF=1, it is
 * differential 11-bit conversion with 2's complement output 0b11..When DIFF=0:It is single-ended 16-bit conversion..;
 * when DIFF=1, it is differential 16-bit conversion with 2's complement output
 */
#define ADC_CFG1_MODE(x) (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_MODE_SHIFT)) & ADC_CFG1_MODE_MASK)
#define ADC_CFG1_ADLSMP_MASK (0x10U)
#define ADC_CFG1_ADLSMP_SHIFT (4U)
/*! ADLSMP - Sample Time Configuration
 *  0b0..Short sample time.
 *  0b1..Long sample time.
 */
#define ADC_CFG1_ADLSMP(x) (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADLSMP_SHIFT)) & ADC_CFG1_ADLSMP_MASK)
#define ADC_CFG1_ADIV_MASK (0x60U)
#define ADC_CFG1_ADIV_SHIFT (5U)
/*! ADIV - Clock Divide Select
 *  0b00..The divide ratio is 1 and the clock rate is input clock.
 *  0b01..The divide ratio is 2 and the clock rate is (input clock)/2.
 *  0b10..The divide ratio is 4 and the clock rate is (input clock)/4.
 *  0b11..The divide ratio is 8 and the clock rate is (input clock)/8.
 */
#define ADC_CFG1_ADIV(x) (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADIV_SHIFT)) & ADC_CFG1_ADIV_MASK)
#define ADC_CFG1_ADLPC_MASK (0x80U)
#define ADC_CFG1_ADLPC_SHIFT (7U)
/*! ADLPC - Low-Power Configuration
 *  0b0..Normal power configuration.
 *  0b1..Low-power configuration. The power is reduced at the expense of maximum clock speed.
 */
#define ADC_CFG1_ADLPC(x) (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADLPC_SHIFT)) & ADC_CFG1_ADLPC_MASK)
/*! @} */

/*! @name CFG2 - ADC Configuration Register 2 */
/*! @{ */
#define ADC_CFG2_ADLSTS_MASK (0x3U)
#define ADC_CFG2_ADLSTS_SHIFT (0U)
/*! ADLSTS - Long Sample Time Select
 *  0b00..Default longest sample time; 20 extra ADCK cycles; 24 ADCK cycles total.
 *  0b01..12 extra ADCK cycles; 16 ADCK cycles total sample time.
 *  0b10..6 extra ADCK cycles; 10 ADCK cycles total sample time.
 *  0b11..2 extra ADCK cycles; 6 ADCK cycles total sample time.
 */
#define ADC_CFG2_ADLSTS(x) (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_ADLSTS_SHIFT)) & ADC_CFG2_ADLSTS_MASK)
#define ADC_CFG2_ADHSC_MASK (0x4U)
#define ADC_CFG2_ADHSC_SHIFT (2U)
/*! ADHSC - High-Speed Configuration
 *  0b0..Normal conversion sequence selected.
 *  0b1..High-speed conversion sequence selected with 2 additional ADCK cycles to total conversion time.
 */
#define ADC_CFG2_ADHSC(x) (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_ADHSC_SHIFT)) & ADC_CFG2_ADHSC_MASK)
#define ADC_CFG2_ADACKEN_MASK (0x8U)
#define ADC_CFG2_ADACKEN_SHIFT (3U)
/*! ADACKEN - Asynchronous Clock Output Enable
 *  0b0..Asynchronous clock output disabled; Asynchronous clock is enabled only if selected by ADICLK and a conversion
 * is active. 0b1..Asynchronous clock and clock output is enabled regardless of the state of the ADC.
 */
#define ADC_CFG2_ADACKEN(x) (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_ADACKEN_SHIFT)) & ADC_CFG2_ADACKEN_MASK)
#define ADC_CFG2_MUXSEL_MASK (0x10U)
#define ADC_CFG2_MUXSEL_SHIFT (4U)
/*! MUXSEL - ADC Mux Select
 *  0b0..ADxxa channels are selected.
 *  0b1..ADxxb channels are selected.
 */
#define ADC_CFG2_MUXSEL(x) (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_MUXSEL_SHIFT)) & ADC_CFG2_MUXSEL_MASK)
/*! @} */

/*! @name R - ADC Data Result Register */
/*! @{ */
#define ADC_R_D_MASK (0xFFFFU)
#define ADC_R_D_SHIFT (0U)
/*! D - Data result
 */
#define ADC_R_D(x) (((uint32_t)(((uint32_t)(x)) << ADC_R_D_SHIFT)) & ADC_R_D_MASK)
/*! @} */

/* The count of ADC_R */
#define ADC_R_COUNT (2U)

/*! @name CV1 - Compare Value Registers */
/*! @{ */
#define ADC_CV1_CV_MASK (0xFFFFU)
#define ADC_CV1_CV_SHIFT (0U)
/*! CV - Compare Value.
 */
#define ADC_CV1_CV(x) (((uint32_t)(((uint32_t)(x)) << ADC_CV1_CV_SHIFT)) & ADC_CV1_CV_MASK)
/*! @} */

/*! @name CV2 - Compare Value Registers */
/*! @{ */
#define ADC_CV2_CV_MASK (0xFFFFU)
#define ADC_CV2_CV_SHIFT (0U)
/*! CV - Compare Value.
 */
#define ADC_CV2_CV(x) (((uint32_t)(((uint32_t)(x)) << ADC_CV2_CV_SHIFT)) & ADC_CV2_CV_MASK)
/*! @} */

/*! @name SC2 - Status and Control Register 2 */
/*! @{ */
#define ADC_SC2_REFSEL_MASK (0x3U)
#define ADC_SC2_REFSEL_SHIFT (0U)
/*! REFSEL - Voltage Reference Selection
 *  0b00..Default voltage reference pin pair, that is, external pins VREFH and VREFL
 *  0b01..Alternate reference pair, that is, VALTH and VALTL . This pair may be additional external pins or
 *        internal sources depending on the MCU configuration. See the chip configuration information for details
 *        specific to this MCU
 *  0b10..Reserved
 *  0b11..Reserved
 */
#define ADC_SC2_REFSEL(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC2_REFSEL_SHIFT)) & ADC_SC2_REFSEL_MASK)
#define ADC_SC2_DMAEN_MASK (0x4U)
#define ADC_SC2_DMAEN_SHIFT (2U)
/*! DMAEN - DMA Enable
 *  0b0..DMA is disabled.
 *  0b1..DMA is enabled and will assert the ADC DMA request during an ADC conversion complete event noted when any
 *       of the SC1n[COCO] flags is asserted.
 */
#define ADC_SC2_DMAEN(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC2_DMAEN_SHIFT)) & ADC_SC2_DMAEN_MASK)
#define ADC_SC2_ACREN_MASK (0x8U)
#define ADC_SC2_ACREN_SHIFT (3U)
/*! ACREN - Compare Function Range Enable
 *  0b0..Range function disabled. Only CV1 is compared.
 *  0b1..Range function enabled. Both CV1 and CV2 are compared.
 */
#define ADC_SC2_ACREN(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ACREN_SHIFT)) & ADC_SC2_ACREN_MASK)
#define ADC_SC2_ACFGT_MASK (0x10U)
#define ADC_SC2_ACFGT_SHIFT (4U)
/*! ACFGT - Compare Function Greater Than Enable
 *  0b0..Configures less than threshold, outside range not inclusive and inside range not inclusive; functionality
 *       based on the values placed in CV1 and CV2.
 *  0b1..Configures greater than or equal to threshold, outside and inside ranges inclusive; functionality based on the
 * values placed in CV1 and CV2.
 */
#define ADC_SC2_ACFGT(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ACFGT_SHIFT)) & ADC_SC2_ACFGT_MASK)
#define ADC_SC2_ACFE_MASK (0x20U)
#define ADC_SC2_ACFE_SHIFT (5U)
/*! ACFE - Compare Function Enable
 *  0b0..Compare function disabled.
 *  0b1..Compare function enabled.
 */
#define ADC_SC2_ACFE(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ACFE_SHIFT)) & ADC_SC2_ACFE_MASK)
#define ADC_SC2_ADTRG_MASK (0x40U)
#define ADC_SC2_ADTRG_SHIFT (6U)
/*! ADTRG - Conversion Trigger Select
 *  0b0..Software trigger selected.
 *  0b1..Hardware trigger selected.
 */
#define ADC_SC2_ADTRG(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ADTRG_SHIFT)) & ADC_SC2_ADTRG_MASK)
#define ADC_SC2_ADACT_MASK (0x80U)
#define ADC_SC2_ADACT_SHIFT (7U)
/*! ADACT - Conversion Active
 *  0b0..Conversion not in progress.
 *  0b1..Conversion in progress.
 */
#define ADC_SC2_ADACT(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ADACT_SHIFT)) & ADC_SC2_ADACT_MASK)
/*! @} */

/*! @name SC3 - Status and Control Register 3 */
/*! @{ */
#define ADC_SC3_AVGS_MASK (0x3U)
#define ADC_SC3_AVGS_SHIFT (0U)
/*! AVGS - Hardware Average Select
 *  0b00..4 samples averaged.
 *  0b01..8 samples averaged.
 *  0b10..16 samples averaged.
 *  0b11..32 samples averaged.
 */
#define ADC_SC3_AVGS(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC3_AVGS_SHIFT)) & ADC_SC3_AVGS_MASK)
#define ADC_SC3_AVGE_MASK (0x4U)
#define ADC_SC3_AVGE_SHIFT (2U)
/*! AVGE - Hardware Average Enable
 *  0b0..Hardware average function disabled.
 *  0b1..Hardware average function enabled.
 */
#define ADC_SC3_AVGE(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC3_AVGE_SHIFT)) & ADC_SC3_AVGE_MASK)
#define ADC_SC3_ADCO_MASK (0x8U)
#define ADC_SC3_ADCO_SHIFT (3U)
/*! ADCO - Continuous Conversion Enable
 *  0b0..One conversion or one set of conversions if the hardware average function is enabled, that is, AVGE=1, after
 * initiating a conversion. 0b1..Continuous conversions or sets of conversions if the hardware average function is
 * enabled, that is, AVGE=1, after initiating a conversion.
 */
#define ADC_SC3_ADCO(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC3_ADCO_SHIFT)) & ADC_SC3_ADCO_MASK)
#define ADC_SC3_CALF_MASK (0x40U)
#define ADC_SC3_CALF_SHIFT (6U)
/*! CALF - Calibration Failed Flag
 *  0b0..Calibration completed normally.
 *  0b1..Calibration failed. ADC accuracy specifications are not guaranteed.
 */
#define ADC_SC3_CALF(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC3_CALF_SHIFT)) & ADC_SC3_CALF_MASK)
#define ADC_SC3_CAL_MASK (0x80U)
#define ADC_SC3_CAL_SHIFT (7U)
/*! CAL - Calibration
 */
#define ADC_SC3_CAL(x) (((uint32_t)(((uint32_t)(x)) << ADC_SC3_CAL_SHIFT)) & ADC_SC3_CAL_MASK)
/*! @} */

/*! @name OFS - ADC Offset Correction Register */
/*! @{ */
#define ADC_OFS_OFS_MASK (0xFFFFU)
#define ADC_OFS_OFS_SHIFT (0U)
/*! OFS - Offset Error Correction Value
 */
#define ADC_OFS_OFS(x) (((uint32_t)(((uint32_t)(x)) << ADC_OFS_OFS_SHIFT)) & ADC_OFS_OFS_MASK)
/*! @} */

/*! @name PG - ADC Plus-Side Gain Register */
/*! @{ */
#define ADC_PG_PG_MASK (0xFFFFU)
#define ADC_PG_PG_SHIFT (0U)
/*! PG - Plus-Side Gain
 */
#define ADC_PG_PG(x) (((uint32_t)(((uint32_t)(x)) << ADC_PG_PG_SHIFT)) & ADC_PG_PG_MASK)
/*! @} */

/*! @name MG - ADC Minus-Side Gain Register */
/*! @{ */
#define ADC_MG_MG_MASK (0xFFFFU)
#define ADC_MG_MG_SHIFT (0U)
/*! MG - Minus-Side Gain
 */
#define ADC_MG_MG(x) (((uint32_t)(((uint32_t)(x)) << ADC_MG_MG_SHIFT)) & ADC_MG_MG_MASK)
/*! @} */

/*! @name CLPD - ADC Plus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLPD_CLPD_MASK (0x3FU)
#define ADC_CLPD_CLPD_SHIFT (0U)
/*! CLPD - Calibration Value
 */
#define ADC_CLPD_CLPD(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLPD_CLPD_SHIFT)) & ADC_CLPD_CLPD_MASK)
/*! @} */

/*! @name CLPS - ADC Plus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLPS_CLPS_MASK (0x3FU)
#define ADC_CLPS_CLPS_SHIFT (0U)
/*! CLPS - Calibration Value
 */
#define ADC_CLPS_CLPS(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLPS_CLPS_SHIFT)) & ADC_CLPS_CLPS_MASK)
/*! @} */

/*! @name CLP4 - ADC Plus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLP4_CLP4_MASK (0x3FFU)
#define ADC_CLP4_CLP4_SHIFT (0U)
/*! CLP4 - Calibration Value
 */
#define ADC_CLP4_CLP4(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLP4_CLP4_SHIFT)) & ADC_CLP4_CLP4_MASK)
/*! @} */

/*! @name CLP3 - ADC Plus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLP3_CLP3_MASK (0x1FFU)
#define ADC_CLP3_CLP3_SHIFT (0U)
/*! CLP3 - Calibration Value
 */
#define ADC_CLP3_CLP3(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLP3_CLP3_SHIFT)) & ADC_CLP3_CLP3_MASK)
/*! @} */

/*! @name CLP2 - ADC Plus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLP2_CLP2_MASK (0xFFU)
#define ADC_CLP2_CLP2_SHIFT (0U)
/*! CLP2 - Calibration Value
 */
#define ADC_CLP2_CLP2(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLP2_CLP2_SHIFT)) & ADC_CLP2_CLP2_MASK)
/*! @} */

/*! @name CLP1 - ADC Plus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLP1_CLP1_MASK (0x7FU)
#define ADC_CLP1_CLP1_SHIFT (0U)
/*! CLP1 - Calibration Value
 */
#define ADC_CLP1_CLP1(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLP1_CLP1_SHIFT)) & ADC_CLP1_CLP1_MASK)
/*! @} */

/*! @name CLP0 - ADC Plus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLP0_CLP0_MASK (0x3FU)
#define ADC_CLP0_CLP0_SHIFT (0U)
/*! CLP0 - Calibration Value
 */
#define ADC_CLP0_CLP0(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLP0_CLP0_SHIFT)) & ADC_CLP0_CLP0_MASK)
/*! @} */

/*! @name CLMD - ADC Minus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLMD_CLMD_MASK (0x3FU)
#define ADC_CLMD_CLMD_SHIFT (0U)
/*! CLMD - Calibration Value
 */
#define ADC_CLMD_CLMD(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLMD_CLMD_SHIFT)) & ADC_CLMD_CLMD_MASK)
/*! @} */

/*! @name CLMS - ADC Minus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLMS_CLMS_MASK (0x3FU)
#define ADC_CLMS_CLMS_SHIFT (0U)
/*! CLMS - Calibration Value
 */
#define ADC_CLMS_CLMS(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLMS_CLMS_SHIFT)) & ADC_CLMS_CLMS_MASK)
/*! @} */

/*! @name CLM4 - ADC Minus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLM4_CLM4_MASK (0x3FFU)
#define ADC_CLM4_CLM4_SHIFT (0U)
/*! CLM4 - Calibration Value
 */
#define ADC_CLM4_CLM4(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLM4_CLM4_SHIFT)) & ADC_CLM4_CLM4_MASK)
/*! @} */

/*! @name CLM3 - ADC Minus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLM3_CLM3_MASK (0x1FFU)
#define ADC_CLM3_CLM3_SHIFT (0U)
/*! CLM3 - Calibration Value
 */
#define ADC_CLM3_CLM3(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLM3_CLM3_SHIFT)) & ADC_CLM3_CLM3_MASK)
/*! @} */

/*! @name CLM2 - ADC Minus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLM2_CLM2_MASK (0xFFU)
#define ADC_CLM2_CLM2_SHIFT (0U)
/*! CLM2 - Calibration Value
 */
#define ADC_CLM2_CLM2(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLM2_CLM2_SHIFT)) & ADC_CLM2_CLM2_MASK)
/*! @} */

/*! @name CLM1 - ADC Minus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLM1_CLM1_MASK (0x7FU)
#define ADC_CLM1_CLM1_SHIFT (0U)
/*! CLM1 - Calibration Value
 */
#define ADC_CLM1_CLM1(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLM1_CLM1_SHIFT)) & ADC_CLM1_CLM1_MASK)
/*! @} */

/*! @name CLM0 - ADC Minus-Side General Calibration Value Register */
/*! @{ */
#define ADC_CLM0_CLM0_MASK (0x3FU)
#define ADC_CLM0_CLM0_SHIFT (0U)
/*! CLM0 - Calibration Value
 */
#define ADC_CLM0_CLM0(x) (((uint32_t)(((uint32_t)(x)) << ADC_CLM0_CLM0_SHIFT)) & ADC_CLM0_CLM0_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group ADC_Register_Masks */

/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base address */
#define ADC0_BASE (0x40066000u)
/** Peripheral ADC0 base pointer */
#define ADC0 ((ADC_Type *)ADC0_BASE)
/** Array initializer of ADC peripheral base addresses */
#define ADC_BASE_ADDRS \
    {                  \
        ADC0_BASE      \
    }
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS \
    {                 \
        ADC0          \
    }
/** Interrupt vectors for the ADC peripheral type */
#define ADC_IRQS  \
    {             \
        ADC0_IRQn \
    }

/*!
 * @}
 */ /* end of group ADC_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- CAU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAU_Peripheral_Access_Layer CAU Peripheral Access Layer
 * @{
 */

/** CAU - Register Layout Typedef */
typedef struct
{
    __O uint32_t
        DIRECT[16]; /**< Direct access register 0..Direct access register 15, array offset: 0x0, array step: 0x4 */
    uint8_t RESERVED_0[2048];
    __O uint32_t LDR_CASR;  /**< Status register - Load Register command, offset: 0x840 */
    __O uint32_t LDR_CAA;   /**< Accumulator register - Load Register command, offset: 0x844 */
    __O uint32_t LDR_CA[9]; /**< General Purpose Register 0 - Load Register command..General Purpose Register 8 - Load
                               Register command, array offset: 0x848, array step: 0x4 */
    uint8_t RESERVED_1[20];
    __I uint32_t STR_CASR;  /**< Status register - Store Register command, offset: 0x880 */
    __I uint32_t STR_CAA;   /**< Accumulator register - Store Register command, offset: 0x884 */
    __I uint32_t STR_CA[9]; /**< General Purpose Register 0 - Store Register command..General Purpose Register 8 - Store
                               Register command, array offset: 0x888, array step: 0x4 */
    uint8_t RESERVED_2[20];
    __O uint32_t ADR_CASR;  /**< Status register - Add Register command, offset: 0x8C0 */
    __O uint32_t ADR_CAA;   /**< Accumulator register - Add to register command, offset: 0x8C4 */
    __O uint32_t ADR_CA[9]; /**< General Purpose Register 0 - Add to register command..General Purpose Register 8 - Add
                               to register command, array offset: 0x8C8, array step: 0x4 */
    uint8_t RESERVED_3[20];
    __O uint32_t RADR_CASR; /**< Status register - Reverse and Add to Register command, offset: 0x900 */
    __O uint32_t RADR_CAA;  /**< Accumulator register - Reverse and Add to Register command, offset: 0x904 */
    __O uint32_t
        RADR_CA[9]; /**< General Purpose Register 0 - Reverse and Add to Register command..General Purpose Register 8 -
                       Reverse and Add to Register command, array offset: 0x908, array step: 0x4 */
    uint8_t RESERVED_4[84];
    __O uint32_t XOR_CASR;  /**< Status register - Exclusive Or command, offset: 0x980 */
    __O uint32_t XOR_CAA;   /**< Accumulator register - Exclusive Or command, offset: 0x984 */
    __O uint32_t XOR_CA[9]; /**< General Purpose Register 0 - Exclusive Or command..General Purpose Register 8 -
                               Exclusive Or command, array offset: 0x988, array step: 0x4 */
    uint8_t RESERVED_5[20];
    __O uint32_t ROTL_CASR;  /**< Status register - Rotate Left command, offset: 0x9C0 */
    __O uint32_t ROTL_CAA;   /**< Accumulator register - Rotate Left command, offset: 0x9C4 */
    __O uint32_t ROTL_CA[9]; /**< General Purpose Register 0 - Rotate Left command..General Purpose Register 8 - Rotate
                                Left command, array offset: 0x9C8, array step: 0x4 */
    uint8_t RESERVED_6[276];
    __O uint32_t AESC_CASR;  /**< Status register - AES Column Operation command, offset: 0xB00 */
    __O uint32_t AESC_CAA;   /**< Accumulator register - AES Column Operation command, offset: 0xB04 */
    __O uint32_t AESC_CA[9]; /**< General Purpose Register 0 - AES Column Operation command..General Purpose Register 8
                                - AES Column Operation command, array offset: 0xB08, array step: 0x4 */
    uint8_t RESERVED_7[20];
    __O uint32_t AESIC_CASR; /**< Status register - AES Inverse Column Operation command, offset: 0xB40 */
    __O uint32_t AESIC_CAA;  /**< Accumulator register - AES Inverse Column Operation command, offset: 0xB44 */
    __O uint32_t
        AESIC_CA[9]; /**< General Purpose Register 0 - AES Inverse Column Operation command..General Purpose Register 8
                        - AES Inverse Column Operation command, array offset: 0xB48, array step: 0x4 */
} CAU_Type;

/* ----------------------------------------------------------------------------
   -- CAU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAU_Register_Masks CAU Register Masks
 * @{
 */

/*! @name DIRECT - Direct access register 0..Direct access register 15 */
/*! @{ */
#define CAU_DIRECT_CAU_DIRECT0_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT0_SHIFT (0U)
/*! CAU_DIRECT0 - Direct register 0
 */
#define CAU_DIRECT_CAU_DIRECT0(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT0_SHIFT)) & CAU_DIRECT_CAU_DIRECT0_MASK)
#define CAU_DIRECT_CAU_DIRECT1_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT1_SHIFT (0U)
/*! CAU_DIRECT1 - Direct register 1
 */
#define CAU_DIRECT_CAU_DIRECT1(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT1_SHIFT)) & CAU_DIRECT_CAU_DIRECT1_MASK)
#define CAU_DIRECT_CAU_DIRECT2_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT2_SHIFT (0U)
/*! CAU_DIRECT2 - Direct register 2
 */
#define CAU_DIRECT_CAU_DIRECT2(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT2_SHIFT)) & CAU_DIRECT_CAU_DIRECT2_MASK)
#define CAU_DIRECT_CAU_DIRECT3_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT3_SHIFT (0U)
/*! CAU_DIRECT3 - Direct register 3
 */
#define CAU_DIRECT_CAU_DIRECT3(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT3_SHIFT)) & CAU_DIRECT_CAU_DIRECT3_MASK)
#define CAU_DIRECT_CAU_DIRECT4_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT4_SHIFT (0U)
/*! CAU_DIRECT4 - Direct register 4
 */
#define CAU_DIRECT_CAU_DIRECT4(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT4_SHIFT)) & CAU_DIRECT_CAU_DIRECT4_MASK)
#define CAU_DIRECT_CAU_DIRECT5_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT5_SHIFT (0U)
/*! CAU_DIRECT5 - Direct register 5
 */
#define CAU_DIRECT_CAU_DIRECT5(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT5_SHIFT)) & CAU_DIRECT_CAU_DIRECT5_MASK)
#define CAU_DIRECT_CAU_DIRECT6_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT6_SHIFT (0U)
/*! CAU_DIRECT6 - Direct register 6
 */
#define CAU_DIRECT_CAU_DIRECT6(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT6_SHIFT)) & CAU_DIRECT_CAU_DIRECT6_MASK)
#define CAU_DIRECT_CAU_DIRECT7_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT7_SHIFT (0U)
/*! CAU_DIRECT7 - Direct register 7
 */
#define CAU_DIRECT_CAU_DIRECT7(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT7_SHIFT)) & CAU_DIRECT_CAU_DIRECT7_MASK)
#define CAU_DIRECT_CAU_DIRECT8_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT8_SHIFT (0U)
/*! CAU_DIRECT8 - Direct register 8
 */
#define CAU_DIRECT_CAU_DIRECT8(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT8_SHIFT)) & CAU_DIRECT_CAU_DIRECT8_MASK)
#define CAU_DIRECT_CAU_DIRECT9_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT9_SHIFT (0U)
/*! CAU_DIRECT9 - Direct register 9
 */
#define CAU_DIRECT_CAU_DIRECT9(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT9_SHIFT)) & CAU_DIRECT_CAU_DIRECT9_MASK)
#define CAU_DIRECT_CAU_DIRECT10_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT10_SHIFT (0U)
/*! CAU_DIRECT10 - Direct register 10
 */
#define CAU_DIRECT_CAU_DIRECT10(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT10_SHIFT)) & CAU_DIRECT_CAU_DIRECT10_MASK)
#define CAU_DIRECT_CAU_DIRECT11_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT11_SHIFT (0U)
/*! CAU_DIRECT11 - Direct register 11
 */
#define CAU_DIRECT_CAU_DIRECT11(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT11_SHIFT)) & CAU_DIRECT_CAU_DIRECT11_MASK)
#define CAU_DIRECT_CAU_DIRECT12_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT12_SHIFT (0U)
/*! CAU_DIRECT12 - Direct register 12
 */
#define CAU_DIRECT_CAU_DIRECT12(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT12_SHIFT)) & CAU_DIRECT_CAU_DIRECT12_MASK)
#define CAU_DIRECT_CAU_DIRECT13_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT13_SHIFT (0U)
/*! CAU_DIRECT13 - Direct register 13
 */
#define CAU_DIRECT_CAU_DIRECT13(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT13_SHIFT)) & CAU_DIRECT_CAU_DIRECT13_MASK)
#define CAU_DIRECT_CAU_DIRECT14_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT14_SHIFT (0U)
/*! CAU_DIRECT14 - Direct register 14
 */
#define CAU_DIRECT_CAU_DIRECT14(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT14_SHIFT)) & CAU_DIRECT_CAU_DIRECT14_MASK)
#define CAU_DIRECT_CAU_DIRECT15_MASK (0xFFFFFFFFU)
#define CAU_DIRECT_CAU_DIRECT15_SHIFT (0U)
/*! CAU_DIRECT15 - Direct register 15
 */
#define CAU_DIRECT_CAU_DIRECT15(x) \
    (((uint32_t)(((uint32_t)(x)) << CAU_DIRECT_CAU_DIRECT15_SHIFT)) & CAU_DIRECT_CAU_DIRECT15_MASK)
/*! @} */

/* The count of CAU_DIRECT */
#define CAU_DIRECT_COUNT (16U)

/*! @name LDR_CASR - Status register - Load Register command */
/*! @{ */
#define CAU_LDR_CASR_IC_MASK (0x1U)
#define CAU_LDR_CASR_IC_SHIFT (0U)
/*! IC
 *  0b0..No illegal commands issued
 *  0b1..Illegal command issued
 */
#define CAU_LDR_CASR_IC(x) (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CASR_IC_SHIFT)) & CAU_LDR_CASR_IC_MASK)
#define CAU_LDR_CASR_DPE_MASK (0x2U)
#define CAU_LDR_CASR_DPE_SHIFT (1U)
/*! DPE
 *  0b0..No error detected
 *  0b1..DES key parity error detected
 */
#define CAU_LDR_CASR_DPE(x) (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CASR_DPE_SHIFT)) & CAU_LDR_CASR_DPE_MASK)
#define CAU_LDR_CASR_VER_MASK (0xF0000000U)
#define CAU_LDR_CASR_VER_SHIFT (28U)
/*! VER - CAU version
 *  0b0001..Initial CAU version
 *  0b0010..Second version, added support for SHA-256 algorithm.(This is the value on this device)
 */
#define CAU_LDR_CASR_VER(x) (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CASR_VER_SHIFT)) & CAU_LDR_CASR_VER_MASK)
/*! @} */

/*! @name LDR_CAA - Accumulator register - Load Register command */
/*! @{ */
#define CAU_LDR_CAA_ACC_MASK (0xFFFFFFFFU)
#define CAU_LDR_CAA_ACC_SHIFT (0U)
/*! ACC - ACC
 */
#define CAU_LDR_CAA_ACC(x) (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CAA_ACC_SHIFT)) & CAU_LDR_CAA_ACC_MASK)
/*! @} */

/*! @name LDR_CA - General Purpose Register 0 - Load Register command..General Purpose Register 8 - Load Register
 * command */
/*! @{ */
#define CAU_LDR_CA_CA0_MASK (0xFFFFFFFFU)
#define CAU_LDR_CA_CA0_SHIFT (0U)
/*! CA0 - CA0
 */
#define CAU_LDR_CA_CA0(x) (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA0_SHIFT)) & CAU_LDR_CA_CA0_MASK)
#define CAU_LDR_CA_CA1_MASK (0xFFFFFFFFU)
#define CAU_LDR_CA_CA1_SHIFT (0U)
/*! CA1 - CA1
 */
#define CAU_LDR_CA_CA1(x) (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA1_SHIFT)) & CAU_LDR_CA_CA1_MASK)
#define CAU_LDR_CA_CA2_MASK (0xFFFFFFFFU)
#define CAU_LDR_CA_CA2_SHIFT (0U)
/*! CA2 - CA2
 */
#define CAU_LDR_CA_CA2(x) (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA2_SHIFT)) & CAU_LDR_CA_CA2_MASK)
#define CAU_LDR_CA_CA3_MASK (0xFFFFFFFFU)
#define CAU_LDR_CA_CA3_SHIFT (0U)
/*! CA3 - CA3
 */
#define CAU_LDR_CA_CA3(x) (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA3_SHIFT)) & CAU_LDR_CA_CA3_MASK)
#define CAU_LDR_CA_CA4_MASK (0xFFFFFFFFU)
#define CAU_LDR_CA_CA4_SHIFT (0U)
/*! CA4 - CA4
 */
#define CAU_LDR_CA_CA4(x) (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA4_SHIFT)) & CAU_LDR_CA_CA4_MASK)
#define CAU_LDR_CA_CA5_MASK (0xFFFFFFFFU)
#define CAU_LDR_CA_CA5_SHIFT (0U)
/*! CA5 - CA5
 */
#define CAU_LDR_CA_CA5(x) (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA5_SHIFT)) & CAU_LDR_CA_CA5_MASK)
#define CAU_LDR_CA_CA6_MASK (0xFFFFFFFFU)
#define CAU_LDR_CA_CA6_SHIFT (0U)
/*! CA6 - CA6
 */
#define CAU_LDR_CA_CA6(x) (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA6_SHIFT)) & CAU_LDR_CA_CA6_MASK)
#define CAU_LDR_CA_CA7_MASK (0xFFFFFFFFU)
#define CAU_LDR_CA_CA7_SHIFT (0U)
/*! CA7 - CA7
 */
#define CAU_LDR_CA_CA7(x) (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA7_SHIFT)) & CAU_LDR_CA_CA7_MASK)
#define CAU_LDR_CA_CA8_MASK (0xFFFFFFFFU)
#define CAU_LDR_CA_CA8_SHIFT (0U)
/*! CA8 - CA8
 */
#define CAU_LDR_CA_CA8(x) (((uint32_t)(((uint32_t)(x)) << CAU_LDR_CA_CA8_SHIFT)) & CAU_LDR_CA_CA8_MASK)
/*! @} */

/* The count of CAU_LDR_CA */
#define CAU_LDR_CA_COUNT (9U)

/*! @name STR_CASR - Status register - Store Register command */
/*! @{ */
#define CAU_STR_CASR_IC_MASK (0x1U)
#define CAU_STR_CASR_IC_SHIFT (0U)
/*! IC
 *  0b0..No illegal commands issued
 *  0b1..Illegal command issued
 */
#define CAU_STR_CASR_IC(x) (((uint32_t)(((uint32_t)(x)) << CAU_STR_CASR_IC_SHIFT)) & CAU_STR_CASR_IC_MASK)
#define CAU_STR_CASR_DPE_MASK (0x2U)
#define CAU_STR_CASR_DPE_SHIFT (1U)
/*! DPE
 *  0b0..No error detected
 *  0b1..DES key parity error detected
 */
#define CAU_STR_CASR_DPE(x) (((uint32_t)(((uint32_t)(x)) << CAU_STR_CASR_DPE_SHIFT)) & CAU_STR_CASR_DPE_MASK)
#define CAU_STR_CASR_VER_MASK (0xF0000000U)
#define CAU_STR_CASR_VER_SHIFT (28U)
/*! VER - CAU version
 *  0b0001..Initial CAU version
 *  0b0010..Second version, added support for SHA-256 algorithm.(This is the value on this device)
 */
#define CAU_STR_CASR_VER(x) (((uint32_t)(((uint32_t)(x)) << CAU_STR_CASR_VER_SHIFT)) & CAU_STR_CASR_VER_MASK)
/*! @} */

/*! @name STR_CAA - Accumulator register - Store Register command */
/*! @{ */
#define CAU_STR_CAA_ACC_MASK (0xFFFFFFFFU)
#define CAU_STR_CAA_ACC_SHIFT (0U)
/*! ACC - ACC
 */
#define CAU_STR_CAA_ACC(x) (((uint32_t)(((uint32_t)(x)) << CAU_STR_CAA_ACC_SHIFT)) & CAU_STR_CAA_ACC_MASK)
/*! @} */

/*! @name STR_CA - General Purpose Register 0 - Store Register command..General Purpose Register 8 - Store Register
 * command */
/*! @{ */
#define CAU_STR_CA_CA0_MASK (0xFFFFFFFFU)
#define CAU_STR_CA_CA0_SHIFT (0U)
/*! CA0 - CA0
 */
#define CAU_STR_CA_CA0(x) (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA0_SHIFT)) & CAU_STR_CA_CA0_MASK)
#define CAU_STR_CA_CA1_MASK (0xFFFFFFFFU)
#define CAU_STR_CA_CA1_SHIFT (0U)
/*! CA1 - CA1
 */
#define CAU_STR_CA_CA1(x) (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA1_SHIFT)) & CAU_STR_CA_CA1_MASK)
#define CAU_STR_CA_CA2_MASK (0xFFFFFFFFU)
#define CAU_STR_CA_CA2_SHIFT (0U)
/*! CA2 - CA2
 */
#define CAU_STR_CA_CA2(x) (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA2_SHIFT)) & CAU_STR_CA_CA2_MASK)
#define CAU_STR_CA_CA3_MASK (0xFFFFFFFFU)
#define CAU_STR_CA_CA3_SHIFT (0U)
/*! CA3 - CA3
 */
#define CAU_STR_CA_CA3(x) (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA3_SHIFT)) & CAU_STR_CA_CA3_MASK)
#define CAU_STR_CA_CA4_MASK (0xFFFFFFFFU)
#define CAU_STR_CA_CA4_SHIFT (0U)
/*! CA4 - CA4
 */
#define CAU_STR_CA_CA4(x) (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA4_SHIFT)) & CAU_STR_CA_CA4_MASK)
#define CAU_STR_CA_CA5_MASK (0xFFFFFFFFU)
#define CAU_STR_CA_CA5_SHIFT (0U)
/*! CA5 - CA5
 */
#define CAU_STR_CA_CA5(x) (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA5_SHIFT)) & CAU_STR_CA_CA5_MASK)
#define CAU_STR_CA_CA6_MASK (0xFFFFFFFFU)
#define CAU_STR_CA_CA6_SHIFT (0U)
/*! CA6 - CA6
 */
#define CAU_STR_CA_CA6(x) (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA6_SHIFT)) & CAU_STR_CA_CA6_MASK)
#define CAU_STR_CA_CA7_MASK (0xFFFFFFFFU)
#define CAU_STR_CA_CA7_SHIFT (0U)
/*! CA7 - CA7
 */
#define CAU_STR_CA_CA7(x) (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA7_SHIFT)) & CAU_STR_CA_CA7_MASK)
#define CAU_STR_CA_CA8_MASK (0xFFFFFFFFU)
#define CAU_STR_CA_CA8_SHIFT (0U)
/*! CA8 - CA8
 */
#define CAU_STR_CA_CA8(x) (((uint32_t)(((uint32_t)(x)) << CAU_STR_CA_CA8_SHIFT)) & CAU_STR_CA_CA8_MASK)
/*! @} */

/* The count of CAU_STR_CA */
#define CAU_STR_CA_COUNT (9U)

/*! @name ADR_CASR - Status register - Add Register command */
/*! @{ */
#define CAU_ADR_CASR_IC_MASK (0x1U)
#define CAU_ADR_CASR_IC_SHIFT (0U)
/*! IC
 *  0b0..No illegal commands issued
 *  0b1..Illegal command issued
 */
#define CAU_ADR_CASR_IC(x) (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CASR_IC_SHIFT)) & CAU_ADR_CASR_IC_MASK)
#define CAU_ADR_CASR_DPE_MASK (0x2U)
#define CAU_ADR_CASR_DPE_SHIFT (1U)
/*! DPE
 *  0b0..No error detected
 *  0b1..DES key parity error detected
 */
#define CAU_ADR_CASR_DPE(x) (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CASR_DPE_SHIFT)) & CAU_ADR_CASR_DPE_MASK)
#define CAU_ADR_CASR_VER_MASK (0xF0000000U)
#define CAU_ADR_CASR_VER_SHIFT (28U)
/*! VER - CAU version
 *  0b0001..Initial CAU version
 *  0b0010..Second version, added support for SHA-256 algorithm.(This is the value on this device)
 */
#define CAU_ADR_CASR_VER(x) (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CASR_VER_SHIFT)) & CAU_ADR_CASR_VER_MASK)
/*! @} */

/*! @name ADR_CAA - Accumulator register - Add to register command */
/*! @{ */
#define CAU_ADR_CAA_ACC_MASK (0xFFFFFFFFU)
#define CAU_ADR_CAA_ACC_SHIFT (0U)
/*! ACC - ACC
 */
#define CAU_ADR_CAA_ACC(x) (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CAA_ACC_SHIFT)) & CAU_ADR_CAA_ACC_MASK)
/*! @} */

/*! @name ADR_CA - General Purpose Register 0 - Add to register command..General Purpose Register 8 - Add to register
 * command */
/*! @{ */
#define CAU_ADR_CA_CA0_MASK (0xFFFFFFFFU)
#define CAU_ADR_CA_CA0_SHIFT (0U)
/*! CA0 - CA0
 */
#define CAU_ADR_CA_CA0(x) (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA0_SHIFT)) & CAU_ADR_CA_CA0_MASK)
#define CAU_ADR_CA_CA1_MASK (0xFFFFFFFFU)
#define CAU_ADR_CA_CA1_SHIFT (0U)
/*! CA1 - CA1
 */
#define CAU_ADR_CA_CA1(x) (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA1_SHIFT)) & CAU_ADR_CA_CA1_MASK)
#define CAU_ADR_CA_CA2_MASK (0xFFFFFFFFU)
#define CAU_ADR_CA_CA2_SHIFT (0U)
/*! CA2 - CA2
 */
#define CAU_ADR_CA_CA2(x) (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA2_SHIFT)) & CAU_ADR_CA_CA2_MASK)
#define CAU_ADR_CA_CA3_MASK (0xFFFFFFFFU)
#define CAU_ADR_CA_CA3_SHIFT (0U)
/*! CA3 - CA3
 */
#define CAU_ADR_CA_CA3(x) (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA3_SHIFT)) & CAU_ADR_CA_CA3_MASK)
#define CAU_ADR_CA_CA4_MASK (0xFFFFFFFFU)
#define CAU_ADR_CA_CA4_SHIFT (0U)
/*! CA4 - CA4
 */
#define CAU_ADR_CA_CA4(x) (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA4_SHIFT)) & CAU_ADR_CA_CA4_MASK)
#define CAU_ADR_CA_CA5_MASK (0xFFFFFFFFU)
#define CAU_ADR_CA_CA5_SHIFT (0U)
/*! CA5 - CA5
 */
#define CAU_ADR_CA_CA5(x) (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA5_SHIFT)) & CAU_ADR_CA_CA5_MASK)
#define CAU_ADR_CA_CA6_MASK (0xFFFFFFFFU)
#define CAU_ADR_CA_CA6_SHIFT (0U)
/*! CA6 - CA6
 */
#define CAU_ADR_CA_CA6(x) (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA6_SHIFT)) & CAU_ADR_CA_CA6_MASK)
#define CAU_ADR_CA_CA7_MASK (0xFFFFFFFFU)
#define CAU_ADR_CA_CA7_SHIFT (0U)
/*! CA7 - CA7
 */
#define CAU_ADR_CA_CA7(x) (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA7_SHIFT)) & CAU_ADR_CA_CA7_MASK)
#define CAU_ADR_CA_CA8_MASK (0xFFFFFFFFU)
#define CAU_ADR_CA_CA8_SHIFT (0U)
/*! CA8 - CA8
 */
#define CAU_ADR_CA_CA8(x) (((uint32_t)(((uint32_t)(x)) << CAU_ADR_CA_CA8_SHIFT)) & CAU_ADR_CA_CA8_MASK)
/*! @} */

/* The count of CAU_ADR_CA */
#define CAU_ADR_CA_COUNT (9U)

/*! @name RADR_CASR - Status register - Reverse and Add to Register command */
/*! @{ */
#define CAU_RADR_CASR_IC_MASK (0x1U)
#define CAU_RADR_CASR_IC_SHIFT (0U)
/*! IC
 *  0b0..No illegal commands issued
 *  0b1..Illegal command issued
 */
#define CAU_RADR_CASR_IC(x) (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CASR_IC_SHIFT)) & CAU_RADR_CASR_IC_MASK)
#define CAU_RADR_CASR_DPE_MASK (0x2U)
#define CAU_RADR_CASR_DPE_SHIFT (1U)
/*! DPE
 *  0b0..No error detected
 *  0b1..DES key parity error detected
 */
#define CAU_RADR_CASR_DPE(x) (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CASR_DPE_SHIFT)) & CAU_RADR_CASR_DPE_MASK)
#define CAU_RADR_CASR_VER_MASK (0xF0000000U)
#define CAU_RADR_CASR_VER_SHIFT (28U)
/*! VER - CAU version
 *  0b0001..Initial CAU version
 *  0b0010..Second version, added support for SHA-256 algorithm.(This is the value on this device)
 */
#define CAU_RADR_CASR_VER(x) (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CASR_VER_SHIFT)) & CAU_RADR_CASR_VER_MASK)
/*! @} */

/*! @name RADR_CAA - Accumulator register - Reverse and Add to Register command */
/*! @{ */
#define CAU_RADR_CAA_ACC_MASK (0xFFFFFFFFU)
#define CAU_RADR_CAA_ACC_SHIFT (0U)
/*! ACC - ACC
 */
#define CAU_RADR_CAA_ACC(x) (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CAA_ACC_SHIFT)) & CAU_RADR_CAA_ACC_MASK)
/*! @} */

/*! @name RADR_CA - General Purpose Register 0 - Reverse and Add to Register command..General Purpose Register 8 -
 * Reverse and Add to Register command */
/*! @{ */
#define CAU_RADR_CA_CA0_MASK (0xFFFFFFFFU)
#define CAU_RADR_CA_CA0_SHIFT (0U)
/*! CA0 - CA0
 */
#define CAU_RADR_CA_CA0(x) (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA0_SHIFT)) & CAU_RADR_CA_CA0_MASK)
#define CAU_RADR_CA_CA1_MASK (0xFFFFFFFFU)
#define CAU_RADR_CA_CA1_SHIFT (0U)
/*! CA1 - CA1
 */
#define CAU_RADR_CA_CA1(x) (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA1_SHIFT)) & CAU_RADR_CA_CA1_MASK)
#define CAU_RADR_CA_CA2_MASK (0xFFFFFFFFU)
#define CAU_RADR_CA_CA2_SHIFT (0U)
/*! CA2 - CA2
 */
#define CAU_RADR_CA_CA2(x) (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA2_SHIFT)) & CAU_RADR_CA_CA2_MASK)
#define CAU_RADR_CA_CA3_MASK (0xFFFFFFFFU)
#define CAU_RADR_CA_CA3_SHIFT (0U)
/*! CA3 - CA3
 */
#define CAU_RADR_CA_CA3(x) (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA3_SHIFT)) & CAU_RADR_CA_CA3_MASK)
#define CAU_RADR_CA_CA4_MASK (0xFFFFFFFFU)
#define CAU_RADR_CA_CA4_SHIFT (0U)
/*! CA4 - CA4
 */
#define CAU_RADR_CA_CA4(x) (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA4_SHIFT)) & CAU_RADR_CA_CA4_MASK)
#define CAU_RADR_CA_CA5_MASK (0xFFFFFFFFU)
#define CAU_RADR_CA_CA5_SHIFT (0U)
/*! CA5 - CA5
 */
#define CAU_RADR_CA_CA5(x) (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA5_SHIFT)) & CAU_RADR_CA_CA5_MASK)
#define CAU_RADR_CA_CA6_MASK (0xFFFFFFFFU)
#define CAU_RADR_CA_CA6_SHIFT (0U)
/*! CA6 - CA6
 */
#define CAU_RADR_CA_CA6(x) (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA6_SHIFT)) & CAU_RADR_CA_CA6_MASK)
#define CAU_RADR_CA_CA7_MASK (0xFFFFFFFFU)
#define CAU_RADR_CA_CA7_SHIFT (0U)
/*! CA7 - CA7
 */
#define CAU_RADR_CA_CA7(x) (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA7_SHIFT)) & CAU_RADR_CA_CA7_MASK)
#define CAU_RADR_CA_CA8_MASK (0xFFFFFFFFU)
#define CAU_RADR_CA_CA8_SHIFT (0U)
/*! CA8 - CA8
 */
#define CAU_RADR_CA_CA8(x) (((uint32_t)(((uint32_t)(x)) << CAU_RADR_CA_CA8_SHIFT)) & CAU_RADR_CA_CA8_MASK)
/*! @} */

/* The count of CAU_RADR_CA */
#define CAU_RADR_CA_COUNT (9U)

/*! @name XOR_CASR - Status register - Exclusive Or command */
/*! @{ */
#define CAU_XOR_CASR_IC_MASK (0x1U)
#define CAU_XOR_CASR_IC_SHIFT (0U)
/*! IC
 *  0b0..No illegal commands issued
 *  0b1..Illegal command issued
 */
#define CAU_XOR_CASR_IC(x) (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CASR_IC_SHIFT)) & CAU_XOR_CASR_IC_MASK)
#define CAU_XOR_CASR_DPE_MASK (0x2U)
#define CAU_XOR_CASR_DPE_SHIFT (1U)
/*! DPE
 *  0b0..No error detected
 *  0b1..DES key parity error detected
 */
#define CAU_XOR_CASR_DPE(x) (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CASR_DPE_SHIFT)) & CAU_XOR_CASR_DPE_MASK)
#define CAU_XOR_CASR_VER_MASK (0xF0000000U)
#define CAU_XOR_CASR_VER_SHIFT (28U)
/*! VER - CAU version
 *  0b0001..Initial CAU version
 *  0b0010..Second version, added support for SHA-256 algorithm.(This is the value on this device)
 */
#define CAU_XOR_CASR_VER(x) (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CASR_VER_SHIFT)) & CAU_XOR_CASR_VER_MASK)
/*! @} */

/*! @name XOR_CAA - Accumulator register - Exclusive Or command */
/*! @{ */
#define CAU_XOR_CAA_ACC_MASK (0xFFFFFFFFU)
#define CAU_XOR_CAA_ACC_SHIFT (0U)
/*! ACC - ACC
 */
#define CAU_XOR_CAA_ACC(x) (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CAA_ACC_SHIFT)) & CAU_XOR_CAA_ACC_MASK)
/*! @} */

/*! @name XOR_CA - General Purpose Register 0 - Exclusive Or command..General Purpose Register 8 - Exclusive Or command
 */
/*! @{ */
#define CAU_XOR_CA_CA0_MASK (0xFFFFFFFFU)
#define CAU_XOR_CA_CA0_SHIFT (0U)
/*! CA0 - CA0
 */
#define CAU_XOR_CA_CA0(x) (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA0_SHIFT)) & CAU_XOR_CA_CA0_MASK)
#define CAU_XOR_CA_CA1_MASK (0xFFFFFFFFU)
#define CAU_XOR_CA_CA1_SHIFT (0U)
/*! CA1 - CA1
 */
#define CAU_XOR_CA_CA1(x) (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA1_SHIFT)) & CAU_XOR_CA_CA1_MASK)
#define CAU_XOR_CA_CA2_MASK (0xFFFFFFFFU)
#define CAU_XOR_CA_CA2_SHIFT (0U)
/*! CA2 - CA2
 */
#define CAU_XOR_CA_CA2(x) (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA2_SHIFT)) & CAU_XOR_CA_CA2_MASK)
#define CAU_XOR_CA_CA3_MASK (0xFFFFFFFFU)
#define CAU_XOR_CA_CA3_SHIFT (0U)
/*! CA3 - CA3
 */
#define CAU_XOR_CA_CA3(x) (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA3_SHIFT)) & CAU_XOR_CA_CA3_MASK)
#define CAU_XOR_CA_CA4_MASK (0xFFFFFFFFU)
#define CAU_XOR_CA_CA4_SHIFT (0U)
/*! CA4 - CA4
 */
#define CAU_XOR_CA_CA4(x) (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA4_SHIFT)) & CAU_XOR_CA_CA4_MASK)
#define CAU_XOR_CA_CA5_MASK (0xFFFFFFFFU)
#define CAU_XOR_CA_CA5_SHIFT (0U)
/*! CA5 - CA5
 */
#define CAU_XOR_CA_CA5(x) (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA5_SHIFT)) & CAU_XOR_CA_CA5_MASK)
#define CAU_XOR_CA_CA6_MASK (0xFFFFFFFFU)
#define CAU_XOR_CA_CA6_SHIFT (0U)
/*! CA6 - CA6
 */
#define CAU_XOR_CA_CA6(x) (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA6_SHIFT)) & CAU_XOR_CA_CA6_MASK)
#define CAU_XOR_CA_CA7_MASK (0xFFFFFFFFU)
#define CAU_XOR_CA_CA7_SHIFT (0U)
/*! CA7 - CA7
 */
#define CAU_XOR_CA_CA7(x) (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA7_SHIFT)) & CAU_XOR_CA_CA7_MASK)
#define CAU_XOR_CA_CA8_MASK (0xFFFFFFFFU)
#define CAU_XOR_CA_CA8_SHIFT (0U)
/*! CA8 - CA8
 */
#define CAU_XOR_CA_CA8(x) (((uint32_t)(((uint32_t)(x)) << CAU_XOR_CA_CA8_SHIFT)) & CAU_XOR_CA_CA8_MASK)
/*! @} */

/* The count of CAU_XOR_CA */
#define CAU_XOR_CA_COUNT (9U)

/*! @name ROTL_CASR - Status register - Rotate Left command */
/*! @{ */
#define CAU_ROTL_CASR_IC_MASK (0x1U)
#define CAU_ROTL_CASR_IC_SHIFT (0U)
/*! IC
 *  0b0..No illegal commands issued
 *  0b1..Illegal command issued
 */
#define CAU_ROTL_CASR_IC(x) (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CASR_IC_SHIFT)) & CAU_ROTL_CASR_IC_MASK)
#define CAU_ROTL_CASR_DPE_MASK (0x2U)
#define CAU_ROTL_CASR_DPE_SHIFT (1U)
/*! DPE
 *  0b0..No error detected
 *  0b1..DES key parity error detected
 */
#define CAU_ROTL_CASR_DPE(x) (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CASR_DPE_SHIFT)) & CAU_ROTL_CASR_DPE_MASK)
#define CAU_ROTL_CASR_VER_MASK (0xF0000000U)
#define CAU_ROTL_CASR_VER_SHIFT (28U)
/*! VER - CAU version
 *  0b0001..Initial CAU version
 *  0b0010..Second version, added support for SHA-256 algorithm.(This is the value on this device)
 */
#define CAU_ROTL_CASR_VER(x) (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CASR_VER_SHIFT)) & CAU_ROTL_CASR_VER_MASK)
/*! @} */

/*! @name ROTL_CAA - Accumulator register - Rotate Left command */
/*! @{ */
#define CAU_ROTL_CAA_ACC_MASK (0xFFFFFFFFU)
#define CAU_ROTL_CAA_ACC_SHIFT (0U)
/*! ACC - ACC
 */
#define CAU_ROTL_CAA_ACC(x) (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CAA_ACC_SHIFT)) & CAU_ROTL_CAA_ACC_MASK)
/*! @} */

/*! @name ROTL_CA - General Purpose Register 0 - Rotate Left command..General Purpose Register 8 - Rotate Left command
 */
/*! @{ */
#define CAU_ROTL_CA_CA0_MASK (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA0_SHIFT (0U)
/*! CA0 - CA0
 */
#define CAU_ROTL_CA_CA0(x) (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA0_SHIFT)) & CAU_ROTL_CA_CA0_MASK)
#define CAU_ROTL_CA_CA1_MASK (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA1_SHIFT (0U)
/*! CA1 - CA1
 */
#define CAU_ROTL_CA_CA1(x) (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA1_SHIFT)) & CAU_ROTL_CA_CA1_MASK)
#define CAU_ROTL_CA_CA2_MASK (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA2_SHIFT (0U)
/*! CA2 - CA2
 */
#define CAU_ROTL_CA_CA2(x) (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA2_SHIFT)) & CAU_ROTL_CA_CA2_MASK)
#define CAU_ROTL_CA_CA3_MASK (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA3_SHIFT (0U)
/*! CA3 - CA3
 */
#define CAU_ROTL_CA_CA3(x) (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA3_SHIFT)) & CAU_ROTL_CA_CA3_MASK)
#define CAU_ROTL_CA_CA4_MASK (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA4_SHIFT (0U)
/*! CA4 - CA4
 */
#define CAU_ROTL_CA_CA4(x) (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA4_SHIFT)) & CAU_ROTL_CA_CA4_MASK)
#define CAU_ROTL_CA_CA5_MASK (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA5_SHIFT (0U)
/*! CA5 - CA5
 */
#define CAU_ROTL_CA_CA5(x) (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA5_SHIFT)) & CAU_ROTL_CA_CA5_MASK)
#define CAU_ROTL_CA_CA6_MASK (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA6_SHIFT (0U)
/*! CA6 - CA6
 */
#define CAU_ROTL_CA_CA6(x) (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA6_SHIFT)) & CAU_ROTL_CA_CA6_MASK)
#define CAU_ROTL_CA_CA7_MASK (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA7_SHIFT (0U)
/*! CA7 - CA7
 */
#define CAU_ROTL_CA_CA7(x) (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA7_SHIFT)) & CAU_ROTL_CA_CA7_MASK)
#define CAU_ROTL_CA_CA8_MASK (0xFFFFFFFFU)
#define CAU_ROTL_CA_CA8_SHIFT (0U)
/*! CA8 - CA8
 */
#define CAU_ROTL_CA_CA8(x) (((uint32_t)(((uint32_t)(x)) << CAU_ROTL_CA_CA8_SHIFT)) & CAU_ROTL_CA_CA8_MASK)
/*! @} */

/* The count of CAU_ROTL_CA */
#define CAU_ROTL_CA_COUNT (9U)

/*! @name AESC_CASR - Status register - AES Column Operation command */
/*! @{ */
#define CAU_AESC_CASR_IC_MASK (0x1U)
#define CAU_AESC_CASR_IC_SHIFT (0U)
/*! IC
 *  0b0..No illegal commands issued
 *  0b1..Illegal command issued
 */
#define CAU_AESC_CASR_IC(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CASR_IC_SHIFT)) & CAU_AESC_CASR_IC_MASK)
#define CAU_AESC_CASR_DPE_MASK (0x2U)
#define CAU_AESC_CASR_DPE_SHIFT (1U)
/*! DPE
 *  0b0..No error detected
 *  0b1..DES key parity error detected
 */
#define CAU_AESC_CASR_DPE(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CASR_DPE_SHIFT)) & CAU_AESC_CASR_DPE_MASK)
#define CAU_AESC_CASR_VER_MASK (0xF0000000U)
#define CAU_AESC_CASR_VER_SHIFT (28U)
/*! VER - CAU version
 *  0b0001..Initial CAU version
 *  0b0010..Second version, added support for SHA-256 algorithm.(This is the value on this device)
 */
#define CAU_AESC_CASR_VER(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CASR_VER_SHIFT)) & CAU_AESC_CASR_VER_MASK)
/*! @} */

/*! @name AESC_CAA - Accumulator register - AES Column Operation command */
/*! @{ */
#define CAU_AESC_CAA_ACC_MASK (0xFFFFFFFFU)
#define CAU_AESC_CAA_ACC_SHIFT (0U)
/*! ACC - ACC
 */
#define CAU_AESC_CAA_ACC(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CAA_ACC_SHIFT)) & CAU_AESC_CAA_ACC_MASK)
/*! @} */

/*! @name AESC_CA - General Purpose Register 0 - AES Column Operation command..General Purpose Register 8 - AES Column
 * Operation command */
/*! @{ */
#define CAU_AESC_CA_CA0_MASK (0xFFFFFFFFU)
#define CAU_AESC_CA_CA0_SHIFT (0U)
/*! CA0 - CA0
 */
#define CAU_AESC_CA_CA0(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA0_SHIFT)) & CAU_AESC_CA_CA0_MASK)
#define CAU_AESC_CA_CA1_MASK (0xFFFFFFFFU)
#define CAU_AESC_CA_CA1_SHIFT (0U)
/*! CA1 - CA1
 */
#define CAU_AESC_CA_CA1(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA1_SHIFT)) & CAU_AESC_CA_CA1_MASK)
#define CAU_AESC_CA_CA2_MASK (0xFFFFFFFFU)
#define CAU_AESC_CA_CA2_SHIFT (0U)
/*! CA2 - CA2
 */
#define CAU_AESC_CA_CA2(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA2_SHIFT)) & CAU_AESC_CA_CA2_MASK)
#define CAU_AESC_CA_CA3_MASK (0xFFFFFFFFU)
#define CAU_AESC_CA_CA3_SHIFT (0U)
/*! CA3 - CA3
 */
#define CAU_AESC_CA_CA3(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA3_SHIFT)) & CAU_AESC_CA_CA3_MASK)
#define CAU_AESC_CA_CA4_MASK (0xFFFFFFFFU)
#define CAU_AESC_CA_CA4_SHIFT (0U)
/*! CA4 - CA4
 */
#define CAU_AESC_CA_CA4(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA4_SHIFT)) & CAU_AESC_CA_CA4_MASK)
#define CAU_AESC_CA_CA5_MASK (0xFFFFFFFFU)
#define CAU_AESC_CA_CA5_SHIFT (0U)
/*! CA5 - CA5
 */
#define CAU_AESC_CA_CA5(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA5_SHIFT)) & CAU_AESC_CA_CA5_MASK)
#define CAU_AESC_CA_CA6_MASK (0xFFFFFFFFU)
#define CAU_AESC_CA_CA6_SHIFT (0U)
/*! CA6 - CA6
 */
#define CAU_AESC_CA_CA6(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA6_SHIFT)) & CAU_AESC_CA_CA6_MASK)
#define CAU_AESC_CA_CA7_MASK (0xFFFFFFFFU)
#define CAU_AESC_CA_CA7_SHIFT (0U)
/*! CA7 - CA7
 */
#define CAU_AESC_CA_CA7(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA7_SHIFT)) & CAU_AESC_CA_CA7_MASK)
#define CAU_AESC_CA_CA8_MASK (0xFFFFFFFFU)
#define CAU_AESC_CA_CA8_SHIFT (0U)
/*! CA8 - CA8
 */
#define CAU_AESC_CA_CA8(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESC_CA_CA8_SHIFT)) & CAU_AESC_CA_CA8_MASK)
/*! @} */

/* The count of CAU_AESC_CA */
#define CAU_AESC_CA_COUNT (9U)

/*! @name AESIC_CASR - Status register - AES Inverse Column Operation command */
/*! @{ */
#define CAU_AESIC_CASR_IC_MASK (0x1U)
#define CAU_AESIC_CASR_IC_SHIFT (0U)
/*! IC
 *  0b0..No illegal commands issued
 *  0b1..Illegal command issued
 */
#define CAU_AESIC_CASR_IC(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CASR_IC_SHIFT)) & CAU_AESIC_CASR_IC_MASK)
#define CAU_AESIC_CASR_DPE_MASK (0x2U)
#define CAU_AESIC_CASR_DPE_SHIFT (1U)
/*! DPE
 *  0b0..No error detected
 *  0b1..DES key parity error detected
 */
#define CAU_AESIC_CASR_DPE(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CASR_DPE_SHIFT)) & CAU_AESIC_CASR_DPE_MASK)
#define CAU_AESIC_CASR_VER_MASK (0xF0000000U)
#define CAU_AESIC_CASR_VER_SHIFT (28U)
/*! VER - CAU version
 *  0b0001..Initial CAU version
 *  0b0010..Second version, added support for SHA-256 algorithm.(This is the value on this device)
 */
#define CAU_AESIC_CASR_VER(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CASR_VER_SHIFT)) & CAU_AESIC_CASR_VER_MASK)
/*! @} */

/*! @name AESIC_CAA - Accumulator register - AES Inverse Column Operation command */
/*! @{ */
#define CAU_AESIC_CAA_ACC_MASK (0xFFFFFFFFU)
#define CAU_AESIC_CAA_ACC_SHIFT (0U)
/*! ACC - ACC
 */
#define CAU_AESIC_CAA_ACC(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CAA_ACC_SHIFT)) & CAU_AESIC_CAA_ACC_MASK)
/*! @} */

/*! @name AESIC_CA - General Purpose Register 0 - AES Inverse Column Operation command..General Purpose Register 8 - AES
 * Inverse Column Operation command */
/*! @{ */
#define CAU_AESIC_CA_CA0_MASK (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA0_SHIFT (0U)
/*! CA0 - CA0
 */
#define CAU_AESIC_CA_CA0(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA0_SHIFT)) & CAU_AESIC_CA_CA0_MASK)
#define CAU_AESIC_CA_CA1_MASK (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA1_SHIFT (0U)
/*! CA1 - CA1
 */
#define CAU_AESIC_CA_CA1(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA1_SHIFT)) & CAU_AESIC_CA_CA1_MASK)
#define CAU_AESIC_CA_CA2_MASK (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA2_SHIFT (0U)
/*! CA2 - CA2
 */
#define CAU_AESIC_CA_CA2(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA2_SHIFT)) & CAU_AESIC_CA_CA2_MASK)
#define CAU_AESIC_CA_CA3_MASK (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA3_SHIFT (0U)
/*! CA3 - CA3
 */
#define CAU_AESIC_CA_CA3(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA3_SHIFT)) & CAU_AESIC_CA_CA3_MASK)
#define CAU_AESIC_CA_CA4_MASK (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA4_SHIFT (0U)
/*! CA4 - CA4
 */
#define CAU_AESIC_CA_CA4(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA4_SHIFT)) & CAU_AESIC_CA_CA4_MASK)
#define CAU_AESIC_CA_CA5_MASK (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA5_SHIFT (0U)
/*! CA5 - CA5
 */
#define CAU_AESIC_CA_CA5(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA5_SHIFT)) & CAU_AESIC_CA_CA5_MASK)
#define CAU_AESIC_CA_CA6_MASK (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA6_SHIFT (0U)
/*! CA6 - CA6
 */
#define CAU_AESIC_CA_CA6(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA6_SHIFT)) & CAU_AESIC_CA_CA6_MASK)
#define CAU_AESIC_CA_CA7_MASK (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA7_SHIFT (0U)
/*! CA7 - CA7
 */
#define CAU_AESIC_CA_CA7(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA7_SHIFT)) & CAU_AESIC_CA_CA7_MASK)
#define CAU_AESIC_CA_CA8_MASK (0xFFFFFFFFU)
#define CAU_AESIC_CA_CA8_SHIFT (0U)
/*! CA8 - CA8
 */
#define CAU_AESIC_CA_CA8(x) (((uint32_t)(((uint32_t)(x)) << CAU_AESIC_CA_CA8_SHIFT)) & CAU_AESIC_CA_CA8_MASK)
/*! @} */

/* The count of CAU_AESIC_CA */
#define CAU_AESIC_CA_COUNT (9U)

/*!
 * @}
 */ /* end of group CAU_Register_Masks */

/* CAU - Peripheral instance base addresses */
/** Peripheral CAU0 base address */
#define CAU0_BASE (0xF0005000u)
/** Peripheral CAU0 base pointer */
#define CAU0 ((CAU_Type *)CAU0_BASE)
/** Array initializer of CAU peripheral base addresses */
#define CAU_BASE_ADDRS \
    {                  \
        CAU0_BASE      \
    }
/** Array initializer of CAU peripheral base pointers */
#define CAU_BASE_PTRS \
    {                 \
        CAU0          \
    }

/*!
 * @}
 */ /* end of group CAU_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- CMP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Peripheral_Access_Layer CMP Peripheral Access Layer
 * @{
 */

/** CMP - Register Layout Typedef */
typedef struct
{
    __IO uint8_t CR0;   /**< CMP Control Register 0, offset: 0x0 */
    __IO uint8_t CR1;   /**< CMP Control Register 1, offset: 0x1 */
    __IO uint8_t FPR;   /**< CMP Filter Period Register, offset: 0x2 */
    __IO uint8_t SCR;   /**< CMP Status and Control Register, offset: 0x3 */
    __IO uint8_t DACCR; /**< DAC Control Register, offset: 0x4 */
    __IO uint8_t MUXCR; /**< MUX Control Register, offset: 0x5 */
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
#define CMP_CR0_HYSTCTR_MASK (0x3U)
#define CMP_CR0_HYSTCTR_SHIFT (0U)
/*! HYSTCTR - Comparator hard block hysteresis control
 *  0b00..Level 0
 *  0b01..Level 1
 *  0b10..Level 2
 *  0b11..Level 3
 */
#define CMP_CR0_HYSTCTR(x) (((uint8_t)(((uint8_t)(x)) << CMP_CR0_HYSTCTR_SHIFT)) & CMP_CR0_HYSTCTR_MASK)
#define CMP_CR0_FILTER_CNT_MASK (0x70U)
#define CMP_CR0_FILTER_CNT_SHIFT (4U)
/*! FILTER_CNT - Filter Sample Count
 *  0b000..Filter is disabled. If SE = 1, then COUT is a logic 0. This is not a legal state, and is not recommended. If
 * SE = 0, COUT = COUTA. 0b001..One sample must agree. The comparator output is simply sampled. 0b010..2 consecutive
 * samples must agree. 0b011..3 consecutive samples must agree. 0b100..4 consecutive samples must agree. 0b101..5
 * consecutive samples must agree. 0b110..6 consecutive samples must agree. 0b111..7 consecutive samples must agree.
 */
#define CMP_CR0_FILTER_CNT(x) (((uint8_t)(((uint8_t)(x)) << CMP_CR0_FILTER_CNT_SHIFT)) & CMP_CR0_FILTER_CNT_MASK)
/*! @} */

/*! @name CR1 - CMP Control Register 1 */
/*! @{ */
#define CMP_CR1_EN_MASK (0x1U)
#define CMP_CR1_EN_SHIFT (0U)
/*! EN - Comparator Module Enable
 *  0b0..Analog Comparator is disabled.
 *  0b1..Analog Comparator is enabled.
 */
#define CMP_CR1_EN(x) (((uint8_t)(((uint8_t)(x)) << CMP_CR1_EN_SHIFT)) & CMP_CR1_EN_MASK)
#define CMP_CR1_OPE_MASK (0x2U)
#define CMP_CR1_OPE_SHIFT (1U)
/*! OPE - Comparator Output Pin Enable
 *  0b0..CMPO is not available on the associated CMPO output pin. If the comparator does not own the pin, this field has
 * no effect. 0b1..CMPO is available on the associated CMPO output pin. The comparator output (CMPO) is driven out on
 * the associated CMPO output pin if the comparator owns the pin. If the comparator does not own the field, this bit has
 * no effect.
 */
#define CMP_CR1_OPE(x) (((uint8_t)(((uint8_t)(x)) << CMP_CR1_OPE_SHIFT)) & CMP_CR1_OPE_MASK)
#define CMP_CR1_COS_MASK (0x4U)
#define CMP_CR1_COS_SHIFT (2U)
/*! COS - Comparator Output Select
 *  0b0..Set the filtered comparator output (CMPO) to equal COUT.
 *  0b1..Set the unfiltered comparator output (CMPO) to equal COUTA.
 */
#define CMP_CR1_COS(x) (((uint8_t)(((uint8_t)(x)) << CMP_CR1_COS_SHIFT)) & CMP_CR1_COS_MASK)
#define CMP_CR1_INV_MASK (0x8U)
#define CMP_CR1_INV_SHIFT (3U)
/*! INV - Comparator INVERT
 *  0b0..Does not invert the comparator output.
 *  0b1..Inverts the comparator output.
 */
#define CMP_CR1_INV(x) (((uint8_t)(((uint8_t)(x)) << CMP_CR1_INV_SHIFT)) & CMP_CR1_INV_MASK)
#define CMP_CR1_PMODE_MASK (0x10U)
#define CMP_CR1_PMODE_SHIFT (4U)
/*! PMODE - Power Mode Select
 *  0b0..Low-Speed (LS) Comparison mode selected. In this mode, CMP has slower output propagation delay and lower
 * current consumption. 0b1..High-Speed (HS) Comparison mode selected. In this mode, CMP has faster output propagation
 * delay and higher current consumption.
 */
#define CMP_CR1_PMODE(x) (((uint8_t)(((uint8_t)(x)) << CMP_CR1_PMODE_SHIFT)) & CMP_CR1_PMODE_MASK)
#define CMP_CR1_TRIGM_MASK (0x20U)
#define CMP_CR1_TRIGM_SHIFT (5U)
/*! TRIGM - Trigger Mode Enable
 *  0b0..Trigger mode is disabled.
 *  0b1..Trigger mode is enabled.
 */
#define CMP_CR1_TRIGM(x) (((uint8_t)(((uint8_t)(x)) << CMP_CR1_TRIGM_SHIFT)) & CMP_CR1_TRIGM_MASK)
#define CMP_CR1_WE_MASK (0x40U)
#define CMP_CR1_WE_SHIFT (6U)
/*! WE - Windowing Enable
 *  0b0..Windowing mode is not selected.
 *  0b1..Windowing mode is selected.
 */
#define CMP_CR1_WE(x) (((uint8_t)(((uint8_t)(x)) << CMP_CR1_WE_SHIFT)) & CMP_CR1_WE_MASK)
#define CMP_CR1_SE_MASK (0x80U)
#define CMP_CR1_SE_SHIFT (7U)
/*! SE - Sample Enable
 *  0b0..Sampling mode is not selected.
 *  0b1..Sampling mode is selected.
 */
#define CMP_CR1_SE(x) (((uint8_t)(((uint8_t)(x)) << CMP_CR1_SE_SHIFT)) & CMP_CR1_SE_MASK)
/*! @} */

/*! @name FPR - CMP Filter Period Register */
/*! @{ */
#define CMP_FPR_FILT_PER_MASK (0xFFU)
#define CMP_FPR_FILT_PER_SHIFT (0U)
/*! FILT_PER - Filter Sample Period
 */
#define CMP_FPR_FILT_PER(x) (((uint8_t)(((uint8_t)(x)) << CMP_FPR_FILT_PER_SHIFT)) & CMP_FPR_FILT_PER_MASK)
/*! @} */

/*! @name SCR - CMP Status and Control Register */
/*! @{ */
#define CMP_SCR_COUT_MASK (0x1U)
#define CMP_SCR_COUT_SHIFT (0U)
/*! COUT - Analog Comparator Output
 */
#define CMP_SCR_COUT(x) (((uint8_t)(((uint8_t)(x)) << CMP_SCR_COUT_SHIFT)) & CMP_SCR_COUT_MASK)
#define CMP_SCR_CFF_MASK (0x2U)
#define CMP_SCR_CFF_SHIFT (1U)
/*! CFF - Analog Comparator Flag Falling
 *  0b0..Falling-edge on COUT has not been detected.
 *  0b1..Falling-edge on COUT has occurred.
 */
#define CMP_SCR_CFF(x) (((uint8_t)(((uint8_t)(x)) << CMP_SCR_CFF_SHIFT)) & CMP_SCR_CFF_MASK)
#define CMP_SCR_CFR_MASK (0x4U)
#define CMP_SCR_CFR_SHIFT (2U)
/*! CFR - Analog Comparator Flag Rising
 *  0b0..Rising-edge on COUT has not been detected.
 *  0b1..Rising-edge on COUT has occurred.
 */
#define CMP_SCR_CFR(x) (((uint8_t)(((uint8_t)(x)) << CMP_SCR_CFR_SHIFT)) & CMP_SCR_CFR_MASK)
#define CMP_SCR_IEF_MASK (0x8U)
#define CMP_SCR_IEF_SHIFT (3U)
/*! IEF - Comparator Interrupt Enable Falling
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define CMP_SCR_IEF(x) (((uint8_t)(((uint8_t)(x)) << CMP_SCR_IEF_SHIFT)) & CMP_SCR_IEF_MASK)
#define CMP_SCR_IER_MASK (0x10U)
#define CMP_SCR_IER_SHIFT (4U)
/*! IER - Comparator Interrupt Enable Rising
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define CMP_SCR_IER(x) (((uint8_t)(((uint8_t)(x)) << CMP_SCR_IER_SHIFT)) & CMP_SCR_IER_MASK)
#define CMP_SCR_DMAEN_MASK (0x40U)
#define CMP_SCR_DMAEN_SHIFT (6U)
/*! DMAEN - DMA Enable Control
 *  0b0..DMA is disabled.
 *  0b1..DMA is enabled.
 */
#define CMP_SCR_DMAEN(x) (((uint8_t)(((uint8_t)(x)) << CMP_SCR_DMAEN_SHIFT)) & CMP_SCR_DMAEN_MASK)
/*! @} */

/*! @name DACCR - DAC Control Register */
/*! @{ */
#define CMP_DACCR_VOSEL_MASK (0x3FU)
#define CMP_DACCR_VOSEL_SHIFT (0U)
/*! VOSEL - DAC Output Voltage Select
 */
#define CMP_DACCR_VOSEL(x) (((uint8_t)(((uint8_t)(x)) << CMP_DACCR_VOSEL_SHIFT)) & CMP_DACCR_VOSEL_MASK)
#define CMP_DACCR_VRSEL_MASK (0x40U)
#define CMP_DACCR_VRSEL_SHIFT (6U)
/*! VRSEL - Supply Voltage Reference Source Select
 *  0b0..Vin1 is selected as resistor ladder network supply reference.
 *  0b1..Vin2 is selected as resistor ladder network supply reference.
 */
#define CMP_DACCR_VRSEL(x) (((uint8_t)(((uint8_t)(x)) << CMP_DACCR_VRSEL_SHIFT)) & CMP_DACCR_VRSEL_MASK)
#define CMP_DACCR_DACEN_MASK (0x80U)
#define CMP_DACCR_DACEN_SHIFT (7U)
/*! DACEN - DAC Enable
 *  0b0..DAC is disabled.
 *  0b1..DAC is enabled.
 */
#define CMP_DACCR_DACEN(x) (((uint8_t)(((uint8_t)(x)) << CMP_DACCR_DACEN_SHIFT)) & CMP_DACCR_DACEN_MASK)
/*! @} */

/*! @name MUXCR - MUX Control Register */
/*! @{ */
#define CMP_MUXCR_MSEL_MASK (0x7U)
#define CMP_MUXCR_MSEL_SHIFT (0U)
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
#define CMP_MUXCR_MSEL(x) (((uint8_t)(((uint8_t)(x)) << CMP_MUXCR_MSEL_SHIFT)) & CMP_MUXCR_MSEL_MASK)
#define CMP_MUXCR_PSEL_MASK (0x38U)
#define CMP_MUXCR_PSEL_SHIFT (3U)
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
#define CMP_MUXCR_PSEL(x) (((uint8_t)(((uint8_t)(x)) << CMP_MUXCR_PSEL_SHIFT)) & CMP_MUXCR_PSEL_MASK)
#define CMP_MUXCR_PSTM_MASK (0x80U)
#define CMP_MUXCR_PSTM_SHIFT (7U)
/*! PSTM - Pass Through Mode Enable
 *  0b0..Pass Through Mode is disabled.
 *  0b1..Pass Through Mode is enabled.
 */
#define CMP_MUXCR_PSTM(x) (((uint8_t)(((uint8_t)(x)) << CMP_MUXCR_PSTM_SHIFT)) & CMP_MUXCR_PSTM_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group CMP_Register_Masks */

/* CMP - Peripheral instance base addresses */
/** Peripheral CMP0 base address */
#define CMP0_BASE (0x4006E000u)
/** Peripheral CMP0 base pointer */
#define CMP0 ((CMP_Type *)CMP0_BASE)
/** Peripheral CMP1 base address */
#define CMP1_BASE (0x400EF000u)
/** Peripheral CMP1 base pointer */
#define CMP1 ((CMP_Type *)CMP1_BASE)
/** Array initializer of CMP peripheral base addresses */
#define CMP_BASE_ADDRS       \
    {                        \
        CMP0_BASE, CMP1_BASE \
    }
/** Array initializer of CMP peripheral base pointers */
#define CMP_BASE_PTRS \
    {                 \
        CMP0, CMP1    \
    }
/** Interrupt vectors for the CMP peripheral type */
#define CMP_IRQS             \
    {                        \
        CMP0_IRQn, CMP1_IRQn \
    }

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
typedef struct
{
    union
    { /* offset: 0x0 */
        struct
        {                        /* offset: 0x0 */
            __IO uint8_t DATALL; /**< CRC_DATALL register., offset: 0x0 */
            __IO uint8_t DATALU; /**< CRC_DATALU register., offset: 0x1 */
            __IO uint8_t DATAHL; /**< CRC_DATAHL register., offset: 0x2 */
            __IO uint8_t DATAHU; /**< CRC_DATAHU register., offset: 0x3 */
        } ACCESS8BIT;
        struct
        {                        /* offset: 0x0 */
            __IO uint16_t DATAL; /**< CRC_DATAL register., offset: 0x0 */
            __IO uint16_t DATAH; /**< CRC_DATAH register., offset: 0x2 */
        } ACCESS16BIT;
        __IO uint32_t DATA; /**< CRC Data register, offset: 0x0 */
    };
    union
    { /* offset: 0x4 */
        struct
        {                         /* offset: 0x4 */
            __IO uint8_t GPOLYLL; /**< CRC_GPOLYLL register., offset: 0x4 */
            __IO uint8_t GPOLYLU; /**< CRC_GPOLYLU register., offset: 0x5 */
            __IO uint8_t GPOLYHL; /**< CRC_GPOLYHL register., offset: 0x6 */
            __IO uint8_t GPOLYHU; /**< CRC_GPOLYHU register., offset: 0x7 */
        } GPOLY_ACCESS8BIT;
        struct
        {                         /* offset: 0x4 */
            __IO uint16_t GPOLYL; /**< CRC_GPOLYL register., offset: 0x4 */
            __IO uint16_t GPOLYH; /**< CRC_GPOLYH register., offset: 0x6 */
        } GPOLY_ACCESS16BIT;
        __IO uint32_t GPOLY; /**< CRC Polynomial register, offset: 0x4 */
    };
    union
    { /* offset: 0x8 */
        struct
        { /* offset: 0x8 */
            uint8_t RESERVED_0[3];
            __IO uint8_t CTRLHU; /**< CRC_CTRLHU register., offset: 0xB */
        } CTRL_ACCESS8BIT;
        __IO uint32_t CTRL; /**< CRC Control register, offset: 0x8 */
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
#define CRC_DATALL_DATALL_MASK (0xFFU)
#define CRC_DATALL_DATALL_SHIFT (0U)
/*! DATALL - CRCLL stores the first 8 bits of the 32 bit DATA
 */
#define CRC_DATALL_DATALL(x) (((uint8_t)(((uint8_t)(x)) << CRC_DATALL_DATALL_SHIFT)) & CRC_DATALL_DATALL_MASK)
/*! @} */

/*! @name DATALU - CRC_DATALU register. */
/*! @{ */
#define CRC_DATALU_DATALU_MASK (0xFFU)
#define CRC_DATALU_DATALU_SHIFT (0U)
/*! DATALU - DATALL stores the second 8 bits of the 32 bit CRC
 */
#define CRC_DATALU_DATALU(x) (((uint8_t)(((uint8_t)(x)) << CRC_DATALU_DATALU_SHIFT)) & CRC_DATALU_DATALU_MASK)
/*! @} */

/*! @name DATAHL - CRC_DATAHL register. */
/*! @{ */
#define CRC_DATAHL_DATAHL_MASK (0xFFU)
#define CRC_DATAHL_DATAHL_SHIFT (0U)
/*! DATAHL - DATAHL stores the third 8 bits of the 32 bit CRC
 */
#define CRC_DATAHL_DATAHL(x) (((uint8_t)(((uint8_t)(x)) << CRC_DATAHL_DATAHL_SHIFT)) & CRC_DATAHL_DATAHL_MASK)
/*! @} */

/*! @name DATAHU - CRC_DATAHU register. */
/*! @{ */
#define CRC_DATAHU_DATAHU_MASK (0xFFU)
#define CRC_DATAHU_DATAHU_SHIFT (0U)
/*! DATAHU - DATAHU stores the fourth 8 bits of the 32 bit CRC
 */
#define CRC_DATAHU_DATAHU(x) (((uint8_t)(((uint8_t)(x)) << CRC_DATAHU_DATAHU_SHIFT)) & CRC_DATAHU_DATAHU_MASK)
/*! @} */

/*! @name DATAL - CRC_DATAL register. */
/*! @{ */
#define CRC_DATAL_DATAL_MASK (0xFFFFU)
#define CRC_DATAL_DATAL_SHIFT (0U)
/*! DATAL - DATAL stores the lower 16 bits of the 16/32 bit CRC
 */
#define CRC_DATAL_DATAL(x) (((uint16_t)(((uint16_t)(x)) << CRC_DATAL_DATAL_SHIFT)) & CRC_DATAL_DATAL_MASK)
/*! @} */

/*! @name DATAH - CRC_DATAH register. */
/*! @{ */
#define CRC_DATAH_DATAH_MASK (0xFFFFU)
#define CRC_DATAH_DATAH_SHIFT (0U)
/*! DATAH - DATAH stores the high 16 bits of the 16/32 bit CRC
 */
#define CRC_DATAH_DATAH(x) (((uint16_t)(((uint16_t)(x)) << CRC_DATAH_DATAH_SHIFT)) & CRC_DATAH_DATAH_MASK)
/*! @} */

/*! @name DATA - CRC Data register */
/*! @{ */
#define CRC_DATA_LL_MASK (0xFFU)
#define CRC_DATA_LL_SHIFT (0U)
/*! LL - CRC Low Lower Byte
 */
#define CRC_DATA_LL(x) (((uint32_t)(((uint32_t)(x)) << CRC_DATA_LL_SHIFT)) & CRC_DATA_LL_MASK)
#define CRC_DATA_LU_MASK (0xFF00U)
#define CRC_DATA_LU_SHIFT (8U)
/*! LU - CRC Low Upper Byte
 */
#define CRC_DATA_LU(x) (((uint32_t)(((uint32_t)(x)) << CRC_DATA_LU_SHIFT)) & CRC_DATA_LU_MASK)
#define CRC_DATA_HL_MASK (0xFF0000U)
#define CRC_DATA_HL_SHIFT (16U)
/*! HL - CRC High Lower Byte
 */
#define CRC_DATA_HL(x) (((uint32_t)(((uint32_t)(x)) << CRC_DATA_HL_SHIFT)) & CRC_DATA_HL_MASK)
#define CRC_DATA_HU_MASK (0xFF000000U)
#define CRC_DATA_HU_SHIFT (24U)
/*! HU - CRC High Upper Byte
 */
#define CRC_DATA_HU(x) (((uint32_t)(((uint32_t)(x)) << CRC_DATA_HU_SHIFT)) & CRC_DATA_HU_MASK)
/*! @} */

/*! @name GPOLYLL - CRC_GPOLYLL register. */
/*! @{ */
#define CRC_GPOLYLL_GPOLYLL_MASK (0xFFU)
#define CRC_GPOLYLL_GPOLYLL_SHIFT (0U)
/*! GPOLYLL - POLYLL stores the first 8 bits of the 32 bit CRC
 */
#define CRC_GPOLYLL_GPOLYLL(x) (((uint8_t)(((uint8_t)(x)) << CRC_GPOLYLL_GPOLYLL_SHIFT)) & CRC_GPOLYLL_GPOLYLL_MASK)
/*! @} */

/*! @name GPOLYLU - CRC_GPOLYLU register. */
/*! @{ */
#define CRC_GPOLYLU_GPOLYLU_MASK (0xFFU)
#define CRC_GPOLYLU_GPOLYLU_SHIFT (0U)
/*! GPOLYLU - POLYLL stores the second 8 bits of the 32 bit CRC
 */
#define CRC_GPOLYLU_GPOLYLU(x) (((uint8_t)(((uint8_t)(x)) << CRC_GPOLYLU_GPOLYLU_SHIFT)) & CRC_GPOLYLU_GPOLYLU_MASK)
/*! @} */

/*! @name GPOLYHL - CRC_GPOLYHL register. */
/*! @{ */
#define CRC_GPOLYHL_GPOLYHL_MASK (0xFFU)
#define CRC_GPOLYHL_GPOLYHL_SHIFT (0U)
/*! GPOLYHL - POLYHL stores the third 8 bits of the 32 bit CRC
 */
#define CRC_GPOLYHL_GPOLYHL(x) (((uint8_t)(((uint8_t)(x)) << CRC_GPOLYHL_GPOLYHL_SHIFT)) & CRC_GPOLYHL_GPOLYHL_MASK)
/*! @} */

/*! @name GPOLYHU - CRC_GPOLYHU register. */
/*! @{ */
#define CRC_GPOLYHU_GPOLYHU_MASK (0xFFU)
#define CRC_GPOLYHU_GPOLYHU_SHIFT (0U)
/*! GPOLYHU - POLYHU stores the fourth 8 bits of the 32 bit CRC
 */
#define CRC_GPOLYHU_GPOLYHU(x) (((uint8_t)(((uint8_t)(x)) << CRC_GPOLYHU_GPOLYHU_SHIFT)) & CRC_GPOLYHU_GPOLYHU_MASK)
/*! @} */

/*! @name GPOLYL - CRC_GPOLYL register. */
/*! @{ */
#define CRC_GPOLYL_GPOLYL_MASK (0xFFFFU)
#define CRC_GPOLYL_GPOLYL_SHIFT (0U)
/*! GPOLYL - POLYL stores the lower 16 bits of the 16/32 bit CRC polynomial value
 */
#define CRC_GPOLYL_GPOLYL(x) (((uint16_t)(((uint16_t)(x)) << CRC_GPOLYL_GPOLYL_SHIFT)) & CRC_GPOLYL_GPOLYL_MASK)
/*! @} */

/*! @name GPOLYH - CRC_GPOLYH register. */
/*! @{ */
#define CRC_GPOLYH_GPOLYH_MASK (0xFFFFU)
#define CRC_GPOLYH_GPOLYH_SHIFT (0U)
/*! GPOLYH - POLYH stores the high 16 bits of the 16/32 bit CRC polynomial value
 */
#define CRC_GPOLYH_GPOLYH(x) (((uint16_t)(((uint16_t)(x)) << CRC_GPOLYH_GPOLYH_SHIFT)) & CRC_GPOLYH_GPOLYH_MASK)
/*! @} */

/*! @name GPOLY - CRC Polynomial register */
/*! @{ */
#define CRC_GPOLY_LOW_MASK (0xFFFFU)
#define CRC_GPOLY_LOW_SHIFT (0U)
/*! LOW - Low Polynominal Half-word
 */
#define CRC_GPOLY_LOW(x) (((uint32_t)(((uint32_t)(x)) << CRC_GPOLY_LOW_SHIFT)) & CRC_GPOLY_LOW_MASK)
#define CRC_GPOLY_HIGH_MASK (0xFFFF0000U)
#define CRC_GPOLY_HIGH_SHIFT (16U)
/*! HIGH - High Polynominal Half-word
 */
#define CRC_GPOLY_HIGH(x) (((uint32_t)(((uint32_t)(x)) << CRC_GPOLY_HIGH_SHIFT)) & CRC_GPOLY_HIGH_MASK)
/*! @} */

/*! @name CTRLHU - CRC_CTRLHU register. */
/*! @{ */
#define CRC_CTRLHU_TCRC_MASK (0x1U)
#define CRC_CTRLHU_TCRC_SHIFT (0U)
/*! TCRC
 *  0b0..16-bit CRC protocol.
 *  0b1..32-bit CRC protocol.
 */
#define CRC_CTRLHU_TCRC(x) (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_TCRC_SHIFT)) & CRC_CTRLHU_TCRC_MASK)
#define CRC_CTRLHU_WAS_MASK (0x2U)
#define CRC_CTRLHU_WAS_SHIFT (1U)
/*! WAS
 *  0b0..Writes to CRC data register are data values.
 *  0b1..Writes to CRC data reguster are seed values.
 */
#define CRC_CTRLHU_WAS(x) (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_WAS_SHIFT)) & CRC_CTRLHU_WAS_MASK)
#define CRC_CTRLHU_FXOR_MASK (0x4U)
#define CRC_CTRLHU_FXOR_SHIFT (2U)
/*! FXOR
 *  0b0..No XOR on reading.
 *  0b1..Invert or complement the read value of CRC data register.
 */
#define CRC_CTRLHU_FXOR(x) (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_FXOR_SHIFT)) & CRC_CTRLHU_FXOR_MASK)
#define CRC_CTRLHU_TOTR_MASK (0x30U)
#define CRC_CTRLHU_TOTR_SHIFT (4U)
/*! TOTR
 *  0b00..No Transposition.
 *  0b01..Bits in bytes are transposed, bytes are not transposed.
 *  0b10..Both bits in bytes and bytes are transposed.
 *  0b11..Only bytes are transposed; no bits in a byte are transposed.
 */
#define CRC_CTRLHU_TOTR(x) (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_TOTR_SHIFT)) & CRC_CTRLHU_TOTR_MASK)
#define CRC_CTRLHU_TOT_MASK (0xC0U)
#define CRC_CTRLHU_TOT_SHIFT (6U)
/*! TOT
 *  0b00..No Transposition.
 *  0b01..Bits in bytes are transposed, bytes are not transposed.
 *  0b10..Both bits in bytes and bytes are transposed.
 *  0b11..Only bytes are transposed; no bits in a byte are transposed.
 */
#define CRC_CTRLHU_TOT(x) (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_TOT_SHIFT)) & CRC_CTRLHU_TOT_MASK)
/*! @} */

/*! @name CTRL - CRC Control register */
/*! @{ */
#define CRC_CTRL_TCRC_MASK (0x1000000U)
#define CRC_CTRL_TCRC_SHIFT (24U)
/*! TCRC
 *  0b0..16-bit CRC protocol.
 *  0b1..32-bit CRC protocol.
 */
#define CRC_CTRL_TCRC(x) (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_TCRC_SHIFT)) & CRC_CTRL_TCRC_MASK)
#define CRC_CTRL_WAS_MASK (0x2000000U)
#define CRC_CTRL_WAS_SHIFT (25U)
/*! WAS - Write CRC Data Register As Seed
 *  0b0..Writes to the CRC data register are data values.
 *  0b1..Writes to the CRC data register are seed values.
 */
#define CRC_CTRL_WAS(x) (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_WAS_SHIFT)) & CRC_CTRL_WAS_MASK)
#define CRC_CTRL_FXOR_MASK (0x4000000U)
#define CRC_CTRL_FXOR_SHIFT (26U)
/*! FXOR - Complement Read Of CRC Data Register
 *  0b0..No XOR on reading.
 *  0b1..Invert or complement the read value of the CRC Data register.
 */
#define CRC_CTRL_FXOR(x) (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_FXOR_SHIFT)) & CRC_CTRL_FXOR_MASK)
#define CRC_CTRL_TOTR_MASK (0x30000000U)
#define CRC_CTRL_TOTR_SHIFT (28U)
/*! TOTR - Type Of Transpose For Read
 *  0b00..No transposition.
 *  0b01..Bits in bytes are transposed; bytes are not transposed.
 *  0b10..Both bits in bytes and bytes are transposed.
 *  0b11..Only bytes are transposed; no bits in a byte are transposed.
 */
#define CRC_CTRL_TOTR(x) (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_TOTR_SHIFT)) & CRC_CTRL_TOTR_MASK)
#define CRC_CTRL_TOT_MASK (0xC0000000U)
#define CRC_CTRL_TOT_SHIFT (30U)
/*! TOT - Type Of Transpose For Writes
 *  0b00..No transposition.
 *  0b01..Bits in bytes are transposed; bytes are not transposed.
 *  0b10..Both bits in bytes and bytes are transposed.
 *  0b11..Only bytes are transposed; no bits in a byte are transposed.
 */
#define CRC_CTRL_TOT(x) (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_TOT_SHIFT)) & CRC_CTRL_TOT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group CRC_Register_Masks */

/* CRC - Peripheral instance base addresses */
/** Peripheral CRC base address */
#define CRC_BASE (0x40078000u)
/** Peripheral CRC base pointer */
#define CRC0 ((CRC_Type *)CRC_BASE)
/** Array initializer of CRC peripheral base addresses */
#define CRC_BASE_ADDRS \
    {                  \
        CRC_BASE       \
    }
/** Array initializer of CRC peripheral base pointers */
#define CRC_BASE_PTRS \
    {                 \
        CRC0          \
    }

/*!
 * @}
 */ /* end of group CRC_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- DAC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DAC_Peripheral_Access_Layer DAC Peripheral Access Layer
 * @{
 */

/** DAC - Register Layout Typedef */
typedef struct
{
    struct
    {                      /* offset: 0x0, array step: 0x2 */
        __IO uint8_t DATL; /**< DAC Data Low Register, array offset: 0x0, array step: 0x2 */
        __IO uint8_t DATH; /**< DAC Data High Register, array offset: 0x1, array step: 0x2 */
    } DAT[16];
    __IO uint8_t SR; /**< DAC Status Register, offset: 0x20 */
    __IO uint8_t C0; /**< DAC Control Register, offset: 0x21 */
    __IO uint8_t C1; /**< DAC Control Register 1, offset: 0x22 */
    __IO uint8_t C2; /**< DAC Control Register 2, offset: 0x23 */
} DAC_Type;

/* ----------------------------------------------------------------------------
   -- DAC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DAC_Register_Masks DAC Register Masks
 * @{
 */

/*! @name DATL - DAC Data Low Register */
/*! @{ */
#define DAC_DATL_DATA0_MASK (0xFFU)
#define DAC_DATL_DATA0_SHIFT (0U)
/*! DATA0 - DATA0
 */
#define DAC_DATL_DATA0(x) (((uint8_t)(((uint8_t)(x)) << DAC_DATL_DATA0_SHIFT)) & DAC_DATL_DATA0_MASK)
/*! @} */

/* The count of DAC_DATL */
#define DAC_DATL_COUNT (16U)

/*! @name DATH - DAC Data High Register */
/*! @{ */
#define DAC_DATH_DATA1_MASK (0xFU)
#define DAC_DATH_DATA1_SHIFT (0U)
/*! DATA1 - DATA1
 */
#define DAC_DATH_DATA1(x) (((uint8_t)(((uint8_t)(x)) << DAC_DATH_DATA1_SHIFT)) & DAC_DATH_DATA1_MASK)
/*! @} */

/* The count of DAC_DATH */
#define DAC_DATH_COUNT (16U)

/*! @name SR - DAC Status Register */
/*! @{ */
#define DAC_SR_DACBFRPBF_MASK (0x1U)
#define DAC_SR_DACBFRPBF_SHIFT (0U)
/*! DACBFRPBF - DAC Buffer Read Pointer Bottom Position Flag
 *  0b0..The DAC buffer read pointer is not equal to C2[DACBFUP].
 *  0b1..The DAC buffer read pointer is equal to C2[DACBFUP].
 */
#define DAC_SR_DACBFRPBF(x) (((uint8_t)(((uint8_t)(x)) << DAC_SR_DACBFRPBF_SHIFT)) & DAC_SR_DACBFRPBF_MASK)
#define DAC_SR_DACBFRPTF_MASK (0x2U)
#define DAC_SR_DACBFRPTF_SHIFT (1U)
/*! DACBFRPTF - DAC Buffer Read Pointer Top Position Flag
 *  0b0..The DAC buffer read pointer is not zero.
 *  0b1..The DAC buffer read pointer is zero.
 */
#define DAC_SR_DACBFRPTF(x) (((uint8_t)(((uint8_t)(x)) << DAC_SR_DACBFRPTF_SHIFT)) & DAC_SR_DACBFRPTF_MASK)
#define DAC_SR_DACBFWMF_MASK (0x4U)
#define DAC_SR_DACBFWMF_SHIFT (2U)
/*! DACBFWMF - DAC Buffer Watermark Flag
 *  0b0..The DAC buffer read pointer has not reached the watermark level.
 *  0b1..The DAC buffer read pointer has reached the watermark level.
 */
#define DAC_SR_DACBFWMF(x) (((uint8_t)(((uint8_t)(x)) << DAC_SR_DACBFWMF_SHIFT)) & DAC_SR_DACBFWMF_MASK)
/*! @} */

/*! @name C0 - DAC Control Register */
/*! @{ */
#define DAC_C0_DACBBIEN_MASK (0x1U)
#define DAC_C0_DACBBIEN_SHIFT (0U)
/*! DACBBIEN - DAC Buffer Read Pointer Bottom Flag Interrupt Enable
 *  0b0..The DAC buffer read pointer bottom flag interrupt is disabled.
 *  0b1..The DAC buffer read pointer bottom flag interrupt is enabled.
 */
#define DAC_C0_DACBBIEN(x) (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACBBIEN_SHIFT)) & DAC_C0_DACBBIEN_MASK)
#define DAC_C0_DACBTIEN_MASK (0x2U)
#define DAC_C0_DACBTIEN_SHIFT (1U)
/*! DACBTIEN - DAC Buffer Read Pointer Top Flag Interrupt Enable
 *  0b0..The DAC buffer read pointer top flag interrupt is disabled.
 *  0b1..The DAC buffer read pointer top flag interrupt is enabled.
 */
#define DAC_C0_DACBTIEN(x) (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACBTIEN_SHIFT)) & DAC_C0_DACBTIEN_MASK)
#define DAC_C0_DACBWIEN_MASK (0x4U)
#define DAC_C0_DACBWIEN_SHIFT (2U)
/*! DACBWIEN - DAC Buffer Watermark Interrupt Enable
 *  0b0..The DAC buffer watermark interrupt is disabled.
 *  0b1..The DAC buffer watermark interrupt is enabled.
 */
#define DAC_C0_DACBWIEN(x) (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACBWIEN_SHIFT)) & DAC_C0_DACBWIEN_MASK)
#define DAC_C0_LPEN_MASK (0x8U)
#define DAC_C0_LPEN_SHIFT (3U)
/*! LPEN - DAC Low Power Control
 *  0b0..High-Power mode
 *  0b1..Low-Power mode
 */
#define DAC_C0_LPEN(x) (((uint8_t)(((uint8_t)(x)) << DAC_C0_LPEN_SHIFT)) & DAC_C0_LPEN_MASK)
#define DAC_C0_DACSWTRG_MASK (0x10U)
#define DAC_C0_DACSWTRG_SHIFT (4U)
/*! DACSWTRG - DAC Software Trigger
 *  0b0..The DAC soft trigger is not valid.
 *  0b1..The DAC soft trigger is valid.
 */
#define DAC_C0_DACSWTRG(x) (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACSWTRG_SHIFT)) & DAC_C0_DACSWTRG_MASK)
#define DAC_C0_DACTRGSEL_MASK (0x20U)
#define DAC_C0_DACTRGSEL_SHIFT (5U)
/*! DACTRGSEL - DAC Trigger Select
 *  0b0..The DAC hardware trigger is selected.
 *  0b1..The DAC software trigger is selected.
 */
#define DAC_C0_DACTRGSEL(x) (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACTRGSEL_SHIFT)) & DAC_C0_DACTRGSEL_MASK)
#define DAC_C0_DACRFS_MASK (0x40U)
#define DAC_C0_DACRFS_SHIFT (6U)
/*! DACRFS - DAC Reference Select
 *  0b0..The DAC selects DACREF_1 as the reference voltage.
 *  0b1..The DAC selects DACREF_2 as the reference voltage.
 */
#define DAC_C0_DACRFS(x) (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACRFS_SHIFT)) & DAC_C0_DACRFS_MASK)
#define DAC_C0_DACEN_MASK (0x80U)
#define DAC_C0_DACEN_SHIFT (7U)
/*! DACEN - DAC Enable
 *  0b0..The DAC system is disabled.
 *  0b1..The DAC system is enabled.
 */
#define DAC_C0_DACEN(x) (((uint8_t)(((uint8_t)(x)) << DAC_C0_DACEN_SHIFT)) & DAC_C0_DACEN_MASK)
/*! @} */

/*! @name C1 - DAC Control Register 1 */
/*! @{ */
#define DAC_C1_DACBFEN_MASK (0x1U)
#define DAC_C1_DACBFEN_SHIFT (0U)
/*! DACBFEN - DAC Buffer Enable
 *  0b0..Buffer read pointer is disabled. The converted data is always the first word of the buffer.
 *  0b1..Buffer read pointer is enabled. The converted data is the word that the read pointer points to. It means
 *       converted data can be from any word of the buffer.
 */
#define DAC_C1_DACBFEN(x) (((uint8_t)(((uint8_t)(x)) << DAC_C1_DACBFEN_SHIFT)) & DAC_C1_DACBFEN_MASK)
#define DAC_C1_DACBFMD_MASK (0x6U)
#define DAC_C1_DACBFMD_SHIFT (1U)
/*! DACBFMD - DAC Buffer Work Mode Select
 *  0b00..Normal mode
 *  0b01..Swing mode
 *  0b10..One-Time Scan mode
 *  0b11..Reserved
 */
#define DAC_C1_DACBFMD(x) (((uint8_t)(((uint8_t)(x)) << DAC_C1_DACBFMD_SHIFT)) & DAC_C1_DACBFMD_MASK)
#define DAC_C1_DACBFWM_MASK (0x18U)
#define DAC_C1_DACBFWM_SHIFT (3U)
/*! DACBFWM - DAC Buffer Watermark Select
 *  0b00..1 word
 *  0b01..2 words
 *  0b10..3 words
 *  0b11..4 words
 */
#define DAC_C1_DACBFWM(x) (((uint8_t)(((uint8_t)(x)) << DAC_C1_DACBFWM_SHIFT)) & DAC_C1_DACBFWM_MASK)
#define DAC_C1_DMAEN_MASK (0x80U)
#define DAC_C1_DMAEN_SHIFT (7U)
/*! DMAEN - DMA Enable Select
 *  0b0..DMA is disabled.
 *  0b1..DMA is enabled. When DMA is enabled, the DMA request will be generated by original interrupts. The
 *       interrupts will not be presented on this module at the same time.
 */
#define DAC_C1_DMAEN(x) (((uint8_t)(((uint8_t)(x)) << DAC_C1_DMAEN_SHIFT)) & DAC_C1_DMAEN_MASK)
/*! @} */

/*! @name C2 - DAC Control Register 2 */
/*! @{ */
#define DAC_C2_DACBFUP_MASK (0xFU)
#define DAC_C2_DACBFUP_SHIFT (0U)
/*! DACBFUP - DAC Buffer Upper Limit
 */
#define DAC_C2_DACBFUP(x) (((uint8_t)(((uint8_t)(x)) << DAC_C2_DACBFUP_SHIFT)) & DAC_C2_DACBFUP_MASK)
#define DAC_C2_DACBFRP_MASK (0xF0U)
#define DAC_C2_DACBFRP_SHIFT (4U)
/*! DACBFRP - DAC Buffer Read Pointer
 */
#define DAC_C2_DACBFRP(x) (((uint8_t)(((uint8_t)(x)) << DAC_C2_DACBFRP_SHIFT)) & DAC_C2_DACBFRP_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group DAC_Register_Masks */

/* DAC - Peripheral instance base addresses */
/** Peripheral DAC0 base address */
#define DAC0_BASE (0x4006A000u)
/** Peripheral DAC0 base pointer */
#define DAC0 ((DAC_Type *)DAC0_BASE)
/** Array initializer of DAC peripheral base addresses */
#define DAC_BASE_ADDRS \
    {                  \
        DAC0_BASE      \
    }
/** Array initializer of DAC peripheral base pointers */
#define DAC_BASE_PTRS \
    {                 \
        DAC0          \
    }
/** Interrupt vectors for the DAC peripheral type */
#define DAC_IRQS  \
    {             \
        DAC0_IRQn \
    }

/*!
 * @}
 */ /* end of group DAC_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- DMA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Peripheral_Access_Layer DMA Peripheral Access Layer
 * @{
 */

/** DMA - Register Layout Typedef */
typedef struct
{
    __IO uint32_t CR; /**< Control Register, offset: 0x0 */
    __I uint32_t ES;  /**< Error Status Register, offset: 0x4 */
    uint8_t RESERVED_0[4];
    __IO uint32_t ERQ; /**< Enable Request Register, offset: 0xC */
    uint8_t RESERVED_1[4];
    __IO uint32_t EEI; /**< Enable Error Interrupt Register, offset: 0x14 */
    __O uint8_t CEEI;  /**< Clear Enable Error Interrupt Register, offset: 0x18 */
    __O uint8_t SEEI;  /**< Set Enable Error Interrupt Register, offset: 0x19 */
    __O uint8_t CERQ;  /**< Clear Enable Request Register, offset: 0x1A */
    __O uint8_t SERQ;  /**< Set Enable Request Register, offset: 0x1B */
    __O uint8_t CDNE;  /**< Clear DONE Status Bit Register, offset: 0x1C */
    __O uint8_t SSRT;  /**< Set START Bit Register, offset: 0x1D */
    __O uint8_t CERR;  /**< Clear Error Register, offset: 0x1E */
    __O uint8_t CINT;  /**< Clear Interrupt Request Register, offset: 0x1F */
    uint8_t RESERVED_2[4];
    __IO uint32_t INT; /**< Interrupt Request Register, offset: 0x24 */
    uint8_t RESERVED_3[4];
    __IO uint32_t ERR; /**< Error Register, offset: 0x2C */
    uint8_t RESERVED_4[4];
    __I uint32_t HRS; /**< Hardware Request Status Register, offset: 0x34 */
    uint8_t RESERVED_5[12];
    __IO uint32_t EARS; /**< Enable Asynchronous Request in Stop Register, offset: 0x44 */
    uint8_t RESERVED_6[184];
    __IO uint8_t DCHPRI3; /**< Channel n Priority Register, offset: 0x100 */
    __IO uint8_t DCHPRI2; /**< Channel n Priority Register, offset: 0x101 */
    __IO uint8_t DCHPRI1; /**< Channel n Priority Register, offset: 0x102 */
    __IO uint8_t DCHPRI0; /**< Channel n Priority Register, offset: 0x103 */
    __IO uint8_t DCHPRI7; /**< Channel n Priority Register, offset: 0x104 */
    __IO uint8_t DCHPRI6; /**< Channel n Priority Register, offset: 0x105 */
    __IO uint8_t DCHPRI5; /**< Channel n Priority Register, offset: 0x106 */
    __IO uint8_t DCHPRI4; /**< Channel n Priority Register, offset: 0x107 */
    uint8_t RESERVED_7[3832];
    struct
    {                        /* offset: 0x1000, array step: 0x20 */
        __IO uint32_t SADDR; /**< TCD Source Address, array offset: 0x1000, array step: 0x20 */
        __IO uint16_t SOFF;  /**< TCD Signed Source Address Offset, array offset: 0x1004, array step: 0x20 */
        __IO uint16_t ATTR;  /**< TCD Transfer Attributes, array offset: 0x1006, array step: 0x20 */
        union
        {                                 /* offset: 0x1008, array step: 0x20 */
            __IO uint32_t NBYTES_MLNO;    /**< TCD Minor Byte Count (Minor Loop Mapping Disabled), array offset: 0x1008,
                                             array step: 0x20 */
            __IO uint32_t NBYTES_MLOFFNO; /**< TCD Signed Minor Loop Offset (Minor Loop Mapping Enabled and Offset
                                             Disabled), array offset: 0x1008, array step: 0x20 */
            __IO uint32_t NBYTES_MLOFFYES; /**< TCD Signed Minor Loop Offset (Minor Loop Mapping and Offset Enabled),
                                              array offset: 0x1008, array step: 0x20 */
        };
        __IO uint32_t SLAST; /**< TCD Last Source Address Adjustment, array offset: 0x100C, array step: 0x20 */
        __IO uint32_t DADDR; /**< TCD Destination Address, array offset: 0x1010, array step: 0x20 */
        __IO uint16_t DOFF;  /**< TCD Signed Destination Address Offset, array offset: 0x1014, array step: 0x20 */
        union
        {                                 /* offset: 0x1016, array step: 0x20 */
            __IO uint16_t CITER_ELINKNO;  /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled),
                                             array offset: 0x1016, array step: 0x20 */
            __IO uint16_t CITER_ELINKYES; /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled),
                                             array offset: 0x1016, array step: 0x20 */
        };
        __IO uint32_t DLAST_SGA; /**< TCD Last Destination Address Adjustment/Scatter Gather Address, array offset:
                                    0x1018, array step: 0x20 */
        __IO uint16_t CSR;       /**< TCD Control and Status, array offset: 0x101C, array step: 0x20 */
        union
        {                                 /* offset: 0x101E, array step: 0x20 */
            __IO uint16_t BITER_ELINKNO;  /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking
                                             Disabled), array offset: 0x101E, array step: 0x20 */
            __IO uint16_t BITER_ELINKYES; /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking
                                             Enabled), array offset: 0x101E, array step: 0x20 */
        };
    } TCD[8];
} DMA_Type;

/* ----------------------------------------------------------------------------
   -- DMA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Masks DMA Register Masks
 * @{
 */

/*! @name CR - Control Register */
/*! @{ */
#define DMA_CR_EDBG_MASK (0x2U)
#define DMA_CR_EDBG_SHIFT (1U)
/*! EDBG - Enable Debug
 *  0b0..When in debug mode, the DMA continues to operate.
 *  0b1..When in debug mode, the DMA stalls the start of a new channel. Executing channels are allowed to
 *       complete. Channel execution resumes when the system exits debug mode or the EDBG bit is cleared.
 */
#define DMA_CR_EDBG(x) (((uint32_t)(((uint32_t)(x)) << DMA_CR_EDBG_SHIFT)) & DMA_CR_EDBG_MASK)
#define DMA_CR_ERCA_MASK (0x4U)
#define DMA_CR_ERCA_SHIFT (2U)
/*! ERCA - Enable Round Robin Channel Arbitration
 *  0b0..Fixed priority arbitration is used for channel selection .
 *  0b1..Round robin arbitration is used for channel selection .
 */
#define DMA_CR_ERCA(x) (((uint32_t)(((uint32_t)(x)) << DMA_CR_ERCA_SHIFT)) & DMA_CR_ERCA_MASK)
#define DMA_CR_HOE_MASK (0x10U)
#define DMA_CR_HOE_SHIFT (4U)
/*! HOE - Halt On Error
 *  0b0..Normal operation
 *  0b1..Any error causes the HALT bit to set. Subsequently, all service requests are ignored until the HALT bit is
 * cleared.
 */
#define DMA_CR_HOE(x) (((uint32_t)(((uint32_t)(x)) << DMA_CR_HOE_SHIFT)) & DMA_CR_HOE_MASK)
#define DMA_CR_HALT_MASK (0x20U)
#define DMA_CR_HALT_SHIFT (5U)
/*! HALT - Halt DMA Operations
 *  0b0..Normal operation
 *  0b1..Stall the start of any new channels. Executing channels are allowed to complete. Channel execution resumes when
 * this bit is cleared.
 */
#define DMA_CR_HALT(x) (((uint32_t)(((uint32_t)(x)) << DMA_CR_HALT_SHIFT)) & DMA_CR_HALT_MASK)
#define DMA_CR_CLM_MASK (0x40U)
#define DMA_CR_CLM_SHIFT (6U)
/*! CLM - Continuous Link Mode
 *  0b0..A minor loop channel link made to itself goes through channel arbitration before being activated again.
 *  0b1..A minor loop channel link made to itself does not go through channel arbitration before being activated
 *       again. Upon minor loop completion, the channel activates again if that channel has a minor loop channel
 *       link enabled and the link channel is itself. This effectively applies the minor loop offsets and restarts the
 *       next minor loop.
 */
#define DMA_CR_CLM(x) (((uint32_t)(((uint32_t)(x)) << DMA_CR_CLM_SHIFT)) & DMA_CR_CLM_MASK)
#define DMA_CR_EMLM_MASK (0x80U)
#define DMA_CR_EMLM_SHIFT (7U)
/*! EMLM - Enable Minor Loop Mapping
 *  0b0..Disabled. TCDn.word2 is defined as a 32-bit NBYTES field.
 *  0b1..Enabled. TCDn.word2 is redefined to include individual enable fields, an offset field, and the NBYTES
 *       field. The individual enable fields allow the minor loop offset to be applied to the source address, the
 *       destination address, or both. The NBYTES field is reduced when either offset is enabled.
 */
#define DMA_CR_EMLM(x) (((uint32_t)(((uint32_t)(x)) << DMA_CR_EMLM_SHIFT)) & DMA_CR_EMLM_MASK)
#define DMA_CR_ECX_MASK (0x10000U)
#define DMA_CR_ECX_SHIFT (16U)
/*! ECX - Error Cancel Transfer
 *  0b0..Normal operation
 *  0b1..Cancel the remaining data transfer in the same fashion as the CX bit. Stop the executing channel and
 *       force the minor loop to finish. The cancel takes effect after the last write of the current read/write
 *       sequence. The ECX bit clears itself after the cancel is honored. In addition to cancelling the transfer, ECX
 *       treats the cancel as an error condition, thus updating the Error Status register (DMAx_ES) and generating an
 *       optional error interrupt.
 */
#define DMA_CR_ECX(x) (((uint32_t)(((uint32_t)(x)) << DMA_CR_ECX_SHIFT)) & DMA_CR_ECX_MASK)
#define DMA_CR_CX_MASK (0x20000U)
#define DMA_CR_CX_SHIFT (17U)
/*! CX - Cancel Transfer
 *  0b0..Normal operation
 *  0b1..Cancel the remaining data transfer. Stop the executing channel and force the minor loop to finish. The
 *       cancel takes effect after the last write of the current read/write sequence. The CX bit clears itself after
 *       the cancel has been honored. This cancel retires the channel normally as if the minor loop was completed.
 */
#define DMA_CR_CX(x) (((uint32_t)(((uint32_t)(x)) << DMA_CR_CX_SHIFT)) & DMA_CR_CX_MASK)
#define DMA_CR_ACTIVE_MASK (0x80000000U)
#define DMA_CR_ACTIVE_SHIFT (31U)
/*! ACTIVE - DMA Active Status
 *  0b0..eDMA is idle.
 *  0b1..eDMA is executing a channel.
 */
#define DMA_CR_ACTIVE(x) (((uint32_t)(((uint32_t)(x)) << DMA_CR_ACTIVE_SHIFT)) & DMA_CR_ACTIVE_MASK)
/*! @} */

/*! @name ES - Error Status Register */
/*! @{ */
#define DMA_ES_DBE_MASK (0x1U)
#define DMA_ES_DBE_SHIFT (0U)
/*! DBE - Destination Bus Error
 *  0b0..No destination bus error
 *  0b1..The last recorded error was a bus error on a destination write
 */
#define DMA_ES_DBE(x) (((uint32_t)(((uint32_t)(x)) << DMA_ES_DBE_SHIFT)) & DMA_ES_DBE_MASK)
#define DMA_ES_SBE_MASK (0x2U)
#define DMA_ES_SBE_SHIFT (1U)
/*! SBE - Source Bus Error
 *  0b0..No source bus error
 *  0b1..The last recorded error was a bus error on a source read
 */
#define DMA_ES_SBE(x) (((uint32_t)(((uint32_t)(x)) << DMA_ES_SBE_SHIFT)) & DMA_ES_SBE_MASK)
#define DMA_ES_SGE_MASK (0x4U)
#define DMA_ES_SGE_SHIFT (2U)
/*! SGE - Scatter/Gather Configuration Error
 *  0b0..No scatter/gather configuration error
 *  0b1..The last recorded error was a configuration error detected in the TCDn_DLASTSGA field. This field is
 *       checked at the beginning of a scatter/gather operation after major loop completion if TCDn_CSR[ESG] is
 *       enabled. TCDn_DLASTSGA is not on a 32 byte boundary.
 */
#define DMA_ES_SGE(x) (((uint32_t)(((uint32_t)(x)) << DMA_ES_SGE_SHIFT)) & DMA_ES_SGE_MASK)
#define DMA_ES_NCE_MASK (0x8U)
#define DMA_ES_NCE_SHIFT (3U)
/*! NCE - NBYTES/CITER Configuration Error
 *  0b0..No NBYTES/CITER configuration error
 *  0b1..The last recorded error was a configuration error detected in the TCDn_NBYTES or TCDn_CITER fields.
 *       TCDn_NBYTES is not a multiple of TCDn_ATTR[SSIZE] and TCDn_ATTR[DSIZE], or TCDn_CITER[CITER] is equal to zero,
 *       or TCDn_CITER[ELINK] is not equal to TCDn_BITER[ELINK]
 */
#define DMA_ES_NCE(x) (((uint32_t)(((uint32_t)(x)) << DMA_ES_NCE_SHIFT)) & DMA_ES_NCE_MASK)
#define DMA_ES_DOE_MASK (0x10U)
#define DMA_ES_DOE_SHIFT (4U)
/*! DOE - Destination Offset Error
 *  0b0..No destination offset configuration error
 *  0b1..The last recorded error was a configuration error detected in the TCDn_DOFF field. TCDn_DOFF is inconsistent
 * with TCDn_ATTR[DSIZE].
 */
#define DMA_ES_DOE(x) (((uint32_t)(((uint32_t)(x)) << DMA_ES_DOE_SHIFT)) & DMA_ES_DOE_MASK)
#define DMA_ES_DAE_MASK (0x20U)
#define DMA_ES_DAE_SHIFT (5U)
/*! DAE - Destination Address Error
 *  0b0..No destination address configuration error
 *  0b1..The last recorded error was a configuration error detected in the TCDn_DADDR field. TCDn_DADDR is inconsistent
 * with TCDn_ATTR[DSIZE].
 */
#define DMA_ES_DAE(x) (((uint32_t)(((uint32_t)(x)) << DMA_ES_DAE_SHIFT)) & DMA_ES_DAE_MASK)
#define DMA_ES_SOE_MASK (0x40U)
#define DMA_ES_SOE_SHIFT (6U)
/*! SOE - Source Offset Error
 *  0b0..No source offset configuration error
 *  0b1..The last recorded error was a configuration error detected in the TCDn_SOFF field. TCDn_SOFF is inconsistent
 * with TCDn_ATTR[SSIZE].
 */
#define DMA_ES_SOE(x) (((uint32_t)(((uint32_t)(x)) << DMA_ES_SOE_SHIFT)) & DMA_ES_SOE_MASK)
#define DMA_ES_SAE_MASK (0x80U)
#define DMA_ES_SAE_SHIFT (7U)
/*! SAE - Source Address Error
 *  0b0..No source address configuration error.
 *  0b1..The last recorded error was a configuration error detected in the TCDn_SADDR field. TCDn_SADDR is inconsistent
 * with TCDn_ATTR[SSIZE].
 */
#define DMA_ES_SAE(x) (((uint32_t)(((uint32_t)(x)) << DMA_ES_SAE_SHIFT)) & DMA_ES_SAE_MASK)
#define DMA_ES_ERRCHN_MASK (0x700U)
#define DMA_ES_ERRCHN_SHIFT (8U)
/*! ERRCHN - Error Channel Number or Canceled Channel Number
 */
#define DMA_ES_ERRCHN(x) (((uint32_t)(((uint32_t)(x)) << DMA_ES_ERRCHN_SHIFT)) & DMA_ES_ERRCHN_MASK)
#define DMA_ES_CPE_MASK (0x4000U)
#define DMA_ES_CPE_SHIFT (14U)
/*! CPE - Channel Priority Error
 *  0b0..No channel priority error
 *  0b1..The last recorded error was a configuration error in the channel priorities . Channel priorities are not
 * unique.
 */
#define DMA_ES_CPE(x) (((uint32_t)(((uint32_t)(x)) << DMA_ES_CPE_SHIFT)) & DMA_ES_CPE_MASK)
#define DMA_ES_ECX_MASK (0x10000U)
#define DMA_ES_ECX_SHIFT (16U)
/*! ECX - Transfer Canceled
 *  0b0..No canceled transfers
 *  0b1..The last recorded entry was a canceled transfer by the error cancel transfer input
 */
#define DMA_ES_ECX(x) (((uint32_t)(((uint32_t)(x)) << DMA_ES_ECX_SHIFT)) & DMA_ES_ECX_MASK)
#define DMA_ES_VLD_MASK (0x80000000U)
#define DMA_ES_VLD_SHIFT (31U)
/*! VLD
 *  0b0..No ERR bits are set.
 *  0b1..At least one ERR bit is set indicating a valid error exists that has not been cleared.
 */
#define DMA_ES_VLD(x) (((uint32_t)(((uint32_t)(x)) << DMA_ES_VLD_SHIFT)) & DMA_ES_VLD_MASK)
/*! @} */

/*! @name ERQ - Enable Request Register */
/*! @{ */
#define DMA_ERQ_ERQ0_MASK (0x1U)
#define DMA_ERQ_ERQ0_SHIFT (0U)
/*! ERQ0 - Enable DMA Request 0
 *  0b0..The DMA request signal for the corresponding channel is disabled
 *  0b1..The DMA request signal for the corresponding channel is enabled
 */
#define DMA_ERQ_ERQ0(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ0_SHIFT)) & DMA_ERQ_ERQ0_MASK)
#define DMA_ERQ_ERQ1_MASK (0x2U)
#define DMA_ERQ_ERQ1_SHIFT (1U)
/*! ERQ1 - Enable DMA Request 1
 *  0b0..The DMA request signal for the corresponding channel is disabled
 *  0b1..The DMA request signal for the corresponding channel is enabled
 */
#define DMA_ERQ_ERQ1(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ1_SHIFT)) & DMA_ERQ_ERQ1_MASK)
#define DMA_ERQ_ERQ2_MASK (0x4U)
#define DMA_ERQ_ERQ2_SHIFT (2U)
/*! ERQ2 - Enable DMA Request 2
 *  0b0..The DMA request signal for the corresponding channel is disabled
 *  0b1..The DMA request signal for the corresponding channel is enabled
 */
#define DMA_ERQ_ERQ2(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ2_SHIFT)) & DMA_ERQ_ERQ2_MASK)
#define DMA_ERQ_ERQ3_MASK (0x8U)
#define DMA_ERQ_ERQ3_SHIFT (3U)
/*! ERQ3 - Enable DMA Request 3
 *  0b0..The DMA request signal for the corresponding channel is disabled
 *  0b1..The DMA request signal for the corresponding channel is enabled
 */
#define DMA_ERQ_ERQ3(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ3_SHIFT)) & DMA_ERQ_ERQ3_MASK)
#define DMA_ERQ_ERQ4_MASK (0x10U)
#define DMA_ERQ_ERQ4_SHIFT (4U)
/*! ERQ4 - Enable DMA Request 4
 *  0b0..The DMA request signal for the corresponding channel is disabled
 *  0b1..The DMA request signal for the corresponding channel is enabled
 */
#define DMA_ERQ_ERQ4(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ4_SHIFT)) & DMA_ERQ_ERQ4_MASK)
#define DMA_ERQ_ERQ5_MASK (0x20U)
#define DMA_ERQ_ERQ5_SHIFT (5U)
/*! ERQ5 - Enable DMA Request 5
 *  0b0..The DMA request signal for the corresponding channel is disabled
 *  0b1..The DMA request signal for the corresponding channel is enabled
 */
#define DMA_ERQ_ERQ5(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ5_SHIFT)) & DMA_ERQ_ERQ5_MASK)
#define DMA_ERQ_ERQ6_MASK (0x40U)
#define DMA_ERQ_ERQ6_SHIFT (6U)
/*! ERQ6 - Enable DMA Request 6
 *  0b0..The DMA request signal for the corresponding channel is disabled
 *  0b1..The DMA request signal for the corresponding channel is enabled
 */
#define DMA_ERQ_ERQ6(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ6_SHIFT)) & DMA_ERQ_ERQ6_MASK)
#define DMA_ERQ_ERQ7_MASK (0x80U)
#define DMA_ERQ_ERQ7_SHIFT (7U)
/*! ERQ7 - Enable DMA Request 7
 *  0b0..The DMA request signal for the corresponding channel is disabled
 *  0b1..The DMA request signal for the corresponding channel is enabled
 */
#define DMA_ERQ_ERQ7(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ7_SHIFT)) & DMA_ERQ_ERQ7_MASK)
/*! @} */

/*! @name EEI - Enable Error Interrupt Register */
/*! @{ */
#define DMA_EEI_EEI0_MASK (0x1U)
#define DMA_EEI_EEI0_SHIFT (0U)
/*! EEI0 - Enable Error Interrupt 0
 *  0b0..The error signal for corresponding channel does not generate an error interrupt
 *  0b1..The assertion of the error signal for corresponding channel generates an error interrupt request
 */
#define DMA_EEI_EEI0(x) (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI0_SHIFT)) & DMA_EEI_EEI0_MASK)
#define DMA_EEI_EEI1_MASK (0x2U)
#define DMA_EEI_EEI1_SHIFT (1U)
/*! EEI1 - Enable Error Interrupt 1
 *  0b0..The error signal for corresponding channel does not generate an error interrupt
 *  0b1..The assertion of the error signal for corresponding channel generates an error interrupt request
 */
#define DMA_EEI_EEI1(x) (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI1_SHIFT)) & DMA_EEI_EEI1_MASK)
#define DMA_EEI_EEI2_MASK (0x4U)
#define DMA_EEI_EEI2_SHIFT (2U)
/*! EEI2 - Enable Error Interrupt 2
 *  0b0..The error signal for corresponding channel does not generate an error interrupt
 *  0b1..The assertion of the error signal for corresponding channel generates an error interrupt request
 */
#define DMA_EEI_EEI2(x) (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI2_SHIFT)) & DMA_EEI_EEI2_MASK)
#define DMA_EEI_EEI3_MASK (0x8U)
#define DMA_EEI_EEI3_SHIFT (3U)
/*! EEI3 - Enable Error Interrupt 3
 *  0b0..The error signal for corresponding channel does not generate an error interrupt
 *  0b1..The assertion of the error signal for corresponding channel generates an error interrupt request
 */
#define DMA_EEI_EEI3(x) (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI3_SHIFT)) & DMA_EEI_EEI3_MASK)
#define DMA_EEI_EEI4_MASK (0x10U)
#define DMA_EEI_EEI4_SHIFT (4U)
/*! EEI4 - Enable Error Interrupt 4
 *  0b0..The error signal for corresponding channel does not generate an error interrupt
 *  0b1..The assertion of the error signal for corresponding channel generates an error interrupt request
 */
#define DMA_EEI_EEI4(x) (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI4_SHIFT)) & DMA_EEI_EEI4_MASK)
#define DMA_EEI_EEI5_MASK (0x20U)
#define DMA_EEI_EEI5_SHIFT (5U)
/*! EEI5 - Enable Error Interrupt 5
 *  0b0..The error signal for corresponding channel does not generate an error interrupt
 *  0b1..The assertion of the error signal for corresponding channel generates an error interrupt request
 */
#define DMA_EEI_EEI5(x) (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI5_SHIFT)) & DMA_EEI_EEI5_MASK)
#define DMA_EEI_EEI6_MASK (0x40U)
#define DMA_EEI_EEI6_SHIFT (6U)
/*! EEI6 - Enable Error Interrupt 6
 *  0b0..The error signal for corresponding channel does not generate an error interrupt
 *  0b1..The assertion of the error signal for corresponding channel generates an error interrupt request
 */
#define DMA_EEI_EEI6(x) (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI6_SHIFT)) & DMA_EEI_EEI6_MASK)
#define DMA_EEI_EEI7_MASK (0x80U)
#define DMA_EEI_EEI7_SHIFT (7U)
/*! EEI7 - Enable Error Interrupt 7
 *  0b0..The error signal for corresponding channel does not generate an error interrupt
 *  0b1..The assertion of the error signal for corresponding channel generates an error interrupt request
 */
#define DMA_EEI_EEI7(x) (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI7_SHIFT)) & DMA_EEI_EEI7_MASK)
/*! @} */

/*! @name CEEI - Clear Enable Error Interrupt Register */
/*! @{ */
#define DMA_CEEI_CEEI_MASK (0x7U)
#define DMA_CEEI_CEEI_SHIFT (0U)
/*! CEEI - Clear Enable Error Interrupt
 */
#define DMA_CEEI_CEEI(x) (((uint8_t)(((uint8_t)(x)) << DMA_CEEI_CEEI_SHIFT)) & DMA_CEEI_CEEI_MASK)
#define DMA_CEEI_CAEE_MASK (0x40U)
#define DMA_CEEI_CAEE_SHIFT (6U)
/*! CAEE - Clear All Enable Error Interrupts
 *  0b0..Clear only the EEI bit specified in the CEEI field
 *  0b1..Clear all bits in EEI
 */
#define DMA_CEEI_CAEE(x) (((uint8_t)(((uint8_t)(x)) << DMA_CEEI_CAEE_SHIFT)) & DMA_CEEI_CAEE_MASK)
#define DMA_CEEI_NOP_MASK (0x80U)
#define DMA_CEEI_NOP_SHIFT (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_CEEI_NOP(x) (((uint8_t)(((uint8_t)(x)) << DMA_CEEI_NOP_SHIFT)) & DMA_CEEI_NOP_MASK)
/*! @} */

/*! @name SEEI - Set Enable Error Interrupt Register */
/*! @{ */
#define DMA_SEEI_SEEI_MASK (0x7U)
#define DMA_SEEI_SEEI_SHIFT (0U)
/*! SEEI - Set Enable Error Interrupt
 */
#define DMA_SEEI_SEEI(x) (((uint8_t)(((uint8_t)(x)) << DMA_SEEI_SEEI_SHIFT)) & DMA_SEEI_SEEI_MASK)
#define DMA_SEEI_SAEE_MASK (0x40U)
#define DMA_SEEI_SAEE_SHIFT (6U)
/*! SAEE - Sets All Enable Error Interrupts
 *  0b0..Set only the EEI bit specified in the SEEI field.
 *  0b1..Sets all bits in EEI
 */
#define DMA_SEEI_SAEE(x) (((uint8_t)(((uint8_t)(x)) << DMA_SEEI_SAEE_SHIFT)) & DMA_SEEI_SAEE_MASK)
#define DMA_SEEI_NOP_MASK (0x80U)
#define DMA_SEEI_NOP_SHIFT (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_SEEI_NOP(x) (((uint8_t)(((uint8_t)(x)) << DMA_SEEI_NOP_SHIFT)) & DMA_SEEI_NOP_MASK)
/*! @} */

/*! @name CERQ - Clear Enable Request Register */
/*! @{ */
#define DMA_CERQ_CERQ_MASK (0x7U)
#define DMA_CERQ_CERQ_SHIFT (0U)
/*! CERQ - Clear Enable Request
 */
#define DMA_CERQ_CERQ(x) (((uint8_t)(((uint8_t)(x)) << DMA_CERQ_CERQ_SHIFT)) & DMA_CERQ_CERQ_MASK)
#define DMA_CERQ_CAER_MASK (0x40U)
#define DMA_CERQ_CAER_SHIFT (6U)
/*! CAER - Clear All Enable Requests
 *  0b0..Clear only the ERQ bit specified in the CERQ field
 *  0b1..Clear all bits in ERQ
 */
#define DMA_CERQ_CAER(x) (((uint8_t)(((uint8_t)(x)) << DMA_CERQ_CAER_SHIFT)) & DMA_CERQ_CAER_MASK)
#define DMA_CERQ_NOP_MASK (0x80U)
#define DMA_CERQ_NOP_SHIFT (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_CERQ_NOP(x) (((uint8_t)(((uint8_t)(x)) << DMA_CERQ_NOP_SHIFT)) & DMA_CERQ_NOP_MASK)
/*! @} */

/*! @name SERQ - Set Enable Request Register */
/*! @{ */
#define DMA_SERQ_SERQ_MASK (0x7U)
#define DMA_SERQ_SERQ_SHIFT (0U)
/*! SERQ - Set Enable Request
 */
#define DMA_SERQ_SERQ(x) (((uint8_t)(((uint8_t)(x)) << DMA_SERQ_SERQ_SHIFT)) & DMA_SERQ_SERQ_MASK)
#define DMA_SERQ_SAER_MASK (0x40U)
#define DMA_SERQ_SAER_SHIFT (6U)
/*! SAER - Set All Enable Requests
 *  0b0..Set only the ERQ bit specified in the SERQ field
 *  0b1..Set all bits in ERQ
 */
#define DMA_SERQ_SAER(x) (((uint8_t)(((uint8_t)(x)) << DMA_SERQ_SAER_SHIFT)) & DMA_SERQ_SAER_MASK)
#define DMA_SERQ_NOP_MASK (0x80U)
#define DMA_SERQ_NOP_SHIFT (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_SERQ_NOP(x) (((uint8_t)(((uint8_t)(x)) << DMA_SERQ_NOP_SHIFT)) & DMA_SERQ_NOP_MASK)
/*! @} */

/*! @name CDNE - Clear DONE Status Bit Register */
/*! @{ */
#define DMA_CDNE_CDNE_MASK (0x7U)
#define DMA_CDNE_CDNE_SHIFT (0U)
/*! CDNE - Clear DONE Bit
 */
#define DMA_CDNE_CDNE(x) (((uint8_t)(((uint8_t)(x)) << DMA_CDNE_CDNE_SHIFT)) & DMA_CDNE_CDNE_MASK)
#define DMA_CDNE_CADN_MASK (0x40U)
#define DMA_CDNE_CADN_SHIFT (6U)
/*! CADN - Clears All DONE Bits
 *  0b0..Clears only the TCDn_CSR[DONE] bit specified in the CDNE field
 *  0b1..Clears all bits in TCDn_CSR[DONE]
 */
#define DMA_CDNE_CADN(x) (((uint8_t)(((uint8_t)(x)) << DMA_CDNE_CADN_SHIFT)) & DMA_CDNE_CADN_MASK)
#define DMA_CDNE_NOP_MASK (0x80U)
#define DMA_CDNE_NOP_SHIFT (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_CDNE_NOP(x) (((uint8_t)(((uint8_t)(x)) << DMA_CDNE_NOP_SHIFT)) & DMA_CDNE_NOP_MASK)
/*! @} */

/*! @name SSRT - Set START Bit Register */
/*! @{ */
#define DMA_SSRT_SSRT_MASK (0x7U)
#define DMA_SSRT_SSRT_SHIFT (0U)
/*! SSRT - Set START Bit
 */
#define DMA_SSRT_SSRT(x) (((uint8_t)(((uint8_t)(x)) << DMA_SSRT_SSRT_SHIFT)) & DMA_SSRT_SSRT_MASK)
#define DMA_SSRT_SAST_MASK (0x40U)
#define DMA_SSRT_SAST_SHIFT (6U)
/*! SAST - Set All START Bits (activates all channels)
 *  0b0..Set only the TCDn_CSR[START] bit specified in the SSRT field
 *  0b1..Set all bits in TCDn_CSR[START]
 */
#define DMA_SSRT_SAST(x) (((uint8_t)(((uint8_t)(x)) << DMA_SSRT_SAST_SHIFT)) & DMA_SSRT_SAST_MASK)
#define DMA_SSRT_NOP_MASK (0x80U)
#define DMA_SSRT_NOP_SHIFT (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_SSRT_NOP(x) (((uint8_t)(((uint8_t)(x)) << DMA_SSRT_NOP_SHIFT)) & DMA_SSRT_NOP_MASK)
/*! @} */

/*! @name CERR - Clear Error Register */
/*! @{ */
#define DMA_CERR_CERR_MASK (0x7U)
#define DMA_CERR_CERR_SHIFT (0U)
/*! CERR - Clear Error Indicator
 */
#define DMA_CERR_CERR(x) (((uint8_t)(((uint8_t)(x)) << DMA_CERR_CERR_SHIFT)) & DMA_CERR_CERR_MASK)
#define DMA_CERR_CAEI_MASK (0x40U)
#define DMA_CERR_CAEI_SHIFT (6U)
/*! CAEI - Clear All Error Indicators
 *  0b0..Clear only the ERR bit specified in the CERR field
 *  0b1..Clear all bits in ERR
 */
#define DMA_CERR_CAEI(x) (((uint8_t)(((uint8_t)(x)) << DMA_CERR_CAEI_SHIFT)) & DMA_CERR_CAEI_MASK)
#define DMA_CERR_NOP_MASK (0x80U)
#define DMA_CERR_NOP_SHIFT (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_CERR_NOP(x) (((uint8_t)(((uint8_t)(x)) << DMA_CERR_NOP_SHIFT)) & DMA_CERR_NOP_MASK)
/*! @} */

/*! @name CINT - Clear Interrupt Request Register */
/*! @{ */
#define DMA_CINT_CINT_MASK (0x7U)
#define DMA_CINT_CINT_SHIFT (0U)
/*! CINT - Clear Interrupt Request
 */
#define DMA_CINT_CINT(x) (((uint8_t)(((uint8_t)(x)) << DMA_CINT_CINT_SHIFT)) & DMA_CINT_CINT_MASK)
#define DMA_CINT_CAIR_MASK (0x40U)
#define DMA_CINT_CAIR_SHIFT (6U)
/*! CAIR - Clear All Interrupt Requests
 *  0b0..Clear only the INT bit specified in the CINT field
 *  0b1..Clear all bits in INT
 */
#define DMA_CINT_CAIR(x) (((uint8_t)(((uint8_t)(x)) << DMA_CINT_CAIR_SHIFT)) & DMA_CINT_CAIR_MASK)
#define DMA_CINT_NOP_MASK (0x80U)
#define DMA_CINT_NOP_SHIFT (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_CINT_NOP(x) (((uint8_t)(((uint8_t)(x)) << DMA_CINT_NOP_SHIFT)) & DMA_CINT_NOP_MASK)
/*! @} */

/*! @name INT - Interrupt Request Register */
/*! @{ */
#define DMA_INT_INT0_MASK (0x1U)
#define DMA_INT_INT0_SHIFT (0U)
/*! INT0 - Interrupt Request 0
 *  0b0..The interrupt request for corresponding channel is cleared
 *  0b1..The interrupt request for corresponding channel is active
 */
#define DMA_INT_INT0(x) (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT0_SHIFT)) & DMA_INT_INT0_MASK)
#define DMA_INT_INT1_MASK (0x2U)
#define DMA_INT_INT1_SHIFT (1U)
/*! INT1 - Interrupt Request 1
 *  0b0..The interrupt request for corresponding channel is cleared
 *  0b1..The interrupt request for corresponding channel is active
 */
#define DMA_INT_INT1(x) (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT1_SHIFT)) & DMA_INT_INT1_MASK)
#define DMA_INT_INT2_MASK (0x4U)
#define DMA_INT_INT2_SHIFT (2U)
/*! INT2 - Interrupt Request 2
 *  0b0..The interrupt request for corresponding channel is cleared
 *  0b1..The interrupt request for corresponding channel is active
 */
#define DMA_INT_INT2(x) (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT2_SHIFT)) & DMA_INT_INT2_MASK)
#define DMA_INT_INT3_MASK (0x8U)
#define DMA_INT_INT3_SHIFT (3U)
/*! INT3 - Interrupt Request 3
 *  0b0..The interrupt request for corresponding channel is cleared
 *  0b1..The interrupt request for corresponding channel is active
 */
#define DMA_INT_INT3(x) (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT3_SHIFT)) & DMA_INT_INT3_MASK)
#define DMA_INT_INT4_MASK (0x10U)
#define DMA_INT_INT4_SHIFT (4U)
/*! INT4 - Interrupt Request 4
 *  0b0..The interrupt request for corresponding channel is cleared
 *  0b1..The interrupt request for corresponding channel is active
 */
#define DMA_INT_INT4(x) (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT4_SHIFT)) & DMA_INT_INT4_MASK)
#define DMA_INT_INT5_MASK (0x20U)
#define DMA_INT_INT5_SHIFT (5U)
/*! INT5 - Interrupt Request 5
 *  0b0..The interrupt request for corresponding channel is cleared
 *  0b1..The interrupt request for corresponding channel is active
 */
#define DMA_INT_INT5(x) (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT5_SHIFT)) & DMA_INT_INT5_MASK)
#define DMA_INT_INT6_MASK (0x40U)
#define DMA_INT_INT6_SHIFT (6U)
/*! INT6 - Interrupt Request 6
 *  0b0..The interrupt request for corresponding channel is cleared
 *  0b1..The interrupt request for corresponding channel is active
 */
#define DMA_INT_INT6(x) (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT6_SHIFT)) & DMA_INT_INT6_MASK)
#define DMA_INT_INT7_MASK (0x80U)
#define DMA_INT_INT7_SHIFT (7U)
/*! INT7 - Interrupt Request 7
 *  0b0..The interrupt request for corresponding channel is cleared
 *  0b1..The interrupt request for corresponding channel is active
 */
#define DMA_INT_INT7(x) (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT7_SHIFT)) & DMA_INT_INT7_MASK)
/*! @} */

/*! @name ERR - Error Register */
/*! @{ */
#define DMA_ERR_ERR0_MASK (0x1U)
#define DMA_ERR_ERR0_SHIFT (0U)
/*! ERR0 - Error In Channel 0
 *  0b0..An error in this channel has not occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR0(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR0_SHIFT)) & DMA_ERR_ERR0_MASK)
#define DMA_ERR_ERR1_MASK (0x2U)
#define DMA_ERR_ERR1_SHIFT (1U)
/*! ERR1 - Error In Channel 1
 *  0b0..An error in this channel has not occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR1(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR1_SHIFT)) & DMA_ERR_ERR1_MASK)
#define DMA_ERR_ERR2_MASK (0x4U)
#define DMA_ERR_ERR2_SHIFT (2U)
/*! ERR2 - Error In Channel 2
 *  0b0..An error in this channel has not occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR2(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR2_SHIFT)) & DMA_ERR_ERR2_MASK)
#define DMA_ERR_ERR3_MASK (0x8U)
#define DMA_ERR_ERR3_SHIFT (3U)
/*! ERR3 - Error In Channel 3
 *  0b0..An error in this channel has not occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR3(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR3_SHIFT)) & DMA_ERR_ERR3_MASK)
#define DMA_ERR_ERR4_MASK (0x10U)
#define DMA_ERR_ERR4_SHIFT (4U)
/*! ERR4 - Error In Channel 4
 *  0b0..An error in this channel has not occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR4(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR4_SHIFT)) & DMA_ERR_ERR4_MASK)
#define DMA_ERR_ERR5_MASK (0x20U)
#define DMA_ERR_ERR5_SHIFT (5U)
/*! ERR5 - Error In Channel 5
 *  0b0..An error in this channel has not occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR5(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR5_SHIFT)) & DMA_ERR_ERR5_MASK)
#define DMA_ERR_ERR6_MASK (0x40U)
#define DMA_ERR_ERR6_SHIFT (6U)
/*! ERR6 - Error In Channel 6
 *  0b0..An error in this channel has not occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR6(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR6_SHIFT)) & DMA_ERR_ERR6_MASK)
#define DMA_ERR_ERR7_MASK (0x80U)
#define DMA_ERR_ERR7_SHIFT (7U)
/*! ERR7 - Error In Channel 7
 *  0b0..An error in this channel has not occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR7(x) (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR7_SHIFT)) & DMA_ERR_ERR7_MASK)
/*! @} */

/*! @name HRS - Hardware Request Status Register */
/*! @{ */
#define DMA_HRS_HRS0_MASK (0x1U)
#define DMA_HRS_HRS0_SHIFT (0U)
/*! HRS0 - Hardware Request Status Channel 0
 *  0b0..A hardware service request for channel 0 is not present
 *  0b1..A hardware service request for channel 0 is present
 */
#define DMA_HRS_HRS0(x) (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS0_SHIFT)) & DMA_HRS_HRS0_MASK)
#define DMA_HRS_HRS1_MASK (0x2U)
#define DMA_HRS_HRS1_SHIFT (1U)
/*! HRS1 - Hardware Request Status Channel 1
 *  0b0..A hardware service request for channel 1 is not present
 *  0b1..A hardware service request for channel 1 is present
 */
#define DMA_HRS_HRS1(x) (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS1_SHIFT)) & DMA_HRS_HRS1_MASK)
#define DMA_HRS_HRS2_MASK (0x4U)
#define DMA_HRS_HRS2_SHIFT (2U)
/*! HRS2 - Hardware Request Status Channel 2
 *  0b0..A hardware service request for channel 2 is not present
 *  0b1..A hardware service request for channel 2 is present
 */
#define DMA_HRS_HRS2(x) (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS2_SHIFT)) & DMA_HRS_HRS2_MASK)
#define DMA_HRS_HRS3_MASK (0x8U)
#define DMA_HRS_HRS3_SHIFT (3U)
/*! HRS3 - Hardware Request Status Channel 3
 *  0b0..A hardware service request for channel 3 is not present
 *  0b1..A hardware service request for channel 3 is present
 */
#define DMA_HRS_HRS3(x) (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS3_SHIFT)) & DMA_HRS_HRS3_MASK)
#define DMA_HRS_HRS4_MASK (0x10U)
#define DMA_HRS_HRS4_SHIFT (4U)
/*! HRS4 - Hardware Request Status Channel 4
 *  0b0..A hardware service request for channel 4 is not present
 *  0b1..A hardware service request for channel 4 is present
 */
#define DMA_HRS_HRS4(x) (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS4_SHIFT)) & DMA_HRS_HRS4_MASK)
#define DMA_HRS_HRS5_MASK (0x20U)
#define DMA_HRS_HRS5_SHIFT (5U)
/*! HRS5 - Hardware Request Status Channel 5
 *  0b0..A hardware service request for channel 5 is not present
 *  0b1..A hardware service request for channel 5 is present
 */
#define DMA_HRS_HRS5(x) (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS5_SHIFT)) & DMA_HRS_HRS5_MASK)
#define DMA_HRS_HRS6_MASK (0x40U)
#define DMA_HRS_HRS6_SHIFT (6U)
/*! HRS6 - Hardware Request Status Channel 6
 *  0b0..A hardware service request for channel 6 is not present
 *  0b1..A hardware service request for channel 6 is present
 */
#define DMA_HRS_HRS6(x) (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS6_SHIFT)) & DMA_HRS_HRS6_MASK)
#define DMA_HRS_HRS7_MASK (0x80U)
#define DMA_HRS_HRS7_SHIFT (7U)
/*! HRS7 - Hardware Request Status Channel 7
 *  0b0..A hardware service request for channel 7 is not present
 *  0b1..A hardware service request for channel 7 is present
 */
#define DMA_HRS_HRS7(x) (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS7_SHIFT)) & DMA_HRS_HRS7_MASK)
/*! @} */

/*! @name EARS - Enable Asynchronous Request in Stop Register */
/*! @{ */
#define DMA_EARS_EDREQ_0_MASK (0x1U)
#define DMA_EARS_EDREQ_0_SHIFT (0U)
/*! EDREQ_0 - Enable asynchronous DMA request in stop mode for channel 0.
 *  0b0..Disable asynchronous DMA request for channel 0.
 *  0b1..Enable asynchronous DMA request for channel 0.
 */
#define DMA_EARS_EDREQ_0(x) (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_0_SHIFT)) & DMA_EARS_EDREQ_0_MASK)
#define DMA_EARS_EDREQ_1_MASK (0x2U)
#define DMA_EARS_EDREQ_1_SHIFT (1U)
/*! EDREQ_1 - Enable asynchronous DMA request in stop mode for channel 1.
 *  0b0..Disable asynchronous DMA request for channel 1
 *  0b1..Enable asynchronous DMA request for channel 1.
 */
#define DMA_EARS_EDREQ_1(x) (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_1_SHIFT)) & DMA_EARS_EDREQ_1_MASK)
#define DMA_EARS_EDREQ_2_MASK (0x4U)
#define DMA_EARS_EDREQ_2_SHIFT (2U)
/*! EDREQ_2 - Enable asynchronous DMA request in stop mode for channel 2.
 *  0b0..Disable asynchronous DMA request for channel 2.
 *  0b1..Enable asynchronous DMA request for channel 2.
 */
#define DMA_EARS_EDREQ_2(x) (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_2_SHIFT)) & DMA_EARS_EDREQ_2_MASK)
#define DMA_EARS_EDREQ_3_MASK (0x8U)
#define DMA_EARS_EDREQ_3_SHIFT (3U)
/*! EDREQ_3 - Enable asynchronous DMA request in stop mode for channel 3.
 *  0b0..Disable asynchronous DMA request for channel 3.
 *  0b1..Enable asynchronous DMA request for channel 3.
 */
#define DMA_EARS_EDREQ_3(x) (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_3_SHIFT)) & DMA_EARS_EDREQ_3_MASK)
#define DMA_EARS_EDREQ_4_MASK (0x10U)
#define DMA_EARS_EDREQ_4_SHIFT (4U)
/*! EDREQ_4 - Enable asynchronous DMA request in stop mode for channel 4
 *  0b0..Disable asynchronous DMA request for channel 4.
 *  0b1..Enable asynchronous DMA request for channel 4.
 */
#define DMA_EARS_EDREQ_4(x) (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_4_SHIFT)) & DMA_EARS_EDREQ_4_MASK)
#define DMA_EARS_EDREQ_5_MASK (0x20U)
#define DMA_EARS_EDREQ_5_SHIFT (5U)
/*! EDREQ_5 - Enable asynchronous DMA request in stop mode for channel 5
 *  0b0..Disable asynchronous DMA request for channel 5.
 *  0b1..Enable asynchronous DMA request for channel 5.
 */
#define DMA_EARS_EDREQ_5(x) (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_5_SHIFT)) & DMA_EARS_EDREQ_5_MASK)
#define DMA_EARS_EDREQ_6_MASK (0x40U)
#define DMA_EARS_EDREQ_6_SHIFT (6U)
/*! EDREQ_6 - Enable asynchronous DMA request in stop mode for channel 6
 *  0b0..Disable asynchronous DMA request for channel 6.
 *  0b1..Enable asynchronous DMA request for channel 6.
 */
#define DMA_EARS_EDREQ_6(x) (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_6_SHIFT)) & DMA_EARS_EDREQ_6_MASK)
#define DMA_EARS_EDREQ_7_MASK (0x80U)
#define DMA_EARS_EDREQ_7_SHIFT (7U)
/*! EDREQ_7 - Enable asynchronous DMA request in stop mode for channel 7
 *  0b0..Disable asynchronous DMA request for channel 7.
 *  0b1..Enable asynchronous DMA request for channel 7.
 */
#define DMA_EARS_EDREQ_7(x) (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_7_SHIFT)) & DMA_EARS_EDREQ_7_MASK)
/*! @} */

/*! @name DCHPRI3 - Channel n Priority Register */
/*! @{ */
#define DMA_DCHPRI3_CHPRI_MASK (0x7U)
#define DMA_DCHPRI3_CHPRI_SHIFT (0U)
/*! CHPRI - Channel n Arbitration Priority
 */
#define DMA_DCHPRI3_CHPRI(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_CHPRI_SHIFT)) & DMA_DCHPRI3_CHPRI_MASK)
#define DMA_DCHPRI3_DPA_MASK (0x40U)
#define DMA_DCHPRI3_DPA_SHIFT (6U)
/*! DPA - Disable Preempt Ability.
 *  0b0..Channel n can suspend a lower priority channel.
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority.
 */
#define DMA_DCHPRI3_DPA(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_DPA_SHIFT)) & DMA_DCHPRI3_DPA_MASK)
#define DMA_DCHPRI3_ECP_MASK (0x80U)
#define DMA_DCHPRI3_ECP_SHIFT (7U)
/*! ECP - Enable Channel Preemption.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request.
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel.
 */
#define DMA_DCHPRI3_ECP(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_ECP_SHIFT)) & DMA_DCHPRI3_ECP_MASK)
/*! @} */

/*! @name DCHPRI2 - Channel n Priority Register */
/*! @{ */
#define DMA_DCHPRI2_CHPRI_MASK (0x7U)
#define DMA_DCHPRI2_CHPRI_SHIFT (0U)
/*! CHPRI - Channel n Arbitration Priority
 */
#define DMA_DCHPRI2_CHPRI(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_CHPRI_SHIFT)) & DMA_DCHPRI2_CHPRI_MASK)
#define DMA_DCHPRI2_DPA_MASK (0x40U)
#define DMA_DCHPRI2_DPA_SHIFT (6U)
/*! DPA - Disable Preempt Ability.
 *  0b0..Channel n can suspend a lower priority channel.
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority.
 */
#define DMA_DCHPRI2_DPA(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_DPA_SHIFT)) & DMA_DCHPRI2_DPA_MASK)
#define DMA_DCHPRI2_ECP_MASK (0x80U)
#define DMA_DCHPRI2_ECP_SHIFT (7U)
/*! ECP - Enable Channel Preemption.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request.
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel.
 */
#define DMA_DCHPRI2_ECP(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_ECP_SHIFT)) & DMA_DCHPRI2_ECP_MASK)
/*! @} */

/*! @name DCHPRI1 - Channel n Priority Register */
/*! @{ */
#define DMA_DCHPRI1_CHPRI_MASK (0x7U)
#define DMA_DCHPRI1_CHPRI_SHIFT (0U)
/*! CHPRI - Channel n Arbitration Priority
 */
#define DMA_DCHPRI1_CHPRI(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_CHPRI_SHIFT)) & DMA_DCHPRI1_CHPRI_MASK)
#define DMA_DCHPRI1_DPA_MASK (0x40U)
#define DMA_DCHPRI1_DPA_SHIFT (6U)
/*! DPA - Disable Preempt Ability.
 *  0b0..Channel n can suspend a lower priority channel.
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority.
 */
#define DMA_DCHPRI1_DPA(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_DPA_SHIFT)) & DMA_DCHPRI1_DPA_MASK)
#define DMA_DCHPRI1_ECP_MASK (0x80U)
#define DMA_DCHPRI1_ECP_SHIFT (7U)
/*! ECP - Enable Channel Preemption.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request.
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel.
 */
#define DMA_DCHPRI1_ECP(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_ECP_SHIFT)) & DMA_DCHPRI1_ECP_MASK)
/*! @} */

/*! @name DCHPRI0 - Channel n Priority Register */
/*! @{ */
#define DMA_DCHPRI0_CHPRI_MASK (0x7U)
#define DMA_DCHPRI0_CHPRI_SHIFT (0U)
/*! CHPRI - Channel n Arbitration Priority
 */
#define DMA_DCHPRI0_CHPRI(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_CHPRI_SHIFT)) & DMA_DCHPRI0_CHPRI_MASK)
#define DMA_DCHPRI0_DPA_MASK (0x40U)
#define DMA_DCHPRI0_DPA_SHIFT (6U)
/*! DPA - Disable Preempt Ability.
 *  0b0..Channel n can suspend a lower priority channel.
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority.
 */
#define DMA_DCHPRI0_DPA(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_DPA_SHIFT)) & DMA_DCHPRI0_DPA_MASK)
#define DMA_DCHPRI0_ECP_MASK (0x80U)
#define DMA_DCHPRI0_ECP_SHIFT (7U)
/*! ECP - Enable Channel Preemption.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request.
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel.
 */
#define DMA_DCHPRI0_ECP(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_ECP_SHIFT)) & DMA_DCHPRI0_ECP_MASK)
/*! @} */

/*! @name DCHPRI7 - Channel n Priority Register */
/*! @{ */
#define DMA_DCHPRI7_CHPRI_MASK (0x7U)
#define DMA_DCHPRI7_CHPRI_SHIFT (0U)
/*! CHPRI - Channel n Arbitration Priority
 */
#define DMA_DCHPRI7_CHPRI(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI7_CHPRI_SHIFT)) & DMA_DCHPRI7_CHPRI_MASK)
#define DMA_DCHPRI7_DPA_MASK (0x40U)
#define DMA_DCHPRI7_DPA_SHIFT (6U)
/*! DPA - Disable Preempt Ability.
 *  0b0..Channel n can suspend a lower priority channel.
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority.
 */
#define DMA_DCHPRI7_DPA(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI7_DPA_SHIFT)) & DMA_DCHPRI7_DPA_MASK)
#define DMA_DCHPRI7_ECP_MASK (0x80U)
#define DMA_DCHPRI7_ECP_SHIFT (7U)
/*! ECP - Enable Channel Preemption.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request.
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel.
 */
#define DMA_DCHPRI7_ECP(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI7_ECP_SHIFT)) & DMA_DCHPRI7_ECP_MASK)
/*! @} */

/*! @name DCHPRI6 - Channel n Priority Register */
/*! @{ */
#define DMA_DCHPRI6_CHPRI_MASK (0x7U)
#define DMA_DCHPRI6_CHPRI_SHIFT (0U)
/*! CHPRI - Channel n Arbitration Priority
 */
#define DMA_DCHPRI6_CHPRI(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI6_CHPRI_SHIFT)) & DMA_DCHPRI6_CHPRI_MASK)
#define DMA_DCHPRI6_DPA_MASK (0x40U)
#define DMA_DCHPRI6_DPA_SHIFT (6U)
/*! DPA - Disable Preempt Ability.
 *  0b0..Channel n can suspend a lower priority channel.
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority.
 */
#define DMA_DCHPRI6_DPA(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI6_DPA_SHIFT)) & DMA_DCHPRI6_DPA_MASK)
#define DMA_DCHPRI6_ECP_MASK (0x80U)
#define DMA_DCHPRI6_ECP_SHIFT (7U)
/*! ECP - Enable Channel Preemption.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request.
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel.
 */
#define DMA_DCHPRI6_ECP(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI6_ECP_SHIFT)) & DMA_DCHPRI6_ECP_MASK)
/*! @} */

/*! @name DCHPRI5 - Channel n Priority Register */
/*! @{ */
#define DMA_DCHPRI5_CHPRI_MASK (0x7U)
#define DMA_DCHPRI5_CHPRI_SHIFT (0U)
/*! CHPRI - Channel n Arbitration Priority
 */
#define DMA_DCHPRI5_CHPRI(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI5_CHPRI_SHIFT)) & DMA_DCHPRI5_CHPRI_MASK)
#define DMA_DCHPRI5_DPA_MASK (0x40U)
#define DMA_DCHPRI5_DPA_SHIFT (6U)
/*! DPA - Disable Preempt Ability.
 *  0b0..Channel n can suspend a lower priority channel.
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority.
 */
#define DMA_DCHPRI5_DPA(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI5_DPA_SHIFT)) & DMA_DCHPRI5_DPA_MASK)
#define DMA_DCHPRI5_ECP_MASK (0x80U)
#define DMA_DCHPRI5_ECP_SHIFT (7U)
/*! ECP - Enable Channel Preemption.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request.
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel.
 */
#define DMA_DCHPRI5_ECP(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI5_ECP_SHIFT)) & DMA_DCHPRI5_ECP_MASK)
/*! @} */

/*! @name DCHPRI4 - Channel n Priority Register */
/*! @{ */
#define DMA_DCHPRI4_CHPRI_MASK (0x7U)
#define DMA_DCHPRI4_CHPRI_SHIFT (0U)
/*! CHPRI - Channel n Arbitration Priority
 */
#define DMA_DCHPRI4_CHPRI(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI4_CHPRI_SHIFT)) & DMA_DCHPRI4_CHPRI_MASK)
#define DMA_DCHPRI4_DPA_MASK (0x40U)
#define DMA_DCHPRI4_DPA_SHIFT (6U)
/*! DPA - Disable Preempt Ability.
 *  0b0..Channel n can suspend a lower priority channel.
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority.
 */
#define DMA_DCHPRI4_DPA(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI4_DPA_SHIFT)) & DMA_DCHPRI4_DPA_MASK)
#define DMA_DCHPRI4_ECP_MASK (0x80U)
#define DMA_DCHPRI4_ECP_SHIFT (7U)
/*! ECP - Enable Channel Preemption.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request.
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel.
 */
#define DMA_DCHPRI4_ECP(x) (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI4_ECP_SHIFT)) & DMA_DCHPRI4_ECP_MASK)
/*! @} */

/*! @name SADDR - TCD Source Address */
/*! @{ */
#define DMA_SADDR_SADDR_MASK (0xFFFFFFFFU)
#define DMA_SADDR_SADDR_SHIFT (0U)
/*! SADDR - Source Address
 */
#define DMA_SADDR_SADDR(x) (((uint32_t)(((uint32_t)(x)) << DMA_SADDR_SADDR_SHIFT)) & DMA_SADDR_SADDR_MASK)
/*! @} */

/* The count of DMA_SADDR */
#define DMA_SADDR_COUNT (8U)

/*! @name SOFF - TCD Signed Source Address Offset */
/*! @{ */
#define DMA_SOFF_SOFF_MASK (0xFFFFU)
#define DMA_SOFF_SOFF_SHIFT (0U)
/*! SOFF - Source address signed offset
 */
#define DMA_SOFF_SOFF(x) (((uint16_t)(((uint16_t)(x)) << DMA_SOFF_SOFF_SHIFT)) & DMA_SOFF_SOFF_MASK)
/*! @} */

/* The count of DMA_SOFF */
#define DMA_SOFF_COUNT (8U)

/*! @name ATTR - TCD Transfer Attributes */
/*! @{ */
#define DMA_ATTR_DSIZE_MASK (0x7U)
#define DMA_ATTR_DSIZE_SHIFT (0U)
/*! DSIZE - Destination data transfer size
 */
#define DMA_ATTR_DSIZE(x) (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_DSIZE_SHIFT)) & DMA_ATTR_DSIZE_MASK)
#define DMA_ATTR_DMOD_MASK (0xF8U)
#define DMA_ATTR_DMOD_SHIFT (3U)
/*! DMOD - Destination Address Modulo
 */
#define DMA_ATTR_DMOD(x) (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_DMOD_SHIFT)) & DMA_ATTR_DMOD_MASK)
#define DMA_ATTR_SSIZE_MASK (0x700U)
#define DMA_ATTR_SSIZE_SHIFT (8U)
/*! SSIZE - Source data transfer size
 *  0b000..8-bit
 *  0b001..16-bit
 *  0b010..32-bit
 *  0b011..Reserved
 *  0b100..16-byte
 *  0b101..32-byte
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define DMA_ATTR_SSIZE(x) (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_SSIZE_SHIFT)) & DMA_ATTR_SSIZE_MASK)
#define DMA_ATTR_SMOD_MASK (0xF800U)
#define DMA_ATTR_SMOD_SHIFT (11U)
/*! SMOD - Source Address Modulo
 *  0b00000..Source address modulo feature is disabled
 */
#define DMA_ATTR_SMOD(x) (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_SMOD_SHIFT)) & DMA_ATTR_SMOD_MASK)
/*! @} */

/* The count of DMA_ATTR */
#define DMA_ATTR_COUNT (8U)

/*! @name NBYTES_MLNO - TCD Minor Byte Count (Minor Loop Mapping Disabled) */
/*! @{ */
#define DMA_NBYTES_MLNO_NBYTES_MASK (0xFFFFFFFFU)
#define DMA_NBYTES_MLNO_NBYTES_SHIFT (0U)
/*! NBYTES - Minor Byte Transfer Count
 */
#define DMA_NBYTES_MLNO_NBYTES(x) \
    (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLNO_NBYTES_SHIFT)) & DMA_NBYTES_MLNO_NBYTES_MASK)
/*! @} */

/* The count of DMA_NBYTES_MLNO */
#define DMA_NBYTES_MLNO_COUNT (8U)

/*! @name NBYTES_MLOFFNO - TCD Signed Minor Loop Offset (Minor Loop Mapping Enabled and Offset Disabled) */
/*! @{ */
#define DMA_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
/*! NBYTES - Minor Byte Transfer Count
 */
#define DMA_NBYTES_MLOFFNO_NBYTES(x) \
    (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_NBYTES_MLOFFNO_NBYTES_MASK)
#define DMA_NBYTES_MLOFFNO_DMLOE_MASK (0x40000000U)
#define DMA_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
/*! DMLOE - Destination Minor Loop Offset enable
 *  0b0..The minor loop offset is not applied to the DADDR
 *  0b1..The minor loop offset is applied to the DADDR
 */
#define DMA_NBYTES_MLOFFNO_DMLOE(x) \
    (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_NBYTES_MLOFFNO_DMLOE_MASK)
#define DMA_NBYTES_MLOFFNO_SMLOE_MASK (0x80000000U)
#define DMA_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
/*! SMLOE - Source Minor Loop Offset Enable
 *  0b0..The minor loop offset is not applied to the SADDR
 *  0b1..The minor loop offset is applied to the SADDR
 */
#define DMA_NBYTES_MLOFFNO_SMLOE(x) \
    (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/* The count of DMA_NBYTES_MLOFFNO */
#define DMA_NBYTES_MLOFFNO_COUNT (8U)

/*! @name NBYTES_MLOFFYES - TCD Signed Minor Loop Offset (Minor Loop Mapping and Offset Enabled) */
/*! @{ */
#define DMA_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
/*! NBYTES - Minor Byte Transfer Count
 */
#define DMA_NBYTES_MLOFFYES_NBYTES(x) \
    (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_NBYTES_MLOFFYES_NBYTES_MASK)
#define DMA_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
/*! MLOFF - If SMLOE or DMLOE is set, this field represents a sign-extended offset applied to the
 *    source or destination address to form the next-state value after the minor loop completes.
 */
#define DMA_NBYTES_MLOFFYES_MLOFF(x) \
    (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_NBYTES_MLOFFYES_MLOFF_MASK)
#define DMA_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
/*! DMLOE - Destination Minor Loop Offset enable
 *  0b0..The minor loop offset is not applied to the DADDR
 *  0b1..The minor loop offset is applied to the DADDR
 */
#define DMA_NBYTES_MLOFFYES_DMLOE(x) \
    (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_NBYTES_MLOFFYES_DMLOE_MASK)
#define DMA_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
/*! SMLOE - Source Minor Loop Offset Enable
 *  0b0..The minor loop offset is not applied to the SADDR
 *  0b1..The minor loop offset is applied to the SADDR
 */
#define DMA_NBYTES_MLOFFYES_SMLOE(x) \
    (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/* The count of DMA_NBYTES_MLOFFYES */
#define DMA_NBYTES_MLOFFYES_COUNT (8U)

/*! @name SLAST - TCD Last Source Address Adjustment */
/*! @{ */
#define DMA_SLAST_SLAST_MASK (0xFFFFFFFFU)
#define DMA_SLAST_SLAST_SHIFT (0U)
/*! SLAST - Last Source Address Adjustment
 */
#define DMA_SLAST_SLAST(x) (((uint32_t)(((uint32_t)(x)) << DMA_SLAST_SLAST_SHIFT)) & DMA_SLAST_SLAST_MASK)
/*! @} */

/* The count of DMA_SLAST */
#define DMA_SLAST_COUNT (8U)

/*! @name DADDR - TCD Destination Address */
/*! @{ */
#define DMA_DADDR_DADDR_MASK (0xFFFFFFFFU)
#define DMA_DADDR_DADDR_SHIFT (0U)
/*! DADDR - Destination Address
 */
#define DMA_DADDR_DADDR(x) (((uint32_t)(((uint32_t)(x)) << DMA_DADDR_DADDR_SHIFT)) & DMA_DADDR_DADDR_MASK)
/*! @} */

/* The count of DMA_DADDR */
#define DMA_DADDR_COUNT (8U)

/*! @name DOFF - TCD Signed Destination Address Offset */
/*! @{ */
#define DMA_DOFF_DOFF_MASK (0xFFFFU)
#define DMA_DOFF_DOFF_SHIFT (0U)
/*! DOFF - Destination Address Signed Offset
 */
#define DMA_DOFF_DOFF(x) (((uint16_t)(((uint16_t)(x)) << DMA_DOFF_DOFF_SHIFT)) & DMA_DOFF_DOFF_MASK)
/*! @} */

/* The count of DMA_DOFF */
#define DMA_DOFF_COUNT (8U)

/*! @name CITER_ELINKNO - TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled) */
/*! @{ */
#define DMA_CITER_ELINKNO_CITER_MASK (0x7FFFU)
#define DMA_CITER_ELINKNO_CITER_SHIFT (0U)
/*! CITER - Current Major Iteration Count
 */
#define DMA_CITER_ELINKNO_CITER(x) \
    (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKNO_CITER_SHIFT)) & DMA_CITER_ELINKNO_CITER_MASK)
#define DMA_CITER_ELINKNO_ELINK_MASK (0x8000U)
#define DMA_CITER_ELINKNO_ELINK_SHIFT (15U)
/*! ELINK - Enable channel-to-channel linking on minor-loop complete
 *  0b0..The channel-to-channel linking is disabled
 *  0b1..The channel-to-channel linking is enabled
 */
#define DMA_CITER_ELINKNO_ELINK(x) \
    (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKNO_ELINK_SHIFT)) & DMA_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/* The count of DMA_CITER_ELINKNO */
#define DMA_CITER_ELINKNO_COUNT (8U)

/*! @name CITER_ELINKYES - TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled) */
/*! @{ */
#define DMA_CITER_ELINKYES_CITER_MASK (0x1FFU)
#define DMA_CITER_ELINKYES_CITER_SHIFT (0U)
/*! CITER - Current Major Iteration Count
 */
#define DMA_CITER_ELINKYES_CITER(x) \
    (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKYES_CITER_SHIFT)) & DMA_CITER_ELINKYES_CITER_MASK)
#define DMA_CITER_ELINKYES_LINKCH_MASK (0xE00U)
#define DMA_CITER_ELINKYES_LINKCH_SHIFT (9U)
/*! LINKCH - Minor Loop Link Channel Number
 */
#define DMA_CITER_ELINKYES_LINKCH(x) \
    (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_CITER_ELINKYES_LINKCH_MASK)
#define DMA_CITER_ELINKYES_ELINK_MASK (0x8000U)
#define DMA_CITER_ELINKYES_ELINK_SHIFT (15U)
/*! ELINK - Enable channel-to-channel linking on minor-loop complete
 *  0b0..The channel-to-channel linking is disabled
 *  0b1..The channel-to-channel linking is enabled
 */
#define DMA_CITER_ELINKYES_ELINK(x) \
    (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKYES_ELINK_SHIFT)) & DMA_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/* The count of DMA_CITER_ELINKYES */
#define DMA_CITER_ELINKYES_COUNT (8U)

/*! @name DLAST_SGA - TCD Last Destination Address Adjustment/Scatter Gather Address */
/*! @{ */
#define DMA_DLAST_SGA_DLASTSGA_MASK (0xFFFFFFFFU)
#define DMA_DLAST_SGA_DLASTSGA_SHIFT (0U)
#define DMA_DLAST_SGA_DLASTSGA(x) \
    (((uint32_t)(((uint32_t)(x)) << DMA_DLAST_SGA_DLASTSGA_SHIFT)) & DMA_DLAST_SGA_DLASTSGA_MASK)
/*! @} */

/* The count of DMA_DLAST_SGA */
#define DMA_DLAST_SGA_COUNT (8U)

/*! @name CSR - TCD Control and Status */
/*! @{ */
#define DMA_CSR_START_MASK (0x1U)
#define DMA_CSR_START_SHIFT (0U)
/*! START - Channel Start
 *  0b0..The channel is not explicitly started.
 *  0b1..The channel is explicitly started via a software initiated service request.
 */
#define DMA_CSR_START(x) (((uint16_t)(((uint16_t)(x)) << DMA_CSR_START_SHIFT)) & DMA_CSR_START_MASK)
#define DMA_CSR_INTMAJOR_MASK (0x2U)
#define DMA_CSR_INTMAJOR_SHIFT (1U)
/*! INTMAJOR - Enable an interrupt when major iteration count completes.
 *  0b0..The end-of-major loop interrupt is disabled.
 *  0b1..The end-of-major loop interrupt is enabled.
 */
#define DMA_CSR_INTMAJOR(x) (((uint16_t)(((uint16_t)(x)) << DMA_CSR_INTMAJOR_SHIFT)) & DMA_CSR_INTMAJOR_MASK)
#define DMA_CSR_INTHALF_MASK (0x4U)
#define DMA_CSR_INTHALF_SHIFT (2U)
/*! INTHALF - Enable an interrupt when major counter is half complete.
 *  0b0..The half-point interrupt is disabled.
 *  0b1..The half-point interrupt is enabled.
 */
#define DMA_CSR_INTHALF(x) (((uint16_t)(((uint16_t)(x)) << DMA_CSR_INTHALF_SHIFT)) & DMA_CSR_INTHALF_MASK)
#define DMA_CSR_DREQ_MASK (0x8U)
#define DMA_CSR_DREQ_SHIFT (3U)
/*! DREQ - Disable Request
 *  0b0..The channel's ERQ bit is not affected.
 *  0b1..The channel's ERQ bit is cleared when the major loop is complete.
 */
#define DMA_CSR_DREQ(x) (((uint16_t)(((uint16_t)(x)) << DMA_CSR_DREQ_SHIFT)) & DMA_CSR_DREQ_MASK)
#define DMA_CSR_ESG_MASK (0x10U)
#define DMA_CSR_ESG_SHIFT (4U)
/*! ESG - Enable Scatter/Gather Processing
 *  0b0..The current channel's TCD is normal format.
 *  0b1..The current channel's TCD specifies a scatter gather format. The DLASTSGA field provides a memory pointer
 *       to the next TCD to be loaded into this channel after the major loop completes its execution.
 */
#define DMA_CSR_ESG(x) (((uint16_t)(((uint16_t)(x)) << DMA_CSR_ESG_SHIFT)) & DMA_CSR_ESG_MASK)
#define DMA_CSR_MAJORELINK_MASK (0x20U)
#define DMA_CSR_MAJORELINK_SHIFT (5U)
/*! MAJORELINK - Enable channel-to-channel linking on major loop complete
 *  0b0..The channel-to-channel linking is disabled.
 *  0b1..The channel-to-channel linking is enabled.
 */
#define DMA_CSR_MAJORELINK(x) (((uint16_t)(((uint16_t)(x)) << DMA_CSR_MAJORELINK_SHIFT)) & DMA_CSR_MAJORELINK_MASK)
#define DMA_CSR_ACTIVE_MASK (0x40U)
#define DMA_CSR_ACTIVE_SHIFT (6U)
/*! ACTIVE - Channel Active
 */
#define DMA_CSR_ACTIVE(x) (((uint16_t)(((uint16_t)(x)) << DMA_CSR_ACTIVE_SHIFT)) & DMA_CSR_ACTIVE_MASK)
#define DMA_CSR_DONE_MASK (0x80U)
#define DMA_CSR_DONE_SHIFT (7U)
/*! DONE - Channel Done
 */
#define DMA_CSR_DONE(x) (((uint16_t)(((uint16_t)(x)) << DMA_CSR_DONE_SHIFT)) & DMA_CSR_DONE_MASK)
#define DMA_CSR_MAJORLINKCH_MASK (0x700U)
#define DMA_CSR_MAJORLINKCH_SHIFT (8U)
/*! MAJORLINKCH - Major Loop Link Channel Number
 */
#define DMA_CSR_MAJORLINKCH(x) (((uint16_t)(((uint16_t)(x)) << DMA_CSR_MAJORLINKCH_SHIFT)) & DMA_CSR_MAJORLINKCH_MASK)
#define DMA_CSR_BWC_MASK (0xC000U)
#define DMA_CSR_BWC_SHIFT (14U)
/*! BWC - Bandwidth Control
 *  0b00..No eDMA engine stalls.
 *  0b01..Reserved
 *  0b10..eDMA engine stalls for 4 cycles after each R/W.
 *  0b11..eDMA engine stalls for 8 cycles after each R/W.
 */
#define DMA_CSR_BWC(x) (((uint16_t)(((uint16_t)(x)) << DMA_CSR_BWC_SHIFT)) & DMA_CSR_BWC_MASK)
/*! @} */

/* The count of DMA_CSR */
#define DMA_CSR_COUNT (8U)

/*! @name BITER_ELINKNO - TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled) */
/*! @{ */
#define DMA_BITER_ELINKNO_BITER_MASK (0x7FFFU)
#define DMA_BITER_ELINKNO_BITER_SHIFT (0U)
/*! BITER - Starting Major Iteration Count
 */
#define DMA_BITER_ELINKNO_BITER(x) \
    (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKNO_BITER_SHIFT)) & DMA_BITER_ELINKNO_BITER_MASK)
#define DMA_BITER_ELINKNO_ELINK_MASK (0x8000U)
#define DMA_BITER_ELINKNO_ELINK_SHIFT (15U)
/*! ELINK - Enables channel-to-channel linking on minor loop complete
 *  0b0..The channel-to-channel linking is disabled
 *  0b1..The channel-to-channel linking is enabled
 */
#define DMA_BITER_ELINKNO_ELINK(x) \
    (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKNO_ELINK_SHIFT)) & DMA_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/* The count of DMA_BITER_ELINKNO */
#define DMA_BITER_ELINKNO_COUNT (8U)

/*! @name BITER_ELINKYES - TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled) */
/*! @{ */
#define DMA_BITER_ELINKYES_BITER_MASK (0x1FFU)
#define DMA_BITER_ELINKYES_BITER_SHIFT (0U)
/*! BITER - Starting major iteration count
 */
#define DMA_BITER_ELINKYES_BITER(x) \
    (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKYES_BITER_SHIFT)) & DMA_BITER_ELINKYES_BITER_MASK)
#define DMA_BITER_ELINKYES_LINKCH_MASK (0xE00U)
#define DMA_BITER_ELINKYES_LINKCH_SHIFT (9U)
/*! LINKCH - Link Channel Number
 */
#define DMA_BITER_ELINKYES_LINKCH(x) \
    (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_BITER_ELINKYES_LINKCH_MASK)
#define DMA_BITER_ELINKYES_ELINK_MASK (0x8000U)
#define DMA_BITER_ELINKYES_ELINK_SHIFT (15U)
/*! ELINK - Enables channel-to-channel linking on minor loop complete
 *  0b0..The channel-to-channel linking is disabled
 *  0b1..The channel-to-channel linking is enabled
 */
#define DMA_BITER_ELINKYES_ELINK(x) \
    (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKYES_ELINK_SHIFT)) & DMA_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/* The count of DMA_BITER_ELINKYES */
#define DMA_BITER_ELINKYES_COUNT (8U)

/*!
 * @}
 */ /* end of group DMA_Register_Masks */

/* DMA - Peripheral instance base addresses */
/** Peripheral DMA0 base address */
#define DMA0_BASE (0x40008000u)
/** Peripheral DMA0 base pointer */
#define DMA0 ((DMA_Type *)DMA0_BASE)
/** Array initializer of DMA peripheral base addresses */
#define DMA_BASE_ADDRS \
    {                  \
        DMA0_BASE      \
    }
/** Array initializer of DMA peripheral base pointers */
#define DMA_BASE_PTRS \
    {                 \
        DMA0          \
    }
/** Interrupt vectors for the DMA peripheral type */
#define DMA_CHN_IRQS                                                                                          \
    {                                                                                                         \
        {                                                                                                     \
            DMA0_04_IRQn, DMA0_15_IRQn, DMA0_26_IRQn, DMA0_37_IRQn, DMA0_04_IRQn, DMA0_15_IRQn, DMA0_26_IRQn, \
                DMA0_37_IRQn                                                                                  \
        }                                                                                                     \
    }
#define DMA_ERROR_IRQS       \
    {                        \
        CTI0_DMA0_Error_IRQn \
    }

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
typedef struct
{
    __IO uint8_t CHCFG[8]; /**< Channel Configuration register, array offset: 0x0, array step: 0x1 */
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
#define DMAMUX_CHCFG_SOURCE_MASK (0x3FU)
#define DMAMUX_CHCFG_SOURCE_SHIFT (0U)
/*! SOURCE - DMA Channel Source (Slot)
 */
#define DMAMUX_CHCFG_SOURCE(x) (((uint8_t)(((uint8_t)(x)) << DMAMUX_CHCFG_SOURCE_SHIFT)) & DMAMUX_CHCFG_SOURCE_MASK)
#define DMAMUX_CHCFG_TRIG_MASK (0x40U)
#define DMAMUX_CHCFG_TRIG_SHIFT (6U)
/*! TRIG - DMA Channel Trigger Enable
 *  0b0..Triggering is disabled. If triggering is disabled and ENBL is set, the DMA Channel will simply route the
 *       specified source to the DMA channel. (Normal mode)
 *  0b1..Triggering is enabled. If triggering is enabled and ENBL is set, the DMAMUX is in Periodic Trigger mode.
 */
#define DMAMUX_CHCFG_TRIG(x) (((uint8_t)(((uint8_t)(x)) << DMAMUX_CHCFG_TRIG_SHIFT)) & DMAMUX_CHCFG_TRIG_MASK)
#define DMAMUX_CHCFG_ENBL_MASK (0x80U)
#define DMAMUX_CHCFG_ENBL_SHIFT (7U)
/*! ENBL - DMA Channel Enable
 *  0b0..DMA channel is disabled. This mode is primarily used during configuration of the DMAMux. The DMA has
 *       separate channel enables/disables, which should be used to disable or reconfigure a DMA channel.
 *  0b1..DMA channel is enabled
 */
#define DMAMUX_CHCFG_ENBL(x) (((uint8_t)(((uint8_t)(x)) << DMAMUX_CHCFG_ENBL_SHIFT)) & DMAMUX_CHCFG_ENBL_MASK)
/*! @} */

/* The count of DMAMUX_CHCFG */
#define DMAMUX_CHCFG_COUNT (8U)

/*!
 * @}
 */ /* end of group DMAMUX_Register_Masks */

/* DMAMUX - Peripheral instance base addresses */
/** Peripheral DMAMUX0 base address */
#define DMAMUX0_BASE (0x40021000u)
/** Peripheral DMAMUX0 base pointer */
#define DMAMUX0 ((DMAMUX_Type *)DMAMUX0_BASE)
/** Array initializer of DMAMUX peripheral base addresses */
#define DMAMUX_BASE_ADDRS \
    {                     \
        DMAMUX0_BASE      \
    }
/** Array initializer of DMAMUX peripheral base pointers */
#define DMAMUX_BASE_PTRS \
    {                    \
        DMAMUX0          \
    }

/*!
 * @}
 */ /* end of group DMAMUX_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- EMVSIM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EMVSIM_Peripheral_Access_Layer EMVSIM Peripheral Access Layer
 * @{
 */

/** EMVSIM - Register Layout Typedef */
typedef struct
{
    __I uint32_t VER_ID;      /**< Version ID Register, offset: 0x0 */
    __I uint32_t PARAM;       /**< Parameter Register, offset: 0x4 */
    __IO uint32_t CLKCFG;     /**< Clock Configuration Register, offset: 0x8 */
    __IO uint32_t DIVISOR;    /**< Baud Rate Divisor Register, offset: 0xC */
    __IO uint32_t CTRL;       /**< Control Register, offset: 0x10 */
    __IO uint32_t INT_MASK;   /**< Interrupt Mask Register, offset: 0x14 */
    __IO uint32_t RX_THD;     /**< Receiver Threshold Register, offset: 0x18 */
    __IO uint32_t TX_THD;     /**< Transmitter Threshold Register, offset: 0x1C */
    __IO uint32_t RX_STATUS;  /**< Receive Status Register, offset: 0x20 */
    __IO uint32_t TX_STATUS;  /**< Transmitter Status Register, offset: 0x24 */
    __IO uint32_t PCSR;       /**< Port Control and Status Register, offset: 0x28 */
    __I uint32_t RX_BUF;      /**< Receive Data Read Buffer, offset: 0x2C */
    __O uint32_t TX_BUF;      /**< Transmit Data Buffer, offset: 0x30 */
    __IO uint32_t TX_GETU;    /**< Transmitter Guard ETU Value Register, offset: 0x34 */
    __IO uint32_t CWT_VAL;    /**< Character Wait Time Value Register, offset: 0x38 */
    __IO uint32_t BWT_VAL;    /**< Block Wait Time Value Register, offset: 0x3C */
    __IO uint32_t BGT_VAL;    /**< Block Guard Time Value Register, offset: 0x40 */
    __IO uint32_t GPCNT0_VAL; /**< General Purpose Counter 0 Timeout Value Register, offset: 0x44 */
    __IO uint32_t GPCNT1_VAL; /**< General Purpose Counter 1 Timeout Value, offset: 0x48 */
} EMVSIM_Type;

/* ----------------------------------------------------------------------------
   -- EMVSIM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EMVSIM_Register_Masks EMVSIM Register Masks
 * @{
 */

/*! @name VER_ID - Version ID Register */
/*! @{ */
#define EMVSIM_VER_ID_VER_MASK (0xFFFFFFFFU)
#define EMVSIM_VER_ID_VER_SHIFT (0U)
/*! VER - Version ID of the module
 */
#define EMVSIM_VER_ID_VER(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_VER_ID_VER_SHIFT)) & EMVSIM_VER_ID_VER_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */
#define EMVSIM_PARAM_RX_FIFO_DEPTH_MASK (0xFFU)
#define EMVSIM_PARAM_RX_FIFO_DEPTH_SHIFT (0U)
/*! RX_FIFO_DEPTH - Receive FIFO Depth
 */
#define EMVSIM_PARAM_RX_FIFO_DEPTH(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_PARAM_RX_FIFO_DEPTH_SHIFT)) & EMVSIM_PARAM_RX_FIFO_DEPTH_MASK)
#define EMVSIM_PARAM_TX_FIFO_DEPTH_MASK (0xFF00U)
#define EMVSIM_PARAM_TX_FIFO_DEPTH_SHIFT (8U)
/*! TX_FIFO_DEPTH - Transmit FIFO Depth
 */
#define EMVSIM_PARAM_TX_FIFO_DEPTH(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_PARAM_TX_FIFO_DEPTH_SHIFT)) & EMVSIM_PARAM_TX_FIFO_DEPTH_MASK)
/*! @} */

/*! @name CLKCFG - Clock Configuration Register */
/*! @{ */
#define EMVSIM_CLKCFG_CLK_PRSC_MASK (0xFFU)
#define EMVSIM_CLKCFG_CLK_PRSC_SHIFT (0U)
/*! CLK_PRSC - Clock Prescaler Value
 *  0b00000010..Divide by 2
 */
#define EMVSIM_CLKCFG_CLK_PRSC(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CLKCFG_CLK_PRSC_SHIFT)) & EMVSIM_CLKCFG_CLK_PRSC_MASK)
#define EMVSIM_CLKCFG_GPCNT1_CLK_SEL_MASK (0x300U)
#define EMVSIM_CLKCFG_GPCNT1_CLK_SEL_SHIFT (8U)
/*! GPCNT1_CLK_SEL - General Purpose Counter 1 Clock Select
 *  0b00..Disabled / Reset (default)
 *  0b01..Card Clock
 *  0b10..Receive Clock
 *  0b11..ETU Clock (transmit clock)
 */
#define EMVSIM_CLKCFG_GPCNT1_CLK_SEL(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CLKCFG_GPCNT1_CLK_SEL_SHIFT)) & EMVSIM_CLKCFG_GPCNT1_CLK_SEL_MASK)
#define EMVSIM_CLKCFG_GPCNT0_CLK_SEL_MASK (0xC00U)
#define EMVSIM_CLKCFG_GPCNT0_CLK_SEL_SHIFT (10U)
/*! GPCNT0_CLK_SEL - General Purpose Counter 0 Clock Select
 *  0b00..Disabled / Reset (default)
 *  0b01..Card Clock
 *  0b10..Receive Clock
 *  0b11..ETU Clock (transmit clock)
 */
#define EMVSIM_CLKCFG_GPCNT0_CLK_SEL(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CLKCFG_GPCNT0_CLK_SEL_SHIFT)) & EMVSIM_CLKCFG_GPCNT0_CLK_SEL_MASK)
/*! @} */

/*! @name DIVISOR - Baud Rate Divisor Register */
/*! @{ */
#define EMVSIM_DIVISOR_DIVISOR_VALUE_MASK (0x1FFU)
#define EMVSIM_DIVISOR_DIVISOR_VALUE_SHIFT (0U)
/*! DIVISOR_VALUE - Divisor (F/D) Value
 *  0b101110100..Divisor value for F = 372 and D = 1 (default)
 */
#define EMVSIM_DIVISOR_DIVISOR_VALUE(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_DIVISOR_DIVISOR_VALUE_SHIFT)) & EMVSIM_DIVISOR_DIVISOR_VALUE_MASK)
/*! @} */

/*! @name CTRL - Control Register */
/*! @{ */
#define EMVSIM_CTRL_IC_MASK (0x1U)
#define EMVSIM_CTRL_IC_SHIFT (0U)
/*! IC - Inverse Convention
 *  0b0..Direction convention transfers enabled (default)
 *  0b1..Inverse convention transfers enabled
 */
#define EMVSIM_CTRL_IC(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_IC_SHIFT)) & EMVSIM_CTRL_IC_MASK)
#define EMVSIM_CTRL_ICM_MASK (0x2U)
#define EMVSIM_CTRL_ICM_SHIFT (1U)
/*! ICM - Initial Character Mode
 *  0b0..Initial Character Mode disabled
 *  0b1..Initial Character Mode enabled (default)
 */
#define EMVSIM_CTRL_ICM(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_ICM_SHIFT)) & EMVSIM_CTRL_ICM_MASK)
#define EMVSIM_CTRL_ANACK_MASK (0x4U)
#define EMVSIM_CTRL_ANACK_SHIFT (2U)
/*! ANACK - Auto NACK Enable
 *  0b0..NACK generation on errors disabled
 *  0b1..NACK generation on errors enabled (default)
 */
#define EMVSIM_CTRL_ANACK(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_ANACK_SHIFT)) & EMVSIM_CTRL_ANACK_MASK)
#define EMVSIM_CTRL_ONACK_MASK (0x8U)
#define EMVSIM_CTRL_ONACK_SHIFT (3U)
/*! ONACK - Overrun NACK Enable
 *  0b0..NACK generation on overrun is disabled (default)
 *  0b1..NACK generation on overrun is enabled
 */
#define EMVSIM_CTRL_ONACK(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_ONACK_SHIFT)) & EMVSIM_CTRL_ONACK_MASK)
#define EMVSIM_CTRL_FLSH_RX_MASK (0x100U)
#define EMVSIM_CTRL_FLSH_RX_SHIFT (8U)
/*! FLSH_RX - Flush Receiver Bit
 *  0b0..EMV SIM Receiver normal operation (default)
 *  0b1..EMV SIM Receiver held in Reset
 */
#define EMVSIM_CTRL_FLSH_RX(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_FLSH_RX_SHIFT)) & EMVSIM_CTRL_FLSH_RX_MASK)
#define EMVSIM_CTRL_FLSH_TX_MASK (0x200U)
#define EMVSIM_CTRL_FLSH_TX_SHIFT (9U)
/*! FLSH_TX - Flush Transmitter Bit
 *  0b0..EMV SIM Transmitter normal operation (default)
 *  0b1..EMV SIM Transmitter held in Reset
 */
#define EMVSIM_CTRL_FLSH_TX(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_FLSH_TX_SHIFT)) & EMVSIM_CTRL_FLSH_TX_MASK)
#define EMVSIM_CTRL_SW_RST_MASK (0x400U)
#define EMVSIM_CTRL_SW_RST_SHIFT (10U)
/*! SW_RST - Software Reset Bit
 *  0b0..EMV SIM Normal operation (default)
 *  0b1..EMV SIM held in Reset
 */
#define EMVSIM_CTRL_SW_RST(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_SW_RST_SHIFT)) & EMVSIM_CTRL_SW_RST_MASK)
#define EMVSIM_CTRL_KILL_CLOCKS_MASK (0x800U)
#define EMVSIM_CTRL_KILL_CLOCKS_SHIFT (11U)
/*! KILL_CLOCKS - Kill all internal clocks
 *  0b0..EMV SIM input clock enabled (default)
 *  0b1..EMV SIM input clock is disabled
 */
#define EMVSIM_CTRL_KILL_CLOCKS(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_KILL_CLOCKS_SHIFT)) & EMVSIM_CTRL_KILL_CLOCKS_MASK)
#define EMVSIM_CTRL_DOZE_EN_MASK (0x1000U)
#define EMVSIM_CTRL_DOZE_EN_SHIFT (12U)
/*! DOZE_EN - Doze Enable
 *  0b0..DOZE instruction will gate all internal EMV SIM clocks as well as the Smart Card clock when the transmit FIFO
 * is empty (default) 0b1..DOZE instruction has no effect on EMV SIM module
 */
#define EMVSIM_CTRL_DOZE_EN(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_DOZE_EN_SHIFT)) & EMVSIM_CTRL_DOZE_EN_MASK)
#define EMVSIM_CTRL_STOP_EN_MASK (0x2000U)
#define EMVSIM_CTRL_STOP_EN_SHIFT (13U)
/*! STOP_EN - STOP Enable
 *  0b0..STOP instruction shuts down all EMV SIM clocks (default)
 *  0b1..STOP instruction shuts down all clocks except for the Smart Card Clock (SCK) (clock provided to Smart Card)
 */
#define EMVSIM_CTRL_STOP_EN(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_STOP_EN_SHIFT)) & EMVSIM_CTRL_STOP_EN_MASK)
#define EMVSIM_CTRL_RCV_EN_MASK (0x10000U)
#define EMVSIM_CTRL_RCV_EN_SHIFT (16U)
/*! RCV_EN - Receiver Enable
 *  0b0..EMV SIM Receiver disabled (default)
 *  0b1..EMV SIM Receiver enabled
 */
#define EMVSIM_CTRL_RCV_EN(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_RCV_EN_SHIFT)) & EMVSIM_CTRL_RCV_EN_MASK)
#define EMVSIM_CTRL_XMT_EN_MASK (0x20000U)
#define EMVSIM_CTRL_XMT_EN_SHIFT (17U)
/*! XMT_EN - Transmitter Enable
 *  0b0..EMV SIM Transmitter disabled (default)
 *  0b1..EMV SIM Transmitter enabled
 */
#define EMVSIM_CTRL_XMT_EN(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_XMT_EN_SHIFT)) & EMVSIM_CTRL_XMT_EN_MASK)
#define EMVSIM_CTRL_RCVR_11_MASK (0x40000U)
#define EMVSIM_CTRL_RCVR_11_SHIFT (18U)
/*! RCVR_11 - Receiver 11 ETU Mode Enable
 *  0b0..Receiver configured for 12 ETU operation mode (default)
 *  0b1..Receiver configured for 11 ETU operation mode
 */
#define EMVSIM_CTRL_RCVR_11(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_RCVR_11_SHIFT)) & EMVSIM_CTRL_RCVR_11_MASK)
#define EMVSIM_CTRL_RX_DMA_EN_MASK (0x80000U)
#define EMVSIM_CTRL_RX_DMA_EN_SHIFT (19U)
/*! RX_DMA_EN - Receive DMA Enable
 *  0b0..No DMA Read Request asserted for Receiver (default)
 *  0b1..DMA Read Request asserted for Receiver
 */
#define EMVSIM_CTRL_RX_DMA_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_RX_DMA_EN_SHIFT)) & EMVSIM_CTRL_RX_DMA_EN_MASK)
#define EMVSIM_CTRL_TX_DMA_EN_MASK (0x100000U)
#define EMVSIM_CTRL_TX_DMA_EN_SHIFT (20U)
/*! TX_DMA_EN - Transmit DMA Enable
 *  0b0..No DMA Write Request asserted for Transmitter (default)
 *  0b1..DMA Write Request asserted for Transmitter
 */
#define EMVSIM_CTRL_TX_DMA_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_TX_DMA_EN_SHIFT)) & EMVSIM_CTRL_TX_DMA_EN_MASK)
#define EMVSIM_CTRL_INV_CRC_VAL_MASK (0x1000000U)
#define EMVSIM_CTRL_INV_CRC_VAL_SHIFT (24U)
/*! INV_CRC_VAL - Invert bits in the CRC Output Value
 *  0b0..Bits in CRC Output value will not be inverted.
 *  0b1..Bits in CRC Output value will be inverted. (default)
 */
#define EMVSIM_CTRL_INV_CRC_VAL(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_INV_CRC_VAL_SHIFT)) & EMVSIM_CTRL_INV_CRC_VAL_MASK)
#define EMVSIM_CTRL_CRC_OUT_FLIP_MASK (0x2000000U)
#define EMVSIM_CTRL_CRC_OUT_FLIP_SHIFT (25U)
/*! CRC_OUT_FLIP - CRC Output Value Bit Reversal or Flip
 *  0b0..Bits within the CRC output bytes will not be reversed i.e. 15:0 will remain 15:0 (default)
 *  0b1..Bits within the CRC output bytes will be reversed i.e. 15:0 will become {8:15,0:7}
 */
#define EMVSIM_CTRL_CRC_OUT_FLIP(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_CRC_OUT_FLIP_SHIFT)) & EMVSIM_CTRL_CRC_OUT_FLIP_MASK)
#define EMVSIM_CTRL_CRC_IN_FLIP_MASK (0x4000000U)
#define EMVSIM_CTRL_CRC_IN_FLIP_SHIFT (26U)
/*! CRC_IN_FLIP - CRC Input Byte's Bit Reversal or Flip Control
 *  0b0..Bits in the input byte will not be reversed (i.e. 7:0 will remain 7:0) before the CRC calculation (default)
 *  0b1..Bits in the input byte will be reversed (i.e. 7:0 will become 0:7) before CRC calculation
 */
#define EMVSIM_CTRL_CRC_IN_FLIP(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_CRC_IN_FLIP_SHIFT)) & EMVSIM_CTRL_CRC_IN_FLIP_MASK)
#define EMVSIM_CTRL_CWT_EN_MASK (0x8000000U)
#define EMVSIM_CTRL_CWT_EN_SHIFT (27U)
/*! CWT_EN - Character Wait Time Counter Enable
 *  0b0..Character Wait time Counter is disabled (default)
 *  0b1..Character Wait time counter is enabled
 */
#define EMVSIM_CTRL_CWT_EN(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_CWT_EN_SHIFT)) & EMVSIM_CTRL_CWT_EN_MASK)
#define EMVSIM_CTRL_LRC_EN_MASK (0x10000000U)
#define EMVSIM_CTRL_LRC_EN_SHIFT (28U)
/*! LRC_EN - LRC Enable
 *  0b0..8-bit Linear Redundancy Checking disabled (default)
 *  0b1..8-bit Linear Redundancy Checking enabled
 */
#define EMVSIM_CTRL_LRC_EN(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_LRC_EN_SHIFT)) & EMVSIM_CTRL_LRC_EN_MASK)
#define EMVSIM_CTRL_CRC_EN_MASK (0x20000000U)
#define EMVSIM_CTRL_CRC_EN_SHIFT (29U)
/*! CRC_EN - CRC Enable
 *  0b0..16-bit Cyclic Redundancy Checking disabled (default)
 *  0b1..16-bit Cyclic Redundancy Checking enabled
 */
#define EMVSIM_CTRL_CRC_EN(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_CRC_EN_SHIFT)) & EMVSIM_CTRL_CRC_EN_MASK)
#define EMVSIM_CTRL_XMT_CRC_LRC_MASK (0x40000000U)
#define EMVSIM_CTRL_XMT_CRC_LRC_SHIFT (30U)
/*! XMT_CRC_LRC - Transmit CRC or LRC Enable
 *  0b0..No CRC or LRC value is transmitted (default)
 *  0b1..Transmit LRC or CRC info when FIFO empties (whichever is enabled)
 */
#define EMVSIM_CTRL_XMT_CRC_LRC(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_XMT_CRC_LRC_SHIFT)) & EMVSIM_CTRL_XMT_CRC_LRC_MASK)
#define EMVSIM_CTRL_BWT_EN_MASK (0x80000000U)
#define EMVSIM_CTRL_BWT_EN_SHIFT (31U)
/*! BWT_EN - Block Wait Time Counter Enable
 *  0b0..Disable BWT, BGT Counters (default)
 *  0b1..Enable BWT, BGT Counters
 */
#define EMVSIM_CTRL_BWT_EN(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CTRL_BWT_EN_SHIFT)) & EMVSIM_CTRL_BWT_EN_MASK)
/*! @} */

/*! @name INT_MASK - Interrupt Mask Register */
/*! @{ */
#define EMVSIM_INT_MASK_RDT_IM_MASK (0x1U)
#define EMVSIM_INT_MASK_RDT_IM_SHIFT (0U)
/*! RDT_IM - Receive Data Threshold Interrupt Mask
 *  0b0..RDTF interrupt enabled
 *  0b1..RDTF interrupt masked (default)
 */
#define EMVSIM_INT_MASK_RDT_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_RDT_IM_SHIFT)) & EMVSIM_INT_MASK_RDT_IM_MASK)
#define EMVSIM_INT_MASK_TC_IM_MASK (0x2U)
#define EMVSIM_INT_MASK_TC_IM_SHIFT (1U)
/*! TC_IM - Transmit Complete Interrupt Mask
 *  0b0..TCF interrupt enabled
 *  0b1..TCF interrupt masked (default)
 */
#define EMVSIM_INT_MASK_TC_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_TC_IM_SHIFT)) & EMVSIM_INT_MASK_TC_IM_MASK)
#define EMVSIM_INT_MASK_RFO_IM_MASK (0x4U)
#define EMVSIM_INT_MASK_RFO_IM_SHIFT (2U)
/*! RFO_IM - Receive FIFO Overflow Interrupt Mask
 *  0b0..RFO interrupt enabled
 *  0b1..RFO interrupt masked (default)
 */
#define EMVSIM_INT_MASK_RFO_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_RFO_IM_SHIFT)) & EMVSIM_INT_MASK_RFO_IM_MASK)
#define EMVSIM_INT_MASK_ETC_IM_MASK (0x8U)
#define EMVSIM_INT_MASK_ETC_IM_SHIFT (3U)
/*! ETC_IM - Early Transmit Complete Interrupt Mask
 *  0b0..ETC interrupt enabled
 *  0b1..ETC interrupt masked (default)
 */
#define EMVSIM_INT_MASK_ETC_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_ETC_IM_SHIFT)) & EMVSIM_INT_MASK_ETC_IM_MASK)
#define EMVSIM_INT_MASK_TFE_IM_MASK (0x10U)
#define EMVSIM_INT_MASK_TFE_IM_SHIFT (4U)
/*! TFE_IM - Transmit FIFO Empty Interrupt Mask
 *  0b0..TFE interrupt enabled
 *  0b1..TFE interrupt masked (default)
 */
#define EMVSIM_INT_MASK_TFE_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_TFE_IM_SHIFT)) & EMVSIM_INT_MASK_TFE_IM_MASK)
#define EMVSIM_INT_MASK_TNACK_IM_MASK (0x20U)
#define EMVSIM_INT_MASK_TNACK_IM_SHIFT (5U)
/*! TNACK_IM - Transmit NACK Threshold Interrupt Mask
 *  0b0..TNTE interrupt enabled
 *  0b1..TNTE interrupt masked (default)
 */
#define EMVSIM_INT_MASK_TNACK_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_TNACK_IM_SHIFT)) & EMVSIM_INT_MASK_TNACK_IM_MASK)
#define EMVSIM_INT_MASK_TFF_IM_MASK (0x40U)
#define EMVSIM_INT_MASK_TFF_IM_SHIFT (6U)
/*! TFF_IM - Transmit FIFO Full Interrupt Mask
 *  0b0..TFF interrupt enabled
 *  0b1..TFF interrupt masked (default)
 */
#define EMVSIM_INT_MASK_TFF_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_TFF_IM_SHIFT)) & EMVSIM_INT_MASK_TFF_IM_MASK)
#define EMVSIM_INT_MASK_TDT_IM_MASK (0x80U)
#define EMVSIM_INT_MASK_TDT_IM_SHIFT (7U)
/*! TDT_IM - Transmit Data Threshold Interrupt Mask
 *  0b0..TDTF interrupt enabled
 *  0b1..TDTF interrupt masked (default)
 */
#define EMVSIM_INT_MASK_TDT_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_TDT_IM_SHIFT)) & EMVSIM_INT_MASK_TDT_IM_MASK)
#define EMVSIM_INT_MASK_GPCNT0_IM_MASK (0x100U)
#define EMVSIM_INT_MASK_GPCNT0_IM_SHIFT (8U)
/*! GPCNT0_IM - General Purpose Timer 0 Timeout Interrupt Mask
 *  0b0..GPCNT0_TO interrupt enabled
 *  0b1..GPCNT0_TO interrupt masked (default)
 */
#define EMVSIM_INT_MASK_GPCNT0_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_GPCNT0_IM_SHIFT)) & EMVSIM_INT_MASK_GPCNT0_IM_MASK)
#define EMVSIM_INT_MASK_CWT_ERR_IM_MASK (0x200U)
#define EMVSIM_INT_MASK_CWT_ERR_IM_SHIFT (9U)
/*! CWT_ERR_IM - Character Wait Time Error Interrupt Mask
 *  0b0..CWT_ERR interrupt enabled
 *  0b1..CWT_ERR interrupt masked (default)
 */
#define EMVSIM_INT_MASK_CWT_ERR_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_CWT_ERR_IM_SHIFT)) & EMVSIM_INT_MASK_CWT_ERR_IM_MASK)
#define EMVSIM_INT_MASK_RNACK_IM_MASK (0x400U)
#define EMVSIM_INT_MASK_RNACK_IM_SHIFT (10U)
/*! RNACK_IM - Receiver NACK Threshold Interrupt Mask
 *  0b0..RTE interrupt enabled
 *  0b1..RTE interrupt masked (default)
 */
#define EMVSIM_INT_MASK_RNACK_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_RNACK_IM_SHIFT)) & EMVSIM_INT_MASK_RNACK_IM_MASK)
#define EMVSIM_INT_MASK_BWT_ERR_IM_MASK (0x800U)
#define EMVSIM_INT_MASK_BWT_ERR_IM_SHIFT (11U)
/*! BWT_ERR_IM - Block Wait Time Error Interrupt Mask
 *  0b0..BWT_ERR interrupt enabled
 *  0b1..BWT_ERR interrupt masked (default)
 */
#define EMVSIM_INT_MASK_BWT_ERR_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_BWT_ERR_IM_SHIFT)) & EMVSIM_INT_MASK_BWT_ERR_IM_MASK)
#define EMVSIM_INT_MASK_BGT_ERR_IM_MASK (0x1000U)
#define EMVSIM_INT_MASK_BGT_ERR_IM_SHIFT (12U)
/*! BGT_ERR_IM - Block Guard Time Error Interrupt
 *  0b0..BGT_ERR interrupt enabled
 *  0b1..BGT_ERR interrupt masked (default)
 */
#define EMVSIM_INT_MASK_BGT_ERR_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_BGT_ERR_IM_SHIFT)) & EMVSIM_INT_MASK_BGT_ERR_IM_MASK)
#define EMVSIM_INT_MASK_GPCNT1_IM_MASK (0x2000U)
#define EMVSIM_INT_MASK_GPCNT1_IM_SHIFT (13U)
/*! GPCNT1_IM - General Purpose Counter 1 Timeout Interrupt Mask
 *  0b0..GPCNT1_TO interrupt enabled
 *  0b1..GPCNT1_TO interrupt masked (default)
 */
#define EMVSIM_INT_MASK_GPCNT1_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_GPCNT1_IM_SHIFT)) & EMVSIM_INT_MASK_GPCNT1_IM_MASK)
#define EMVSIM_INT_MASK_RX_DATA_IM_MASK (0x4000U)
#define EMVSIM_INT_MASK_RX_DATA_IM_SHIFT (14U)
/*! RX_DATA_IM - Receive Data Interrupt Mask
 *  0b0..RX_DATA interrupt enabled
 *  0b1..RX_DATA interrupt masked (default)
 */
#define EMVSIM_INT_MASK_RX_DATA_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_RX_DATA_IM_SHIFT)) & EMVSIM_INT_MASK_RX_DATA_IM_MASK)
#define EMVSIM_INT_MASK_PEF_IM_MASK (0x8000U)
#define EMVSIM_INT_MASK_PEF_IM_SHIFT (15U)
/*! PEF_IM - Parity Error Interrupt Mask
 *  0b0..PEF interrupt enabled
 *  0b1..PEF interrupt masked (default)
 */
#define EMVSIM_INT_MASK_PEF_IM(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_INT_MASK_PEF_IM_SHIFT)) & EMVSIM_INT_MASK_PEF_IM_MASK)
/*! @} */

/*! @name RX_THD - Receiver Threshold Register */
/*! @{ */
#define EMVSIM_RX_THD_RDT_MASK (0xFU)
#define EMVSIM_RX_THD_RDT_SHIFT (0U)
/*! RDT - Receiver Data Threshold Value
 */
#define EMVSIM_RX_THD_RDT(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_THD_RDT_SHIFT)) & EMVSIM_RX_THD_RDT_MASK)
#define EMVSIM_RX_THD_RNCK_THD_MASK (0xF00U)
#define EMVSIM_RX_THD_RNCK_THD_SHIFT (8U)
/*! RNCK_THD - Receiver NACK Threshold Value
 *  0b0000..Zero Threshold. RTE will not be set
 */
#define EMVSIM_RX_THD_RNCK_THD(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_THD_RNCK_THD_SHIFT)) & EMVSIM_RX_THD_RNCK_THD_MASK)
/*! @} */

/*! @name TX_THD - Transmitter Threshold Register */
/*! @{ */
#define EMVSIM_TX_THD_TDT_MASK (0xFU)
#define EMVSIM_TX_THD_TDT_SHIFT (0U)
/*! TDT - Transmitter Data Threshold Value
 */
#define EMVSIM_TX_THD_TDT(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_THD_TDT_SHIFT)) & EMVSIM_TX_THD_TDT_MASK)
#define EMVSIM_TX_THD_TNCK_THD_MASK (0xF00U)
#define EMVSIM_TX_THD_TNCK_THD_SHIFT (8U)
/*! TNCK_THD - Transmitter NACK Threshold Value
 *  0b0000..TNTE will never be set; retransmission after NACK reception is disabled.
 *  0b0001..TNTE will be set after 1 nack is received; 0 retransmissions occurs.
 *  0b0010..TNTE will be set after 2 nacks are received; at most 1 retransmission occurs.
 *  0b0011..TNTE will be set after 3 nacks are received; at most 2 retransmissions occurs.
 *  0b1111..TNTE will be set after 15 nacks are received; at most 14 retransmissions occurs.
 */
#define EMVSIM_TX_THD_TNCK_THD(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_THD_TNCK_THD_SHIFT)) & EMVSIM_TX_THD_TNCK_THD_MASK)
/*! @} */

/*! @name RX_STATUS - Receive Status Register */
/*! @{ */
#define EMVSIM_RX_STATUS_RFO_MASK (0x1U)
#define EMVSIM_RX_STATUS_RFO_SHIFT (0U)
/*! RFO - Receive FIFO Overflow Flag
 *  0b0..No overrun error has occurred (default)
 *  0b1..A byte was received when the received FIFO was already full
 */
#define EMVSIM_RX_STATUS_RFO(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_RFO_SHIFT)) & EMVSIM_RX_STATUS_RFO_MASK)
#define EMVSIM_RX_STATUS_RX_DATA_MASK (0x10U)
#define EMVSIM_RX_STATUS_RX_DATA_SHIFT (4U)
/*! RX_DATA - Receive Data Interrupt Flag
 *  0b0..No new byte is received
 *  0b1..New byte is received ans stored in Receive FIFO
 */
#define EMVSIM_RX_STATUS_RX_DATA(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_RX_DATA_SHIFT)) & EMVSIM_RX_STATUS_RX_DATA_MASK)
#define EMVSIM_RX_STATUS_RDTF_MASK (0x20U)
#define EMVSIM_RX_STATUS_RDTF_SHIFT (5U)
/*! RDTF - Receive Data Threshold Interrupt Flag
 *  0b0..Number of unread bytes in receive FIFO less than the value set by RDT[3:0] (default).
 *  0b1..Number of unread bytes in receive FIFO greater or than equal to value set by RDT[3:0].
 */
#define EMVSIM_RX_STATUS_RDTF(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_RDTF_SHIFT)) & EMVSIM_RX_STATUS_RDTF_MASK)
#define EMVSIM_RX_STATUS_LRC_OK_MASK (0x40U)
#define EMVSIM_RX_STATUS_LRC_OK_SHIFT (6U)
/*! LRC_OK - LRC Check OK Flag
 *  0b0..Current LRC value does not match remainder.
 *  0b1..Current calculated LRC value matches the expected result (i.e. zero).
 */
#define EMVSIM_RX_STATUS_LRC_OK(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_LRC_OK_SHIFT)) & EMVSIM_RX_STATUS_LRC_OK_MASK)
#define EMVSIM_RX_STATUS_CRC_OK_MASK (0x80U)
#define EMVSIM_RX_STATUS_CRC_OK_SHIFT (7U)
/*! CRC_OK - CRC Check OK Flag
 *  0b0..Current CRC value does not match remainder.
 *  0b1..Current calculated CRC value matches the expected result.
 */
#define EMVSIM_RX_STATUS_CRC_OK(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_CRC_OK_SHIFT)) & EMVSIM_RX_STATUS_CRC_OK_MASK)
#define EMVSIM_RX_STATUS_CWT_ERR_MASK (0x100U)
#define EMVSIM_RX_STATUS_CWT_ERR_SHIFT (8U)
/*! CWT_ERR - Character Wait Time Error Flag
 *  0b0..No CWT violation has occurred (default).
 *  0b1..Time between two consecutive characters has exceeded the value in CHAR_WAIT.
 */
#define EMVSIM_RX_STATUS_CWT_ERR(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_CWT_ERR_SHIFT)) & EMVSIM_RX_STATUS_CWT_ERR_MASK)
#define EMVSIM_RX_STATUS_RTE_MASK (0x200U)
#define EMVSIM_RX_STATUS_RTE_SHIFT (9U)
/*! RTE - Received NACK Threshold Error Flag
 *  0b0..Number of NACKs generated by the receiver is less than the value programmed in RTH[3:0]
 *  0b1..Number of NACKs generated by the receiver is equal to the value programmed in RTH[3:0]
 */
#define EMVSIM_RX_STATUS_RTE(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_RTE_SHIFT)) & EMVSIM_RX_STATUS_RTE_MASK)
#define EMVSIM_RX_STATUS_BWT_ERR_MASK (0x400U)
#define EMVSIM_RX_STATUS_BWT_ERR_SHIFT (10U)
/*! BWT_ERR - Block Wait Time Error Flag
 *  0b0..Block wait time not exceeded
 *  0b1..Block wait time was exceeded
 */
#define EMVSIM_RX_STATUS_BWT_ERR(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_BWT_ERR_SHIFT)) & EMVSIM_RX_STATUS_BWT_ERR_MASK)
#define EMVSIM_RX_STATUS_BGT_ERR_MASK (0x800U)
#define EMVSIM_RX_STATUS_BGT_ERR_SHIFT (11U)
/*! BGT_ERR - Block Guard Time Error Flag
 *  0b0..Block guard time was sufficient
 *  0b1..Block guard time was too small
 */
#define EMVSIM_RX_STATUS_BGT_ERR(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_BGT_ERR_SHIFT)) & EMVSIM_RX_STATUS_BGT_ERR_MASK)
#define EMVSIM_RX_STATUS_PEF_MASK (0x1000U)
#define EMVSIM_RX_STATUS_PEF_SHIFT (12U)
/*! PEF - Parity Error Flag
 *  0b0..No parity error detected
 *  0b1..Parity error detected
 */
#define EMVSIM_RX_STATUS_PEF(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_PEF_SHIFT)) & EMVSIM_RX_STATUS_PEF_MASK)
#define EMVSIM_RX_STATUS_FEF_MASK (0x2000U)
#define EMVSIM_RX_STATUS_FEF_SHIFT (13U)
/*! FEF - Frame Error Flag
 *  0b0..No frame error detected
 *  0b1..Frame error detected
 */
#define EMVSIM_RX_STATUS_FEF(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_FEF_SHIFT)) & EMVSIM_RX_STATUS_FEF_MASK)
#define EMVSIM_RX_STATUS_RX_WPTR_MASK (0x30000U)
#define EMVSIM_RX_STATUS_RX_WPTR_SHIFT (16U)
/*! RX_WPTR - Receive FIFO Write Pointer Value
 */
#define EMVSIM_RX_STATUS_RX_WPTR(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_RX_WPTR_SHIFT)) & EMVSIM_RX_STATUS_RX_WPTR_MASK)
#define EMVSIM_RX_STATUS_RX_CNT_MASK (0x1C00000U)
#define EMVSIM_RX_STATUS_RX_CNT_SHIFT (22U)
/*! RX_CNT - Receive FIFO Byte Count
 *  0b000..FIFO is emtpy
 */
#define EMVSIM_RX_STATUS_RX_CNT(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_STATUS_RX_CNT_SHIFT)) & EMVSIM_RX_STATUS_RX_CNT_MASK)
/*! @} */

/*! @name TX_STATUS - Transmitter Status Register */
/*! @{ */
#define EMVSIM_TX_STATUS_TNTE_MASK (0x1U)
#define EMVSIM_TX_STATUS_TNTE_SHIFT (0U)
/*! TNTE - Transmit NACK Threshold Error Flag
 *  0b0..Transmit NACK threshold has not been reached (default)
 *  0b1..Transmit NACK threshold reached; transmitter frozen
 */
#define EMVSIM_TX_STATUS_TNTE(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TNTE_SHIFT)) & EMVSIM_TX_STATUS_TNTE_MASK)
#define EMVSIM_TX_STATUS_TFE_MASK (0x8U)
#define EMVSIM_TX_STATUS_TFE_SHIFT (3U)
/*! TFE - Transmit FIFO Empty Flag
 *  0b0..Transmit FIFO is not empty
 *  0b1..Transmit FIFO is empty (default)
 */
#define EMVSIM_TX_STATUS_TFE(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TFE_SHIFT)) & EMVSIM_TX_STATUS_TFE_MASK)
#define EMVSIM_TX_STATUS_ETCF_MASK (0x10U)
#define EMVSIM_TX_STATUS_ETCF_SHIFT (4U)
/*! ETCF - Early Transmit Complete Flag
 *  0b0..Transmit pending or in progress
 *  0b1..Transmit complete (default)
 */
#define EMVSIM_TX_STATUS_ETCF(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_ETCF_SHIFT)) & EMVSIM_TX_STATUS_ETCF_MASK)
#define EMVSIM_TX_STATUS_TCF_MASK (0x20U)
#define EMVSIM_TX_STATUS_TCF_SHIFT (5U)
/*! TCF - Transmit Complete Flag
 *  0b0..Transmit pending or in progress
 *  0b1..Transmit complete (default)
 */
#define EMVSIM_TX_STATUS_TCF(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TCF_SHIFT)) & EMVSIM_TX_STATUS_TCF_MASK)
#define EMVSIM_TX_STATUS_TFF_MASK (0x40U)
#define EMVSIM_TX_STATUS_TFF_SHIFT (6U)
/*! TFF - Transmit FIFO Full Flag
 *  0b0..Transmit FIFO Full condition has not occurred (default)
 *  0b1..A Transmit FIFO Full condition has occurred
 */
#define EMVSIM_TX_STATUS_TFF(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TFF_SHIFT)) & EMVSIM_TX_STATUS_TFF_MASK)
#define EMVSIM_TX_STATUS_TDTF_MASK (0x80U)
#define EMVSIM_TX_STATUS_TDTF_SHIFT (7U)
/*! TDTF - Transmit Data Threshold Flag
 *  0b0..Number of bytes in FIFO is greater than TDT[3:0], or bit has been cleared
 *  0b1..Number of bytes in FIFO is less than or equal to TDT[3:0] (default)
 */
#define EMVSIM_TX_STATUS_TDTF(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TDTF_SHIFT)) & EMVSIM_TX_STATUS_TDTF_MASK)
#define EMVSIM_TX_STATUS_GPCNT0_TO_MASK (0x100U)
#define EMVSIM_TX_STATUS_GPCNT0_TO_SHIFT (8U)
/*! GPCNT0_TO - General Purpose Counter 0 Timeout Flag
 *  0b0..GPCNT0_VAL time not reached, or bit has been cleared. (default)
 *  0b1..General Purpose counter has reached the GPCNT0_VAL value
 */
#define EMVSIM_TX_STATUS_GPCNT0_TO(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_GPCNT0_TO_SHIFT)) & EMVSIM_TX_STATUS_GPCNT0_TO_MASK)
#define EMVSIM_TX_STATUS_GPCNT1_TO_MASK (0x200U)
#define EMVSIM_TX_STATUS_GPCNT1_TO_SHIFT (9U)
/*! GPCNT1_TO - General Purpose Counter 1 Timeout Flag
 *  0b0..GPCNT1_VAL time not reached, or bit has been cleared. (default)
 *  0b1..General Purpose counter has reached the GPCNT1_VAL value
 */
#define EMVSIM_TX_STATUS_GPCNT1_TO(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_GPCNT1_TO_SHIFT)) & EMVSIM_TX_STATUS_GPCNT1_TO_MASK)
#define EMVSIM_TX_STATUS_TX_RPTR_MASK (0x30000U)
#define EMVSIM_TX_STATUS_TX_RPTR_SHIFT (16U)
/*! TX_RPTR - Transmit FIFO Read Pointer
 */
#define EMVSIM_TX_STATUS_TX_RPTR(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TX_RPTR_SHIFT)) & EMVSIM_TX_STATUS_TX_RPTR_MASK)
#define EMVSIM_TX_STATUS_TX_CNT_MASK (0x1C00000U)
#define EMVSIM_TX_STATUS_TX_CNT_SHIFT (22U)
/*! TX_CNT - Transmit FIFO Byte Count
 *  0b000..FIFO is emtpy
 */
#define EMVSIM_TX_STATUS_TX_CNT(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_STATUS_TX_CNT_SHIFT)) & EMVSIM_TX_STATUS_TX_CNT_MASK)
/*! @} */

/*! @name PCSR - Port Control and Status Register */
/*! @{ */
#define EMVSIM_PCSR_SAPD_MASK (0x1U)
#define EMVSIM_PCSR_SAPD_SHIFT (0U)
/*! SAPD - Auto Power Down Enable
 *  0b0..Auto power down disabled (default)
 *  0b1..Auto power down enabled
 */
#define EMVSIM_PCSR_SAPD(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SAPD_SHIFT)) & EMVSIM_PCSR_SAPD_MASK)
#define EMVSIM_PCSR_SVCC_EN_MASK (0x2U)
#define EMVSIM_PCSR_SVCC_EN_SHIFT (1U)
/*! SVCC_EN - Vcc Enable for Smart Card
 *  0b0..Smart Card Voltage disabled (default)
 *  0b1..Smart Card Voltage enabled
 */
#define EMVSIM_PCSR_SVCC_EN(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SVCC_EN_SHIFT)) & EMVSIM_PCSR_SVCC_EN_MASK)
#define EMVSIM_PCSR_VCCENP_MASK (0x4U)
#define EMVSIM_PCSR_VCCENP_SHIFT (2U)
/*! VCCENP - VCC Enable Polarity Control
 *  0b0..VCC_EN is active high. Polarity of SVCC_EN is unchanged.
 *  0b1..VCC_EN is active low. Polarity of SVCC_EN is inverted.
 */
#define EMVSIM_PCSR_VCCENP(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_VCCENP_SHIFT)) & EMVSIM_PCSR_VCCENP_MASK)
#define EMVSIM_PCSR_SRST_MASK (0x8U)
#define EMVSIM_PCSR_SRST_SHIFT (3U)
/*! SRST - Reset to Smart Card
 *  0b0..Smart Card Reset is asserted (default)
 *  0b1..Smart Card Reset is de-asserted
 */
#define EMVSIM_PCSR_SRST(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SRST_SHIFT)) & EMVSIM_PCSR_SRST_MASK)
#define EMVSIM_PCSR_SCEN_MASK (0x10U)
#define EMVSIM_PCSR_SCEN_SHIFT (4U)
/*! SCEN - Clock Enable for Smart Card
 *  0b0..Smart Card Clock Disabled
 *  0b1..Smart Card Clock Enabled
 */
#define EMVSIM_PCSR_SCEN(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SCEN_SHIFT)) & EMVSIM_PCSR_SCEN_MASK)
#define EMVSIM_PCSR_SCSP_MASK (0x20U)
#define EMVSIM_PCSR_SCSP_SHIFT (5U)
/*! SCSP - Smart Card Clock Stop Polarity
 *  0b0..Clock is logic 0 when stopped by SCEN
 *  0b1..Clock is logic 1 when stopped by SCEN
 */
#define EMVSIM_PCSR_SCSP(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SCSP_SHIFT)) & EMVSIM_PCSR_SCSP_MASK)
#define EMVSIM_PCSR_SPD_MASK (0x80U)
#define EMVSIM_PCSR_SPD_SHIFT (7U)
/*! SPD - Auto Power Down Control
 *  0b0..No effect (default)
 *  0b1..Start Auto Powerdown or Power Down is in progress
 */
#define EMVSIM_PCSR_SPD(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SPD_SHIFT)) & EMVSIM_PCSR_SPD_MASK)
#define EMVSIM_PCSR_SPDIM_MASK (0x1000000U)
#define EMVSIM_PCSR_SPDIM_SHIFT (24U)
/*! SPDIM - Smart Card Presence Detect Interrupt Mask
 *  0b0..SIM presence detect interrupt is enabled
 *  0b1..SIM presence detect interrupt is masked (default)
 */
#define EMVSIM_PCSR_SPDIM(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SPDIM_SHIFT)) & EMVSIM_PCSR_SPDIM_MASK)
#define EMVSIM_PCSR_SPDIF_MASK (0x2000000U)
#define EMVSIM_PCSR_SPDIF_SHIFT (25U)
/*! SPDIF - Smart Card Presence Detect Interrupt Flag
 *  0b0..No insertion or removal of Smart Card detected on Port (default)
 *  0b1..Insertion or removal of Smart Card detected on Port
 */
#define EMVSIM_PCSR_SPDIF(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SPDIF_SHIFT)) & EMVSIM_PCSR_SPDIF_MASK)
#define EMVSIM_PCSR_SPDP_MASK (0x4000000U)
#define EMVSIM_PCSR_SPDP_SHIFT (26U)
/*! SPDP - Smart Card Presence Detect Pin Status
 *  0b0..SIM Presence Detect pin is logic low
 *  0b1..SIM Presence Detectpin is logic high
 */
#define EMVSIM_PCSR_SPDP(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SPDP_SHIFT)) & EMVSIM_PCSR_SPDP_MASK)
#define EMVSIM_PCSR_SPDES_MASK (0x8000000U)
#define EMVSIM_PCSR_SPDES_SHIFT (27U)
/*! SPDES - SIM Presence Detect Edge Select
 *  0b0..Falling edge on the pin (default)
 *  0b1..Rising edge on the pin
 */
#define EMVSIM_PCSR_SPDES(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_PCSR_SPDES_SHIFT)) & EMVSIM_PCSR_SPDES_MASK)
/*! @} */

/*! @name RX_BUF - Receive Data Read Buffer */
/*! @{ */
#define EMVSIM_RX_BUF_RX_BYTE_MASK (0xFFU)
#define EMVSIM_RX_BUF_RX_BYTE_SHIFT (0U)
/*! RX_BYTE - Receive Data Byte Read
 */
#define EMVSIM_RX_BUF_RX_BYTE(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_RX_BUF_RX_BYTE_SHIFT)) & EMVSIM_RX_BUF_RX_BYTE_MASK)
/*! @} */

/*! @name TX_BUF - Transmit Data Buffer */
/*! @{ */
#define EMVSIM_TX_BUF_TX_BYTE_MASK (0xFFU)
#define EMVSIM_TX_BUF_TX_BYTE_SHIFT (0U)
/*! TX_BYTE - Transmit Data Byte
 */
#define EMVSIM_TX_BUF_TX_BYTE(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_BUF_TX_BYTE_SHIFT)) & EMVSIM_TX_BUF_TX_BYTE_MASK)
/*! @} */

/*! @name TX_GETU - Transmitter Guard ETU Value Register */
/*! @{ */
#define EMVSIM_TX_GETU_GETU_MASK (0xFFU)
#define EMVSIM_TX_GETU_GETU_SHIFT (0U)
/*! GETU - Transmitter Guard Time Value in ETU
 *  0b00000000..no additional ETUs inserted (default)
 *  0b00000001..1 additional ETU inserted
 *  0b11111110..254 additional ETUs inserted
 *  0b11111111..Subtracts one ETU by reducing the number of STOP bits from two to one
 */
#define EMVSIM_TX_GETU_GETU(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_TX_GETU_GETU_SHIFT)) & EMVSIM_TX_GETU_GETU_MASK)
/*! @} */

/*! @name CWT_VAL - Character Wait Time Value Register */
/*! @{ */
#define EMVSIM_CWT_VAL_CWT_MASK (0xFFFFU)
#define EMVSIM_CWT_VAL_CWT_SHIFT (0U)
/*! CWT - Character Wait Time Value
 */
#define EMVSIM_CWT_VAL_CWT(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_CWT_VAL_CWT_SHIFT)) & EMVSIM_CWT_VAL_CWT_MASK)
/*! @} */

/*! @name BWT_VAL - Block Wait Time Value Register */
/*! @{ */
#define EMVSIM_BWT_VAL_BWT_MASK (0xFFFFFFFFU)
#define EMVSIM_BWT_VAL_BWT_SHIFT (0U)
/*! BWT - Block Wait Time Value
 */
#define EMVSIM_BWT_VAL_BWT(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_BWT_VAL_BWT_SHIFT)) & EMVSIM_BWT_VAL_BWT_MASK)
/*! @} */

/*! @name BGT_VAL - Block Guard Time Value Register */
/*! @{ */
#define EMVSIM_BGT_VAL_BGT_MASK (0xFFFFU)
#define EMVSIM_BGT_VAL_BGT_SHIFT (0U)
/*! BGT - Block Guard Time Value
 */
#define EMVSIM_BGT_VAL_BGT(x) (((uint32_t)(((uint32_t)(x)) << EMVSIM_BGT_VAL_BGT_SHIFT)) & EMVSIM_BGT_VAL_BGT_MASK)
/*! @} */

/*! @name GPCNT0_VAL - General Purpose Counter 0 Timeout Value Register */
/*! @{ */
#define EMVSIM_GPCNT0_VAL_GPCNT0_MASK (0xFFFFU)
#define EMVSIM_GPCNT0_VAL_GPCNT0_SHIFT (0U)
/*! GPCNT0 - General Purpose Counter 0 Timeout Value
 */
#define EMVSIM_GPCNT0_VAL_GPCNT0(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_GPCNT0_VAL_GPCNT0_SHIFT)) & EMVSIM_GPCNT0_VAL_GPCNT0_MASK)
/*! @} */

/*! @name GPCNT1_VAL - General Purpose Counter 1 Timeout Value */
/*! @{ */
#define EMVSIM_GPCNT1_VAL_GPCNT1_MASK (0xFFFFU)
#define EMVSIM_GPCNT1_VAL_GPCNT1_SHIFT (0U)
/*! GPCNT1 - General Purpose Counter 1 Timeout Value
 */
#define EMVSIM_GPCNT1_VAL_GPCNT1(x) \
    (((uint32_t)(((uint32_t)(x)) << EMVSIM_GPCNT1_VAL_GPCNT1_SHIFT)) & EMVSIM_GPCNT1_VAL_GPCNT1_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group EMVSIM_Register_Masks */

/* EMVSIM - Peripheral instance base addresses */
/** Peripheral EMVSIM0 base address */
#define EMVSIM0_BASE (0x4004E000u)
/** Peripheral EMVSIM0 base pointer */
#define EMVSIM0 ((EMVSIM_Type *)EMVSIM0_BASE)
/** Array initializer of EMVSIM peripheral base addresses */
#define EMVSIM_BASE_ADDRS \
    {                     \
        EMVSIM0_BASE      \
    }
/** Array initializer of EMVSIM peripheral base pointers */
#define EMVSIM_BASE_PTRS \
    {                    \
        EMVSIM0          \
    }
/** Interrupt vectors for the EMVSIM peripheral type */
#define EMVSIM_IRQS  \
    {                \
        EMVSIM0_IRQn \
    }

/*!
 * @}
 */ /* end of group EMVSIM_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- FGPIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Peripheral_Access_Layer FGPIO Peripheral Access Layer
 * @{
 */

/** FGPIO - Register Layout Typedef */
typedef struct
{
    __IO uint32_t PDOR; /**< Port Data Output Register, offset: 0x0 */
    __O uint32_t PSOR;  /**< Port Set Output Register, offset: 0x4 */
    __O uint32_t PCOR;  /**< Port Clear Output Register, offset: 0x8 */
    __O uint32_t PTOR;  /**< Port Toggle Output Register, offset: 0xC */
    __I uint32_t PDIR;  /**< Port Data Input Register, offset: 0x10 */
    __IO uint32_t PDDR; /**< Port Data Direction Register, offset: 0x14 */
} FGPIO_Type;

/* ----------------------------------------------------------------------------
   -- FGPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Register_Masks FGPIO Register Masks
 * @{
 */

/*! @name PDOR - Port Data Output Register */
/*! @{ */
#define FGPIO_PDOR_PDO_MASK (0xFFFFFFFFU)
#define FGPIO_PDOR_PDO_SHIFT (0U)
/*! PDO - Port Data Output
 *  0b00000000000000000000000000000000..Logic level 0 is driven on pin, provided pin is configured for general-purpose
 * output. 0b00000000000000000000000000000001..Logic level 1 is driven on pin, provided pin is configured for
 * general-purpose output.
 */
#define FGPIO_PDOR_PDO(x) (((uint32_t)(((uint32_t)(x)) << FGPIO_PDOR_PDO_SHIFT)) & FGPIO_PDOR_PDO_MASK)
/*! @} */

/*! @name PSOR - Port Set Output Register */
/*! @{ */
#define FGPIO_PSOR_PTSO_MASK (0xFFFFFFFFU)
#define FGPIO_PSOR_PTSO_SHIFT (0U)
/*! PTSO - Port Set Output
 *  0b00000000000000000000000000000000..Corresponding bit in PDORn does not change.
 *  0b00000000000000000000000000000001..Corresponding bit in PDORn is set to logic 1.
 */
#define FGPIO_PSOR_PTSO(x) (((uint32_t)(((uint32_t)(x)) << FGPIO_PSOR_PTSO_SHIFT)) & FGPIO_PSOR_PTSO_MASK)
/*! @} */

/*! @name PCOR - Port Clear Output Register */
/*! @{ */
#define FGPIO_PCOR_PTCO_MASK (0xFFFFFFFFU)
#define FGPIO_PCOR_PTCO_SHIFT (0U)
/*! PTCO - Port Clear Output
 *  0b00000000000000000000000000000000..Corresponding bit in PDORn does not change.
 *  0b00000000000000000000000000000001..Corresponding bit in PDORn is cleared to logic 0.
 */
#define FGPIO_PCOR_PTCO(x) (((uint32_t)(((uint32_t)(x)) << FGPIO_PCOR_PTCO_SHIFT)) & FGPIO_PCOR_PTCO_MASK)
/*! @} */

/*! @name PTOR - Port Toggle Output Register */
/*! @{ */
#define FGPIO_PTOR_PTTO_MASK (0xFFFFFFFFU)
#define FGPIO_PTOR_PTTO_SHIFT (0U)
/*! PTTO - Port Toggle Output
 *  0b00000000000000000000000000000000..Corresponding bit in PDORn does not change.
 *  0b00000000000000000000000000000001..Corresponding bit in PDORn is set to the inverse of its existing logic state.
 */
#define FGPIO_PTOR_PTTO(x) (((uint32_t)(((uint32_t)(x)) << FGPIO_PTOR_PTTO_SHIFT)) & FGPIO_PTOR_PTTO_MASK)
/*! @} */

/*! @name PDIR - Port Data Input Register */
/*! @{ */
#define FGPIO_PDIR_PDI_MASK (0xFFFFFFFFU)
#define FGPIO_PDIR_PDI_SHIFT (0U)
/*! PDI - Port Data Input
 *  0b00000000000000000000000000000000..Pin logic level is logic 0, or is not configured for use by digital function.
 *  0b00000000000000000000000000000001..Pin logic level is logic 1.
 */
#define FGPIO_PDIR_PDI(x) (((uint32_t)(((uint32_t)(x)) << FGPIO_PDIR_PDI_SHIFT)) & FGPIO_PDIR_PDI_MASK)
/*! @} */

/*! @name PDDR - Port Data Direction Register */
/*! @{ */
#define FGPIO_PDDR_PDD_MASK (0xFFFFFFFFU)
#define FGPIO_PDDR_PDD_SHIFT (0U)
/*! PDD - Port Data Direction
 *  0b00000000000000000000000000000000..Pin is configured as general-purpose input, for the GPIO function.
 *  0b00000000000000000000000000000001..Pin is configured as general-purpose output, for the GPIO function.
 */
#define FGPIO_PDDR_PDD(x) (((uint32_t)(((uint32_t)(x)) << FGPIO_PDDR_PDD_SHIFT)) & FGPIO_PDDR_PDD_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group FGPIO_Register_Masks */

/* FGPIO - Peripheral instance base addresses */
/** Peripheral FGPIOA base address */
#define FGPIOA_BASE (0xF8000000u)
/** Peripheral FGPIOA base pointer */
#define FGPIOA ((FGPIO_Type *)FGPIOA_BASE)
/** Array initializer of FGPIO peripheral base addresses */
#define FGPIO_BASE_ADDRS \
    {                    \
        FGPIOA_BASE      \
    }
/** Array initializer of FGPIO peripheral base pointers */
#define FGPIO_BASE_PTRS \
    {                   \
        FGPIOA          \
    }

/*!
 * @}
 */ /* end of group FGPIO_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- FLEXIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLEXIO_Peripheral_Access_Layer FLEXIO Peripheral Access Layer
 * @{
 */

/** FLEXIO - Register Layout Typedef */
typedef struct
{
    __I uint32_t VERID;      /**< Version ID Register, offset: 0x0 */
    __I uint32_t PARAM;      /**< Parameter Register, offset: 0x4 */
    __IO uint32_t CTRL;      /**< FlexIO Control Register, offset: 0x8 */
    __I uint32_t PIN;        /**< Pin State Register, offset: 0xC */
    __IO uint32_t SHIFTSTAT; /**< Shifter Status Register, offset: 0x10 */
    __IO uint32_t SHIFTERR;  /**< Shifter Error Register, offset: 0x14 */
    __IO uint32_t TIMSTAT;   /**< Timer Status Register, offset: 0x18 */
    uint8_t RESERVED_0[4];
    __IO uint32_t SHIFTSIEN; /**< Shifter Status Interrupt Enable, offset: 0x20 */
    __IO uint32_t SHIFTEIEN; /**< Shifter Error Interrupt Enable, offset: 0x24 */
    __IO uint32_t TIMIEN;    /**< Timer Interrupt Enable Register, offset: 0x28 */
    uint8_t RESERVED_1[4];
    __IO uint32_t SHIFTSDEN; /**< Shifter Status DMA Enable, offset: 0x30 */
    uint8_t RESERVED_2[12];
    __IO uint32_t SHIFTSTATE; /**< Shifter State Register, offset: 0x40 */
    uint8_t RESERVED_3[60];
    __IO uint32_t SHIFTCTL[8]; /**< Shifter Control N Register, array offset: 0x80, array step: 0x4 */
    uint8_t RESERVED_4[96];
    __IO uint32_t SHIFTCFG[8]; /**< Shifter Configuration N Register, array offset: 0x100, array step: 0x4 */
    uint8_t RESERVED_5[224];
    __IO uint32_t SHIFTBUF[8]; /**< Shifter Buffer N Register, array offset: 0x200, array step: 0x4 */
    uint8_t RESERVED_6[96];
    __IO uint32_t SHIFTBUFBIS[8]; /**< Shifter Buffer N Bit Swapped Register, array offset: 0x280, array step: 0x4 */
    uint8_t RESERVED_7[96];
    __IO uint32_t SHIFTBUFBYS[8]; /**< Shifter Buffer N Byte Swapped Register, array offset: 0x300, array step: 0x4 */
    uint8_t RESERVED_8[96];
    __IO uint32_t
        SHIFTBUFBBS[8]; /**< Shifter Buffer N Bit Byte Swapped Register, array offset: 0x380, array step: 0x4 */
    uint8_t RESERVED_9[96];
    __IO uint32_t TIMCTL[8]; /**< Timer Control N Register, array offset: 0x400, array step: 0x4 */
    uint8_t RESERVED_10[96];
    __IO uint32_t TIMCFG[8]; /**< Timer Configuration N Register, array offset: 0x480, array step: 0x4 */
    uint8_t RESERVED_11[96];
    __IO uint32_t TIMCMP[8]; /**< Timer Compare N Register, array offset: 0x500, array step: 0x4 */
    uint8_t RESERVED_12[352];
    __IO uint32_t
        SHIFTBUFNBS[8]; /**< Shifter Buffer N Nibble Byte Swapped Register, array offset: 0x680, array step: 0x4 */
    uint8_t RESERVED_13[96];
    __IO uint32_t
        SHIFTBUFHWS[8]; /**< Shifter Buffer N Half Word Swapped Register, array offset: 0x700, array step: 0x4 */
    uint8_t RESERVED_14[96];
    __IO uint32_t SHIFTBUFNIS[8]; /**< Shifter Buffer N Nibble Swapped Register, array offset: 0x780, array step: 0x4 */
} FLEXIO_Type;

/* ----------------------------------------------------------------------------
   -- FLEXIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLEXIO_Register_Masks FLEXIO Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */
#define FLEXIO_VERID_FEATURE_MASK (0xFFFFU)
#define FLEXIO_VERID_FEATURE_SHIFT (0U)
/*! FEATURE - Feature Specification Number
 *  0b0000000000000000..Standard features implemented.
 *  0b0000000000000001..Supports state, logic and parallel modes.
 */
#define FLEXIO_VERID_FEATURE(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_VERID_FEATURE_SHIFT)) & FLEXIO_VERID_FEATURE_MASK)
#define FLEXIO_VERID_MINOR_MASK (0xFF0000U)
#define FLEXIO_VERID_MINOR_SHIFT (16U)
/*! MINOR - Minor Version Number
 */
#define FLEXIO_VERID_MINOR(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_VERID_MINOR_SHIFT)) & FLEXIO_VERID_MINOR_MASK)
#define FLEXIO_VERID_MAJOR_MASK (0xFF000000U)
#define FLEXIO_VERID_MAJOR_SHIFT (24U)
/*! MAJOR - Major Version Number
 */
#define FLEXIO_VERID_MAJOR(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_VERID_MAJOR_SHIFT)) & FLEXIO_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */
#define FLEXIO_PARAM_SHIFTER_MASK (0xFFU)
#define FLEXIO_PARAM_SHIFTER_SHIFT (0U)
/*! SHIFTER - Shifter Number
 */
#define FLEXIO_PARAM_SHIFTER(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_PARAM_SHIFTER_SHIFT)) & FLEXIO_PARAM_SHIFTER_MASK)
#define FLEXIO_PARAM_TIMER_MASK (0xFF00U)
#define FLEXIO_PARAM_TIMER_SHIFT (8U)
/*! TIMER - Timer Number
 */
#define FLEXIO_PARAM_TIMER(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_PARAM_TIMER_SHIFT)) & FLEXIO_PARAM_TIMER_MASK)
#define FLEXIO_PARAM_PIN_MASK (0xFF0000U)
#define FLEXIO_PARAM_PIN_SHIFT (16U)
/*! PIN - Pin Number
 */
#define FLEXIO_PARAM_PIN(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_PARAM_PIN_SHIFT)) & FLEXIO_PARAM_PIN_MASK)
#define FLEXIO_PARAM_TRIGGER_MASK (0xFF000000U)
#define FLEXIO_PARAM_TRIGGER_SHIFT (24U)
/*! TRIGGER - Trigger Number
 */
#define FLEXIO_PARAM_TRIGGER(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_PARAM_TRIGGER_SHIFT)) & FLEXIO_PARAM_TRIGGER_MASK)
/*! @} */

/*! @name CTRL - FlexIO Control Register */
/*! @{ */
#define FLEXIO_CTRL_FLEXEN_MASK (0x1U)
#define FLEXIO_CTRL_FLEXEN_SHIFT (0U)
/*! FLEXEN - FlexIO Enable
 *  0b0..FlexIO module is disabled.
 *  0b1..FlexIO module is enabled.
 */
#define FLEXIO_CTRL_FLEXEN(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_FLEXEN_SHIFT)) & FLEXIO_CTRL_FLEXEN_MASK)
#define FLEXIO_CTRL_SWRST_MASK (0x2U)
#define FLEXIO_CTRL_SWRST_SHIFT (1U)
/*! SWRST - Software Reset
 *  0b0..Software reset is disabled
 *  0b1..Software reset is enabled, all FlexIO registers except the Control Register are reset.
 */
#define FLEXIO_CTRL_SWRST(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_SWRST_SHIFT)) & FLEXIO_CTRL_SWRST_MASK)
#define FLEXIO_CTRL_FASTACC_MASK (0x4U)
#define FLEXIO_CTRL_FASTACC_SHIFT (2U)
/*! FASTACC - Fast Access
 *  0b0..Configures for normal register accesses to FlexIO
 *  0b1..Configures for fast register accesses to FlexIO
 */
#define FLEXIO_CTRL_FASTACC(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_FASTACC_SHIFT)) & FLEXIO_CTRL_FASTACC_MASK)
#define FLEXIO_CTRL_DBGE_MASK (0x40000000U)
#define FLEXIO_CTRL_DBGE_SHIFT (30U)
/*! DBGE - Debug Enable
 *  0b0..FlexIO is disabled in debug modes.
 *  0b1..FlexIO is enabled in debug modes
 */
#define FLEXIO_CTRL_DBGE(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_DBGE_SHIFT)) & FLEXIO_CTRL_DBGE_MASK)
#define FLEXIO_CTRL_DOZEN_MASK (0x80000000U)
#define FLEXIO_CTRL_DOZEN_SHIFT (31U)
/*! DOZEN - Doze Enable
 *  0b0..FlexIO enabled in Doze modes.
 *  0b1..FlexIO disabled in Doze modes.
 */
#define FLEXIO_CTRL_DOZEN(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_DOZEN_SHIFT)) & FLEXIO_CTRL_DOZEN_MASK)
/*! @} */

/*! @name PIN - Pin State Register */
/*! @{ */
#define FLEXIO_PIN_PDI_MASK (0xFFFFFFFFU)
#define FLEXIO_PIN_PDI_SHIFT (0U)
/*! PDI - Pin Data Input
 */
#define FLEXIO_PIN_PDI(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_PIN_PDI_SHIFT)) & FLEXIO_PIN_PDI_MASK)
/*! @} */

/*! @name SHIFTSTAT - Shifter Status Register */
/*! @{ */
#define FLEXIO_SHIFTSTAT_SSF_MASK (0xFFU)
#define FLEXIO_SHIFTSTAT_SSF_SHIFT (0U)
/*! SSF - Shifter Status Flag
 *  0b00000000..Status flag is clear
 *  0b00000001..Status flag is set
 */
#define FLEXIO_SHIFTSTAT_SSF(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTSTAT_SSF_SHIFT)) & FLEXIO_SHIFTSTAT_SSF_MASK)
/*! @} */

/*! @name SHIFTERR - Shifter Error Register */
/*! @{ */
#define FLEXIO_SHIFTERR_SEF_MASK (0xFFU)
#define FLEXIO_SHIFTERR_SEF_SHIFT (0U)
/*! SEF - Shifter Error Flags
 *  0b00000000..Shifter Error Flag is clear
 *  0b00000001..Shifter Error Flag is set
 */
#define FLEXIO_SHIFTERR_SEF(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTERR_SEF_SHIFT)) & FLEXIO_SHIFTERR_SEF_MASK)
/*! @} */

/*! @name TIMSTAT - Timer Status Register */
/*! @{ */
#define FLEXIO_TIMSTAT_TSF_MASK (0xFFU)
#define FLEXIO_TIMSTAT_TSF_SHIFT (0U)
/*! TSF - Timer Status Flags
 *  0b00000000..Timer Status Flag is clear
 *  0b00000001..Timer Status Flag is set
 */
#define FLEXIO_TIMSTAT_TSF(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMSTAT_TSF_SHIFT)) & FLEXIO_TIMSTAT_TSF_MASK)
/*! @} */

/*! @name SHIFTSIEN - Shifter Status Interrupt Enable */
/*! @{ */
#define FLEXIO_SHIFTSIEN_SSIE_MASK (0xFFU)
#define FLEXIO_SHIFTSIEN_SSIE_SHIFT (0U)
/*! SSIE - Shifter Status Interrupt Enable
 *  0b00000000..Shifter Status Flag interrupt disabled
 *  0b00000001..Shifter Status Flag interrupt enabled
 */
#define FLEXIO_SHIFTSIEN_SSIE(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTSIEN_SSIE_SHIFT)) & FLEXIO_SHIFTSIEN_SSIE_MASK)
/*! @} */

/*! @name SHIFTEIEN - Shifter Error Interrupt Enable */
/*! @{ */
#define FLEXIO_SHIFTEIEN_SEIE_MASK (0xFFU)
#define FLEXIO_SHIFTEIEN_SEIE_SHIFT (0U)
/*! SEIE - Shifter Error Interrupt Enable
 *  0b00000000..Shifter Error Flag interrupt disabled
 *  0b00000001..Shifter Error Flag interrupt enabled
 */
#define FLEXIO_SHIFTEIEN_SEIE(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTEIEN_SEIE_SHIFT)) & FLEXIO_SHIFTEIEN_SEIE_MASK)
/*! @} */

/*! @name TIMIEN - Timer Interrupt Enable Register */
/*! @{ */
#define FLEXIO_TIMIEN_TEIE_MASK (0xFFU)
#define FLEXIO_TIMIEN_TEIE_SHIFT (0U)
/*! TEIE - Timer Status Interrupt Enable
 *  0b00000000..Timer Status Flag interrupt is disabled
 *  0b00000001..Timer Status Flag interrupt is enabled
 */
#define FLEXIO_TIMIEN_TEIE(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMIEN_TEIE_SHIFT)) & FLEXIO_TIMIEN_TEIE_MASK)
/*! @} */

/*! @name SHIFTSDEN - Shifter Status DMA Enable */
/*! @{ */
#define FLEXIO_SHIFTSDEN_SSDE_MASK (0xFFU)
#define FLEXIO_SHIFTSDEN_SSDE_SHIFT (0U)
/*! SSDE - Shifter Status DMA Enable
 *  0b00000000..Shifter Status Flag DMA request is disabled
 *  0b00000001..Shifter Status Flag DMA request is enabled
 */
#define FLEXIO_SHIFTSDEN_SSDE(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTSDEN_SSDE_SHIFT)) & FLEXIO_SHIFTSDEN_SSDE_MASK)
/*! @} */

/*! @name SHIFTSTATE - Shifter State Register */
/*! @{ */
#define FLEXIO_SHIFTSTATE_STATE_MASK (0x7U)
#define FLEXIO_SHIFTSTATE_STATE_SHIFT (0U)
/*! STATE - Current State Pointer
 */
#define FLEXIO_SHIFTSTATE_STATE(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTSTATE_STATE_SHIFT)) & FLEXIO_SHIFTSTATE_STATE_MASK)
/*! @} */

/*! @name SHIFTCTL - Shifter Control N Register */
/*! @{ */
#define FLEXIO_SHIFTCTL_SMOD_MASK (0x7U)
#define FLEXIO_SHIFTCTL_SMOD_SHIFT (0U)
/*! SMOD - Shifter Mode
 *  0b000..Disabled.
 *  0b001..Receive mode. Captures the current Shifter content into the SHIFTBUF on expiration of the Timer.
 *  0b010..Transmit mode. Load SHIFTBUF contents into the Shifter on expiration of the Timer.
 *  0b011..Reserved.
 *  0b100..Match Store mode. Shifter data is compared to SHIFTBUF content on expiration of the Timer.
 *  0b101..Match Continuous mode. Shifter data is continuously compared to SHIFTBUF contents.
 *  0b110..State mode. SHIFTBUF contents are used for storing programmable state attributes.
 *  0b111..Logic mode. SHIFTBUF contents are used for implementing programmable logic look up table.
 */
#define FLEXIO_SHIFTCTL_SMOD(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_SMOD_SHIFT)) & FLEXIO_SHIFTCTL_SMOD_MASK)
#define FLEXIO_SHIFTCTL_PINPOL_MASK (0x80U)
#define FLEXIO_SHIFTCTL_PINPOL_SHIFT (7U)
/*! PINPOL - Shifter Pin Polarity
 *  0b0..Pin is active high
 *  0b1..Pin is active low
 */
#define FLEXIO_SHIFTCTL_PINPOL(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_PINPOL_SHIFT)) & FLEXIO_SHIFTCTL_PINPOL_MASK)
#define FLEXIO_SHIFTCTL_PINSEL_MASK (0x1F00U)
#define FLEXIO_SHIFTCTL_PINSEL_SHIFT (8U)
/*! PINSEL - Shifter Pin Select
 */
#define FLEXIO_SHIFTCTL_PINSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_PINSEL_SHIFT)) & FLEXIO_SHIFTCTL_PINSEL_MASK)
#define FLEXIO_SHIFTCTL_PINCFG_MASK (0x30000U)
#define FLEXIO_SHIFTCTL_PINCFG_SHIFT (16U)
/*! PINCFG - Shifter Pin Configuration
 *  0b00..Shifter pin output disabled
 *  0b01..Shifter pin open drain or bidirectional output enable
 *  0b10..Shifter pin bidirectional output data
 *  0b11..Shifter pin output
 */
#define FLEXIO_SHIFTCTL_PINCFG(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_PINCFG_SHIFT)) & FLEXIO_SHIFTCTL_PINCFG_MASK)
#define FLEXIO_SHIFTCTL_TIMPOL_MASK (0x800000U)
#define FLEXIO_SHIFTCTL_TIMPOL_SHIFT (23U)
/*! TIMPOL - Timer Polarity
 *  0b0..Shift on posedge of Shift clock
 *  0b1..Shift on negedge of Shift clock
 */
#define FLEXIO_SHIFTCTL_TIMPOL(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_TIMPOL_SHIFT)) & FLEXIO_SHIFTCTL_TIMPOL_MASK)
#define FLEXIO_SHIFTCTL_TIMSEL_MASK (0x7000000U)
#define FLEXIO_SHIFTCTL_TIMSEL_SHIFT (24U)
/*! TIMSEL - Timer Select
 */
#define FLEXIO_SHIFTCTL_TIMSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_TIMSEL_SHIFT)) & FLEXIO_SHIFTCTL_TIMSEL_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTCTL */
#define FLEXIO_SHIFTCTL_COUNT (8U)

/*! @name SHIFTCFG - Shifter Configuration N Register */
/*! @{ */
#define FLEXIO_SHIFTCFG_SSTART_MASK (0x3U)
#define FLEXIO_SHIFTCFG_SSTART_SHIFT (0U)
/*! SSTART - Shifter Start bit
 *  0b00..Start bit disabled for transmitter/receiver/match store, transmitter loads data on enable
 *  0b01..Start bit disabled for transmitter/receiver/match store, transmitter loads data on first shift
 *  0b10..Transmitter outputs start bit value 0 before loading data on first shift, receiver/match store sets error flag
 * if start bit is not 0 0b11..Transmitter outputs start bit value 1 before loading data on first shift, receiver/match
 * store sets error flag if start bit is not 1
 */
#define FLEXIO_SHIFTCFG_SSTART(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCFG_SSTART_SHIFT)) & FLEXIO_SHIFTCFG_SSTART_MASK)
#define FLEXIO_SHIFTCFG_SSTOP_MASK (0x30U)
#define FLEXIO_SHIFTCFG_SSTOP_SHIFT (4U)
/*! SSTOP - Shifter Stop bit
 *  0b00..Stop bit disabled for transmitter/receiver/match store
 *  0b01..Reserved for transmitter/receiver/match store
 *  0b10..Transmitter outputs stop bit value 0 on store, receiver/match store sets error flag if stop bit is not 0
 *  0b11..Transmitter outputs stop bit value 1 on store, receiver/match store sets error flag if stop bit is not 1
 */
#define FLEXIO_SHIFTCFG_SSTOP(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCFG_SSTOP_SHIFT)) & FLEXIO_SHIFTCFG_SSTOP_MASK)
#define FLEXIO_SHIFTCFG_INSRC_MASK (0x100U)
#define FLEXIO_SHIFTCFG_INSRC_SHIFT (8U)
/*! INSRC - Input Source
 *  0b0..Pin
 *  0b1..Shifter N+1 Output
 */
#define FLEXIO_SHIFTCFG_INSRC(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCFG_INSRC_SHIFT)) & FLEXIO_SHIFTCFG_INSRC_MASK)
#define FLEXIO_SHIFTCFG_PWIDTH_MASK (0x1F0000U)
#define FLEXIO_SHIFTCFG_PWIDTH_SHIFT (16U)
/*! PWIDTH - Parallel Width
 */
#define FLEXIO_SHIFTCFG_PWIDTH(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCFG_PWIDTH_SHIFT)) & FLEXIO_SHIFTCFG_PWIDTH_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTCFG */
#define FLEXIO_SHIFTCFG_COUNT (8U)

/*! @name SHIFTBUF - Shifter Buffer N Register */
/*! @{ */
#define FLEXIO_SHIFTBUF_SHIFTBUF_MASK (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUF_SHIFTBUF_SHIFT (0U)
/*! SHIFTBUF - Shift Buffer
 */
#define FLEXIO_SHIFTBUF_SHIFTBUF(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUF_SHIFTBUF_SHIFT)) & FLEXIO_SHIFTBUF_SHIFTBUF_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTBUF */
#define FLEXIO_SHIFTBUF_COUNT (8U)

/*! @name SHIFTBUFBIS - Shifter Buffer N Bit Swapped Register */
/*! @{ */
#define FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS_MASK (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS_SHIFT (0U)
/*! SHIFTBUFBIS - Shift Buffer
 */
#define FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS_SHIFT)) & FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTBUFBIS */
#define FLEXIO_SHIFTBUFBIS_COUNT (8U)

/*! @name SHIFTBUFBYS - Shifter Buffer N Byte Swapped Register */
/*! @{ */
#define FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS_MASK (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS_SHIFT (0U)
/*! SHIFTBUFBYS - Shift Buffer
 */
#define FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS_SHIFT)) & FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTBUFBYS */
#define FLEXIO_SHIFTBUFBYS_COUNT (8U)

/*! @name SHIFTBUFBBS - Shifter Buffer N Bit Byte Swapped Register */
/*! @{ */
#define FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS_MASK (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS_SHIFT (0U)
/*! SHIFTBUFBBS - Shift Buffer
 */
#define FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS_SHIFT)) & FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTBUFBBS */
#define FLEXIO_SHIFTBUFBBS_COUNT (8U)

/*! @name TIMCTL - Timer Control N Register */
/*! @{ */
#define FLEXIO_TIMCTL_TIMOD_MASK (0x3U)
#define FLEXIO_TIMCTL_TIMOD_SHIFT (0U)
/*! TIMOD - Timer Mode
 *  0b00..Timer Disabled.
 *  0b01..Dual 8-bit counters baud/bit mode.
 *  0b10..Dual 8-bit counters PWM mode.
 *  0b11..Single 16-bit counter mode.
 */
#define FLEXIO_TIMCTL_TIMOD(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_TIMOD_SHIFT)) & FLEXIO_TIMCTL_TIMOD_MASK)
#define FLEXIO_TIMCTL_PINPOL_MASK (0x80U)
#define FLEXIO_TIMCTL_PINPOL_SHIFT (7U)
/*! PINPOL - Timer Pin Polarity
 *  0b0..Pin is active high
 *  0b1..Pin is active low
 */
#define FLEXIO_TIMCTL_PINPOL(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_PINPOL_SHIFT)) & FLEXIO_TIMCTL_PINPOL_MASK)
#define FLEXIO_TIMCTL_PINSEL_MASK (0x1F00U)
#define FLEXIO_TIMCTL_PINSEL_SHIFT (8U)
/*! PINSEL - Timer Pin Select
 */
#define FLEXIO_TIMCTL_PINSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_PINSEL_SHIFT)) & FLEXIO_TIMCTL_PINSEL_MASK)
#define FLEXIO_TIMCTL_PINCFG_MASK (0x30000U)
#define FLEXIO_TIMCTL_PINCFG_SHIFT (16U)
/*! PINCFG - Timer Pin Configuration
 *  0b00..Timer pin output disabled
 *  0b01..Timer pin open drain or bidirectional output enable
 *  0b10..Timer pin bidirectional output data
 *  0b11..Timer pin output
 */
#define FLEXIO_TIMCTL_PINCFG(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_PINCFG_SHIFT)) & FLEXIO_TIMCTL_PINCFG_MASK)
#define FLEXIO_TIMCTL_TRGSRC_MASK (0x400000U)
#define FLEXIO_TIMCTL_TRGSRC_SHIFT (22U)
/*! TRGSRC - Trigger Source
 *  0b0..External trigger selected
 *  0b1..Internal trigger selected
 */
#define FLEXIO_TIMCTL_TRGSRC(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_TRGSRC_SHIFT)) & FLEXIO_TIMCTL_TRGSRC_MASK)
#define FLEXIO_TIMCTL_TRGPOL_MASK (0x800000U)
#define FLEXIO_TIMCTL_TRGPOL_SHIFT (23U)
/*! TRGPOL - Trigger Polarity
 *  0b0..Trigger active high
 *  0b1..Trigger active low
 */
#define FLEXIO_TIMCTL_TRGPOL(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_TRGPOL_SHIFT)) & FLEXIO_TIMCTL_TRGPOL_MASK)
#define FLEXIO_TIMCTL_TRGSEL_MASK (0x3F000000U)
#define FLEXIO_TIMCTL_TRGSEL_SHIFT (24U)
/*! TRGSEL - Trigger Select
 */
#define FLEXIO_TIMCTL_TRGSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_TRGSEL_SHIFT)) & FLEXIO_TIMCTL_TRGSEL_MASK)
/*! @} */

/* The count of FLEXIO_TIMCTL */
#define FLEXIO_TIMCTL_COUNT (8U)

/*! @name TIMCFG - Timer Configuration N Register */
/*! @{ */
#define FLEXIO_TIMCFG_TSTART_MASK (0x2U)
#define FLEXIO_TIMCFG_TSTART_SHIFT (1U)
/*! TSTART - Timer Start Bit
 *  0b0..Start bit disabled
 *  0b1..Start bit enabled
 */
#define FLEXIO_TIMCFG_TSTART(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TSTART_SHIFT)) & FLEXIO_TIMCFG_TSTART_MASK)
#define FLEXIO_TIMCFG_TSTOP_MASK (0x30U)
#define FLEXIO_TIMCFG_TSTOP_SHIFT (4U)
/*! TSTOP - Timer Stop Bit
 *  0b00..Stop bit disabled
 *  0b01..Stop bit is enabled on timer compare
 *  0b10..Stop bit is enabled on timer disable
 *  0b11..Stop bit is enabled on timer compare and timer disable
 */
#define FLEXIO_TIMCFG_TSTOP(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TSTOP_SHIFT)) & FLEXIO_TIMCFG_TSTOP_MASK)
#define FLEXIO_TIMCFG_TIMENA_MASK (0x700U)
#define FLEXIO_TIMCFG_TIMENA_SHIFT (8U)
/*! TIMENA - Timer Enable
 *  0b000..Timer always enabled
 *  0b001..Timer enabled on Timer N-1 enable
 *  0b010..Timer enabled on Trigger high
 *  0b011..Timer enabled on Trigger high and Pin high
 *  0b100..Timer enabled on Pin rising edge
 *  0b101..Timer enabled on Pin rising edge and Trigger high
 *  0b110..Timer enabled on Trigger rising edge
 *  0b111..Timer enabled on Trigger rising or falling edge
 */
#define FLEXIO_TIMCFG_TIMENA(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMENA_SHIFT)) & FLEXIO_TIMCFG_TIMENA_MASK)
#define FLEXIO_TIMCFG_TIMDIS_MASK (0x7000U)
#define FLEXIO_TIMCFG_TIMDIS_SHIFT (12U)
/*! TIMDIS - Timer Disable
 *  0b000..Timer never disabled
 *  0b001..Timer disabled on Timer N-1 disable
 *  0b010..Timer disabled on Timer compare
 *  0b011..Timer disabled on Timer compare and Trigger Low
 *  0b100..Timer disabled on Pin rising or falling edge
 *  0b101..Timer disabled on Pin rising or falling edge provided Trigger is high
 *  0b110..Timer disabled on Trigger falling edge
 *  0b111..Reserved
 */
#define FLEXIO_TIMCFG_TIMDIS(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMDIS_SHIFT)) & FLEXIO_TIMCFG_TIMDIS_MASK)
#define FLEXIO_TIMCFG_TIMRST_MASK (0x70000U)
#define FLEXIO_TIMCFG_TIMRST_SHIFT (16U)
/*! TIMRST - Timer Reset
 *  0b000..Timer never reset
 *  0b001..Reserved
 *  0b010..Timer reset on Timer Pin equal to Timer Output
 *  0b011..Timer reset on Timer Trigger equal to Timer Output
 *  0b100..Timer reset on Timer Pin rising edge
 *  0b101..Reserved
 *  0b110..Timer reset on Trigger rising edge
 *  0b111..Timer reset on Trigger rising or falling edge
 */
#define FLEXIO_TIMCFG_TIMRST(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMRST_SHIFT)) & FLEXIO_TIMCFG_TIMRST_MASK)
#define FLEXIO_TIMCFG_TIMDEC_MASK (0x300000U)
#define FLEXIO_TIMCFG_TIMDEC_SHIFT (20U)
/*! TIMDEC - Timer Decrement
 *  0b00..Decrement counter on FlexIO clock, Shift clock equals Timer output.
 *  0b01..Decrement counter on Trigger input (both edges), Shift clock equals Timer output.
 *  0b10..Decrement counter on Pin input (both edges), Shift clock equals Pin input.
 *  0b11..Decrement counter on Trigger input (both edges), Shift clock equals Trigger input.
 */
#define FLEXIO_TIMCFG_TIMDEC(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMDEC_SHIFT)) & FLEXIO_TIMCFG_TIMDEC_MASK)
#define FLEXIO_TIMCFG_TIMOUT_MASK (0x3000000U)
#define FLEXIO_TIMCFG_TIMOUT_SHIFT (24U)
/*! TIMOUT - Timer Output
 *  0b00..Timer output is logic one when enabled and is not affected by timer reset
 *  0b01..Timer output is logic zero when enabled and is not affected by timer reset
 *  0b10..Timer output is logic one when enabled and on timer reset
 *  0b11..Timer output is logic zero when enabled and on timer reset
 */
#define FLEXIO_TIMCFG_TIMOUT(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMOUT_SHIFT)) & FLEXIO_TIMCFG_TIMOUT_MASK)
/*! @} */

/* The count of FLEXIO_TIMCFG */
#define FLEXIO_TIMCFG_COUNT (8U)

/*! @name TIMCMP - Timer Compare N Register */
/*! @{ */
#define FLEXIO_TIMCMP_CMP_MASK (0xFFFFU)
#define FLEXIO_TIMCMP_CMP_SHIFT (0U)
/*! CMP - Timer Compare Value
 */
#define FLEXIO_TIMCMP_CMP(x) (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCMP_CMP_SHIFT)) & FLEXIO_TIMCMP_CMP_MASK)
/*! @} */

/* The count of FLEXIO_TIMCMP */
#define FLEXIO_TIMCMP_COUNT (8U)

/*! @name SHIFTBUFNBS - Shifter Buffer N Nibble Byte Swapped Register */
/*! @{ */
#define FLEXIO_SHIFTBUFNBS_SHIFTBUFNBS_MASK (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFNBS_SHIFTBUFNBS_SHIFT (0U)
/*! SHIFTBUFNBS - Shift Buffer
 */
#define FLEXIO_SHIFTBUFNBS_SHIFTBUFNBS(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFNBS_SHIFTBUFNBS_SHIFT)) & FLEXIO_SHIFTBUFNBS_SHIFTBUFNBS_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTBUFNBS */
#define FLEXIO_SHIFTBUFNBS_COUNT (8U)

/*! @name SHIFTBUFHWS - Shifter Buffer N Half Word Swapped Register */
/*! @{ */
#define FLEXIO_SHIFTBUFHWS_SHIFTBUFHWS_MASK (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFHWS_SHIFTBUFHWS_SHIFT (0U)
/*! SHIFTBUFHWS - Shift Buffer
 */
#define FLEXIO_SHIFTBUFHWS_SHIFTBUFHWS(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFHWS_SHIFTBUFHWS_SHIFT)) & FLEXIO_SHIFTBUFHWS_SHIFTBUFHWS_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTBUFHWS */
#define FLEXIO_SHIFTBUFHWS_COUNT (8U)

/*! @name SHIFTBUFNIS - Shifter Buffer N Nibble Swapped Register */
/*! @{ */
#define FLEXIO_SHIFTBUFNIS_SHIFTBUFNIS_MASK (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFNIS_SHIFTBUFNIS_SHIFT (0U)
/*! SHIFTBUFNIS - Shift Buffer
 */
#define FLEXIO_SHIFTBUFNIS_SHIFTBUFNIS(x) \
    (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFNIS_SHIFTBUFNIS_SHIFT)) & FLEXIO_SHIFTBUFNIS_SHIFTBUFNIS_MASK)
/*! @} */

/* The count of FLEXIO_SHIFTBUFNIS */
#define FLEXIO_SHIFTBUFNIS_COUNT (8U)

/*!
 * @}
 */ /* end of group FLEXIO_Register_Masks */

/* FLEXIO - Peripheral instance base addresses */
/** Peripheral FLEXIO0 base address */
#define FLEXIO0_BASE (0x400CA000u)
/** Peripheral FLEXIO0 base pointer */
#define FLEXIO0 ((FLEXIO_Type *)FLEXIO0_BASE)
/** Array initializer of FLEXIO peripheral base addresses */
#define FLEXIO_BASE_ADDRS \
    {                     \
        FLEXIO0_BASE      \
    }
/** Array initializer of FLEXIO peripheral base pointers */
#define FLEXIO_BASE_PTRS \
    {                    \
        FLEXIO0          \
    }
/** Interrupt vectors for the FLEXIO peripheral type */
#define FLEXIO_IRQS  \
    {                \
        FLEXIO0_IRQn \
    }

/*!
 * @}
 */ /* end of group FLEXIO_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- FTFA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFA_Peripheral_Access_Layer FTFA Peripheral Access Layer
 * @{
 */

/** FTFA - Register Layout Typedef */
typedef struct
{
    __IO uint8_t FSTAT;  /**< Flash Status Register, offset: 0x0 */
    __IO uint8_t FCNFG;  /**< Flash Configuration Register, offset: 0x1 */
    __I uint8_t FSEC;    /**< Flash Security Register, offset: 0x2 */
    __I uint8_t FOPT;    /**< Flash Option Register, offset: 0x3 */
    __IO uint8_t FCCOB3; /**< Flash Common Command Object Registers, offset: 0x4 */
    __IO uint8_t FCCOB2; /**< Flash Common Command Object Registers, offset: 0x5 */
    __IO uint8_t FCCOB1; /**< Flash Common Command Object Registers, offset: 0x6 */
    __IO uint8_t FCCOB0; /**< Flash Common Command Object Registers, offset: 0x7 */
    __IO uint8_t FCCOB7; /**< Flash Common Command Object Registers, offset: 0x8 */
    __IO uint8_t FCCOB6; /**< Flash Common Command Object Registers, offset: 0x9 */
    __IO uint8_t FCCOB5; /**< Flash Common Command Object Registers, offset: 0xA */
    __IO uint8_t FCCOB4; /**< Flash Common Command Object Registers, offset: 0xB */
    __IO uint8_t FCCOBB; /**< Flash Common Command Object Registers, offset: 0xC */
    __IO uint8_t FCCOBA; /**< Flash Common Command Object Registers, offset: 0xD */
    __IO uint8_t FCCOB9; /**< Flash Common Command Object Registers, offset: 0xE */
    __IO uint8_t FCCOB8; /**< Flash Common Command Object Registers, offset: 0xF */
    __IO uint8_t FPROT3; /**< Program Flash Protection Registers, offset: 0x10 */
    __IO uint8_t FPROT2; /**< Program Flash Protection Registers, offset: 0x11 */
    __IO uint8_t FPROT1; /**< Program Flash Protection Registers, offset: 0x12 */
    __IO uint8_t FPROT0; /**< Program Flash Protection Registers, offset: 0x13 */
    uint8_t RESERVED_0[4];
    __I uint8_t XACCH3; /**< Execute-only Access Registers, offset: 0x18 */
    __I uint8_t XACCH2; /**< Execute-only Access Registers, offset: 0x19 */
    __I uint8_t XACCH1; /**< Execute-only Access Registers, offset: 0x1A */
    __I uint8_t XACCH0; /**< Execute-only Access Registers, offset: 0x1B */
    __I uint8_t XACCL3; /**< Execute-only Access Registers, offset: 0x1C */
    __I uint8_t XACCL2; /**< Execute-only Access Registers, offset: 0x1D */
    __I uint8_t XACCL1; /**< Execute-only Access Registers, offset: 0x1E */
    __I uint8_t XACCL0; /**< Execute-only Access Registers, offset: 0x1F */
    __I uint8_t SACCH3; /**< Supervisor-only Access Registers, offset: 0x20 */
    __I uint8_t SACCH2; /**< Supervisor-only Access Registers, offset: 0x21 */
    __I uint8_t SACCH1; /**< Supervisor-only Access Registers, offset: 0x22 */
    __I uint8_t SACCH0; /**< Supervisor-only Access Registers, offset: 0x23 */
    __I uint8_t SACCL3; /**< Supervisor-only Access Registers, offset: 0x24 */
    __I uint8_t SACCL2; /**< Supervisor-only Access Registers, offset: 0x25 */
    __I uint8_t SACCL1; /**< Supervisor-only Access Registers, offset: 0x26 */
    __I uint8_t SACCL0; /**< Supervisor-only Access Registers, offset: 0x27 */
    __I uint8_t FACSS;  /**< Flash Access Segment Size Register, offset: 0x28 */
    uint8_t RESERVED_1[2];
    __I uint8_t FACSN; /**< Flash Access Segment Number Register, offset: 0x2B */
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
#define FTFA_FSTAT_MGSTAT0_MASK (0x1U)
#define FTFA_FSTAT_MGSTAT0_SHIFT (0U)
/*! MGSTAT0 - Memory Controller Command Completion Status Flag
 */
#define FTFA_FSTAT_MGSTAT0(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_MGSTAT0_SHIFT)) & FTFA_FSTAT_MGSTAT0_MASK)
#define FTFA_FSTAT_FPVIOL_MASK (0x10U)
#define FTFA_FSTAT_FPVIOL_SHIFT (4U)
/*! FPVIOL - Flash Protection Violation Flag
 *  0b0..No protection violation detected
 *  0b1..Protection violation detected
 */
#define FTFA_FSTAT_FPVIOL(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_FPVIOL_SHIFT)) & FTFA_FSTAT_FPVIOL_MASK)
#define FTFA_FSTAT_ACCERR_MASK (0x20U)
#define FTFA_FSTAT_ACCERR_SHIFT (5U)
/*! ACCERR - Flash Access Error Flag
 *  0b0..No access error detected
 *  0b1..Access error detected
 */
#define FTFA_FSTAT_ACCERR(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_ACCERR_SHIFT)) & FTFA_FSTAT_ACCERR_MASK)
#define FTFA_FSTAT_RDCOLERR_MASK (0x40U)
#define FTFA_FSTAT_RDCOLERR_SHIFT (6U)
/*! RDCOLERR - Flash Read Collision Error Flag
 *  0b0..No collision error detected
 *  0b1..Collision error detected
 */
#define FTFA_FSTAT_RDCOLERR(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_RDCOLERR_SHIFT)) & FTFA_FSTAT_RDCOLERR_MASK)
#define FTFA_FSTAT_CCIF_MASK (0x80U)
#define FTFA_FSTAT_CCIF_SHIFT (7U)
/*! CCIF - Command Complete Interrupt Flag
 *  0b0..Flash command in progress
 *  0b1..Flash command has completed
 */
#define FTFA_FSTAT_CCIF(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_CCIF_SHIFT)) & FTFA_FSTAT_CCIF_MASK)
/*! @} */

/*! @name FCNFG - Flash Configuration Register */
/*! @{ */
#define FTFA_FCNFG_ERSSUSP_MASK (0x10U)
#define FTFA_FCNFG_ERSSUSP_SHIFT (4U)
/*! ERSSUSP - Erase Suspend
 *  0b0..No suspend requested
 *  0b1..Suspend the current Erase Flash Sector command execution.
 */
#define FTFA_FCNFG_ERSSUSP(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCNFG_ERSSUSP_SHIFT)) & FTFA_FCNFG_ERSSUSP_MASK)
#define FTFA_FCNFG_ERSAREQ_MASK (0x20U)
#define FTFA_FCNFG_ERSAREQ_SHIFT (5U)
/*! ERSAREQ - Erase All Request
 *  0b0..No request or request complete
 *  0b1..Request to: run the Erase All Blocks command, verify the erased state, program the security byte in the
 *       Flash Configuration Field to the unsecure state, and release MCU security by setting the FSEC[SEC] field to
 *       the unsecure state.
 */
#define FTFA_FCNFG_ERSAREQ(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCNFG_ERSAREQ_SHIFT)) & FTFA_FCNFG_ERSAREQ_MASK)
#define FTFA_FCNFG_RDCOLLIE_MASK (0x40U)
#define FTFA_FCNFG_RDCOLLIE_SHIFT (6U)
/*! RDCOLLIE - Read Collision Error Interrupt Enable
 *  0b0..Read collision error interrupt disabled
 *  0b1..Read collision error interrupt enabled. An interrupt request is generated whenever a flash memory read
 *       collision error is detected (see the description of FSTAT[RDCOLERR]).
 */
#define FTFA_FCNFG_RDCOLLIE(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCNFG_RDCOLLIE_SHIFT)) & FTFA_FCNFG_RDCOLLIE_MASK)
#define FTFA_FCNFG_CCIE_MASK (0x80U)
#define FTFA_FCNFG_CCIE_SHIFT (7U)
/*! CCIE - Command Complete Interrupt Enable
 *  0b0..Command complete interrupt disabled
 *  0b1..Command complete interrupt enabled. An interrupt request is generated whenever the FSTAT[CCIF] flag is set.
 */
#define FTFA_FCNFG_CCIE(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCNFG_CCIE_SHIFT)) & FTFA_FCNFG_CCIE_MASK)
/*! @} */

/*! @name FSEC - Flash Security Register */
/*! @{ */
#define FTFA_FSEC_SEC_MASK (0x3U)
#define FTFA_FSEC_SEC_SHIFT (0U)
/*! SEC - Flash Security
 *  0b00..MCU security status is secure.
 *  0b01..MCU security status is secure.
 *  0b10..MCU security status is unsecure. (The standard shipping condition of the flash memory module is unsecure.)
 *  0b11..MCU security status is secure.
 */
#define FTFA_FSEC_SEC(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FSEC_SEC_SHIFT)) & FTFA_FSEC_SEC_MASK)
#define FTFA_FSEC_FSLACC_MASK (0xCU)
#define FTFA_FSEC_FSLACC_SHIFT (2U)
/*! FSLACC - Factory Security Level Access Code
 *  0b00..NXP factory access granted
 *  0b01..NXP factory access denied
 *  0b10..NXP factory access denied
 *  0b11..NXP factory access granted
 */
#define FTFA_FSEC_FSLACC(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FSEC_FSLACC_SHIFT)) & FTFA_FSEC_FSLACC_MASK)
#define FTFA_FSEC_MEEN_MASK (0x30U)
#define FTFA_FSEC_MEEN_SHIFT (4U)
/*! MEEN - Mass Erase Enable
 *  0b00..Mass erase is enabled
 *  0b01..Mass erase is enabled
 *  0b10..Mass erase is disabled
 *  0b11..Mass erase is enabled
 */
#define FTFA_FSEC_MEEN(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FSEC_MEEN_SHIFT)) & FTFA_FSEC_MEEN_MASK)
#define FTFA_FSEC_KEYEN_MASK (0xC0U)
#define FTFA_FSEC_KEYEN_SHIFT (6U)
/*! KEYEN - Backdoor Key Security Enable
 *  0b00..Backdoor key access disabled
 *  0b01..Backdoor key access disabled (preferred KEYEN state to disable backdoor key access)
 *  0b10..Backdoor key access enabled
 *  0b11..Backdoor key access disabled
 */
#define FTFA_FSEC_KEYEN(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FSEC_KEYEN_SHIFT)) & FTFA_FSEC_KEYEN_MASK)
/*! @} */

/*! @name FOPT - Flash Option Register */
/*! @{ */
#define FTFA_FOPT_OPT_MASK (0xFFU)
#define FTFA_FOPT_OPT_SHIFT (0U)
/*! OPT - Nonvolatile Option
 */
#define FTFA_FOPT_OPT(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FOPT_OPT_SHIFT)) & FTFA_FOPT_OPT_MASK)
/*! @} */

/*! @name FCCOB3 - Flash Common Command Object Registers */
/*! @{ */
#define FTFA_FCCOB3_CCOBn_MASK (0xFFU)
#define FTFA_FCCOB3_CCOBn_SHIFT (0U)
#define FTFA_FCCOB3_CCOBn(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB3_CCOBn_SHIFT)) & FTFA_FCCOB3_CCOBn_MASK)
/*! @} */

/*! @name FCCOB2 - Flash Common Command Object Registers */
/*! @{ */
#define FTFA_FCCOB2_CCOBn_MASK (0xFFU)
#define FTFA_FCCOB2_CCOBn_SHIFT (0U)
#define FTFA_FCCOB2_CCOBn(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB2_CCOBn_SHIFT)) & FTFA_FCCOB2_CCOBn_MASK)
/*! @} */

/*! @name FCCOB1 - Flash Common Command Object Registers */
/*! @{ */
#define FTFA_FCCOB1_CCOBn_MASK (0xFFU)
#define FTFA_FCCOB1_CCOBn_SHIFT (0U)
#define FTFA_FCCOB1_CCOBn(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB1_CCOBn_SHIFT)) & FTFA_FCCOB1_CCOBn_MASK)
/*! @} */

/*! @name FCCOB0 - Flash Common Command Object Registers */
/*! @{ */
#define FTFA_FCCOB0_CCOBn_MASK (0xFFU)
#define FTFA_FCCOB0_CCOBn_SHIFT (0U)
#define FTFA_FCCOB0_CCOBn(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB0_CCOBn_SHIFT)) & FTFA_FCCOB0_CCOBn_MASK)
/*! @} */

/*! @name FCCOB7 - Flash Common Command Object Registers */
/*! @{ */
#define FTFA_FCCOB7_CCOBn_MASK (0xFFU)
#define FTFA_FCCOB7_CCOBn_SHIFT (0U)
#define FTFA_FCCOB7_CCOBn(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB7_CCOBn_SHIFT)) & FTFA_FCCOB7_CCOBn_MASK)
/*! @} */

/*! @name FCCOB6 - Flash Common Command Object Registers */
/*! @{ */
#define FTFA_FCCOB6_CCOBn_MASK (0xFFU)
#define FTFA_FCCOB6_CCOBn_SHIFT (0U)
#define FTFA_FCCOB6_CCOBn(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB6_CCOBn_SHIFT)) & FTFA_FCCOB6_CCOBn_MASK)
/*! @} */

/*! @name FCCOB5 - Flash Common Command Object Registers */
/*! @{ */
#define FTFA_FCCOB5_CCOBn_MASK (0xFFU)
#define FTFA_FCCOB5_CCOBn_SHIFT (0U)
#define FTFA_FCCOB5_CCOBn(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB5_CCOBn_SHIFT)) & FTFA_FCCOB5_CCOBn_MASK)
/*! @} */

/*! @name FCCOB4 - Flash Common Command Object Registers */
/*! @{ */
#define FTFA_FCCOB4_CCOBn_MASK (0xFFU)
#define FTFA_FCCOB4_CCOBn_SHIFT (0U)
#define FTFA_FCCOB4_CCOBn(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB4_CCOBn_SHIFT)) & FTFA_FCCOB4_CCOBn_MASK)
/*! @} */

/*! @name FCCOBB - Flash Common Command Object Registers */
/*! @{ */
#define FTFA_FCCOBB_CCOBn_MASK (0xFFU)
#define FTFA_FCCOBB_CCOBn_SHIFT (0U)
#define FTFA_FCCOBB_CCOBn(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOBB_CCOBn_SHIFT)) & FTFA_FCCOBB_CCOBn_MASK)
/*! @} */

/*! @name FCCOBA - Flash Common Command Object Registers */
/*! @{ */
#define FTFA_FCCOBA_CCOBn_MASK (0xFFU)
#define FTFA_FCCOBA_CCOBn_SHIFT (0U)
#define FTFA_FCCOBA_CCOBn(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOBA_CCOBn_SHIFT)) & FTFA_FCCOBA_CCOBn_MASK)
/*! @} */

/*! @name FCCOB9 - Flash Common Command Object Registers */
/*! @{ */
#define FTFA_FCCOB9_CCOBn_MASK (0xFFU)
#define FTFA_FCCOB9_CCOBn_SHIFT (0U)
#define FTFA_FCCOB9_CCOBn(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB9_CCOBn_SHIFT)) & FTFA_FCCOB9_CCOBn_MASK)
/*! @} */

/*! @name FCCOB8 - Flash Common Command Object Registers */
/*! @{ */
#define FTFA_FCCOB8_CCOBn_MASK (0xFFU)
#define FTFA_FCCOB8_CCOBn_SHIFT (0U)
#define FTFA_FCCOB8_CCOBn(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB8_CCOBn_SHIFT)) & FTFA_FCCOB8_CCOBn_MASK)
/*! @} */

/*! @name FPROT3 - Program Flash Protection Registers */
/*! @{ */
#define FTFA_FPROT3_PROT_MASK (0xFFU)
#define FTFA_FPROT3_PROT_SHIFT (0U)
/*! PROT - Program Flash Region Protect
 *  0b00000000..Program flash region is protected.
 *  0b00000001..Program flash region is not protected
 */
#define FTFA_FPROT3_PROT(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FPROT3_PROT_SHIFT)) & FTFA_FPROT3_PROT_MASK)
/*! @} */

/*! @name FPROT2 - Program Flash Protection Registers */
/*! @{ */
#define FTFA_FPROT2_PROT_MASK (0xFFU)
#define FTFA_FPROT2_PROT_SHIFT (0U)
/*! PROT - Program Flash Region Protect
 *  0b00000000..Program flash region is protected.
 *  0b00000001..Program flash region is not protected
 */
#define FTFA_FPROT2_PROT(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FPROT2_PROT_SHIFT)) & FTFA_FPROT2_PROT_MASK)
/*! @} */

/*! @name FPROT1 - Program Flash Protection Registers */
/*! @{ */
#define FTFA_FPROT1_PROT_MASK (0xFFU)
#define FTFA_FPROT1_PROT_SHIFT (0U)
/*! PROT - Program Flash Region Protect
 *  0b00000000..Program flash region is protected.
 *  0b00000001..Program flash region is not protected
 */
#define FTFA_FPROT1_PROT(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FPROT1_PROT_SHIFT)) & FTFA_FPROT1_PROT_MASK)
/*! @} */

/*! @name FPROT0 - Program Flash Protection Registers */
/*! @{ */
#define FTFA_FPROT0_PROT_MASK (0xFFU)
#define FTFA_FPROT0_PROT_SHIFT (0U)
/*! PROT - Program Flash Region Protect
 *  0b00000000..Program flash region is protected.
 *  0b00000001..Program flash region is not protected
 */
#define FTFA_FPROT0_PROT(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FPROT0_PROT_SHIFT)) & FTFA_FPROT0_PROT_MASK)
/*! @} */

/*! @name XACCH3 - Execute-only Access Registers */
/*! @{ */
#define FTFA_XACCH3_XA_MASK (0xFFU)
#define FTFA_XACCH3_XA_SHIFT (0U)
/*! XA - Execute-only access control
 *  0b00000000..Associated segment is accessible in execute mode only (as an instruction fetch)
 *  0b00000001..Associated segment is accessible as data or in execute mode
 */
#define FTFA_XACCH3_XA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_XACCH3_XA_SHIFT)) & FTFA_XACCH3_XA_MASK)
/*! @} */

/*! @name XACCH2 - Execute-only Access Registers */
/*! @{ */
#define FTFA_XACCH2_XA_MASK (0xFFU)
#define FTFA_XACCH2_XA_SHIFT (0U)
/*! XA - Execute-only access control
 *  0b00000000..Associated segment is accessible in execute mode only (as an instruction fetch)
 *  0b00000001..Associated segment is accessible as data or in execute mode
 */
#define FTFA_XACCH2_XA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_XACCH2_XA_SHIFT)) & FTFA_XACCH2_XA_MASK)
/*! @} */

/*! @name XACCH1 - Execute-only Access Registers */
/*! @{ */
#define FTFA_XACCH1_XA_MASK (0xFFU)
#define FTFA_XACCH1_XA_SHIFT (0U)
/*! XA - Execute-only access control
 *  0b00000000..Associated segment is accessible in execute mode only (as an instruction fetch)
 *  0b00000001..Associated segment is accessible as data or in execute mode
 */
#define FTFA_XACCH1_XA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_XACCH1_XA_SHIFT)) & FTFA_XACCH1_XA_MASK)
/*! @} */

/*! @name XACCH0 - Execute-only Access Registers */
/*! @{ */
#define FTFA_XACCH0_XA_MASK (0xFFU)
#define FTFA_XACCH0_XA_SHIFT (0U)
/*! XA - Execute-only access control
 *  0b00000000..Associated segment is accessible in execute mode only (as an instruction fetch)
 *  0b00000001..Associated segment is accessible as data or in execute mode
 */
#define FTFA_XACCH0_XA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_XACCH0_XA_SHIFT)) & FTFA_XACCH0_XA_MASK)
/*! @} */

/*! @name XACCL3 - Execute-only Access Registers */
/*! @{ */
#define FTFA_XACCL3_XA_MASK (0xFFU)
#define FTFA_XACCL3_XA_SHIFT (0U)
/*! XA - Execute-only access control
 *  0b00000000..Associated segment is accessible in execute mode only (as an instruction fetch)
 *  0b00000001..Associated segment is accessible as data or in execute mode
 */
#define FTFA_XACCL3_XA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_XACCL3_XA_SHIFT)) & FTFA_XACCL3_XA_MASK)
/*! @} */

/*! @name XACCL2 - Execute-only Access Registers */
/*! @{ */
#define FTFA_XACCL2_XA_MASK (0xFFU)
#define FTFA_XACCL2_XA_SHIFT (0U)
/*! XA - Execute-only access control
 *  0b00000000..Associated segment is accessible in execute mode only (as an instruction fetch)
 *  0b00000001..Associated segment is accessible as data or in execute mode
 */
#define FTFA_XACCL2_XA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_XACCL2_XA_SHIFT)) & FTFA_XACCL2_XA_MASK)
/*! @} */

/*! @name XACCL1 - Execute-only Access Registers */
/*! @{ */
#define FTFA_XACCL1_XA_MASK (0xFFU)
#define FTFA_XACCL1_XA_SHIFT (0U)
/*! XA - Execute-only access control
 *  0b00000000..Associated segment is accessible in execute mode only (as an instruction fetch)
 *  0b00000001..Associated segment is accessible as data or in execute mode
 */
#define FTFA_XACCL1_XA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_XACCL1_XA_SHIFT)) & FTFA_XACCL1_XA_MASK)
/*! @} */

/*! @name XACCL0 - Execute-only Access Registers */
/*! @{ */
#define FTFA_XACCL0_XA_MASK (0xFFU)
#define FTFA_XACCL0_XA_SHIFT (0U)
/*! XA - Execute-only access control
 *  0b00000000..Associated segment is accessible in execute mode only (as an instruction fetch)
 *  0b00000001..Associated segment is accessible as data or in execute mode
 */
#define FTFA_XACCL0_XA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_XACCL0_XA_SHIFT)) & FTFA_XACCL0_XA_MASK)
/*! @} */

/*! @name SACCH3 - Supervisor-only Access Registers */
/*! @{ */
#define FTFA_SACCH3_SA_MASK (0xFFU)
#define FTFA_SACCH3_SA_SHIFT (0U)
/*! SA - Supervisor-only access control
 *  0b00000000..Associated segment is accessible in supervisor mode only
 *  0b00000001..Associated segment is accessible in user or supervisor mode
 */
#define FTFA_SACCH3_SA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_SACCH3_SA_SHIFT)) & FTFA_SACCH3_SA_MASK)
/*! @} */

/*! @name SACCH2 - Supervisor-only Access Registers */
/*! @{ */
#define FTFA_SACCH2_SA_MASK (0xFFU)
#define FTFA_SACCH2_SA_SHIFT (0U)
/*! SA - Supervisor-only access control
 *  0b00000000..Associated segment is accessible in supervisor mode only
 *  0b00000001..Associated segment is accessible in user or supervisor mode
 */
#define FTFA_SACCH2_SA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_SACCH2_SA_SHIFT)) & FTFA_SACCH2_SA_MASK)
/*! @} */

/*! @name SACCH1 - Supervisor-only Access Registers */
/*! @{ */
#define FTFA_SACCH1_SA_MASK (0xFFU)
#define FTFA_SACCH1_SA_SHIFT (0U)
/*! SA - Supervisor-only access control
 *  0b00000000..Associated segment is accessible in supervisor mode only
 *  0b00000001..Associated segment is accessible in user or supervisor mode
 */
#define FTFA_SACCH1_SA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_SACCH1_SA_SHIFT)) & FTFA_SACCH1_SA_MASK)
/*! @} */

/*! @name SACCH0 - Supervisor-only Access Registers */
/*! @{ */
#define FTFA_SACCH0_SA_MASK (0xFFU)
#define FTFA_SACCH0_SA_SHIFT (0U)
/*! SA - Supervisor-only access control
 *  0b00000000..Associated segment is accessible in supervisor mode only
 *  0b00000001..Associated segment is accessible in user or supervisor mode
 */
#define FTFA_SACCH0_SA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_SACCH0_SA_SHIFT)) & FTFA_SACCH0_SA_MASK)
/*! @} */

/*! @name SACCL3 - Supervisor-only Access Registers */
/*! @{ */
#define FTFA_SACCL3_SA_MASK (0xFFU)
#define FTFA_SACCL3_SA_SHIFT (0U)
/*! SA - Supervisor-only access control
 *  0b00000000..Associated segment is accessible in supervisor mode only
 *  0b00000001..Associated segment is accessible in user or supervisor mode
 */
#define FTFA_SACCL3_SA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_SACCL3_SA_SHIFT)) & FTFA_SACCL3_SA_MASK)
/*! @} */

/*! @name SACCL2 - Supervisor-only Access Registers */
/*! @{ */
#define FTFA_SACCL2_SA_MASK (0xFFU)
#define FTFA_SACCL2_SA_SHIFT (0U)
/*! SA - Supervisor-only access control
 *  0b00000000..Associated segment is accessible in supervisor mode only
 *  0b00000001..Associated segment is accessible in user or supervisor mode
 */
#define FTFA_SACCL2_SA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_SACCL2_SA_SHIFT)) & FTFA_SACCL2_SA_MASK)
/*! @} */

/*! @name SACCL1 - Supervisor-only Access Registers */
/*! @{ */
#define FTFA_SACCL1_SA_MASK (0xFFU)
#define FTFA_SACCL1_SA_SHIFT (0U)
/*! SA - Supervisor-only access control
 *  0b00000000..Associated segment is accessible in supervisor mode only
 *  0b00000001..Associated segment is accessible in user or supervisor mode
 */
#define FTFA_SACCL1_SA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_SACCL1_SA_SHIFT)) & FTFA_SACCL1_SA_MASK)
/*! @} */

/*! @name SACCL0 - Supervisor-only Access Registers */
/*! @{ */
#define FTFA_SACCL0_SA_MASK (0xFFU)
#define FTFA_SACCL0_SA_SHIFT (0U)
/*! SA - Supervisor-only access control
 *  0b00000000..Associated segment is accessible in supervisor mode only
 *  0b00000001..Associated segment is accessible in user or supervisor mode
 */
#define FTFA_SACCL0_SA(x) (((uint8_t)(((uint8_t)(x)) << FTFA_SACCL0_SA_SHIFT)) & FTFA_SACCL0_SA_MASK)
/*! @} */

/*! @name FACSS - Flash Access Segment Size Register */
/*! @{ */
#define FTFA_FACSS_SGSIZE_MASK (0xFFU)
#define FTFA_FACSS_SGSIZE_SHIFT (0U)
/*! SGSIZE - Segment Size
 */
#define FTFA_FACSS_SGSIZE(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FACSS_SGSIZE_SHIFT)) & FTFA_FACSS_SGSIZE_MASK)
/*! @} */

/*! @name FACSN - Flash Access Segment Number Register */
/*! @{ */
#define FTFA_FACSN_NUMSG_MASK (0xFFU)
#define FTFA_FACSN_NUMSG_SHIFT (0U)
/*! NUMSG - Number of Segments Indicator
 */
#define FTFA_FACSN_NUMSG(x) (((uint8_t)(((uint8_t)(x)) << FTFA_FACSN_NUMSG_SHIFT)) & FTFA_FACSN_NUMSG_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group FTFA_Register_Masks */

/* FTFA - Peripheral instance base addresses */
/** Peripheral FTFA base address */
#define FTFA_BASE (0x40020000u)
/** Peripheral FTFA base pointer */
#define FTFA ((FTFA_Type *)FTFA_BASE)
/** Array initializer of FTFA peripheral base addresses */
#define FTFA_BASE_ADDRS \
    {                   \
        FTFA_BASE       \
    }
/** Array initializer of FTFA peripheral base pointers */
#define FTFA_BASE_PTRS \
    {                  \
        FTFA           \
    }
/** Interrupt vectors for the FTFA peripheral type */
#define FTFA_COMMAND_COMPLETE_IRQS \
    {                              \
        FTFA_IRQn                  \
    }

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
typedef struct
{
    __IO uint32_t PDOR; /**< Port Data Output Register, offset: 0x0 */
    __O uint32_t PSOR;  /**< Port Set Output Register, offset: 0x4 */
    __O uint32_t PCOR;  /**< Port Clear Output Register, offset: 0x8 */
    __O uint32_t PTOR;  /**< Port Toggle Output Register, offset: 0xC */
    __I uint32_t PDIR;  /**< Port Data Input Register, offset: 0x10 */
    __IO uint32_t PDDR; /**< Port Data Direction Register, offset: 0x14 */
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
#define GPIO_PDOR_PDO_MASK (0xFFFFFFFFU)
#define GPIO_PDOR_PDO_SHIFT (0U)
/*! PDO - Port Data Output
 *  0b00000000000000000000000000000000..Logic level 0 is driven on pin, provided pin is configured for general-purpose
 * output. 0b00000000000000000000000000000001..Logic level 1 is driven on pin, provided pin is configured for
 * general-purpose output.
 */
#define GPIO_PDOR_PDO(x) (((uint32_t)(((uint32_t)(x)) << GPIO_PDOR_PDO_SHIFT)) & GPIO_PDOR_PDO_MASK)
/*! @} */

/*! @name PSOR - Port Set Output Register */
/*! @{ */
#define GPIO_PSOR_PTSO_MASK (0xFFFFFFFFU)
#define GPIO_PSOR_PTSO_SHIFT (0U)
/*! PTSO - Port Set Output
 *  0b00000000000000000000000000000000..Corresponding bit in PDORn does not change.
 *  0b00000000000000000000000000000001..Corresponding bit in PDORn is set to logic 1.
 */
#define GPIO_PSOR_PTSO(x) (((uint32_t)(((uint32_t)(x)) << GPIO_PSOR_PTSO_SHIFT)) & GPIO_PSOR_PTSO_MASK)
/*! @} */

/*! @name PCOR - Port Clear Output Register */
/*! @{ */
#define GPIO_PCOR_PTCO_MASK (0xFFFFFFFFU)
#define GPIO_PCOR_PTCO_SHIFT (0U)
/*! PTCO - Port Clear Output
 *  0b00000000000000000000000000000000..Corresponding bit in PDORn does not change.
 *  0b00000000000000000000000000000001..Corresponding bit in PDORn is cleared to logic 0.
 */
#define GPIO_PCOR_PTCO(x) (((uint32_t)(((uint32_t)(x)) << GPIO_PCOR_PTCO_SHIFT)) & GPIO_PCOR_PTCO_MASK)
/*! @} */

/*! @name PTOR - Port Toggle Output Register */
/*! @{ */
#define GPIO_PTOR_PTTO_MASK (0xFFFFFFFFU)
#define GPIO_PTOR_PTTO_SHIFT (0U)
/*! PTTO - Port Toggle Output
 *  0b00000000000000000000000000000000..Corresponding bit in PDORn does not change.
 *  0b00000000000000000000000000000001..Corresponding bit in PDORn is set to the inverse of its existing logic state.
 */
#define GPIO_PTOR_PTTO(x) (((uint32_t)(((uint32_t)(x)) << GPIO_PTOR_PTTO_SHIFT)) & GPIO_PTOR_PTTO_MASK)
/*! @} */

/*! @name PDIR - Port Data Input Register */
/*! @{ */
#define GPIO_PDIR_PDI_MASK (0xFFFFFFFFU)
#define GPIO_PDIR_PDI_SHIFT (0U)
/*! PDI - Port Data Input
 *  0b00000000000000000000000000000000..Pin logic level is logic 0, or is not configured for use by digital function.
 *  0b00000000000000000000000000000001..Pin logic level is logic 1.
 */
#define GPIO_PDIR_PDI(x) (((uint32_t)(((uint32_t)(x)) << GPIO_PDIR_PDI_SHIFT)) & GPIO_PDIR_PDI_MASK)
/*! @} */

/*! @name PDDR - Port Data Direction Register */
/*! @{ */
#define GPIO_PDDR_PDD_MASK (0xFFFFFFFFU)
#define GPIO_PDDR_PDD_SHIFT (0U)
/*! PDD - Port Data Direction
 *  0b00000000000000000000000000000000..Pin is configured as general-purpose input, for the GPIO function.
 *  0b00000000000000000000000000000001..Pin is configured as general-purpose output, for the GPIO function.
 */
#define GPIO_PDDR_PDD(x) (((uint32_t)(((uint32_t)(x)) << GPIO_PDDR_PDD_SHIFT)) & GPIO_PDDR_PDD_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group GPIO_Register_Masks */

/* GPIO - Peripheral instance base addresses */
/** Peripheral GPIOA base address */
#define GPIOA_BASE (0x4000F000u)
/** Peripheral GPIOA base pointer */
#define GPIOA ((GPIO_Type *)GPIOA_BASE)
/** Peripheral GPIOB base address */
#define GPIOB_BASE (0x4000F040u)
/** Peripheral GPIOB base pointer */
#define GPIOB ((GPIO_Type *)GPIOB_BASE)
/** Peripheral GPIOC base address */
#define GPIOC_BASE (0x4000F080u)
/** Peripheral GPIOC base pointer */
#define GPIOC ((GPIO_Type *)GPIOC_BASE)
/** Peripheral GPIOD base address */
#define GPIOD_BASE (0x4000F0C0u)
/** Peripheral GPIOD base pointer */
#define GPIOD ((GPIO_Type *)GPIOD_BASE)
/** Peripheral GPIOE base address */
#define GPIOE_BASE (0x4000F100u)
/** Peripheral GPIOE base pointer */
#define GPIOE ((GPIO_Type *)GPIOE_BASE)
/** Array initializer of GPIO peripheral base addresses */
#define GPIO_BASE_ADDRS                                            \
    {                                                              \
        GPIOA_BASE, GPIOB_BASE, GPIOC_BASE, GPIOD_BASE, GPIOE_BASE \
    }
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                    \
    {                                     \
        GPIOA, GPIOB, GPIOC, GPIOD, GPIOE \
    }

/*!
 * @}
 */ /* end of group GPIO_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- INTMUX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup INTMUX_Peripheral_Access_Layer INTMUX Peripheral Access Layer
 * @{
 */

/** INTMUX - Register Layout Typedef */
typedef struct
{
    struct
    {                          /* offset: 0x0, array step: 0x40 */
        __IO uint32_t CHn_CSR; /**< Channel n Control Status Register, array offset: 0x0, array step: 0x40 */
        __I uint32_t CHn_VEC;  /**< Channel n Vector Number Register, array offset: 0x4, array step: 0x40 */
        uint8_t RESERVED_0[8];
        __IO uint32_t CHn_IER_31_0; /**< Channel n Interrupt Enable Register, array offset: 0x10, array step: 0x40 */
        uint8_t RESERVED_1[12];
        __I uint32_t CHn_IPR_31_0; /**< Channel n Interrupt Pending Register, array offset: 0x20, array step: 0x40 */
        uint8_t RESERVED_2[28];
    } CHANNEL[4];
} INTMUX_Type;

/* ----------------------------------------------------------------------------
   -- INTMUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup INTMUX_Register_Masks INTMUX Register Masks
 * @{
 */

/*! @name CHn_CSR - Channel n Control Status Register */
/*! @{ */
#define INTMUX_CHn_CSR_RST_MASK (0x1U)
#define INTMUX_CHn_CSR_RST_SHIFT (0U)
/*! RST - Software Reset
 *  0b0..No operation.
 *  0b1..Perform a software reset on this channel.
 */
#define INTMUX_CHn_CSR_RST(x) (((uint32_t)(((uint32_t)(x)) << INTMUX_CHn_CSR_RST_SHIFT)) & INTMUX_CHn_CSR_RST_MASK)
#define INTMUX_CHn_CSR_AND_MASK (0x2U)
#define INTMUX_CHn_CSR_AND_SHIFT (1U)
/*! AND - Logic AND
 *  0b0..Logic OR all enabled interrupt inputs.
 *  0b1..Logic AND all enabled interrupt inputs.
 */
#define INTMUX_CHn_CSR_AND(x) (((uint32_t)(((uint32_t)(x)) << INTMUX_CHn_CSR_AND_SHIFT)) & INTMUX_CHn_CSR_AND_MASK)
#define INTMUX_CHn_CSR_IRQN_MASK (0x30U)
#define INTMUX_CHn_CSR_IRQN_SHIFT (4U)
/*! IRQN - Channel Input Number
 *  0b00..32 interrupt inputs
 *  0b01..Reserved
 *  0b10..Reserved
 *  0b11..Reserved
 */
#define INTMUX_CHn_CSR_IRQN(x) (((uint32_t)(((uint32_t)(x)) << INTMUX_CHn_CSR_IRQN_SHIFT)) & INTMUX_CHn_CSR_IRQN_MASK)
#define INTMUX_CHn_CSR_CHIN_MASK (0xF00U)
#define INTMUX_CHn_CSR_CHIN_SHIFT (8U)
/*! CHIN - Channel Instance Number
 */
#define INTMUX_CHn_CSR_CHIN(x) (((uint32_t)(((uint32_t)(x)) << INTMUX_CHn_CSR_CHIN_SHIFT)) & INTMUX_CHn_CSR_CHIN_MASK)
#define INTMUX_CHn_CSR_IRQP_MASK (0x80000000U)
#define INTMUX_CHn_CSR_IRQP_SHIFT (31U)
/*! IRQP - Channel Interrupt Request Pending
 *  0b0..No interrupt is pending.
 *  0b1..The interrupt output of this channel is pending.
 */
#define INTMUX_CHn_CSR_IRQP(x) (((uint32_t)(((uint32_t)(x)) << INTMUX_CHn_CSR_IRQP_SHIFT)) & INTMUX_CHn_CSR_IRQP_MASK)
/*! @} */

/* The count of INTMUX_CHn_CSR */
#define INTMUX_CHn_CSR_COUNT (4U)

/*! @name CHn_VEC - Channel n Vector Number Register */
/*! @{ */
#define INTMUX_CHn_VEC_VECN_MASK (0x3FFCU)
#define INTMUX_CHn_VEC_VECN_SHIFT (2U)
/*! VECN - Vector Number
 */
#define INTMUX_CHn_VEC_VECN(x) (((uint32_t)(((uint32_t)(x)) << INTMUX_CHn_VEC_VECN_SHIFT)) & INTMUX_CHn_VEC_VECN_MASK)
/*! @} */

/* The count of INTMUX_CHn_VEC */
#define INTMUX_CHn_VEC_COUNT (4U)

/*! @name CHn_IER_31_0 - Channel n Interrupt Enable Register */
/*! @{ */
#define INTMUX_CHn_IER_31_0_INTE_MASK (0xFFFFFFFFU)
#define INTMUX_CHn_IER_31_0_INTE_SHIFT (0U)
/*! INTE - Interrupt Enable
 *  0b00000000000000000000000000000000..Interrupt is disabled.
 *  0b00000000000000000000000000000001..Interrupt is enabled.
 */
#define INTMUX_CHn_IER_31_0_INTE(x) \
    (((uint32_t)(((uint32_t)(x)) << INTMUX_CHn_IER_31_0_INTE_SHIFT)) & INTMUX_CHn_IER_31_0_INTE_MASK)
/*! @} */

/* The count of INTMUX_CHn_IER_31_0 */
#define INTMUX_CHn_IER_31_0_COUNT (4U)

/*! @name CHn_IPR_31_0 - Channel n Interrupt Pending Register */
/*! @{ */
#define INTMUX_CHn_IPR_31_0_INTP_MASK (0xFFFFFFFFU)
#define INTMUX_CHn_IPR_31_0_INTP_SHIFT (0U)
/*! INTP - Interrupt Pending
 *  0b00000000000000000000000000000000..No interrupt.
 *  0b00000000000000000000000000000001..Interrupt is pending.
 */
#define INTMUX_CHn_IPR_31_0_INTP(x) \
    (((uint32_t)(((uint32_t)(x)) << INTMUX_CHn_IPR_31_0_INTP_SHIFT)) & INTMUX_CHn_IPR_31_0_INTP_MASK)
/*! @} */

/* The count of INTMUX_CHn_IPR_31_0 */
#define INTMUX_CHn_IPR_31_0_COUNT (4U)

/*!
 * @}
 */ /* end of group INTMUX_Register_Masks */

/* INTMUX - Peripheral instance base addresses */
/** Peripheral INTMUX0 base address */
#define INTMUX0_BASE (0x40024000u)
/** Peripheral INTMUX0 base pointer */
#define INTMUX0 ((INTMUX_Type *)INTMUX0_BASE)
/** Array initializer of INTMUX peripheral base addresses */
#define INTMUX_BASE_ADDRS \
    {                     \
        INTMUX0_BASE      \
    }
/** Array initializer of INTMUX peripheral base pointers */
#define INTMUX_BASE_PTRS \
    {                    \
        INTMUX0          \
    }
/** Interrupt vectors for the INTMUX peripheral type */
#define INTMUX_IRQS                                                        \
    {                                                                      \
        {                                                                  \
            INTMUX0_0_IRQn, INTMUX0_1_IRQn, INTMUX0_2_IRQn, INTMUX0_3_IRQn \
        }                                                                  \
    }

/*!
 * @}
 */ /* end of group INTMUX_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- LLWU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Peripheral_Access_Layer LLWU Peripheral Access Layer
 * @{
 */

/** LLWU - Register Layout Typedef */
typedef struct
{
    __I uint32_t VERID; /**< Version ID Register, offset: 0x0 */
    __I uint32_t PARAM; /**< Parameter Register, offset: 0x4 */
    __IO uint32_t PE1;  /**< LLWU Pin Enable 1 register, offset: 0x8 */
    __IO uint32_t PE2;  /**< LLWU Pin Enable 2 register, offset: 0xC */
    uint8_t RESERVED_0[8];
    __IO uint32_t ME; /**< LLWU Module Interrupt Enable register, offset: 0x18 */
    __IO uint32_t DE; /**< LLWU Module DMA Enable register, offset: 0x1C */
    __IO uint32_t PF; /**< LLWU Pin Flag register, offset: 0x20 */
    uint8_t RESERVED_1[4];
    __I uint32_t MF; /**< LLWU Module Interrupt Flag register, offset: 0x28 */
    uint8_t RESERVED_2[4];
    __IO uint32_t FILT; /**< LLWU Pin Filter register, offset: 0x30 */
} LLWU_Type;

/* ----------------------------------------------------------------------------
   -- LLWU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Register_Masks LLWU Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */
#define LLWU_VERID_FEATURE_MASK (0xFFFFU)
#define LLWU_VERID_FEATURE_SHIFT (0U)
/*! FEATURE - Feature Specification Number
 *  0b0000000000000000..Standard features implemented
 */
#define LLWU_VERID_FEATURE(x) (((uint32_t)(((uint32_t)(x)) << LLWU_VERID_FEATURE_SHIFT)) & LLWU_VERID_FEATURE_MASK)
#define LLWU_VERID_MINOR_MASK (0xFF0000U)
#define LLWU_VERID_MINOR_SHIFT (16U)
/*! MINOR - Minor Version Number
 */
#define LLWU_VERID_MINOR(x) (((uint32_t)(((uint32_t)(x)) << LLWU_VERID_MINOR_SHIFT)) & LLWU_VERID_MINOR_MASK)
#define LLWU_VERID_MAJOR_MASK (0xFF000000U)
#define LLWU_VERID_MAJOR_SHIFT (24U)
/*! MAJOR - Major Version Number
 */
#define LLWU_VERID_MAJOR(x) (((uint32_t)(((uint32_t)(x)) << LLWU_VERID_MAJOR_SHIFT)) & LLWU_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */
#define LLWU_PARAM_FILTERS_MASK (0xFFU)
#define LLWU_PARAM_FILTERS_SHIFT (0U)
/*! FILTERS - Filter Number
 */
#define LLWU_PARAM_FILTERS(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PARAM_FILTERS_SHIFT)) & LLWU_PARAM_FILTERS_MASK)
#define LLWU_PARAM_DMAS_MASK (0xFF00U)
#define LLWU_PARAM_DMAS_SHIFT (8U)
/*! DMAS - DMA Number
 */
#define LLWU_PARAM_DMAS(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PARAM_DMAS_SHIFT)) & LLWU_PARAM_DMAS_MASK)
#define LLWU_PARAM_MODULES_MASK (0xFF0000U)
#define LLWU_PARAM_MODULES_SHIFT (16U)
/*! MODULES - Module Number
 */
#define LLWU_PARAM_MODULES(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PARAM_MODULES_SHIFT)) & LLWU_PARAM_MODULES_MASK)
#define LLWU_PARAM_PINS_MASK (0xFF000000U)
#define LLWU_PARAM_PINS_SHIFT (24U)
/*! PINS - Pin Number
 */
#define LLWU_PARAM_PINS(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PARAM_PINS_SHIFT)) & LLWU_PARAM_PINS_MASK)
/*! @} */

/*! @name PE1 - LLWU Pin Enable 1 register */
/*! @{ */
#define LLWU_PE1_WUPE0_MASK (0x3U)
#define LLWU_PE1_WUPE0_SHIFT (0U)
/*! WUPE0 - Wakeup Pin Enable For LLWU_P0
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE0(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE0_SHIFT)) & LLWU_PE1_WUPE0_MASK)
#define LLWU_PE1_WUPE1_MASK (0xCU)
#define LLWU_PE1_WUPE1_SHIFT (2U)
/*! WUPE1 - Wakeup Pin Enable For LLWU_P1
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE1(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE1_SHIFT)) & LLWU_PE1_WUPE1_MASK)
#define LLWU_PE1_WUPE2_MASK (0x30U)
#define LLWU_PE1_WUPE2_SHIFT (4U)
/*! WUPE2 - Wakeup Pin Enable For LLWU_P2
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE2(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE2_SHIFT)) & LLWU_PE1_WUPE2_MASK)
#define LLWU_PE1_WUPE3_MASK (0xC0U)
#define LLWU_PE1_WUPE3_SHIFT (6U)
/*! WUPE3 - Wakeup Pin Enable For LLWU_P3
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE3(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE3_SHIFT)) & LLWU_PE1_WUPE3_MASK)
#define LLWU_PE1_WUPE4_MASK (0x300U)
#define LLWU_PE1_WUPE4_SHIFT (8U)
/*! WUPE4 - Wakeup Pin Enable For LLWU_P4
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE4(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE4_SHIFT)) & LLWU_PE1_WUPE4_MASK)
#define LLWU_PE1_WUPE5_MASK (0xC00U)
#define LLWU_PE1_WUPE5_SHIFT (10U)
/*! WUPE5 - Wakeup Pin Enable For LLWU_P5
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE5(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE5_SHIFT)) & LLWU_PE1_WUPE5_MASK)
#define LLWU_PE1_WUPE6_MASK (0x3000U)
#define LLWU_PE1_WUPE6_SHIFT (12U)
/*! WUPE6 - Wakeup Pin Enable For LLWU_P6
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE6(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE6_SHIFT)) & LLWU_PE1_WUPE6_MASK)
#define LLWU_PE1_WUPE7_MASK (0xC000U)
#define LLWU_PE1_WUPE7_SHIFT (14U)
/*! WUPE7 - Wakeup Pin Enable For LLWU_P7
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE7(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE7_SHIFT)) & LLWU_PE1_WUPE7_MASK)
#define LLWU_PE1_WUPE8_MASK (0x30000U)
#define LLWU_PE1_WUPE8_SHIFT (16U)
/*! WUPE8 - Wakeup Pin Enable For LLWU_P8
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE8(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE8_SHIFT)) & LLWU_PE1_WUPE8_MASK)
#define LLWU_PE1_WUPE9_MASK (0xC0000U)
#define LLWU_PE1_WUPE9_SHIFT (18U)
/*! WUPE9 - Wakeup Pin Enable For LLWU_P9
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE9(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE9_SHIFT)) & LLWU_PE1_WUPE9_MASK)
#define LLWU_PE1_WUPE10_MASK (0x300000U)
#define LLWU_PE1_WUPE10_SHIFT (20U)
/*! WUPE10 - Wakeup Pin Enable For LLWU_P10
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE10(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE10_SHIFT)) & LLWU_PE1_WUPE10_MASK)
#define LLWU_PE1_WUPE11_MASK (0xC00000U)
#define LLWU_PE1_WUPE11_SHIFT (22U)
/*! WUPE11 - Wakeup Pin Enable For LLWU_P11
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE11(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE11_SHIFT)) & LLWU_PE1_WUPE11_MASK)
#define LLWU_PE1_WUPE12_MASK (0x3000000U)
#define LLWU_PE1_WUPE12_SHIFT (24U)
/*! WUPE12 - Wakeup Pin Enable For LLWU_P12
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE12(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE12_SHIFT)) & LLWU_PE1_WUPE12_MASK)
#define LLWU_PE1_WUPE13_MASK (0xC000000U)
#define LLWU_PE1_WUPE13_SHIFT (26U)
/*! WUPE13 - Wakeup Pin Enable For LLWU_P13
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE13(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE13_SHIFT)) & LLWU_PE1_WUPE13_MASK)
#define LLWU_PE1_WUPE14_MASK (0x30000000U)
#define LLWU_PE1_WUPE14_SHIFT (28U)
/*! WUPE14 - Wakeup Pin Enable For LLWU_P14
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE14(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE14_SHIFT)) & LLWU_PE1_WUPE14_MASK)
#define LLWU_PE1_WUPE15_MASK (0xC0000000U)
#define LLWU_PE1_WUPE15_SHIFT (30U)
/*! WUPE15 - Wakeup Pin Enable For LLWU_P15
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE15(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE1_WUPE15_SHIFT)) & LLWU_PE1_WUPE15_MASK)
/*! @} */

/*! @name PE2 - LLWU Pin Enable 2 register */
/*! @{ */
#define LLWU_PE2_WUPE16_MASK (0x3U)
#define LLWU_PE2_WUPE16_SHIFT (0U)
/*! WUPE16 - Wakeup Pin Enable For LLWU_P16
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE16(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE16_SHIFT)) & LLWU_PE2_WUPE16_MASK)
#define LLWU_PE2_WUPE17_MASK (0xCU)
#define LLWU_PE2_WUPE17_SHIFT (2U)
/*! WUPE17 - Wakeup Pin Enable For LLWU_P17
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE17(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE17_SHIFT)) & LLWU_PE2_WUPE17_MASK)
#define LLWU_PE2_WUPE18_MASK (0x30U)
#define LLWU_PE2_WUPE18_SHIFT (4U)
/*! WUPE18 - Wakeup Pin Enable For LLWU_P18
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE18(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE18_SHIFT)) & LLWU_PE2_WUPE18_MASK)
#define LLWU_PE2_WUPE19_MASK (0xC0U)
#define LLWU_PE2_WUPE19_SHIFT (6U)
/*! WUPE19 - Wakeup Pin Enable For LLWU_P19
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE19(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE19_SHIFT)) & LLWU_PE2_WUPE19_MASK)
#define LLWU_PE2_WUPE20_MASK (0x300U)
#define LLWU_PE2_WUPE20_SHIFT (8U)
/*! WUPE20 - Wakeup Pin Enable For LLWU_P20
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE20(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE20_SHIFT)) & LLWU_PE2_WUPE20_MASK)
#define LLWU_PE2_WUPE21_MASK (0xC00U)
#define LLWU_PE2_WUPE21_SHIFT (10U)
/*! WUPE21 - Wakeup Pin Enable For LLWU_P21
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE21(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE21_SHIFT)) & LLWU_PE2_WUPE21_MASK)
#define LLWU_PE2_WUPE22_MASK (0x3000U)
#define LLWU_PE2_WUPE22_SHIFT (12U)
/*! WUPE22 - Wakeup Pin Enable For LLWU_P22
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE22(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE22_SHIFT)) & LLWU_PE2_WUPE22_MASK)
#define LLWU_PE2_WUPE23_MASK (0xC000U)
#define LLWU_PE2_WUPE23_SHIFT (14U)
/*! WUPE23 - Wakeup Pin Enable For LLWU_P23
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE23(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE23_SHIFT)) & LLWU_PE2_WUPE23_MASK)
#define LLWU_PE2_WUPE24_MASK (0x30000U)
#define LLWU_PE2_WUPE24_SHIFT (16U)
/*! WUPE24 - Wakeup Pin Enable For LLWU_P24
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE24(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE24_SHIFT)) & LLWU_PE2_WUPE24_MASK)
#define LLWU_PE2_WUPE25_MASK (0xC0000U)
#define LLWU_PE2_WUPE25_SHIFT (18U)
/*! WUPE25 - Wakeup Pin Enable For LLWU_P25
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE25(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE25_SHIFT)) & LLWU_PE2_WUPE25_MASK)
#define LLWU_PE2_WUPE26_MASK (0x300000U)
#define LLWU_PE2_WUPE26_SHIFT (20U)
/*! WUPE26 - Wakeup Pin Enable For LLWU_P26
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE26(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE26_SHIFT)) & LLWU_PE2_WUPE26_MASK)
#define LLWU_PE2_WUPE27_MASK (0xC00000U)
#define LLWU_PE2_WUPE27_SHIFT (22U)
/*! WUPE27 - Wakeup Pin Enable For LLWU_P27
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE27(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE27_SHIFT)) & LLWU_PE2_WUPE27_MASK)
#define LLWU_PE2_WUPE28_MASK (0x3000000U)
#define LLWU_PE2_WUPE28_SHIFT (24U)
/*! WUPE28 - Wakeup Pin Enable For LLWU_P28
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE28(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE28_SHIFT)) & LLWU_PE2_WUPE28_MASK)
#define LLWU_PE2_WUPE29_MASK (0xC000000U)
#define LLWU_PE2_WUPE29_SHIFT (26U)
/*! WUPE29 - Wakeup Pin Enable For LLWU_P29
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE29(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE29_SHIFT)) & LLWU_PE2_WUPE29_MASK)
#define LLWU_PE2_WUPE30_MASK (0x30000000U)
#define LLWU_PE2_WUPE30_SHIFT (28U)
/*! WUPE30 - Wakeup Pin Enable For LLWU_P30
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE30(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE30_SHIFT)) & LLWU_PE2_WUPE30_MASK)
#define LLWU_PE2_WUPE31_MASK (0xC0000000U)
#define LLWU_PE2_WUPE31_SHIFT (30U)
/*! WUPE31 - Wakeup Pin Enable For LLWU_P31
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE31(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PE2_WUPE31_SHIFT)) & LLWU_PE2_WUPE31_MASK)
/*! @} */

/*! @name ME - LLWU Module Interrupt Enable register */
/*! @{ */
#define LLWU_ME_WUME0_MASK (0x1U)
#define LLWU_ME_WUME0_SHIFT (0U)
/*! WUME0 - Wakeup Module Enable For Module 0
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME0(x) (((uint32_t)(((uint32_t)(x)) << LLWU_ME_WUME0_SHIFT)) & LLWU_ME_WUME0_MASK)
#define LLWU_ME_WUME1_MASK (0x2U)
#define LLWU_ME_WUME1_SHIFT (1U)
/*! WUME1 - Wakeup Module Enable for Module 1
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME1(x) (((uint32_t)(((uint32_t)(x)) << LLWU_ME_WUME1_SHIFT)) & LLWU_ME_WUME1_MASK)
#define LLWU_ME_WUME2_MASK (0x4U)
#define LLWU_ME_WUME2_SHIFT (2U)
/*! WUME2 - Wakeup Module Enable For Module 2
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME2(x) (((uint32_t)(((uint32_t)(x)) << LLWU_ME_WUME2_SHIFT)) & LLWU_ME_WUME2_MASK)
#define LLWU_ME_WUME3_MASK (0x8U)
#define LLWU_ME_WUME3_SHIFT (3U)
/*! WUME3 - Wakeup Module Enable For Module 3
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME3(x) (((uint32_t)(((uint32_t)(x)) << LLWU_ME_WUME3_SHIFT)) & LLWU_ME_WUME3_MASK)
#define LLWU_ME_WUME4_MASK (0x10U)
#define LLWU_ME_WUME4_SHIFT (4U)
/*! WUME4 - Wakeup Module Enable For Module 4
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME4(x) (((uint32_t)(((uint32_t)(x)) << LLWU_ME_WUME4_SHIFT)) & LLWU_ME_WUME4_MASK)
#define LLWU_ME_WUME5_MASK (0x20U)
#define LLWU_ME_WUME5_SHIFT (5U)
/*! WUME5 - Wakeup Module Enable For Module 5
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME5(x) (((uint32_t)(((uint32_t)(x)) << LLWU_ME_WUME5_SHIFT)) & LLWU_ME_WUME5_MASK)
#define LLWU_ME_WUME6_MASK (0x40U)
#define LLWU_ME_WUME6_SHIFT (6U)
/*! WUME6 - Wakeup Module Enable For Module 6
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME6(x) (((uint32_t)(((uint32_t)(x)) << LLWU_ME_WUME6_SHIFT)) & LLWU_ME_WUME6_MASK)
#define LLWU_ME_WUME7_MASK (0x80U)
#define LLWU_ME_WUME7_SHIFT (7U)
/*! WUME7 - Wakeup Module Enable For Module 7
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME7(x) (((uint32_t)(((uint32_t)(x)) << LLWU_ME_WUME7_SHIFT)) & LLWU_ME_WUME7_MASK)
/*! @} */

/*! @name DE - LLWU Module DMA Enable register */
/*! @{ */
#define LLWU_DE_WUDE0_MASK (0x1U)
#define LLWU_DE_WUDE0_SHIFT (0U)
/*! WUDE0 - DMA Wakeup Enable For Module 0
 *  0b0..Internal module request not used as a DMA wakeup source
 *  0b1..Internal module request used as a DMA wakeup source
 */
#define LLWU_DE_WUDE0(x) (((uint32_t)(((uint32_t)(x)) << LLWU_DE_WUDE0_SHIFT)) & LLWU_DE_WUDE0_MASK)
#define LLWU_DE_WUDE1_MASK (0x2U)
#define LLWU_DE_WUDE1_SHIFT (1U)
/*! WUDE1 - DMA Wakeup Enable for Module 1
 *  0b0..Internal module request not used as a DMA wakeup source
 *  0b1..Internal module request used as a DMA wakeup source
 */
#define LLWU_DE_WUDE1(x) (((uint32_t)(((uint32_t)(x)) << LLWU_DE_WUDE1_SHIFT)) & LLWU_DE_WUDE1_MASK)
#define LLWU_DE_WUDE2_MASK (0x4U)
#define LLWU_DE_WUDE2_SHIFT (2U)
/*! WUDE2 - DMA Wakeup Enable For Module 2
 *  0b0..Internal module request not used as a DMA wakeup source
 *  0b1..Internal module request used as a DMA wakeup source
 */
#define LLWU_DE_WUDE2(x) (((uint32_t)(((uint32_t)(x)) << LLWU_DE_WUDE2_SHIFT)) & LLWU_DE_WUDE2_MASK)
#define LLWU_DE_WUDE3_MASK (0x8U)
#define LLWU_DE_WUDE3_SHIFT (3U)
/*! WUDE3 - DMA Wakeup Enable For Module 3
 *  0b0..Internal module request not used as a DMA wakeup source
 *  0b1..Internal module request used as a DMA wakeup source
 */
#define LLWU_DE_WUDE3(x) (((uint32_t)(((uint32_t)(x)) << LLWU_DE_WUDE3_SHIFT)) & LLWU_DE_WUDE3_MASK)
#define LLWU_DE_WUDE4_MASK (0x10U)
#define LLWU_DE_WUDE4_SHIFT (4U)
/*! WUDE4 - DMA Wakeup Enable For Module 4
 *  0b0..Internal module request not used as a DMA wakeup source
 *  0b1..Internal module request used as a DMA wakeup source
 */
#define LLWU_DE_WUDE4(x) (((uint32_t)(((uint32_t)(x)) << LLWU_DE_WUDE4_SHIFT)) & LLWU_DE_WUDE4_MASK)
#define LLWU_DE_WUDE5_MASK (0x20U)
#define LLWU_DE_WUDE5_SHIFT (5U)
/*! WUDE5 - DMA Wakeup Enable For Module 5
 *  0b0..Internal module request not used as a DMA wakeup source
 *  0b1..Internal module request used as a DMA wakeup source
 */
#define LLWU_DE_WUDE5(x) (((uint32_t)(((uint32_t)(x)) << LLWU_DE_WUDE5_SHIFT)) & LLWU_DE_WUDE5_MASK)
#define LLWU_DE_WUDE6_MASK (0x40U)
#define LLWU_DE_WUDE6_SHIFT (6U)
/*! WUDE6 - DMA Wakeup Enable For Module 6
 *  0b0..Internal module request not used as a DMA wakeup source
 *  0b1..Internal module request used as a DMA wakeup source
 */
#define LLWU_DE_WUDE6(x) (((uint32_t)(((uint32_t)(x)) << LLWU_DE_WUDE6_SHIFT)) & LLWU_DE_WUDE6_MASK)
#define LLWU_DE_WUDE7_MASK (0x80U)
#define LLWU_DE_WUDE7_SHIFT (7U)
/*! WUDE7 - DMA Wakeup Enable For Module 7
 *  0b0..Internal module request not used as a DMA wakeup source
 *  0b1..Internal module request used as a DMA wakeup source
 */
#define LLWU_DE_WUDE7(x) (((uint32_t)(((uint32_t)(x)) << LLWU_DE_WUDE7_SHIFT)) & LLWU_DE_WUDE7_MASK)
/*! @} */

/*! @name PF - LLWU Pin Flag register */
/*! @{ */
#define LLWU_PF_WUF0_MASK (0x1U)
#define LLWU_PF_WUF0_SHIFT (0U)
/*! WUF0 - Wakeup Flag For LLWU_P0
 *  0b0..LLWU_P0 input was not a wakeup source
 *  0b1..LLWU_P0 input was a wakeup source
 */
#define LLWU_PF_WUF0(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF0_SHIFT)) & LLWU_PF_WUF0_MASK)
#define LLWU_PF_WUF1_MASK (0x2U)
#define LLWU_PF_WUF1_SHIFT (1U)
/*! WUF1 - Wakeup Flag For LLWU_P1
 *  0b0..LLWU_P1 input was not a wakeup source
 *  0b1..LLWU_P1 input was a wakeup source
 */
#define LLWU_PF_WUF1(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF1_SHIFT)) & LLWU_PF_WUF1_MASK)
#define LLWU_PF_WUF2_MASK (0x4U)
#define LLWU_PF_WUF2_SHIFT (2U)
/*! WUF2 - Wakeup Flag For LLWU_P2
 *  0b0..LLWU_P2 input was not a wakeup source
 *  0b1..LLWU_P2 input was a wakeup source
 */
#define LLWU_PF_WUF2(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF2_SHIFT)) & LLWU_PF_WUF2_MASK)
#define LLWU_PF_WUF3_MASK (0x8U)
#define LLWU_PF_WUF3_SHIFT (3U)
/*! WUF3 - Wakeup Flag For LLWU_P3
 *  0b0..LLWU_P3 input was not a wakeup source
 *  0b1..LLWU_P3 input was a wakeup source
 */
#define LLWU_PF_WUF3(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF3_SHIFT)) & LLWU_PF_WUF3_MASK)
#define LLWU_PF_WUF4_MASK (0x10U)
#define LLWU_PF_WUF4_SHIFT (4U)
/*! WUF4 - Wakeup Flag For LLWU_P4
 *  0b0..LLWU_P4 input was not a wakeup source
 *  0b1..LLWU_P4 input was a wakeup source
 */
#define LLWU_PF_WUF4(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF4_SHIFT)) & LLWU_PF_WUF4_MASK)
#define LLWU_PF_WUF5_MASK (0x20U)
#define LLWU_PF_WUF5_SHIFT (5U)
/*! WUF5 - Wakeup Flag For LLWU_P5
 *  0b0..LLWU_P5 input was not a wakeup source
 *  0b1..LLWU_P5 input was a wakeup source
 */
#define LLWU_PF_WUF5(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF5_SHIFT)) & LLWU_PF_WUF5_MASK)
#define LLWU_PF_WUF6_MASK (0x40U)
#define LLWU_PF_WUF6_SHIFT (6U)
/*! WUF6 - Wakeup Flag For LLWU_P6
 *  0b0..LLWU_P6 input was not a wakeup source
 *  0b1..LLWU_P6 input was a wakeup source
 */
#define LLWU_PF_WUF6(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF6_SHIFT)) & LLWU_PF_WUF6_MASK)
#define LLWU_PF_WUF7_MASK (0x80U)
#define LLWU_PF_WUF7_SHIFT (7U)
/*! WUF7 - Wakeup Flag For LLWU_P7
 *  0b0..LLWU_P7 input was not a wakeup source
 *  0b1..LLWU_P7 input was a wakeup source
 */
#define LLWU_PF_WUF7(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF7_SHIFT)) & LLWU_PF_WUF7_MASK)
#define LLWU_PF_WUF8_MASK (0x100U)
#define LLWU_PF_WUF8_SHIFT (8U)
/*! WUF8 - Wakeup Flag For LLWU_P8
 *  0b0..LLWU_P8 input was not a wakeup source
 *  0b1..LLWU_P8 input was a wakeup source
 */
#define LLWU_PF_WUF8(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF8_SHIFT)) & LLWU_PF_WUF8_MASK)
#define LLWU_PF_WUF9_MASK (0x200U)
#define LLWU_PF_WUF9_SHIFT (9U)
/*! WUF9 - Wakeup Flag For LLWU_P9
 *  0b0..LLWU_P9 input was not a wakeup source
 *  0b1..LLWU_P9 input was a wakeup source
 */
#define LLWU_PF_WUF9(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF9_SHIFT)) & LLWU_PF_WUF9_MASK)
#define LLWU_PF_WUF10_MASK (0x400U)
#define LLWU_PF_WUF10_SHIFT (10U)
/*! WUF10 - Wakeup Flag For LLWU_P10
 *  0b0..LLWU_P10 input was not a wakeup source
 *  0b1..LLWU_P10 input was a wakeup source
 */
#define LLWU_PF_WUF10(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF10_SHIFT)) & LLWU_PF_WUF10_MASK)
#define LLWU_PF_WUF11_MASK (0x800U)
#define LLWU_PF_WUF11_SHIFT (11U)
/*! WUF11 - Wakeup Flag For LLWU_P11
 *  0b0..LLWU_P11 input was not a wakeup source
 *  0b1..LLWU_P11 input was a wakeup source
 */
#define LLWU_PF_WUF11(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF11_SHIFT)) & LLWU_PF_WUF11_MASK)
#define LLWU_PF_WUF12_MASK (0x1000U)
#define LLWU_PF_WUF12_SHIFT (12U)
/*! WUF12 - Wakeup Flag For LLWU_P12
 *  0b0..LLWU_P12 input was not a wakeup source
 *  0b1..LLWU_P12 input was a wakeup source
 */
#define LLWU_PF_WUF12(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF12_SHIFT)) & LLWU_PF_WUF12_MASK)
#define LLWU_PF_WUF13_MASK (0x2000U)
#define LLWU_PF_WUF13_SHIFT (13U)
/*! WUF13 - Wakeup Flag For LLWU_P13
 *  0b0..LLWU_P13 input was not a wakeup source
 *  0b1..LLWU_P13 input was a wakeup source
 */
#define LLWU_PF_WUF13(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF13_SHIFT)) & LLWU_PF_WUF13_MASK)
#define LLWU_PF_WUF14_MASK (0x4000U)
#define LLWU_PF_WUF14_SHIFT (14U)
/*! WUF14 - Wakeup Flag For LLWU_P14
 *  0b0..LLWU_P14 input was not a wakeup source
 *  0b1..LLWU_P14 input was a wakeup source
 */
#define LLWU_PF_WUF14(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF14_SHIFT)) & LLWU_PF_WUF14_MASK)
#define LLWU_PF_WUF15_MASK (0x8000U)
#define LLWU_PF_WUF15_SHIFT (15U)
/*! WUF15 - Wakeup Flag For LLWU_P15
 *  0b0..LLWU_P15 input was not a wakeup source
 *  0b1..LLWU_P15 input was a wakeup source
 */
#define LLWU_PF_WUF15(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF15_SHIFT)) & LLWU_PF_WUF15_MASK)
#define LLWU_PF_WUF16_MASK (0x10000U)
#define LLWU_PF_WUF16_SHIFT (16U)
/*! WUF16 - Wakeup Flag For LLWU_P16
 *  0b0..LLWU_P16 input was not a wakeup source
 *  0b1..LLWU_P16 input was a wakeup source
 */
#define LLWU_PF_WUF16(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF16_SHIFT)) & LLWU_PF_WUF16_MASK)
#define LLWU_PF_WUF17_MASK (0x20000U)
#define LLWU_PF_WUF17_SHIFT (17U)
/*! WUF17 - Wakeup Flag For LLWU_P17
 *  0b0..LLWU_P17 input was not a wakeup source
 *  0b1..LLWU_P17 input was a wakeup source
 */
#define LLWU_PF_WUF17(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF17_SHIFT)) & LLWU_PF_WUF17_MASK)
#define LLWU_PF_WUF18_MASK (0x40000U)
#define LLWU_PF_WUF18_SHIFT (18U)
/*! WUF18 - Wakeup Flag For LLWU_P18
 *  0b0..LLWU_P18 input was not a wakeup source
 *  0b1..LLWU_P18 input was a wakeup source
 */
#define LLWU_PF_WUF18(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF18_SHIFT)) & LLWU_PF_WUF18_MASK)
#define LLWU_PF_WUF19_MASK (0x80000U)
#define LLWU_PF_WUF19_SHIFT (19U)
/*! WUF19 - Wakeup Flag For LLWU_P19
 *  0b0..LLWU_P19 input was not a wakeup source
 *  0b1..LLWU_P19 input was a wakeup source
 */
#define LLWU_PF_WUF19(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF19_SHIFT)) & LLWU_PF_WUF19_MASK)
#define LLWU_PF_WUF20_MASK (0x100000U)
#define LLWU_PF_WUF20_SHIFT (20U)
/*! WUF20 - Wakeup Flag For LLWU_P20
 *  0b0..LLWU_P20 input was not a wakeup source
 *  0b1..LLWU_P20 input was a wakeup source
 */
#define LLWU_PF_WUF20(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF20_SHIFT)) & LLWU_PF_WUF20_MASK)
#define LLWU_PF_WUF21_MASK (0x200000U)
#define LLWU_PF_WUF21_SHIFT (21U)
/*! WUF21 - Wakeup Flag For LLWU_P21
 *  0b0..LLWU_P21 input was not a wakeup source
 *  0b1..LLWU_P21 input was a wakeup source
 */
#define LLWU_PF_WUF21(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF21_SHIFT)) & LLWU_PF_WUF21_MASK)
#define LLWU_PF_WUF22_MASK (0x400000U)
#define LLWU_PF_WUF22_SHIFT (22U)
/*! WUF22 - Wakeup Flag For LLWU_P22
 *  0b0..LLWU_P22 input was not a wakeup source
 *  0b1..LLWU_P22 input was a wakeup source
 */
#define LLWU_PF_WUF22(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF22_SHIFT)) & LLWU_PF_WUF22_MASK)
#define LLWU_PF_WUF23_MASK (0x800000U)
#define LLWU_PF_WUF23_SHIFT (23U)
/*! WUF23 - Wakeup Flag For LLWU_P23
 *  0b0..LLWU_P23 input was not a wakeup source
 *  0b1..LLWU_P23 input was a wakeup source
 */
#define LLWU_PF_WUF23(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF23_SHIFT)) & LLWU_PF_WUF23_MASK)
#define LLWU_PF_WUF24_MASK (0x1000000U)
#define LLWU_PF_WUF24_SHIFT (24U)
/*! WUF24 - Wakeup Flag For LLWU_P24
 *  0b0..LLWU_P24 input was not a wakeup source
 *  0b1..LLWU_P24 input was a wakeup source
 */
#define LLWU_PF_WUF24(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF24_SHIFT)) & LLWU_PF_WUF24_MASK)
#define LLWU_PF_WUF25_MASK (0x2000000U)
#define LLWU_PF_WUF25_SHIFT (25U)
/*! WUF25 - Wakeup Flag For LLWU_P25
 *  0b0..LLWU_P25 input was not a wakeup source
 *  0b1..LLWU_P25 input was a wakeup source
 */
#define LLWU_PF_WUF25(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF25_SHIFT)) & LLWU_PF_WUF25_MASK)
#define LLWU_PF_WUF26_MASK (0x4000000U)
#define LLWU_PF_WUF26_SHIFT (26U)
/*! WUF26 - Wakeup Flag For LLWU_P26
 *  0b0..LLWU_P26 input was not a wakeup source
 *  0b1..LLWU_P26 input was a wakeup source
 */
#define LLWU_PF_WUF26(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF26_SHIFT)) & LLWU_PF_WUF26_MASK)
#define LLWU_PF_WUF27_MASK (0x8000000U)
#define LLWU_PF_WUF27_SHIFT (27U)
/*! WUF27 - Wakeup Flag For LLWU_P27
 *  0b0..LLWU_P27 input was not a wakeup source
 *  0b1..LLWU_P27 input was a wakeup source
 */
#define LLWU_PF_WUF27(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF27_SHIFT)) & LLWU_PF_WUF27_MASK)
#define LLWU_PF_WUF28_MASK (0x10000000U)
#define LLWU_PF_WUF28_SHIFT (28U)
/*! WUF28 - Wakeup Flag For LLWU_P28
 *  0b0..LLWU_P28 input was not a wakeup source
 *  0b1..LLWU_P28 input was a wakeup source
 */
#define LLWU_PF_WUF28(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF28_SHIFT)) & LLWU_PF_WUF28_MASK)
#define LLWU_PF_WUF29_MASK (0x20000000U)
#define LLWU_PF_WUF29_SHIFT (29U)
/*! WUF29 - Wakeup Flag For LLWU_P29
 *  0b0..LLWU_P29 input was not a wakeup source
 *  0b1..LLWU_P29 input was a wakeup source
 */
#define LLWU_PF_WUF29(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF29_SHIFT)) & LLWU_PF_WUF29_MASK)
#define LLWU_PF_WUF30_MASK (0x40000000U)
#define LLWU_PF_WUF30_SHIFT (30U)
/*! WUF30 - Wakeup Flag For LLWU_P30
 *  0b0..LLWU_P30 input was not a wakeup source
 *  0b1..LLWU_P30 input was a wakeup source
 */
#define LLWU_PF_WUF30(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF30_SHIFT)) & LLWU_PF_WUF30_MASK)
#define LLWU_PF_WUF31_MASK (0x80000000U)
#define LLWU_PF_WUF31_SHIFT (31U)
/*! WUF31 - Wakeup Flag For LLWU_P31
 *  0b0..LLWU_P31 input was not a wakeup source
 *  0b1..LLWU_P31 input was a wakeup source
 */
#define LLWU_PF_WUF31(x) (((uint32_t)(((uint32_t)(x)) << LLWU_PF_WUF31_SHIFT)) & LLWU_PF_WUF31_MASK)
/*! @} */

/*! @name MF - LLWU Module Interrupt Flag register */
/*! @{ */
#define LLWU_MF_MWUF0_MASK (0x1U)
#define LLWU_MF_MWUF0_SHIFT (0U)
/*! MWUF0 - Wakeup flag For module 0
 *  0b0..Module 0 input was not a wakeup source
 *  0b1..Module 0 input was a wakeup source
 */
#define LLWU_MF_MWUF0(x) (((uint32_t)(((uint32_t)(x)) << LLWU_MF_MWUF0_SHIFT)) & LLWU_MF_MWUF0_MASK)
#define LLWU_MF_MWUF1_MASK (0x2U)
#define LLWU_MF_MWUF1_SHIFT (1U)
/*! MWUF1 - Wakeup flag For module 1
 *  0b0..Module 1 input was not a wakeup source
 *  0b1..Module 1 input was a wakeup source
 */
#define LLWU_MF_MWUF1(x) (((uint32_t)(((uint32_t)(x)) << LLWU_MF_MWUF1_SHIFT)) & LLWU_MF_MWUF1_MASK)
#define LLWU_MF_MWUF2_MASK (0x4U)
#define LLWU_MF_MWUF2_SHIFT (2U)
/*! MWUF2 - Wakeup flag For module 2
 *  0b0..Module 2 input was not a wakeup source
 *  0b1..Module 2 input was a wakeup source
 */
#define LLWU_MF_MWUF2(x) (((uint32_t)(((uint32_t)(x)) << LLWU_MF_MWUF2_SHIFT)) & LLWU_MF_MWUF2_MASK)
#define LLWU_MF_MWUF3_MASK (0x8U)
#define LLWU_MF_MWUF3_SHIFT (3U)
/*! MWUF3 - Wakeup flag For module 3
 *  0b0..Module 3 input was not a wakeup source
 *  0b1..Module 3 input was a wakeup source
 */
#define LLWU_MF_MWUF3(x) (((uint32_t)(((uint32_t)(x)) << LLWU_MF_MWUF3_SHIFT)) & LLWU_MF_MWUF3_MASK)
#define LLWU_MF_MWUF4_MASK (0x10U)
#define LLWU_MF_MWUF4_SHIFT (4U)
/*! MWUF4 - Wakeup flag For module 4
 *  0b0..Module 4 input was not a wakeup source
 *  0b1..Module 4 input was a wakeup source
 */
#define LLWU_MF_MWUF4(x) (((uint32_t)(((uint32_t)(x)) << LLWU_MF_MWUF4_SHIFT)) & LLWU_MF_MWUF4_MASK)
#define LLWU_MF_MWUF5_MASK (0x20U)
#define LLWU_MF_MWUF5_SHIFT (5U)
/*! MWUF5 - Wakeup flag For module 5
 *  0b0..Module 5 input was not a wakeup source
 *  0b1..Module 5 input was a wakeup source
 */
#define LLWU_MF_MWUF5(x) (((uint32_t)(((uint32_t)(x)) << LLWU_MF_MWUF5_SHIFT)) & LLWU_MF_MWUF5_MASK)
#define LLWU_MF_MWUF6_MASK (0x40U)
#define LLWU_MF_MWUF6_SHIFT (6U)
/*! MWUF6 - Wakeup flag For module 6
 *  0b0..Module 6 input was not a wakeup source
 *  0b1..Module 6 input was a wakeup source
 */
#define LLWU_MF_MWUF6(x) (((uint32_t)(((uint32_t)(x)) << LLWU_MF_MWUF6_SHIFT)) & LLWU_MF_MWUF6_MASK)
#define LLWU_MF_MWUF7_MASK (0x80U)
#define LLWU_MF_MWUF7_SHIFT (7U)
/*! MWUF7 - Wakeup flag For module 7
 *  0b0..Module 7 input was not a wakeup source
 *  0b1..Module 7 input was a wakeup source
 */
#define LLWU_MF_MWUF7(x) (((uint32_t)(((uint32_t)(x)) << LLWU_MF_MWUF7_SHIFT)) & LLWU_MF_MWUF7_MASK)
/*! @} */

/*! @name FILT - LLWU Pin Filter register */
/*! @{ */
#define LLWU_FILT_FILTSEL1_MASK (0x1FU)
#define LLWU_FILT_FILTSEL1_SHIFT (0U)
/*! FILTSEL1 - Filter 1 Pin Select
 *  0b00000..Select LLWU_P0 for filter
 *  0b11111..Select LLWU_P31 for filter
 */
#define LLWU_FILT_FILTSEL1(x) (((uint32_t)(((uint32_t)(x)) << LLWU_FILT_FILTSEL1_SHIFT)) & LLWU_FILT_FILTSEL1_MASK)
#define LLWU_FILT_FILTE1_MASK (0x60U)
#define LLWU_FILT_FILTE1_SHIFT (5U)
/*! FILTE1 - Filter 1 Enable
 *  0b00..Filter disabled
 *  0b01..Filter posedge detect enabled
 *  0b10..Filter negedge detect enabled
 *  0b11..Filter any edge detect enabled
 */
#define LLWU_FILT_FILTE1(x) (((uint32_t)(((uint32_t)(x)) << LLWU_FILT_FILTE1_SHIFT)) & LLWU_FILT_FILTE1_MASK)
#define LLWU_FILT_FILTF1_MASK (0x80U)
#define LLWU_FILT_FILTF1_SHIFT (7U)
/*! FILTF1 - Filter 1 Flag
 *  0b0..Pin Filter 1 was not a wakeup source
 *  0b1..Pin Filter 1 was a wakeup source
 */
#define LLWU_FILT_FILTF1(x) (((uint32_t)(((uint32_t)(x)) << LLWU_FILT_FILTF1_SHIFT)) & LLWU_FILT_FILTF1_MASK)
#define LLWU_FILT_FILTSEL2_MASK (0x1F00U)
#define LLWU_FILT_FILTSEL2_SHIFT (8U)
/*! FILTSEL2 - Filter 2 Pin Select
 *  0b00000..Select LLWU_P0 for filter
 *  0b11111..Select LLWU_P31 for filter
 */
#define LLWU_FILT_FILTSEL2(x) (((uint32_t)(((uint32_t)(x)) << LLWU_FILT_FILTSEL2_SHIFT)) & LLWU_FILT_FILTSEL2_MASK)
#define LLWU_FILT_FILTE2_MASK (0x6000U)
#define LLWU_FILT_FILTE2_SHIFT (13U)
/*! FILTE2 - Filter 2 Enable
 *  0b00..Filter disabled
 *  0b01..Filter posedge detect enabled
 *  0b10..Filter negedge detect enabled
 *  0b11..Filter any edge detect enabled
 */
#define LLWU_FILT_FILTE2(x) (((uint32_t)(((uint32_t)(x)) << LLWU_FILT_FILTE2_SHIFT)) & LLWU_FILT_FILTE2_MASK)
#define LLWU_FILT_FILTF2_MASK (0x8000U)
#define LLWU_FILT_FILTF2_SHIFT (15U)
/*! FILTF2 - Filter 2 Flag
 *  0b0..Pin Filter 1 was not a wakeup source
 *  0b1..Pin Filter 1 was a wakeup source
 */
#define LLWU_FILT_FILTF2(x) (((uint32_t)(((uint32_t)(x)) << LLWU_FILT_FILTF2_SHIFT)) & LLWU_FILT_FILTF2_MASK)
#define LLWU_FILT_FILTSEL3_MASK (0x1F0000U)
#define LLWU_FILT_FILTSEL3_SHIFT (16U)
/*! FILTSEL3 - Filter 3 Pin Select
 *  0b00000..Select LLWU_P0 for filter
 *  0b11111..Select LLWU_P31 for filter
 */
#define LLWU_FILT_FILTSEL3(x) (((uint32_t)(((uint32_t)(x)) << LLWU_FILT_FILTSEL3_SHIFT)) & LLWU_FILT_FILTSEL3_MASK)
#define LLWU_FILT_FILTE3_MASK (0x600000U)
#define LLWU_FILT_FILTE3_SHIFT (21U)
/*! FILTE3 - Filter 3 Enable
 *  0b00..Filter disabled
 *  0b01..Filter posedge detect enabled
 *  0b10..Filter negedge detect enabled
 *  0b11..Filter any edge detect enabled
 */
#define LLWU_FILT_FILTE3(x) (((uint32_t)(((uint32_t)(x)) << LLWU_FILT_FILTE3_SHIFT)) & LLWU_FILT_FILTE3_MASK)
#define LLWU_FILT_FILTF3_MASK (0x800000U)
#define LLWU_FILT_FILTF3_SHIFT (23U)
/*! FILTF3 - Filter 3 Flag
 *  0b0..Pin Filter 1 was not a wakeup source
 *  0b1..Pin Filter 1 was a wakeup source
 */
#define LLWU_FILT_FILTF3(x) (((uint32_t)(((uint32_t)(x)) << LLWU_FILT_FILTF3_SHIFT)) & LLWU_FILT_FILTF3_MASK)
#define LLWU_FILT_FILTSEL4_MASK (0x1F000000U)
#define LLWU_FILT_FILTSEL4_SHIFT (24U)
/*! FILTSEL4 - Filter 4 Pin Select
 *  0b00000..Select LLWU_P0 for filter
 *  0b11111..Select LLWU_P31 for filter
 */
#define LLWU_FILT_FILTSEL4(x) (((uint32_t)(((uint32_t)(x)) << LLWU_FILT_FILTSEL4_SHIFT)) & LLWU_FILT_FILTSEL4_MASK)
#define LLWU_FILT_FILTE4_MASK (0x60000000U)
#define LLWU_FILT_FILTE4_SHIFT (29U)
/*! FILTE4 - Filter 4 Enable
 *  0b00..Filter disabled
 *  0b01..Filter posedge detect enabled
 *  0b10..Filter negedge detect enabled
 *  0b11..Filter any edge detect enabled
 */
#define LLWU_FILT_FILTE4(x) (((uint32_t)(((uint32_t)(x)) << LLWU_FILT_FILTE4_SHIFT)) & LLWU_FILT_FILTE4_MASK)
#define LLWU_FILT_FILTF4_MASK (0x80000000U)
#define LLWU_FILT_FILTF4_SHIFT (31U)
/*! FILTF4 - Filter 4 Flag
 *  0b0..Pin Filter 1 was not a wakeup source
 *  0b1..Pin Filter 1 was a wakeup source
 */
#define LLWU_FILT_FILTF4(x) (((uint32_t)(((uint32_t)(x)) << LLWU_FILT_FILTF4_SHIFT)) & LLWU_FILT_FILTF4_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group LLWU_Register_Masks */

/* LLWU - Peripheral instance base addresses */
/** Peripheral LLWU base address */
#define LLWU_BASE (0x40061000u)
/** Peripheral LLWU base pointer */
#define LLWU ((LLWU_Type *)LLWU_BASE)
/** Array initializer of LLWU peripheral base addresses */
#define LLWU_BASE_ADDRS \
    {                   \
        LLWU_BASE       \
    }
/** Array initializer of LLWU peripheral base pointers */
#define LLWU_BASE_PTRS \
    {                  \
        LLWU           \
    }
/** Interrupt vectors for the LLWU peripheral type */
#define LLWU_IRQS \
    {             \
        LLWU_IRQn \
    }

/*!
 * @}
 */ /* end of group LLWU_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- LPI2C Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPI2C_Peripheral_Access_Layer LPI2C Peripheral Access Layer
 * @{
 */

/** LPI2C - Register Layout Typedef */
typedef struct
{
    __I uint32_t VERID; /**< Version ID Register, offset: 0x0 */
    __I uint32_t PARAM; /**< Parameter Register, offset: 0x4 */
    uint8_t RESERVED_0[8];
    __IO uint32_t MCR;    /**< Master Control Register, offset: 0x10 */
    __IO uint32_t MSR;    /**< Master Status Register, offset: 0x14 */
    __IO uint32_t MIER;   /**< Master Interrupt Enable Register, offset: 0x18 */
    __IO uint32_t MDER;   /**< Master DMA Enable Register, offset: 0x1C */
    __IO uint32_t MCFGR0; /**< Master Configuration Register 0, offset: 0x20 */
    __IO uint32_t MCFGR1; /**< Master Configuration Register 1, offset: 0x24 */
    __IO uint32_t MCFGR2; /**< Master Configuration Register 2, offset: 0x28 */
    __IO uint32_t MCFGR3; /**< Master Configuration Register 3, offset: 0x2C */
    uint8_t RESERVED_1[16];
    __IO uint32_t MDMR; /**< Master Data Match Register, offset: 0x40 */
    uint8_t RESERVED_2[4];
    __IO uint32_t MCCR0; /**< Master Clock Configuration Register 0, offset: 0x48 */
    uint8_t RESERVED_3[4];
    __IO uint32_t MCCR1; /**< Master Clock Configuration Register 1, offset: 0x50 */
    uint8_t RESERVED_4[4];
    __IO uint32_t MFCR; /**< Master FIFO Control Register, offset: 0x58 */
    __I uint32_t MFSR;  /**< Master FIFO Status Register, offset: 0x5C */
    __O uint32_t MTDR;  /**< Master Transmit Data Register, offset: 0x60 */
    uint8_t RESERVED_5[12];
    __I uint32_t MRDR; /**< Master Receive Data Register, offset: 0x70 */
    uint8_t RESERVED_6[156];
    __IO uint32_t SCR;  /**< Slave Control Register, offset: 0x110 */
    __IO uint32_t SSR;  /**< Slave Status Register, offset: 0x114 */
    __IO uint32_t SIER; /**< Slave Interrupt Enable Register, offset: 0x118 */
    __IO uint32_t SDER; /**< Slave DMA Enable Register, offset: 0x11C */
    uint8_t RESERVED_7[4];
    __IO uint32_t SCFGR1; /**< Slave Configuration Register 1, offset: 0x124 */
    __IO uint32_t SCFGR2; /**< Slave Configuration Register 2, offset: 0x128 */
    uint8_t RESERVED_8[20];
    __IO uint32_t SAMR; /**< Slave Address Match Register, offset: 0x140 */
    uint8_t RESERVED_9[12];
    __I uint32_t SASR;  /**< Slave Address Status Register, offset: 0x150 */
    __IO uint32_t STAR; /**< Slave Transmit ACK Register, offset: 0x154 */
    uint8_t RESERVED_10[8];
    __O uint32_t STDR; /**< Slave Transmit Data Register, offset: 0x160 */
    uint8_t RESERVED_11[12];
    __I uint32_t SRDR; /**< Slave Receive Data Register, offset: 0x170 */
} LPI2C_Type;

/* ----------------------------------------------------------------------------
   -- LPI2C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPI2C_Register_Masks LPI2C Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */
#define LPI2C_VERID_FEATURE_MASK (0xFFFFU)
#define LPI2C_VERID_FEATURE_SHIFT (0U)
/*! FEATURE - Feature Specification Number
 *  0b0000000000000010..Master only with standard feature set.
 *  0b0000000000000011..Master and slave with standard feature set.
 */
#define LPI2C_VERID_FEATURE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_VERID_FEATURE_SHIFT)) & LPI2C_VERID_FEATURE_MASK)
#define LPI2C_VERID_MINOR_MASK (0xFF0000U)
#define LPI2C_VERID_MINOR_SHIFT (16U)
/*! MINOR - Minor Version Number
 */
#define LPI2C_VERID_MINOR(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_VERID_MINOR_SHIFT)) & LPI2C_VERID_MINOR_MASK)
#define LPI2C_VERID_MAJOR_MASK (0xFF000000U)
#define LPI2C_VERID_MAJOR_SHIFT (24U)
/*! MAJOR - Major Version Number
 */
#define LPI2C_VERID_MAJOR(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_VERID_MAJOR_SHIFT)) & LPI2C_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */
#define LPI2C_PARAM_MTXFIFO_MASK (0xFU)
#define LPI2C_PARAM_MTXFIFO_SHIFT (0U)
/*! MTXFIFO - Master Transmit FIFO Size
 */
#define LPI2C_PARAM_MTXFIFO(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_PARAM_MTXFIFO_SHIFT)) & LPI2C_PARAM_MTXFIFO_MASK)
#define LPI2C_PARAM_MRXFIFO_MASK (0xF00U)
#define LPI2C_PARAM_MRXFIFO_SHIFT (8U)
/*! MRXFIFO - Master Receive FIFO Size
 */
#define LPI2C_PARAM_MRXFIFO(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_PARAM_MRXFIFO_SHIFT)) & LPI2C_PARAM_MRXFIFO_MASK)
/*! @} */

/*! @name MCR - Master Control Register */
/*! @{ */
#define LPI2C_MCR_MEN_MASK (0x1U)
#define LPI2C_MCR_MEN_SHIFT (0U)
/*! MEN - Master Enable
 *  0b0..Master logic is disabled.
 *  0b1..Master logic is enabled.
 */
#define LPI2C_MCR_MEN(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCR_MEN_SHIFT)) & LPI2C_MCR_MEN_MASK)
#define LPI2C_MCR_RST_MASK (0x2U)
#define LPI2C_MCR_RST_SHIFT (1U)
/*! RST - Software Reset
 *  0b0..Master logic is not reset.
 *  0b1..Master logic is reset.
 */
#define LPI2C_MCR_RST(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCR_RST_SHIFT)) & LPI2C_MCR_RST_MASK)
#define LPI2C_MCR_DOZEN_MASK (0x4U)
#define LPI2C_MCR_DOZEN_SHIFT (2U)
/*! DOZEN - Doze mode enable
 *  0b0..Master is enabled in Doze mode.
 *  0b1..Master is disabled in Doze mode.
 */
#define LPI2C_MCR_DOZEN(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCR_DOZEN_SHIFT)) & LPI2C_MCR_DOZEN_MASK)
#define LPI2C_MCR_DBGEN_MASK (0x8U)
#define LPI2C_MCR_DBGEN_SHIFT (3U)
/*! DBGEN - Debug Enable
 *  0b0..Master is disabled in debug mode.
 *  0b1..Master is enabled in debug mode.
 */
#define LPI2C_MCR_DBGEN(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCR_DBGEN_SHIFT)) & LPI2C_MCR_DBGEN_MASK)
#define LPI2C_MCR_RTF_MASK (0x100U)
#define LPI2C_MCR_RTF_SHIFT (8U)
/*! RTF - Reset Transmit FIFO
 *  0b0..No effect.
 *  0b1..Transmit FIFO is reset.
 */
#define LPI2C_MCR_RTF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCR_RTF_SHIFT)) & LPI2C_MCR_RTF_MASK)
#define LPI2C_MCR_RRF_MASK (0x200U)
#define LPI2C_MCR_RRF_SHIFT (9U)
/*! RRF - Reset Receive FIFO
 *  0b0..No effect.
 *  0b1..Receive FIFO is reset.
 */
#define LPI2C_MCR_RRF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCR_RRF_SHIFT)) & LPI2C_MCR_RRF_MASK)
/*! @} */

/*! @name MSR - Master Status Register */
/*! @{ */
#define LPI2C_MSR_TDF_MASK (0x1U)
#define LPI2C_MSR_TDF_SHIFT (0U)
/*! TDF - Transmit Data Flag
 *  0b0..Transmit data not requested.
 *  0b1..Transmit data is requested.
 */
#define LPI2C_MSR_TDF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_TDF_SHIFT)) & LPI2C_MSR_TDF_MASK)
#define LPI2C_MSR_RDF_MASK (0x2U)
#define LPI2C_MSR_RDF_SHIFT (1U)
/*! RDF - Receive Data Flag
 *  0b0..Receive Data is not ready.
 *  0b1..Receive data is ready.
 */
#define LPI2C_MSR_RDF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_RDF_SHIFT)) & LPI2C_MSR_RDF_MASK)
#define LPI2C_MSR_EPF_MASK (0x100U)
#define LPI2C_MSR_EPF_SHIFT (8U)
/*! EPF - End Packet Flag
 *  0b0..Master has not generated a STOP or Repeated START condition.
 *  0b1..Master has generated a STOP or Repeated START condition.
 */
#define LPI2C_MSR_EPF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_EPF_SHIFT)) & LPI2C_MSR_EPF_MASK)
#define LPI2C_MSR_SDF_MASK (0x200U)
#define LPI2C_MSR_SDF_SHIFT (9U)
/*! SDF - STOP Detect Flag
 *  0b0..Master has not generated a STOP condition.
 *  0b1..Master has generated a STOP condition.
 */
#define LPI2C_MSR_SDF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_SDF_SHIFT)) & LPI2C_MSR_SDF_MASK)
#define LPI2C_MSR_NDF_MASK (0x400U)
#define LPI2C_MSR_NDF_SHIFT (10U)
/*! NDF - NACK Detect Flag
 *  0b0..Unexpected NACK not detected.
 *  0b1..Unexpected NACK was detected.
 */
#define LPI2C_MSR_NDF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_NDF_SHIFT)) & LPI2C_MSR_NDF_MASK)
#define LPI2C_MSR_ALF_MASK (0x800U)
#define LPI2C_MSR_ALF_SHIFT (11U)
/*! ALF - Arbitration Lost Flag
 *  0b0..Master has not lost arbitration.
 *  0b1..Master has lost arbitration.
 */
#define LPI2C_MSR_ALF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_ALF_SHIFT)) & LPI2C_MSR_ALF_MASK)
#define LPI2C_MSR_FEF_MASK (0x1000U)
#define LPI2C_MSR_FEF_SHIFT (12U)
/*! FEF - FIFO Error Flag
 *  0b0..No error.
 *  0b1..Master sending or receiving data without START condition.
 */
#define LPI2C_MSR_FEF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_FEF_SHIFT)) & LPI2C_MSR_FEF_MASK)
#define LPI2C_MSR_PLTF_MASK (0x2000U)
#define LPI2C_MSR_PLTF_SHIFT (13U)
/*! PLTF - Pin Low Timeout Flag
 *  0b0..Pin low timeout has not occurred or is disabled.
 *  0b1..Pin low timeout has occurred.
 */
#define LPI2C_MSR_PLTF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_PLTF_SHIFT)) & LPI2C_MSR_PLTF_MASK)
#define LPI2C_MSR_DMF_MASK (0x4000U)
#define LPI2C_MSR_DMF_SHIFT (14U)
/*! DMF - Data Match Flag
 *  0b0..Have not received matching data.
 *  0b1..Have received matching data.
 */
#define LPI2C_MSR_DMF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_DMF_SHIFT)) & LPI2C_MSR_DMF_MASK)
#define LPI2C_MSR_MBF_MASK (0x1000000U)
#define LPI2C_MSR_MBF_SHIFT (24U)
/*! MBF - Master Busy Flag
 *  0b0..I2C Master is idle.
 *  0b1..I2C Master is busy.
 */
#define LPI2C_MSR_MBF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_MBF_SHIFT)) & LPI2C_MSR_MBF_MASK)
#define LPI2C_MSR_BBF_MASK (0x2000000U)
#define LPI2C_MSR_BBF_SHIFT (25U)
/*! BBF - Bus Busy Flag
 *  0b0..I2C Bus is idle.
 *  0b1..I2C Bus is busy.
 */
#define LPI2C_MSR_BBF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_BBF_SHIFT)) & LPI2C_MSR_BBF_MASK)
/*! @} */

/*! @name MIER - Master Interrupt Enable Register */
/*! @{ */
#define LPI2C_MIER_TDIE_MASK (0x1U)
#define LPI2C_MIER_TDIE_SHIFT (0U)
/*! TDIE - Transmit Data Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled
 */
#define LPI2C_MIER_TDIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_TDIE_SHIFT)) & LPI2C_MIER_TDIE_MASK)
#define LPI2C_MIER_RDIE_MASK (0x2U)
#define LPI2C_MIER_RDIE_SHIFT (1U)
/*! RDIE - Receive Data Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_MIER_RDIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_RDIE_SHIFT)) & LPI2C_MIER_RDIE_MASK)
#define LPI2C_MIER_EPIE_MASK (0x100U)
#define LPI2C_MIER_EPIE_SHIFT (8U)
/*! EPIE - End Packet Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_MIER_EPIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_EPIE_SHIFT)) & LPI2C_MIER_EPIE_MASK)
#define LPI2C_MIER_SDIE_MASK (0x200U)
#define LPI2C_MIER_SDIE_SHIFT (9U)
/*! SDIE - STOP Detect Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_MIER_SDIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_SDIE_SHIFT)) & LPI2C_MIER_SDIE_MASK)
#define LPI2C_MIER_NDIE_MASK (0x400U)
#define LPI2C_MIER_NDIE_SHIFT (10U)
/*! NDIE - NACK Detect Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_MIER_NDIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_NDIE_SHIFT)) & LPI2C_MIER_NDIE_MASK)
#define LPI2C_MIER_ALIE_MASK (0x800U)
#define LPI2C_MIER_ALIE_SHIFT (11U)
/*! ALIE - Arbitration Lost Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_MIER_ALIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_ALIE_SHIFT)) & LPI2C_MIER_ALIE_MASK)
#define LPI2C_MIER_FEIE_MASK (0x1000U)
#define LPI2C_MIER_FEIE_SHIFT (12U)
/*! FEIE - FIFO Error Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_MIER_FEIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_FEIE_SHIFT)) & LPI2C_MIER_FEIE_MASK)
#define LPI2C_MIER_PLTIE_MASK (0x2000U)
#define LPI2C_MIER_PLTIE_SHIFT (13U)
/*! PLTIE - Pin Low Timeout Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_MIER_PLTIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_PLTIE_SHIFT)) & LPI2C_MIER_PLTIE_MASK)
#define LPI2C_MIER_DMIE_MASK (0x4000U)
#define LPI2C_MIER_DMIE_SHIFT (14U)
/*! DMIE - Data Match Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_MIER_DMIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_DMIE_SHIFT)) & LPI2C_MIER_DMIE_MASK)
/*! @} */

/*! @name MDER - Master DMA Enable Register */
/*! @{ */
#define LPI2C_MDER_TDDE_MASK (0x1U)
#define LPI2C_MDER_TDDE_SHIFT (0U)
/*! TDDE - Transmit Data DMA Enable
 *  0b0..DMA request disabled.
 *  0b1..DMA request enabled
 */
#define LPI2C_MDER_TDDE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MDER_TDDE_SHIFT)) & LPI2C_MDER_TDDE_MASK)
#define LPI2C_MDER_RDDE_MASK (0x2U)
#define LPI2C_MDER_RDDE_SHIFT (1U)
/*! RDDE - Receive Data DMA Enable
 *  0b0..DMA request disabled.
 *  0b1..DMA request enabled.
 */
#define LPI2C_MDER_RDDE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MDER_RDDE_SHIFT)) & LPI2C_MDER_RDDE_MASK)
/*! @} */

/*! @name MCFGR0 - Master Configuration Register 0 */
/*! @{ */
#define LPI2C_MCFGR0_HREN_MASK (0x1U)
#define LPI2C_MCFGR0_HREN_SHIFT (0U)
/*! HREN - Host Request Enable
 *  0b0..Host request input is disabled.
 *  0b1..Host request input is enabled.
 */
#define LPI2C_MCFGR0_HREN(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR0_HREN_SHIFT)) & LPI2C_MCFGR0_HREN_MASK)
#define LPI2C_MCFGR0_HRPOL_MASK (0x2U)
#define LPI2C_MCFGR0_HRPOL_SHIFT (1U)
/*! HRPOL - Host Request Polarity
 *  0b0..Active low.
 *  0b1..Active high.
 */
#define LPI2C_MCFGR0_HRPOL(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR0_HRPOL_SHIFT)) & LPI2C_MCFGR0_HRPOL_MASK)
#define LPI2C_MCFGR0_HRSEL_MASK (0x4U)
#define LPI2C_MCFGR0_HRSEL_SHIFT (2U)
/*! HRSEL - Host Request Select
 *  0b0..Host request input is pin LPI2C_HREQ.
 *  0b1..Host request input is input trigger.
 */
#define LPI2C_MCFGR0_HRSEL(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR0_HRSEL_SHIFT)) & LPI2C_MCFGR0_HRSEL_MASK)
#define LPI2C_MCFGR0_CIRFIFO_MASK (0x100U)
#define LPI2C_MCFGR0_CIRFIFO_SHIFT (8U)
/*! CIRFIFO - Circular FIFO Enable
 *  0b0..Circular FIFO is disabled.
 *  0b1..Circular FIFO is enabled.
 */
#define LPI2C_MCFGR0_CIRFIFO(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR0_CIRFIFO_SHIFT)) & LPI2C_MCFGR0_CIRFIFO_MASK)
#define LPI2C_MCFGR0_RDMO_MASK (0x200U)
#define LPI2C_MCFGR0_RDMO_SHIFT (9U)
/*! RDMO - Receive Data Match Only
 *  0b0..Received data is stored in the receive FIFO as normal.
 *  0b1..Received data is discarded unless the RMF is set.
 */
#define LPI2C_MCFGR0_RDMO(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR0_RDMO_SHIFT)) & LPI2C_MCFGR0_RDMO_MASK)
/*! @} */

/*! @name MCFGR1 - Master Configuration Register 1 */
/*! @{ */
#define LPI2C_MCFGR1_PRESCALE_MASK (0x7U)
#define LPI2C_MCFGR1_PRESCALE_SHIFT (0U)
/*! PRESCALE - Prescaler
 *  0b000..Divide by 1.
 *  0b001..Divide by 2.
 *  0b010..Divide by 4.
 *  0b011..Divide by 8.
 *  0b100..Divide by 16.
 *  0b101..Divide by 32.
 *  0b110..Divide by 64.
 *  0b111..Divide by 128.
 */
#define LPI2C_MCFGR1_PRESCALE(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR1_PRESCALE_SHIFT)) & LPI2C_MCFGR1_PRESCALE_MASK)
#define LPI2C_MCFGR1_AUTOSTOP_MASK (0x100U)
#define LPI2C_MCFGR1_AUTOSTOP_SHIFT (8U)
/*! AUTOSTOP - Automatic STOP Generation
 *  0b0..No effect.
 *  0b1..STOP condition is automatically generated whenever the transmit FIFO is empty and LPI2C master is busy.
 */
#define LPI2C_MCFGR1_AUTOSTOP(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR1_AUTOSTOP_SHIFT)) & LPI2C_MCFGR1_AUTOSTOP_MASK)
#define LPI2C_MCFGR1_IGNACK_MASK (0x200U)
#define LPI2C_MCFGR1_IGNACK_SHIFT (9U)
/*! IGNACK
 *  0b0..LPI2C Master will receive ACK and NACK normally.
 *  0b1..LPI2C Master will treat a received NACK as if it was an ACK.
 */
#define LPI2C_MCFGR1_IGNACK(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR1_IGNACK_SHIFT)) & LPI2C_MCFGR1_IGNACK_MASK)
#define LPI2C_MCFGR1_TIMECFG_MASK (0x400U)
#define LPI2C_MCFGR1_TIMECFG_SHIFT (10U)
/*! TIMECFG - Timeout Configuration
 *  0b0..Pin Low Timeout Flag will set if SCL is low for longer than the configured timeout.
 *  0b1..Pin Low Timeout Flag will set if either SCL or SDA is low for longer than the configured timeout.
 */
#define LPI2C_MCFGR1_TIMECFG(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR1_TIMECFG_SHIFT)) & LPI2C_MCFGR1_TIMECFG_MASK)
#define LPI2C_MCFGR1_MATCFG_MASK (0x70000U)
#define LPI2C_MCFGR1_MATCFG_SHIFT (16U)
/*! MATCFG - Match Configuration
 *  0b000..Match disabled.
 *  0b001..Reserved.
 *  0b010..Match enabled (1st data word equals MATCH0 OR MATCH1).
 *  0b011..Match enabled (any data word equals MATCH0 OR MATCH1).
 *  0b100..Match enabled (1st data word equals MATCH0 AND 2nd data word equals MATCH1).
 *  0b101..Match enabled (any data word equals MATCH0 AND next data word equals MATCH1).
 *  0b110..Match enabled (1st data word AND MATCH1 equals MATCH0 AND MATCH1).
 *  0b111..Match enabled (any data word AND MATCH1 equals MATCH0 AND MATCH1).
 */
#define LPI2C_MCFGR1_MATCFG(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR1_MATCFG_SHIFT)) & LPI2C_MCFGR1_MATCFG_MASK)
#define LPI2C_MCFGR1_PINCFG_MASK (0x7000000U)
#define LPI2C_MCFGR1_PINCFG_SHIFT (24U)
/*! PINCFG - Pin Configuration
 *  0b000..LPI2C configured for 2-pin open drain mode.
 *  0b001..LPI2C configured for 2-pin output only mode (ultra-fast mode).
 *  0b010..LPI2C configured for 2-pin push-pull mode.
 *  0b011..LPI2C configured for 4-pin push-pull mode.
 *  0b100..LPI2C configured for 2-pin open drain mode with separate LPI2C slave.
 *  0b101..LPI2C configured for 2-pin output only mode (ultra-fast mode) with separate LPI2C slave.
 *  0b110..LPI2C configured for 2-pin push-pull mode with separate LPI2C slave.
 *  0b111..LPI2C configured for 4-pin push-pull mode (inverted outputs).
 */
#define LPI2C_MCFGR1_PINCFG(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR1_PINCFG_SHIFT)) & LPI2C_MCFGR1_PINCFG_MASK)
/*! @} */

/*! @name MCFGR2 - Master Configuration Register 2 */
/*! @{ */
#define LPI2C_MCFGR2_BUSIDLE_MASK (0xFFFU)
#define LPI2C_MCFGR2_BUSIDLE_SHIFT (0U)
/*! BUSIDLE - Bus Idle Timeout
 */
#define LPI2C_MCFGR2_BUSIDLE(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR2_BUSIDLE_SHIFT)) & LPI2C_MCFGR2_BUSIDLE_MASK)
#define LPI2C_MCFGR2_FILTSCL_MASK (0xF0000U)
#define LPI2C_MCFGR2_FILTSCL_SHIFT (16U)
/*! FILTSCL - Glitch Filter SCL
 */
#define LPI2C_MCFGR2_FILTSCL(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR2_FILTSCL_SHIFT)) & LPI2C_MCFGR2_FILTSCL_MASK)
#define LPI2C_MCFGR2_FILTSDA_MASK (0xF000000U)
#define LPI2C_MCFGR2_FILTSDA_SHIFT (24U)
/*! FILTSDA - Glitch Filter SDA
 */
#define LPI2C_MCFGR2_FILTSDA(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR2_FILTSDA_SHIFT)) & LPI2C_MCFGR2_FILTSDA_MASK)
/*! @} */

/*! @name MCFGR3 - Master Configuration Register 3 */
/*! @{ */
#define LPI2C_MCFGR3_PINLOW_MASK (0xFFF00U)
#define LPI2C_MCFGR3_PINLOW_SHIFT (8U)
/*! PINLOW - Pin Low Timeout
 */
#define LPI2C_MCFGR3_PINLOW(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR3_PINLOW_SHIFT)) & LPI2C_MCFGR3_PINLOW_MASK)
/*! @} */

/*! @name MDMR - Master Data Match Register */
/*! @{ */
#define LPI2C_MDMR_MATCH0_MASK (0xFFU)
#define LPI2C_MDMR_MATCH0_SHIFT (0U)
/*! MATCH0 - Match 0 Value
 */
#define LPI2C_MDMR_MATCH0(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MDMR_MATCH0_SHIFT)) & LPI2C_MDMR_MATCH0_MASK)
#define LPI2C_MDMR_MATCH1_MASK (0xFF0000U)
#define LPI2C_MDMR_MATCH1_SHIFT (16U)
/*! MATCH1 - Match 1 Value
 */
#define LPI2C_MDMR_MATCH1(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MDMR_MATCH1_SHIFT)) & LPI2C_MDMR_MATCH1_MASK)
/*! @} */

/*! @name MCCR0 - Master Clock Configuration Register 0 */
/*! @{ */
#define LPI2C_MCCR0_CLKLO_MASK (0x3FU)
#define LPI2C_MCCR0_CLKLO_SHIFT (0U)
/*! CLKLO - Clock Low Period
 */
#define LPI2C_MCCR0_CLKLO(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR0_CLKLO_SHIFT)) & LPI2C_MCCR0_CLKLO_MASK)
#define LPI2C_MCCR0_CLKHI_MASK (0x3F00U)
#define LPI2C_MCCR0_CLKHI_SHIFT (8U)
/*! CLKHI - Clock High Period
 */
#define LPI2C_MCCR0_CLKHI(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR0_CLKHI_SHIFT)) & LPI2C_MCCR0_CLKHI_MASK)
#define LPI2C_MCCR0_SETHOLD_MASK (0x3F0000U)
#define LPI2C_MCCR0_SETHOLD_SHIFT (16U)
/*! SETHOLD - Setup Hold Delay
 */
#define LPI2C_MCCR0_SETHOLD(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR0_SETHOLD_SHIFT)) & LPI2C_MCCR0_SETHOLD_MASK)
#define LPI2C_MCCR0_DATAVD_MASK (0x3F000000U)
#define LPI2C_MCCR0_DATAVD_SHIFT (24U)
/*! DATAVD - Data Valid Delay
 */
#define LPI2C_MCCR0_DATAVD(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR0_DATAVD_SHIFT)) & LPI2C_MCCR0_DATAVD_MASK)
/*! @} */

/*! @name MCCR1 - Master Clock Configuration Register 1 */
/*! @{ */
#define LPI2C_MCCR1_CLKLO_MASK (0x3FU)
#define LPI2C_MCCR1_CLKLO_SHIFT (0U)
/*! CLKLO - Clock Low Period
 */
#define LPI2C_MCCR1_CLKLO(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR1_CLKLO_SHIFT)) & LPI2C_MCCR1_CLKLO_MASK)
#define LPI2C_MCCR1_CLKHI_MASK (0x3F00U)
#define LPI2C_MCCR1_CLKHI_SHIFT (8U)
/*! CLKHI - Clock High Period
 */
#define LPI2C_MCCR1_CLKHI(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR1_CLKHI_SHIFT)) & LPI2C_MCCR1_CLKHI_MASK)
#define LPI2C_MCCR1_SETHOLD_MASK (0x3F0000U)
#define LPI2C_MCCR1_SETHOLD_SHIFT (16U)
/*! SETHOLD - Setup Hold Delay
 */
#define LPI2C_MCCR1_SETHOLD(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR1_SETHOLD_SHIFT)) & LPI2C_MCCR1_SETHOLD_MASK)
#define LPI2C_MCCR1_DATAVD_MASK (0x3F000000U)
#define LPI2C_MCCR1_DATAVD_SHIFT (24U)
/*! DATAVD - Data Valid Delay
 */
#define LPI2C_MCCR1_DATAVD(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR1_DATAVD_SHIFT)) & LPI2C_MCCR1_DATAVD_MASK)
/*! @} */

/*! @name MFCR - Master FIFO Control Register */
/*! @{ */
#define LPI2C_MFCR_TXWATER_MASK (0xFFU)
#define LPI2C_MFCR_TXWATER_SHIFT (0U)
/*! TXWATER - Transmit FIFO Watermark
 */
#define LPI2C_MFCR_TXWATER(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MFCR_TXWATER_SHIFT)) & LPI2C_MFCR_TXWATER_MASK)
#define LPI2C_MFCR_RXWATER_MASK (0xFF0000U)
#define LPI2C_MFCR_RXWATER_SHIFT (16U)
/*! RXWATER - Receive FIFO Watermark
 */
#define LPI2C_MFCR_RXWATER(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MFCR_RXWATER_SHIFT)) & LPI2C_MFCR_RXWATER_MASK)
/*! @} */

/*! @name MFSR - Master FIFO Status Register */
/*! @{ */
#define LPI2C_MFSR_TXCOUNT_MASK (0xFFU)
#define LPI2C_MFSR_TXCOUNT_SHIFT (0U)
/*! TXCOUNT - Transmit FIFO Count
 */
#define LPI2C_MFSR_TXCOUNT(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MFSR_TXCOUNT_SHIFT)) & LPI2C_MFSR_TXCOUNT_MASK)
#define LPI2C_MFSR_RXCOUNT_MASK (0xFF0000U)
#define LPI2C_MFSR_RXCOUNT_SHIFT (16U)
/*! RXCOUNT - Receive FIFO Count
 */
#define LPI2C_MFSR_RXCOUNT(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MFSR_RXCOUNT_SHIFT)) & LPI2C_MFSR_RXCOUNT_MASK)
/*! @} */

/*! @name MTDR - Master Transmit Data Register */
/*! @{ */
#define LPI2C_MTDR_DATA_MASK (0xFFU)
#define LPI2C_MTDR_DATA_SHIFT (0U)
/*! DATA - Transmit Data
 */
#define LPI2C_MTDR_DATA(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MTDR_DATA_SHIFT)) & LPI2C_MTDR_DATA_MASK)
#define LPI2C_MTDR_CMD_MASK (0x700U)
#define LPI2C_MTDR_CMD_SHIFT (8U)
/*! CMD - Command Data
 *  0b000..Transmit DATA[7:0].
 *  0b001..Receive (DATA[7:0] + 1) bytes.
 *  0b010..Generate STOP condition.
 *  0b011..Receive and discard (DATA[7:0] + 1) bytes.
 *  0b100..Generate (repeated) START and transmit address in DATA[7:0].
 *  0b101..Generate (repeated) START and transmit address in DATA[7:0]. This transfer expects a NACK to be returned.
 *  0b110..Generate (repeated) START and transmit address in DATA[7:0] using high speed mode.
 *  0b111..Generate (repeated) START and transmit address in DATA[7:0] using high speed mode. This transfer expects a
 * NACK to be returned.
 */
#define LPI2C_MTDR_CMD(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MTDR_CMD_SHIFT)) & LPI2C_MTDR_CMD_MASK)
/*! @} */

/*! @name MRDR - Master Receive Data Register */
/*! @{ */
#define LPI2C_MRDR_DATA_MASK (0xFFU)
#define LPI2C_MRDR_DATA_SHIFT (0U)
/*! DATA - Receive Data
 */
#define LPI2C_MRDR_DATA(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MRDR_DATA_SHIFT)) & LPI2C_MRDR_DATA_MASK)
#define LPI2C_MRDR_RXEMPTY_MASK (0x4000U)
#define LPI2C_MRDR_RXEMPTY_SHIFT (14U)
/*! RXEMPTY - RX Empty
 *  0b0..Receive FIFO is not empty.
 *  0b1..Receive FIFO is empty.
 */
#define LPI2C_MRDR_RXEMPTY(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_MRDR_RXEMPTY_SHIFT)) & LPI2C_MRDR_RXEMPTY_MASK)
/*! @} */

/*! @name SCR - Slave Control Register */
/*! @{ */
#define LPI2C_SCR_SEN_MASK (0x1U)
#define LPI2C_SCR_SEN_SHIFT (0U)
/*! SEN - Slave Enable
 *  0b0..Slave mode is disabled.
 *  0b1..Slave mode is enabled.
 */
#define LPI2C_SCR_SEN(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SCR_SEN_SHIFT)) & LPI2C_SCR_SEN_MASK)
#define LPI2C_SCR_RST_MASK (0x2U)
#define LPI2C_SCR_RST_SHIFT (1U)
/*! RST - Software Reset
 *  0b0..Slave logic is not reset.
 *  0b1..Slave logic is reset.
 */
#define LPI2C_SCR_RST(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SCR_RST_SHIFT)) & LPI2C_SCR_RST_MASK)
#define LPI2C_SCR_FILTEN_MASK (0x10U)
#define LPI2C_SCR_FILTEN_SHIFT (4U)
/*! FILTEN - Filter Enable
 *  0b0..Disable digital filter and output delay counter for slave mode.
 *  0b1..Enable digital filter and output delay counter for slave mode.
 */
#define LPI2C_SCR_FILTEN(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SCR_FILTEN_SHIFT)) & LPI2C_SCR_FILTEN_MASK)
#define LPI2C_SCR_FILTDZ_MASK (0x20U)
#define LPI2C_SCR_FILTDZ_SHIFT (5U)
/*! FILTDZ - Filter Doze Enable
 *  0b0..Filter remains enabled in Doze mode.
 *  0b1..Filter is disabled in Doze mode.
 */
#define LPI2C_SCR_FILTDZ(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SCR_FILTDZ_SHIFT)) & LPI2C_SCR_FILTDZ_MASK)
#define LPI2C_SCR_RTF_MASK (0x100U)
#define LPI2C_SCR_RTF_SHIFT (8U)
/*! RTF - Reset Transmit FIFO
 *  0b0..No effect.
 *  0b1..Transmit Data Register is now empty.
 */
#define LPI2C_SCR_RTF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SCR_RTF_SHIFT)) & LPI2C_SCR_RTF_MASK)
#define LPI2C_SCR_RRF_MASK (0x200U)
#define LPI2C_SCR_RRF_SHIFT (9U)
/*! RRF - Reset Receive FIFO
 *  0b0..No effect.
 *  0b1..Receive Data Register is now empty.
 */
#define LPI2C_SCR_RRF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SCR_RRF_SHIFT)) & LPI2C_SCR_RRF_MASK)
/*! @} */

/*! @name SSR - Slave Status Register */
/*! @{ */
#define LPI2C_SSR_TDF_MASK (0x1U)
#define LPI2C_SSR_TDF_SHIFT (0U)
/*! TDF - Transmit Data Flag
 *  0b0..Transmit data not requested.
 *  0b1..Transmit data is requested.
 */
#define LPI2C_SSR_TDF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_TDF_SHIFT)) & LPI2C_SSR_TDF_MASK)
#define LPI2C_SSR_RDF_MASK (0x2U)
#define LPI2C_SSR_RDF_SHIFT (1U)
/*! RDF - Receive Data Flag
 *  0b0..Receive Data is not ready.
 *  0b1..Receive data is ready.
 */
#define LPI2C_SSR_RDF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_RDF_SHIFT)) & LPI2C_SSR_RDF_MASK)
#define LPI2C_SSR_AVF_MASK (0x4U)
#define LPI2C_SSR_AVF_SHIFT (2U)
/*! AVF - Address Valid Flag
 *  0b0..Address Status Register is not valid.
 *  0b1..Address Status Register is valid.
 */
#define LPI2C_SSR_AVF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_AVF_SHIFT)) & LPI2C_SSR_AVF_MASK)
#define LPI2C_SSR_TAF_MASK (0x8U)
#define LPI2C_SSR_TAF_SHIFT (3U)
/*! TAF - Transmit ACK Flag
 *  0b0..Transmit ACK/NACK is not required.
 *  0b1..Transmit ACK/NACK is required.
 */
#define LPI2C_SSR_TAF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_TAF_SHIFT)) & LPI2C_SSR_TAF_MASK)
#define LPI2C_SSR_RSF_MASK (0x100U)
#define LPI2C_SSR_RSF_SHIFT (8U)
/*! RSF - Repeated Start Flag
 *  0b0..Slave has not detected a Repeated START condition.
 *  0b1..Slave has detected a Repeated START condition.
 */
#define LPI2C_SSR_RSF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_RSF_SHIFT)) & LPI2C_SSR_RSF_MASK)
#define LPI2C_SSR_SDF_MASK (0x200U)
#define LPI2C_SSR_SDF_SHIFT (9U)
/*! SDF - STOP Detect Flag
 *  0b0..Slave has not detected a STOP condition.
 *  0b1..Slave has detected a STOP condition.
 */
#define LPI2C_SSR_SDF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_SDF_SHIFT)) & LPI2C_SSR_SDF_MASK)
#define LPI2C_SSR_BEF_MASK (0x400U)
#define LPI2C_SSR_BEF_SHIFT (10U)
/*! BEF - Bit Error Flag
 *  0b0..Slave has not detected a bit error.
 *  0b1..Slave has detected a bit error.
 */
#define LPI2C_SSR_BEF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_BEF_SHIFT)) & LPI2C_SSR_BEF_MASK)
#define LPI2C_SSR_FEF_MASK (0x800U)
#define LPI2C_SSR_FEF_SHIFT (11U)
/*! FEF - FIFO Error Flag
 *  0b0..FIFO underflow or overflow not detected.
 *  0b1..FIFO underflow or overflow detected.
 */
#define LPI2C_SSR_FEF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_FEF_SHIFT)) & LPI2C_SSR_FEF_MASK)
#define LPI2C_SSR_AM0F_MASK (0x1000U)
#define LPI2C_SSR_AM0F_SHIFT (12U)
/*! AM0F - Address Match 0 Flag
 *  0b0..Have not received ADDR0 matching address.
 *  0b1..Have received ADDR0 matching address.
 */
#define LPI2C_SSR_AM0F(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_AM0F_SHIFT)) & LPI2C_SSR_AM0F_MASK)
#define LPI2C_SSR_AM1F_MASK (0x2000U)
#define LPI2C_SSR_AM1F_SHIFT (13U)
/*! AM1F - Address Match 1 Flag
 *  0b0..Have not received ADDR1 or ADDR0/ADDR1 range matching address.
 *  0b1..Have received ADDR1 or ADDR0/ADDR1 range matching address.
 */
#define LPI2C_SSR_AM1F(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_AM1F_SHIFT)) & LPI2C_SSR_AM1F_MASK)
#define LPI2C_SSR_GCF_MASK (0x4000U)
#define LPI2C_SSR_GCF_SHIFT (14U)
/*! GCF - General Call Flag
 *  0b0..Slave has not detected the General Call Address or General Call Address disabled.
 *  0b1..Slave has detected the General Call Address.
 */
#define LPI2C_SSR_GCF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_GCF_SHIFT)) & LPI2C_SSR_GCF_MASK)
#define LPI2C_SSR_SARF_MASK (0x8000U)
#define LPI2C_SSR_SARF_SHIFT (15U)
/*! SARF - SMBus Alert Response Flag
 *  0b0..SMBus Alert Response disabled or not detected.
 *  0b1..SMBus Alert Response enabled and detected.
 */
#define LPI2C_SSR_SARF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_SARF_SHIFT)) & LPI2C_SSR_SARF_MASK)
#define LPI2C_SSR_SBF_MASK (0x1000000U)
#define LPI2C_SSR_SBF_SHIFT (24U)
/*! SBF - Slave Busy Flag
 *  0b0..I2C Slave is idle.
 *  0b1..I2C Slave is busy.
 */
#define LPI2C_SSR_SBF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_SBF_SHIFT)) & LPI2C_SSR_SBF_MASK)
#define LPI2C_SSR_BBF_MASK (0x2000000U)
#define LPI2C_SSR_BBF_SHIFT (25U)
/*! BBF - Bus Busy Flag
 *  0b0..I2C Bus is idle.
 *  0b1..I2C Bus is busy.
 */
#define LPI2C_SSR_BBF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_BBF_SHIFT)) & LPI2C_SSR_BBF_MASK)
/*! @} */

/*! @name SIER - Slave Interrupt Enable Register */
/*! @{ */
#define LPI2C_SIER_TDIE_MASK (0x1U)
#define LPI2C_SIER_TDIE_SHIFT (0U)
/*! TDIE - Transmit Data Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled
 */
#define LPI2C_SIER_TDIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_TDIE_SHIFT)) & LPI2C_SIER_TDIE_MASK)
#define LPI2C_SIER_RDIE_MASK (0x2U)
#define LPI2C_SIER_RDIE_SHIFT (1U)
/*! RDIE - Receive Data Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_SIER_RDIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_RDIE_SHIFT)) & LPI2C_SIER_RDIE_MASK)
#define LPI2C_SIER_AVIE_MASK (0x4U)
#define LPI2C_SIER_AVIE_SHIFT (2U)
/*! AVIE - Address Valid Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_SIER_AVIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_AVIE_SHIFT)) & LPI2C_SIER_AVIE_MASK)
#define LPI2C_SIER_TAIE_MASK (0x8U)
#define LPI2C_SIER_TAIE_SHIFT (3U)
/*! TAIE - Transmit ACK Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_SIER_TAIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_TAIE_SHIFT)) & LPI2C_SIER_TAIE_MASK)
#define LPI2C_SIER_RSIE_MASK (0x100U)
#define LPI2C_SIER_RSIE_SHIFT (8U)
/*! RSIE - Repeated Start Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_SIER_RSIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_RSIE_SHIFT)) & LPI2C_SIER_RSIE_MASK)
#define LPI2C_SIER_SDIE_MASK (0x200U)
#define LPI2C_SIER_SDIE_SHIFT (9U)
/*! SDIE - STOP Detect Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_SIER_SDIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_SDIE_SHIFT)) & LPI2C_SIER_SDIE_MASK)
#define LPI2C_SIER_BEIE_MASK (0x400U)
#define LPI2C_SIER_BEIE_SHIFT (10U)
/*! BEIE - Bit Error Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_SIER_BEIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_BEIE_SHIFT)) & LPI2C_SIER_BEIE_MASK)
#define LPI2C_SIER_FEIE_MASK (0x800U)
#define LPI2C_SIER_FEIE_SHIFT (11U)
/*! FEIE - FIFO Error Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_SIER_FEIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_FEIE_SHIFT)) & LPI2C_SIER_FEIE_MASK)
#define LPI2C_SIER_AM0IE_MASK (0x1000U)
#define LPI2C_SIER_AM0IE_SHIFT (12U)
/*! AM0IE - Address Match 0 Interrupt Enable
 *  0b0..Interrupt enabled.
 *  0b1..Interrupt disabled.
 */
#define LPI2C_SIER_AM0IE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_AM0IE_SHIFT)) & LPI2C_SIER_AM0IE_MASK)
#define LPI2C_SIER_AM1F_MASK (0x2000U)
#define LPI2C_SIER_AM1F_SHIFT (13U)
/*! AM1F - Address Match 1 Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_SIER_AM1F(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_AM1F_SHIFT)) & LPI2C_SIER_AM1F_MASK)
#define LPI2C_SIER_GCIE_MASK (0x4000U)
#define LPI2C_SIER_GCIE_SHIFT (14U)
/*! GCIE - General Call Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_SIER_GCIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_GCIE_SHIFT)) & LPI2C_SIER_GCIE_MASK)
#define LPI2C_SIER_SARIE_MASK (0x8000U)
#define LPI2C_SIER_SARIE_SHIFT (15U)
/*! SARIE - SMBus Alert Response Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPI2C_SIER_SARIE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_SARIE_SHIFT)) & LPI2C_SIER_SARIE_MASK)
/*! @} */

/*! @name SDER - Slave DMA Enable Register */
/*! @{ */
#define LPI2C_SDER_TDDE_MASK (0x1U)
#define LPI2C_SDER_TDDE_SHIFT (0U)
/*! TDDE - Transmit Data DMA Enable
 *  0b0..DMA request disabled.
 *  0b1..DMA request enabled
 */
#define LPI2C_SDER_TDDE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SDER_TDDE_SHIFT)) & LPI2C_SDER_TDDE_MASK)
#define LPI2C_SDER_RDDE_MASK (0x2U)
#define LPI2C_SDER_RDDE_SHIFT (1U)
/*! RDDE - Receive Data DMA Enable
 *  0b0..DMA request disabled.
 *  0b1..DMA request enabled.
 */
#define LPI2C_SDER_RDDE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SDER_RDDE_SHIFT)) & LPI2C_SDER_RDDE_MASK)
#define LPI2C_SDER_AVDE_MASK (0x4U)
#define LPI2C_SDER_AVDE_SHIFT (2U)
/*! AVDE - Address Valid DMA Enable
 *  0b0..DMA request disabled.
 *  0b1..DMA request enabled.
 */
#define LPI2C_SDER_AVDE(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SDER_AVDE_SHIFT)) & LPI2C_SDER_AVDE_MASK)
/*! @} */

/*! @name SCFGR1 - Slave Configuration Register 1 */
/*! @{ */
#define LPI2C_SCFGR1_ADRSTALL_MASK (0x1U)
#define LPI2C_SCFGR1_ADRSTALL_SHIFT (0U)
/*! ADRSTALL - Address SCL Stall
 *  0b0..Clock stretching disabled.
 *  0b1..Clock stretching enabled.
 */
#define LPI2C_SCFGR1_ADRSTALL(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_ADRSTALL_SHIFT)) & LPI2C_SCFGR1_ADRSTALL_MASK)
#define LPI2C_SCFGR1_RXSTALL_MASK (0x2U)
#define LPI2C_SCFGR1_RXSTALL_SHIFT (1U)
/*! RXSTALL - RX SCL Stall
 *  0b0..Clock stretching disabled.
 *  0b1..Clock stretching enabled.
 */
#define LPI2C_SCFGR1_RXSTALL(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_RXSTALL_SHIFT)) & LPI2C_SCFGR1_RXSTALL_MASK)
#define LPI2C_SCFGR1_TXDSTALL_MASK (0x4U)
#define LPI2C_SCFGR1_TXDSTALL_SHIFT (2U)
/*! TXDSTALL - TX Data SCL Stall
 *  0b0..Clock stretching disabled.
 *  0b1..Clock stretching enabled.
 */
#define LPI2C_SCFGR1_TXDSTALL(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_TXDSTALL_SHIFT)) & LPI2C_SCFGR1_TXDSTALL_MASK)
#define LPI2C_SCFGR1_ACKSTALL_MASK (0x8U)
#define LPI2C_SCFGR1_ACKSTALL_SHIFT (3U)
/*! ACKSTALL - ACK SCL Stall
 *  0b0..Clock stretching disabled.
 *  0b1..Clock stretching enabled.
 */
#define LPI2C_SCFGR1_ACKSTALL(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_ACKSTALL_SHIFT)) & LPI2C_SCFGR1_ACKSTALL_MASK)
#define LPI2C_SCFGR1_GCEN_MASK (0x100U)
#define LPI2C_SCFGR1_GCEN_SHIFT (8U)
/*! GCEN - General Call Enable
 *  0b0..General Call address is disabled.
 *  0b1..General call address is enabled.
 */
#define LPI2C_SCFGR1_GCEN(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_GCEN_SHIFT)) & LPI2C_SCFGR1_GCEN_MASK)
#define LPI2C_SCFGR1_SAEN_MASK (0x200U)
#define LPI2C_SCFGR1_SAEN_SHIFT (9U)
/*! SAEN - SMBus Alert Enable
 *  0b0..Disables match on SMBus Alert.
 *  0b1..Enables match on SMBus Alert.
 */
#define LPI2C_SCFGR1_SAEN(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_SAEN_SHIFT)) & LPI2C_SCFGR1_SAEN_MASK)
#define LPI2C_SCFGR1_TXCFG_MASK (0x400U)
#define LPI2C_SCFGR1_TXCFG_SHIFT (10U)
/*! TXCFG - Transmit Flag Configuration
 *  0b0..Transmit Data Flag will only assert during a slave-transmit transfer when the transmit data register is empty.
 *  0b1..Transmit Data Flag will assert whenever the transmit data register is empty.
 */
#define LPI2C_SCFGR1_TXCFG(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_TXCFG_SHIFT)) & LPI2C_SCFGR1_TXCFG_MASK)
#define LPI2C_SCFGR1_RXCFG_MASK (0x800U)
#define LPI2C_SCFGR1_RXCFG_SHIFT (11U)
/*! RXCFG - Receive Data Configuration
 *  0b0..Reading the receive data register will return receive data and clear the receive data flag.
 *  0b1..Reading the receive data register when the address valid flag is set will return the address status
 *       register and clear the address valid flag. Reading the receive data register when the address valid flag is
 *       clear will return receive data and clear the receive data flag.
 */
#define LPI2C_SCFGR1_RXCFG(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_RXCFG_SHIFT)) & LPI2C_SCFGR1_RXCFG_MASK)
#define LPI2C_SCFGR1_IGNACK_MASK (0x1000U)
#define LPI2C_SCFGR1_IGNACK_SHIFT (12U)
/*! IGNACK - Ignore NACK
 *  0b0..Slave will end transfer when NACK detected.
 *  0b1..Slave will not end transfer when NACK detected.
 */
#define LPI2C_SCFGR1_IGNACK(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_IGNACK_SHIFT)) & LPI2C_SCFGR1_IGNACK_MASK)
#define LPI2C_SCFGR1_HSMEN_MASK (0x2000U)
#define LPI2C_SCFGR1_HSMEN_SHIFT (13U)
/*! HSMEN - High Speed Mode Enable
 *  0b0..Disables detection of Hs-mode master code.
 *  0b1..Enables detection of Hs-mode master code.
 */
#define LPI2C_SCFGR1_HSMEN(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_HSMEN_SHIFT)) & LPI2C_SCFGR1_HSMEN_MASK)
#define LPI2C_SCFGR1_ADDRCFG_MASK (0x70000U)
#define LPI2C_SCFGR1_ADDRCFG_SHIFT (16U)
/*! ADDRCFG - Address Configuration
 *  0b000..Address match 0 (7-bit).
 *  0b001..Address match 0 (10-bit).
 *  0b010..Address match 0 (7-bit) or Address match 1 (7-bit).
 *  0b011..Address match 0 (10-bit) or Address match 1 (10-bit).
 *  0b100..Address match 0 (7-bit) or Address match 1 (10-bit).
 *  0b101..Address match 0 (10-bit) or Address match 1 (7-bit).
 *  0b110..From Address match 0 (7-bit) to Address match 1 (7-bit).
 *  0b111..From Address match 0 (10-bit) to Address match 1 (10-bit).
 */
#define LPI2C_SCFGR1_ADDRCFG(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_ADDRCFG_SHIFT)) & LPI2C_SCFGR1_ADDRCFG_MASK)
/*! @} */

/*! @name SCFGR2 - Slave Configuration Register 2 */
/*! @{ */
#define LPI2C_SCFGR2_CLKHOLD_MASK (0xFU)
#define LPI2C_SCFGR2_CLKHOLD_SHIFT (0U)
/*! CLKHOLD - Clock Hold Time
 */
#define LPI2C_SCFGR2_CLKHOLD(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR2_CLKHOLD_SHIFT)) & LPI2C_SCFGR2_CLKHOLD_MASK)
#define LPI2C_SCFGR2_DATAVD_MASK (0x3F00U)
#define LPI2C_SCFGR2_DATAVD_SHIFT (8U)
/*! DATAVD - Data Valid Delay
 */
#define LPI2C_SCFGR2_DATAVD(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR2_DATAVD_SHIFT)) & LPI2C_SCFGR2_DATAVD_MASK)
#define LPI2C_SCFGR2_FILTSCL_MASK (0xF0000U)
#define LPI2C_SCFGR2_FILTSCL_SHIFT (16U)
/*! FILTSCL - Glitch Filter SCL
 */
#define LPI2C_SCFGR2_FILTSCL(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR2_FILTSCL_SHIFT)) & LPI2C_SCFGR2_FILTSCL_MASK)
#define LPI2C_SCFGR2_FILTSDA_MASK (0xF000000U)
#define LPI2C_SCFGR2_FILTSDA_SHIFT (24U)
/*! FILTSDA - Glitch Filter SDA
 */
#define LPI2C_SCFGR2_FILTSDA(x) \
    (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR2_FILTSDA_SHIFT)) & LPI2C_SCFGR2_FILTSDA_MASK)
/*! @} */

/*! @name SAMR - Slave Address Match Register */
/*! @{ */
#define LPI2C_SAMR_ADDR0_MASK (0x7FEU)
#define LPI2C_SAMR_ADDR0_SHIFT (1U)
/*! ADDR0 - Address 0 Value
 */
#define LPI2C_SAMR_ADDR0(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SAMR_ADDR0_SHIFT)) & LPI2C_SAMR_ADDR0_MASK)
#define LPI2C_SAMR_ADDR1_MASK (0x7FE0000U)
#define LPI2C_SAMR_ADDR1_SHIFT (17U)
/*! ADDR1 - Address 1 Value
 */
#define LPI2C_SAMR_ADDR1(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SAMR_ADDR1_SHIFT)) & LPI2C_SAMR_ADDR1_MASK)
/*! @} */

/*! @name SASR - Slave Address Status Register */
/*! @{ */
#define LPI2C_SASR_RADDR_MASK (0x7FFU)
#define LPI2C_SASR_RADDR_SHIFT (0U)
/*! RADDR - Received Address
 */
#define LPI2C_SASR_RADDR(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SASR_RADDR_SHIFT)) & LPI2C_SASR_RADDR_MASK)
#define LPI2C_SASR_ANV_MASK (0x4000U)
#define LPI2C_SASR_ANV_SHIFT (14U)
/*! ANV - Address Not Valid
 *  0b0..RADDR is valid.
 *  0b1..RADDR is not valid.
 */
#define LPI2C_SASR_ANV(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SASR_ANV_SHIFT)) & LPI2C_SASR_ANV_MASK)
/*! @} */

/*! @name STAR - Slave Transmit ACK Register */
/*! @{ */
#define LPI2C_STAR_TXNACK_MASK (0x1U)
#define LPI2C_STAR_TXNACK_SHIFT (0U)
/*! TXNACK - Transmit NACK
 *  0b0..Transmit ACK for received word.
 *  0b1..Transmit NACK for received word.
 */
#define LPI2C_STAR_TXNACK(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_STAR_TXNACK_SHIFT)) & LPI2C_STAR_TXNACK_MASK)
/*! @} */

/*! @name STDR - Slave Transmit Data Register */
/*! @{ */
#define LPI2C_STDR_DATA_MASK (0xFFU)
#define LPI2C_STDR_DATA_SHIFT (0U)
/*! DATA - Transmit Data
 */
#define LPI2C_STDR_DATA(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_STDR_DATA_SHIFT)) & LPI2C_STDR_DATA_MASK)
/*! @} */

/*! @name SRDR - Slave Receive Data Register */
/*! @{ */
#define LPI2C_SRDR_DATA_MASK (0xFFU)
#define LPI2C_SRDR_DATA_SHIFT (0U)
/*! DATA - Receive Data
 */
#define LPI2C_SRDR_DATA(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SRDR_DATA_SHIFT)) & LPI2C_SRDR_DATA_MASK)
#define LPI2C_SRDR_RXEMPTY_MASK (0x4000U)
#define LPI2C_SRDR_RXEMPTY_SHIFT (14U)
/*! RXEMPTY - RX Empty
 *  0b0..The Receive Data Register is not empty.
 *  0b1..The Receive Data Register is empty.
 */
#define LPI2C_SRDR_RXEMPTY(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SRDR_RXEMPTY_SHIFT)) & LPI2C_SRDR_RXEMPTY_MASK)
#define LPI2C_SRDR_SOF_MASK (0x8000U)
#define LPI2C_SRDR_SOF_SHIFT (15U)
/*! SOF - Start Of Frame
 *  0b0..Indicates this is not the first data word since a (repeated) START or STOP condition.
 *  0b1..Indicates this is the first data word since a (repeated) START or STOP condition.
 */
#define LPI2C_SRDR_SOF(x) (((uint32_t)(((uint32_t)(x)) << LPI2C_SRDR_SOF_SHIFT)) & LPI2C_SRDR_SOF_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group LPI2C_Register_Masks */

/* LPI2C - Peripheral instance base addresses */
/** Peripheral LPI2C0 base address */
#define LPI2C0_BASE (0x400C0000u)
/** Peripheral LPI2C0 base pointer */
#define LPI2C0 ((LPI2C_Type *)LPI2C0_BASE)
/** Peripheral LPI2C1 base address */
#define LPI2C1_BASE (0x400C1000u)
/** Peripheral LPI2C1 base pointer */
#define LPI2C1 ((LPI2C_Type *)LPI2C1_BASE)
/** Peripheral LPI2C2 base address */
#define LPI2C2_BASE (0x40042000u)
/** Peripheral LPI2C2 base pointer */
#define LPI2C2 ((LPI2C_Type *)LPI2C2_BASE)
/** Array initializer of LPI2C peripheral base addresses */
#define LPI2C_BASE_ADDRS                      \
    {                                         \
        LPI2C0_BASE, LPI2C1_BASE, LPI2C2_BASE \
    }
/** Array initializer of LPI2C peripheral base pointers */
#define LPI2C_BASE_PTRS        \
    {                          \
        LPI2C0, LPI2C1, LPI2C2 \
    }
/** Interrupt vectors for the LPI2C peripheral type */
#define LPI2C_IRQS                            \
    {                                         \
        LPI2C0_IRQn, LPI2C1_IRQn, LPI2C2_IRQn \
    }

/*!
 * @}
 */ /* end of group LPI2C_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- LPIT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPIT_Peripheral_Access_Layer LPIT Peripheral Access Layer
 * @{
 */

/** LPIT - Register Layout Typedef */
typedef struct
{
    __I uint32_t VERID;   /**< Version ID Register, offset: 0x0 */
    __I uint32_t PARAM;   /**< Parameter Register, offset: 0x4 */
    __IO uint32_t MCR;    /**< Module Control Register, offset: 0x8 */
    __IO uint32_t MSR;    /**< Module Status Register, offset: 0xC */
    __IO uint32_t MIER;   /**< Module Interrupt Enable Register, offset: 0x10 */
    __IO uint32_t SETTEN; /**< Set Timer Enable Register, offset: 0x14 */
    __O uint32_t CLRTEN;  /**< Clear Timer Enable Register, offset: 0x18 */
    uint8_t RESERVED_0[4];
    struct
    {                        /* offset: 0x20, array step: 0x10 */
        __IO uint32_t TVAL;  /**< Timer Value Register, array offset: 0x20, array step: 0x10 */
        __I uint32_t CVAL;   /**< Current Timer Value, array offset: 0x24, array step: 0x10 */
        __IO uint32_t TCTRL; /**< Timer Control Register, array offset: 0x28, array step: 0x10 */
        uint8_t RESERVED_0[4];
    } CHANNEL[4];
} LPIT_Type;

/* ----------------------------------------------------------------------------
   -- LPIT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPIT_Register_Masks LPIT Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */
#define LPIT_VERID_FEATURE_MASK (0xFFFFU)
#define LPIT_VERID_FEATURE_SHIFT (0U)
/*! FEATURE - Feature Number
 */
#define LPIT_VERID_FEATURE(x) (((uint32_t)(((uint32_t)(x)) << LPIT_VERID_FEATURE_SHIFT)) & LPIT_VERID_FEATURE_MASK)
#define LPIT_VERID_MINOR_MASK (0xFF0000U)
#define LPIT_VERID_MINOR_SHIFT (16U)
/*! MINOR - Minor Version Number
 */
#define LPIT_VERID_MINOR(x) (((uint32_t)(((uint32_t)(x)) << LPIT_VERID_MINOR_SHIFT)) & LPIT_VERID_MINOR_MASK)
#define LPIT_VERID_MAJOR_MASK (0xFF000000U)
#define LPIT_VERID_MAJOR_SHIFT (24U)
/*! MAJOR - Major Version Number
 */
#define LPIT_VERID_MAJOR(x) (((uint32_t)(((uint32_t)(x)) << LPIT_VERID_MAJOR_SHIFT)) & LPIT_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */
#define LPIT_PARAM_CHANNEL_MASK (0xFFU)
#define LPIT_PARAM_CHANNEL_SHIFT (0U)
/*! CHANNEL - Number of Timer Channels
 */
#define LPIT_PARAM_CHANNEL(x) (((uint32_t)(((uint32_t)(x)) << LPIT_PARAM_CHANNEL_SHIFT)) & LPIT_PARAM_CHANNEL_MASK)
#define LPIT_PARAM_EXT_TRIG_MASK (0xFF00U)
#define LPIT_PARAM_EXT_TRIG_SHIFT (8U)
/*! EXT_TRIG - Number of External Trigger Inputs
 */
#define LPIT_PARAM_EXT_TRIG(x) (((uint32_t)(((uint32_t)(x)) << LPIT_PARAM_EXT_TRIG_SHIFT)) & LPIT_PARAM_EXT_TRIG_MASK)
/*! @} */

/*! @name MCR - Module Control Register */
/*! @{ */
#define LPIT_MCR_M_CEN_MASK (0x1U)
#define LPIT_MCR_M_CEN_SHIFT (0U)
/*! M_CEN - Module Clock Enable
 *  0b0..Protocol clock to timers is disabled
 *  0b1..Protocol clock to timers is enabled
 */
#define LPIT_MCR_M_CEN(x) (((uint32_t)(((uint32_t)(x)) << LPIT_MCR_M_CEN_SHIFT)) & LPIT_MCR_M_CEN_MASK)
#define LPIT_MCR_SW_RST_MASK (0x2U)
#define LPIT_MCR_SW_RST_SHIFT (1U)
/*! SW_RST - Software Reset Bit
 *  0b0..Timer channels and registers are not reset
 *  0b1..Timer channels and registers are reset
 */
#define LPIT_MCR_SW_RST(x) (((uint32_t)(((uint32_t)(x)) << LPIT_MCR_SW_RST_SHIFT)) & LPIT_MCR_SW_RST_MASK)
#define LPIT_MCR_DOZE_EN_MASK (0x4U)
#define LPIT_MCR_DOZE_EN_SHIFT (2U)
/*! DOZE_EN - DOZE Mode Enable Bit
 *  0b0..Timer channels are stopped in DOZE mode
 *  0b1..Timer channels continue to run in DOZE mode
 */
#define LPIT_MCR_DOZE_EN(x) (((uint32_t)(((uint32_t)(x)) << LPIT_MCR_DOZE_EN_SHIFT)) & LPIT_MCR_DOZE_EN_MASK)
#define LPIT_MCR_DBG_EN_MASK (0x8U)
#define LPIT_MCR_DBG_EN_SHIFT (3U)
/*! DBG_EN - Debug Enable Bit
 *  0b0..Timer channels are stopped in Debug mode
 *  0b1..Timer channels continue to run in Debug mode
 */
#define LPIT_MCR_DBG_EN(x) (((uint32_t)(((uint32_t)(x)) << LPIT_MCR_DBG_EN_SHIFT)) & LPIT_MCR_DBG_EN_MASK)
/*! @} */

/*! @name MSR - Module Status Register */
/*! @{ */
#define LPIT_MSR_TIF0_MASK (0x1U)
#define LPIT_MSR_TIF0_SHIFT (0U)
/*! TIF0 - Channel 0 Timer Interrupt Flag
 *  0b0..Timer has not timed out
 *  0b1..Timeout has occurred
 */
#define LPIT_MSR_TIF0(x) (((uint32_t)(((uint32_t)(x)) << LPIT_MSR_TIF0_SHIFT)) & LPIT_MSR_TIF0_MASK)
#define LPIT_MSR_TIF1_MASK (0x2U)
#define LPIT_MSR_TIF1_SHIFT (1U)
/*! TIF1 - Channel 1 Timer Interrupt Flag
 *  0b0..Timer has not timed out
 *  0b1..Timeout has occurred
 */
#define LPIT_MSR_TIF1(x) (((uint32_t)(((uint32_t)(x)) << LPIT_MSR_TIF1_SHIFT)) & LPIT_MSR_TIF1_MASK)
#define LPIT_MSR_TIF2_MASK (0x4U)
#define LPIT_MSR_TIF2_SHIFT (2U)
/*! TIF2 - Channel 2 Timer Interrupt Flag
 *  0b0..Timer has not timed out
 *  0b1..Timeout has occurred
 */
#define LPIT_MSR_TIF2(x) (((uint32_t)(((uint32_t)(x)) << LPIT_MSR_TIF2_SHIFT)) & LPIT_MSR_TIF2_MASK)
#define LPIT_MSR_TIF3_MASK (0x8U)
#define LPIT_MSR_TIF3_SHIFT (3U)
/*! TIF3 - Channel 3 Timer Interrupt Flag
 *  0b0..Timer has not timed out
 *  0b1..Timeout has occurred
 */
#define LPIT_MSR_TIF3(x) (((uint32_t)(((uint32_t)(x)) << LPIT_MSR_TIF3_SHIFT)) & LPIT_MSR_TIF3_MASK)
/*! @} */

/*! @name MIER - Module Interrupt Enable Register */
/*! @{ */
#define LPIT_MIER_TIE0_MASK (0x1U)
#define LPIT_MIER_TIE0_SHIFT (0U)
/*! TIE0 - Channel 0 Timer Interrupt Enable
 *  0b0..Interrupt generation is disabled
 *  0b1..Interrupt generation is enabled
 */
#define LPIT_MIER_TIE0(x) (((uint32_t)(((uint32_t)(x)) << LPIT_MIER_TIE0_SHIFT)) & LPIT_MIER_TIE0_MASK)
#define LPIT_MIER_TIE1_MASK (0x2U)
#define LPIT_MIER_TIE1_SHIFT (1U)
/*! TIE1 - Channel 1 Timer Interrupt Enable
 *  0b0..Interrupt generation is disabled
 *  0b1..Interrupt generation is enabled
 */
#define LPIT_MIER_TIE1(x) (((uint32_t)(((uint32_t)(x)) << LPIT_MIER_TIE1_SHIFT)) & LPIT_MIER_TIE1_MASK)
#define LPIT_MIER_TIE2_MASK (0x4U)
#define LPIT_MIER_TIE2_SHIFT (2U)
/*! TIE2 - Channel 2 Timer Interrupt Enable
 *  0b0..Interrupt generation is disabled
 *  0b1..Interrupt generation is enabled
 */
#define LPIT_MIER_TIE2(x) (((uint32_t)(((uint32_t)(x)) << LPIT_MIER_TIE2_SHIFT)) & LPIT_MIER_TIE2_MASK)
#define LPIT_MIER_TIE3_MASK (0x8U)
#define LPIT_MIER_TIE3_SHIFT (3U)
/*! TIE3 - Channel 3 Timer Interrupt Enable
 *  0b0..Interrupt generation is disabled
 *  0b1..Interrupt generation is enabled
 */
#define LPIT_MIER_TIE3(x) (((uint32_t)(((uint32_t)(x)) << LPIT_MIER_TIE3_SHIFT)) & LPIT_MIER_TIE3_MASK)
/*! @} */

/*! @name SETTEN - Set Timer Enable Register */
/*! @{ */
#define LPIT_SETTEN_SET_T_EN_0_MASK (0x1U)
#define LPIT_SETTEN_SET_T_EN_0_SHIFT (0U)
/*! SET_T_EN_0 - Set Timer 0 Enable
 *  0b0..No effect
 *  0b1..Enables the Timer Channel 0
 */
#define LPIT_SETTEN_SET_T_EN_0(x) \
    (((uint32_t)(((uint32_t)(x)) << LPIT_SETTEN_SET_T_EN_0_SHIFT)) & LPIT_SETTEN_SET_T_EN_0_MASK)
#define LPIT_SETTEN_SET_T_EN_1_MASK (0x2U)
#define LPIT_SETTEN_SET_T_EN_1_SHIFT (1U)
/*! SET_T_EN_1 - Set Timer 1 Enable
 *  0b0..No Effect
 *  0b1..Enables the Timer Channel 1
 */
#define LPIT_SETTEN_SET_T_EN_1(x) \
    (((uint32_t)(((uint32_t)(x)) << LPIT_SETTEN_SET_T_EN_1_SHIFT)) & LPIT_SETTEN_SET_T_EN_1_MASK)
#define LPIT_SETTEN_SET_T_EN_2_MASK (0x4U)
#define LPIT_SETTEN_SET_T_EN_2_SHIFT (2U)
/*! SET_T_EN_2 - Set Timer 2 Enable
 *  0b0..No Effect
 *  0b1..Enables the Timer Channel 2
 */
#define LPIT_SETTEN_SET_T_EN_2(x) \
    (((uint32_t)(((uint32_t)(x)) << LPIT_SETTEN_SET_T_EN_2_SHIFT)) & LPIT_SETTEN_SET_T_EN_2_MASK)
#define LPIT_SETTEN_SET_T_EN_3_MASK (0x8U)
#define LPIT_SETTEN_SET_T_EN_3_SHIFT (3U)
/*! SET_T_EN_3 - Set Timer 3 Enable
 *  0b0..No effect
 *  0b1..Enables the Timer Channel 3
 */
#define LPIT_SETTEN_SET_T_EN_3(x) \
    (((uint32_t)(((uint32_t)(x)) << LPIT_SETTEN_SET_T_EN_3_SHIFT)) & LPIT_SETTEN_SET_T_EN_3_MASK)
/*! @} */

/*! @name CLRTEN - Clear Timer Enable Register */
/*! @{ */
#define LPIT_CLRTEN_CLR_T_EN_0_MASK (0x1U)
#define LPIT_CLRTEN_CLR_T_EN_0_SHIFT (0U)
/*! CLR_T_EN_0 - Clear Timer 0 Enable
 *  0b0..No action
 *  0b1..Clear T_EN bit for Timer Channel 0
 */
#define LPIT_CLRTEN_CLR_T_EN_0(x) \
    (((uint32_t)(((uint32_t)(x)) << LPIT_CLRTEN_CLR_T_EN_0_SHIFT)) & LPIT_CLRTEN_CLR_T_EN_0_MASK)
#define LPIT_CLRTEN_CLR_T_EN_1_MASK (0x2U)
#define LPIT_CLRTEN_CLR_T_EN_1_SHIFT (1U)
/*! CLR_T_EN_1 - Clear Timer 1 Enable
 *  0b0..No Action
 *  0b1..Clear T_EN bit for Timer Channel 1
 */
#define LPIT_CLRTEN_CLR_T_EN_1(x) \
    (((uint32_t)(((uint32_t)(x)) << LPIT_CLRTEN_CLR_T_EN_1_SHIFT)) & LPIT_CLRTEN_CLR_T_EN_1_MASK)
#define LPIT_CLRTEN_CLR_T_EN_2_MASK (0x4U)
#define LPIT_CLRTEN_CLR_T_EN_2_SHIFT (2U)
/*! CLR_T_EN_2 - Clear Timer 2 Enable
 *  0b0..No Action
 *  0b1..Clear T_EN bit for Timer Channel 2
 */
#define LPIT_CLRTEN_CLR_T_EN_2(x) \
    (((uint32_t)(((uint32_t)(x)) << LPIT_CLRTEN_CLR_T_EN_2_SHIFT)) & LPIT_CLRTEN_CLR_T_EN_2_MASK)
#define LPIT_CLRTEN_CLR_T_EN_3_MASK (0x8U)
#define LPIT_CLRTEN_CLR_T_EN_3_SHIFT (3U)
/*! CLR_T_EN_3 - Clear Timer 3 Enable
 *  0b0..No Action
 *  0b1..Clear T_EN bit for Timer Channel 3
 */
#define LPIT_CLRTEN_CLR_T_EN_3(x) \
    (((uint32_t)(((uint32_t)(x)) << LPIT_CLRTEN_CLR_T_EN_3_SHIFT)) & LPIT_CLRTEN_CLR_T_EN_3_MASK)
/*! @} */

/*! @name TVAL - Timer Value Register */
/*! @{ */
#define LPIT_TVAL_TMR_VAL_MASK (0xFFFFFFFFU)
#define LPIT_TVAL_TMR_VAL_SHIFT (0U)
/*! TMR_VAL - Timer Value
 *  0b00000000000000000000000000000000..Invalid load value in compare modes
 */
#define LPIT_TVAL_TMR_VAL(x) (((uint32_t)(((uint32_t)(x)) << LPIT_TVAL_TMR_VAL_SHIFT)) & LPIT_TVAL_TMR_VAL_MASK)
/*! @} */

/* The count of LPIT_TVAL */
#define LPIT_TVAL_COUNT (4U)

/*! @name CVAL - Current Timer Value */
/*! @{ */
#define LPIT_CVAL_TMR_CUR_VAL_MASK (0xFFFFFFFFU)
#define LPIT_CVAL_TMR_CUR_VAL_SHIFT (0U)
/*! TMR_CUR_VAL - Current Timer Value
 */
#define LPIT_CVAL_TMR_CUR_VAL(x) \
    (((uint32_t)(((uint32_t)(x)) << LPIT_CVAL_TMR_CUR_VAL_SHIFT)) & LPIT_CVAL_TMR_CUR_VAL_MASK)
/*! @} */

/* The count of LPIT_CVAL */
#define LPIT_CVAL_COUNT (4U)

/*! @name TCTRL - Timer Control Register */
/*! @{ */
#define LPIT_TCTRL_T_EN_MASK (0x1U)
#define LPIT_TCTRL_T_EN_SHIFT (0U)
/*! T_EN - Timer Enable
 *  0b0..Timer Channel is disabled
 *  0b1..Timer Channel is enabled
 */
#define LPIT_TCTRL_T_EN(x) (((uint32_t)(((uint32_t)(x)) << LPIT_TCTRL_T_EN_SHIFT)) & LPIT_TCTRL_T_EN_MASK)
#define LPIT_TCTRL_CHAIN_MASK (0x2U)
#define LPIT_TCTRL_CHAIN_SHIFT (1U)
/*! CHAIN - Chain Channel
 *  0b0..Channel Chaining is disabled. Channel Timer runs independently.
 *  0b1..Channel Chaining is enabled. Timer decrements on previous channel's timeout
 */
#define LPIT_TCTRL_CHAIN(x) (((uint32_t)(((uint32_t)(x)) << LPIT_TCTRL_CHAIN_SHIFT)) & LPIT_TCTRL_CHAIN_MASK)
#define LPIT_TCTRL_MODE_MASK (0xCU)
#define LPIT_TCTRL_MODE_SHIFT (2U)
/*! MODE - Timer Operation Mode
 *  0b00..32-bit Periodic Counter
 *  0b01..Dual 16-bit Periodic Counter
 *  0b10..32-bit Trigger Accumulator
 *  0b11..32-bit Trigger Input Capture
 */
#define LPIT_TCTRL_MODE(x) (((uint32_t)(((uint32_t)(x)) << LPIT_TCTRL_MODE_SHIFT)) & LPIT_TCTRL_MODE_MASK)
#define LPIT_TCTRL_TSOT_MASK (0x10000U)
#define LPIT_TCTRL_TSOT_SHIFT (16U)
/*! TSOT - Timer Start On Trigger
 *  0b0..Timer starts to decrement immediately based on restart condition (controlled by TSOI bit)
 *  0b1..Timer starts to decrement when rising edge on selected trigger is detected
 */
#define LPIT_TCTRL_TSOT(x) (((uint32_t)(((uint32_t)(x)) << LPIT_TCTRL_TSOT_SHIFT)) & LPIT_TCTRL_TSOT_MASK)
#define LPIT_TCTRL_TSOI_MASK (0x20000U)
#define LPIT_TCTRL_TSOI_SHIFT (17U)
/*! TSOI - Timer Stop On Interrupt
 *  0b0..Timer does not stop after timeout
 *  0b1..Timer will stop after timeout and will restart after rising edge on the T_EN bit is detected (i.e. timer
 *       channel is disabled and then enabled)
 */
#define LPIT_TCTRL_TSOI(x) (((uint32_t)(((uint32_t)(x)) << LPIT_TCTRL_TSOI_SHIFT)) & LPIT_TCTRL_TSOI_MASK)
#define LPIT_TCTRL_TROT_MASK (0x40000U)
#define LPIT_TCTRL_TROT_SHIFT (18U)
/*! TROT - Timer Reload On Trigger
 *  0b0..Timer will not reload on selected trigger
 *  0b1..Timer will reload on selected trigger
 */
#define LPIT_TCTRL_TROT(x) (((uint32_t)(((uint32_t)(x)) << LPIT_TCTRL_TROT_SHIFT)) & LPIT_TCTRL_TROT_MASK)
#define LPIT_TCTRL_TRG_SRC_MASK (0x800000U)
#define LPIT_TCTRL_TRG_SRC_SHIFT (23U)
/*! TRG_SRC - Trigger Source
 *  0b0..Trigger source selected in external
 *  0b1..Trigger source selected is the internal trigger
 */
#define LPIT_TCTRL_TRG_SRC(x) (((uint32_t)(((uint32_t)(x)) << LPIT_TCTRL_TRG_SRC_SHIFT)) & LPIT_TCTRL_TRG_SRC_MASK)
#define LPIT_TCTRL_TRG_SEL_MASK (0xF000000U)
#define LPIT_TCTRL_TRG_SEL_SHIFT (24U)
/*! TRG_SEL - Trigger Select
 *  0b0000..Timer channel 0 trigger source is selected
 *  0b0001..Timer channel 1 trigger source is selected
 *  0b0010..Timer channel 2 trigger source is selected
 */
#define LPIT_TCTRL_TRG_SEL(x) (((uint32_t)(((uint32_t)(x)) << LPIT_TCTRL_TRG_SEL_SHIFT)) & LPIT_TCTRL_TRG_SEL_MASK)
/*! @} */

/* The count of LPIT_TCTRL */
#define LPIT_TCTRL_COUNT (4U)

/*!
 * @}
 */ /* end of group LPIT_Register_Masks */

/* LPIT - Peripheral instance base addresses */
/** Peripheral LPIT0 base address */
#define LPIT0_BASE (0x40030000u)
/** Peripheral LPIT0 base pointer */
#define LPIT0 ((LPIT_Type *)LPIT0_BASE)
/** Array initializer of LPIT peripheral base addresses */
#define LPIT_BASE_ADDRS \
    {                   \
        LPIT0_BASE      \
    }
/** Array initializer of LPIT peripheral base pointers */
#define LPIT_BASE_PTRS \
    {                  \
        LPIT0          \
    }
/** Interrupt vectors for the LPIT peripheral type */
#define LPIT_IRQS                                          \
    {                                                      \
        {                                                  \
            LPIT0_IRQn, LPIT0_IRQn, LPIT0_IRQn, LPIT0_IRQn \
        }                                                  \
    }

/*!
 * @}
 */ /* end of group LPIT_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- LPSPI Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPSPI_Peripheral_Access_Layer LPSPI Peripheral Access Layer
 * @{
 */

/** LPSPI - Register Layout Typedef */
typedef struct
{
    __I uint32_t VERID; /**< Version ID Register, offset: 0x0 */
    __I uint32_t PARAM; /**< Parameter Register, offset: 0x4 */
    uint8_t RESERVED_0[8];
    __IO uint32_t CR;    /**< Control Register, offset: 0x10 */
    __IO uint32_t SR;    /**< Status Register, offset: 0x14 */
    __IO uint32_t IER;   /**< Interrupt Enable Register, offset: 0x18 */
    __IO uint32_t DER;   /**< DMA Enable Register, offset: 0x1C */
    __IO uint32_t CFGR0; /**< Configuration Register 0, offset: 0x20 */
    __IO uint32_t CFGR1; /**< Configuration Register 1, offset: 0x24 */
    uint8_t RESERVED_1[8];
    __IO uint32_t DMR0; /**< Data Match Register 0, offset: 0x30 */
    __IO uint32_t DMR1; /**< Data Match Register 1, offset: 0x34 */
    uint8_t RESERVED_2[8];
    __IO uint32_t CCR; /**< Clock Configuration Register, offset: 0x40 */
    uint8_t RESERVED_3[20];
    __IO uint32_t FCR; /**< FIFO Control Register, offset: 0x58 */
    __I uint32_t FSR;  /**< FIFO Status Register, offset: 0x5C */
    __IO uint32_t TCR; /**< Transmit Command Register, offset: 0x60 */
    __O uint32_t TDR;  /**< Transmit Data Register, offset: 0x64 */
    uint8_t RESERVED_4[8];
    __I uint32_t RSR; /**< Receive Status Register, offset: 0x70 */
    __I uint32_t RDR; /**< Receive Data Register, offset: 0x74 */
} LPSPI_Type;

/* ----------------------------------------------------------------------------
   -- LPSPI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPSPI_Register_Masks LPSPI Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */
#define LPSPI_VERID_FEATURE_MASK (0xFFFFU)
#define LPSPI_VERID_FEATURE_SHIFT (0U)
/*! FEATURE - Module Identification Number
 *  0b0000000000000100..Standard feature set supporting 32-bit shift register.
 */
#define LPSPI_VERID_FEATURE(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_VERID_FEATURE_SHIFT)) & LPSPI_VERID_FEATURE_MASK)
#define LPSPI_VERID_MINOR_MASK (0xFF0000U)
#define LPSPI_VERID_MINOR_SHIFT (16U)
/*! MINOR - Minor Version Number
 */
#define LPSPI_VERID_MINOR(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_VERID_MINOR_SHIFT)) & LPSPI_VERID_MINOR_MASK)
#define LPSPI_VERID_MAJOR_MASK (0xFF000000U)
#define LPSPI_VERID_MAJOR_SHIFT (24U)
/*! MAJOR - Major Version Number
 */
#define LPSPI_VERID_MAJOR(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_VERID_MAJOR_SHIFT)) & LPSPI_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */
#define LPSPI_PARAM_TXFIFO_MASK (0xFFU)
#define LPSPI_PARAM_TXFIFO_SHIFT (0U)
/*! TXFIFO - Transmit FIFO Size
 */
#define LPSPI_PARAM_TXFIFO(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_PARAM_TXFIFO_SHIFT)) & LPSPI_PARAM_TXFIFO_MASK)
#define LPSPI_PARAM_RXFIFO_MASK (0xFF00U)
#define LPSPI_PARAM_RXFIFO_SHIFT (8U)
/*! RXFIFO - Receive FIFO Size
 */
#define LPSPI_PARAM_RXFIFO(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_PARAM_RXFIFO_SHIFT)) & LPSPI_PARAM_RXFIFO_MASK)
/*! @} */

/*! @name CR - Control Register */
/*! @{ */
#define LPSPI_CR_MEN_MASK (0x1U)
#define LPSPI_CR_MEN_SHIFT (0U)
/*! MEN - Module Enable
 *  0b0..Module is disabled.
 *  0b1..Module is enabled.
 */
#define LPSPI_CR_MEN(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CR_MEN_SHIFT)) & LPSPI_CR_MEN_MASK)
#define LPSPI_CR_RST_MASK (0x2U)
#define LPSPI_CR_RST_SHIFT (1U)
/*! RST - Software Reset
 *  0b0..Master logic is not reset.
 *  0b1..Master logic is reset.
 */
#define LPSPI_CR_RST(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CR_RST_SHIFT)) & LPSPI_CR_RST_MASK)
#define LPSPI_CR_DOZEN_MASK (0x4U)
#define LPSPI_CR_DOZEN_SHIFT (2U)
/*! DOZEN - Doze mode enable
 *  0b0..Module is enabled in Doze mode.
 *  0b1..Module is disabled in Doze mode.
 */
#define LPSPI_CR_DOZEN(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CR_DOZEN_SHIFT)) & LPSPI_CR_DOZEN_MASK)
#define LPSPI_CR_DBGEN_MASK (0x8U)
#define LPSPI_CR_DBGEN_SHIFT (3U)
/*! DBGEN - Debug Enable
 *  0b0..Module is disabled in debug mode.
 *  0b1..Module is enabled in debug mode.
 */
#define LPSPI_CR_DBGEN(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CR_DBGEN_SHIFT)) & LPSPI_CR_DBGEN_MASK)
#define LPSPI_CR_RTF_MASK (0x100U)
#define LPSPI_CR_RTF_SHIFT (8U)
/*! RTF - Reset Transmit FIFO
 *  0b0..No effect.
 *  0b1..Transmit FIFO is reset.
 */
#define LPSPI_CR_RTF(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CR_RTF_SHIFT)) & LPSPI_CR_RTF_MASK)
#define LPSPI_CR_RRF_MASK (0x200U)
#define LPSPI_CR_RRF_SHIFT (9U)
/*! RRF - Reset Receive FIFO
 *  0b0..No effect.
 *  0b1..Receive FIFO is reset.
 */
#define LPSPI_CR_RRF(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CR_RRF_SHIFT)) & LPSPI_CR_RRF_MASK)
/*! @} */

/*! @name SR - Status Register */
/*! @{ */
#define LPSPI_SR_TDF_MASK (0x1U)
#define LPSPI_SR_TDF_SHIFT (0U)
/*! TDF - Transmit Data Flag
 *  0b0..Transmit data not requested.
 *  0b1..Transmit data is requested.
 */
#define LPSPI_SR_TDF(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_SR_TDF_SHIFT)) & LPSPI_SR_TDF_MASK)
#define LPSPI_SR_RDF_MASK (0x2U)
#define LPSPI_SR_RDF_SHIFT (1U)
/*! RDF - Receive Data Flag
 *  0b0..Receive Data is not ready.
 *  0b1..Receive data is ready.
 */
#define LPSPI_SR_RDF(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_SR_RDF_SHIFT)) & LPSPI_SR_RDF_MASK)
#define LPSPI_SR_WCF_MASK (0x100U)
#define LPSPI_SR_WCF_SHIFT (8U)
/*! WCF - Word Complete Flag
 *  0b0..Transfer word not completed.
 *  0b1..Transfer word completed.
 */
#define LPSPI_SR_WCF(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_SR_WCF_SHIFT)) & LPSPI_SR_WCF_MASK)
#define LPSPI_SR_FCF_MASK (0x200U)
#define LPSPI_SR_FCF_SHIFT (9U)
/*! FCF - Frame Complete Flag
 *  0b0..Frame transfer has not completed.
 *  0b1..Frame transfer has completed.
 */
#define LPSPI_SR_FCF(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_SR_FCF_SHIFT)) & LPSPI_SR_FCF_MASK)
#define LPSPI_SR_TCF_MASK (0x400U)
#define LPSPI_SR_TCF_SHIFT (10U)
/*! TCF - Transfer Complete Flag
 *  0b0..All transfers have not completed.
 *  0b1..All transfers have completed.
 */
#define LPSPI_SR_TCF(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_SR_TCF_SHIFT)) & LPSPI_SR_TCF_MASK)
#define LPSPI_SR_TEF_MASK (0x800U)
#define LPSPI_SR_TEF_SHIFT (11U)
/*! TEF - Transmit Error Flag
 *  0b0..Transmit FIFO underrun has not occurred.
 *  0b1..Transmit FIFO underrun has occurred
 */
#define LPSPI_SR_TEF(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_SR_TEF_SHIFT)) & LPSPI_SR_TEF_MASK)
#define LPSPI_SR_REF_MASK (0x1000U)
#define LPSPI_SR_REF_SHIFT (12U)
/*! REF - Receive Error Flag
 *  0b0..Receive FIFO has not overflowed.
 *  0b1..Receive FIFO has overflowed.
 */
#define LPSPI_SR_REF(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_SR_REF_SHIFT)) & LPSPI_SR_REF_MASK)
#define LPSPI_SR_DMF_MASK (0x2000U)
#define LPSPI_SR_DMF_SHIFT (13U)
/*! DMF - Data Match Flag
 *  0b0..Have not received matching data.
 *  0b1..Have received matching data.
 */
#define LPSPI_SR_DMF(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_SR_DMF_SHIFT)) & LPSPI_SR_DMF_MASK)
#define LPSPI_SR_MBF_MASK (0x1000000U)
#define LPSPI_SR_MBF_SHIFT (24U)
/*! MBF - Module Busy Flag
 *  0b0..LPSPI is idle.
 *  0b1..LPSPI is busy.
 */
#define LPSPI_SR_MBF(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_SR_MBF_SHIFT)) & LPSPI_SR_MBF_MASK)
/*! @} */

/*! @name IER - Interrupt Enable Register */
/*! @{ */
#define LPSPI_IER_TDIE_MASK (0x1U)
#define LPSPI_IER_TDIE_SHIFT (0U)
/*! TDIE - Transmit Data Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled
 */
#define LPSPI_IER_TDIE(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_IER_TDIE_SHIFT)) & LPSPI_IER_TDIE_MASK)
#define LPSPI_IER_RDIE_MASK (0x2U)
#define LPSPI_IER_RDIE_SHIFT (1U)
/*! RDIE - Receive Data Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPSPI_IER_RDIE(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_IER_RDIE_SHIFT)) & LPSPI_IER_RDIE_MASK)
#define LPSPI_IER_WCIE_MASK (0x100U)
#define LPSPI_IER_WCIE_SHIFT (8U)
/*! WCIE - Word Complete Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPSPI_IER_WCIE(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_IER_WCIE_SHIFT)) & LPSPI_IER_WCIE_MASK)
#define LPSPI_IER_FCIE_MASK (0x200U)
#define LPSPI_IER_FCIE_SHIFT (9U)
/*! FCIE - Frame Complete Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPSPI_IER_FCIE(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_IER_FCIE_SHIFT)) & LPSPI_IER_FCIE_MASK)
#define LPSPI_IER_TCIE_MASK (0x400U)
#define LPSPI_IER_TCIE_SHIFT (10U)
/*! TCIE - Transfer Complete Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPSPI_IER_TCIE(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_IER_TCIE_SHIFT)) & LPSPI_IER_TCIE_MASK)
#define LPSPI_IER_TEIE_MASK (0x800U)
#define LPSPI_IER_TEIE_SHIFT (11U)
/*! TEIE - Transmit Error Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPSPI_IER_TEIE(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_IER_TEIE_SHIFT)) & LPSPI_IER_TEIE_MASK)
#define LPSPI_IER_REIE_MASK (0x1000U)
#define LPSPI_IER_REIE_SHIFT (12U)
/*! REIE - Receive Error Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPSPI_IER_REIE(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_IER_REIE_SHIFT)) & LPSPI_IER_REIE_MASK)
#define LPSPI_IER_DMIE_MASK (0x2000U)
#define LPSPI_IER_DMIE_SHIFT (13U)
/*! DMIE - Data Match Interrupt Enable
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define LPSPI_IER_DMIE(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_IER_DMIE_SHIFT)) & LPSPI_IER_DMIE_MASK)
/*! @} */

/*! @name DER - DMA Enable Register */
/*! @{ */
#define LPSPI_DER_TDDE_MASK (0x1U)
#define LPSPI_DER_TDDE_SHIFT (0U)
/*! TDDE - Transmit Data DMA Enable
 *  0b0..DMA request disabled.
 *  0b1..DMA request enabled
 */
#define LPSPI_DER_TDDE(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_DER_TDDE_SHIFT)) & LPSPI_DER_TDDE_MASK)
#define LPSPI_DER_RDDE_MASK (0x2U)
#define LPSPI_DER_RDDE_SHIFT (1U)
/*! RDDE - Receive Data DMA Enable
 *  0b0..DMA request disabled.
 *  0b1..DMA request enabled.
 */
#define LPSPI_DER_RDDE(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_DER_RDDE_SHIFT)) & LPSPI_DER_RDDE_MASK)
/*! @} */

/*! @name CFGR0 - Configuration Register 0 */
/*! @{ */
#define LPSPI_CFGR0_HREN_MASK (0x1U)
#define LPSPI_CFGR0_HREN_SHIFT (0U)
/*! HREN - Host Request Enable
 *  0b0..Host request is disabled.
 *  0b1..Host request is enabled.
 */
#define LPSPI_CFGR0_HREN(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR0_HREN_SHIFT)) & LPSPI_CFGR0_HREN_MASK)
#define LPSPI_CFGR0_HRPOL_MASK (0x2U)
#define LPSPI_CFGR0_HRPOL_SHIFT (1U)
/*! HRPOL - Host Request Polarity
 *  0b0..Active low.
 *  0b1..Active high.
 */
#define LPSPI_CFGR0_HRPOL(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR0_HRPOL_SHIFT)) & LPSPI_CFGR0_HRPOL_MASK)
#define LPSPI_CFGR0_HRSEL_MASK (0x4U)
#define LPSPI_CFGR0_HRSEL_SHIFT (2U)
/*! HRSEL - Host Request Select
 *  0b0..Host request input is pin LPSPI_HREQ.
 *  0b1..Host request input is input trigger.
 */
#define LPSPI_CFGR0_HRSEL(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR0_HRSEL_SHIFT)) & LPSPI_CFGR0_HRSEL_MASK)
#define LPSPI_CFGR0_CIRFIFO_MASK (0x100U)
#define LPSPI_CFGR0_CIRFIFO_SHIFT (8U)
/*! CIRFIFO - Circular FIFO Enable
 *  0b0..Circular FIFO is disabled.
 *  0b1..Circular FIFO is enabled.
 */
#define LPSPI_CFGR0_CIRFIFO(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR0_CIRFIFO_SHIFT)) & LPSPI_CFGR0_CIRFIFO_MASK)
#define LPSPI_CFGR0_RDMO_MASK (0x200U)
#define LPSPI_CFGR0_RDMO_SHIFT (9U)
/*! RDMO - Receive Data Match Only
 *  0b0..Received data is stored in the receive FIFO as normal.
 *  0b1..Received data is discarded unless the DMF is set.
 */
#define LPSPI_CFGR0_RDMO(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR0_RDMO_SHIFT)) & LPSPI_CFGR0_RDMO_MASK)
/*! @} */

/*! @name CFGR1 - Configuration Register 1 */
/*! @{ */
#define LPSPI_CFGR1_MASTER_MASK (0x1U)
#define LPSPI_CFGR1_MASTER_SHIFT (0U)
/*! MASTER - Master Mode
 *  0b0..Slave mode.
 *  0b1..Master mode.
 */
#define LPSPI_CFGR1_MASTER(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR1_MASTER_SHIFT)) & LPSPI_CFGR1_MASTER_MASK)
#define LPSPI_CFGR1_SAMPLE_MASK (0x2U)
#define LPSPI_CFGR1_SAMPLE_SHIFT (1U)
/*! SAMPLE - Sample Point
 *  0b0..Input data sampled on SCK edge.
 *  0b1..Input data sampled on delayed SCK edge.
 */
#define LPSPI_CFGR1_SAMPLE(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR1_SAMPLE_SHIFT)) & LPSPI_CFGR1_SAMPLE_MASK)
#define LPSPI_CFGR1_AUTOPCS_MASK (0x4U)
#define LPSPI_CFGR1_AUTOPCS_SHIFT (2U)
/*! AUTOPCS - Automatic PCS
 *  0b0..Automatic PCS generation disabled.
 *  0b1..Automatic PCS generation enabled.
 */
#define LPSPI_CFGR1_AUTOPCS(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR1_AUTOPCS_SHIFT)) & LPSPI_CFGR1_AUTOPCS_MASK)
#define LPSPI_CFGR1_NOSTALL_MASK (0x8U)
#define LPSPI_CFGR1_NOSTALL_SHIFT (3U)
/*! NOSTALL - No Stall
 *  0b0..Transfers will stall when transmit FIFO is empty or receive FIFO is full.
 *  0b1..Transfers will not stall, allowing transmit FIFO underrun or receive FIFO overrun to occur.
 */
#define LPSPI_CFGR1_NOSTALL(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR1_NOSTALL_SHIFT)) & LPSPI_CFGR1_NOSTALL_MASK)
#define LPSPI_CFGR1_PCSPOL_MASK (0xF00U)
#define LPSPI_CFGR1_PCSPOL_SHIFT (8U)
/*! PCSPOL - Peripheral Chip Select Polarity
 *  0b0000..The PCSx is active low.
 *  0b0001..The PCSx is active high.
 */
#define LPSPI_CFGR1_PCSPOL(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR1_PCSPOL_SHIFT)) & LPSPI_CFGR1_PCSPOL_MASK)
#define LPSPI_CFGR1_MATCFG_MASK (0x70000U)
#define LPSPI_CFGR1_MATCFG_SHIFT (16U)
/*! MATCFG - Match Configuration
 *  0b000..Match disabled.
 *  0b001..Reserved
 *  0b010..Match enabled (1st data word equals MATCH0 OR MATCH1).
 *  0b011..Match enabled (any data word equals MATCH0 OR MATCH1).
 *  0b100..Match enabled (1st data word equals MATCH0 AND 2nd data word equals MATCH1).
 *  0b101..Match enabled (any data word equals MATCH0 AND next data word equals MATCH1)
 *  0b110..Match enabled (1st data word AND MATCH1 equals MATCH0 AND MATCH1)
 *  0b111..Match enabled (any data word AND MATCH1 equals MATCH0 AND MATCH1).
 */
#define LPSPI_CFGR1_MATCFG(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR1_MATCFG_SHIFT)) & LPSPI_CFGR1_MATCFG_MASK)
#define LPSPI_CFGR1_PINCFG_MASK (0x3000000U)
#define LPSPI_CFGR1_PINCFG_SHIFT (24U)
/*! PINCFG - Pin Configuration
 *  0b00..SIN is used for input data and SOUT for output data.
 *  0b01..SIN is used for both input and output data.
 *  0b10..SOUT is used for both input and output data.
 *  0b11..SOUT is used for input data and SIN for output data.
 */
#define LPSPI_CFGR1_PINCFG(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR1_PINCFG_SHIFT)) & LPSPI_CFGR1_PINCFG_MASK)
#define LPSPI_CFGR1_OUTCFG_MASK (0x4000000U)
#define LPSPI_CFGR1_OUTCFG_SHIFT (26U)
/*! OUTCFG - Output Config
 *  0b0..Output data retains last value when chip select is negated.
 *  0b1..Output data is tristated when chip select is negated.
 */
#define LPSPI_CFGR1_OUTCFG(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR1_OUTCFG_SHIFT)) & LPSPI_CFGR1_OUTCFG_MASK)
#define LPSPI_CFGR1_PCSCFG_MASK (0x8000000U)
#define LPSPI_CFGR1_PCSCFG_SHIFT (27U)
/*! PCSCFG - Peripheral Chip Select Configuration
 *  0b0..PCS[3:2] are enabled.
 *  0b1..PCS[3:2] are disabled.
 */
#define LPSPI_CFGR1_PCSCFG(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CFGR1_PCSCFG_SHIFT)) & LPSPI_CFGR1_PCSCFG_MASK)
/*! @} */

/*! @name DMR0 - Data Match Register 0 */
/*! @{ */
#define LPSPI_DMR0_MATCH0_MASK (0xFFFFFFFFU)
#define LPSPI_DMR0_MATCH0_SHIFT (0U)
/*! MATCH0 - Match 0 Value
 */
#define LPSPI_DMR0_MATCH0(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_DMR0_MATCH0_SHIFT)) & LPSPI_DMR0_MATCH0_MASK)
/*! @} */

/*! @name DMR1 - Data Match Register 1 */
/*! @{ */
#define LPSPI_DMR1_MATCH1_MASK (0xFFFFFFFFU)
#define LPSPI_DMR1_MATCH1_SHIFT (0U)
/*! MATCH1 - Match 1 Value
 */
#define LPSPI_DMR1_MATCH1(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_DMR1_MATCH1_SHIFT)) & LPSPI_DMR1_MATCH1_MASK)
/*! @} */

/*! @name CCR - Clock Configuration Register */
/*! @{ */
#define LPSPI_CCR_SCKDIV_MASK (0xFFU)
#define LPSPI_CCR_SCKDIV_SHIFT (0U)
/*! SCKDIV - SCK Divider
 */
#define LPSPI_CCR_SCKDIV(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CCR_SCKDIV_SHIFT)) & LPSPI_CCR_SCKDIV_MASK)
#define LPSPI_CCR_DBT_MASK (0xFF00U)
#define LPSPI_CCR_DBT_SHIFT (8U)
/*! DBT - Delay Between Transfers
 */
#define LPSPI_CCR_DBT(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CCR_DBT_SHIFT)) & LPSPI_CCR_DBT_MASK)
#define LPSPI_CCR_PCSSCK_MASK (0xFF0000U)
#define LPSPI_CCR_PCSSCK_SHIFT (16U)
/*! PCSSCK - PCS to SCK Delay
 */
#define LPSPI_CCR_PCSSCK(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CCR_PCSSCK_SHIFT)) & LPSPI_CCR_PCSSCK_MASK)
#define LPSPI_CCR_SCKPCS_MASK (0xFF000000U)
#define LPSPI_CCR_SCKPCS_SHIFT (24U)
/*! SCKPCS - SCK to PCS Delay
 */
#define LPSPI_CCR_SCKPCS(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_CCR_SCKPCS_SHIFT)) & LPSPI_CCR_SCKPCS_MASK)
/*! @} */

/*! @name FCR - FIFO Control Register */
/*! @{ */
#define LPSPI_FCR_TXWATER_MASK (0xFFU)
#define LPSPI_FCR_TXWATER_SHIFT (0U)
/*! TXWATER - Transmit FIFO Watermark
 */
#define LPSPI_FCR_TXWATER(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_FCR_TXWATER_SHIFT)) & LPSPI_FCR_TXWATER_MASK)
#define LPSPI_FCR_RXWATER_MASK (0xFF0000U)
#define LPSPI_FCR_RXWATER_SHIFT (16U)
/*! RXWATER - Receive FIFO Watermark
 */
#define LPSPI_FCR_RXWATER(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_FCR_RXWATER_SHIFT)) & LPSPI_FCR_RXWATER_MASK)
/*! @} */

/*! @name FSR - FIFO Status Register */
/*! @{ */
#define LPSPI_FSR_TXCOUNT_MASK (0xFFU)
#define LPSPI_FSR_TXCOUNT_SHIFT (0U)
/*! TXCOUNT - Transmit FIFO Count
 */
#define LPSPI_FSR_TXCOUNT(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_FSR_TXCOUNT_SHIFT)) & LPSPI_FSR_TXCOUNT_MASK)
#define LPSPI_FSR_RXCOUNT_MASK (0xFF0000U)
#define LPSPI_FSR_RXCOUNT_SHIFT (16U)
/*! RXCOUNT - Receive FIFO Count
 */
#define LPSPI_FSR_RXCOUNT(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_FSR_RXCOUNT_SHIFT)) & LPSPI_FSR_RXCOUNT_MASK)
/*! @} */

/*! @name TCR - Transmit Command Register */
/*! @{ */
#define LPSPI_TCR_FRAMESZ_MASK (0xFFFU)
#define LPSPI_TCR_FRAMESZ_SHIFT (0U)
/*! FRAMESZ - Frame Size
 */
#define LPSPI_TCR_FRAMESZ(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_TCR_FRAMESZ_SHIFT)) & LPSPI_TCR_FRAMESZ_MASK)
#define LPSPI_TCR_WIDTH_MASK (0x30000U)
#define LPSPI_TCR_WIDTH_SHIFT (16U)
/*! WIDTH - Transfer Width
 *  0b00..Single bit transfer.
 *  0b01..Two bit transfer.
 *  0b10..Four bit transfer.
 *  0b11..Reserved.
 */
#define LPSPI_TCR_WIDTH(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_TCR_WIDTH_SHIFT)) & LPSPI_TCR_WIDTH_MASK)
#define LPSPI_TCR_TXMSK_MASK (0x40000U)
#define LPSPI_TCR_TXMSK_SHIFT (18U)
/*! TXMSK - Transmit Data Mask
 *  0b0..Normal transfer.
 *  0b1..Mask transmit data.
 */
#define LPSPI_TCR_TXMSK(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_TCR_TXMSK_SHIFT)) & LPSPI_TCR_TXMSK_MASK)
#define LPSPI_TCR_RXMSK_MASK (0x80000U)
#define LPSPI_TCR_RXMSK_SHIFT (19U)
/*! RXMSK - Receive Data Mask
 *  0b0..Normal transfer.
 *  0b1..Receive data is masked.
 */
#define LPSPI_TCR_RXMSK(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_TCR_RXMSK_SHIFT)) & LPSPI_TCR_RXMSK_MASK)
#define LPSPI_TCR_CONTC_MASK (0x100000U)
#define LPSPI_TCR_CONTC_SHIFT (20U)
/*! CONTC - Continuing Command
 *  0b0..Command word for start of new transfer.
 *  0b1..Command word for continuing transfer.
 */
#define LPSPI_TCR_CONTC(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_TCR_CONTC_SHIFT)) & LPSPI_TCR_CONTC_MASK)
#define LPSPI_TCR_CONT_MASK (0x200000U)
#define LPSPI_TCR_CONT_SHIFT (21U)
/*! CONT - Continuous Transfer
 *  0b0..Continuous transfer disabled.
 *  0b1..Continuous transfer enabled.
 */
#define LPSPI_TCR_CONT(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_TCR_CONT_SHIFT)) & LPSPI_TCR_CONT_MASK)
#define LPSPI_TCR_BYSW_MASK (0x400000U)
#define LPSPI_TCR_BYSW_SHIFT (22U)
/*! BYSW - Byte Swap
 *  0b0..Byte swap disabled.
 *  0b1..Byte swap enabled.
 */
#define LPSPI_TCR_BYSW(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_TCR_BYSW_SHIFT)) & LPSPI_TCR_BYSW_MASK)
#define LPSPI_TCR_LSBF_MASK (0x800000U)
#define LPSPI_TCR_LSBF_SHIFT (23U)
/*! LSBF - LSB First
 *  0b0..Data is transferred MSB first.
 *  0b1..Data is transferred LSB first.
 */
#define LPSPI_TCR_LSBF(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_TCR_LSBF_SHIFT)) & LPSPI_TCR_LSBF_MASK)
#define LPSPI_TCR_PCS_MASK (0x3000000U)
#define LPSPI_TCR_PCS_SHIFT (24U)
/*! PCS - Peripheral Chip Select
 *  0b00..Transfer using LPSPI_PCS[0]
 *  0b01..Transfer using LPSPI_PCS[1]
 *  0b10..Transfer using LPSPI_PCS[2]
 *  0b11..Transfer using LPSPI_PCS[3]
 */
#define LPSPI_TCR_PCS(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_TCR_PCS_SHIFT)) & LPSPI_TCR_PCS_MASK)
#define LPSPI_TCR_PRESCALE_MASK (0x38000000U)
#define LPSPI_TCR_PRESCALE_SHIFT (27U)
/*! PRESCALE - Prescaler Value
 *  0b000..Divide by 1.
 *  0b001..Divide by 2.
 *  0b010..Divide by 4.
 *  0b011..Divide by 8.
 *  0b100..Divide by 16.
 *  0b101..Divide by 32.
 *  0b110..Divide by 64.
 *  0b111..Divide by 128.
 */
#define LPSPI_TCR_PRESCALE(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_TCR_PRESCALE_SHIFT)) & LPSPI_TCR_PRESCALE_MASK)
#define LPSPI_TCR_CPHA_MASK (0x40000000U)
#define LPSPI_TCR_CPHA_SHIFT (30U)
/*! CPHA - Clock Phase
 *  0b0..Data is captured on the leading edge of SCK and changed on the following edge.
 *  0b1..Data is changed on the leading edge of SCK and captured on the following edge.
 */
#define LPSPI_TCR_CPHA(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_TCR_CPHA_SHIFT)) & LPSPI_TCR_CPHA_MASK)
#define LPSPI_TCR_CPOL_MASK (0x80000000U)
#define LPSPI_TCR_CPOL_SHIFT (31U)
/*! CPOL - Clock Polarity
 *  0b0..The inactive state value of SCK is low.
 *  0b1..The inactive state value of SCK is high.
 */
#define LPSPI_TCR_CPOL(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_TCR_CPOL_SHIFT)) & LPSPI_TCR_CPOL_MASK)
/*! @} */

/*! @name TDR - Transmit Data Register */
/*! @{ */
#define LPSPI_TDR_DATA_MASK (0xFFFFFFFFU)
#define LPSPI_TDR_DATA_SHIFT (0U)
/*! DATA - Transmit Data
 */
#define LPSPI_TDR_DATA(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_TDR_DATA_SHIFT)) & LPSPI_TDR_DATA_MASK)
/*! @} */

/*! @name RSR - Receive Status Register */
/*! @{ */
#define LPSPI_RSR_SOF_MASK (0x1U)
#define LPSPI_RSR_SOF_SHIFT (0U)
/*! SOF - Start Of Frame
 *  0b0..Subsequent data word received after LPSPI_PCS assertion.
 *  0b1..First data word received after LPSPI_PCS assertion.
 */
#define LPSPI_RSR_SOF(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_RSR_SOF_SHIFT)) & LPSPI_RSR_SOF_MASK)
#define LPSPI_RSR_RXEMPTY_MASK (0x2U)
#define LPSPI_RSR_RXEMPTY_SHIFT (1U)
/*! RXEMPTY - RX FIFO Empty
 *  0b0..RX FIFO is not empty.
 *  0b1..RX FIFO is empty.
 */
#define LPSPI_RSR_RXEMPTY(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_RSR_RXEMPTY_SHIFT)) & LPSPI_RSR_RXEMPTY_MASK)
/*! @} */

/*! @name RDR - Receive Data Register */
/*! @{ */
#define LPSPI_RDR_DATA_MASK (0xFFFFFFFFU)
#define LPSPI_RDR_DATA_SHIFT (0U)
/*! DATA - Receive Data
 */
#define LPSPI_RDR_DATA(x) (((uint32_t)(((uint32_t)(x)) << LPSPI_RDR_DATA_SHIFT)) & LPSPI_RDR_DATA_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group LPSPI_Register_Masks */

/* LPSPI - Peripheral instance base addresses */
/** Peripheral LPSPI0 base address */
#define LPSPI0_BASE (0x400BC000u)
/** Peripheral LPSPI0 base pointer */
#define LPSPI0 ((LPSPI_Type *)LPSPI0_BASE)
/** Peripheral LPSPI1 base address */
#define LPSPI1_BASE (0x400BD000u)
/** Peripheral LPSPI1 base pointer */
#define LPSPI1 ((LPSPI_Type *)LPSPI1_BASE)
/** Peripheral LPSPI2 base address */
#define LPSPI2_BASE (0x4003E000u)
/** Peripheral LPSPI2 base pointer */
#define LPSPI2 ((LPSPI_Type *)LPSPI2_BASE)
/** Array initializer of LPSPI peripheral base addresses */
#define LPSPI_BASE_ADDRS                      \
    {                                         \
        LPSPI0_BASE, LPSPI1_BASE, LPSPI2_BASE \
    }
/** Array initializer of LPSPI peripheral base pointers */
#define LPSPI_BASE_PTRS        \
    {                          \
        LPSPI0, LPSPI1, LPSPI2 \
    }
/** Interrupt vectors for the LPSPI peripheral type */
#define LPSPI_IRQS                            \
    {                                         \
        LPSPI0_IRQn, LPSPI1_IRQn, LPSPI2_IRQn \
    }

/*!
 * @}
 */ /* end of group LPSPI_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- LPTMR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Peripheral_Access_Layer LPTMR Peripheral Access Layer
 * @{
 */

/** LPTMR - Register Layout Typedef */
typedef struct
{
    __IO uint32_t CSR; /**< Low Power Timer Control Status Register, offset: 0x0 */
    __IO uint32_t PSR; /**< Low Power Timer Prescale Register, offset: 0x4 */
    __IO uint32_t CMR; /**< Low Power Timer Compare Register, offset: 0x8 */
    __IO uint32_t CNR; /**< Low Power Timer Counter Register, offset: 0xC */
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
#define LPTMR_CSR_TEN_MASK (0x1U)
#define LPTMR_CSR_TEN_SHIFT (0U)
/*! TEN - Timer Enable
 *  0b0..LPTMR is disabled and internal logic is reset.
 *  0b1..LPTMR is enabled.
 */
#define LPTMR_CSR_TEN(x) (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TEN_SHIFT)) & LPTMR_CSR_TEN_MASK)
#define LPTMR_CSR_TMS_MASK (0x2U)
#define LPTMR_CSR_TMS_SHIFT (1U)
/*! TMS - Timer Mode Select
 *  0b0..Time Counter mode.
 *  0b1..Pulse Counter mode.
 */
#define LPTMR_CSR_TMS(x) (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TMS_SHIFT)) & LPTMR_CSR_TMS_MASK)
#define LPTMR_CSR_TFC_MASK (0x4U)
#define LPTMR_CSR_TFC_SHIFT (2U)
/*! TFC - Timer Free-Running Counter
 *  0b0..CNR is reset whenever TCF is set.
 *  0b1..CNR is reset on overflow.
 */
#define LPTMR_CSR_TFC(x) (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TFC_SHIFT)) & LPTMR_CSR_TFC_MASK)
#define LPTMR_CSR_TPP_MASK (0x8U)
#define LPTMR_CSR_TPP_SHIFT (3U)
/*! TPP - Timer Pin Polarity
 *  0b0..Pulse Counter input source is active-high, and the CNR will increment on the rising-edge.
 *  0b1..Pulse Counter input source is active-low, and the CNR will increment on the falling-edge.
 */
#define LPTMR_CSR_TPP(x) (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TPP_SHIFT)) & LPTMR_CSR_TPP_MASK)
#define LPTMR_CSR_TPS_MASK (0x30U)
#define LPTMR_CSR_TPS_SHIFT (4U)
/*! TPS - Timer Pin Select
 *  0b00..Pulse counter input 0 is selected.
 *  0b01..Pulse counter input 1 is selected.
 *  0b10..Pulse counter input 2 is selected.
 *  0b11..Pulse counter input 3 is selected.
 */
#define LPTMR_CSR_TPS(x) (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TPS_SHIFT)) & LPTMR_CSR_TPS_MASK)
#define LPTMR_CSR_TIE_MASK (0x40U)
#define LPTMR_CSR_TIE_SHIFT (6U)
/*! TIE - Timer Interrupt Enable
 *  0b0..Timer interrupt disabled.
 *  0b1..Timer interrupt enabled.
 */
#define LPTMR_CSR_TIE(x) (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TIE_SHIFT)) & LPTMR_CSR_TIE_MASK)
#define LPTMR_CSR_TCF_MASK (0x80U)
#define LPTMR_CSR_TCF_SHIFT (7U)
/*! TCF - Timer Compare Flag
 *  0b0..The value of CNR is not equal to CMR and increments.
 *  0b1..The value of CNR is equal to CMR and increments.
 */
#define LPTMR_CSR_TCF(x) (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TCF_SHIFT)) & LPTMR_CSR_TCF_MASK)
#define LPTMR_CSR_TDRE_MASK (0x100U)
#define LPTMR_CSR_TDRE_SHIFT (8U)
/*! TDRE - Timer DMA Request Enable
 *  0b0..Timer DMA Request disabled.
 *  0b1..Timer DMA Request enabled.
 */
#define LPTMR_CSR_TDRE(x) (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TDRE_SHIFT)) & LPTMR_CSR_TDRE_MASK)
/*! @} */

/*! @name PSR - Low Power Timer Prescale Register */
/*! @{ */
#define LPTMR_PSR_PCS_MASK (0x3U)
#define LPTMR_PSR_PCS_SHIFT (0U)
/*! PCS - Prescaler Clock Select
 *  0b00..Prescaler/glitch filter clock 0 selected.
 *  0b01..Prescaler/glitch filter clock 1 selected.
 *  0b10..Prescaler/glitch filter clock 2 selected.
 *  0b11..Prescaler/glitch filter clock 3 selected.
 */
#define LPTMR_PSR_PCS(x) (((uint32_t)(((uint32_t)(x)) << LPTMR_PSR_PCS_SHIFT)) & LPTMR_PSR_PCS_MASK)
#define LPTMR_PSR_PBYP_MASK (0x4U)
#define LPTMR_PSR_PBYP_SHIFT (2U)
/*! PBYP - Prescaler Bypass
 *  0b0..Prescaler/glitch filter is enabled.
 *  0b1..Prescaler/glitch filter is bypassed.
 */
#define LPTMR_PSR_PBYP(x) (((uint32_t)(((uint32_t)(x)) << LPTMR_PSR_PBYP_SHIFT)) & LPTMR_PSR_PBYP_MASK)
#define LPTMR_PSR_PRESCALE_MASK (0x78U)
#define LPTMR_PSR_PRESCALE_SHIFT (3U)
/*! PRESCALE - Prescale Value
 *  0b0000..Prescaler divides the prescaler clock by 2; glitch filter does not support this configuration.
 *  0b0001..Prescaler divides the prescaler clock by 4; glitch filter recognizes change on input pin after 2 rising
 * clock edges. 0b0010..Prescaler divides the prescaler clock by 8; glitch filter recognizes change on input pin after 4
 * rising clock edges. 0b0011..Prescaler divides the prescaler clock by 16; glitch filter recognizes change on input pin
 * after 8 rising clock edges. 0b0100..Prescaler divides the prescaler clock by 32; glitch filter recognizes change on
 * input pin after 16 rising clock edges. 0b0101..Prescaler divides the prescaler clock by 64; glitch filter recognizes
 * change on input pin after 32 rising clock edges. 0b0110..Prescaler divides the prescaler clock by 128; glitch filter
 * recognizes change on input pin after 64 rising clock edges. 0b0111..Prescaler divides the prescaler clock by 256;
 * glitch filter recognizes change on input pin after 128 rising clock edges. 0b1000..Prescaler divides the prescaler
 * clock by 512; glitch filter recognizes change on input pin after 256 rising clock edges. 0b1001..Prescaler divides
 * the prescaler clock by 1024; glitch filter recognizes change on input pin after 512 rising clock edges.
 *  0b1010..Prescaler divides the prescaler clock by 2048; glitch filter recognizes change on input pin after 1024
 * rising clock edges. 0b1011..Prescaler divides the prescaler clock by 4096; glitch filter recognizes change on input
 * pin after 2048 rising clock edges. 0b1100..Prescaler divides the prescaler clock by 8192; glitch filter recognizes
 * change on input pin after 4096 rising clock edges. 0b1101..Prescaler divides the prescaler clock by 16,384; glitch
 * filter recognizes change on input pin after 8192 rising clock edges. 0b1110..Prescaler divides the prescaler clock by
 * 32,768; glitch filter recognizes change on input pin after 16,384 rising clock edges. 0b1111..Prescaler divides the
 * prescaler clock by 65,536; glitch filter recognizes change on input pin after 32,768 rising clock edges.
 */
#define LPTMR_PSR_PRESCALE(x) (((uint32_t)(((uint32_t)(x)) << LPTMR_PSR_PRESCALE_SHIFT)) & LPTMR_PSR_PRESCALE_MASK)
/*! @} */

/*! @name CMR - Low Power Timer Compare Register */
/*! @{ */
#define LPTMR_CMR_COMPARE_MASK (0xFFFFU)
#define LPTMR_CMR_COMPARE_SHIFT (0U)
/*! COMPARE - Compare Value
 */
#define LPTMR_CMR_COMPARE(x) (((uint32_t)(((uint32_t)(x)) << LPTMR_CMR_COMPARE_SHIFT)) & LPTMR_CMR_COMPARE_MASK)
/*! @} */

/*! @name CNR - Low Power Timer Counter Register */
/*! @{ */
#define LPTMR_CNR_COUNTER_MASK (0xFFFFU)
#define LPTMR_CNR_COUNTER_SHIFT (0U)
/*! COUNTER - Counter Value
 */
#define LPTMR_CNR_COUNTER(x) (((uint32_t)(((uint32_t)(x)) << LPTMR_CNR_COUNTER_SHIFT)) & LPTMR_CNR_COUNTER_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group LPTMR_Register_Masks */

/* LPTMR - Peripheral instance base addresses */
/** Peripheral LPTMR0 base address */
#define LPTMR0_BASE (0x40034000u)
/** Peripheral LPTMR0 base pointer */
#define LPTMR0 ((LPTMR_Type *)LPTMR0_BASE)
/** Peripheral LPTMR1 base address */
#define LPTMR1_BASE (0x400B5000u)
/** Peripheral LPTMR1 base pointer */
#define LPTMR1 ((LPTMR_Type *)LPTMR1_BASE)
/** Array initializer of LPTMR peripheral base addresses */
#define LPTMR_BASE_ADDRS         \
    {                            \
        LPTMR0_BASE, LPTMR1_BASE \
    }
/** Array initializer of LPTMR peripheral base pointers */
#define LPTMR_BASE_PTRS \
    {                   \
        LPTMR0, LPTMR1  \
    }
/** Interrupt vectors for the LPTMR peripheral type */
#define LPTMR_IRQS               \
    {                            \
        LPTMR0_IRQn, LPTMR1_IRQn \
    }

/*!
 * @}
 */ /* end of group LPTMR_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- LPUART Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPUART_Peripheral_Access_Layer LPUART Peripheral Access Layer
 * @{
 */

/** LPUART - Register Layout Typedef */
typedef struct
{
    __I uint32_t VERID;   /**< Version ID Register, offset: 0x0 */
    __I uint32_t PARAM;   /**< Parameter Register, offset: 0x4 */
    __IO uint32_t GLOBAL; /**< LPUART Global Register, offset: 0x8 */
    __IO uint32_t PINCFG; /**< LPUART Pin Configuration Register, offset: 0xC */
    __IO uint32_t BAUD;   /**< LPUART Baud Rate Register, offset: 0x10 */
    __IO uint32_t STAT;   /**< LPUART Status Register, offset: 0x14 */
    __IO uint32_t CTRL;   /**< LPUART Control Register, offset: 0x18 */
    __IO uint32_t DATA;   /**< LPUART Data Register, offset: 0x1C */
    __IO uint32_t MATCH;  /**< LPUART Match Address Register, offset: 0x20 */
    __IO uint32_t MODIR;  /**< LPUART Modem IrDA Register, offset: 0x24 */
    __IO uint32_t FIFO;   /**< LPUART FIFO Register, offset: 0x28 */
    __IO uint32_t WATER;  /**< LPUART Watermark Register, offset: 0x2C */
} LPUART_Type;

/* ----------------------------------------------------------------------------
   -- LPUART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPUART_Register_Masks LPUART Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */
#define LPUART_VERID_FEATURE_MASK (0xFFFFU)
#define LPUART_VERID_FEATURE_SHIFT (0U)
/*! FEATURE - Feature Identification Number
 *  0b0000000000000001..Standard feature set.
 *  0b0000000000000011..Standard feature set with MODEM/IrDA support.
 */
#define LPUART_VERID_FEATURE(x) \
    (((uint32_t)(((uint32_t)(x)) << LPUART_VERID_FEATURE_SHIFT)) & LPUART_VERID_FEATURE_MASK)
#define LPUART_VERID_MINOR_MASK (0xFF0000U)
#define LPUART_VERID_MINOR_SHIFT (16U)
/*! MINOR - Minor Version Number
 */
#define LPUART_VERID_MINOR(x) (((uint32_t)(((uint32_t)(x)) << LPUART_VERID_MINOR_SHIFT)) & LPUART_VERID_MINOR_MASK)
#define LPUART_VERID_MAJOR_MASK (0xFF000000U)
#define LPUART_VERID_MAJOR_SHIFT (24U)
/*! MAJOR - Major Version Number
 */
#define LPUART_VERID_MAJOR(x) (((uint32_t)(((uint32_t)(x)) << LPUART_VERID_MAJOR_SHIFT)) & LPUART_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */
#define LPUART_PARAM_TXFIFO_MASK (0xFFU)
#define LPUART_PARAM_TXFIFO_SHIFT (0U)
/*! TXFIFO - Transmit FIFO Size
 */
#define LPUART_PARAM_TXFIFO(x) (((uint32_t)(((uint32_t)(x)) << LPUART_PARAM_TXFIFO_SHIFT)) & LPUART_PARAM_TXFIFO_MASK)
#define LPUART_PARAM_RXFIFO_MASK (0xFF00U)
#define LPUART_PARAM_RXFIFO_SHIFT (8U)
/*! RXFIFO - Receive FIFO Size
 */
#define LPUART_PARAM_RXFIFO(x) (((uint32_t)(((uint32_t)(x)) << LPUART_PARAM_RXFIFO_SHIFT)) & LPUART_PARAM_RXFIFO_MASK)
/*! @} */

/*! @name GLOBAL - LPUART Global Register */
/*! @{ */
#define LPUART_GLOBAL_RST_MASK (0x2U)
#define LPUART_GLOBAL_RST_SHIFT (1U)
/*! RST - Software Reset
 *  0b0..Module is not reset.
 *  0b1..Module is reset.
 */
#define LPUART_GLOBAL_RST(x) (((uint32_t)(((uint32_t)(x)) << LPUART_GLOBAL_RST_SHIFT)) & LPUART_GLOBAL_RST_MASK)
/*! @} */

/*! @name PINCFG - LPUART Pin Configuration Register */
/*! @{ */
#define LPUART_PINCFG_TRGSEL_MASK (0x3U)
#define LPUART_PINCFG_TRGSEL_SHIFT (0U)
/*! TRGSEL - Trigger Select
 *  0b00..Input trigger is disabled.
 *  0b01..Input trigger is used instead of RXD pin input.
 *  0b10..Input trigger is used instead of CTS pin input.
 *  0b11..Input trigger is used to modulate the TXD pin output.
 */
#define LPUART_PINCFG_TRGSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << LPUART_PINCFG_TRGSEL_SHIFT)) & LPUART_PINCFG_TRGSEL_MASK)
/*! @} */

/*! @name BAUD - LPUART Baud Rate Register */
/*! @{ */
#define LPUART_BAUD_SBR_MASK (0x1FFFU)
#define LPUART_BAUD_SBR_SHIFT (0U)
/*! SBR - Baud Rate Modulo Divisor.
 */
#define LPUART_BAUD_SBR(x) (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_SBR_SHIFT)) & LPUART_BAUD_SBR_MASK)
#define LPUART_BAUD_SBNS_MASK (0x2000U)
#define LPUART_BAUD_SBNS_SHIFT (13U)
/*! SBNS - Stop Bit Number Select
 *  0b0..One stop bit.
 *  0b1..Two stop bits.
 */
#define LPUART_BAUD_SBNS(x) (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_SBNS_SHIFT)) & LPUART_BAUD_SBNS_MASK)
#define LPUART_BAUD_RXEDGIE_MASK (0x4000U)
#define LPUART_BAUD_RXEDGIE_SHIFT (14U)
/*! RXEDGIE - RX Input Active Edge Interrupt Enable
 *  0b0..Hardware interrupts from LPUART_STAT[RXEDGIF] disabled (use polling).
 *  0b1..Hardware interrupt requested when LPUART_STAT[RXEDGIF] flag is 1.
 */
#define LPUART_BAUD_RXEDGIE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_RXEDGIE_SHIFT)) & LPUART_BAUD_RXEDGIE_MASK)
#define LPUART_BAUD_LBKDIE_MASK (0x8000U)
#define LPUART_BAUD_LBKDIE_SHIFT (15U)
/*! LBKDIE - LIN Break Detect Interrupt Enable
 *  0b0..Hardware interrupts from LPUART_STAT[LBKDIF] disabled (use polling).
 *  0b1..Hardware interrupt requested when LPUART_STAT[LBKDIF] flag is 1.
 */
#define LPUART_BAUD_LBKDIE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_LBKDIE_SHIFT)) & LPUART_BAUD_LBKDIE_MASK)
#define LPUART_BAUD_RESYNCDIS_MASK (0x10000U)
#define LPUART_BAUD_RESYNCDIS_SHIFT (16U)
/*! RESYNCDIS - Resynchronization Disable
 *  0b0..Resynchronization during received data word is supported
 *  0b1..Resynchronization during received data word is disabled
 */
#define LPUART_BAUD_RESYNCDIS(x) \
    (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_RESYNCDIS_SHIFT)) & LPUART_BAUD_RESYNCDIS_MASK)
#define LPUART_BAUD_BOTHEDGE_MASK (0x20000U)
#define LPUART_BAUD_BOTHEDGE_SHIFT (17U)
/*! BOTHEDGE - Both Edge Sampling
 *  0b0..Receiver samples input data using the rising edge of the baud rate clock.
 *  0b1..Receiver samples input data using the rising and falling edge of the baud rate clock.
 */
#define LPUART_BAUD_BOTHEDGE(x) \
    (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_BOTHEDGE_SHIFT)) & LPUART_BAUD_BOTHEDGE_MASK)
#define LPUART_BAUD_MATCFG_MASK (0xC0000U)
#define LPUART_BAUD_MATCFG_SHIFT (18U)
/*! MATCFG - Match Configuration
 *  0b00..Address Match Wakeup
 *  0b01..Idle Match Wakeup
 *  0b10..Match On and Match Off
 *  0b11..Enables RWU on Data Match and Match On/Off for transmitter CTS input
 */
#define LPUART_BAUD_MATCFG(x) (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_MATCFG_SHIFT)) & LPUART_BAUD_MATCFG_MASK)
#define LPUART_BAUD_RDMAE_MASK (0x200000U)
#define LPUART_BAUD_RDMAE_SHIFT (21U)
/*! RDMAE - Receiver Full DMA Enable
 *  0b0..DMA request disabled.
 *  0b1..DMA request enabled.
 */
#define LPUART_BAUD_RDMAE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_RDMAE_SHIFT)) & LPUART_BAUD_RDMAE_MASK)
#define LPUART_BAUD_TDMAE_MASK (0x800000U)
#define LPUART_BAUD_TDMAE_SHIFT (23U)
/*! TDMAE - Transmitter DMA Enable
 *  0b0..DMA request disabled.
 *  0b1..DMA request enabled.
 */
#define LPUART_BAUD_TDMAE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_TDMAE_SHIFT)) & LPUART_BAUD_TDMAE_MASK)
#define LPUART_BAUD_OSR_MASK (0x1F000000U)
#define LPUART_BAUD_OSR_SHIFT (24U)
/*! OSR - Oversampling Ratio
 */
#define LPUART_BAUD_OSR(x) (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_OSR_SHIFT)) & LPUART_BAUD_OSR_MASK)
#define LPUART_BAUD_M10_MASK (0x20000000U)
#define LPUART_BAUD_M10_SHIFT (29U)
/*! M10 - 10-bit Mode select
 *  0b0..Receiver and transmitter use 8-bit or 9-bit data characters.
 *  0b1..Receiver and transmitter use 10-bit data characters.
 */
#define LPUART_BAUD_M10(x) (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_M10_SHIFT)) & LPUART_BAUD_M10_MASK)
#define LPUART_BAUD_MAEN2_MASK (0x40000000U)
#define LPUART_BAUD_MAEN2_SHIFT (30U)
/*! MAEN2 - Match Address Mode Enable 2
 *  0b0..Normal operation.
 *  0b1..Enables automatic address matching or data matching mode for MATCH[MA2].
 */
#define LPUART_BAUD_MAEN2(x) (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_MAEN2_SHIFT)) & LPUART_BAUD_MAEN2_MASK)
#define LPUART_BAUD_MAEN1_MASK (0x80000000U)
#define LPUART_BAUD_MAEN1_SHIFT (31U)
/*! MAEN1 - Match Address Mode Enable 1
 *  0b0..Normal operation.
 *  0b1..Enables automatic address matching or data matching mode for MATCH[MA1].
 */
#define LPUART_BAUD_MAEN1(x) (((uint32_t)(((uint32_t)(x)) << LPUART_BAUD_MAEN1_SHIFT)) & LPUART_BAUD_MAEN1_MASK)
/*! @} */

/*! @name STAT - LPUART Status Register */
/*! @{ */
#define LPUART_STAT_MA2F_MASK (0x4000U)
#define LPUART_STAT_MA2F_SHIFT (14U)
/*! MA2F - Match 2 Flag
 *  0b0..Received data is not equal to MA2
 *  0b1..Received data is equal to MA2
 */
#define LPUART_STAT_MA2F(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_MA2F_SHIFT)) & LPUART_STAT_MA2F_MASK)
#define LPUART_STAT_MA1F_MASK (0x8000U)
#define LPUART_STAT_MA1F_SHIFT (15U)
/*! MA1F - Match 1 Flag
 *  0b0..Received data is not equal to MA1
 *  0b1..Received data is equal to MA1
 */
#define LPUART_STAT_MA1F(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_MA1F_SHIFT)) & LPUART_STAT_MA1F_MASK)
#define LPUART_STAT_PF_MASK (0x10000U)
#define LPUART_STAT_PF_SHIFT (16U)
/*! PF - Parity Error Flag
 *  0b0..No parity error.
 *  0b1..Parity error.
 */
#define LPUART_STAT_PF(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_PF_SHIFT)) & LPUART_STAT_PF_MASK)
#define LPUART_STAT_FE_MASK (0x20000U)
#define LPUART_STAT_FE_SHIFT (17U)
/*! FE - Framing Error Flag
 *  0b0..No framing error detected. This does not guarantee the framing is correct.
 *  0b1..Framing error.
 */
#define LPUART_STAT_FE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_FE_SHIFT)) & LPUART_STAT_FE_MASK)
#define LPUART_STAT_NF_MASK (0x40000U)
#define LPUART_STAT_NF_SHIFT (18U)
/*! NF - Noise Flag
 *  0b0..No noise detected.
 *  0b1..Noise detected in the received character in LPUART_DATA.
 */
#define LPUART_STAT_NF(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_NF_SHIFT)) & LPUART_STAT_NF_MASK)
#define LPUART_STAT_OR_MASK (0x80000U)
#define LPUART_STAT_OR_SHIFT (19U)
/*! OR - Receiver Overrun Flag
 *  0b0..No overrun.
 *  0b1..Receive overrun (new LPUART data lost).
 */
#define LPUART_STAT_OR(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_OR_SHIFT)) & LPUART_STAT_OR_MASK)
#define LPUART_STAT_IDLE_MASK (0x100000U)
#define LPUART_STAT_IDLE_SHIFT (20U)
/*! IDLE - Idle Line Flag
 *  0b0..No idle line detected.
 *  0b1..Idle line was detected.
 */
#define LPUART_STAT_IDLE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_IDLE_SHIFT)) & LPUART_STAT_IDLE_MASK)
#define LPUART_STAT_RDRF_MASK (0x200000U)
#define LPUART_STAT_RDRF_SHIFT (21U)
/*! RDRF - Receive Data Register Full Flag
 *  0b0..Receive data buffer empty.
 *  0b1..Receive data buffer full.
 */
#define LPUART_STAT_RDRF(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_RDRF_SHIFT)) & LPUART_STAT_RDRF_MASK)
#define LPUART_STAT_TC_MASK (0x400000U)
#define LPUART_STAT_TC_SHIFT (22U)
/*! TC - Transmission Complete Flag
 *  0b0..Transmitter active (sending data, a preamble, or a break).
 *  0b1..Transmitter idle (transmission activity complete).
 */
#define LPUART_STAT_TC(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_TC_SHIFT)) & LPUART_STAT_TC_MASK)
#define LPUART_STAT_TDRE_MASK (0x800000U)
#define LPUART_STAT_TDRE_SHIFT (23U)
/*! TDRE - Transmit Data Register Empty Flag
 *  0b0..Transmit data buffer full.
 *  0b1..Transmit data buffer empty.
 */
#define LPUART_STAT_TDRE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_TDRE_SHIFT)) & LPUART_STAT_TDRE_MASK)
#define LPUART_STAT_RAF_MASK (0x1000000U)
#define LPUART_STAT_RAF_SHIFT (24U)
/*! RAF - Receiver Active Flag
 *  0b0..LPUART receiver idle waiting for a start bit.
 *  0b1..LPUART receiver active (LPUART_RX input not idle).
 */
#define LPUART_STAT_RAF(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_RAF_SHIFT)) & LPUART_STAT_RAF_MASK)
#define LPUART_STAT_LBKDE_MASK (0x2000000U)
#define LPUART_STAT_LBKDE_SHIFT (25U)
/*! LBKDE - LIN Break Detection Enable
 *  0b0..Break character is detected at length 10 bit times (if M = 0, SBNS = 0) or 11 (if M = 1, SBNS = 0 or M =
 *       0, SBNS = 1) or 12 (if M = 1, SBNS = 1 or M10 = 1, SNBS = 0) or 13 (if M10 = 1, SNBS = 1).
 *  0b1..Break character is detected at length of 11 bit times (if M = 0, SBNS = 0) or 12 (if M = 1, SBNS = 0 or M
 *       = 0, SBNS = 1) or 14 (if M = 1, SBNS = 1 or M10 = 1, SNBS = 0) or 15 (if M10 = 1, SNBS = 1).
 */
#define LPUART_STAT_LBKDE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_LBKDE_SHIFT)) & LPUART_STAT_LBKDE_MASK)
#define LPUART_STAT_BRK13_MASK (0x4000000U)
#define LPUART_STAT_BRK13_SHIFT (26U)
/*! BRK13 - Break Character Generation Length
 *  0b0..Break character is transmitted with length of 10 bit times (if M = 0, SBNS = 0) or 11 (if M = 1, SBNS = 0
 *       or M = 0, SBNS = 1) or 12 (if M = 1, SBNS = 1 or M10 = 1, SNBS = 0) or 13 (if M10 = 1, SNBS = 1).
 *  0b1..Break character is transmitted with length of 13 bit times (if M = 0, SBNS = 0) or 14 (if M = 1, SBNS = 0
 *       or M = 0, SBNS = 1) or 15 (if M = 1, SBNS = 1 or M10 = 1, SNBS = 0) or 16 (if M10 = 1, SNBS = 1).
 */
#define LPUART_STAT_BRK13(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_BRK13_SHIFT)) & LPUART_STAT_BRK13_MASK)
#define LPUART_STAT_RWUID_MASK (0x8000000U)
#define LPUART_STAT_RWUID_SHIFT (27U)
/*! RWUID - Receive Wake Up Idle Detect
 *  0b0..During receive standby state (RWU = 1), the IDLE bit does not get set upon detection of an idle
 *       character. During address match wakeup, the IDLE bit does not get set when an address does not match.
 *  0b1..During receive standby state (RWU = 1), the IDLE bit gets set upon detection of an idle character. During
 *       address match wakeup, the IDLE bit does get set when an address does not match.
 */
#define LPUART_STAT_RWUID(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_RWUID_SHIFT)) & LPUART_STAT_RWUID_MASK)
#define LPUART_STAT_RXINV_MASK (0x10000000U)
#define LPUART_STAT_RXINV_SHIFT (28U)
/*! RXINV - Receive Data Inversion
 *  0b0..Receive data not inverted.
 *  0b1..Receive data inverted.
 */
#define LPUART_STAT_RXINV(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_RXINV_SHIFT)) & LPUART_STAT_RXINV_MASK)
#define LPUART_STAT_MSBF_MASK (0x20000000U)
#define LPUART_STAT_MSBF_SHIFT (29U)
/*! MSBF - MSB First
 *  0b0..LSB (bit0) is the first bit that is transmitted following the start bit. Further, the first bit received
 *       after the start bit is identified as bit0.
 *  0b1..MSB (bit9, bit8, bit7 or bit6) is the first bit that is transmitted following the start bit depending on
 *       the setting of CTRL[M], CTRL[PE] and BAUD[M10]. Further, the first bit received after the start bit is
 *       identified as bit9, bit8, bit7 or bit6 depending on the setting of CTRL[M] and CTRL[PE].
 */
#define LPUART_STAT_MSBF(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_MSBF_SHIFT)) & LPUART_STAT_MSBF_MASK)
#define LPUART_STAT_RXEDGIF_MASK (0x40000000U)
#define LPUART_STAT_RXEDGIF_SHIFT (30U)
/*! RXEDGIF - LPUART_RX Pin Active Edge Interrupt Flag
 *  0b0..No active edge on the receive pin has occurred.
 *  0b1..An active edge on the receive pin has occurred.
 */
#define LPUART_STAT_RXEDGIF(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_RXEDGIF_SHIFT)) & LPUART_STAT_RXEDGIF_MASK)
#define LPUART_STAT_LBKDIF_MASK (0x80000000U)
#define LPUART_STAT_LBKDIF_SHIFT (31U)
/*! LBKDIF - LIN Break Detect Interrupt Flag
 *  0b0..No LIN break character has been detected.
 *  0b1..LIN break character has been detected.
 */
#define LPUART_STAT_LBKDIF(x) (((uint32_t)(((uint32_t)(x)) << LPUART_STAT_LBKDIF_SHIFT)) & LPUART_STAT_LBKDIF_MASK)
/*! @} */

/*! @name CTRL - LPUART Control Register */
/*! @{ */
#define LPUART_CTRL_PT_MASK (0x1U)
#define LPUART_CTRL_PT_SHIFT (0U)
/*! PT - Parity Type
 *  0b0..Even parity.
 *  0b1..Odd parity.
 */
#define LPUART_CTRL_PT(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_PT_SHIFT)) & LPUART_CTRL_PT_MASK)
#define LPUART_CTRL_PE_MASK (0x2U)
#define LPUART_CTRL_PE_SHIFT (1U)
/*! PE - Parity Enable
 *  0b0..No hardware parity generation or checking.
 *  0b1..Parity enabled.
 */
#define LPUART_CTRL_PE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_PE_SHIFT)) & LPUART_CTRL_PE_MASK)
#define LPUART_CTRL_ILT_MASK (0x4U)
#define LPUART_CTRL_ILT_SHIFT (2U)
/*! ILT - Idle Line Type Select
 *  0b0..Idle character bit count starts after start bit.
 *  0b1..Idle character bit count starts after stop bit.
 */
#define LPUART_CTRL_ILT(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_ILT_SHIFT)) & LPUART_CTRL_ILT_MASK)
#define LPUART_CTRL_WAKE_MASK (0x8U)
#define LPUART_CTRL_WAKE_SHIFT (3U)
/*! WAKE - Receiver Wakeup Method Select
 *  0b0..Configures RWU for idle-line wakeup.
 *  0b1..Configures RWU with address-mark wakeup.
 */
#define LPUART_CTRL_WAKE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_WAKE_SHIFT)) & LPUART_CTRL_WAKE_MASK)
#define LPUART_CTRL_M_MASK (0x10U)
#define LPUART_CTRL_M_SHIFT (4U)
/*! M - 9-Bit or 8-Bit Mode Select
 *  0b0..Receiver and transmitter use 8-bit data characters.
 *  0b1..Receiver and transmitter use 9-bit data characters.
 */
#define LPUART_CTRL_M(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_M_SHIFT)) & LPUART_CTRL_M_MASK)
#define LPUART_CTRL_RSRC_MASK (0x20U)
#define LPUART_CTRL_RSRC_SHIFT (5U)
/*! RSRC - Receiver Source Select
 *  0b0..Provided LOOPS is set, RSRC is cleared, selects internal loop back mode and the LPUART does not use the
 * LPUART_RX pin. 0b1..Single-wire LPUART mode where the LPUART_TX pin is connected to the transmitter output and
 * receiver input.
 */
#define LPUART_CTRL_RSRC(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_RSRC_SHIFT)) & LPUART_CTRL_RSRC_MASK)
#define LPUART_CTRL_DOZEEN_MASK (0x40U)
#define LPUART_CTRL_DOZEEN_SHIFT (6U)
/*! DOZEEN - Doze Enable
 *  0b0..LPUART is enabled in Doze mode.
 *  0b1..LPUART is disabled in Doze mode.
 */
#define LPUART_CTRL_DOZEEN(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_DOZEEN_SHIFT)) & LPUART_CTRL_DOZEEN_MASK)
#define LPUART_CTRL_LOOPS_MASK (0x80U)
#define LPUART_CTRL_LOOPS_SHIFT (7U)
/*! LOOPS - Loop Mode Select
 *  0b0..Normal operation - LPUART_RX and LPUART_TX use separate pins.
 *  0b1..Loop mode or single-wire mode where transmitter outputs are internally connected to receiver input (see RSRC
 * bit).
 */
#define LPUART_CTRL_LOOPS(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_LOOPS_SHIFT)) & LPUART_CTRL_LOOPS_MASK)
#define LPUART_CTRL_IDLECFG_MASK (0x700U)
#define LPUART_CTRL_IDLECFG_SHIFT (8U)
/*! IDLECFG - Idle Configuration
 *  0b000..1 idle character
 *  0b001..2 idle characters
 *  0b010..4 idle characters
 *  0b011..8 idle characters
 *  0b100..16 idle characters
 *  0b101..32 idle characters
 *  0b110..64 idle characters
 *  0b111..128 idle characters
 */
#define LPUART_CTRL_IDLECFG(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_IDLECFG_SHIFT)) & LPUART_CTRL_IDLECFG_MASK)
#define LPUART_CTRL_MA2IE_MASK (0x4000U)
#define LPUART_CTRL_MA2IE_SHIFT (14U)
/*! MA2IE - Match 2 Interrupt Enable
 *  0b0..MA2F interrupt disabled
 *  0b1..MA2F interrupt enabled
 */
#define LPUART_CTRL_MA2IE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_MA2IE_SHIFT)) & LPUART_CTRL_MA2IE_MASK)
#define LPUART_CTRL_MA1IE_MASK (0x8000U)
#define LPUART_CTRL_MA1IE_SHIFT (15U)
/*! MA1IE - Match 1 Interrupt Enable
 *  0b0..MA1F interrupt disabled
 *  0b1..MA1F interrupt enabled
 */
#define LPUART_CTRL_MA1IE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_MA1IE_SHIFT)) & LPUART_CTRL_MA1IE_MASK)
#define LPUART_CTRL_SBK_MASK (0x10000U)
#define LPUART_CTRL_SBK_SHIFT (16U)
/*! SBK - Send Break
 *  0b0..Normal transmitter operation.
 *  0b1..Queue break character(s) to be sent.
 */
#define LPUART_CTRL_SBK(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_SBK_SHIFT)) & LPUART_CTRL_SBK_MASK)
#define LPUART_CTRL_RWU_MASK (0x20000U)
#define LPUART_CTRL_RWU_SHIFT (17U)
/*! RWU - Receiver Wakeup Control
 *  0b0..Normal receiver operation.
 *  0b1..LPUART receiver in standby waiting for wakeup condition.
 */
#define LPUART_CTRL_RWU(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_RWU_SHIFT)) & LPUART_CTRL_RWU_MASK)
#define LPUART_CTRL_RE_MASK (0x40000U)
#define LPUART_CTRL_RE_SHIFT (18U)
/*! RE - Receiver Enable
 *  0b0..Receiver disabled.
 *  0b1..Receiver enabled.
 */
#define LPUART_CTRL_RE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_RE_SHIFT)) & LPUART_CTRL_RE_MASK)
#define LPUART_CTRL_TE_MASK (0x80000U)
#define LPUART_CTRL_TE_SHIFT (19U)
/*! TE - Transmitter Enable
 *  0b0..Transmitter disabled.
 *  0b1..Transmitter enabled.
 */
#define LPUART_CTRL_TE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_TE_SHIFT)) & LPUART_CTRL_TE_MASK)
#define LPUART_CTRL_ILIE_MASK (0x100000U)
#define LPUART_CTRL_ILIE_SHIFT (20U)
/*! ILIE - Idle Line Interrupt Enable
 *  0b0..Hardware interrupts from IDLE disabled; use polling.
 *  0b1..Hardware interrupt requested when IDLE flag is 1.
 */
#define LPUART_CTRL_ILIE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_ILIE_SHIFT)) & LPUART_CTRL_ILIE_MASK)
#define LPUART_CTRL_RIE_MASK (0x200000U)
#define LPUART_CTRL_RIE_SHIFT (21U)
/*! RIE - Receiver Interrupt Enable
 *  0b0..Hardware interrupts from RDRF disabled; use polling.
 *  0b1..Hardware interrupt requested when RDRF flag is 1.
 */
#define LPUART_CTRL_RIE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_RIE_SHIFT)) & LPUART_CTRL_RIE_MASK)
#define LPUART_CTRL_TCIE_MASK (0x400000U)
#define LPUART_CTRL_TCIE_SHIFT (22U)
/*! TCIE - Transmission Complete Interrupt Enable for
 *  0b0..Hardware interrupts from TC disabled; use polling.
 *  0b1..Hardware interrupt requested when TC flag is 1.
 */
#define LPUART_CTRL_TCIE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_TCIE_SHIFT)) & LPUART_CTRL_TCIE_MASK)
#define LPUART_CTRL_TIE_MASK (0x800000U)
#define LPUART_CTRL_TIE_SHIFT (23U)
/*! TIE - Transmit Interrupt Enable
 *  0b0..Hardware interrupts from TDRE disabled; use polling.
 *  0b1..Hardware interrupt requested when TDRE flag is 1.
 */
#define LPUART_CTRL_TIE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_TIE_SHIFT)) & LPUART_CTRL_TIE_MASK)
#define LPUART_CTRL_PEIE_MASK (0x1000000U)
#define LPUART_CTRL_PEIE_SHIFT (24U)
/*! PEIE - Parity Error Interrupt Enable
 *  0b0..PF interrupts disabled; use polling).
 *  0b1..Hardware interrupt requested when PF is set.
 */
#define LPUART_CTRL_PEIE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_PEIE_SHIFT)) & LPUART_CTRL_PEIE_MASK)
#define LPUART_CTRL_FEIE_MASK (0x2000000U)
#define LPUART_CTRL_FEIE_SHIFT (25U)
/*! FEIE - Framing Error Interrupt Enable
 *  0b0..FE interrupts disabled; use polling.
 *  0b1..Hardware interrupt requested when FE is set.
 */
#define LPUART_CTRL_FEIE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_FEIE_SHIFT)) & LPUART_CTRL_FEIE_MASK)
#define LPUART_CTRL_NEIE_MASK (0x4000000U)
#define LPUART_CTRL_NEIE_SHIFT (26U)
/*! NEIE - Noise Error Interrupt Enable
 *  0b0..NF interrupts disabled; use polling.
 *  0b1..Hardware interrupt requested when NF is set.
 */
#define LPUART_CTRL_NEIE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_NEIE_SHIFT)) & LPUART_CTRL_NEIE_MASK)
#define LPUART_CTRL_ORIE_MASK (0x8000000U)
#define LPUART_CTRL_ORIE_SHIFT (27U)
/*! ORIE - Overrun Interrupt Enable
 *  0b0..OR interrupts disabled; use polling.
 *  0b1..Hardware interrupt requested when OR is set.
 */
#define LPUART_CTRL_ORIE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_ORIE_SHIFT)) & LPUART_CTRL_ORIE_MASK)
#define LPUART_CTRL_TXINV_MASK (0x10000000U)
#define LPUART_CTRL_TXINV_SHIFT (28U)
/*! TXINV - Transmit Data Inversion
 *  0b0..Transmit data not inverted.
 *  0b1..Transmit data inverted.
 */
#define LPUART_CTRL_TXINV(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_TXINV_SHIFT)) & LPUART_CTRL_TXINV_MASK)
#define LPUART_CTRL_TXDIR_MASK (0x20000000U)
#define LPUART_CTRL_TXDIR_SHIFT (29U)
/*! TXDIR - LPUART_TX Pin Direction in Single-Wire Mode
 *  0b0..LPUART_TX pin is an input in single-wire mode.
 *  0b1..LPUART_TX pin is an output in single-wire mode.
 */
#define LPUART_CTRL_TXDIR(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_TXDIR_SHIFT)) & LPUART_CTRL_TXDIR_MASK)
#define LPUART_CTRL_R9T8_MASK (0x40000000U)
#define LPUART_CTRL_R9T8_SHIFT (30U)
/*! R9T8 - Receive Bit 9 / Transmit Bit 8
 */
#define LPUART_CTRL_R9T8(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_R9T8_SHIFT)) & LPUART_CTRL_R9T8_MASK)
#define LPUART_CTRL_R8T9_MASK (0x80000000U)
#define LPUART_CTRL_R8T9_SHIFT (31U)
/*! R8T9 - Receive Bit 8 / Transmit Bit 9
 */
#define LPUART_CTRL_R8T9(x) (((uint32_t)(((uint32_t)(x)) << LPUART_CTRL_R8T9_SHIFT)) & LPUART_CTRL_R8T9_MASK)
/*! @} */

/*! @name DATA - LPUART Data Register */
/*! @{ */
#define LPUART_DATA_R0T0_MASK (0x1U)
#define LPUART_DATA_R0T0_SHIFT (0U)
#define LPUART_DATA_R0T0(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R0T0_SHIFT)) & LPUART_DATA_R0T0_MASK)
#define LPUART_DATA_R1T1_MASK (0x2U)
#define LPUART_DATA_R1T1_SHIFT (1U)
#define LPUART_DATA_R1T1(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R1T1_SHIFT)) & LPUART_DATA_R1T1_MASK)
#define LPUART_DATA_R2T2_MASK (0x4U)
#define LPUART_DATA_R2T2_SHIFT (2U)
#define LPUART_DATA_R2T2(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R2T2_SHIFT)) & LPUART_DATA_R2T2_MASK)
#define LPUART_DATA_R3T3_MASK (0x8U)
#define LPUART_DATA_R3T3_SHIFT (3U)
#define LPUART_DATA_R3T3(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R3T3_SHIFT)) & LPUART_DATA_R3T3_MASK)
#define LPUART_DATA_R4T4_MASK (0x10U)
#define LPUART_DATA_R4T4_SHIFT (4U)
#define LPUART_DATA_R4T4(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R4T4_SHIFT)) & LPUART_DATA_R4T4_MASK)
#define LPUART_DATA_R5T5_MASK (0x20U)
#define LPUART_DATA_R5T5_SHIFT (5U)
#define LPUART_DATA_R5T5(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R5T5_SHIFT)) & LPUART_DATA_R5T5_MASK)
#define LPUART_DATA_R6T6_MASK (0x40U)
#define LPUART_DATA_R6T6_SHIFT (6U)
#define LPUART_DATA_R6T6(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R6T6_SHIFT)) & LPUART_DATA_R6T6_MASK)
#define LPUART_DATA_R7T7_MASK (0x80U)
#define LPUART_DATA_R7T7_SHIFT (7U)
#define LPUART_DATA_R7T7(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R7T7_SHIFT)) & LPUART_DATA_R7T7_MASK)
#define LPUART_DATA_R8T8_MASK (0x100U)
#define LPUART_DATA_R8T8_SHIFT (8U)
#define LPUART_DATA_R8T8(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R8T8_SHIFT)) & LPUART_DATA_R8T8_MASK)
#define LPUART_DATA_R9T9_MASK (0x200U)
#define LPUART_DATA_R9T9_SHIFT (9U)
#define LPUART_DATA_R9T9(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_R9T9_SHIFT)) & LPUART_DATA_R9T9_MASK)
#define LPUART_DATA_IDLINE_MASK (0x800U)
#define LPUART_DATA_IDLINE_SHIFT (11U)
/*! IDLINE - Idle Line
 *  0b0..Receiver was not idle before receiving this character.
 *  0b1..Receiver was idle before receiving this character.
 */
#define LPUART_DATA_IDLINE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_IDLINE_SHIFT)) & LPUART_DATA_IDLINE_MASK)
#define LPUART_DATA_RXEMPT_MASK (0x1000U)
#define LPUART_DATA_RXEMPT_SHIFT (12U)
/*! RXEMPT - Receive Buffer Empty
 *  0b0..Receive buffer contains valid data.
 *  0b1..Receive buffer is empty, data returned on read is not valid.
 */
#define LPUART_DATA_RXEMPT(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_RXEMPT_SHIFT)) & LPUART_DATA_RXEMPT_MASK)
#define LPUART_DATA_FRETSC_MASK (0x2000U)
#define LPUART_DATA_FRETSC_SHIFT (13U)
/*! FRETSC - Frame Error / Transmit Special Character
 *  0b0..The dataword was received without a frame error on read, transmit a normal character on write.
 *  0b1..The dataword was received with a frame error, transmit an idle or break character on transmit.
 */
#define LPUART_DATA_FRETSC(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_FRETSC_SHIFT)) & LPUART_DATA_FRETSC_MASK)
#define LPUART_DATA_PARITYE_MASK (0x4000U)
#define LPUART_DATA_PARITYE_SHIFT (14U)
/*! PARITYE
 *  0b0..The dataword was received without a parity error.
 *  0b1..The dataword was received with a parity error.
 */
#define LPUART_DATA_PARITYE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_PARITYE_SHIFT)) & LPUART_DATA_PARITYE_MASK)
#define LPUART_DATA_NOISY_MASK (0x8000U)
#define LPUART_DATA_NOISY_SHIFT (15U)
/*! NOISY
 *  0b0..The dataword was received without noise.
 *  0b1..The data was received with noise.
 */
#define LPUART_DATA_NOISY(x) (((uint32_t)(((uint32_t)(x)) << LPUART_DATA_NOISY_SHIFT)) & LPUART_DATA_NOISY_MASK)
/*! @} */

/*! @name MATCH - LPUART Match Address Register */
/*! @{ */
#define LPUART_MATCH_MA1_MASK (0x3FFU)
#define LPUART_MATCH_MA1_SHIFT (0U)
/*! MA1 - Match Address 1
 */
#define LPUART_MATCH_MA1(x) (((uint32_t)(((uint32_t)(x)) << LPUART_MATCH_MA1_SHIFT)) & LPUART_MATCH_MA1_MASK)
#define LPUART_MATCH_MA2_MASK (0x3FF0000U)
#define LPUART_MATCH_MA2_SHIFT (16U)
/*! MA2 - Match Address 2
 */
#define LPUART_MATCH_MA2(x) (((uint32_t)(((uint32_t)(x)) << LPUART_MATCH_MA2_SHIFT)) & LPUART_MATCH_MA2_MASK)
/*! @} */

/*! @name MODIR - LPUART Modem IrDA Register */
/*! @{ */
#define LPUART_MODIR_TXCTSE_MASK (0x1U)
#define LPUART_MODIR_TXCTSE_SHIFT (0U)
/*! TXCTSE - Transmitter clear-to-send enable
 *  0b0..CTS has no effect on the transmitter.
 *  0b1..Enables clear-to-send operation. The transmitter checks the state of CTS each time it is ready to send a
 *       character. If CTS is asserted, the character is sent. If CTS is deasserted, the signal TXD remains in the
 *       mark state and transmission is delayed until CTS is asserted. Changes in CTS as a character is being sent
 *       do not affect its transmission.
 */
#define LPUART_MODIR_TXCTSE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_MODIR_TXCTSE_SHIFT)) & LPUART_MODIR_TXCTSE_MASK)
#define LPUART_MODIR_TXRTSE_MASK (0x2U)
#define LPUART_MODIR_TXRTSE_SHIFT (1U)
/*! TXRTSE - Transmitter request-to-send enable
 *  0b0..The transmitter has no effect on RTS.
 *  0b1..When a character is placed into an empty transmitter data buffer , RTS asserts one bit time before the
 *       start bit is transmitted. RTS deasserts one bit time after all characters in the transmitter data buffer and
 *       shift register are completely sent, including the last stop bit.
 */
#define LPUART_MODIR_TXRTSE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_MODIR_TXRTSE_SHIFT)) & LPUART_MODIR_TXRTSE_MASK)
#define LPUART_MODIR_TXRTSPOL_MASK (0x4U)
#define LPUART_MODIR_TXRTSPOL_SHIFT (2U)
/*! TXRTSPOL - Transmitter request-to-send polarity
 *  0b0..Transmitter RTS is active low.
 *  0b1..Transmitter RTS is active high.
 */
#define LPUART_MODIR_TXRTSPOL(x) \
    (((uint32_t)(((uint32_t)(x)) << LPUART_MODIR_TXRTSPOL_SHIFT)) & LPUART_MODIR_TXRTSPOL_MASK)
#define LPUART_MODIR_RXRTSE_MASK (0x8U)
#define LPUART_MODIR_RXRTSE_SHIFT (3U)
/*! RXRTSE - Receiver request-to-send enable
 *  0b0..The receiver has no effect on RTS.
 *  0b1..RTS assertion is configured by the RTSWATER field
 */
#define LPUART_MODIR_RXRTSE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_MODIR_RXRTSE_SHIFT)) & LPUART_MODIR_RXRTSE_MASK)
#define LPUART_MODIR_TXCTSC_MASK (0x10U)
#define LPUART_MODIR_TXCTSC_SHIFT (4U)
/*! TXCTSC - Transmit CTS Configuration
 *  0b0..CTS input is sampled at the start of each character.
 *  0b1..CTS input is sampled when the transmitter is idle.
 */
#define LPUART_MODIR_TXCTSC(x) (((uint32_t)(((uint32_t)(x)) << LPUART_MODIR_TXCTSC_SHIFT)) & LPUART_MODIR_TXCTSC_MASK)
#define LPUART_MODIR_TXCTSSRC_MASK (0x20U)
#define LPUART_MODIR_TXCTSSRC_SHIFT (5U)
/*! TXCTSSRC - Transmit CTS Source
 *  0b0..CTS input is the LPUART_CTS pin.
 *  0b1..CTS input is the inverted Receiver Match result.
 */
#define LPUART_MODIR_TXCTSSRC(x) \
    (((uint32_t)(((uint32_t)(x)) << LPUART_MODIR_TXCTSSRC_SHIFT)) & LPUART_MODIR_TXCTSSRC_MASK)
#define LPUART_MODIR_RTSWATER_MASK (0xFF00U)
#define LPUART_MODIR_RTSWATER_SHIFT (8U)
/*! RTSWATER - Receive RTS Configuration
 *  0b00000000..RTS asserts when the receiver FIFO is full or receiving a character that causes the FIFO to become full.
 *  0b00000001..RTS asserts when the receive FIFO is less than or equal to the RXWATER configuration and negates
 *              when the receive FIFO is greater than the RXWATER configuration.
 */
#define LPUART_MODIR_RTSWATER(x) \
    (((uint32_t)(((uint32_t)(x)) << LPUART_MODIR_RTSWATER_SHIFT)) & LPUART_MODIR_RTSWATER_MASK)
#define LPUART_MODIR_TNP_MASK (0x30000U)
#define LPUART_MODIR_TNP_SHIFT (16U)
/*! TNP - Transmitter narrow pulse
 *  0b00..1/OSR.
 *  0b01..2/OSR.
 *  0b10..3/OSR.
 *  0b11..4/OSR.
 */
#define LPUART_MODIR_TNP(x) (((uint32_t)(((uint32_t)(x)) << LPUART_MODIR_TNP_SHIFT)) & LPUART_MODIR_TNP_MASK)
#define LPUART_MODIR_IREN_MASK (0x40000U)
#define LPUART_MODIR_IREN_SHIFT (18U)
/*! IREN - Infrared enable
 *  0b0..IR disabled.
 *  0b1..IR enabled.
 */
#define LPUART_MODIR_IREN(x) (((uint32_t)(((uint32_t)(x)) << LPUART_MODIR_IREN_SHIFT)) & LPUART_MODIR_IREN_MASK)
/*! @} */

/*! @name FIFO - LPUART FIFO Register */
/*! @{ */
#define LPUART_FIFO_RXFIFOSIZE_MASK (0x7U)
#define LPUART_FIFO_RXFIFOSIZE_SHIFT (0U)
/*! RXFIFOSIZE - Receive FIFO. Buffer Depth
 *  0b001..Receive FIFO/Buffer depth = 4 datawords.
 */
#define LPUART_FIFO_RXFIFOSIZE(x) \
    (((uint32_t)(((uint32_t)(x)) << LPUART_FIFO_RXFIFOSIZE_SHIFT)) & LPUART_FIFO_RXFIFOSIZE_MASK)
#define LPUART_FIFO_RXFE_MASK (0x8U)
#define LPUART_FIFO_RXFE_SHIFT (3U)
/*! RXFE - Receive FIFO Enable
 *  0b0..Receive FIFO is not enabled. Buffer is depth 1. (Legacy support)
 *  0b1..Receive FIFO is enabled. Buffer is depth indicted by RXFIFOSIZE.
 */
#define LPUART_FIFO_RXFE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_FIFO_RXFE_SHIFT)) & LPUART_FIFO_RXFE_MASK)
#define LPUART_FIFO_TXFIFOSIZE_MASK (0x70U)
#define LPUART_FIFO_TXFIFOSIZE_SHIFT (4U)
/*! TXFIFOSIZE - Transmit FIFO. Buffer Depth
 *  0b001..Transmit FIFO/Buffer depth = 4 datawords.
 */
#define LPUART_FIFO_TXFIFOSIZE(x) \
    (((uint32_t)(((uint32_t)(x)) << LPUART_FIFO_TXFIFOSIZE_SHIFT)) & LPUART_FIFO_TXFIFOSIZE_MASK)
#define LPUART_FIFO_TXFE_MASK (0x80U)
#define LPUART_FIFO_TXFE_SHIFT (7U)
/*! TXFE - Transmit FIFO Enable
 *  0b0..Transmit FIFO is not enabled. Buffer is depth 1. (Legacy support).
 *  0b1..Transmit FIFO is enabled. Buffer is depth indicated by TXFIFOSIZE.
 */
#define LPUART_FIFO_TXFE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_FIFO_TXFE_SHIFT)) & LPUART_FIFO_TXFE_MASK)
#define LPUART_FIFO_RXUFE_MASK (0x100U)
#define LPUART_FIFO_RXUFE_SHIFT (8U)
/*! RXUFE - Receive FIFO Underflow Interrupt Enable
 *  0b0..RXUF flag does not generate an interrupt to the host.
 *  0b1..RXUF flag generates an interrupt to the host.
 */
#define LPUART_FIFO_RXUFE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_FIFO_RXUFE_SHIFT)) & LPUART_FIFO_RXUFE_MASK)
#define LPUART_FIFO_TXOFE_MASK (0x200U)
#define LPUART_FIFO_TXOFE_SHIFT (9U)
/*! TXOFE - Transmit FIFO Overflow Interrupt Enable
 *  0b0..TXOF flag does not generate an interrupt to the host.
 *  0b1..TXOF flag generates an interrupt to the host.
 */
#define LPUART_FIFO_TXOFE(x) (((uint32_t)(((uint32_t)(x)) << LPUART_FIFO_TXOFE_SHIFT)) & LPUART_FIFO_TXOFE_MASK)
#define LPUART_FIFO_RXIDEN_MASK (0x1C00U)
#define LPUART_FIFO_RXIDEN_SHIFT (10U)
/*! RXIDEN - Receiver Idle Empty Enable
 *  0b000..Disable RDRF assertion due to partially filled FIFO when receiver is idle.
 *  0b001..Enable RDRF assertion due to partially filled FIFO when receiver is idle for 1 character.
 *  0b010..Enable RDRF assertion due to partially filled FIFO when receiver is idle for 2 characters.
 *  0b011..Enable RDRF assertion due to partially filled FIFO when receiver is idle for 4 characters.
 *  0b100..Enable RDRF assertion due to partially filled FIFO when receiver is idle for 8 characters.
 *  0b101..Enable RDRF assertion due to partially filled FIFO when receiver is idle for 16 characters.
 *  0b110..Enable RDRF assertion due to partially filled FIFO when receiver is idle for 32 characters.
 *  0b111..Enable RDRF assertion due to partially filled FIFO when receiver is idle for 64 characters.
 */
#define LPUART_FIFO_RXIDEN(x) (((uint32_t)(((uint32_t)(x)) << LPUART_FIFO_RXIDEN_SHIFT)) & LPUART_FIFO_RXIDEN_MASK)
#define LPUART_FIFO_RXFLUSH_MASK (0x4000U)
#define LPUART_FIFO_RXFLUSH_SHIFT (14U)
/*! RXFLUSH - Receive FIFO/Buffer Flush
 *  0b0..No flush operation occurs.
 *  0b1..All data in the receive FIFO/buffer is cleared out.
 */
#define LPUART_FIFO_RXFLUSH(x) (((uint32_t)(((uint32_t)(x)) << LPUART_FIFO_RXFLUSH_SHIFT)) & LPUART_FIFO_RXFLUSH_MASK)
#define LPUART_FIFO_TXFLUSH_MASK (0x8000U)
#define LPUART_FIFO_TXFLUSH_SHIFT (15U)
/*! TXFLUSH - Transmit FIFO/Buffer Flush
 *  0b0..No flush operation occurs.
 *  0b1..All data in the transmit FIFO/Buffer is cleared out.
 */
#define LPUART_FIFO_TXFLUSH(x) (((uint32_t)(((uint32_t)(x)) << LPUART_FIFO_TXFLUSH_SHIFT)) & LPUART_FIFO_TXFLUSH_MASK)
#define LPUART_FIFO_RXUF_MASK (0x10000U)
#define LPUART_FIFO_RXUF_SHIFT (16U)
/*! RXUF - Receiver Buffer Underflow Flag
 *  0b0..No receive buffer underflow has occurred since the last time the flag was cleared.
 *  0b1..At least one receive buffer underflow has occurred since the last time the flag was cleared.
 */
#define LPUART_FIFO_RXUF(x) (((uint32_t)(((uint32_t)(x)) << LPUART_FIFO_RXUF_SHIFT)) & LPUART_FIFO_RXUF_MASK)
#define LPUART_FIFO_TXOF_MASK (0x20000U)
#define LPUART_FIFO_TXOF_SHIFT (17U)
/*! TXOF - Transmitter Buffer Overflow Flag
 *  0b0..No transmit buffer overflow has occurred since the last time the flag was cleared.
 *  0b1..At least one transmit buffer overflow has occurred since the last time the flag was cleared.
 */
#define LPUART_FIFO_TXOF(x) (((uint32_t)(((uint32_t)(x)) << LPUART_FIFO_TXOF_SHIFT)) & LPUART_FIFO_TXOF_MASK)
#define LPUART_FIFO_RXEMPT_MASK (0x400000U)
#define LPUART_FIFO_RXEMPT_SHIFT (22U)
/*! RXEMPT - Receive Buffer/FIFO Empty
 *  0b0..Receive buffer is not empty.
 *  0b1..Receive buffer is empty.
 */
#define LPUART_FIFO_RXEMPT(x) (((uint32_t)(((uint32_t)(x)) << LPUART_FIFO_RXEMPT_SHIFT)) & LPUART_FIFO_RXEMPT_MASK)
#define LPUART_FIFO_TXEMPT_MASK (0x800000U)
#define LPUART_FIFO_TXEMPT_SHIFT (23U)
/*! TXEMPT - Transmit Buffer/FIFO Empty
 *  0b0..Transmit buffer is not empty.
 *  0b1..Transmit buffer is empty.
 */
#define LPUART_FIFO_TXEMPT(x) (((uint32_t)(((uint32_t)(x)) << LPUART_FIFO_TXEMPT_SHIFT)) & LPUART_FIFO_TXEMPT_MASK)
/*! @} */

/*! @name WATER - LPUART Watermark Register */
/*! @{ */
#define LPUART_WATER_TXWATER_MASK (0xFFU)
#define LPUART_WATER_TXWATER_SHIFT (0U)
/*! TXWATER - Transmit Watermark
 */
#define LPUART_WATER_TXWATER(x) \
    (((uint32_t)(((uint32_t)(x)) << LPUART_WATER_TXWATER_SHIFT)) & LPUART_WATER_TXWATER_MASK)
#define LPUART_WATER_TXCOUNT_MASK (0xFF00U)
#define LPUART_WATER_TXCOUNT_SHIFT (8U)
/*! TXCOUNT - Transmit Counter
 */
#define LPUART_WATER_TXCOUNT(x) \
    (((uint32_t)(((uint32_t)(x)) << LPUART_WATER_TXCOUNT_SHIFT)) & LPUART_WATER_TXCOUNT_MASK)
#define LPUART_WATER_RXWATER_MASK (0xFF0000U)
#define LPUART_WATER_RXWATER_SHIFT (16U)
/*! RXWATER - Receive Watermark
 */
#define LPUART_WATER_RXWATER(x) \
    (((uint32_t)(((uint32_t)(x)) << LPUART_WATER_RXWATER_SHIFT)) & LPUART_WATER_RXWATER_MASK)
#define LPUART_WATER_RXCOUNT_MASK (0xFF000000U)
#define LPUART_WATER_RXCOUNT_SHIFT (24U)
/*! RXCOUNT - Receive Counter
 */
#define LPUART_WATER_RXCOUNT(x) \
    (((uint32_t)(((uint32_t)(x)) << LPUART_WATER_RXCOUNT_SHIFT)) & LPUART_WATER_RXCOUNT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group LPUART_Register_Masks */

/* LPUART - Peripheral instance base addresses */
/** Peripheral LPUART0 base address */
#define LPUART0_BASE (0x400C4000u)
/** Peripheral LPUART0 base pointer */
#define LPUART0 ((LPUART_Type *)LPUART0_BASE)
/** Peripheral LPUART1 base address */
#define LPUART1_BASE (0x400C5000u)
/** Peripheral LPUART1 base pointer */
#define LPUART1 ((LPUART_Type *)LPUART1_BASE)
/** Peripheral LPUART2 base address */
#define LPUART2_BASE (0x40046000u)
/** Peripheral LPUART2 base pointer */
#define LPUART2 ((LPUART_Type *)LPUART2_BASE)
/** Array initializer of LPUART peripheral base addresses */
#define LPUART_BASE_ADDRS                        \
    {                                            \
        LPUART0_BASE, LPUART1_BASE, LPUART2_BASE \
    }
/** Array initializer of LPUART peripheral base pointers */
#define LPUART_BASE_PTRS          \
    {                             \
        LPUART0, LPUART1, LPUART2 \
    }
/** Interrupt vectors for the LPUART peripheral type */
#define LPUART_RX_TX_IRQS                        \
    {                                            \
        LPUART0_IRQn, LPUART1_IRQn, LPUART2_IRQn \
    }
#define LPUART_ERR_IRQS                          \
    {                                            \
        LPUART0_IRQn, LPUART1_IRQn, LPUART2_IRQn \
    }

/*!
 * @}
 */ /* end of group LPUART_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- MCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Peripheral_Access_Layer MCM Peripheral Access Layer
 * @{
 */

/** MCM - Register Layout Typedef */
typedef struct
{
    uint8_t RESERVED_0[8];
    __I uint16_t PLASC;  /**< Crossbar Switch (AXBS) Slave Configuration, offset: 0x8 */
    __I uint16_t PLAMC;  /**< Crossbar Switch (AXBS) Master Configuration, offset: 0xA */
    __IO uint32_t PLACR; /**< Platform Control Register, offset: 0xC */
    uint8_t RESERVED_1[48];
    __IO uint32_t CPO; /**< Compute Operation Control Register, offset: 0x40 */
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
#define MCM_PLASC_ASC_MASK (0xFFU)
#define MCM_PLASC_ASC_SHIFT (0U)
/*! ASC - Each bit in the ASC field indicates whether there is a corresponding connection to the
 *    crossbar switch's slave input port.
 *  0b00000000..A bus slave connection to AXBS input port n is absent.
 *  0b00000001..A bus slave connection to AXBS input port n is present.
 */
#define MCM_PLASC_ASC(x) (((uint16_t)(((uint16_t)(x)) << MCM_PLASC_ASC_SHIFT)) & MCM_PLASC_ASC_MASK)
/*! @} */

/*! @name PLAMC - Crossbar Switch (AXBS) Master Configuration */
/*! @{ */
#define MCM_PLAMC_AMC_MASK (0xFFU)
#define MCM_PLAMC_AMC_SHIFT (0U)
/*! AMC - Each bit in the AMC field indicates whether there is a corresponding connection to the AXBS master input port.
 *  0b00000000..A bus master connection to AXBS input port n is absent
 *  0b00000001..A bus master connection to AXBS input port n is present
 */
#define MCM_PLAMC_AMC(x) (((uint16_t)(((uint16_t)(x)) << MCM_PLAMC_AMC_SHIFT)) & MCM_PLAMC_AMC_MASK)
/*! @} */

/*! @name PLACR - Platform Control Register */
/*! @{ */
#define MCM_PLACR_MMCAU_MASK (0x100U)
#define MCM_PLACR_MMCAU_SHIFT (8U)
/*! MMCAU - MMCAU Present
 *  0b0..MMCAU is disabled
 *  0b1..MMCAU is enabled
 */
#define MCM_PLACR_MMCAU(x) (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_MMCAU_SHIFT)) & MCM_PLACR_MMCAU_MASK)
#define MCM_PLACR_ARB_MASK (0x200U)
#define MCM_PLACR_ARB_SHIFT (9U)
/*! ARB - Arbitration select
 *  0b0..Fixed-priority arbitration for the crossbar masters
 *  0b1..Round-robin arbitration for the crossbar masters
 */
#define MCM_PLACR_ARB(x) (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_ARB_SHIFT)) & MCM_PLACR_ARB_MASK)
#define MCM_PLACR_CFCC_MASK (0x400U)
#define MCM_PLACR_CFCC_SHIFT (10U)
/*! CFCC - Clear Flash Controller Cache
 */
#define MCM_PLACR_CFCC(x) (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_CFCC_SHIFT)) & MCM_PLACR_CFCC_MASK)
#define MCM_PLACR_DFCDA_MASK (0x800U)
#define MCM_PLACR_DFCDA_SHIFT (11U)
/*! DFCDA - Disable Flash Controller Data Caching
 *  0b0..Enable flash controller data caching
 *  0b1..Disable flash controller data caching.
 */
#define MCM_PLACR_DFCDA(x) (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_DFCDA_SHIFT)) & MCM_PLACR_DFCDA_MASK)
#define MCM_PLACR_DFCIC_MASK (0x1000U)
#define MCM_PLACR_DFCIC_SHIFT (12U)
/*! DFCIC - Disable Flash Controller Instruction Caching
 *  0b0..Enable flash controller instruction caching.
 *  0b1..Disable flash controller instruction caching.
 */
#define MCM_PLACR_DFCIC(x) (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_DFCIC_SHIFT)) & MCM_PLACR_DFCIC_MASK)
#define MCM_PLACR_DFCC_MASK (0x2000U)
#define MCM_PLACR_DFCC_SHIFT (13U)
/*! DFCC - Disable Flash Controller Cache
 *  0b0..Enable flash controller cache.
 *  0b1..Disable flash controller cache.
 */
#define MCM_PLACR_DFCC(x) (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_DFCC_SHIFT)) & MCM_PLACR_DFCC_MASK)
#define MCM_PLACR_EFDS_MASK (0x4000U)
#define MCM_PLACR_EFDS_SHIFT (14U)
/*! EFDS - Enable Flash Data Speculation
 *  0b0..Disable flash data speculation.
 *  0b1..Enable flash data speculation.
 */
#define MCM_PLACR_EFDS(x) (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_EFDS_SHIFT)) & MCM_PLACR_EFDS_MASK)
#define MCM_PLACR_DFCS_MASK (0x8000U)
#define MCM_PLACR_DFCS_SHIFT (15U)
/*! DFCS - Disable Flash Controller Speculation
 *  0b0..Enable flash controller speculation.
 *  0b1..Disable flash controller speculation.
 */
#define MCM_PLACR_DFCS(x) (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_DFCS_SHIFT)) & MCM_PLACR_DFCS_MASK)
#define MCM_PLACR_ESFC_MASK (0x10000U)
#define MCM_PLACR_ESFC_SHIFT (16U)
/*! ESFC - Enable Stalling Flash Controller
 *  0b0..Disable stalling flash controller when flash is busy.
 *  0b1..Enable stalling flash controller when flash is busy.
 */
#define MCM_PLACR_ESFC(x) (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_ESFC_SHIFT)) & MCM_PLACR_ESFC_MASK)
/*! @} */

/*! @name CPO - Compute Operation Control Register */
/*! @{ */
#define MCM_CPO_CPOREQ_MASK (0x1U)
#define MCM_CPO_CPOREQ_SHIFT (0U)
/*! CPOREQ - Compute Operation Request
 *  0b0..Request is cleared.
 *  0b1..Request Compute Operation.
 */
#define MCM_CPO_CPOREQ(x) (((uint32_t)(((uint32_t)(x)) << MCM_CPO_CPOREQ_SHIFT)) & MCM_CPO_CPOREQ_MASK)
#define MCM_CPO_CPOACK_MASK (0x2U)
#define MCM_CPO_CPOACK_SHIFT (1U)
/*! CPOACK - Compute Operation Acknowledge
 *  0b0..Compute operation entry has not completed or compute operation exit has completed.
 *  0b1..Compute operation entry has completed or compute operation exit has not completed.
 */
#define MCM_CPO_CPOACK(x) (((uint32_t)(((uint32_t)(x)) << MCM_CPO_CPOACK_SHIFT)) & MCM_CPO_CPOACK_MASK)
#define MCM_CPO_CPOWOI_MASK (0x4U)
#define MCM_CPO_CPOWOI_SHIFT (2U)
/*! CPOWOI - Compute Operation Wake-up on Interrupt
 *  0b0..No effect.
 *  0b1..When set, the CPOREQ is cleared on any interrupt or exception vector fetch.
 */
#define MCM_CPO_CPOWOI(x) (((uint32_t)(((uint32_t)(x)) << MCM_CPO_CPOWOI_SHIFT)) & MCM_CPO_CPOWOI_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group MCM_Register_Masks */

/* MCM - Peripheral instance base addresses */
/** Peripheral MCM0 base address */
#define MCM0_BASE (0xF0003008u)
/** Peripheral MCM0 base pointer */
#define MCM0 ((MCM_Type *)MCM0_BASE)
/** Array initializer of MCM peripheral base addresses */
#define MCM_BASE_ADDRS \
    {                  \
        MCM0_BASE      \
    }
/** Array initializer of MCM peripheral base pointers */
#define MCM_BASE_PTRS \
    {                 \
        MCM0          \
    }

/*!
 * @}
 */ /* end of group MCM_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- MMDVSQ Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MMDVSQ_Peripheral_Access_Layer MMDVSQ Peripheral Access Layer
 * @{
 */

/** MMDVSQ - Register Layout Typedef */
typedef struct
{
    __IO uint32_t DEND; /**< Dividend Register, offset: 0x0 */
    __IO uint32_t DSOR; /**< Divisor Register, offset: 0x4 */
    __IO uint32_t CSR;  /**< Control/Status Register, offset: 0x8 */
    __IO uint32_t RES;  /**< Result Register, offset: 0xC */
    __O uint32_t RCND;  /**< Radicand Register, offset: 0x10 */
} MMDVSQ_Type;

/* ----------------------------------------------------------------------------
   -- MMDVSQ Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MMDVSQ_Register_Masks MMDVSQ Register Masks
 * @{
 */

/*! @name DEND - Dividend Register */
/*! @{ */
#define MMDVSQ_DEND_DIVIDEND_MASK (0xFFFFFFFFU)
#define MMDVSQ_DEND_DIVIDEND_SHIFT (0U)
/*! DIVIDEND - Dividend
 */
#define MMDVSQ_DEND_DIVIDEND(x) \
    (((uint32_t)(((uint32_t)(x)) << MMDVSQ_DEND_DIVIDEND_SHIFT)) & MMDVSQ_DEND_DIVIDEND_MASK)
/*! @} */

/*! @name DSOR - Divisor Register */
/*! @{ */
#define MMDVSQ_DSOR_DIVISOR_MASK (0xFFFFFFFFU)
#define MMDVSQ_DSOR_DIVISOR_SHIFT (0U)
/*! DIVISOR - Divisor
 */
#define MMDVSQ_DSOR_DIVISOR(x) (((uint32_t)(((uint32_t)(x)) << MMDVSQ_DSOR_DIVISOR_SHIFT)) & MMDVSQ_DSOR_DIVISOR_MASK)
/*! @} */

/*! @name CSR - Control/Status Register */
/*! @{ */
#define MMDVSQ_CSR_SRT_MASK (0x1U)
#define MMDVSQ_CSR_SRT_SHIFT (0U)
/*! SRT - Start
 *  0b0..No operation initiated
 *  0b1..If CSR[DFS] = 1, then initiate a divide calculation, else ignore
 */
#define MMDVSQ_CSR_SRT(x) (((uint32_t)(((uint32_t)(x)) << MMDVSQ_CSR_SRT_SHIFT)) & MMDVSQ_CSR_SRT_MASK)
#define MMDVSQ_CSR_USGN_MASK (0x2U)
#define MMDVSQ_CSR_USGN_SHIFT (1U)
/*! USGN - Unsigned calculation
 *  0b0..Perform a signed divide
 *  0b1..Perform an unsigned divide
 */
#define MMDVSQ_CSR_USGN(x) (((uint32_t)(((uint32_t)(x)) << MMDVSQ_CSR_USGN_SHIFT)) & MMDVSQ_CSR_USGN_MASK)
#define MMDVSQ_CSR_REM_MASK (0x4U)
#define MMDVSQ_CSR_REM_SHIFT (2U)
/*! REM - REMainder calculation
 *  0b0..Return the quotient in the RES for the divide calculation
 *  0b1..Return the remainder in the RES for the divide calculation
 */
#define MMDVSQ_CSR_REM(x) (((uint32_t)(((uint32_t)(x)) << MMDVSQ_CSR_REM_SHIFT)) & MMDVSQ_CSR_REM_MASK)
#define MMDVSQ_CSR_DZE_MASK (0x8U)
#define MMDVSQ_CSR_DZE_SHIFT (3U)
/*! DZE - Divide-by-Zero-Enable
 *  0b0..Reads of the RES register return the register contents
 *  0b1..If CSR[DZ] = 1, an attempted read of RES register is error terminated to signal a divide-by-zero, else the
 * register contents are returned
 */
#define MMDVSQ_CSR_DZE(x) (((uint32_t)(((uint32_t)(x)) << MMDVSQ_CSR_DZE_SHIFT)) & MMDVSQ_CSR_DZE_MASK)
#define MMDVSQ_CSR_DZ_MASK (0x10U)
#define MMDVSQ_CSR_DZ_SHIFT (4U)
/*! DZ - Divide-by-Zero
 *  0b0..The last divide operation had a non-zero divisor, that is, DSOR != 0
 *  0b1..The last divide operation had a zero divisor, that is, DSOR = 0
 */
#define MMDVSQ_CSR_DZ(x) (((uint32_t)(((uint32_t)(x)) << MMDVSQ_CSR_DZ_SHIFT)) & MMDVSQ_CSR_DZ_MASK)
#define MMDVSQ_CSR_DFS_MASK (0x20U)
#define MMDVSQ_CSR_DFS_SHIFT (5U)
/*! DFS - Disable Fast Start
 *  0b0..A divide operation is initiated by a write to the DSOR register
 *  0b1..A divide operation is initiated by a write to the CSR register with CSR[SRT] = 1
 */
#define MMDVSQ_CSR_DFS(x) (((uint32_t)(((uint32_t)(x)) << MMDVSQ_CSR_DFS_SHIFT)) & MMDVSQ_CSR_DFS_MASK)
#define MMDVSQ_CSR_SQRT_MASK (0x20000000U)
#define MMDVSQ_CSR_SQRT_SHIFT (29U)
/*! SQRT - SQUARE ROOT
 *  0b0..Current or last MMDVSQ operation was not a square root
 *  0b1..Current or last MMDVSQ operation was a square root
 */
#define MMDVSQ_CSR_SQRT(x) (((uint32_t)(((uint32_t)(x)) << MMDVSQ_CSR_SQRT_SHIFT)) & MMDVSQ_CSR_SQRT_MASK)
#define MMDVSQ_CSR_DIV_MASK (0x40000000U)
#define MMDVSQ_CSR_DIV_SHIFT (30U)
/*! DIV - DIVIDE
 *  0b0..Current or last MMDVSQ operation was not a divide
 *  0b1..Current or last MMDVSQ operation was a divide
 */
#define MMDVSQ_CSR_DIV(x) (((uint32_t)(((uint32_t)(x)) << MMDVSQ_CSR_DIV_SHIFT)) & MMDVSQ_CSR_DIV_MASK)
#define MMDVSQ_CSR_BUSY_MASK (0x80000000U)
#define MMDVSQ_CSR_BUSY_SHIFT (31U)
/*! BUSY - BUSY
 *  0b0..MMDVSQ is idle
 *  0b1..MMDVSQ is busy performing a divide or square root calculation
 */
#define MMDVSQ_CSR_BUSY(x) (((uint32_t)(((uint32_t)(x)) << MMDVSQ_CSR_BUSY_SHIFT)) & MMDVSQ_CSR_BUSY_MASK)
/*! @} */

/*! @name RES - Result Register */
/*! @{ */
#define MMDVSQ_RES_RESULT_MASK (0xFFFFFFFFU)
#define MMDVSQ_RES_RESULT_SHIFT (0U)
/*! RESULT - Result
 */
#define MMDVSQ_RES_RESULT(x) (((uint32_t)(((uint32_t)(x)) << MMDVSQ_RES_RESULT_SHIFT)) & MMDVSQ_RES_RESULT_MASK)
/*! @} */

/*! @name RCND - Radicand Register */
/*! @{ */
#define MMDVSQ_RCND_RADICAND_MASK (0xFFFFFFFFU)
#define MMDVSQ_RCND_RADICAND_SHIFT (0U)
/*! RADICAND - Radicand
 */
#define MMDVSQ_RCND_RADICAND(x) \
    (((uint32_t)(((uint32_t)(x)) << MMDVSQ_RCND_RADICAND_SHIFT)) & MMDVSQ_RCND_RADICAND_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group MMDVSQ_Register_Masks */

/* MMDVSQ - Peripheral instance base addresses */
/** Peripheral MMDVSQ0 base address */
#define MMDVSQ0_BASE (0xF0004000u)
/** Peripheral MMDVSQ0 base pointer */
#define MMDVSQ0 ((MMDVSQ_Type *)MMDVSQ0_BASE)
/** Array initializer of MMDVSQ peripheral base addresses */
#define MMDVSQ_BASE_ADDRS \
    {                     \
        MMDVSQ0_BASE      \
    }
/** Array initializer of MMDVSQ peripheral base pointers */
#define MMDVSQ_BASE_PTRS \
    {                    \
        MMDVSQ0          \
    }

/*!
 * @}
 */ /* end of group MMDVSQ_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- MSCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MSCM_Peripheral_Access_Layer MSCM Peripheral Access Layer
 * @{
 */

/** MSCM - Register Layout Typedef */
typedef struct
{
    __I uint32_t CPxTYPE;   /**< Processor X Type Register, offset: 0x0 */
    __I uint32_t CPxNUM;    /**< Processor X Number Register, offset: 0x4 */
    __I uint32_t CPxMASTER; /**< Processor X Master Register, offset: 0x8 */
    __I uint32_t CPxCOUNT;  /**< Processor X Count Register, offset: 0xC */
    __I uint32_t CPxCFG0;   /**< Processor X Configuration Register, offset: 0x10 */
    __I uint32_t CPxCFG1;   /**< Processor X Configuration Register, offset: 0x14 */
    __I uint32_t CPxCFG2;   /**< Processor X Configuration Register, offset: 0x18 */
    __I uint32_t CPxCFG3;   /**< Processor X Configuration Register, offset: 0x1C */
    struct
    {                        /* offset: 0x20, array step: 0x20 */
        __I uint32_t TYPE;   /**< Processor 0 Type Register, array offset: 0x20, array step: 0x20 */
        __I uint32_t NUM;    /**< Processor 0 Number Register, array offset: 0x24, array step: 0x20 */
        __I uint32_t MASTER; /**< Processor 0 Master Register, array offset: 0x28, array step: 0x20 */
        __I uint32_t COUNT;  /**< Processor 0 Count Register, array offset: 0x2C, array step: 0x20 */
        __I uint32_t CFG0;   /**< Processor 0 Configuration Register, array offset: 0x30, array step: 0x20 */
        __I uint32_t CFG1;   /**< Processor 0 Configuration Register, array offset: 0x34, array step: 0x20 */
        __I uint32_t CFG2;   /**< Processor 0 Configuration Register, array offset: 0x38, array step: 0x20 */
        __I uint32_t CFG3;   /**< Processor 0 Configuration Register, array offset: 0x3C, array step: 0x20 */
    } CP[1];
    uint8_t RESERVED_0[960];
    __I uint32_t OCMDR[3]; /**< On-Chip Memory Descriptor Register, array offset: 0x400, array step: 0x4 */
} MSCM_Type;

/* ----------------------------------------------------------------------------
   -- MSCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MSCM_Register_Masks MSCM Register Masks
 * @{
 */

/*! @name CPxTYPE - Processor X Type Register */
/*! @{ */
#define MSCM_CPxTYPE_RYPZ_MASK (0xFFU)
#define MSCM_CPxTYPE_RYPZ_SHIFT (0U)
/*! RYPZ - Processor x Revision
 */
#define MSCM_CPxTYPE_RYPZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxTYPE_RYPZ_SHIFT)) & MSCM_CPxTYPE_RYPZ_MASK)
#define MSCM_CPxTYPE_PERSONALITY_MASK (0xFFFFFF00U)
#define MSCM_CPxTYPE_PERSONALITY_SHIFT (8U)
/*! PERSONALITY - Processor x Personality
 */
#define MSCM_CPxTYPE_PERSONALITY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPxTYPE_PERSONALITY_SHIFT)) & MSCM_CPxTYPE_PERSONALITY_MASK)
/*! @} */

/*! @name CPxNUM - Processor X Number Register */
/*! @{ */
#define MSCM_CPxNUM_CPN_MASK (0x1U)
#define MSCM_CPxNUM_CPN_SHIFT (0U)
/*! CPN - Processor x Number
 */
#define MSCM_CPxNUM_CPN(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxNUM_CPN_SHIFT)) & MSCM_CPxNUM_CPN_MASK)
/*! @} */

/*! @name CPxMASTER - Processor X Master Register */
/*! @{ */
#define MSCM_CPxMASTER_PPN_MASK (0x3FU)
#define MSCM_CPxMASTER_PPN_SHIFT (0U)
/*! PPN - Processor x Physical Port Number
 */
#define MSCM_CPxMASTER_PPN(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxMASTER_PPN_SHIFT)) & MSCM_CPxMASTER_PPN_MASK)
/*! @} */

/*! @name CPxCOUNT - Processor X Count Register */
/*! @{ */
#define MSCM_CPxCOUNT_PCNT_MASK (0x3U)
#define MSCM_CPxCOUNT_PCNT_SHIFT (0U)
/*! PCNT - Processor Count
 */
#define MSCM_CPxCOUNT_PCNT(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCOUNT_PCNT_SHIFT)) & MSCM_CPxCOUNT_PCNT_MASK)
/*! @} */

/*! @name CPxCFG0 - Processor X Configuration Register */
/*! @{ */
#define MSCM_CPxCFG0_DCWY_MASK (0xFFU)
#define MSCM_CPxCFG0_DCWY_SHIFT (0U)
/*! DCWY - Level 1 Data Cache Ways
 */
#define MSCM_CPxCFG0_DCWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG0_DCWY_SHIFT)) & MSCM_CPxCFG0_DCWY_MASK)
#define MSCM_CPxCFG0_DCSZ_MASK (0xFF00U)
#define MSCM_CPxCFG0_DCSZ_SHIFT (8U)
/*! DCSZ - Level 1 Data Cache Size
 */
#define MSCM_CPxCFG0_DCSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG0_DCSZ_SHIFT)) & MSCM_CPxCFG0_DCSZ_MASK)
#define MSCM_CPxCFG0_ICWY_MASK (0xFF0000U)
#define MSCM_CPxCFG0_ICWY_SHIFT (16U)
/*! ICWY - Level 1 Instruction Cache Ways
 */
#define MSCM_CPxCFG0_ICWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG0_ICWY_SHIFT)) & MSCM_CPxCFG0_ICWY_MASK)
#define MSCM_CPxCFG0_ICSZ_MASK (0xFF000000U)
#define MSCM_CPxCFG0_ICSZ_SHIFT (24U)
/*! ICSZ - Level 1 Instruction Cache Size
 */
#define MSCM_CPxCFG0_ICSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG0_ICSZ_SHIFT)) & MSCM_CPxCFG0_ICSZ_MASK)
/*! @} */

/*! @name CPxCFG1 - Processor X Configuration Register */
/*! @{ */
#define MSCM_CPxCFG1_DCWY_MASK (0xFFU)
#define MSCM_CPxCFG1_DCWY_SHIFT (0U)
/*! DCWY - Level 1 Data Cache Ways
 */
#define MSCM_CPxCFG1_DCWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG1_DCWY_SHIFT)) & MSCM_CPxCFG1_DCWY_MASK)
#define MSCM_CPxCFG1_DCSZ_MASK (0xFF00U)
#define MSCM_CPxCFG1_DCSZ_SHIFT (8U)
/*! DCSZ - Level 1 Data Cache Size
 */
#define MSCM_CPxCFG1_DCSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG1_DCSZ_SHIFT)) & MSCM_CPxCFG1_DCSZ_MASK)
#define MSCM_CPxCFG1_ICWY_MASK (0xFF0000U)
#define MSCM_CPxCFG1_ICWY_SHIFT (16U)
/*! ICWY - Level 1 Instruction Cache Ways
 */
#define MSCM_CPxCFG1_ICWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG1_ICWY_SHIFT)) & MSCM_CPxCFG1_ICWY_MASK)
#define MSCM_CPxCFG1_ICSZ_MASK (0xFF000000U)
#define MSCM_CPxCFG1_ICSZ_SHIFT (24U)
/*! ICSZ - Level 1 Instruction Cache Size
 */
#define MSCM_CPxCFG1_ICSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG1_ICSZ_SHIFT)) & MSCM_CPxCFG1_ICSZ_MASK)
/*! @} */

/*! @name CPxCFG2 - Processor X Configuration Register */
/*! @{ */
#define MSCM_CPxCFG2_DCWY_MASK (0xFFU)
#define MSCM_CPxCFG2_DCWY_SHIFT (0U)
/*! DCWY - Level 1 Data Cache Ways
 */
#define MSCM_CPxCFG2_DCWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG2_DCWY_SHIFT)) & MSCM_CPxCFG2_DCWY_MASK)
#define MSCM_CPxCFG2_DCSZ_MASK (0xFF00U)
#define MSCM_CPxCFG2_DCSZ_SHIFT (8U)
/*! DCSZ - Level 1 Data Cache Size
 */
#define MSCM_CPxCFG2_DCSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG2_DCSZ_SHIFT)) & MSCM_CPxCFG2_DCSZ_MASK)
#define MSCM_CPxCFG2_ICWY_MASK (0xFF0000U)
#define MSCM_CPxCFG2_ICWY_SHIFT (16U)
/*! ICWY - Level 1 Instruction Cache Ways
 */
#define MSCM_CPxCFG2_ICWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG2_ICWY_SHIFT)) & MSCM_CPxCFG2_ICWY_MASK)
#define MSCM_CPxCFG2_ICSZ_MASK (0xFF000000U)
#define MSCM_CPxCFG2_ICSZ_SHIFT (24U)
/*! ICSZ - Level 1 Instruction Cache Size
 */
#define MSCM_CPxCFG2_ICSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG2_ICSZ_SHIFT)) & MSCM_CPxCFG2_ICSZ_MASK)
/*! @} */

/*! @name CPxCFG3 - Processor X Configuration Register */
/*! @{ */
#define MSCM_CPxCFG3_DCWY_MASK (0xFFU)
#define MSCM_CPxCFG3_DCWY_SHIFT (0U)
/*! DCWY - Level 1 Data Cache Ways
 */
#define MSCM_CPxCFG3_DCWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG3_DCWY_SHIFT)) & MSCM_CPxCFG3_DCWY_MASK)
#define MSCM_CPxCFG3_DCSZ_MASK (0xFF00U)
#define MSCM_CPxCFG3_DCSZ_SHIFT (8U)
/*! DCSZ - Level 1 Data Cache Size
 */
#define MSCM_CPxCFG3_DCSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG3_DCSZ_SHIFT)) & MSCM_CPxCFG3_DCSZ_MASK)
#define MSCM_CPxCFG3_ICWY_MASK (0xFF0000U)
#define MSCM_CPxCFG3_ICWY_SHIFT (16U)
/*! ICWY - Level 1 Instruction Cache Ways
 */
#define MSCM_CPxCFG3_ICWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG3_ICWY_SHIFT)) & MSCM_CPxCFG3_ICWY_MASK)
#define MSCM_CPxCFG3_ICSZ_MASK (0xFF000000U)
#define MSCM_CPxCFG3_ICSZ_SHIFT (24U)
/*! ICSZ - Level 1 Instruction Cache Size
 */
#define MSCM_CPxCFG3_ICSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CPxCFG3_ICSZ_SHIFT)) & MSCM_CPxCFG3_ICSZ_MASK)
/*! @} */

/*! @name TYPE - Processor 0 Type Register */
/*! @{ */
#define MSCM_TYPE_RYPZ_MASK (0xFFU)
#define MSCM_TYPE_RYPZ_SHIFT (0U)
/*! RYPZ - Processor x Revision
 */
#define MSCM_TYPE_RYPZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_TYPE_RYPZ_SHIFT)) & MSCM_TYPE_RYPZ_MASK)
#define MSCM_TYPE_PERSONALITY_MASK (0xFFFFFF00U)
#define MSCM_TYPE_PERSONALITY_SHIFT (8U)
/*! PERSONALITY - Processor x Personality
 */
#define MSCM_TYPE_PERSONALITY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_TYPE_PERSONALITY_SHIFT)) & MSCM_TYPE_PERSONALITY_MASK)
/*! @} */

/* The count of MSCM_TYPE */
#define MSCM_TYPE_COUNT (1U)

/*! @name NUM - Processor 0 Number Register */
/*! @{ */
#define MSCM_NUM_CPN_MASK (0x1U)
#define MSCM_NUM_CPN_SHIFT (0U)
/*! CPN - Processor x Number
 */
#define MSCM_NUM_CPN(x) (((uint32_t)(((uint32_t)(x)) << MSCM_NUM_CPN_SHIFT)) & MSCM_NUM_CPN_MASK)
/*! @} */

/* The count of MSCM_NUM */
#define MSCM_NUM_COUNT (1U)

/*! @name MASTER - Processor 0 Master Register */
/*! @{ */
#define MSCM_MASTER_PPN_MASK (0x3FU)
#define MSCM_MASTER_PPN_SHIFT (0U)
/*! PPN - Processor x Physical Port Number
 */
#define MSCM_MASTER_PPN(x) (((uint32_t)(((uint32_t)(x)) << MSCM_MASTER_PPN_SHIFT)) & MSCM_MASTER_PPN_MASK)
/*! @} */

/* The count of MSCM_MASTER */
#define MSCM_MASTER_COUNT (1U)

/*! @name COUNT - Processor 0 Count Register */
/*! @{ */
#define MSCM_COUNT_PCNT_MASK (0x3U)
#define MSCM_COUNT_PCNT_SHIFT (0U)
/*! PCNT - Processor Count
 */
#define MSCM_COUNT_PCNT(x) (((uint32_t)(((uint32_t)(x)) << MSCM_COUNT_PCNT_SHIFT)) & MSCM_COUNT_PCNT_MASK)
/*! @} */

/* The count of MSCM_COUNT */
#define MSCM_COUNT_COUNT (1U)

/*! @name CFG0 - Processor 0 Configuration Register */
/*! @{ */
#define MSCM_CFG0_DCWY_MASK (0xFFU)
#define MSCM_CFG0_DCWY_SHIFT (0U)
/*! DCWY - Level 1 Data Cache Ways
 */
#define MSCM_CFG0_DCWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG0_DCWY_SHIFT)) & MSCM_CFG0_DCWY_MASK)
#define MSCM_CFG0_DCSZ_MASK (0xFF00U)
#define MSCM_CFG0_DCSZ_SHIFT (8U)
/*! DCSZ - Level 1 Data Cache Size
 */
#define MSCM_CFG0_DCSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG0_DCSZ_SHIFT)) & MSCM_CFG0_DCSZ_MASK)
#define MSCM_CFG0_ICWY_MASK (0xFF0000U)
#define MSCM_CFG0_ICWY_SHIFT (16U)
/*! ICWY - Level 1 Instruction Cache Ways
 */
#define MSCM_CFG0_ICWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG0_ICWY_SHIFT)) & MSCM_CFG0_ICWY_MASK)
#define MSCM_CFG0_ICSZ_MASK (0xFF000000U)
#define MSCM_CFG0_ICSZ_SHIFT (24U)
/*! ICSZ - Level 1 Instruction Cache Size
 */
#define MSCM_CFG0_ICSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG0_ICSZ_SHIFT)) & MSCM_CFG0_ICSZ_MASK)
/*! @} */

/* The count of MSCM_CFG0 */
#define MSCM_CFG0_COUNT (1U)

/*! @name CFG1 - Processor 0 Configuration Register */
/*! @{ */
#define MSCM_CFG1_DCWY_MASK (0xFFU)
#define MSCM_CFG1_DCWY_SHIFT (0U)
/*! DCWY - Level 1 Data Cache Ways
 */
#define MSCM_CFG1_DCWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG1_DCWY_SHIFT)) & MSCM_CFG1_DCWY_MASK)
#define MSCM_CFG1_DCSZ_MASK (0xFF00U)
#define MSCM_CFG1_DCSZ_SHIFT (8U)
/*! DCSZ - Level 1 Data Cache Size
 */
#define MSCM_CFG1_DCSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG1_DCSZ_SHIFT)) & MSCM_CFG1_DCSZ_MASK)
#define MSCM_CFG1_ICWY_MASK (0xFF0000U)
#define MSCM_CFG1_ICWY_SHIFT (16U)
/*! ICWY - Level 1 Instruction Cache Ways
 */
#define MSCM_CFG1_ICWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG1_ICWY_SHIFT)) & MSCM_CFG1_ICWY_MASK)
#define MSCM_CFG1_ICSZ_MASK (0xFF000000U)
#define MSCM_CFG1_ICSZ_SHIFT (24U)
/*! ICSZ - Level 1 Instruction Cache Size
 */
#define MSCM_CFG1_ICSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG1_ICSZ_SHIFT)) & MSCM_CFG1_ICSZ_MASK)
/*! @} */

/* The count of MSCM_CFG1 */
#define MSCM_CFG1_COUNT (1U)

/*! @name CFG2 - Processor 0 Configuration Register */
/*! @{ */
#define MSCM_CFG2_DCWY_MASK (0xFFU)
#define MSCM_CFG2_DCWY_SHIFT (0U)
/*! DCWY - Level 1 Data Cache Ways
 */
#define MSCM_CFG2_DCWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG2_DCWY_SHIFT)) & MSCM_CFG2_DCWY_MASK)
#define MSCM_CFG2_DCSZ_MASK (0xFF00U)
#define MSCM_CFG2_DCSZ_SHIFT (8U)
/*! DCSZ - Level 1 Data Cache Size
 */
#define MSCM_CFG2_DCSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG2_DCSZ_SHIFT)) & MSCM_CFG2_DCSZ_MASK)
#define MSCM_CFG2_ICWY_MASK (0xFF0000U)
#define MSCM_CFG2_ICWY_SHIFT (16U)
/*! ICWY - Level 1 Instruction Cache Ways
 */
#define MSCM_CFG2_ICWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG2_ICWY_SHIFT)) & MSCM_CFG2_ICWY_MASK)
#define MSCM_CFG2_ICSZ_MASK (0xFF000000U)
#define MSCM_CFG2_ICSZ_SHIFT (24U)
/*! ICSZ - Level 1 Instruction Cache Size
 */
#define MSCM_CFG2_ICSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG2_ICSZ_SHIFT)) & MSCM_CFG2_ICSZ_MASK)
/*! @} */

/* The count of MSCM_CFG2 */
#define MSCM_CFG2_COUNT (1U)

/*! @name CFG3 - Processor 0 Configuration Register */
/*! @{ */
#define MSCM_CFG3_DCWY_MASK (0xFFU)
#define MSCM_CFG3_DCWY_SHIFT (0U)
/*! DCWY - Level 1 Data Cache Ways
 */
#define MSCM_CFG3_DCWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG3_DCWY_SHIFT)) & MSCM_CFG3_DCWY_MASK)
#define MSCM_CFG3_DCSZ_MASK (0xFF00U)
#define MSCM_CFG3_DCSZ_SHIFT (8U)
/*! DCSZ - Level 1 Data Cache Size
 */
#define MSCM_CFG3_DCSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG3_DCSZ_SHIFT)) & MSCM_CFG3_DCSZ_MASK)
#define MSCM_CFG3_ICWY_MASK (0xFF0000U)
#define MSCM_CFG3_ICWY_SHIFT (16U)
/*! ICWY - Level 1 Instruction Cache Ways
 */
#define MSCM_CFG3_ICWY(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG3_ICWY_SHIFT)) & MSCM_CFG3_ICWY_MASK)
#define MSCM_CFG3_ICSZ_MASK (0xFF000000U)
#define MSCM_CFG3_ICSZ_SHIFT (24U)
/*! ICSZ - Level 1 Instruction Cache Size
 */
#define MSCM_CFG3_ICSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_CFG3_ICSZ_SHIFT)) & MSCM_CFG3_ICSZ_MASK)
/*! @} */

/* The count of MSCM_CFG3 */
#define MSCM_CFG3_COUNT (1U)

/*! @name OCMDR - On-Chip Memory Descriptor Register */
/*! @{ */
#define MSCM_OCMDR_OCMPU_MASK (0x1000U)
#define MSCM_OCMDR_OCMPU_SHIFT (12U)
#define MSCM_OCMDR_OCMPU(x) (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_OCMPU_SHIFT)) & MSCM_OCMDR_OCMPU_MASK)
#define MSCM_OCMDR_OCMT_MASK (0xE000U)
#define MSCM_OCMDR_OCMT_SHIFT (13U)
/*! OCMT
 *  0b000..OCMEMn is a system RAM.
 *  0b001..OCMEMn is a graphics RAM.
 *  0b010..Reserved
 *  0b011..OCMEMn is a ROM.
 *  0b100..Reserved
 *  0b101..Reserved
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define MSCM_OCMDR_OCMT(x) (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_OCMT_SHIFT)) & MSCM_OCMDR_OCMT_MASK)
#define MSCM_OCMDR_RO_MASK (0x10000U)
#define MSCM_OCMDR_RO_SHIFT (16U)
/*! RO
 *  0b0..Writes to the OCMDRn[11:0] are allowed
 *  0b1..Writes to the OCMDRn[11:0] are ignored
 */
#define MSCM_OCMDR_RO(x) (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_RO_SHIFT)) & MSCM_OCMDR_RO_MASK)
#define MSCM_OCMDR_OCMW_MASK (0xE0000U)
#define MSCM_OCMDR_OCMW_SHIFT (17U)
/*! OCMW
 *  0b010..OCMEMn 32-bits wide
 *  0b011..OCMEMn 64-bits wide
 */
#define MSCM_OCMDR_OCMW(x) (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_OCMW_SHIFT)) & MSCM_OCMDR_OCMW_MASK)
#define MSCM_OCMDR_OCMSZ_MASK (0xF000000U)
#define MSCM_OCMDR_OCMSZ_SHIFT (24U)
/*! OCMSZ
 *  0b0000..no OCMEMn
 *  0b0100..4KB OCMEMn
 *  0b0101..8KB OCMEMn
 *  0b0110..16KB OCMEMn
 *  0b0111..32KB OCMEMn
 *  0b1111..8192KB OCMEMn
 */
#define MSCM_OCMDR_OCMSZ(x) (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_OCMSZ_SHIFT)) & MSCM_OCMDR_OCMSZ_MASK)
#define MSCM_OCMDR_OCMSZH_MASK (0x10000000U)
#define MSCM_OCMDR_OCMSZH_SHIFT (28U)
/*! OCMSZH
 *  0b0..OCMEMn is a power-of-2 capacity.
 *  0b1..OCMEMn is not a power-of-2, with a capacity is 0.75 * OCMSZ.
 */
#define MSCM_OCMDR_OCMSZH(x) (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_OCMSZH_SHIFT)) & MSCM_OCMDR_OCMSZH_MASK)
#define MSCM_OCMDR_V_MASK (0x80000000U)
#define MSCM_OCMDR_V_SHIFT (31U)
/*! V
 *  0b0..OCMEMn is not present.
 *  0b1..OCMEMn is present.
 */
#define MSCM_OCMDR_V(x) (((uint32_t)(((uint32_t)(x)) << MSCM_OCMDR_V_SHIFT)) & MSCM_OCMDR_V_MASK)
/*! @} */

/* The count of MSCM_OCMDR */
#define MSCM_OCMDR_COUNT (3U)

/*!
 * @}
 */ /* end of group MSCM_Register_Masks */

/* MSCM - Peripheral instance base addresses */
/** Peripheral MSCM base address */
#define MSCM_BASE (0x40001000u)
/** Peripheral MSCM base pointer */
#define MSCM ((MSCM_Type *)MSCM_BASE)
/** Array initializer of MSCM peripheral base addresses */
#define MSCM_BASE_ADDRS \
    {                   \
        MSCM_BASE       \
    }
/** Array initializer of MSCM peripheral base pointers */
#define MSCM_BASE_PTRS \
    {                  \
        MSCM           \
    }

/*!
 * @}
 */ /* end of group MSCM_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- MTB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_Peripheral_Access_Layer MTB Peripheral Access Layer
 * @{
 */

/** MTB - Register Layout Typedef */
typedef struct
{
    __IO uint32_t POSITION; /**< MTB Position Register, offset: 0x0 */
    __IO uint32_t MASTER;   /**< MTB Master Register, offset: 0x4 */
    __IO uint32_t FLOW;     /**< MTB Flow Register, offset: 0x8 */
    __I uint32_t BASE;      /**< MTB Base Register, offset: 0xC */
    uint8_t RESERVED_0[3824];
    __I uint32_t MODECTRL; /**< Integration Mode Control Register, offset: 0xF00 */
    uint8_t RESERVED_1[156];
    __I uint32_t TAGSET;   /**< Claim TAG Set Register, offset: 0xFA0 */
    __I uint32_t TAGCLEAR; /**< Claim TAG Clear Register, offset: 0xFA4 */
    uint8_t RESERVED_2[8];
    __I uint32_t LOCKACCESS; /**< Lock Access Register, offset: 0xFB0 */
    __I uint32_t LOCKSTAT;   /**< Lock Status Register, offset: 0xFB4 */
    __I uint32_t AUTHSTAT;   /**< Authentication Status Register, offset: 0xFB8 */
    __I uint32_t DEVICEARCH; /**< Device Architecture Register, offset: 0xFBC */
    uint8_t RESERVED_3[8];
    __I uint32_t DEVICECFG;   /**< Device Configuration Register, offset: 0xFC8 */
    __I uint32_t DEVICETYPID; /**< Device Type Identifier Register, offset: 0xFCC */
    __I uint32_t PERIPHID4;   /**< Peripheral ID Register, offset: 0xFD0 */
    __I uint32_t PERIPHID5;   /**< Peripheral ID Register, offset: 0xFD4 */
    __I uint32_t PERIPHID6;   /**< Peripheral ID Register, offset: 0xFD8 */
    __I uint32_t PERIPHID7;   /**< Peripheral ID Register, offset: 0xFDC */
    __I uint32_t PERIPHID0;   /**< Peripheral ID Register, offset: 0xFE0 */
    __I uint32_t PERIPHID1;   /**< Peripheral ID Register, offset: 0xFE4 */
    __I uint32_t PERIPHID2;   /**< Peripheral ID Register, offset: 0xFE8 */
    __I uint32_t PERIPHID3;   /**< Peripheral ID Register, offset: 0xFEC */
    __I uint32_t COMPID[4];   /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
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
#define MTB_POSITION_WRAP_MASK (0x4U)
#define MTB_POSITION_WRAP_SHIFT (2U)
/*! WRAP - WRAP
 */
#define MTB_POSITION_WRAP(x) (((uint32_t)(((uint32_t)(x)) << MTB_POSITION_WRAP_SHIFT)) & MTB_POSITION_WRAP_MASK)
#define MTB_POSITION_POINTER_MASK (0xFFFFFFF8U)
#define MTB_POSITION_POINTER_SHIFT (3U)
/*! POINTER - Trace Packet Address Pointer[28:0]
 */
#define MTB_POSITION_POINTER(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_POSITION_POINTER_SHIFT)) & MTB_POSITION_POINTER_MASK)
/*! @} */

/*! @name MASTER - MTB Master Register */
/*! @{ */
#define MTB_MASTER_MASK_MASK (0x1FU)
#define MTB_MASTER_MASK_SHIFT (0U)
/*! MASK - Mask
 */
#define MTB_MASTER_MASK(x) (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_MASK_SHIFT)) & MTB_MASTER_MASK_MASK)
#define MTB_MASTER_TSTARTEN_MASK (0x20U)
#define MTB_MASTER_TSTARTEN_SHIFT (5U)
/*! TSTARTEN - Trace Start Input Enable
 */
#define MTB_MASTER_TSTARTEN(x) (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_TSTARTEN_SHIFT)) & MTB_MASTER_TSTARTEN_MASK)
#define MTB_MASTER_TSTOPEN_MASK (0x40U)
#define MTB_MASTER_TSTOPEN_SHIFT (6U)
/*! TSTOPEN - Trace Stop Input Enable
 */
#define MTB_MASTER_TSTOPEN(x) (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_TSTOPEN_SHIFT)) & MTB_MASTER_TSTOPEN_MASK)
#define MTB_MASTER_SFRWPRIV_MASK (0x80U)
#define MTB_MASTER_SFRWPRIV_SHIFT (7U)
/*! SFRWPRIV - Special Function Register Write Privilege
 */
#define MTB_MASTER_SFRWPRIV(x) (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_SFRWPRIV_SHIFT)) & MTB_MASTER_SFRWPRIV_MASK)
#define MTB_MASTER_RAMPRIV_MASK (0x100U)
#define MTB_MASTER_RAMPRIV_SHIFT (8U)
/*! RAMPRIV - RAM Privilege
 */
#define MTB_MASTER_RAMPRIV(x) (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_RAMPRIV_SHIFT)) & MTB_MASTER_RAMPRIV_MASK)
#define MTB_MASTER_HALTREQ_MASK (0x200U)
#define MTB_MASTER_HALTREQ_SHIFT (9U)
/*! HALTREQ - Halt Request
 */
#define MTB_MASTER_HALTREQ(x) (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_HALTREQ_SHIFT)) & MTB_MASTER_HALTREQ_MASK)
#define MTB_MASTER_EN_MASK (0x80000000U)
#define MTB_MASTER_EN_SHIFT (31U)
/*! EN - Main Trace Enable
 */
#define MTB_MASTER_EN(x) (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_EN_SHIFT)) & MTB_MASTER_EN_MASK)
/*! @} */

/*! @name FLOW - MTB Flow Register */
/*! @{ */
#define MTB_FLOW_AUTOSTOP_MASK (0x1U)
#define MTB_FLOW_AUTOSTOP_SHIFT (0U)
/*! AUTOSTOP - AUTOSTOP
 */
#define MTB_FLOW_AUTOSTOP(x) (((uint32_t)(((uint32_t)(x)) << MTB_FLOW_AUTOSTOP_SHIFT)) & MTB_FLOW_AUTOSTOP_MASK)
#define MTB_FLOW_AUTOHALT_MASK (0x2U)
#define MTB_FLOW_AUTOHALT_SHIFT (1U)
/*! AUTOHALT - AUTOHALT
 */
#define MTB_FLOW_AUTOHALT(x) (((uint32_t)(((uint32_t)(x)) << MTB_FLOW_AUTOHALT_SHIFT)) & MTB_FLOW_AUTOHALT_MASK)
#define MTB_FLOW_WATERMARK_MASK (0xFFFFFFF8U)
#define MTB_FLOW_WATERMARK_SHIFT (3U)
/*! WATERMARK - WATERMARK[28:0]
 */
#define MTB_FLOW_WATERMARK(x) (((uint32_t)(((uint32_t)(x)) << MTB_FLOW_WATERMARK_SHIFT)) & MTB_FLOW_WATERMARK_MASK)
/*! @} */

/*! @name BASE - MTB Base Register */
/*! @{ */
#define MTB_BASE_BASEADDR_MASK (0xFFFFFFFFU)
#define MTB_BASE_BASEADDR_SHIFT (0U)
/*! BASEADDR - BASEADDR
 */
#define MTB_BASE_BASEADDR(x) (((uint32_t)(((uint32_t)(x)) << MTB_BASE_BASEADDR_SHIFT)) & MTB_BASE_BASEADDR_MASK)
/*! @} */

/*! @name MODECTRL - Integration Mode Control Register */
/*! @{ */
#define MTB_MODECTRL_MODECTRL_MASK (0xFFFFFFFFU)
#define MTB_MODECTRL_MODECTRL_SHIFT (0U)
/*! MODECTRL - MODECTRL
 */
#define MTB_MODECTRL_MODECTRL(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_MODECTRL_MODECTRL_SHIFT)) & MTB_MODECTRL_MODECTRL_MASK)
/*! @} */

/*! @name TAGSET - Claim TAG Set Register */
/*! @{ */
#define MTB_TAGSET_TAGSET_MASK (0xFFFFFFFFU)
#define MTB_TAGSET_TAGSET_SHIFT (0U)
/*! TAGSET - TAGSET
 */
#define MTB_TAGSET_TAGSET(x) (((uint32_t)(((uint32_t)(x)) << MTB_TAGSET_TAGSET_SHIFT)) & MTB_TAGSET_TAGSET_MASK)
/*! @} */

/*! @name TAGCLEAR - Claim TAG Clear Register */
/*! @{ */
#define MTB_TAGCLEAR_TAGCLEAR_MASK (0xFFFFFFFFU)
#define MTB_TAGCLEAR_TAGCLEAR_SHIFT (0U)
/*! TAGCLEAR - TAGCLEAR
 */
#define MTB_TAGCLEAR_TAGCLEAR(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_TAGCLEAR_TAGCLEAR_SHIFT)) & MTB_TAGCLEAR_TAGCLEAR_MASK)
/*! @} */

/*! @name LOCKACCESS - Lock Access Register */
/*! @{ */
#define MTB_LOCKACCESS_LOCKACCESS_MASK (0xFFFFFFFFU)
#define MTB_LOCKACCESS_LOCKACCESS_SHIFT (0U)
#define MTB_LOCKACCESS_LOCKACCESS(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_LOCKACCESS_LOCKACCESS_SHIFT)) & MTB_LOCKACCESS_LOCKACCESS_MASK)
/*! @} */

/*! @name LOCKSTAT - Lock Status Register */
/*! @{ */
#define MTB_LOCKSTAT_LOCKSTAT_MASK (0xFFFFFFFFU)
#define MTB_LOCKSTAT_LOCKSTAT_SHIFT (0U)
/*! LOCKSTAT - LOCKSTAT
 */
#define MTB_LOCKSTAT_LOCKSTAT(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_LOCKSTAT_LOCKSTAT_SHIFT)) & MTB_LOCKSTAT_LOCKSTAT_MASK)
/*! @} */

/*! @name AUTHSTAT - Authentication Status Register */
/*! @{ */
#define MTB_AUTHSTAT_BIT0_MASK (0x1U)
#define MTB_AUTHSTAT_BIT0_SHIFT (0U)
#define MTB_AUTHSTAT_BIT0(x) (((uint32_t)(((uint32_t)(x)) << MTB_AUTHSTAT_BIT0_SHIFT)) & MTB_AUTHSTAT_BIT0_MASK)
#define MTB_AUTHSTAT_BIT1_MASK (0x2U)
#define MTB_AUTHSTAT_BIT1_SHIFT (1U)
/*! BIT1 - BIT1
 */
#define MTB_AUTHSTAT_BIT1(x) (((uint32_t)(((uint32_t)(x)) << MTB_AUTHSTAT_BIT1_SHIFT)) & MTB_AUTHSTAT_BIT1_MASK)
#define MTB_AUTHSTAT_BIT2_MASK (0x4U)
#define MTB_AUTHSTAT_BIT2_SHIFT (2U)
/*! BIT2 - BIT2
 */
#define MTB_AUTHSTAT_BIT2(x) (((uint32_t)(((uint32_t)(x)) << MTB_AUTHSTAT_BIT2_SHIFT)) & MTB_AUTHSTAT_BIT2_MASK)
#define MTB_AUTHSTAT_BIT3_MASK (0x8U)
#define MTB_AUTHSTAT_BIT3_SHIFT (3U)
/*! BIT3 - BIT3
 */
#define MTB_AUTHSTAT_BIT3(x) (((uint32_t)(((uint32_t)(x)) << MTB_AUTHSTAT_BIT3_SHIFT)) & MTB_AUTHSTAT_BIT3_MASK)
/*! @} */

/*! @name DEVICEARCH - Device Architecture Register */
/*! @{ */
#define MTB_DEVICEARCH_DEVICEARCH_MASK (0xFFFFFFFFU)
#define MTB_DEVICEARCH_DEVICEARCH_SHIFT (0U)
/*! DEVICEARCH - DEVICEARCH
 */
#define MTB_DEVICEARCH_DEVICEARCH(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DEVICEARCH_DEVICEARCH_SHIFT)) & MTB_DEVICEARCH_DEVICEARCH_MASK)
/*! @} */

/*! @name DEVICECFG - Device Configuration Register */
/*! @{ */
#define MTB_DEVICECFG_DEVICECFG_MASK (0xFFFFFFFFU)
#define MTB_DEVICECFG_DEVICECFG_SHIFT (0U)
/*! DEVICECFG - DEVICECFG
 */
#define MTB_DEVICECFG_DEVICECFG(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DEVICECFG_DEVICECFG_SHIFT)) & MTB_DEVICECFG_DEVICECFG_MASK)
/*! @} */

/*! @name DEVICETYPID - Device Type Identifier Register */
/*! @{ */
#define MTB_DEVICETYPID_DEVICETYPID_MASK (0xFFFFFFFFU)
#define MTB_DEVICETYPID_DEVICETYPID_SHIFT (0U)
/*! DEVICETYPID - DEVICETYPID
 */
#define MTB_DEVICETYPID_DEVICETYPID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DEVICETYPID_DEVICETYPID_SHIFT)) & MTB_DEVICETYPID_DEVICETYPID_MASK)
/*! @} */

/*! @name PERIPHID4 - Peripheral ID Register */
/*! @{ */
#define MTB_PERIPHID4_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_PERIPHID4_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID4_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID4_PERIPHID_SHIFT)) & MTB_PERIPHID4_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID5 - Peripheral ID Register */
/*! @{ */
#define MTB_PERIPHID5_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_PERIPHID5_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID5_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID5_PERIPHID_SHIFT)) & MTB_PERIPHID5_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID6 - Peripheral ID Register */
/*! @{ */
#define MTB_PERIPHID6_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_PERIPHID6_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID6_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID6_PERIPHID_SHIFT)) & MTB_PERIPHID6_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID7 - Peripheral ID Register */
/*! @{ */
#define MTB_PERIPHID7_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_PERIPHID7_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID7_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID7_PERIPHID_SHIFT)) & MTB_PERIPHID7_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID0 - Peripheral ID Register */
/*! @{ */
#define MTB_PERIPHID0_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_PERIPHID0_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID0_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID0_PERIPHID_SHIFT)) & MTB_PERIPHID0_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID1 - Peripheral ID Register */
/*! @{ */
#define MTB_PERIPHID1_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_PERIPHID1_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID1_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID1_PERIPHID_SHIFT)) & MTB_PERIPHID1_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID2 - Peripheral ID Register */
/*! @{ */
#define MTB_PERIPHID2_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_PERIPHID2_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID2_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID2_PERIPHID_SHIFT)) & MTB_PERIPHID2_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID3 - Peripheral ID Register */
/*! @{ */
#define MTB_PERIPHID3_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_PERIPHID3_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID3_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID3_PERIPHID_SHIFT)) & MTB_PERIPHID3_PERIPHID_MASK)
/*! @} */

/*! @name COMPID - Component ID Register */
/*! @{ */
#define MTB_COMPID_COMPID_MASK (0xFFFFFFFFU)
#define MTB_COMPID_COMPID_SHIFT (0U)
/*! COMPID - Component ID
 */
#define MTB_COMPID_COMPID(x) (((uint32_t)(((uint32_t)(x)) << MTB_COMPID_COMPID_SHIFT)) & MTB_COMPID_COMPID_MASK)
/*! @} */

/* The count of MTB_COMPID */
#define MTB_COMPID_COUNT (4U)

/*!
 * @}
 */ /* end of group MTB_Register_Masks */

/* MTB - Peripheral instance base addresses */
/** Peripheral MTB0 base address */
#define MTB0_BASE (0xF0000000u)
/** Peripheral MTB0 base pointer */
#define MTB0 ((MTB_Type *)MTB0_BASE)
/** Array initializer of MTB peripheral base addresses */
#define MTB_BASE_ADDRS \
    {                  \
        MTB0_BASE      \
    }
/** Array initializer of MTB peripheral base pointers */
#define MTB_BASE_PTRS \
    {                 \
        MTB0          \
    }

/*!
 * @}
 */ /* end of group MTB_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- MTB_DWT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_DWT_Peripheral_Access_Layer MTB_DWT Peripheral Access Layer
 * @{
 */

/** MTB_DWT - Register Layout Typedef */
typedef struct
{
    __I uint32_t CTRL; /**< MTB DWT Control Register, offset: 0x0 */
    uint8_t RESERVED_0[28];
    struct
    {                       /* offset: 0x20, array step: 0x10 */
        __IO uint32_t COMP; /**< MTB_DWT Comparator Register, array offset: 0x20, array step: 0x10 */
        __IO uint32_t MASK; /**< MTB_DWT Comparator Mask Register, array offset: 0x24, array step: 0x10 */
        __IO uint32_t FCT;  /**< MTB_DWT Comparator Function Register 0..MTB_DWT Comparator Function Register 1, array
                               offset: 0x28, array step: 0x10 */
        uint8_t RESERVED_0[4];
    } COMPARATOR[2];
    uint8_t RESERVED_1[448];
    __IO uint32_t TBCTRL; /**< MTB_DWT Trace Buffer Control Register, offset: 0x200 */
    uint8_t RESERVED_2[3524];
    __I uint32_t DEVICECFG;   /**< Device Configuration Register, offset: 0xFC8 */
    __I uint32_t DEVICETYPID; /**< Device Type Identifier Register, offset: 0xFCC */
    __I uint32_t PERIPHID4;   /**< Peripheral ID Register, offset: 0xFD0 */
    __I uint32_t PERIPHID5;   /**< Peripheral ID Register, offset: 0xFD4 */
    __I uint32_t PERIPHID6;   /**< Peripheral ID Register, offset: 0xFD8 */
    __I uint32_t PERIPHID7;   /**< Peripheral ID Register, offset: 0xFDC */
    __I uint32_t PERIPHID0;   /**< Peripheral ID Register, offset: 0xFE0 */
    __I uint32_t PERIPHID1;   /**< Peripheral ID Register, offset: 0xFE4 */
    __I uint32_t PERIPHID2;   /**< Peripheral ID Register, offset: 0xFE8 */
    __I uint32_t PERIPHID3;   /**< Peripheral ID Register, offset: 0xFEC */
    __I uint32_t COMPID[4];   /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} MTB_DWT_Type;

/* ----------------------------------------------------------------------------
   -- MTB_DWT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_DWT_Register_Masks MTB_DWT Register Masks
 * @{
 */

/*! @name CTRL - MTB DWT Control Register */
/*! @{ */
#define MTB_DWT_CTRL_DWTCFGCTRL_MASK (0xFFFFFFFU)
#define MTB_DWT_CTRL_DWTCFGCTRL_SHIFT (0U)
/*! DWTCFGCTRL - DWT configuration controls
 */
#define MTB_DWT_CTRL_DWTCFGCTRL(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_CTRL_DWTCFGCTRL_SHIFT)) & MTB_DWT_CTRL_DWTCFGCTRL_MASK)
#define MTB_DWT_CTRL_NUMCMP_MASK (0xF0000000U)
#define MTB_DWT_CTRL_NUMCMP_SHIFT (28U)
/*! NUMCMP - Number of comparators
 */
#define MTB_DWT_CTRL_NUMCMP(x) (((uint32_t)(((uint32_t)(x)) << MTB_DWT_CTRL_NUMCMP_SHIFT)) & MTB_DWT_CTRL_NUMCMP_MASK)
/*! @} */

/*! @name COMP - MTB_DWT Comparator Register */
/*! @{ */
#define MTB_DWT_COMP_COMP_MASK (0xFFFFFFFFU)
#define MTB_DWT_COMP_COMP_SHIFT (0U)
/*! COMP - Reference value for comparison
 */
#define MTB_DWT_COMP_COMP(x) (((uint32_t)(((uint32_t)(x)) << MTB_DWT_COMP_COMP_SHIFT)) & MTB_DWT_COMP_COMP_MASK)
/*! @} */

/* The count of MTB_DWT_COMP */
#define MTB_DWT_COMP_COUNT (2U)

/*! @name MASK - MTB_DWT Comparator Mask Register */
/*! @{ */
#define MTB_DWT_MASK_MASK_MASK (0x1FU)
#define MTB_DWT_MASK_MASK_SHIFT (0U)
/*! MASK - MASK
 */
#define MTB_DWT_MASK_MASK(x) (((uint32_t)(((uint32_t)(x)) << MTB_DWT_MASK_MASK_SHIFT)) & MTB_DWT_MASK_MASK_MASK)
/*! @} */

/* The count of MTB_DWT_MASK */
#define MTB_DWT_MASK_COUNT (2U)

/*! @name FCT - MTB_DWT Comparator Function Register 0..MTB_DWT Comparator Function Register 1 */
/*! @{ */
#define MTB_DWT_FCT_FUNCTION_MASK (0xFU)
#define MTB_DWT_FCT_FUNCTION_SHIFT (0U)
/*! FUNCTION - Function
 *  0b0000..Disabled.
 *  0b0100..Instruction fetch.
 *  0b0101..Data operand read.
 *  0b0110..Data operand write.
 *  0b0111..Data operand (read + write).
 */
#define MTB_DWT_FCT_FUNCTION(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_FCT_FUNCTION_SHIFT)) & MTB_DWT_FCT_FUNCTION_MASK)
#define MTB_DWT_FCT_DATAVMATCH_MASK (0x100U)
#define MTB_DWT_FCT_DATAVMATCH_SHIFT (8U)
/*! DATAVMATCH - Data Value Match
 *  0b0..Perform address comparison.
 *  0b1..Perform data value comparison.
 */
#define MTB_DWT_FCT_DATAVMATCH(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_FCT_DATAVMATCH_SHIFT)) & MTB_DWT_FCT_DATAVMATCH_MASK)
#define MTB_DWT_FCT_DATAVSIZE_MASK (0xC00U)
#define MTB_DWT_FCT_DATAVSIZE_SHIFT (10U)
/*! DATAVSIZE - Data Value Size
 *  0b00..Byte.
 *  0b01..Halfword.
 *  0b10..Word.
 *  0b11..Reserved. Any attempts to use this value results in UNPREDICTABLE behavior.
 */
#define MTB_DWT_FCT_DATAVSIZE(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_FCT_DATAVSIZE_SHIFT)) & MTB_DWT_FCT_DATAVSIZE_MASK)
#define MTB_DWT_FCT_DATAVADDR0_MASK (0xF000U)
#define MTB_DWT_FCT_DATAVADDR0_SHIFT (12U)
/*! DATAVADDR0 - Data Value Address 0
 */
#define MTB_DWT_FCT_DATAVADDR0(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_FCT_DATAVADDR0_SHIFT)) & MTB_DWT_FCT_DATAVADDR0_MASK)
#define MTB_DWT_FCT_MATCHED_MASK (0x1000000U)
#define MTB_DWT_FCT_MATCHED_SHIFT (24U)
/*! MATCHED - Comparator match
 *  0b0..No match.
 *  0b1..Match occurred.
 */
#define MTB_DWT_FCT_MATCHED(x) (((uint32_t)(((uint32_t)(x)) << MTB_DWT_FCT_MATCHED_SHIFT)) & MTB_DWT_FCT_MATCHED_MASK)
/*! @} */

/* The count of MTB_DWT_FCT */
#define MTB_DWT_FCT_COUNT (2U)

/*! @name TBCTRL - MTB_DWT Trace Buffer Control Register */
/*! @{ */
#define MTB_DWT_TBCTRL_ACOMP0_MASK (0x1U)
#define MTB_DWT_TBCTRL_ACOMP0_SHIFT (0U)
/*! ACOMP0 - Action based on Comparator 0 match
 *  0b0..Trigger TSTOP based on the assertion of MTBDWT_FCT0[MATCHED].
 *  0b1..Trigger TSTART based on the assertion of MTBDWT_FCT0[MATCHED].
 */
#define MTB_DWT_TBCTRL_ACOMP0(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_TBCTRL_ACOMP0_SHIFT)) & MTB_DWT_TBCTRL_ACOMP0_MASK)
#define MTB_DWT_TBCTRL_ACOMP1_MASK (0x2U)
#define MTB_DWT_TBCTRL_ACOMP1_SHIFT (1U)
/*! ACOMP1 - Action based on Comparator 1 match
 *  0b0..Trigger TSTOP based on the assertion of MTBDWT_FCT1[MATCHED].
 *  0b1..Trigger TSTART based on the assertion of MTBDWT_FCT1[MATCHED].
 */
#define MTB_DWT_TBCTRL_ACOMP1(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_TBCTRL_ACOMP1_SHIFT)) & MTB_DWT_TBCTRL_ACOMP1_MASK)
#define MTB_DWT_TBCTRL_NUMCOMP_MASK (0xF0000000U)
#define MTB_DWT_TBCTRL_NUMCOMP_SHIFT (28U)
/*! NUMCOMP - Number of Comparators
 */
#define MTB_DWT_TBCTRL_NUMCOMP(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_TBCTRL_NUMCOMP_SHIFT)) & MTB_DWT_TBCTRL_NUMCOMP_MASK)
/*! @} */

/*! @name DEVICECFG - Device Configuration Register */
/*! @{ */
#define MTB_DWT_DEVICECFG_DEVICECFG_MASK (0xFFFFFFFFU)
#define MTB_DWT_DEVICECFG_DEVICECFG_SHIFT (0U)
/*! DEVICECFG - DEVICECFG
 */
#define MTB_DWT_DEVICECFG_DEVICECFG(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_DEVICECFG_DEVICECFG_SHIFT)) & MTB_DWT_DEVICECFG_DEVICECFG_MASK)
/*! @} */

/*! @name DEVICETYPID - Device Type Identifier Register */
/*! @{ */
#define MTB_DWT_DEVICETYPID_DEVICETYPID_MASK (0xFFFFFFFFU)
#define MTB_DWT_DEVICETYPID_DEVICETYPID_SHIFT (0U)
/*! DEVICETYPID - DEVICETYPID
 */
#define MTB_DWT_DEVICETYPID_DEVICETYPID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_DEVICETYPID_DEVICETYPID_SHIFT)) & MTB_DWT_DEVICETYPID_DEVICETYPID_MASK)
/*! @} */

/*! @name PERIPHID4 - Peripheral ID Register */
/*! @{ */
#define MTB_DWT_PERIPHID4_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_DWT_PERIPHID4_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_DWT_PERIPHID4_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_PERIPHID4_PERIPHID_SHIFT)) & MTB_DWT_PERIPHID4_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID5 - Peripheral ID Register */
/*! @{ */
#define MTB_DWT_PERIPHID5_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_DWT_PERIPHID5_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_DWT_PERIPHID5_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_PERIPHID5_PERIPHID_SHIFT)) & MTB_DWT_PERIPHID5_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID6 - Peripheral ID Register */
/*! @{ */
#define MTB_DWT_PERIPHID6_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_DWT_PERIPHID6_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_DWT_PERIPHID6_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_PERIPHID6_PERIPHID_SHIFT)) & MTB_DWT_PERIPHID6_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID7 - Peripheral ID Register */
/*! @{ */
#define MTB_DWT_PERIPHID7_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_DWT_PERIPHID7_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_DWT_PERIPHID7_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_PERIPHID7_PERIPHID_SHIFT)) & MTB_DWT_PERIPHID7_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID0 - Peripheral ID Register */
/*! @{ */
#define MTB_DWT_PERIPHID0_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_DWT_PERIPHID0_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_DWT_PERIPHID0_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_PERIPHID0_PERIPHID_SHIFT)) & MTB_DWT_PERIPHID0_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID1 - Peripheral ID Register */
/*! @{ */
#define MTB_DWT_PERIPHID1_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_DWT_PERIPHID1_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_DWT_PERIPHID1_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_PERIPHID1_PERIPHID_SHIFT)) & MTB_DWT_PERIPHID1_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID2 - Peripheral ID Register */
/*! @{ */
#define MTB_DWT_PERIPHID2_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_DWT_PERIPHID2_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_DWT_PERIPHID2_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_PERIPHID2_PERIPHID_SHIFT)) & MTB_DWT_PERIPHID2_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID3 - Peripheral ID Register */
/*! @{ */
#define MTB_DWT_PERIPHID3_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_DWT_PERIPHID3_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_DWT_PERIPHID3_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_PERIPHID3_PERIPHID_SHIFT)) & MTB_DWT_PERIPHID3_PERIPHID_MASK)
/*! @} */

/*! @name COMPID - Component ID Register */
/*! @{ */
#define MTB_DWT_COMPID_COMPID_MASK (0xFFFFFFFFU)
#define MTB_DWT_COMPID_COMPID_SHIFT (0U)
/*! COMPID - Component ID
 */
#define MTB_DWT_COMPID_COMPID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_DWT_COMPID_COMPID_SHIFT)) & MTB_DWT_COMPID_COMPID_MASK)
/*! @} */

/* The count of MTB_DWT_COMPID */
#define MTB_DWT_COMPID_COUNT (4U)

/*!
 * @}
 */ /* end of group MTB_DWT_Register_Masks */

/* MTB_DWT - Peripheral instance base addresses */
/** Peripheral MTB0_DWT base address */
#define MTB0_DWT_BASE (0xF0001000u)
/** Peripheral MTB0_DWT base pointer */
#define MTB0_DWT ((MTB_DWT_Type *)MTB0_DWT_BASE)
/** Array initializer of MTB_DWT peripheral base addresses */
#define MTB_DWT_BASE_ADDRS \
    {                      \
        MTB0_DWT_BASE      \
    }
/** Array initializer of MTB_DWT peripheral base pointers */
#define MTB_DWT_BASE_PTRS \
    {                     \
        MTB0_DWT          \
    }

/*!
 * @}
 */ /* end of group MTB_DWT_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- MTB_ROM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_ROM_Peripheral_Access_Layer MTB_ROM Peripheral Access Layer
 * @{
 */

/** MTB_ROM - Register Layout Typedef */
typedef struct
{
    __I uint32_t ENTRY[4];  /**< Entry, array offset: 0x0, array step: 0x4 */
    __I uint32_t TABLEMARK; /**< End of Table Marker Register, offset: 0x10 */
    uint8_t RESERVED_0[4024];
    __I uint32_t SYSACCESS; /**< System Access Register, offset: 0xFCC */
    __I uint32_t PERIPHID4; /**< Peripheral ID Register, offset: 0xFD0 */
    __I uint32_t PERIPHID5; /**< Peripheral ID Register, offset: 0xFD4 */
    __I uint32_t PERIPHID6; /**< Peripheral ID Register, offset: 0xFD8 */
    __I uint32_t PERIPHID7; /**< Peripheral ID Register, offset: 0xFDC */
    __I uint32_t PERIPHID0; /**< Peripheral ID Register, offset: 0xFE0 */
    __I uint32_t PERIPHID1; /**< Peripheral ID Register, offset: 0xFE4 */
    __I uint32_t PERIPHID2; /**< Peripheral ID Register, offset: 0xFE8 */
    __I uint32_t PERIPHID3; /**< Peripheral ID Register, offset: 0xFEC */
    __I uint32_t COMPID[4]; /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} MTB_ROM_Type;

/* ----------------------------------------------------------------------------
   -- MTB_ROM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_ROM_Register_Masks MTB_ROM Register Masks
 * @{
 */

/*! @name ENTRY - Entry */
/*! @{ */
#define MTB_ROM_ENTRY_ENTRY_MASK (0xFFFFFFFFU)
#define MTB_ROM_ENTRY_ENTRY_SHIFT (0U)
/*! ENTRY - ENTRY
 */
#define MTB_ROM_ENTRY_ENTRY(x) (((uint32_t)(((uint32_t)(x)) << MTB_ROM_ENTRY_ENTRY_SHIFT)) & MTB_ROM_ENTRY_ENTRY_MASK)
/*! @} */

/* The count of MTB_ROM_ENTRY */
#define MTB_ROM_ENTRY_COUNT (4U)

/*! @name TABLEMARK - End of Table Marker Register */
/*! @{ */
#define MTB_ROM_TABLEMARK_MARK_MASK (0xFFFFFFFFU)
#define MTB_ROM_TABLEMARK_MARK_SHIFT (0U)
/*! MARK - MARK
 */
#define MTB_ROM_TABLEMARK_MARK(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_ROM_TABLEMARK_MARK_SHIFT)) & MTB_ROM_TABLEMARK_MARK_MASK)
/*! @} */

/*! @name SYSACCESS - System Access Register */
/*! @{ */
#define MTB_ROM_SYSACCESS_SYSACCESS_MASK (0xFFFFFFFFU)
#define MTB_ROM_SYSACCESS_SYSACCESS_SHIFT (0U)
/*! SYSACCESS - SYSACCESS
 */
#define MTB_ROM_SYSACCESS_SYSACCESS(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_ROM_SYSACCESS_SYSACCESS_SHIFT)) & MTB_ROM_SYSACCESS_SYSACCESS_MASK)
/*! @} */

/*! @name PERIPHID4 - Peripheral ID Register */
/*! @{ */
#define MTB_ROM_PERIPHID4_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_ROM_PERIPHID4_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_ROM_PERIPHID4_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_ROM_PERIPHID4_PERIPHID_SHIFT)) & MTB_ROM_PERIPHID4_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID5 - Peripheral ID Register */
/*! @{ */
#define MTB_ROM_PERIPHID5_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_ROM_PERIPHID5_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_ROM_PERIPHID5_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_ROM_PERIPHID5_PERIPHID_SHIFT)) & MTB_ROM_PERIPHID5_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID6 - Peripheral ID Register */
/*! @{ */
#define MTB_ROM_PERIPHID6_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_ROM_PERIPHID6_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_ROM_PERIPHID6_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_ROM_PERIPHID6_PERIPHID_SHIFT)) & MTB_ROM_PERIPHID6_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID7 - Peripheral ID Register */
/*! @{ */
#define MTB_ROM_PERIPHID7_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_ROM_PERIPHID7_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_ROM_PERIPHID7_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_ROM_PERIPHID7_PERIPHID_SHIFT)) & MTB_ROM_PERIPHID7_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID0 - Peripheral ID Register */
/*! @{ */
#define MTB_ROM_PERIPHID0_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_ROM_PERIPHID0_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_ROM_PERIPHID0_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_ROM_PERIPHID0_PERIPHID_SHIFT)) & MTB_ROM_PERIPHID0_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID1 - Peripheral ID Register */
/*! @{ */
#define MTB_ROM_PERIPHID1_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_ROM_PERIPHID1_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_ROM_PERIPHID1_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_ROM_PERIPHID1_PERIPHID_SHIFT)) & MTB_ROM_PERIPHID1_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID2 - Peripheral ID Register */
/*! @{ */
#define MTB_ROM_PERIPHID2_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_ROM_PERIPHID2_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_ROM_PERIPHID2_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_ROM_PERIPHID2_PERIPHID_SHIFT)) & MTB_ROM_PERIPHID2_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID3 - Peripheral ID Register */
/*! @{ */
#define MTB_ROM_PERIPHID3_PERIPHID_MASK (0xFFFFFFFFU)
#define MTB_ROM_PERIPHID3_PERIPHID_SHIFT (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_ROM_PERIPHID3_PERIPHID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_ROM_PERIPHID3_PERIPHID_SHIFT)) & MTB_ROM_PERIPHID3_PERIPHID_MASK)
/*! @} */

/*! @name COMPID - Component ID Register */
/*! @{ */
#define MTB_ROM_COMPID_COMPID_MASK (0xFFFFFFFFU)
#define MTB_ROM_COMPID_COMPID_SHIFT (0U)
/*! COMPID - Component ID
 */
#define MTB_ROM_COMPID_COMPID(x) \
    (((uint32_t)(((uint32_t)(x)) << MTB_ROM_COMPID_COMPID_SHIFT)) & MTB_ROM_COMPID_COMPID_MASK)
/*! @} */

/* The count of MTB_ROM_COMPID */
#define MTB_ROM_COMPID_COUNT (4U)

/*!
 * @}
 */ /* end of group MTB_ROM_Register_Masks */

/* MTB_ROM - Peripheral instance base addresses */
/** Peripheral MTB0_ROM base address */
#define MTB0_ROM_BASE (0xF0002000u)
/** Peripheral MTB0_ROM base pointer */
#define MTB0_ROM ((MTB_ROM_Type *)MTB0_ROM_BASE)
/** Array initializer of MTB_ROM peripheral base addresses */
#define MTB_ROM_BASE_ADDRS \
    {                      \
        MTB0_ROM_BASE      \
    }
/** Array initializer of MTB_ROM peripheral base pointers */
#define MTB_ROM_BASE_PTRS \
    {                     \
        MTB0_ROM          \
    }

/*!
 * @}
 */ /* end of group MTB_ROM_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- NV Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Peripheral_Access_Layer NV Peripheral Access Layer
 * @{
 */

/** NV - Register Layout Typedef */
typedef struct
{
    __I uint8_t BACKKEY3; /**< Backdoor Comparison Key 3., offset: 0x0 */
    __I uint8_t BACKKEY2; /**< Backdoor Comparison Key 2., offset: 0x1 */
    __I uint8_t BACKKEY1; /**< Backdoor Comparison Key 1., offset: 0x2 */
    __I uint8_t BACKKEY0; /**< Backdoor Comparison Key 0., offset: 0x3 */
    __I uint8_t BACKKEY7; /**< Backdoor Comparison Key 7., offset: 0x4 */
    __I uint8_t BACKKEY6; /**< Backdoor Comparison Key 6., offset: 0x5 */
    __I uint8_t BACKKEY5; /**< Backdoor Comparison Key 5., offset: 0x6 */
    __I uint8_t BACKKEY4; /**< Backdoor Comparison Key 4., offset: 0x7 */
    __I uint8_t FPROT3;   /**< Non-volatile P-Flash Protection 1 - Low Register, offset: 0x8 */
    __I uint8_t FPROT2;   /**< Non-volatile P-Flash Protection 1 - High Register, offset: 0x9 */
    __I uint8_t FPROT1;   /**< Non-volatile P-Flash Protection 0 - Low Register, offset: 0xA */
    __I uint8_t FPROT0;   /**< Non-volatile P-Flash Protection 0 - High Register, offset: 0xB */
    __I uint8_t FSEC;     /**< Non-volatile Flash Security Register, offset: 0xC */
    __I uint8_t FOPT;     /**< Non-volatile Flash Option Register, offset: 0xD */
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
#define NV_BACKKEY3_KEY_MASK (0xFFU)
#define NV_BACKKEY3_KEY_SHIFT (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY3_KEY(x) (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY3_KEY_SHIFT)) & NV_BACKKEY3_KEY_MASK)
/*! @} */

/*! @name BACKKEY2 - Backdoor Comparison Key 2. */
/*! @{ */
#define NV_BACKKEY2_KEY_MASK (0xFFU)
#define NV_BACKKEY2_KEY_SHIFT (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY2_KEY(x) (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY2_KEY_SHIFT)) & NV_BACKKEY2_KEY_MASK)
/*! @} */

/*! @name BACKKEY1 - Backdoor Comparison Key 1. */
/*! @{ */
#define NV_BACKKEY1_KEY_MASK (0xFFU)
#define NV_BACKKEY1_KEY_SHIFT (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY1_KEY(x) (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY1_KEY_SHIFT)) & NV_BACKKEY1_KEY_MASK)
/*! @} */

/*! @name BACKKEY0 - Backdoor Comparison Key 0. */
/*! @{ */
#define NV_BACKKEY0_KEY_MASK (0xFFU)
#define NV_BACKKEY0_KEY_SHIFT (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY0_KEY(x) (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY0_KEY_SHIFT)) & NV_BACKKEY0_KEY_MASK)
/*! @} */

/*! @name BACKKEY7 - Backdoor Comparison Key 7. */
/*! @{ */
#define NV_BACKKEY7_KEY_MASK (0xFFU)
#define NV_BACKKEY7_KEY_SHIFT (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY7_KEY(x) (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY7_KEY_SHIFT)) & NV_BACKKEY7_KEY_MASK)
/*! @} */

/*! @name BACKKEY6 - Backdoor Comparison Key 6. */
/*! @{ */
#define NV_BACKKEY6_KEY_MASK (0xFFU)
#define NV_BACKKEY6_KEY_SHIFT (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY6_KEY(x) (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY6_KEY_SHIFT)) & NV_BACKKEY6_KEY_MASK)
/*! @} */

/*! @name BACKKEY5 - Backdoor Comparison Key 5. */
/*! @{ */
#define NV_BACKKEY5_KEY_MASK (0xFFU)
#define NV_BACKKEY5_KEY_SHIFT (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY5_KEY(x) (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY5_KEY_SHIFT)) & NV_BACKKEY5_KEY_MASK)
/*! @} */

/*! @name BACKKEY4 - Backdoor Comparison Key 4. */
/*! @{ */
#define NV_BACKKEY4_KEY_MASK (0xFFU)
#define NV_BACKKEY4_KEY_SHIFT (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY4_KEY(x) (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY4_KEY_SHIFT)) & NV_BACKKEY4_KEY_MASK)
/*! @} */

/*! @name FPROT3 - Non-volatile P-Flash Protection 1 - Low Register */
/*! @{ */
#define NV_FPROT3_PROT_MASK (0xFFU)
#define NV_FPROT3_PROT_SHIFT (0U)
/*! PROT - P-Flash Region Protect
 */
#define NV_FPROT3_PROT(x) (((uint8_t)(((uint8_t)(x)) << NV_FPROT3_PROT_SHIFT)) & NV_FPROT3_PROT_MASK)
/*! @} */

/*! @name FPROT2 - Non-volatile P-Flash Protection 1 - High Register */
/*! @{ */
#define NV_FPROT2_PROT_MASK (0xFFU)
#define NV_FPROT2_PROT_SHIFT (0U)
/*! PROT - P-Flash Region Protect
 */
#define NV_FPROT2_PROT(x) (((uint8_t)(((uint8_t)(x)) << NV_FPROT2_PROT_SHIFT)) & NV_FPROT2_PROT_MASK)
/*! @} */

/*! @name FPROT1 - Non-volatile P-Flash Protection 0 - Low Register */
/*! @{ */
#define NV_FPROT1_PROT_MASK (0xFFU)
#define NV_FPROT1_PROT_SHIFT (0U)
/*! PROT - P-Flash Region Protect
 */
#define NV_FPROT1_PROT(x) (((uint8_t)(((uint8_t)(x)) << NV_FPROT1_PROT_SHIFT)) & NV_FPROT1_PROT_MASK)
/*! @} */

/*! @name FPROT0 - Non-volatile P-Flash Protection 0 - High Register */
/*! @{ */
#define NV_FPROT0_PROT_MASK (0xFFU)
#define NV_FPROT0_PROT_SHIFT (0U)
/*! PROT - P-Flash Region Protect
 */
#define NV_FPROT0_PROT(x) (((uint8_t)(((uint8_t)(x)) << NV_FPROT0_PROT_SHIFT)) & NV_FPROT0_PROT_MASK)
/*! @} */

/*! @name FSEC - Non-volatile Flash Security Register */
/*! @{ */
#define NV_FSEC_SEC_MASK (0x3U)
#define NV_FSEC_SEC_SHIFT (0U)
/*! SEC - Flash Security
 *  0b10..MCU security status is unsecure
 *  0b11..MCU security status is secure
 */
#define NV_FSEC_SEC(x) (((uint8_t)(((uint8_t)(x)) << NV_FSEC_SEC_SHIFT)) & NV_FSEC_SEC_MASK)
#define NV_FSEC_FSLACC_MASK (0xCU)
#define NV_FSEC_FSLACC_SHIFT (2U)
/*! FSLACC - Freescale Failure Analysis Access Code
 *  0b10..Freescale factory access denied
 *  0b11..Freescale factory access granted
 */
#define NV_FSEC_FSLACC(x) (((uint8_t)(((uint8_t)(x)) << NV_FSEC_FSLACC_SHIFT)) & NV_FSEC_FSLACC_MASK)
#define NV_FSEC_MEEN_MASK (0x30U)
#define NV_FSEC_MEEN_SHIFT (4U)
/*! MEEN
 *  0b10..Mass erase is disabled
 *  0b11..Mass erase is enabled
 */
#define NV_FSEC_MEEN(x) (((uint8_t)(((uint8_t)(x)) << NV_FSEC_MEEN_SHIFT)) & NV_FSEC_MEEN_MASK)
#define NV_FSEC_KEYEN_MASK (0xC0U)
#define NV_FSEC_KEYEN_SHIFT (6U)
/*! KEYEN - Backdoor Key Security Enable
 *  0b10..Backdoor key access enabled
 *  0b11..Backdoor key access disabled
 */
#define NV_FSEC_KEYEN(x) (((uint8_t)(((uint8_t)(x)) << NV_FSEC_KEYEN_SHIFT)) & NV_FSEC_KEYEN_MASK)
/*! @} */

/*! @name FOPT - Non-volatile Flash Option Register */
/*! @{ */
#define NV_FOPT_LPBOOT0_MASK (0x1U)
#define NV_FOPT_LPBOOT0_SHIFT (0U)
/*! LPBOOT0
 *  0b0..Core and system clock divider (OUTDIV1) is 0x7 (divide by 8) when LPBOOT1=0 or 0x1 (divide by 2) when
 * LPBOOT1=1. 0b1..Core and system clock divider (OUTDIV1) is 0x3 (divide by 4) when LPBOOT1=0 or 0x0 (divide by 1) when
 * LPBOOT1=1.
 */
#define NV_FOPT_LPBOOT0(x) (((uint8_t)(((uint8_t)(x)) << NV_FOPT_LPBOOT0_SHIFT)) & NV_FOPT_LPBOOT0_MASK)
#define NV_FOPT_BOOTPIN_OPT_MASK (0x2U)
#define NV_FOPT_BOOTPIN_OPT_SHIFT (1U)
/*! BOOTPIN_OPT
 *  0b0..Force Boot from ROM if BOOTCFG0 asserted, where BOOTCFG0 is the boot config function which is muxed with NMI
 * pin 0b1..Boot source configured by FOPT (BOOTSRC_SEL) bits
 */
#define NV_FOPT_BOOTPIN_OPT(x) (((uint8_t)(((uint8_t)(x)) << NV_FOPT_BOOTPIN_OPT_SHIFT)) & NV_FOPT_BOOTPIN_OPT_MASK)
#define NV_FOPT_NMI_DIS_MASK (0x4U)
#define NV_FOPT_NMI_DIS_SHIFT (2U)
/*! NMI_DIS
 *  0b0..NMI interrupts are always blocked
 *  0b1..NMI_b pin/interrupts reset default to enabled
 */
#define NV_FOPT_NMI_DIS(x) (((uint8_t)(((uint8_t)(x)) << NV_FOPT_NMI_DIS_SHIFT)) & NV_FOPT_NMI_DIS_MASK)
#define NV_FOPT_RESET_PIN_CFG_MASK (0x8U)
#define NV_FOPT_RESET_PIN_CFG_SHIFT (3U)
/*! RESET_PIN_CFG
 *  0b0..RESET pin is disabled following a POR and cannot be enabled as reset function
 *  0b1..RESET_b pin is dedicated
 */
#define NV_FOPT_RESET_PIN_CFG(x) \
    (((uint8_t)(((uint8_t)(x)) << NV_FOPT_RESET_PIN_CFG_SHIFT)) & NV_FOPT_RESET_PIN_CFG_MASK)
#define NV_FOPT_LPBOOT1_MASK (0x10U)
#define NV_FOPT_LPBOOT1_SHIFT (4U)
/*! LPBOOT1
 *  0b0..Core and system clock divider (OUTDIV1) is 0x7 (divide by 8) when LPBOOT0=0 or 0x3 (divide by 4) when
 * LPBOOT0=1. 0b1..Core and system clock divider (OUTDIV1) is 0x1 (divide by 2) when LPBOOT0=0 or 0x0 (divide by 1) when
 * LPBOOT0=1.
 */
#define NV_FOPT_LPBOOT1(x) (((uint8_t)(((uint8_t)(x)) << NV_FOPT_LPBOOT1_SHIFT)) & NV_FOPT_LPBOOT1_MASK)
#define NV_FOPT_FAST_INIT_MASK (0x20U)
#define NV_FOPT_FAST_INIT_SHIFT (5U)
/*! FAST_INIT
 *  0b0..Slower initialization
 *  0b1..Fast Initialization
 */
#define NV_FOPT_FAST_INIT(x) (((uint8_t)(((uint8_t)(x)) << NV_FOPT_FAST_INIT_SHIFT)) & NV_FOPT_FAST_INIT_MASK)
#define NV_FOPT_BOOTSRC_SEL_MASK (0xC0U)
#define NV_FOPT_BOOTSRC_SEL_SHIFT (6U)
/*! BOOTSRC_SEL - Boot source selection
 *  0b00..Boot from Flash
 *  0b10..Boot from ROM
 *  0b11..Boot from ROM
 */
#define NV_FOPT_BOOTSRC_SEL(x) (((uint8_t)(((uint8_t)(x)) << NV_FOPT_BOOTSRC_SEL_SHIFT)) & NV_FOPT_BOOTSRC_SEL_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group NV_Register_Masks */

/* NV - Peripheral instance base addresses */
/** Peripheral FTFA_FlashConfig base address */
#define FTFA_FlashConfig_BASE (0x400u)
/** Peripheral FTFA_FlashConfig base pointer */
#define FTFA_FlashConfig ((NV_Type *)FTFA_FlashConfig_BASE)
/** Array initializer of NV peripheral base addresses */
#define NV_BASE_ADDRS         \
    {                         \
        FTFA_FlashConfig_BASE \
    }
/** Array initializer of NV peripheral base pointers */
#define NV_BASE_PTRS     \
    {                    \
        FTFA_FlashConfig \
    }

/*!
 * @}
 */ /* end of group NV_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- PCC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PCC_Peripheral_Access_Layer PCC Peripheral Access Layer
 * @{
 */

/** PCC - Register Layout Typedef */
typedef struct
{
    __IO uint32_t CLKCFG[121]; /**< PCC CLKCFG Register, array offset: 0x0, array step: 0x4 */
} PCC_Type;

/* ----------------------------------------------------------------------------
   -- PCC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PCC_Register_Masks PCC Register Masks
 * @{
 */

/*! @name CLKCFG - PCC CLKCFG Register */
/*! @{ */
#define PCC_CLKCFG_PCD_MASK (0x7U)
#define PCC_CLKCFG_PCD_SHIFT (0U)
/*! PCD - Peripheral Clock Divider Select
 *  0b000..Divide by 1 (pass-through, no clock divide).
 *  0b001..Divide by 2.
 *  0b010..Divide by 3.
 *  0b011..Divide by 4.
 *  0b100..Divide by 5.
 *  0b101..Divide by 6.
 *  0b110..Divide by 7.
 *  0b111..Divide by 8.
 */
#define PCC_CLKCFG_PCD(x) (((uint32_t)(((uint32_t)(x)) << PCC_CLKCFG_PCD_SHIFT)) & PCC_CLKCFG_PCD_MASK)
#define PCC_CLKCFG_FRAC_MASK (0x8U)
#define PCC_CLKCFG_FRAC_SHIFT (3U)
/*! FRAC - Peripheral Clock Divider Fraction
 *  0b0..Fractional value is 0.
 *  0b1..Fractional value is 1.
 */
#define PCC_CLKCFG_FRAC(x) (((uint32_t)(((uint32_t)(x)) << PCC_CLKCFG_FRAC_SHIFT)) & PCC_CLKCFG_FRAC_MASK)
#define PCC_CLKCFG_PCS_MASK (0x7000000U)
#define PCC_CLKCFG_PCS_SHIFT (24U)
/*! PCS - Peripheral Clock Source Select
 *  0b000..Clock is off (or test clock is enabled).
 *  0b001..OSCCLK - System Oscillator Bus Clock(scg_sosc_slow_clk).
 *  0b010..SCGIRCLK - Slow IRC Clock(scg_sirc_slow_clk), (maximum is 8MHz).
 *  0b011..SCGFIRCLK - Fast IRC Clock(scg_firc_slow_clk), (maximum is 48MHz).
 *  0b100..Reserved.
 *  0b101..Reserved.
 *  0b110..SCGPCLK System PLL clock (scg_spll_slow_clk).
 *  0b111..Reserved.
 */
#define PCC_CLKCFG_PCS(x) (((uint32_t)(((uint32_t)(x)) << PCC_CLKCFG_PCS_SHIFT)) & PCC_CLKCFG_PCS_MASK)
#define PCC_CLKCFG_INUSE_MASK (0x20000000U)
#define PCC_CLKCFG_INUSE_SHIFT (29U)
/*! INUSE - Clock Gate Control
 *  0b0..Another core is not using this peripheral.
 *  0b1..Another core is using this peripheral. Software cannot modify the existing clocking configuration.
 */
#define PCC_CLKCFG_INUSE(x) (((uint32_t)(((uint32_t)(x)) << PCC_CLKCFG_INUSE_SHIFT)) & PCC_CLKCFG_INUSE_MASK)
#define PCC_CLKCFG_CGC_MASK (0x40000000U)
#define PCC_CLKCFG_CGC_SHIFT (30U)
/*! CGC - Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define PCC_CLKCFG_CGC(x) (((uint32_t)(((uint32_t)(x)) << PCC_CLKCFG_CGC_SHIFT)) & PCC_CLKCFG_CGC_MASK)
#define PCC_CLKCFG_PR_MASK (0x80000000U)
#define PCC_CLKCFG_PR_SHIFT (31U)
/*! PR - Enable
 *  0b0..Peripheral is not present.
 *  0b1..Peripheral is present.
 */
#define PCC_CLKCFG_PR(x) (((uint32_t)(((uint32_t)(x)) << PCC_CLKCFG_PR_SHIFT)) & PCC_CLKCFG_PR_MASK)
/*! @} */

/* The count of PCC_CLKCFG */
#define PCC_CLKCFG_COUNT (121U)

/*!
 * @}
 */ /* end of group PCC_Register_Masks */

/* PCC - Peripheral instance base addresses */
/** Peripheral PCC0 base address */
#define PCC0_BASE (0x4007A000u)
/** Peripheral PCC0 base pointer */
#define PCC0 ((PCC_Type *)PCC0_BASE)
/** Peripheral PCC1 base address */
#define PCC1_BASE (0x400FA000u)
/** Peripheral PCC1 base pointer */
#define PCC1 ((PCC_Type *)PCC1_BASE)
/** Array initializer of PCC peripheral base addresses */
#define PCC_BASE_ADDRS       \
    {                        \
        PCC0_BASE, PCC1_BASE \
    }
/** Array initializer of PCC peripheral base pointers */
#define PCC_BASE_PTRS \
    {                 \
        PCC0, PCC1    \
    }
#define PCC_INSTANCE_MASK 0xF
#define PCC_INSTANCE_SHIFT 12
#define PCC_PERIPHERAL_MASK 0xFFF
#define PCC_PERIPHERAL_SHIFT 0
#define PCC_INSTANCE_0 0
#define PCC_INSTANCE_1 1

#define PCC_DMA0_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 8)
#define PCC_FLASH_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 32)
#define PCC_DMAMUX0_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 33)
#define PCC_INTMUX0_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 36)
#define PCC_TPM2_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 46)
#define PCC_LPIT0_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 48)
#define PCC_LPTMR0_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 52)
#define PCC_RTC_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 56)
#define PCC_LPSPI2_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 62)
#define PCC_LPI2C2_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 66)
#define PCC_LPUART2_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 70)
#define PCC_EMVSIM0_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 78)
#define PCC_USB0FS_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 85)
#define PCC_PORTA_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 90)
#define PCC_PORTB_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 91)
#define PCC_PORTC_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 92)
#define PCC_PORTD_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 93)
#define PCC_PORTE_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 94)
#define PCC_TSI0_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 98)
#define PCC_ADC0_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 102)
#define PCC_DAC0_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 106)
#define PCC_CMP0_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 110)
#define PCC_VREF_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 114)
#define PCC_CRC_INDEX ((uint16_t)((PCC_INSTANCE_0 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 120)
#define PCC_DMA0 (PCC0->CLKCFG[8])
#define PCC_FLASH (PCC0->CLKCFG[32])
#define PCC_DMAMUX0 (PCC0->CLKCFG[33])
#define PCC_INTMUX0 (PCC0->CLKCFG[36])
#define PCC_TPM2 (PCC0->CLKCFG[46])
#define PCC_LPIT0 (PCC0->CLKCFG[48])
#define PCC_LPTMR0 (PCC0->CLKCFG[52])
#define PCC_RTC (PCC0->CLKCFG[56])
#define PCC_LPSPI2 (PCC0->CLKCFG[62])
#define PCC_LPI2C2 (PCC0->CLKCFG[66])
#define PCC_LPUART2 (PCC0->CLKCFG[70])
#define PCC_EMVSIM0 (PCC0->CLKCFG[78])
#define PCC_USB0FS (PCC0->CLKCFG[85])
#define PCC_PORTA (PCC0->CLKCFG[90])
#define PCC_PORTB (PCC0->CLKCFG[91])
#define PCC_PORTC (PCC0->CLKCFG[92])
#define PCC_PORTD (PCC0->CLKCFG[93])
#define PCC_PORTE (PCC0->CLKCFG[94])
#define PCC_TSI0 (PCC0->CLKCFG[98])
#define PCC_ADC0 (PCC0->CLKCFG[102])
#define PCC_DAC0 (PCC0->CLKCFG[106])
#define PCC_CMP0 (PCC0->CLKCFG[110])
#define PCC_VREF (PCC0->CLKCFG[114])
#define PCC_CRC (PCC0->CLKCFG[120])

#define PCC_TRNG_INDEX ((uint16_t)((PCC_INSTANCE_1 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 37)
#define PCC_TPM0_INDEX ((uint16_t)((PCC_INSTANCE_1 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 44)
#define PCC_TPM1_INDEX ((uint16_t)((PCC_INSTANCE_1 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 45)
#define PCC_LPTMR1_INDEX ((uint16_t)((PCC_INSTANCE_1 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 53)
#define PCC_LPSPI0_INDEX ((uint16_t)((PCC_INSTANCE_1 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 60)
#define PCC_LPSPI1_INDEX ((uint16_t)((PCC_INSTANCE_1 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 61)
#define PCC_LPI2C0_INDEX ((uint16_t)((PCC_INSTANCE_1 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 64)
#define PCC_LPI2C1_INDEX ((uint16_t)((PCC_INSTANCE_1 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 65)
#define PCC_LPUART0_INDEX ((uint16_t)((PCC_INSTANCE_1 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 68)
#define PCC_LPUART1_INDEX ((uint16_t)((PCC_INSTANCE_1 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 69)
#define PCC_FLEXIO0_INDEX ((uint16_t)((PCC_INSTANCE_1 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 74)
#define PCC_PORTM_INDEX ((uint16_t)((PCC_INSTANCE_1 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 96)
#define PCC_CMP1_INDEX ((uint16_t)((PCC_INSTANCE_1 & PCC_INSTANCE_MASK) << PCC_INSTANCE_SHIFT) | 111)
#define PCC_TRNG (PCC1->CLKCFG[37])
#define PCC_TPM0 (PCC1->CLKCFG[44])
#define PCC_TPM1 (PCC1->CLKCFG[45])
#define PCC_LPTMR1 (PCC1->CLKCFG[53])
#define PCC_LPSPI0 (PCC1->CLKCFG[60])
#define PCC_LPSPI1 (PCC1->CLKCFG[61])
#define PCC_LPI2C0 (PCC1->CLKCFG[64])
#define PCC_LPI2C1 (PCC1->CLKCFG[65])
#define PCC_LPUART0 (PCC1->CLKCFG[68])
#define PCC_LPUART1 (PCC1->CLKCFG[69])
#define PCC_FLEXIO0 (PCC1->CLKCFG[74])
#define PCC_CMP1 (PCC1->CLKCFG[111])

/*!
 * @}
 */ /* end of group PCC_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- PMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Peripheral_Access_Layer PMC Peripheral Access Layer
 * @{
 */

/** PMC - Register Layout Typedef */
typedef struct
{
    __I uint32_t VERID;   /**< Version ID register, offset: 0x0 */
    __I uint32_t PARAM;   /**< Parameter register, offset: 0x4 */
    __IO uint32_t LVDSC1; /**< Low Voltage Detect Status And Control 1 register, offset: 0x8 */
    __IO uint32_t LVDSC2; /**< Low Voltage Detect Status And Control 2 register, offset: 0xC */
    __IO uint32_t REGSC;  /**< Regulator Status And Control register, offset: 0x10 */
    uint8_t RESERVED_0[32];
    __IO uint32_t HVDSC1; /**< High Voltage Detect Status And Control 1 register, offset: 0x34 */
} PMC_Type;

/* ----------------------------------------------------------------------------
   -- PMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Masks PMC Register Masks
 * @{
 */

/*! @name VERID - Version ID register */
/*! @{ */
#define PMC_VERID_FEATURE_MASK (0xFFFFU)
#define PMC_VERID_FEATURE_SHIFT (0U)
/*! FEATURE - Feature Specification Number
 *  0b0000000000000000..Standard features implemented
 */
#define PMC_VERID_FEATURE(x) (((uint32_t)(((uint32_t)(x)) << PMC_VERID_FEATURE_SHIFT)) & PMC_VERID_FEATURE_MASK)
#define PMC_VERID_MINOR_MASK (0xFF0000U)
#define PMC_VERID_MINOR_SHIFT (16U)
/*! MINOR - Minor Version Number
 */
#define PMC_VERID_MINOR(x) (((uint32_t)(((uint32_t)(x)) << PMC_VERID_MINOR_SHIFT)) & PMC_VERID_MINOR_MASK)
#define PMC_VERID_MAJOR_MASK (0xFF000000U)
#define PMC_VERID_MAJOR_SHIFT (24U)
/*! MAJOR - Major Version Number
 */
#define PMC_VERID_MAJOR(x) (((uint32_t)(((uint32_t)(x)) << PMC_VERID_MAJOR_SHIFT)) & PMC_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter register */
/*! @{ */
#define PMC_PARAM_VLPOE_MASK (0x1U)
#define PMC_PARAM_VLPOE_SHIFT (0U)
/*! VLPOE - VLPO Enable
 */
#define PMC_PARAM_VLPOE(x) (((uint32_t)(((uint32_t)(x)) << PMC_PARAM_VLPOE_SHIFT)) & PMC_PARAM_VLPOE_MASK)
#define PMC_PARAM_HVDE_MASK (0x2U)
#define PMC_PARAM_HVDE_SHIFT (1U)
/*! HVDE - HVD Enabled
 */
#define PMC_PARAM_HVDE(x) (((uint32_t)(((uint32_t)(x)) << PMC_PARAM_HVDE_SHIFT)) & PMC_PARAM_HVDE_MASK)
/*! @} */

/*! @name LVDSC1 - Low Voltage Detect Status And Control 1 register */
/*! @{ */
#define PMC_LVDSC1_LVDV_MASK (0x3U)
#define PMC_LVDSC1_LVDV_SHIFT (0U)
/*! LVDV - Low-Voltage Detect Voltage Select
 *  0b00..Low trip point selected (V LVD = V LVDL )
 *  0b01..High trip point selected (V LVD = V LVDH )
 *  0b10..Reserved
 *  0b11..Reserved
 */
#define PMC_LVDSC1_LVDV(x) (((uint32_t)(((uint32_t)(x)) << PMC_LVDSC1_LVDV_SHIFT)) & PMC_LVDSC1_LVDV_MASK)
#define PMC_LVDSC1_LVDRE_MASK (0x10U)
#define PMC_LVDSC1_LVDRE_SHIFT (4U)
/*! LVDRE - Low-Voltage Detect Reset Enable
 *  0b0..LVDF does not generate hardware resets
 *  0b1..Force an MCU reset when LVDF = 1
 */
#define PMC_LVDSC1_LVDRE(x) (((uint32_t)(((uint32_t)(x)) << PMC_LVDSC1_LVDRE_SHIFT)) & PMC_LVDSC1_LVDRE_MASK)
#define PMC_LVDSC1_LVDIE_MASK (0x20U)
#define PMC_LVDSC1_LVDIE_SHIFT (5U)
/*! LVDIE - Low-Voltage Detect Interrupt Enable
 *  0b0..Hardware interrupt disabled (use polling)
 *  0b1..Request a hardware interrupt when LVDF = 1
 */
#define PMC_LVDSC1_LVDIE(x) (((uint32_t)(((uint32_t)(x)) << PMC_LVDSC1_LVDIE_SHIFT)) & PMC_LVDSC1_LVDIE_MASK)
#define PMC_LVDSC1_LVDACK_MASK (0x40U)
#define PMC_LVDSC1_LVDACK_SHIFT (6U)
/*! LVDACK - Low-Voltage Detect Acknowledge
 */
#define PMC_LVDSC1_LVDACK(x) (((uint32_t)(((uint32_t)(x)) << PMC_LVDSC1_LVDACK_SHIFT)) & PMC_LVDSC1_LVDACK_MASK)
#define PMC_LVDSC1_LVDF_MASK (0x80U)
#define PMC_LVDSC1_LVDF_SHIFT (7U)
/*! LVDF - Low-Voltage Detect Flag
 *  0b0..Low-voltage event not detected
 *  0b1..Low-voltage event detected
 */
#define PMC_LVDSC1_LVDF(x) (((uint32_t)(((uint32_t)(x)) << PMC_LVDSC1_LVDF_SHIFT)) & PMC_LVDSC1_LVDF_MASK)
/*! @} */

/*! @name LVDSC2 - Low Voltage Detect Status And Control 2 register */
/*! @{ */
#define PMC_LVDSC2_LVWV_MASK (0x3U)
#define PMC_LVDSC2_LVWV_SHIFT (0U)
/*! LVWV - Low-Voltage Warning Voltage Select
 *  0b00..Low trip point selected (VLVW = VLVW1)
 *  0b01..Mid 1 trip point selected (VLVW = VLVW2)
 *  0b10..Mid 2 trip point selected (VLVW = VLVW3)
 *  0b11..High trip point selected (VLVW = VLVW4)
 */
#define PMC_LVDSC2_LVWV(x) (((uint32_t)(((uint32_t)(x)) << PMC_LVDSC2_LVWV_SHIFT)) & PMC_LVDSC2_LVWV_MASK)
#define PMC_LVDSC2_LVWIE_MASK (0x20U)
#define PMC_LVDSC2_LVWIE_SHIFT (5U)
/*! LVWIE - Low-Voltage Warning Interrupt Enable
 *  0b0..Hardware interrupt disabled (use polling)
 *  0b1..Request a hardware interrupt when LVWF = 1
 */
#define PMC_LVDSC2_LVWIE(x) (((uint32_t)(((uint32_t)(x)) << PMC_LVDSC2_LVWIE_SHIFT)) & PMC_LVDSC2_LVWIE_MASK)
#define PMC_LVDSC2_LVWACK_MASK (0x40U)
#define PMC_LVDSC2_LVWACK_SHIFT (6U)
/*! LVWACK - Low-Voltage Warning Acknowledge
 */
#define PMC_LVDSC2_LVWACK(x) (((uint32_t)(((uint32_t)(x)) << PMC_LVDSC2_LVWACK_SHIFT)) & PMC_LVDSC2_LVWACK_MASK)
#define PMC_LVDSC2_LVWF_MASK (0x80U)
#define PMC_LVDSC2_LVWF_SHIFT (7U)
/*! LVWF - Low-Voltage Warning Flag
 *  0b0..Low-voltage warning event not detected
 *  0b1..Low-voltage warning event detected
 */
#define PMC_LVDSC2_LVWF(x) (((uint32_t)(((uint32_t)(x)) << PMC_LVDSC2_LVWF_SHIFT)) & PMC_LVDSC2_LVWF_MASK)
/*! @} */

/*! @name REGSC - Regulator Status And Control register */
/*! @{ */
#define PMC_REGSC_BGBE_MASK (0x1U)
#define PMC_REGSC_BGBE_SHIFT (0U)
/*! BGBE - Bandgap Buffer Enable
 *  0b0..Bandgap buffer not enabled
 *  0b1..Bandgap buffer enabled
 */
#define PMC_REGSC_BGBE(x) (((uint32_t)(((uint32_t)(x)) << PMC_REGSC_BGBE_SHIFT)) & PMC_REGSC_BGBE_MASK)
#define PMC_REGSC_REGONS_MASK (0x4U)
#define PMC_REGSC_REGONS_SHIFT (2U)
/*! REGONS - Regulator In Run Regulation Status
 *  0b0..Regulator is in stop regulation or in transition to/from it
 *  0b1..Regulator is in run regulation
 */
#define PMC_REGSC_REGONS(x) (((uint32_t)(((uint32_t)(x)) << PMC_REGSC_REGONS_SHIFT)) & PMC_REGSC_REGONS_MASK)
#define PMC_REGSC_ACKISO_MASK (0x8U)
#define PMC_REGSC_ACKISO_SHIFT (3U)
/*! ACKISO - Acknowledge Isolation
 *  0b0..Peripherals and I/O pads are in normal run state.
 *  0b1..Certain peripherals and I/O pads are in an isolated and latched state.
 */
#define PMC_REGSC_ACKISO(x) (((uint32_t)(((uint32_t)(x)) << PMC_REGSC_ACKISO_SHIFT)) & PMC_REGSC_ACKISO_MASK)
#define PMC_REGSC_BGEN_MASK (0x10U)
#define PMC_REGSC_BGEN_SHIFT (4U)
/*! BGEN - Bandgap Enable In VLPx Operation
 *  0b0..Bandgap voltage reference is disabled in VLPx , LLS , and VLLSx modes.
 *  0b1..Bandgap voltage reference is enabled in VLPx , LLS , and VLLSx modes.
 */
#define PMC_REGSC_BGEN(x) (((uint32_t)(((uint32_t)(x)) << PMC_REGSC_BGEN_SHIFT)) & PMC_REGSC_BGEN_MASK)
#define PMC_REGSC_VLPO_MASK (0x40U)
#define PMC_REGSC_VLPO_SHIFT (6U)
/*! VLPO - VLPx Option
 *  0b0..Operating frequencies and SCG clocking modes are restricted during VLPx modes as listed in the Power Management
 * chapter. 0b1..If BGEN is also set, operating frequencies and SCG clocking modes are unrestricted during VLPx modes.
 *       Note that flash access frequency is still restricted however.
 */
#define PMC_REGSC_VLPO(x) (((uint32_t)(((uint32_t)(x)) << PMC_REGSC_VLPO_SHIFT)) & PMC_REGSC_VLPO_MASK)
/*! @} */

/*! @name HVDSC1 - High Voltage Detect Status And Control 1 register */
/*! @{ */
#define PMC_HVDSC1_HVDV_MASK (0x1U)
#define PMC_HVDSC1_HVDV_SHIFT (0U)
/*! HVDV - High-Voltage Detect Voltage Select
 *  0b0..Low trip point selected (V HVD = V HVDL )
 *  0b1..High trip point selected (V HVD = V HVDH )
 */
#define PMC_HVDSC1_HVDV(x) (((uint32_t)(((uint32_t)(x)) << PMC_HVDSC1_HVDV_SHIFT)) & PMC_HVDSC1_HVDV_MASK)
#define PMC_HVDSC1_HVDRE_MASK (0x10U)
#define PMC_HVDSC1_HVDRE_SHIFT (4U)
/*! HVDRE - High-Voltage Detect Reset Enable
 *  0b0..HVDF does not generate hardware resets
 *  0b1..Force an MCU reset when HVDF = 1
 */
#define PMC_HVDSC1_HVDRE(x) (((uint32_t)(((uint32_t)(x)) << PMC_HVDSC1_HVDRE_SHIFT)) & PMC_HVDSC1_HVDRE_MASK)
#define PMC_HVDSC1_HVDIE_MASK (0x20U)
#define PMC_HVDSC1_HVDIE_SHIFT (5U)
/*! HVDIE - High-Voltage Detect Interrupt Enable
 *  0b0..Hardware interrupt disabled (use polling)
 *  0b1..Request a hardware interrupt when HVDF = 1
 */
#define PMC_HVDSC1_HVDIE(x) (((uint32_t)(((uint32_t)(x)) << PMC_HVDSC1_HVDIE_SHIFT)) & PMC_HVDSC1_HVDIE_MASK)
#define PMC_HVDSC1_HVDACK_MASK (0x40U)
#define PMC_HVDSC1_HVDACK_SHIFT (6U)
/*! HVDACK - High-Voltage Detect Acknowledge
 */
#define PMC_HVDSC1_HVDACK(x) (((uint32_t)(((uint32_t)(x)) << PMC_HVDSC1_HVDACK_SHIFT)) & PMC_HVDSC1_HVDACK_MASK)
#define PMC_HVDSC1_HVDF_MASK (0x80U)
#define PMC_HVDSC1_HVDF_SHIFT (7U)
/*! HVDF - High-Voltage Detect Flag
 *  0b0..High-voltage event not detected
 *  0b1..High-voltage event detected
 */
#define PMC_HVDSC1_HVDF(x) (((uint32_t)(((uint32_t)(x)) << PMC_HVDSC1_HVDF_SHIFT)) & PMC_HVDSC1_HVDF_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group PMC_Register_Masks */

/* PMC - Peripheral instance base addresses */
/** Peripheral PMC base address */
#define PMC_BASE (0x4007D000u)
/** Peripheral PMC base pointer */
#define PMC ((PMC_Type *)PMC_BASE)
/** Array initializer of PMC peripheral base addresses */
#define PMC_BASE_ADDRS \
    {                  \
        PMC_BASE       \
    }
/** Array initializer of PMC peripheral base pointers */
#define PMC_BASE_PTRS \
    {                 \
        PMC           \
    }
/** Interrupt vectors for the PMC peripheral type */
#define PMC_IRQS \
    {            \
        PMC_IRQn \
    }

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
typedef struct
{
    __IO uint32_t PCR[32]; /**< Pin Control Register n, array offset: 0x0, array step: 0x4 */
    __O uint32_t GPCLR;    /**< Global Pin Control Low Register, offset: 0x80 */
    __O uint32_t GPCHR;    /**< Global Pin Control High Register, offset: 0x84 */
    __O uint32_t GICLR;    /**< Global Interrupt Control Low Register, offset: 0x88 */
    __O uint32_t GICHR;    /**< Global Interrupt Control High Register, offset: 0x8C */
    uint8_t RESERVED_0[16];
    __IO uint32_t ISFR; /**< Interrupt Status Flag Register, offset: 0xA0 */
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
#define PORT_PCR_PS_MASK (0x1U)
#define PORT_PCR_PS_SHIFT (0U)
/*! PS - Pull Select
 *  0b0..Internal pulldown resistor is enabled on the corresponding pin, if the corresponding PE field is set.
 *  0b1..Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set.
 */
#define PORT_PCR_PS(x) (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PS_SHIFT)) & PORT_PCR_PS_MASK)
#define PORT_PCR_PE_MASK (0x2U)
#define PORT_PCR_PE_SHIFT (1U)
/*! PE - Pull Enable
 *  0b0..Internal pullup or pulldown resistor is not enabled on the corresponding pin.
 *  0b1..Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is configured as a digital
 * input.
 */
#define PORT_PCR_PE(x) (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PE_SHIFT)) & PORT_PCR_PE_MASK)
#define PORT_PCR_SRE_MASK (0x4U)
#define PORT_PCR_SRE_SHIFT (2U)
/*! SRE - Slew Rate Enable
 *  0b0..Fast slew rate is configured on the corresponding pin, if the pin is configured as a digital output.
 *  0b1..Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output.
 */
#define PORT_PCR_SRE(x) (((uint32_t)(((uint32_t)(x)) << PORT_PCR_SRE_SHIFT)) & PORT_PCR_SRE_MASK)
#define PORT_PCR_PFE_MASK (0x10U)
#define PORT_PCR_PFE_SHIFT (4U)
/*! PFE - Passive Filter Enable
 *  0b0..Passive input filter is disabled on the corresponding pin.
 *  0b1..Passive input filter is enabled on the corresponding pin, if the pin is configured as a digital input.
 *       Refer to the device data sheet for filter characteristics.
 */
#define PORT_PCR_PFE(x) (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PFE_SHIFT)) & PORT_PCR_PFE_MASK)
#define PORT_PCR_ODE_MASK (0x20U)
#define PORT_PCR_ODE_SHIFT (5U)
/*! ODE - Open Drain Enable
 *  0b0..Open drain output is disabled on the corresponding pin.
 *  0b1..Open drain output is enabled on the corresponding pin, if the pin is configured as a digital output.
 */
#define PORT_PCR_ODE(x) (((uint32_t)(((uint32_t)(x)) << PORT_PCR_ODE_SHIFT)) & PORT_PCR_ODE_MASK)
#define PORT_PCR_DSE_MASK (0x40U)
#define PORT_PCR_DSE_SHIFT (6U)
/*! DSE - Drive Strength Enable
 *  0b0..Low drive strength is configured on the corresponding pin, if pin is configured as a digital output.
 *  0b1..High drive strength is configured on the corresponding pin, if pin is configured as a digital output.
 */
#define PORT_PCR_DSE(x) (((uint32_t)(((uint32_t)(x)) << PORT_PCR_DSE_SHIFT)) & PORT_PCR_DSE_MASK)
#define PORT_PCR_MUX_MASK (0x700U)
#define PORT_PCR_MUX_SHIFT (8U)
/*! MUX - Pin Mux Control
 *  0b000..Pin disabled (Alternative 0) (analog).
 *  0b001..Alternative 1 (GPIO).
 *  0b010..Alternative 2 (chip-specific).
 *  0b011..Alternative 3 (chip-specific).
 *  0b100..Alternative 4 (chip-specific).
 *  0b101..Alternative 5 (chip-specific).
 *  0b110..Alternative 6 (chip-specific).
 *  0b111..Alternative 7 (chip-specific).
 */
#define PORT_PCR_MUX(x) (((uint32_t)(((uint32_t)(x)) << PORT_PCR_MUX_SHIFT)) & PORT_PCR_MUX_MASK)
#define PORT_PCR_LK_MASK (0x8000U)
#define PORT_PCR_LK_SHIFT (15U)
/*! LK - Lock Register
 *  0b0..Pin Control Register fields [15:0] are not locked.
 *  0b1..Pin Control Register fields [15:0] are locked and cannot be updated until the next system reset.
 */
#define PORT_PCR_LK(x) (((uint32_t)(((uint32_t)(x)) << PORT_PCR_LK_SHIFT)) & PORT_PCR_LK_MASK)
#define PORT_PCR_IRQC_MASK (0xF0000U)
#define PORT_PCR_IRQC_SHIFT (16U)
/*! IRQC - Interrupt Configuration
 *  0b0000..Interrupt Status Flag (ISF) is disabled.
 *  0b0001..ISF flag and DMA request on rising edge.
 *  0b0010..ISF flag and DMA request on falling edge.
 *  0b0011..ISF flag and DMA request on either edge.
 *  0b0100..Reserved.
 *  0b0101..Flag sets on rising edge.
 *  0b0110..Flag sets on falling edge.
 *  0b0111..Flag sets on either edge.
 *  0b1000..ISF flag and Interrupt when logic 0.
 *  0b1001..ISF flag and Interrupt on rising-edge.
 *  0b1010..ISF flag and Interrupt on falling-edge.
 *  0b1011..ISF flag and Interrupt on either edge.
 *  0b1100..ISF flag and Interrupt when logic 1.
 *  0b1101..Enable active high trigger output, flag is disabled. [The trigger output goes to the trigger mux,
 *          which allows pins to trigger other peripherals (configurable polarity; 1 pin per port; if multiple pins are
 *          configured, then they are ORed together to create the trigger)]
 *  0b1110..Enable active low trigger output, flag is disabled.
 *  0b1111..Reserved.
 */
#define PORT_PCR_IRQC(x) (((uint32_t)(((uint32_t)(x)) << PORT_PCR_IRQC_SHIFT)) & PORT_PCR_IRQC_MASK)
#define PORT_PCR_ISF_MASK (0x1000000U)
#define PORT_PCR_ISF_SHIFT (24U)
/*! ISF - Interrupt Status Flag
 *  0b0..Configured interrupt is not detected.
 *  0b1..Configured interrupt is detected. If the pin is configured to generate a DMA request, then the
 *       corresponding flag will be cleared automatically at the completion of the requested DMA transfer. Otherwise,
 * the flag remains set until a logic 1 is written to the flag. If the pin is configured for a level sensitive interrupt
 * and the pin remains asserted, then the flag is set again immediately after it is cleared.
 */
#define PORT_PCR_ISF(x) (((uint32_t)(((uint32_t)(x)) << PORT_PCR_ISF_SHIFT)) & PORT_PCR_ISF_MASK)
/*! @} */

/* The count of PORT_PCR */
#define PORT_PCR_COUNT (32U)

/*! @name GPCLR - Global Pin Control Low Register */
/*! @{ */
#define PORT_GPCLR_GPWD_MASK (0xFFFFU)
#define PORT_GPCLR_GPWD_SHIFT (0U)
/*! GPWD - Global Pin Write Data
 */
#define PORT_GPCLR_GPWD(x) (((uint32_t)(((uint32_t)(x)) << PORT_GPCLR_GPWD_SHIFT)) & PORT_GPCLR_GPWD_MASK)
#define PORT_GPCLR_GPWE_MASK (0xFFFF0000U)
#define PORT_GPCLR_GPWE_SHIFT (16U)
/*! GPWE - Global Pin Write Enable
 *  0b0000000000000000..Corresponding Pin Control Register is not updated with the value in GPWD.
 *  0b0000000000000001..Corresponding Pin Control Register is updated with the value in GPWD.
 */
#define PORT_GPCLR_GPWE(x) (((uint32_t)(((uint32_t)(x)) << PORT_GPCLR_GPWE_SHIFT)) & PORT_GPCLR_GPWE_MASK)
/*! @} */

/*! @name GPCHR - Global Pin Control High Register */
/*! @{ */
#define PORT_GPCHR_GPWD_MASK (0xFFFFU)
#define PORT_GPCHR_GPWD_SHIFT (0U)
/*! GPWD - Global Pin Write Data
 */
#define PORT_GPCHR_GPWD(x) (((uint32_t)(((uint32_t)(x)) << PORT_GPCHR_GPWD_SHIFT)) & PORT_GPCHR_GPWD_MASK)
#define PORT_GPCHR_GPWE_MASK (0xFFFF0000U)
#define PORT_GPCHR_GPWE_SHIFT (16U)
/*! GPWE - Global Pin Write Enable
 *  0b0000000000000000..Corresponding Pin Control Register is not updated with the value in GPWD.
 *  0b0000000000000001..Corresponding Pin Control Register is updated with the value in GPWD.
 */
#define PORT_GPCHR_GPWE(x) (((uint32_t)(((uint32_t)(x)) << PORT_GPCHR_GPWE_SHIFT)) & PORT_GPCHR_GPWE_MASK)
/*! @} */

/*! @name GICLR - Global Interrupt Control Low Register */
/*! @{ */
#define PORT_GICLR_GIWE_MASK (0xFFFFU)
#define PORT_GICLR_GIWE_SHIFT (0U)
/*! GIWE - Global Interrupt Write Enable
 *  0b0000000000000000..Corresponding Pin Control Register is not updated with the value in GPWD.
 *  0b0000000000000001..Corresponding Pin Control Register is updated with the value in GPWD.
 */
#define PORT_GICLR_GIWE(x) (((uint32_t)(((uint32_t)(x)) << PORT_GICLR_GIWE_SHIFT)) & PORT_GICLR_GIWE_MASK)
#define PORT_GICLR_GIWD_MASK (0xFFFF0000U)
#define PORT_GICLR_GIWD_SHIFT (16U)
/*! GIWD - Global Interrupt Write Data
 */
#define PORT_GICLR_GIWD(x) (((uint32_t)(((uint32_t)(x)) << PORT_GICLR_GIWD_SHIFT)) & PORT_GICLR_GIWD_MASK)
/*! @} */

/*! @name GICHR - Global Interrupt Control High Register */
/*! @{ */
#define PORT_GICHR_GIWE_MASK (0xFFFFU)
#define PORT_GICHR_GIWE_SHIFT (0U)
/*! GIWE - Global Interrupt Write Enable
 *  0b0000000000000000..Corresponding Pin Control Register is not updated with the value in GPWD.
 *  0b0000000000000001..Corresponding Pin Control Register is updated with the value in GPWD.
 */
#define PORT_GICHR_GIWE(x) (((uint32_t)(((uint32_t)(x)) << PORT_GICHR_GIWE_SHIFT)) & PORT_GICHR_GIWE_MASK)
#define PORT_GICHR_GIWD_MASK (0xFFFF0000U)
#define PORT_GICHR_GIWD_SHIFT (16U)
/*! GIWD - Global Interrupt Write Data
 */
#define PORT_GICHR_GIWD(x) (((uint32_t)(((uint32_t)(x)) << PORT_GICHR_GIWD_SHIFT)) & PORT_GICHR_GIWD_MASK)
/*! @} */

/*! @name ISFR - Interrupt Status Flag Register */
/*! @{ */
#define PORT_ISFR_ISF_MASK (0xFFFFFFFFU)
#define PORT_ISFR_ISF_SHIFT (0U)
/*! ISF - Interrupt Status Flag
 *  0b00000000000000000000000000000000..Configured interrupt is not detected.
 *  0b00000000000000000000000000000001..Configured interrupt is detected. If the pin is configured to generate a
 *                                      DMA request, then the corresponding flag will be cleared automatically at
 *                                      the completion of the requested DMA transfer. Otherwise, the flag remains set
 *                                      until a logic 1 is written to the flag. If the pin is configured for a
 *                                      level sensitive interrupt and the pin remains asserted, then the flag is set
 *                                      again immediately after it is cleared.
 */
#define PORT_ISFR_ISF(x) (((uint32_t)(((uint32_t)(x)) << PORT_ISFR_ISF_SHIFT)) & PORT_ISFR_ISF_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group PORT_Register_Masks */

/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base address */
#define PORTA_BASE (0x4005A000u)
/** Peripheral PORTA base pointer */
#define PORTA ((PORT_Type *)PORTA_BASE)
/** Peripheral PORTB base address */
#define PORTB_BASE (0x4005B000u)
/** Peripheral PORTB base pointer */
#define PORTB ((PORT_Type *)PORTB_BASE)
/** Peripheral PORTC base address */
#define PORTC_BASE (0x4005C000u)
/** Peripheral PORTC base pointer */
#define PORTC ((PORT_Type *)PORTC_BASE)
/** Peripheral PORTD base address */
#define PORTD_BASE (0x4005D000u)
/** Peripheral PORTD base pointer */
#define PORTD ((PORT_Type *)PORTD_BASE)
/** Peripheral PORTE base address */
#define PORTE_BASE (0x4005E000u)
/** Peripheral PORTE base pointer */
#define PORTE ((PORT_Type *)PORTE_BASE)
/** Array initializer of PORT peripheral base addresses */
#define PORT_BASE_ADDRS                                            \
    {                                                              \
        PORTA_BASE, PORTB_BASE, PORTC_BASE, PORTD_BASE, PORTE_BASE \
    }
/** Array initializer of PORT peripheral base pointers */
#define PORT_BASE_PTRS                    \
    {                                     \
        PORTA, PORTB, PORTC, PORTD, PORTE \
    }
/** Interrupt vectors for the PORT peripheral type */
#define PORT_IRQS                                                  \
    {                                                              \
        PORTA_IRQn, PORTB_IRQn, PORTC_IRQn, PORTD_IRQn, PORTE_IRQn \
    }

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
typedef struct
{
    __I uint32_t VERID; /**< Version ID Register, offset: 0x0 */
    __I uint32_t PARAM; /**< Parameter Register, offset: 0x4 */
    __I uint32_t SRS;   /**< System Reset Status Register, offset: 0x8 */
    __IO uint32_t RPC;  /**< Reset Pin Control register, offset: 0xC */
    __IO uint32_t MR;   /**< Mode Register, offset: 0x10 */
    __IO uint32_t FM;   /**< Force Mode Register, offset: 0x14 */
    __IO uint32_t SSRS; /**< Sticky System Reset Status Register, offset: 0x18 */
    __IO uint32_t SRIE; /**< System Reset Interrupt Enable Register, offset: 0x1C */
} RCM_Type;

/* ----------------------------------------------------------------------------
   -- RCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Register_Masks RCM Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */
#define RCM_VERID_FEATURE_MASK (0xFFFFU)
#define RCM_VERID_FEATURE_SHIFT (0U)
/*! FEATURE - Feature Specification Number
 *  0b0000000000000011..Standard feature set.
 */
#define RCM_VERID_FEATURE(x) (((uint32_t)(((uint32_t)(x)) << RCM_VERID_FEATURE_SHIFT)) & RCM_VERID_FEATURE_MASK)
#define RCM_VERID_MINOR_MASK (0xFF0000U)
#define RCM_VERID_MINOR_SHIFT (16U)
/*! MINOR - Minor Version Number
 */
#define RCM_VERID_MINOR(x) (((uint32_t)(((uint32_t)(x)) << RCM_VERID_MINOR_SHIFT)) & RCM_VERID_MINOR_MASK)
#define RCM_VERID_MAJOR_MASK (0xFF000000U)
#define RCM_VERID_MAJOR_SHIFT (24U)
/*! MAJOR - Major Version Number
 */
#define RCM_VERID_MAJOR(x) (((uint32_t)(((uint32_t)(x)) << RCM_VERID_MAJOR_SHIFT)) & RCM_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */
#define RCM_PARAM_EWAKEUP_MASK (0x1U)
#define RCM_PARAM_EWAKEUP_SHIFT (0U)
/*! EWAKEUP - Existence of SRS[WAKEUP] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_EWAKEUP(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_EWAKEUP_SHIFT)) & RCM_PARAM_EWAKEUP_MASK)
#define RCM_PARAM_ELVD_MASK (0x2U)
#define RCM_PARAM_ELVD_SHIFT (1U)
/*! ELVD - Existence of SRS[LVD] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_ELVD(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_ELVD_SHIFT)) & RCM_PARAM_ELVD_MASK)
#define RCM_PARAM_ELOC_MASK (0x4U)
#define RCM_PARAM_ELOC_SHIFT (2U)
/*! ELOC - Existence of SRS[LOC] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_ELOC(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_ELOC_SHIFT)) & RCM_PARAM_ELOC_MASK)
#define RCM_PARAM_ELOL_MASK (0x8U)
#define RCM_PARAM_ELOL_SHIFT (3U)
/*! ELOL - Existence of SRS[LOL] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_ELOL(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_ELOL_SHIFT)) & RCM_PARAM_ELOL_MASK)
#define RCM_PARAM_ECMU_LOC_MASK (0x10U)
#define RCM_PARAM_ECMU_LOC_SHIFT (4U)
/*! ECMU_LOC - Existence of SRS[CMU_LOC] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_ECMU_LOC(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_ECMU_LOC_SHIFT)) & RCM_PARAM_ECMU_LOC_MASK)
#define RCM_PARAM_EWDOG_MASK (0x20U)
#define RCM_PARAM_EWDOG_SHIFT (5U)
/*! EWDOG - Existence of SRS[WDOG] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_EWDOG(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_EWDOG_SHIFT)) & RCM_PARAM_EWDOG_MASK)
#define RCM_PARAM_EPIN_MASK (0x40U)
#define RCM_PARAM_EPIN_SHIFT (6U)
/*! EPIN - Existence of SRS[PIN] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_EPIN(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_EPIN_SHIFT)) & RCM_PARAM_EPIN_MASK)
#define RCM_PARAM_EPOR_MASK (0x80U)
#define RCM_PARAM_EPOR_SHIFT (7U)
/*! EPOR - Existence of SRS[POR] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_EPOR(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_EPOR_SHIFT)) & RCM_PARAM_EPOR_MASK)
#define RCM_PARAM_EJTAG_MASK (0x100U)
#define RCM_PARAM_EJTAG_SHIFT (8U)
/*! EJTAG - Existence of SRS[JTAG] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_EJTAG(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_EJTAG_SHIFT)) & RCM_PARAM_EJTAG_MASK)
#define RCM_PARAM_ELOCKUP_MASK (0x200U)
#define RCM_PARAM_ELOCKUP_SHIFT (9U)
/*! ELOCKUP - Existence of SRS[LOCKUP] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_ELOCKUP(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_ELOCKUP_SHIFT)) & RCM_PARAM_ELOCKUP_MASK)
#define RCM_PARAM_ESW_MASK (0x400U)
#define RCM_PARAM_ESW_SHIFT (10U)
/*! ESW - Existence of SRS[SW] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_ESW(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_ESW_SHIFT)) & RCM_PARAM_ESW_MASK)
#define RCM_PARAM_EMDM_AP_MASK (0x800U)
#define RCM_PARAM_EMDM_AP_SHIFT (11U)
/*! EMDM_AP - Existence of SRS[MDM_AP] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_EMDM_AP(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_EMDM_AP_SHIFT)) & RCM_PARAM_EMDM_AP_MASK)
#define RCM_PARAM_ESACKERR_MASK (0x2000U)
#define RCM_PARAM_ESACKERR_SHIFT (13U)
/*! ESACKERR - Existence of SRS[SACKERR] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_ESACKERR(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_ESACKERR_SHIFT)) & RCM_PARAM_ESACKERR_MASK)
#define RCM_PARAM_ETAMPER_MASK (0x8000U)
#define RCM_PARAM_ETAMPER_SHIFT (15U)
/*! ETAMPER - Existence of SRS[TAMPER] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_ETAMPER(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_ETAMPER_SHIFT)) & RCM_PARAM_ETAMPER_MASK)
#define RCM_PARAM_ECORE1_MASK (0x10000U)
#define RCM_PARAM_ECORE1_SHIFT (16U)
/*! ECORE1 - Existence of SRS[CORE1] status indication feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define RCM_PARAM_ECORE1(x) (((uint32_t)(((uint32_t)(x)) << RCM_PARAM_ECORE1_SHIFT)) & RCM_PARAM_ECORE1_MASK)
/*! @} */

/*! @name SRS - System Reset Status Register */
/*! @{ */
#define RCM_SRS_WAKEUP_MASK (0x1U)
#define RCM_SRS_WAKEUP_SHIFT (0U)
/*! WAKEUP - VLLS Wakeup Reset
 *  0b0..Reset not caused by wakeup from VLLS mode.
 *  0b1..Reset caused by wakeup from VLLS mode.
 */
#define RCM_SRS_WAKEUP(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRS_WAKEUP_SHIFT)) & RCM_SRS_WAKEUP_MASK)
#define RCM_SRS_LVD_MASK (0x2U)
#define RCM_SRS_LVD_SHIFT (1U)
/*! LVD - Low-Voltage Detect Reset or High-Voltage Detect Reset
 *  0b0..Reset not caused by LVD trip, HVD trip or POR
 *  0b1..Reset caused by LVD trip, HVD trip or POR
 */
#define RCM_SRS_LVD(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRS_LVD_SHIFT)) & RCM_SRS_LVD_MASK)
#define RCM_SRS_LOC_MASK (0x4U)
#define RCM_SRS_LOC_SHIFT (2U)
/*! LOC - Loss-of-Clock Reset
 *  0b0..Reset not caused by a loss of external clock.
 *  0b1..Reset caused by a loss of external clock.
 */
#define RCM_SRS_LOC(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRS_LOC_SHIFT)) & RCM_SRS_LOC_MASK)
#define RCM_SRS_LOL_MASK (0x8U)
#define RCM_SRS_LOL_SHIFT (3U)
/*! LOL - Loss-of-Lock Reset
 *  0b0..Reset not caused by a loss of lock in the PLL/FLL
 *  0b1..Reset caused by a loss of lock in the PLL/FLL
 */
#define RCM_SRS_LOL(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRS_LOL_SHIFT)) & RCM_SRS_LOL_MASK)
#define RCM_SRS_WDOG_MASK (0x20U)
#define RCM_SRS_WDOG_SHIFT (5U)
/*! WDOG - Watchdog
 *  0b0..Reset not caused by watchdog timeout
 *  0b1..Reset caused by watchdog timeout
 */
#define RCM_SRS_WDOG(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRS_WDOG_SHIFT)) & RCM_SRS_WDOG_MASK)
#define RCM_SRS_PIN_MASK (0x40U)
#define RCM_SRS_PIN_SHIFT (6U)
/*! PIN - External Reset Pin
 *  0b0..Reset not caused by external reset pin
 *  0b1..Reset caused by external reset pin
 */
#define RCM_SRS_PIN(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRS_PIN_SHIFT)) & RCM_SRS_PIN_MASK)
#define RCM_SRS_POR_MASK (0x80U)
#define RCM_SRS_POR_SHIFT (7U)
/*! POR - Power-On Reset
 *  0b0..Reset not caused by POR
 *  0b1..Reset caused by POR
 */
#define RCM_SRS_POR(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRS_POR_SHIFT)) & RCM_SRS_POR_MASK)
#define RCM_SRS_LOCKUP_MASK (0x200U)
#define RCM_SRS_LOCKUP_SHIFT (9U)
/*! LOCKUP - Core Lockup
 *  0b0..Reset not caused by core LOCKUP event
 *  0b1..Reset caused by core LOCKUP event
 */
#define RCM_SRS_LOCKUP(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRS_LOCKUP_SHIFT)) & RCM_SRS_LOCKUP_MASK)
#define RCM_SRS_SW_MASK (0x400U)
#define RCM_SRS_SW_SHIFT (10U)
/*! SW - Software
 *  0b0..Reset not caused by software setting of SYSRESETREQ bit
 *  0b1..Reset caused by software setting of SYSRESETREQ bit
 */
#define RCM_SRS_SW(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRS_SW_SHIFT)) & RCM_SRS_SW_MASK)
#define RCM_SRS_MDM_AP_MASK (0x800U)
#define RCM_SRS_MDM_AP_SHIFT (11U)
/*! MDM_AP - MDM-AP System Reset Request
 *  0b0..Reset was not caused by host debugger system setting of the System Reset Request bit
 *  0b1..Reset was caused by host debugger system setting of the System Reset Request bit
 */
#define RCM_SRS_MDM_AP(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRS_MDM_AP_SHIFT)) & RCM_SRS_MDM_AP_MASK)
#define RCM_SRS_SACKERR_MASK (0x2000U)
#define RCM_SRS_SACKERR_SHIFT (13U)
/*! SACKERR - Stop Acknowledge Error
 *  0b0..Reset not caused by peripheral failure to acknowledge attempt to enter stop mode
 *  0b1..Reset caused by peripheral failure to acknowledge attempt to enter stop mode
 */
#define RCM_SRS_SACKERR(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRS_SACKERR_SHIFT)) & RCM_SRS_SACKERR_MASK)
/*! @} */

/*! @name RPC - Reset Pin Control register */
/*! @{ */
#define RCM_RPC_RSTFLTSRW_MASK (0x3U)
#define RCM_RPC_RSTFLTSRW_SHIFT (0U)
/*! RSTFLTSRW - Reset Pin Filter Select in Run and Wait Modes
 *  0b00..All filtering disabled
 *  0b01..Bus clock filter enabled for normal operation
 *  0b10..LPO clock filter enabled for normal operation
 *  0b11..Reserved
 */
#define RCM_RPC_RSTFLTSRW(x) (((uint32_t)(((uint32_t)(x)) << RCM_RPC_RSTFLTSRW_SHIFT)) & RCM_RPC_RSTFLTSRW_MASK)
#define RCM_RPC_RSTFLTSS_MASK (0x4U)
#define RCM_RPC_RSTFLTSS_SHIFT (2U)
/*! RSTFLTSS - Reset Pin Filter Select in Stop Mode
 *  0b0..All filtering disabled
 *  0b1..LPO clock filter enabled
 */
#define RCM_RPC_RSTFLTSS(x) (((uint32_t)(((uint32_t)(x)) << RCM_RPC_RSTFLTSS_SHIFT)) & RCM_RPC_RSTFLTSS_MASK)
#define RCM_RPC_RSTFLTSEL_MASK (0x1F00U)
#define RCM_RPC_RSTFLTSEL_SHIFT (8U)
/*! RSTFLTSEL - Reset Pin Filter Bus Clock Select
 */
#define RCM_RPC_RSTFLTSEL(x) (((uint32_t)(((uint32_t)(x)) << RCM_RPC_RSTFLTSEL_SHIFT)) & RCM_RPC_RSTFLTSEL_MASK)
/*! @} */

/*! @name MR - Mode Register */
/*! @{ */
#define RCM_MR_BOOTROM_MASK (0x6U)
#define RCM_MR_BOOTROM_SHIFT (1U)
/*! BOOTROM - Boot ROM Configuration
 *  0b00..Boot from Flash
 *  0b01..Boot from ROM due to BOOTCFG0 pin assertion / Reserved if no Boot pin
 *  0b10..Boot form ROM due to FOPT[7] configuration
 *  0b11..Boot from ROM due to both BOOTCFG0 pin assertion and FOPT[7] configuration
 */
#define RCM_MR_BOOTROM(x) (((uint32_t)(((uint32_t)(x)) << RCM_MR_BOOTROM_SHIFT)) & RCM_MR_BOOTROM_MASK)
/*! @} */

/*! @name FM - Force Mode Register */
/*! @{ */
#define RCM_FM_FORCEROM_MASK (0x6U)
#define RCM_FM_FORCEROM_SHIFT (1U)
/*! FORCEROM - Force ROM Boot
 *  0b00..No effect
 *  0b01..Force boot from ROM with RCM_MR[1] set.
 *  0b10..Force boot from ROM with RCM_MR[2] set.
 *  0b11..Force boot from ROM with RCM_MR[2:1] set.
 */
#define RCM_FM_FORCEROM(x) (((uint32_t)(((uint32_t)(x)) << RCM_FM_FORCEROM_SHIFT)) & RCM_FM_FORCEROM_MASK)
/*! @} */

/*! @name SSRS - Sticky System Reset Status Register */
/*! @{ */
#define RCM_SSRS_SWAKEUP_MASK (0x1U)
#define RCM_SSRS_SWAKEUP_SHIFT (0U)
/*! SWAKEUP - Sticky VLLS Wakeup Reset
 *  0b0..Reset not caused by wakeup from VLLS mode.
 *  0b1..Reset caused by wakeup from VLLS mode.
 */
#define RCM_SSRS_SWAKEUP(x) (((uint32_t)(((uint32_t)(x)) << RCM_SSRS_SWAKEUP_SHIFT)) & RCM_SSRS_SWAKEUP_MASK)
#define RCM_SSRS_SLVD_MASK (0x2U)
#define RCM_SSRS_SLVD_SHIFT (1U)
/*! SLVD - Sticky Low-Voltage Detect Reset
 *  0b0..Reset not caused by LVD trip or POR
 *  0b1..Reset caused by LVD trip or POR
 */
#define RCM_SSRS_SLVD(x) (((uint32_t)(((uint32_t)(x)) << RCM_SSRS_SLVD_SHIFT)) & RCM_SSRS_SLVD_MASK)
#define RCM_SSRS_SLOC_MASK (0x4U)
#define RCM_SSRS_SLOC_SHIFT (2U)
/*! SLOC - Sticky Loss-of-Clock Reset
 *  0b0..Reset not caused by a loss of external clock.
 *  0b1..Reset caused by a loss of external clock.
 */
#define RCM_SSRS_SLOC(x) (((uint32_t)(((uint32_t)(x)) << RCM_SSRS_SLOC_SHIFT)) & RCM_SSRS_SLOC_MASK)
#define RCM_SSRS_SLOL_MASK (0x8U)
#define RCM_SSRS_SLOL_SHIFT (3U)
/*! SLOL - Sticky Loss-of-Lock Reset
 *  0b0..Reset not caused by a loss of lock in the PLL/FLL
 *  0b1..Reset caused by a loss of lock in the PLL/FLL
 */
#define RCM_SSRS_SLOL(x) (((uint32_t)(((uint32_t)(x)) << RCM_SSRS_SLOL_SHIFT)) & RCM_SSRS_SLOL_MASK)
#define RCM_SSRS_SWDOG_MASK (0x20U)
#define RCM_SSRS_SWDOG_SHIFT (5U)
/*! SWDOG - Sticky Watchdog
 *  0b0..Reset not caused by watchdog timeout
 *  0b1..Reset caused by watchdog timeout
 */
#define RCM_SSRS_SWDOG(x) (((uint32_t)(((uint32_t)(x)) << RCM_SSRS_SWDOG_SHIFT)) & RCM_SSRS_SWDOG_MASK)
#define RCM_SSRS_SPIN_MASK (0x40U)
#define RCM_SSRS_SPIN_SHIFT (6U)
/*! SPIN - Sticky External Reset Pin
 *  0b0..Reset not caused by external reset pin
 *  0b1..Reset caused by external reset pin
 */
#define RCM_SSRS_SPIN(x) (((uint32_t)(((uint32_t)(x)) << RCM_SSRS_SPIN_SHIFT)) & RCM_SSRS_SPIN_MASK)
#define RCM_SSRS_SPOR_MASK (0x80U)
#define RCM_SSRS_SPOR_SHIFT (7U)
/*! SPOR - Sticky Power-On Reset
 *  0b0..Reset not caused by POR
 *  0b1..Reset caused by POR
 */
#define RCM_SSRS_SPOR(x) (((uint32_t)(((uint32_t)(x)) << RCM_SSRS_SPOR_SHIFT)) & RCM_SSRS_SPOR_MASK)
#define RCM_SSRS_SLOCKUP_MASK (0x200U)
#define RCM_SSRS_SLOCKUP_SHIFT (9U)
/*! SLOCKUP - Sticky Core Lockup
 *  0b0..Reset not caused by core LOCKUP event
 *  0b1..Reset caused by core LOCKUP event
 */
#define RCM_SSRS_SLOCKUP(x) (((uint32_t)(((uint32_t)(x)) << RCM_SSRS_SLOCKUP_SHIFT)) & RCM_SSRS_SLOCKUP_MASK)
#define RCM_SSRS_SSW_MASK (0x400U)
#define RCM_SSRS_SSW_SHIFT (10U)
/*! SSW - Sticky Software
 *  0b0..Reset not caused by software setting of SYSRESETREQ bit
 *  0b1..Reset caused by software setting of SYSRESETREQ bit
 */
#define RCM_SSRS_SSW(x) (((uint32_t)(((uint32_t)(x)) << RCM_SSRS_SSW_SHIFT)) & RCM_SSRS_SSW_MASK)
#define RCM_SSRS_SMDM_AP_MASK (0x800U)
#define RCM_SSRS_SMDM_AP_SHIFT (11U)
/*! SMDM_AP - Sticky MDM-AP System Reset Request
 *  0b0..Reset was not caused by host debugger system setting of the System Reset Request bit
 *  0b1..Reset was caused by host debugger system setting of the System Reset Request bit
 */
#define RCM_SSRS_SMDM_AP(x) (((uint32_t)(((uint32_t)(x)) << RCM_SSRS_SMDM_AP_SHIFT)) & RCM_SSRS_SMDM_AP_MASK)
#define RCM_SSRS_SSACKERR_MASK (0x2000U)
#define RCM_SSRS_SSACKERR_SHIFT (13U)
/*! SSACKERR - Sticky Stop Acknowledge Error
 *  0b0..Reset not caused by peripheral failure to acknowledge attempt to enter stop mode
 *  0b1..Reset caused by peripheral failure to acknowledge attempt to enter stop mode
 */
#define RCM_SSRS_SSACKERR(x) (((uint32_t)(((uint32_t)(x)) << RCM_SSRS_SSACKERR_SHIFT)) & RCM_SSRS_SSACKERR_MASK)
/*! @} */

/*! @name SRIE - System Reset Interrupt Enable Register */
/*! @{ */
#define RCM_SRIE_DELAY_MASK (0x3U)
#define RCM_SRIE_DELAY_SHIFT (0U)
/*! DELAY - Reset Delay Time
 *  0b00..10 LPO cycles
 *  0b01..34 LPO cycles
 *  0b10..130 LPO cycles
 *  0b11..514 LPO cycles
 */
#define RCM_SRIE_DELAY(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRIE_DELAY_SHIFT)) & RCM_SRIE_DELAY_MASK)
#define RCM_SRIE_LOC_MASK (0x4U)
#define RCM_SRIE_LOC_SHIFT (2U)
/*! LOC - Loss-of-Clock Interrupt
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define RCM_SRIE_LOC(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRIE_LOC_SHIFT)) & RCM_SRIE_LOC_MASK)
#define RCM_SRIE_LOL_MASK (0x8U)
#define RCM_SRIE_LOL_SHIFT (3U)
/*! LOL - Loss-of-Lock Interrupt
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define RCM_SRIE_LOL(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRIE_LOL_SHIFT)) & RCM_SRIE_LOL_MASK)
#define RCM_SRIE_WDOG_MASK (0x20U)
#define RCM_SRIE_WDOG_SHIFT (5U)
/*! WDOG - Watchdog Interrupt
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define RCM_SRIE_WDOG(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRIE_WDOG_SHIFT)) & RCM_SRIE_WDOG_MASK)
#define RCM_SRIE_PIN_MASK (0x40U)
#define RCM_SRIE_PIN_SHIFT (6U)
/*! PIN - External Reset Pin Interrupt
 *  0b0..Reset not caused by external reset pin
 *  0b1..Reset caused by external reset pin
 */
#define RCM_SRIE_PIN(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRIE_PIN_SHIFT)) & RCM_SRIE_PIN_MASK)
#define RCM_SRIE_GIE_MASK (0x80U)
#define RCM_SRIE_GIE_SHIFT (7U)
/*! GIE - Global Interrupt Enable
 *  0b0..All interrupt sources disabled.
 *  0b1..All interrupt sources enabled. Note that the individual interrupt-enable bits still need to be set to generate
 * interrupts.
 */
#define RCM_SRIE_GIE(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRIE_GIE_SHIFT)) & RCM_SRIE_GIE_MASK)
#define RCM_SRIE_LOCKUP_MASK (0x200U)
#define RCM_SRIE_LOCKUP_SHIFT (9U)
/*! LOCKUP - Core Lockup Interrupt
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define RCM_SRIE_LOCKUP(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRIE_LOCKUP_SHIFT)) & RCM_SRIE_LOCKUP_MASK)
#define RCM_SRIE_SW_MASK (0x400U)
#define RCM_SRIE_SW_SHIFT (10U)
/*! SW - Software Interrupt
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define RCM_SRIE_SW(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRIE_SW_SHIFT)) & RCM_SRIE_SW_MASK)
#define RCM_SRIE_MDM_AP_MASK (0x800U)
#define RCM_SRIE_MDM_AP_SHIFT (11U)
/*! MDM_AP - MDM-AP System Reset Request
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define RCM_SRIE_MDM_AP(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRIE_MDM_AP_SHIFT)) & RCM_SRIE_MDM_AP_MASK)
#define RCM_SRIE_SACKERR_MASK (0x2000U)
#define RCM_SRIE_SACKERR_SHIFT (13U)
/*! SACKERR - Stop Acknowledge Error Interrupt
 *  0b0..Interrupt disabled.
 *  0b1..Interrupt enabled.
 */
#define RCM_SRIE_SACKERR(x) (((uint32_t)(((uint32_t)(x)) << RCM_SRIE_SACKERR_SHIFT)) & RCM_SRIE_SACKERR_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group RCM_Register_Masks */

/* RCM - Peripheral instance base addresses */
/** Peripheral RCM base address */
#define RCM_BASE (0x4007F000u)
/** Peripheral RCM base pointer */
#define RCM ((RCM_Type *)RCM_BASE)
/** Array initializer of RCM peripheral base addresses */
#define RCM_BASE_ADDRS \
    {                  \
        RCM_BASE       \
    }
/** Array initializer of RCM peripheral base pointers */
#define RCM_BASE_PTRS \
    {                 \
        RCM           \
    }
/** Interrupt vectors for the RCM peripheral type */
#define RCM_IRQS \
    {            \
        RCM_IRQn \
    }

/*!
 * @}
 */ /* end of group RCM_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- RFSYS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFSYS_Peripheral_Access_Layer RFSYS Peripheral Access Layer
 * @{
 */

/** RFSYS - Register Layout Typedef */
typedef struct
{
    __IO uint32_t REG[8]; /**< Register file register, array offset: 0x0, array step: 0x4 */
} RFSYS_Type;

/* ----------------------------------------------------------------------------
   -- RFSYS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFSYS_Register_Masks RFSYS Register Masks
 * @{
 */

/*! @name REG - Register file register */
/*! @{ */
#define RFSYS_REG_LL_MASK (0xFFU)
#define RFSYS_REG_LL_SHIFT (0U)
#define RFSYS_REG_LL(x) (((uint32_t)(((uint32_t)(x)) << RFSYS_REG_LL_SHIFT)) & RFSYS_REG_LL_MASK)
#define RFSYS_REG_LH_MASK (0xFF00U)
#define RFSYS_REG_LH_SHIFT (8U)
#define RFSYS_REG_LH(x) (((uint32_t)(((uint32_t)(x)) << RFSYS_REG_LH_SHIFT)) & RFSYS_REG_LH_MASK)
#define RFSYS_REG_HL_MASK (0xFF0000U)
#define RFSYS_REG_HL_SHIFT (16U)
#define RFSYS_REG_HL(x) (((uint32_t)(((uint32_t)(x)) << RFSYS_REG_HL_SHIFT)) & RFSYS_REG_HL_MASK)
#define RFSYS_REG_HH_MASK (0xFF000000U)
#define RFSYS_REG_HH_SHIFT (24U)
#define RFSYS_REG_HH(x) (((uint32_t)(((uint32_t)(x)) << RFSYS_REG_HH_SHIFT)) & RFSYS_REG_HH_MASK)
/*! @} */

/* The count of RFSYS_REG */
#define RFSYS_REG_COUNT (8U)

/*!
 * @}
 */ /* end of group RFSYS_Register_Masks */

/* RFSYS - Peripheral instance base addresses */
/** Peripheral RFSYS base address */
#define RFSYS_BASE (0x4007C000u)
/** Peripheral RFSYS base pointer */
#define RFSYS ((RFSYS_Type *)RFSYS_BASE)
/** Array initializer of RFSYS peripheral base addresses */
#define RFSYS_BASE_ADDRS \
    {                    \
        RFSYS_BASE       \
    }
/** Array initializer of RFSYS peripheral base pointers */
#define RFSYS_BASE_PTRS \
    {                   \
        RFSYS           \
    }

/*!
 * @}
 */ /* end of group RFSYS_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- RTC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Peripheral_Access_Layer RTC Peripheral Access Layer
 * @{
 */

/** RTC - Register Layout Typedef */
typedef struct
{
    __IO uint32_t TSR; /**< RTC Time Seconds Register, offset: 0x0 */
    __IO uint32_t TPR; /**< RTC Time Prescaler Register, offset: 0x4 */
    __IO uint32_t TAR; /**< RTC Time Alarm Register, offset: 0x8 */
    __IO uint32_t TCR; /**< RTC Time Compensation Register, offset: 0xC */
    __IO uint32_t CR;  /**< RTC Control Register, offset: 0x10 */
    __IO uint32_t SR;  /**< RTC Status Register, offset: 0x14 */
    __IO uint32_t LR;  /**< RTC Lock Register, offset: 0x18 */
    __IO uint32_t IER; /**< RTC Interrupt Enable Register, offset: 0x1C */
} RTC_Type;

/* ----------------------------------------------------------------------------
   -- RTC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Masks RTC Register Masks
 * @{
 */

/*! @name TSR - RTC Time Seconds Register */
/*! @{ */
#define RTC_TSR_TSR_MASK (0xFFFFFFFFU)
#define RTC_TSR_TSR_SHIFT (0U)
/*! TSR - Time Seconds Register
 */
#define RTC_TSR_TSR(x) (((uint32_t)(((uint32_t)(x)) << RTC_TSR_TSR_SHIFT)) & RTC_TSR_TSR_MASK)
/*! @} */

/*! @name TPR - RTC Time Prescaler Register */
/*! @{ */
#define RTC_TPR_TPR_MASK (0xFFFFU)
#define RTC_TPR_TPR_SHIFT (0U)
/*! TPR - Time Prescaler Register
 */
#define RTC_TPR_TPR(x) (((uint32_t)(((uint32_t)(x)) << RTC_TPR_TPR_SHIFT)) & RTC_TPR_TPR_MASK)
/*! @} */

/*! @name TAR - RTC Time Alarm Register */
/*! @{ */
#define RTC_TAR_TAR_MASK (0xFFFFFFFFU)
#define RTC_TAR_TAR_SHIFT (0U)
/*! TAR - Time Alarm Register
 */
#define RTC_TAR_TAR(x) (((uint32_t)(((uint32_t)(x)) << RTC_TAR_TAR_SHIFT)) & RTC_TAR_TAR_MASK)
/*! @} */

/*! @name TCR - RTC Time Compensation Register */
/*! @{ */
#define RTC_TCR_TCR_MASK (0xFFU)
#define RTC_TCR_TCR_SHIFT (0U)
/*! TCR - Time Compensation Register
 *  0b10000000..Time Prescaler Register overflows every 32896 clock cycles.
 *  0b11111111..Time Prescaler Register overflows every 32769 clock cycles.
 *  0b00000000..Time Prescaler Register overflows every 32768 clock cycles.
 *  0b00000001..Time Prescaler Register overflows every 32767 clock cycles.
 *  0b01111111..Time Prescaler Register overflows every 32641 clock cycles.
 */
#define RTC_TCR_TCR(x) (((uint32_t)(((uint32_t)(x)) << RTC_TCR_TCR_SHIFT)) & RTC_TCR_TCR_MASK)
#define RTC_TCR_CIR_MASK (0xFF00U)
#define RTC_TCR_CIR_SHIFT (8U)
/*! CIR - Compensation Interval Register
 */
#define RTC_TCR_CIR(x) (((uint32_t)(((uint32_t)(x)) << RTC_TCR_CIR_SHIFT)) & RTC_TCR_CIR_MASK)
#define RTC_TCR_TCV_MASK (0xFF0000U)
#define RTC_TCR_TCV_SHIFT (16U)
/*! TCV - Time Compensation Value
 */
#define RTC_TCR_TCV(x) (((uint32_t)(((uint32_t)(x)) << RTC_TCR_TCV_SHIFT)) & RTC_TCR_TCV_MASK)
#define RTC_TCR_CIC_MASK (0xFF000000U)
#define RTC_TCR_CIC_SHIFT (24U)
/*! CIC - Compensation Interval Counter
 */
#define RTC_TCR_CIC(x) (((uint32_t)(((uint32_t)(x)) << RTC_TCR_CIC_SHIFT)) & RTC_TCR_CIC_MASK)
/*! @} */

/*! @name CR - RTC Control Register */
/*! @{ */
#define RTC_CR_SWR_MASK (0x1U)
#define RTC_CR_SWR_SHIFT (0U)
/*! SWR - Software Reset
 *  0b0..No effect.
 *  0b1..Resets all RTC registers except for the SWR bit . The SWR bit is cleared by POR and by software explicitly
 * clearing it.
 */
#define RTC_CR_SWR(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_SWR_SHIFT)) & RTC_CR_SWR_MASK)
#define RTC_CR_WPE_MASK (0x2U)
#define RTC_CR_WPE_SHIFT (1U)
/*! WPE - Wakeup Pin Enable
 *  0b0..Wakeup pin is disabled.
 *  0b1..Wakeup pin is enabled and wakeup pin asserts if the RTC interrupt asserts or the wakeup pin is turned on.
 */
#define RTC_CR_WPE(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_WPE_SHIFT)) & RTC_CR_WPE_MASK)
#define RTC_CR_SUP_MASK (0x4U)
#define RTC_CR_SUP_SHIFT (2U)
/*! SUP - Supervisor Access
 *  0b0..Non-supervisor mode write accesses are not supported and generate a bus error.
 *  0b1..Non-supervisor mode write accesses are supported.
 */
#define RTC_CR_SUP(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_SUP_SHIFT)) & RTC_CR_SUP_MASK)
#define RTC_CR_UM_MASK (0x8U)
#define RTC_CR_UM_SHIFT (3U)
/*! UM - Update Mode
 *  0b0..Registers cannot be written when locked.
 *  0b1..Registers can be written when locked under limited conditions.
 */
#define RTC_CR_UM(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_UM_SHIFT)) & RTC_CR_UM_MASK)
#define RTC_CR_WPS_MASK (0x10U)
#define RTC_CR_WPS_SHIFT (4U)
/*! WPS - Wakeup Pin Select
 *  0b0..Wakeup pin asserts (active low, open drain) if the RTC interrupt asserts or the wakeup pin is turned on.
 *  0b1..Wakeup pin instead outputs the RTC 32kHz clock, provided the wakeup pin is turned on and the 32kHz clock is
 * output to other peripherals.
 */
#define RTC_CR_WPS(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_WPS_SHIFT)) & RTC_CR_WPS_MASK)
#define RTC_CR_CPS_MASK (0x20U)
#define RTC_CR_CPS_SHIFT (5U)
/*! CPS - Clock Pin Select
 *  0b0..The prescaler output clock (as configured by TSIC) is output on RTC_CLKOUT.
 *  0b1..The RTC 32kHz crystal clock is output on RTC_CLKOUT.
 */
#define RTC_CR_CPS(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_CPS_SHIFT)) & RTC_CR_CPS_MASK)
#define RTC_CR_LPOS_MASK (0x80U)
#define RTC_CR_LPOS_SHIFT (7U)
/*! LPOS - LPO Select
 *  0b0..RTC prescaler increments using 32kHz crystal.
 *  0b1..RTC prescaler increments using 1kHz LPO, bits [4:0] of the prescaler are bypassed.
 */
#define RTC_CR_LPOS(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_LPOS_SHIFT)) & RTC_CR_LPOS_MASK)
#define RTC_CR_OSCE_MASK (0x100U)
#define RTC_CR_OSCE_SHIFT (8U)
/*! OSCE - Oscillator Enable
 *  0b0..32.768 kHz oscillator is disabled.
 *  0b1..32.768 kHz oscillator is enabled. After setting this bit, wait the oscillator startup time before
 *       enabling the time counter to allow the 32.768 kHz clock time to stabilize.
 */
#define RTC_CR_OSCE(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_OSCE_SHIFT)) & RTC_CR_OSCE_MASK)
#define RTC_CR_CLKO_MASK (0x200U)
#define RTC_CR_CLKO_SHIFT (9U)
/*! CLKO - Clock Output
 *  0b0..The 32 kHz clock is output to other peripherals.
 *  0b1..The 32 kHz clock is not output to other peripherals.
 */
#define RTC_CR_CLKO(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_CLKO_SHIFT)) & RTC_CR_CLKO_MASK)
#define RTC_CR_SC16P_MASK (0x400U)
#define RTC_CR_SC16P_SHIFT (10U)
/*! SC16P - Oscillator 16pF Load Configure
 *  0b0..Disable the load.
 *  0b1..Enable the additional load.
 */
#define RTC_CR_SC16P(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_SC16P_SHIFT)) & RTC_CR_SC16P_MASK)
#define RTC_CR_SC8P_MASK (0x800U)
#define RTC_CR_SC8P_SHIFT (11U)
/*! SC8P - Oscillator 8pF Load Configure
 *  0b0..Disable the load.
 *  0b1..Enable the additional load.
 */
#define RTC_CR_SC8P(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_SC8P_SHIFT)) & RTC_CR_SC8P_MASK)
#define RTC_CR_SC4P_MASK (0x1000U)
#define RTC_CR_SC4P_SHIFT (12U)
/*! SC4P - Oscillator 4pF Load Configure
 *  0b0..Disable the load.
 *  0b1..Enable the additional load.
 */
#define RTC_CR_SC4P(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_SC4P_SHIFT)) & RTC_CR_SC4P_MASK)
#define RTC_CR_SC2P_MASK (0x2000U)
#define RTC_CR_SC2P_SHIFT (13U)
/*! SC2P - Oscillator 2pF Load Configure
 *  0b0..Disable the load.
 *  0b1..Enable the additional load.
 */
#define RTC_CR_SC2P(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_SC2P_SHIFT)) & RTC_CR_SC2P_MASK)
#define RTC_CR_CPE_MASK (0x3000000U)
#define RTC_CR_CPE_SHIFT (24U)
/*! CPE - Clock Pin Enable
 *  0b00..RTC_CLKOUT is disabled.
 *  0b01..RTC_CLKOUT is enabled on pin PTE0.
 *  0b10..RTC_CLKOUT is enabled on pin PTE26.
 *  0b11..Reserved.
 */
#define RTC_CR_CPE(x) (((uint32_t)(((uint32_t)(x)) << RTC_CR_CPE_SHIFT)) & RTC_CR_CPE_MASK)
/*! @} */

/*! @name SR - RTC Status Register */
/*! @{ */
#define RTC_SR_TIF_MASK (0x1U)
#define RTC_SR_TIF_SHIFT (0U)
/*! TIF - Time Invalid Flag
 *  0b0..Time is valid.
 *  0b1..Time is invalid and time counter is read as zero.
 */
#define RTC_SR_TIF(x) (((uint32_t)(((uint32_t)(x)) << RTC_SR_TIF_SHIFT)) & RTC_SR_TIF_MASK)
#define RTC_SR_TOF_MASK (0x2U)
#define RTC_SR_TOF_SHIFT (1U)
/*! TOF - Time Overflow Flag
 *  0b0..Time overflow has not occurred.
 *  0b1..Time overflow has occurred and time counter is read as zero.
 */
#define RTC_SR_TOF(x) (((uint32_t)(((uint32_t)(x)) << RTC_SR_TOF_SHIFT)) & RTC_SR_TOF_MASK)
#define RTC_SR_TAF_MASK (0x4U)
#define RTC_SR_TAF_SHIFT (2U)
/*! TAF - Time Alarm Flag
 *  0b0..Time alarm has not occurred.
 *  0b1..Time alarm has occurred.
 */
#define RTC_SR_TAF(x) (((uint32_t)(((uint32_t)(x)) << RTC_SR_TAF_SHIFT)) & RTC_SR_TAF_MASK)
#define RTC_SR_TCE_MASK (0x10U)
#define RTC_SR_TCE_SHIFT (4U)
/*! TCE - Time Counter Enable
 *  0b0..Time counter is disabled.
 *  0b1..Time counter is enabled.
 */
#define RTC_SR_TCE(x) (((uint32_t)(((uint32_t)(x)) << RTC_SR_TCE_SHIFT)) & RTC_SR_TCE_MASK)
/*! @} */

/*! @name LR - RTC Lock Register */
/*! @{ */
#define RTC_LR_TCL_MASK (0x8U)
#define RTC_LR_TCL_SHIFT (3U)
/*! TCL - Time Compensation Lock
 *  0b0..Time Compensation Register is locked and writes are ignored.
 *  0b1..Time Compensation Register is not locked and writes complete as normal.
 */
#define RTC_LR_TCL(x) (((uint32_t)(((uint32_t)(x)) << RTC_LR_TCL_SHIFT)) & RTC_LR_TCL_MASK)
#define RTC_LR_CRL_MASK (0x10U)
#define RTC_LR_CRL_SHIFT (4U)
/*! CRL - Control Register Lock
 *  0b0..Control Register is locked and writes are ignored.
 *  0b1..Control Register is not locked and writes complete as normal.
 */
#define RTC_LR_CRL(x) (((uint32_t)(((uint32_t)(x)) << RTC_LR_CRL_SHIFT)) & RTC_LR_CRL_MASK)
#define RTC_LR_SRL_MASK (0x20U)
#define RTC_LR_SRL_SHIFT (5U)
/*! SRL - Status Register Lock
 *  0b0..Status Register is locked and writes are ignored.
 *  0b1..Status Register is not locked and writes complete as normal.
 */
#define RTC_LR_SRL(x) (((uint32_t)(((uint32_t)(x)) << RTC_LR_SRL_SHIFT)) & RTC_LR_SRL_MASK)
#define RTC_LR_LRL_MASK (0x40U)
#define RTC_LR_LRL_SHIFT (6U)
/*! LRL - Lock Register Lock
 *  0b0..Lock Register is locked and writes are ignored.
 *  0b1..Lock Register is not locked and writes complete as normal.
 */
#define RTC_LR_LRL(x) (((uint32_t)(((uint32_t)(x)) << RTC_LR_LRL_SHIFT)) & RTC_LR_LRL_MASK)
/*! @} */

/*! @name IER - RTC Interrupt Enable Register */
/*! @{ */
#define RTC_IER_TIIE_MASK (0x1U)
#define RTC_IER_TIIE_SHIFT (0U)
/*! TIIE - Time Invalid Interrupt Enable
 *  0b0..Time invalid flag does not generate an interrupt.
 *  0b1..Time invalid flag does generate an interrupt.
 */
#define RTC_IER_TIIE(x) (((uint32_t)(((uint32_t)(x)) << RTC_IER_TIIE_SHIFT)) & RTC_IER_TIIE_MASK)
#define RTC_IER_TOIE_MASK (0x2U)
#define RTC_IER_TOIE_SHIFT (1U)
/*! TOIE - Time Overflow Interrupt Enable
 *  0b0..Time overflow flag does not generate an interrupt.
 *  0b1..Time overflow flag does generate an interrupt.
 */
#define RTC_IER_TOIE(x) (((uint32_t)(((uint32_t)(x)) << RTC_IER_TOIE_SHIFT)) & RTC_IER_TOIE_MASK)
#define RTC_IER_TAIE_MASK (0x4U)
#define RTC_IER_TAIE_SHIFT (2U)
/*! TAIE - Time Alarm Interrupt Enable
 *  0b0..Time alarm flag does not generate an interrupt.
 *  0b1..Time alarm flag does generate an interrupt.
 */
#define RTC_IER_TAIE(x) (((uint32_t)(((uint32_t)(x)) << RTC_IER_TAIE_SHIFT)) & RTC_IER_TAIE_MASK)
#define RTC_IER_TSIE_MASK (0x10U)
#define RTC_IER_TSIE_SHIFT (4U)
/*! TSIE - Time Seconds Interrupt Enable
 *  0b0..Seconds interrupt is disabled.
 *  0b1..Seconds interrupt is enabled.
 */
#define RTC_IER_TSIE(x) (((uint32_t)(((uint32_t)(x)) << RTC_IER_TSIE_SHIFT)) & RTC_IER_TSIE_MASK)
#define RTC_IER_WPON_MASK (0x80U)
#define RTC_IER_WPON_SHIFT (7U)
/*! WPON - Wakeup Pin On
 *  0b0..No effect.
 *  0b1..If the wakeup pin is enabled, then the wakeup pin will assert.
 */
#define RTC_IER_WPON(x) (((uint32_t)(((uint32_t)(x)) << RTC_IER_WPON_SHIFT)) & RTC_IER_WPON_MASK)
#define RTC_IER_TSIC_MASK (0x70000U)
#define RTC_IER_TSIC_SHIFT (16U)
/*! TSIC - Timer Seconds Interrupt Configuration
 *  0b000..1 Hz.
 *  0b001..2 Hz.
 *  0b010..4 Hz.
 *  0b011..8 Hz.
 *  0b100..16 Hz.
 *  0b101..32 Hz.
 *  0b110..64 Hz.
 *  0b111..128 Hz.
 */
#define RTC_IER_TSIC(x) (((uint32_t)(((uint32_t)(x)) << RTC_IER_TSIC_SHIFT)) & RTC_IER_TSIC_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group RTC_Register_Masks */

/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base address */
#define RTC_BASE (0x40038000u)
/** Peripheral RTC base pointer */
#define RTC ((RTC_Type *)RTC_BASE)
/** Array initializer of RTC peripheral base addresses */
#define RTC_BASE_ADDRS \
    {                  \
        RTC_BASE       \
    }
/** Array initializer of RTC peripheral base pointers */
#define RTC_BASE_PTRS \
    {                 \
        RTC           \
    }
/** Interrupt vectors for the RTC peripheral type */
#define RTC_IRQS \
    {            \
        RTC_IRQn \
    }
#define RTC_SECONDS_IRQS \
    {                    \
        RTC_Seconds_IRQn \
    }

/*!
 * @}
 */ /* end of group RTC_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- SCG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCG_Peripheral_Access_Layer SCG Peripheral Access Layer
 * @{
 */

/** SCG - Register Layout Typedef */
typedef struct
{
    __I uint32_t VERID; /**< Version ID Register, offset: 0x0 */
    __I uint32_t PARAM; /**< Parameter Register, offset: 0x4 */
    uint8_t RESERVED_0[8];
    __I uint32_t CSR;         /**< Clock Status Register, offset: 0x10 */
    __IO uint32_t RCCR;       /**< Run Clock Control Register, offset: 0x14 */
    __IO uint32_t VCCR;       /**< VLPR Clock Control Register, offset: 0x18 */
    __IO uint32_t HCCR;       /**< HSRUN Clock Control Register, offset: 0x1C */
    __IO uint32_t CLKOUTCNFG; /**< SCG CLKOUT Configuration Register, offset: 0x20 */
    uint8_t RESERVED_1[220];
    __IO uint32_t SOSCCSR; /**< System OSC Control Status Register, offset: 0x100 */
    __IO uint32_t SOSCDIV; /**< System OSC Divide Register, offset: 0x104 */
    __IO uint32_t SOSCCFG; /**< System Oscillator Configuration Register, offset: 0x108 */
    uint8_t RESERVED_2[244];
    __IO uint32_t SIRCCSR; /**< Slow IRC Control Status Register, offset: 0x200 */
    __IO uint32_t SIRCDIV; /**< Slow IRC Divide Register, offset: 0x204 */
    __IO uint32_t SIRCCFG; /**< Slow IRC Configuration Register, offset: 0x208 */
    uint8_t RESERVED_3[244];
    __IO uint32_t FIRCCSR;  /**< Fast IRC Control Status Register, offset: 0x300 */
    __IO uint32_t FIRCDIV;  /**< Fast IRC Divide Register, offset: 0x304 */
    __IO uint32_t FIRCCFG;  /**< Fast IRC Configuration Register, offset: 0x308 */
    __IO uint32_t FIRCTCFG; /**< Fast IRC Trim Configuration Register, offset: 0x30C */
    uint8_t RESERVED_4[8];
    __IO uint32_t FIRCSTAT; /**< Fast IRC Status Register, offset: 0x318 */
    uint8_t RESERVED_5[740];
    __IO uint32_t SPLLCSR; /**< System PLL Control Status Register, offset: 0x600 */
    __IO uint32_t SPLLDIV; /**< System PLL Divide Register, offset: 0x604 */
    __IO uint32_t SPLLCFG; /**< System PLL Configuration Register, offset: 0x608 */
} SCG_Type;

/* ----------------------------------------------------------------------------
   -- SCG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCG_Register_Masks SCG Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */
#define SCG_VERID_VERSION_MASK (0xFFFFFFFFU)
#define SCG_VERID_VERSION_SHIFT (0U)
/*! VERSION - SCG Version Number
 */
#define SCG_VERID_VERSION(x) (((uint32_t)(((uint32_t)(x)) << SCG_VERID_VERSION_SHIFT)) & SCG_VERID_VERSION_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */
#define SCG_PARAM_CLKPRES_MASK (0xFFU)
#define SCG_PARAM_CLKPRES_SHIFT (0U)
/*! CLKPRES - Clock Present
 */
#define SCG_PARAM_CLKPRES(x) (((uint32_t)(((uint32_t)(x)) << SCG_PARAM_CLKPRES_SHIFT)) & SCG_PARAM_CLKPRES_MASK)
#define SCG_PARAM_DIVPRES_MASK (0xF8000000U)
#define SCG_PARAM_DIVPRES_SHIFT (27U)
/*! DIVPRES - Divider Present
 */
#define SCG_PARAM_DIVPRES(x) (((uint32_t)(((uint32_t)(x)) << SCG_PARAM_DIVPRES_SHIFT)) & SCG_PARAM_DIVPRES_MASK)
/*! @} */

/*! @name CSR - Clock Status Register */
/*! @{ */
#define SCG_CSR_DIVSLOW_MASK (0xFU)
#define SCG_CSR_DIVSLOW_SHIFT (0U)
/*! DIVSLOW - Slow Clock Divide Ratio
 *  0b0000..Divide-by-1
 *  0b0001..Divide-by-2
 *  0b0010..Divide-by-3
 *  0b0011..Divide-by-4
 *  0b0100..Divide-by-5
 *  0b0101..Divide-by-6
 *  0b0110..Divide-by-7
 *  0b0111..Divide-by-8
 *  0b1000..Divide-by-9
 *  0b1001..Divide-by-10
 *  0b1010..Divide-by-11
 *  0b1011..Divide-by-12
 *  0b1100..Divide-by-13
 *  0b1101..Divide-by-14
 *  0b1110..Divide-by-15
 *  0b1111..Divide-by-16
 */
#define SCG_CSR_DIVSLOW(x) (((uint32_t)(((uint32_t)(x)) << SCG_CSR_DIVSLOW_SHIFT)) & SCG_CSR_DIVSLOW_MASK)
#define SCG_CSR_DIVCORE_MASK (0xF0000U)
#define SCG_CSR_DIVCORE_SHIFT (16U)
/*! DIVCORE - Core Clock Divide Ratio
 *  0b0000..Divide-by-1
 *  0b0001..Divide-by-2
 *  0b0010..Divide-by-3
 *  0b0011..Divide-by-4
 *  0b0100..Divide-by-5
 *  0b0101..Divide-by-6
 *  0b0110..Divide-by-7
 *  0b0111..Divide-by-8
 *  0b1000..Divide-by-9
 *  0b1001..Divide-by-10
 *  0b1010..Divide-by-11
 *  0b1011..Divide-by-12
 *  0b1100..Divide-by-13
 *  0b1101..Divide-by-14
 *  0b1110..Divide-by-15
 *  0b1111..Divide-by-16
 */
#define SCG_CSR_DIVCORE(x) (((uint32_t)(((uint32_t)(x)) << SCG_CSR_DIVCORE_SHIFT)) & SCG_CSR_DIVCORE_MASK)
#define SCG_CSR_SCS_MASK (0xF000000U)
#define SCG_CSR_SCS_SHIFT (24U)
/*! SCS - System Clock Source
 *  0b0000..Reserved
 *  0b0001..System OSC (SOSC_CLK)
 *  0b0010..Slow IRC (SIRC_CLK)
 *  0b0011..Fast IRC (FIRC_CLK)
 *  0b0100..Reserved
 *  0b0101..Reserved
 *  0b0110..System PLL (SPLL_CLK)
 *  0b0111..Reserved
 */
#define SCG_CSR_SCS(x) (((uint32_t)(((uint32_t)(x)) << SCG_CSR_SCS_SHIFT)) & SCG_CSR_SCS_MASK)
/*! @} */

/*! @name RCCR - Run Clock Control Register */
/*! @{ */
#define SCG_RCCR_DIVSLOW_MASK (0xFU)
#define SCG_RCCR_DIVSLOW_SHIFT (0U)
/*! DIVSLOW - Slow Clock Divide Ratio
 *  0b0000..Divide-by-1
 *  0b0001..Divide-by-2
 *  0b0010..Divide-by-3
 *  0b0011..Divide-by-4
 *  0b0100..Divide-by-5
 *  0b0101..Divide-by-6
 *  0b0110..Divide-by-7
 *  0b0111..Divide-by-8
 *  0b1000..Divide-by-9
 *  0b1001..Divide-by-10
 *  0b1010..Divide-by-11
 *  0b1011..Divide-by-12
 *  0b1100..Divide-by-13
 *  0b1101..Divide-by-14
 *  0b1110..Divide-by-15
 *  0b1111..Divide-by-16
 */
#define SCG_RCCR_DIVSLOW(x) (((uint32_t)(((uint32_t)(x)) << SCG_RCCR_DIVSLOW_SHIFT)) & SCG_RCCR_DIVSLOW_MASK)
#define SCG_RCCR_DIVCORE_MASK (0xF0000U)
#define SCG_RCCR_DIVCORE_SHIFT (16U)
/*! DIVCORE - Core Clock Divide Ratio
 *  0b0000..Divide-by-1
 *  0b0001..Divide-by-2
 *  0b0010..Divide-by-3
 *  0b0011..Divide-by-4
 *  0b0100..Divide-by-5
 *  0b0101..Divide-by-6
 *  0b0110..Divide-by-7
 *  0b0111..Divide-by-8
 *  0b1000..Divide-by-9
 *  0b1001..Divide-by-10
 *  0b1010..Divide-by-11
 *  0b1011..Divide-by-12
 *  0b1100..Divide-by-13
 *  0b1101..Divide-by-14
 *  0b1110..Divide-by-15
 *  0b1111..Divide-by-16
 */
#define SCG_RCCR_DIVCORE(x) (((uint32_t)(((uint32_t)(x)) << SCG_RCCR_DIVCORE_SHIFT)) & SCG_RCCR_DIVCORE_MASK)
#define SCG_RCCR_SCS_MASK (0xF000000U)
#define SCG_RCCR_SCS_SHIFT (24U)
/*! SCS - System Clock Source
 *  0b0000..Reserved
 *  0b0001..System OSC (SOSC_CLK)
 *  0b0010..Slow IRC (SIRC_CLK)
 *  0b0011..Fast IRC (FIRC_CLK)
 *  0b0100..Reserved
 *  0b0101..Reserved
 *  0b0110..System PLL (SPLL_CLK)
 *  0b0111..Reserved
 */
#define SCG_RCCR_SCS(x) (((uint32_t)(((uint32_t)(x)) << SCG_RCCR_SCS_SHIFT)) & SCG_RCCR_SCS_MASK)
/*! @} */

/*! @name VCCR - VLPR Clock Control Register */
/*! @{ */
#define SCG_VCCR_DIVSLOW_MASK (0xFU)
#define SCG_VCCR_DIVSLOW_SHIFT (0U)
/*! DIVSLOW - Slow Clock Divide Ratio
 *  0b0000..Divide-by-1
 *  0b0001..Divide-by-2
 *  0b0010..Divide-by-3
 *  0b0011..Divide-by-4
 *  0b0100..Divide-by-5
 *  0b0101..Divide-by-6
 *  0b0110..Divide-by-7
 *  0b0111..Divide-by-8
 *  0b1000..Divide-by-9
 *  0b1001..Divide-by-10
 *  0b1010..Divide-by-11
 *  0b1011..Divide-by-12
 *  0b1100..Divide-by-13
 *  0b1101..Divide-by-14
 *  0b1110..Divide-by-15
 *  0b1111..Divide-by-16
 */
#define SCG_VCCR_DIVSLOW(x) (((uint32_t)(((uint32_t)(x)) << SCG_VCCR_DIVSLOW_SHIFT)) & SCG_VCCR_DIVSLOW_MASK)
#define SCG_VCCR_DIVCORE_MASK (0xF0000U)
#define SCG_VCCR_DIVCORE_SHIFT (16U)
/*! DIVCORE - Core Clock Divide Ratio
 *  0b0000..Divide-by-1
 *  0b0001..Divide-by-2
 *  0b0010..Divide-by-3
 *  0b0011..Divide-by-4
 *  0b0100..Divide-by-5
 *  0b0101..Divide-by-6
 *  0b0110..Divide-by-7
 *  0b0111..Divide-by-8
 *  0b1000..Divide-by-9
 *  0b1001..Divide-by-10
 *  0b1010..Divide-by-11
 *  0b1011..Divide-by-12
 *  0b1100..Divide-by-13
 *  0b1101..Divide-by-14
 *  0b1110..Divide-by-15
 *  0b1111..Divide-by-16
 */
#define SCG_VCCR_DIVCORE(x) (((uint32_t)(((uint32_t)(x)) << SCG_VCCR_DIVCORE_SHIFT)) & SCG_VCCR_DIVCORE_MASK)
#define SCG_VCCR_SCS_MASK (0xF000000U)
#define SCG_VCCR_SCS_SHIFT (24U)
/*! SCS - System Clock Source
 *  0b0000..Reserved
 *  0b0001..System OSC (SOSC_CLK)
 *  0b0010..Slow IRC (SIRC_CLK)
 *  0b0011..Reserved
 *  0b0100..Reserved
 *  0b0101..Reserved
 *  0b0110..Reserved
 *  0b0111..Reserved
 */
#define SCG_VCCR_SCS(x) (((uint32_t)(((uint32_t)(x)) << SCG_VCCR_SCS_SHIFT)) & SCG_VCCR_SCS_MASK)
/*! @} */

/*! @name HCCR - HSRUN Clock Control Register */
/*! @{ */
#define SCG_HCCR_DIVSLOW_MASK (0xFU)
#define SCG_HCCR_DIVSLOW_SHIFT (0U)
/*! DIVSLOW - Slow Clock Divide Ratio
 *  0b0000..Divide-by-1
 *  0b0001..Divide-by-2
 *  0b0010..Divide-by-3
 *  0b0011..Divide-by-4
 *  0b0100..Divide-by-5
 *  0b0101..Divide-by-6
 *  0b0110..Divide-by-7
 *  0b0111..Divide-by-8
 *  0b1000..Divide-by-9
 *  0b1001..Divide-by-10
 *  0b1010..Divide-by-11
 *  0b1011..Divide-by-12
 *  0b1100..Divide-by-13
 *  0b1101..Divide-by-14
 *  0b1110..Divide-by-15
 *  0b1111..Divide-by-16
 */
#define SCG_HCCR_DIVSLOW(x) (((uint32_t)(((uint32_t)(x)) << SCG_HCCR_DIVSLOW_SHIFT)) & SCG_HCCR_DIVSLOW_MASK)
#define SCG_HCCR_DIVCORE_MASK (0xF0000U)
#define SCG_HCCR_DIVCORE_SHIFT (16U)
/*! DIVCORE - Core Clock Divide Ratio
 *  0b0000..Divide-by-1
 *  0b0001..Divide-by-2
 *  0b0010..Divide-by-3
 *  0b0011..Divide-by-4
 *  0b0100..Divide-by-5
 *  0b0101..Divide-by-6
 *  0b0110..Divide-by-7
 *  0b0111..Divide-by-8
 *  0b1000..Divide-by-9
 *  0b1001..Divide-by-10
 *  0b1010..Divide-by-11
 *  0b1011..Divide-by-12
 *  0b1100..Divide-by-13
 *  0b1101..Divide-by-14
 *  0b1110..Divide-by-15
 *  0b1111..Divide-by-16
 */
#define SCG_HCCR_DIVCORE(x) (((uint32_t)(((uint32_t)(x)) << SCG_HCCR_DIVCORE_SHIFT)) & SCG_HCCR_DIVCORE_MASK)
#define SCG_HCCR_SCS_MASK (0xF000000U)
#define SCG_HCCR_SCS_SHIFT (24U)
/*! SCS - System Clock Source
 *  0b0000..Reserved
 *  0b0001..System OSC (SOSC_CLK)
 *  0b0010..Slow IRC (SIRC_CLK)
 *  0b0011..Fast IRC (FIRC_CLK)
 *  0b0100..Reserved
 *  0b0101..Reserved
 *  0b0110..System PLL (SPLL_CLK)
 *  0b0111..Reserved
 */
#define SCG_HCCR_SCS(x) (((uint32_t)(((uint32_t)(x)) << SCG_HCCR_SCS_SHIFT)) & SCG_HCCR_SCS_MASK)
/*! @} */

/*! @name CLKOUTCNFG - SCG CLKOUT Configuration Register */
/*! @{ */
#define SCG_CLKOUTCNFG_CLKOUTSEL_MASK (0xF000000U)
#define SCG_CLKOUTCNFG_CLKOUTSEL_SHIFT (24U)
/*! CLKOUTSEL - SCG Clkout Select
 *  0b0000..SCG SLOW Clock
 *  0b0001..System OSC (SOSC_CLK)
 *  0b0010..Slow IRC (SIRC_CLK)
 *  0b0011..Fast IRC (FIRC_CLK)
 *  0b0100..Reserved
 *  0b0101..Reserved
 *  0b0110..System PLL (SPLL_CLK)
 *  0b0111..Reserved
 *  0b1111..Reserved
 */
#define SCG_CLKOUTCNFG_CLKOUTSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_CLKOUTCNFG_CLKOUTSEL_SHIFT)) & SCG_CLKOUTCNFG_CLKOUTSEL_MASK)
/*! @} */

/*! @name SOSCCSR - System OSC Control Status Register */
/*! @{ */
#define SCG_SOSCCSR_SOSCEN_MASK (0x1U)
#define SCG_SOSCCSR_SOSCEN_SHIFT (0U)
/*! SOSCEN - System OSC Enable
 *  0b0..System OSC is disabled
 *  0b1..System OSC is enabled
 */
#define SCG_SOSCCSR_SOSCEN(x) (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCSR_SOSCEN_SHIFT)) & SCG_SOSCCSR_SOSCEN_MASK)
#define SCG_SOSCCSR_SOSCSTEN_MASK (0x2U)
#define SCG_SOSCCSR_SOSCSTEN_SHIFT (1U)
/*! SOSCSTEN - System OSC Stop Enable
 *  0b0..System OSC is disabled in Stop modes
 *  0b1..System OSC is enabled in Stop modes if SOSCEN=1. In VLLS0, system oscillator is disabled even if SOSCSTEN=1 and
 * SOSCEN=1.
 */
#define SCG_SOSCCSR_SOSCSTEN(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCSR_SOSCSTEN_SHIFT)) & SCG_SOSCCSR_SOSCSTEN_MASK)
#define SCG_SOSCCSR_SOSCLPEN_MASK (0x4U)
#define SCG_SOSCCSR_SOSCLPEN_SHIFT (2U)
/*! SOSCLPEN - System OSC Low Power Enable
 *  0b0..System OSC is disabled in VLP modes
 *  0b1..System OSC is enabled in VLP modes
 */
#define SCG_SOSCCSR_SOSCLPEN(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCSR_SOSCLPEN_SHIFT)) & SCG_SOSCCSR_SOSCLPEN_MASK)
#define SCG_SOSCCSR_SOSCERCLKEN_MASK (0x8U)
#define SCG_SOSCCSR_SOSCERCLKEN_SHIFT (3U)
/*! SOSCERCLKEN - System OSC 3V ERCLK Enable
 *  0b0..System OSC 3V ERCLK output clock is disabled.
 *  0b1..System OSC 3V ERCLK output clock is enabled when SYSOSC is enabled.
 */
#define SCG_SOSCCSR_SOSCERCLKEN(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCSR_SOSCERCLKEN_SHIFT)) & SCG_SOSCCSR_SOSCERCLKEN_MASK)
#define SCG_SOSCCSR_SOSCCM_MASK (0x10000U)
#define SCG_SOSCCSR_SOSCCM_SHIFT (16U)
/*! SOSCCM - System OSC Clock Monitor
 *  0b0..System OSC Clock Monitor is disabled
 *  0b1..System OSC Clock Monitor is enabled
 */
#define SCG_SOSCCSR_SOSCCM(x) (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCSR_SOSCCM_SHIFT)) & SCG_SOSCCSR_SOSCCM_MASK)
#define SCG_SOSCCSR_SOSCCMRE_MASK (0x20000U)
#define SCG_SOSCCSR_SOSCCMRE_SHIFT (17U)
/*! SOSCCMRE - System OSC Clock Monitor Reset Enable
 *  0b0..Clock Monitor generates interrupt when error detected
 *  0b1..Clock Monitor generates reset when error detected
 */
#define SCG_SOSCCSR_SOSCCMRE(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCSR_SOSCCMRE_SHIFT)) & SCG_SOSCCSR_SOSCCMRE_MASK)
#define SCG_SOSCCSR_LK_MASK (0x800000U)
#define SCG_SOSCCSR_LK_SHIFT (23U)
/*! LK - Lock Register
 *  0b0..This Control Status Register can be written.
 *  0b1..This Control Status Register cannot be written.
 */
#define SCG_SOSCCSR_LK(x) (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCSR_LK_SHIFT)) & SCG_SOSCCSR_LK_MASK)
#define SCG_SOSCCSR_SOSCVLD_MASK (0x1000000U)
#define SCG_SOSCCSR_SOSCVLD_SHIFT (24U)
/*! SOSCVLD - System OSC Valid
 *  0b0..System OSC is not enabled or clock is not valid
 *  0b1..System OSC is enabled and output clock is valid
 */
#define SCG_SOSCCSR_SOSCVLD(x) (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCSR_SOSCVLD_SHIFT)) & SCG_SOSCCSR_SOSCVLD_MASK)
#define SCG_SOSCCSR_SOSCSEL_MASK (0x2000000U)
#define SCG_SOSCCSR_SOSCSEL_SHIFT (25U)
/*! SOSCSEL - System OSC Selected
 *  0b0..System OSC is not the system clock source
 *  0b1..System OSC is the system clock source
 */
#define SCG_SOSCCSR_SOSCSEL(x) (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCSR_SOSCSEL_SHIFT)) & SCG_SOSCCSR_SOSCSEL_MASK)
#define SCG_SOSCCSR_SOSCERR_MASK (0x4000000U)
#define SCG_SOSCCSR_SOSCERR_SHIFT (26U)
/*! SOSCERR - System OSC Clock Error
 *  0b0..System OSC Clock Monitor is disabled or has not detected an error
 *  0b1..System OSC Clock Monitor is enabled and detected an error
 */
#define SCG_SOSCCSR_SOSCERR(x) (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCSR_SOSCERR_SHIFT)) & SCG_SOSCCSR_SOSCERR_MASK)
/*! @} */

/*! @name SOSCDIV - System OSC Divide Register */
/*! @{ */
#define SCG_SOSCDIV_SOSCDIV1_MASK (0x7U)
#define SCG_SOSCDIV_SOSCDIV1_SHIFT (0U)
/*! SOSCDIV1 - System OSC Clock Divide 1
 *  0b000..Output disabled
 *  0b001..Divide by 1
 *  0b010..Divide by 2
 *  0b011..Divide by 4
 *  0b100..Divide by 8
 *  0b101..Divide by 16
 *  0b110..Divide by 32
 *  0b111..Divide by 64
 */
#define SCG_SOSCDIV_SOSCDIV1(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SOSCDIV_SOSCDIV1_SHIFT)) & SCG_SOSCDIV_SOSCDIV1_MASK)
#define SCG_SOSCDIV_SOSCDIV2_MASK (0x700U)
#define SCG_SOSCDIV_SOSCDIV2_SHIFT (8U)
/*! SOSCDIV2 - System OSC Clock Divide 2
 *  0b000..Output disabled
 *  0b001..Divide by 1
 *  0b010..Divide by 2
 *  0b011..Divide by 4
 *  0b100..Divide by 8
 *  0b101..Divide by 16
 *  0b110..Divide by 32
 *  0b111..Divide by 64
 */
#define SCG_SOSCDIV_SOSCDIV2(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SOSCDIV_SOSCDIV2_SHIFT)) & SCG_SOSCDIV_SOSCDIV2_MASK)
#define SCG_SOSCDIV_SOSCDIV3_MASK (0x70000U)
#define SCG_SOSCDIV_SOSCDIV3_SHIFT (16U)
/*! SOSCDIV3 - System OSC Clock Divide 3
 *  0b000..Output disabled
 *  0b001..Divide by 1
 *  0b010..Divide by 2
 *  0b011..Divide by 4
 *  0b100..Divide by 8
 *  0b101..Divide by 16
 *  0b110..Divide by 32
 *  0b111..Divide by 64
 */
#define SCG_SOSCDIV_SOSCDIV3(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SOSCDIV_SOSCDIV3_SHIFT)) & SCG_SOSCDIV_SOSCDIV3_MASK)
/*! @} */

/*! @name SOSCCFG - System Oscillator Configuration Register */
/*! @{ */
#define SCG_SOSCCFG_EREFS_MASK (0x4U)
#define SCG_SOSCCFG_EREFS_SHIFT (2U)
/*! EREFS - External Reference Select
 *  0b0..External reference clock selected
 *  0b1..Internal crystal oscillator of OSC selected. In VLLS0, the internal oscillator of OSC is disabled even if
 * SOSCEN=1 and SOSCSTEN=1.
 */
#define SCG_SOSCCFG_EREFS(x) (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCFG_EREFS_SHIFT)) & SCG_SOSCCFG_EREFS_MASK)
#define SCG_SOSCCFG_HGO_MASK (0x8U)
#define SCG_SOSCCFG_HGO_SHIFT (3U)
/*! HGO - High Gain Oscillator Select
 *  0b0..Configure crystal oscillator for low-gain operation
 *  0b1..Configure crystal oscillator for high-gain operation
 */
#define SCG_SOSCCFG_HGO(x) (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCFG_HGO_SHIFT)) & SCG_SOSCCFG_HGO_MASK)
#define SCG_SOSCCFG_RANGE_MASK (0x30U)
#define SCG_SOSCCFG_RANGE_SHIFT (4U)
/*! RANGE - System OSC Range Select
 *  0b00..Reserved
 *  0b01..Low frequency range selected for the crystal oscillator
 *  0b10..Medium frequency range selected for the crytstal oscillator
 *  0b11..High frequency range selected for the crystal oscillator
 */
#define SCG_SOSCCFG_RANGE(x) (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCFG_RANGE_SHIFT)) & SCG_SOSCCFG_RANGE_MASK)
#define SCG_SOSCCFG_SC16P_MASK (0x100U)
#define SCG_SOSCCFG_SC16P_SHIFT (8U)
/*! SC16P - Oscillator 16 pF Capacitor Load
 */
#define SCG_SOSCCFG_SC16P(x) (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCFG_SC16P_SHIFT)) & SCG_SOSCCFG_SC16P_MASK)
#define SCG_SOSCCFG_SC8P_MASK (0x200U)
#define SCG_SOSCCFG_SC8P_SHIFT (9U)
/*! SC8P - Oscillator 8 pF Capacitor Load Configure
 */
#define SCG_SOSCCFG_SC8P(x) (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCFG_SC8P_SHIFT)) & SCG_SOSCCFG_SC8P_MASK)
#define SCG_SOSCCFG_SC4P_MASK (0x400U)
#define SCG_SOSCCFG_SC4P_SHIFT (10U)
/*! SC4P - Oscillator 4 pF Capacitor Load
 */
#define SCG_SOSCCFG_SC4P(x) (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCFG_SC4P_SHIFT)) & SCG_SOSCCFG_SC4P_MASK)
#define SCG_SOSCCFG_SC2P_MASK (0x800U)
#define SCG_SOSCCFG_SC2P_SHIFT (11U)
/*! SC2P - Oscillator 2 pF Capacitor Load
 */
#define SCG_SOSCCFG_SC2P(x) (((uint32_t)(((uint32_t)(x)) << SCG_SOSCCFG_SC2P_SHIFT)) & SCG_SOSCCFG_SC2P_MASK)
/*! @} */

/*! @name SIRCCSR - Slow IRC Control Status Register */
/*! @{ */
#define SCG_SIRCCSR_SIRCEN_MASK (0x1U)
#define SCG_SIRCCSR_SIRCEN_SHIFT (0U)
/*! SIRCEN - Slow IRC Enable
 *  0b0..Slow IRC is disabled
 *  0b1..Slow IRC is enabled
 */
#define SCG_SIRCCSR_SIRCEN(x) (((uint32_t)(((uint32_t)(x)) << SCG_SIRCCSR_SIRCEN_SHIFT)) & SCG_SIRCCSR_SIRCEN_MASK)
#define SCG_SIRCCSR_SIRCSTEN_MASK (0x2U)
#define SCG_SIRCCSR_SIRCSTEN_SHIFT (1U)
/*! SIRCSTEN - Slow IRC Stop Enable
 *  0b0..Slow IRC is disabled in supported Stop modes
 *  0b1..Slow IRC is enabled in supported Stop modes
 */
#define SCG_SIRCCSR_SIRCSTEN(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SIRCCSR_SIRCSTEN_SHIFT)) & SCG_SIRCCSR_SIRCSTEN_MASK)
#define SCG_SIRCCSR_SIRCLPEN_MASK (0x4U)
#define SCG_SIRCCSR_SIRCLPEN_SHIFT (2U)
/*! SIRCLPEN - Slow IRC Low Power Enable
 *  0b0..Slow IRC is disabled in VLP modes
 *  0b1..Slow IRC is enabled in VLP modes
 */
#define SCG_SIRCCSR_SIRCLPEN(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SIRCCSR_SIRCLPEN_SHIFT)) & SCG_SIRCCSR_SIRCLPEN_MASK)
#define SCG_SIRCCSR_LK_MASK (0x800000U)
#define SCG_SIRCCSR_LK_SHIFT (23U)
/*! LK - Lock Register
 *  0b0..Control Status Register can be written.
 *  0b1..Control Status Register cannot be written.
 */
#define SCG_SIRCCSR_LK(x) (((uint32_t)(((uint32_t)(x)) << SCG_SIRCCSR_LK_SHIFT)) & SCG_SIRCCSR_LK_MASK)
#define SCG_SIRCCSR_SIRCVLD_MASK (0x1000000U)
#define SCG_SIRCCSR_SIRCVLD_SHIFT (24U)
/*! SIRCVLD - Slow IRC Valid
 *  0b0..Slow IRC is not enabled or clock is not valid
 *  0b1..Slow IRC is enabled and output clock is valid
 */
#define SCG_SIRCCSR_SIRCVLD(x) (((uint32_t)(((uint32_t)(x)) << SCG_SIRCCSR_SIRCVLD_SHIFT)) & SCG_SIRCCSR_SIRCVLD_MASK)
#define SCG_SIRCCSR_SIRCSEL_MASK (0x2000000U)
#define SCG_SIRCCSR_SIRCSEL_SHIFT (25U)
/*! SIRCSEL - Slow IRC Selected
 *  0b0..Slow IRC is not the system clock source
 *  0b1..Slow IRC is the system clock source
 */
#define SCG_SIRCCSR_SIRCSEL(x) (((uint32_t)(((uint32_t)(x)) << SCG_SIRCCSR_SIRCSEL_SHIFT)) & SCG_SIRCCSR_SIRCSEL_MASK)
/*! @} */

/*! @name SIRCDIV - Slow IRC Divide Register */
/*! @{ */
#define SCG_SIRCDIV_SIRCDIV1_MASK (0x7U)
#define SCG_SIRCDIV_SIRCDIV1_SHIFT (0U)
/*! SIRCDIV1 - Slow IRC Clock Divide 1
 *  0b000..Output disabled
 *  0b001..Divide by 1
 *  0b010..Divide by 2
 *  0b011..Divide by 4
 *  0b100..Divide by 8
 *  0b101..Divide by 16
 *  0b110..Divide by 32
 *  0b111..Divide by 64
 */
#define SCG_SIRCDIV_SIRCDIV1(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SIRCDIV_SIRCDIV1_SHIFT)) & SCG_SIRCDIV_SIRCDIV1_MASK)
#define SCG_SIRCDIV_SIRCDIV2_MASK (0x700U)
#define SCG_SIRCDIV_SIRCDIV2_SHIFT (8U)
/*! SIRCDIV2 - Slow IRC Clock Divide 2
 *  0b000..Output disabled
 *  0b001..Divide by 1
 *  0b010..Divide by 2
 *  0b011..Divide by 4
 *  0b100..Divide by 8
 *  0b101..Divide by 16
 *  0b110..Divide by 32
 *  0b111..Divide by 64
 */
#define SCG_SIRCDIV_SIRCDIV2(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SIRCDIV_SIRCDIV2_SHIFT)) & SCG_SIRCDIV_SIRCDIV2_MASK)
#define SCG_SIRCDIV_SIRCDIV3_MASK (0x70000U)
#define SCG_SIRCDIV_SIRCDIV3_SHIFT (16U)
/*! SIRCDIV3 - Slow IRC Clock Divider 3
 *  0b000..Output disabled
 *  0b001..Divide by 1
 *  0b010..Divide by 2
 *  0b011..Divide by 4
 *  0b100..Divide by 8
 *  0b101..Divide by 16
 *  0b110..Divide by 32
 *  0b111..Divide by 64
 */
#define SCG_SIRCDIV_SIRCDIV3(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SIRCDIV_SIRCDIV3_SHIFT)) & SCG_SIRCDIV_SIRCDIV3_MASK)
/*! @} */

/*! @name SIRCCFG - Slow IRC Configuration Register */
/*! @{ */
#define SCG_SIRCCFG_RANGE_MASK (0x1U)
#define SCG_SIRCCFG_RANGE_SHIFT (0U)
/*! RANGE - Frequency Range
 *  0b0..Slow IRC low range clock (2 MHz)
 *  0b1..Slow IRC high range clock (8 MHz )
 */
#define SCG_SIRCCFG_RANGE(x) (((uint32_t)(((uint32_t)(x)) << SCG_SIRCCFG_RANGE_SHIFT)) & SCG_SIRCCFG_RANGE_MASK)
/*! @} */

/*! @name FIRCCSR - Fast IRC Control Status Register */
/*! @{ */
#define SCG_FIRCCSR_FIRCEN_MASK (0x1U)
#define SCG_FIRCCSR_FIRCEN_SHIFT (0U)
/*! FIRCEN - Fast IRC Enable
 *  0b0..Fast IRC is disabled
 *  0b1..Fast IRC is enabled
 */
#define SCG_FIRCCSR_FIRCEN(x) (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCSR_FIRCEN_SHIFT)) & SCG_FIRCCSR_FIRCEN_MASK)
#define SCG_FIRCCSR_FIRCSTEN_MASK (0x2U)
#define SCG_FIRCCSR_FIRCSTEN_SHIFT (1U)
/*! FIRCSTEN - Fast IRC Stop Enable
 *  0b0..Fast IRC is disabled in Stop modes. When selected as the reference clock to the System PLL and if the
 *       System PLL is enabled in STOP mode, the Fast IRC will stay enabled even if FIRCSTEN=0.
 *  0b1..Fast IRC is enabled in Stop modes
 */
#define SCG_FIRCCSR_FIRCSTEN(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCSR_FIRCSTEN_SHIFT)) & SCG_FIRCCSR_FIRCSTEN_MASK)
#define SCG_FIRCCSR_FIRCLPEN_MASK (0x4U)
#define SCG_FIRCCSR_FIRCLPEN_SHIFT (2U)
/*! FIRCLPEN - Fast IRC Low Power Enable
 *  0b0..Fast IRC is disabled in VLP modes
 *  0b1..Fast IRC is enabled in VLP modes
 */
#define SCG_FIRCCSR_FIRCLPEN(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCSR_FIRCLPEN_SHIFT)) & SCG_FIRCCSR_FIRCLPEN_MASK)
#define SCG_FIRCCSR_FIRCREGOFF_MASK (0x8U)
#define SCG_FIRCCSR_FIRCREGOFF_SHIFT (3U)
/*! FIRCREGOFF - Fast IRC Regulator Enable
 *  0b0..Fast IRC Regulator is enabled.
 *  0b1..Fast IRC Regulator is disabled.
 */
#define SCG_FIRCCSR_FIRCREGOFF(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCSR_FIRCREGOFF_SHIFT)) & SCG_FIRCCSR_FIRCREGOFF_MASK)
#define SCG_FIRCCSR_FIRCTREN_MASK (0x100U)
#define SCG_FIRCCSR_FIRCTREN_SHIFT (8U)
/*! FIRCTREN - Fast IRC Trim Enable
 *  0b0..Disable trimming Fast IRC to an external clock source
 *  0b1..Enable trimming Fast IRC to an external clock source
 */
#define SCG_FIRCCSR_FIRCTREN(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCSR_FIRCTREN_SHIFT)) & SCG_FIRCCSR_FIRCTREN_MASK)
#define SCG_FIRCCSR_FIRCTRUP_MASK (0x200U)
#define SCG_FIRCCSR_FIRCTRUP_SHIFT (9U)
/*! FIRCTRUP - Fast IRC Trim Update
 *  0b0..Disable Fast IRC trimming updates
 *  0b1..Enable Fast IRC trimming updates
 */
#define SCG_FIRCCSR_FIRCTRUP(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCSR_FIRCTRUP_SHIFT)) & SCG_FIRCCSR_FIRCTRUP_MASK)
#define SCG_FIRCCSR_LK_MASK (0x800000U)
#define SCG_FIRCCSR_LK_SHIFT (23U)
/*! LK - Lock Register
 *  0b0..Control Status Register can be written.
 *  0b1..Control Status Register cannot be written.
 */
#define SCG_FIRCCSR_LK(x) (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCSR_LK_SHIFT)) & SCG_FIRCCSR_LK_MASK)
#define SCG_FIRCCSR_FIRCVLD_MASK (0x1000000U)
#define SCG_FIRCCSR_FIRCVLD_SHIFT (24U)
/*! FIRCVLD - Fast IRC Valid status
 *  0b0..Fast IRC is not enabled or clock is not valid.
 *  0b1..Fast IRC is enabled and output clock is valid. The clock is valid once there is an output clock from the FIRC
 * analog.
 */
#define SCG_FIRCCSR_FIRCVLD(x) (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCSR_FIRCVLD_SHIFT)) & SCG_FIRCCSR_FIRCVLD_MASK)
#define SCG_FIRCCSR_FIRCSEL_MASK (0x2000000U)
#define SCG_FIRCCSR_FIRCSEL_SHIFT (25U)
/*! FIRCSEL - Fast IRC Selected status
 *  0b0..Fast IRC is not the system clock source
 *  0b1..Fast IRC is the system clock source
 */
#define SCG_FIRCCSR_FIRCSEL(x) (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCSR_FIRCSEL_SHIFT)) & SCG_FIRCCSR_FIRCSEL_MASK)
#define SCG_FIRCCSR_FIRCERR_MASK (0x4000000U)
#define SCG_FIRCCSR_FIRCERR_SHIFT (26U)
/*! FIRCERR - Fast IRC Clock Error
 *  0b0..Error not detected with the Fast IRC trimming.
 *  0b1..Error detected with the Fast IRC trimming.
 */
#define SCG_FIRCCSR_FIRCERR(x) (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCSR_FIRCERR_SHIFT)) & SCG_FIRCCSR_FIRCERR_MASK)
/*! @} */

/*! @name FIRCDIV - Fast IRC Divide Register */
/*! @{ */
#define SCG_FIRCDIV_FIRCDIV1_MASK (0x7U)
#define SCG_FIRCDIV_FIRCDIV1_SHIFT (0U)
/*! FIRCDIV1 - Fast IRC Clock Divide 1
 *  0b000..Output disabled
 *  0b001..Divide by 1
 *  0b010..Divide by 2
 *  0b011..Divide by 4
 *  0b100..Divide by 8
 *  0b101..Divide by 16
 *  0b110..Divide by 32
 *  0b111..Divide by 64
 */
#define SCG_FIRCDIV_FIRCDIV1(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_FIRCDIV_FIRCDIV1_SHIFT)) & SCG_FIRCDIV_FIRCDIV1_MASK)
#define SCG_FIRCDIV_FIRCDIV2_MASK (0x700U)
#define SCG_FIRCDIV_FIRCDIV2_SHIFT (8U)
/*! FIRCDIV2 - Fast IRC Clock Divide 2
 *  0b000..Output disabled
 *  0b001..Divide by 1
 *  0b010..Divide by 2
 *  0b011..Divide by 4
 *  0b100..Divide by 8
 *  0b101..Divide by 16
 *  0b110..Divide by 32
 *  0b111..Divide by 64
 */
#define SCG_FIRCDIV_FIRCDIV2(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_FIRCDIV_FIRCDIV2_SHIFT)) & SCG_FIRCDIV_FIRCDIV2_MASK)
#define SCG_FIRCDIV_FIRCDIV3_MASK (0x70000U)
#define SCG_FIRCDIV_FIRCDIV3_SHIFT (16U)
/*! FIRCDIV3 - Fast IRC Clock Divider 3
 *  0b000..Clock disabled
 *  0b001..Divide by 1
 *  0b010..Divide by 2
 *  0b011..Divide by 4
 *  0b100..Divide by 8
 *  0b101..Divide by 16
 *  0b110..Divide by 32
 *  0b111..Divide by 64
 */
#define SCG_FIRCDIV_FIRCDIV3(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_FIRCDIV_FIRCDIV3_SHIFT)) & SCG_FIRCDIV_FIRCDIV3_MASK)
/*! @} */

/*! @name FIRCCFG - Fast IRC Configuration Register */
/*! @{ */
#define SCG_FIRCCFG_RANGE_MASK (0x3U)
#define SCG_FIRCCFG_RANGE_SHIFT (0U)
/*! RANGE - Frequency Range
 *  0b00..Fast IRC is trimmed to 48 MHz
 *  0b01..Fast IRC is trimmed to 52 MHz
 *  0b10..Fast IRC is trimmed to 56 MHz
 *  0b11..Fast IRC is trimmed to 60 MHz
 */
#define SCG_FIRCCFG_RANGE(x) (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCFG_RANGE_SHIFT)) & SCG_FIRCCFG_RANGE_MASK)
/*! @} */

/*! @name FIRCTCFG - Fast IRC Trim Configuration Register */
/*! @{ */
#define SCG_FIRCTCFG_TRIMSRC_MASK (0x3U)
#define SCG_FIRCTCFG_TRIMSRC_SHIFT (0U)
/*! TRIMSRC - Trim Source
 *  0b00..USB0 Start of Frame (1 kHz)
 *  0b01..Reserved
 *  0b10..System OSC
 *  0b11..Reserved
 */
#define SCG_FIRCTCFG_TRIMSRC(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_FIRCTCFG_TRIMSRC_SHIFT)) & SCG_FIRCTCFG_TRIMSRC_MASK)
#define SCG_FIRCTCFG_TRIMDIV_MASK (0x700U)
#define SCG_FIRCTCFG_TRIMDIV_SHIFT (8U)
/*! TRIMDIV - Fast IRC Trim Predivide
 *  0b000..Divide by 1
 *  0b001..Divide by 128
 *  0b010..Divide by 256
 *  0b011..Divide by 512
 *  0b100..Divide by 1024
 *  0b101..Divide by 2048
 *  0b110..Reserved. Writing this value will result in Divide by 1.
 *  0b111..Reserved. Writing this value will result in a Divide by 1.
 */
#define SCG_FIRCTCFG_TRIMDIV(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_FIRCTCFG_TRIMDIV_SHIFT)) & SCG_FIRCTCFG_TRIMDIV_MASK)
/*! @} */

/*! @name FIRCSTAT - Fast IRC Status Register */
/*! @{ */
#define SCG_FIRCSTAT_TRIMFINE_MASK (0x7FU)
#define SCG_FIRCSTAT_TRIMFINE_SHIFT (0U)
/*! TRIMFINE - Trim Fine Status
 */
#define SCG_FIRCSTAT_TRIMFINE(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_FIRCSTAT_TRIMFINE_SHIFT)) & SCG_FIRCSTAT_TRIMFINE_MASK)
#define SCG_FIRCSTAT_TRIMCOAR_MASK (0x3F00U)
#define SCG_FIRCSTAT_TRIMCOAR_SHIFT (8U)
/*! TRIMCOAR - Trim Coarse
 */
#define SCG_FIRCSTAT_TRIMCOAR(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_FIRCSTAT_TRIMCOAR_SHIFT)) & SCG_FIRCSTAT_TRIMCOAR_MASK)
/*! @} */

/*! @name SPLLCSR - System PLL Control Status Register */
/*! @{ */
#define SCG_SPLLCSR_SPLLEN_MASK (0x1U)
#define SCG_SPLLCSR_SPLLEN_SHIFT (0U)
/*! SPLLEN - System PLL Enable
 *  0b0..System PLL is disabled
 *  0b1..System PLL is enabled
 */
#define SCG_SPLLCSR_SPLLEN(x) (((uint32_t)(((uint32_t)(x)) << SCG_SPLLCSR_SPLLEN_SHIFT)) & SCG_SPLLCSR_SPLLEN_MASK)
#define SCG_SPLLCSR_SPLLSTEN_MASK (0x2U)
#define SCG_SPLLCSR_SPLLSTEN_SHIFT (1U)
/*! SPLLSTEN - System PLL Stop Enable
 *  0b0..System PLL is disabled in Stop modes
 *  0b1..System PLL is enabled in Stop modes
 */
#define SCG_SPLLCSR_SPLLSTEN(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SPLLCSR_SPLLSTEN_SHIFT)) & SCG_SPLLCSR_SPLLSTEN_MASK)
#define SCG_SPLLCSR_SPLLCM_MASK (0x10000U)
#define SCG_SPLLCSR_SPLLCM_SHIFT (16U)
/*! SPLLCM - System PLL Clock Monitor
 *  0b0..System PLL Clock Monitor is disabled
 *  0b1..System PLL Clock Monitor is enabled
 */
#define SCG_SPLLCSR_SPLLCM(x) (((uint32_t)(((uint32_t)(x)) << SCG_SPLLCSR_SPLLCM_SHIFT)) & SCG_SPLLCSR_SPLLCM_MASK)
#define SCG_SPLLCSR_SPLLCMRE_MASK (0x20000U)
#define SCG_SPLLCSR_SPLLCMRE_SHIFT (17U)
/*! SPLLCMRE - System PLL Clock Monitor Reset Enable
 *  0b0..Clock Monitor generates interrupt when error detected
 *  0b1..Clock Monitor generates reset when error detected
 */
#define SCG_SPLLCSR_SPLLCMRE(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SPLLCSR_SPLLCMRE_SHIFT)) & SCG_SPLLCSR_SPLLCMRE_MASK)
#define SCG_SPLLCSR_LK_MASK (0x800000U)
#define SCG_SPLLCSR_LK_SHIFT (23U)
/*! LK - Lock Register
 *  0b0..Control Status Register can be written.
 *  0b1..Control Status Register cannot be written.
 */
#define SCG_SPLLCSR_LK(x) (((uint32_t)(((uint32_t)(x)) << SCG_SPLLCSR_LK_SHIFT)) & SCG_SPLLCSR_LK_MASK)
#define SCG_SPLLCSR_SPLLVLD_MASK (0x1000000U)
#define SCG_SPLLCSR_SPLLVLD_SHIFT (24U)
/*! SPLLVLD - System PLL Valid
 *  0b0..System PLL is not enabled or clock is not valid
 *  0b1..System PLL is enabled and output clock is valid
 */
#define SCG_SPLLCSR_SPLLVLD(x) (((uint32_t)(((uint32_t)(x)) << SCG_SPLLCSR_SPLLVLD_SHIFT)) & SCG_SPLLCSR_SPLLVLD_MASK)
#define SCG_SPLLCSR_SPLLSEL_MASK (0x2000000U)
#define SCG_SPLLCSR_SPLLSEL_SHIFT (25U)
/*! SPLLSEL - System PLL Selected
 *  0b0..System PLL is not the system clock source
 *  0b1..System PLL is the system clock source
 */
#define SCG_SPLLCSR_SPLLSEL(x) (((uint32_t)(((uint32_t)(x)) << SCG_SPLLCSR_SPLLSEL_SHIFT)) & SCG_SPLLCSR_SPLLSEL_MASK)
#define SCG_SPLLCSR_SPLLERR_MASK (0x4000000U)
#define SCG_SPLLCSR_SPLLERR_SHIFT (26U)
/*! SPLLERR - System PLL Clock Error
 *  0b0..System PLL Clock Monitor is disabled or has not detected an error
 *  0b1..System PLL Clock Monitor is enabled and detected an error. System PLL Clock Error flag will not set when
 *       System OSC is selected as its source and SOSCERR has set.
 */
#define SCG_SPLLCSR_SPLLERR(x) (((uint32_t)(((uint32_t)(x)) << SCG_SPLLCSR_SPLLERR_SHIFT)) & SCG_SPLLCSR_SPLLERR_MASK)
/*! @} */

/*! @name SPLLDIV - System PLL Divide Register */
/*! @{ */
#define SCG_SPLLDIV_SPLLDIV1_MASK (0x7U)
#define SCG_SPLLDIV_SPLLDIV1_SHIFT (0U)
/*! SPLLDIV1 - System PLL Clock Divide 1
 *  0b000..Clock disabled
 *  0b001..Divide by 1
 *  0b010..Divide by 2
 *  0b011..Divide by 4
 *  0b100..Divide by 8
 *  0b101..Divide by 16
 *  0b110..Divide by 32
 *  0b111..Divide by 64
 */
#define SCG_SPLLDIV_SPLLDIV1(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SPLLDIV_SPLLDIV1_SHIFT)) & SCG_SPLLDIV_SPLLDIV1_MASK)
#define SCG_SPLLDIV_SPLLDIV2_MASK (0x700U)
#define SCG_SPLLDIV_SPLLDIV2_SHIFT (8U)
/*! SPLLDIV2 - System PLL Clock Divide 2
 *  0b000..Clock disabled
 *  0b001..Divide by 1
 *  0b010..Divide by 2
 *  0b011..Divide by 4
 *  0b100..Divide by 8
 *  0b101..Divide by 16
 *  0b110..Divide by 32
 *  0b111..Divide by 64
 */
#define SCG_SPLLDIV_SPLLDIV2(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SPLLDIV_SPLLDIV2_SHIFT)) & SCG_SPLLDIV_SPLLDIV2_MASK)
#define SCG_SPLLDIV_SPLLDIV3_MASK (0x70000U)
#define SCG_SPLLDIV_SPLLDIV3_SHIFT (16U)
/*! SPLLDIV3 - System PLL Clock Divide 3
 *  0b000..Clock disabled
 *  0b001..Divide by 1
 *  0b010..Divide by 2
 *  0b011..Divide by 4
 *  0b100..Divide by 8
 *  0b101..Divide by 16
 *  0b110..Divide by 32
 *  0b111..Divide by 64
 */
#define SCG_SPLLDIV_SPLLDIV3(x) \
    (((uint32_t)(((uint32_t)(x)) << SCG_SPLLDIV_SPLLDIV3_SHIFT)) & SCG_SPLLDIV_SPLLDIV3_MASK)
/*! @} */

/*! @name SPLLCFG - System PLL Configuration Register */
/*! @{ */
#define SCG_SPLLCFG_SOURCE_MASK (0x1U)
#define SCG_SPLLCFG_SOURCE_SHIFT (0U)
/*! SOURCE - Clock Source
 *  0b0..System OSC (SOSC)
 *  0b1..Fast IRC (FIRC)
 */
#define SCG_SPLLCFG_SOURCE(x) (((uint32_t)(((uint32_t)(x)) << SCG_SPLLCFG_SOURCE_SHIFT)) & SCG_SPLLCFG_SOURCE_MASK)
#define SCG_SPLLCFG_PREDIV_MASK (0x700U)
#define SCG_SPLLCFG_PREDIV_SHIFT (8U)
/*! PREDIV - PLL Reference Clock Divider
 */
#define SCG_SPLLCFG_PREDIV(x) (((uint32_t)(((uint32_t)(x)) << SCG_SPLLCFG_PREDIV_SHIFT)) & SCG_SPLLCFG_PREDIV_MASK)
#define SCG_SPLLCFG_MULT_MASK (0x1F0000U)
#define SCG_SPLLCFG_MULT_SHIFT (16U)
/*! MULT - System PLL Multiplier
 */
#define SCG_SPLLCFG_MULT(x) (((uint32_t)(((uint32_t)(x)) << SCG_SPLLCFG_MULT_SHIFT)) & SCG_SPLLCFG_MULT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group SCG_Register_Masks */

/* SCG - Peripheral instance base addresses */
/** Peripheral SCG base address */
#define SCG_BASE (0x4007B000u)
/** Peripheral SCG base pointer */
#define SCG ((SCG_Type *)SCG_BASE)
/** Array initializer of SCG peripheral base addresses */
#define SCG_BASE_ADDRS \
    {                  \
        SCG_BASE       \
    }
/** Array initializer of SCG peripheral base pointers */
#define SCG_BASE_PTRS \
    {                 \
        SCG           \
    }
/** Interrupt vectors for the SCG peripheral type */
#define SCG_IRQS \
    {            \
        SCG_IRQn \
    }

/*!
 * @}
 */ /* end of group SCG_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- SIM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Peripheral_Access_Layer SIM Peripheral Access Layer
 * @{
 */

/** SIM - Register Layout Typedef */
typedef struct
{
    __IO uint32_t SOPT1;    /**< System Options Register 1, offset: 0x0 */
    __IO uint32_t SOPT1CFG; /**< SOPT1 Configuration Register, offset: 0x4 */
    uint8_t RESERVED_0[4124];
    __I uint32_t SDID; /**< System Device Identification Register, offset: 0x1024 */
    uint8_t RESERVED_1[36];
    __IO uint32_t FCFG1; /**< Flash Configuration Register 1, offset: 0x104C */
    __I uint32_t FCFG2;  /**< Flash Configuration Register 2, offset: 0x1050 */
    uint8_t RESERVED_2[4];
    __I uint32_t UIDMH; /**< Unique Identification Register Mid-High, offset: 0x1058 */
    __I uint32_t UIDML; /**< Unique Identification Register Mid Low, offset: 0x105C */
    __I uint32_t UIDL;  /**< Unique Identification Register Low, offset: 0x1060 */
    uint8_t RESERVED_3[136];
    __I uint32_t PCSR; /**< Peripheral Clock Status Register, offset: 0x10EC */
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
#define SIM_SOPT1_USBVSTBY_MASK (0x20000000U)
#define SIM_SOPT1_USBVSTBY_SHIFT (29U)
/*! USBVSTBY - USB voltage regulator in standby mode during VLPR and VLPW modes
 *  0b0..USB voltage regulator not in standby during VLPR and VLPW modes.
 *  0b1..USB voltage regulator in standby during VLPR and VLPW modes.
 */
#define SIM_SOPT1_USBVSTBY(x) (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_USBVSTBY_SHIFT)) & SIM_SOPT1_USBVSTBY_MASK)
#define SIM_SOPT1_USBSSTBY_MASK (0x40000000U)
#define SIM_SOPT1_USBSSTBY_SHIFT (30U)
/*! USBSSTBY - USB voltage regulator in standby mode during Stop, VLPS, LLS and VLLS modes.
 *  0b0..USB voltage regulator not in standby during Stop, VLPS, LLS and VLLS modes.
 *  0b1..USB voltage regulator in standby during Stop, VLPS, LLS and VLLS modes.
 */
#define SIM_SOPT1_USBSSTBY(x) (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_USBSSTBY_SHIFT)) & SIM_SOPT1_USBSSTBY_MASK)
#define SIM_SOPT1_USBREGEN_MASK (0x80000000U)
#define SIM_SOPT1_USBREGEN_SHIFT (31U)
/*! USBREGEN - USB voltage regulator enable
 *  0b0..USB voltage regulator is disabled.
 *  0b1..USB voltage regulator is enabled.
 */
#define SIM_SOPT1_USBREGEN(x) (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_USBREGEN_SHIFT)) & SIM_SOPT1_USBREGEN_MASK)
/*! @} */

/*! @name SOPT1CFG - SOPT1 Configuration Register */
/*! @{ */
#define SIM_SOPT1CFG_URWE_MASK (0x1000000U)
#define SIM_SOPT1CFG_URWE_SHIFT (24U)
/*! URWE - USB voltage regulator enable write enable
 *  0b0..SOPT1 USBREGEN cannot be written.
 *  0b1..SOPT1 USBREGEN can be written.
 */
#define SIM_SOPT1CFG_URWE(x) (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1CFG_URWE_SHIFT)) & SIM_SOPT1CFG_URWE_MASK)
#define SIM_SOPT1CFG_UVSWE_MASK (0x2000000U)
#define SIM_SOPT1CFG_UVSWE_SHIFT (25U)
/*! UVSWE - USB voltage regulator VLP standby write enable
 *  0b0..SOPT1 USBVSTB cannot be written.
 *  0b1..SOPT1 USBVSTB can be written.
 */
#define SIM_SOPT1CFG_UVSWE(x) (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1CFG_UVSWE_SHIFT)) & SIM_SOPT1CFG_UVSWE_MASK)
#define SIM_SOPT1CFG_USSWE_MASK (0x4000000U)
#define SIM_SOPT1CFG_USSWE_SHIFT (26U)
/*! USSWE - USB voltage regulator stop standby write enable
 *  0b0..SOPT1 USBSSTB cannot be written.
 *  0b1..SOPT1 USBSSTB can be written.
 */
#define SIM_SOPT1CFG_USSWE(x) (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1CFG_USSWE_SHIFT)) & SIM_SOPT1CFG_USSWE_MASK)
/*! @} */

/*! @name SDID - System Device Identification Register */
/*! @{ */
#define SIM_SDID_PINID_MASK (0xFU)
#define SIM_SDID_PINID_SHIFT (0U)
/*! PINID - Pin count identification
 *  0b0000..Reserved
 *  0b0001..Reserved
 *  0b0010..Reserved
 *  0b0011..Reserved
 *  0b0100..Reserved
 *  0b0101..Reserved
 *  0b0110..Reserved
 *  0b0111..Reserved
 *  0b1000..100-pin
 *  0b1001..121-pin
 *  0b1010..Reserved
 *  0b1011..Reserved
 *  0b1100..Reserved
 *  0b1101..Reserved
 *  0b1110..Reserved
 *  0b1111..Reserved
 */
#define SIM_SDID_PINID(x) (((uint32_t)(((uint32_t)(x)) << SIM_SDID_PINID_SHIFT)) & SIM_SDID_PINID_MASK)
#define SIM_SDID_KEYATT_MASK (0x70U)
#define SIM_SDID_KEYATT_SHIFT (4U)
/*! KEYATT - Core configuration of the device.
 *  0b000..Cortex CM0+ Core
 *  0b001..Reserved
 *  0b010..Reserved
 *  0b011..Reserved
 *  0b100..Reserved
 *  0b101..Reserved
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define SIM_SDID_KEYATT(x) (((uint32_t)(((uint32_t)(x)) << SIM_SDID_KEYATT_SHIFT)) & SIM_SDID_KEYATT_MASK)
#define SIM_SDID_DIEID_MASK (0xF80U)
#define SIM_SDID_DIEID_SHIFT (7U)
/*! DIEID - Device Die Number
 */
#define SIM_SDID_DIEID(x) (((uint32_t)(((uint32_t)(x)) << SIM_SDID_DIEID_SHIFT)) & SIM_SDID_DIEID_MASK)
#define SIM_SDID_REVID_MASK (0xF000U)
#define SIM_SDID_REVID_SHIFT (12U)
/*! REVID - Device Revision Number
 *  0b0001..Revision 1.1
 */
#define SIM_SDID_REVID(x) (((uint32_t)(((uint32_t)(x)) << SIM_SDID_REVID_SHIFT)) & SIM_SDID_REVID_MASK)
#define SIM_SDID_SRAMSIZE_MASK (0xF0000U)
#define SIM_SDID_SRAMSIZE_SHIFT (16U)
/*! SRAMSIZE - System SRAM Size
 *  0b1000..96 KB
 *  0b1001..128 KB
 */
#define SIM_SDID_SRAMSIZE(x) (((uint32_t)(((uint32_t)(x)) << SIM_SDID_SRAMSIZE_SHIFT)) & SIM_SDID_SRAMSIZE_MASK)
#define SIM_SDID_SERIESID_MASK (0xF00000U)
#define SIM_SDID_SERIESID_SHIFT (20U)
/*! SERIESID - Kinetis Series ID
 *  0b0001..KL family
 */
#define SIM_SDID_SERIESID(x) (((uint32_t)(((uint32_t)(x)) << SIM_SDID_SERIESID_SHIFT)) & SIM_SDID_SERIESID_MASK)
#define SIM_SDID_SUBFAMID_MASK (0xF000000U)
#define SIM_SDID_SUBFAMID_SHIFT (24U)
/*! SUBFAMID - Kinetis Sub-Family ID
 *  0b0010..KLx2 Subfamily
 *  0b0011..KLx3 Subfamily
 *  0b0100..KLx4 Subfamily
 *  0b0101..KLx5 Subfamily
 *  0b0110..KLx6 Subfamily
 *  0b0111..KLx7 Subfamily
 *  0b1000..KLx8 Subfamily
 *  0b1001..KLx9 Subfamily
 */
#define SIM_SDID_SUBFAMID(x) (((uint32_t)(((uint32_t)(x)) << SIM_SDID_SUBFAMID_SHIFT)) & SIM_SDID_SUBFAMID_MASK)
#define SIM_SDID_FAMID_MASK (0xF0000000U)
#define SIM_SDID_FAMID_SHIFT (28U)
/*! FAMID - Kinetis family ID
 *  0b0010..KL2x Family (USB)
 */
#define SIM_SDID_FAMID(x) (((uint32_t)(((uint32_t)(x)) << SIM_SDID_FAMID_SHIFT)) & SIM_SDID_FAMID_MASK)
/*! @} */

/*! @name FCFG1 - Flash Configuration Register 1 */
/*! @{ */
#define SIM_FCFG1_FLASHDIS_MASK (0x1U)
#define SIM_FCFG1_FLASHDIS_SHIFT (0U)
/*! FLASHDIS - Flash Disable
 *  0b0..Flash is enabled.
 *  0b1..Flash is disabled.
 */
#define SIM_FCFG1_FLASHDIS(x) (((uint32_t)(((uint32_t)(x)) << SIM_FCFG1_FLASHDIS_SHIFT)) & SIM_FCFG1_FLASHDIS_MASK)
#define SIM_FCFG1_FLASHDOZE_MASK (0x2U)
#define SIM_FCFG1_FLASHDOZE_SHIFT (1U)
/*! FLASHDOZE - Flash Doze
 *  0b0..Flash remains enabled during Doze mode.
 *  0b1..Flash is disabled for the duration of Doze mode.
 */
#define SIM_FCFG1_FLASHDOZE(x) (((uint32_t)(((uint32_t)(x)) << SIM_FCFG1_FLASHDOZE_SHIFT)) & SIM_FCFG1_FLASHDOZE_MASK)
#define SIM_FCFG1_PFSIZE_MASK (0xF000000U)
#define SIM_FCFG1_PFSIZE_SHIFT (24U)
/*! PFSIZE - Program Flash Size
 *  0b0101..64 KB of program flash memory, 2 KB protection region
 *  0b0111..128 KB of program flash memory, 4 KB protection region
 *  0b1001..256 KB of program flash memory, 8 KB protection region
 *  0b1011..512 KB of program flash memory, 16 KB protection region
 */
#define SIM_FCFG1_PFSIZE(x) (((uint32_t)(((uint32_t)(x)) << SIM_FCFG1_PFSIZE_SHIFT)) & SIM_FCFG1_PFSIZE_MASK)
/*! @} */

/*! @name FCFG2 - Flash Configuration Register 2 */
/*! @{ */
#define SIM_FCFG2_MAXADDR0_MASK (0x7F000000U)
#define SIM_FCFG2_MAXADDR0_SHIFT (24U)
/*! MAXADDR0 - Max Address lock
 */
#define SIM_FCFG2_MAXADDR0(x) (((uint32_t)(((uint32_t)(x)) << SIM_FCFG2_MAXADDR0_SHIFT)) & SIM_FCFG2_MAXADDR0_MASK)
/*! @} */

/*! @name UIDMH - Unique Identification Register Mid-High */
/*! @{ */
#define SIM_UIDMH_UID_MASK (0xFFFFU)
#define SIM_UIDMH_UID_SHIFT (0U)
/*! UID - Unique Identification
 */
#define SIM_UIDMH_UID(x) (((uint32_t)(((uint32_t)(x)) << SIM_UIDMH_UID_SHIFT)) & SIM_UIDMH_UID_MASK)
/*! @} */

/*! @name UIDML - Unique Identification Register Mid Low */
/*! @{ */
#define SIM_UIDML_UID_MASK (0xFFFFFFFFU)
#define SIM_UIDML_UID_SHIFT (0U)
/*! UID - Unique Identification
 */
#define SIM_UIDML_UID(x) (((uint32_t)(((uint32_t)(x)) << SIM_UIDML_UID_SHIFT)) & SIM_UIDML_UID_MASK)
/*! @} */

/*! @name UIDL - Unique Identification Register Low */
/*! @{ */
#define SIM_UIDL_UID_MASK (0xFFFFFFFFU)
#define SIM_UIDL_UID_SHIFT (0U)
/*! UID - Unique Identification
 */
#define SIM_UIDL_UID(x) (((uint32_t)(((uint32_t)(x)) << SIM_UIDL_UID_SHIFT)) & SIM_UIDL_UID_MASK)
/*! @} */

/*! @name PCSR - Peripheral Clock Status Register */
/*! @{ */
#define SIM_PCSR_CS1_MASK (0x2U)
#define SIM_PCSR_CS1_SHIFT (1U)
/*! CS1 - Clock Source 1
 *  0b0..Clock not ready.
 *  0b1..Clock ready.
 */
#define SIM_PCSR_CS1(x) (((uint32_t)(((uint32_t)(x)) << SIM_PCSR_CS1_SHIFT)) & SIM_PCSR_CS1_MASK)
#define SIM_PCSR_CS2_MASK (0x4U)
#define SIM_PCSR_CS2_SHIFT (2U)
/*! CS2 - Clock Source 2
 *  0b0..Clock not ready.
 *  0b1..Clock ready.
 */
#define SIM_PCSR_CS2(x) (((uint32_t)(((uint32_t)(x)) << SIM_PCSR_CS2_SHIFT)) & SIM_PCSR_CS2_MASK)
#define SIM_PCSR_CS3_MASK (0x8U)
#define SIM_PCSR_CS3_SHIFT (3U)
/*! CS3 - Clock Source 3
 *  0b0..Clock not ready.
 *  0b1..Clock ready.
 */
#define SIM_PCSR_CS3(x) (((uint32_t)(((uint32_t)(x)) << SIM_PCSR_CS3_SHIFT)) & SIM_PCSR_CS3_MASK)
#define SIM_PCSR_CS4_MASK (0x10U)
#define SIM_PCSR_CS4_SHIFT (4U)
/*! CS4 - Clock Source 4
 *  0b0..Clock not ready.
 *  0b1..Clock ready.
 */
#define SIM_PCSR_CS4(x) (((uint32_t)(((uint32_t)(x)) << SIM_PCSR_CS4_SHIFT)) & SIM_PCSR_CS4_MASK)
#define SIM_PCSR_CS5_MASK (0x20U)
#define SIM_PCSR_CS5_SHIFT (5U)
/*! CS5 - Clock Source 5
 *  0b0..Clock not ready.
 *  0b1..Clock ready.
 */
#define SIM_PCSR_CS5(x) (((uint32_t)(((uint32_t)(x)) << SIM_PCSR_CS5_SHIFT)) & SIM_PCSR_CS5_MASK)
#define SIM_PCSR_CS6_MASK (0x40U)
#define SIM_PCSR_CS6_SHIFT (6U)
/*! CS6 - Clock Source 6
 *  0b0..Clock not ready.
 *  0b1..Clock ready.
 */
#define SIM_PCSR_CS6(x) (((uint32_t)(((uint32_t)(x)) << SIM_PCSR_CS6_SHIFT)) & SIM_PCSR_CS6_MASK)
#define SIM_PCSR_CS7_MASK (0x80U)
#define SIM_PCSR_CS7_SHIFT (7U)
/*! CS7 - Clock Source 7
 *  0b0..Clock not ready.
 *  0b1..Clock ready.
 */
#define SIM_PCSR_CS7(x) (((uint32_t)(((uint32_t)(x)) << SIM_PCSR_CS7_SHIFT)) & SIM_PCSR_CS7_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group SIM_Register_Masks */

/* SIM - Peripheral instance base addresses */
/** Peripheral SIM base address */
#define SIM_BASE (0x40074000u)
/** Peripheral SIM base pointer */
#define SIM ((SIM_Type *)SIM_BASE)
/** Array initializer of SIM peripheral base addresses */
#define SIM_BASE_ADDRS \
    {                  \
        SIM_BASE       \
    }
/** Array initializer of SIM peripheral base pointers */
#define SIM_BASE_PTRS \
    {                 \
        SIM           \
    }

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
typedef struct
{
    __I uint32_t VERID;     /**< SMC Version ID Register, offset: 0x0 */
    __I uint32_t PARAM;     /**< SMC Parameter Register, offset: 0x4 */
    __IO uint32_t PMPROT;   /**< Power Mode Protection register, offset: 0x8 */
    __IO uint32_t PMCTRL;   /**< Power Mode Control register, offset: 0xC */
    __IO uint32_t STOPCTRL; /**< Stop Control Register, offset: 0x10 */
    __I uint32_t PMSTAT;    /**< Power Mode Status register, offset: 0x14 */
} SMC_Type;

/* ----------------------------------------------------------------------------
   -- SMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Register_Masks SMC Register Masks
 * @{
 */

/*! @name VERID - SMC Version ID Register */
/*! @{ */
#define SMC_VERID_FEATURE_MASK (0xFFFFU)
#define SMC_VERID_FEATURE_SHIFT (0U)
/*! FEATURE - Feature Specification Number
 *  0b0000000000000000..Standard features implemented
 */
#define SMC_VERID_FEATURE(x) (((uint32_t)(((uint32_t)(x)) << SMC_VERID_FEATURE_SHIFT)) & SMC_VERID_FEATURE_MASK)
#define SMC_VERID_MINOR_MASK (0xFF0000U)
#define SMC_VERID_MINOR_SHIFT (16U)
/*! MINOR - Minor Version Number
 */
#define SMC_VERID_MINOR(x) (((uint32_t)(((uint32_t)(x)) << SMC_VERID_MINOR_SHIFT)) & SMC_VERID_MINOR_MASK)
#define SMC_VERID_MAJOR_MASK (0xFF000000U)
#define SMC_VERID_MAJOR_SHIFT (24U)
/*! MAJOR - Major Version Number
 */
#define SMC_VERID_MAJOR(x) (((uint32_t)(((uint32_t)(x)) << SMC_VERID_MAJOR_SHIFT)) & SMC_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - SMC Parameter Register */
/*! @{ */
#define SMC_PARAM_EHSRUN_MASK (0x1U)
#define SMC_PARAM_EHSRUN_SHIFT (0U)
/*! EHSRUN - Existence of HSRUN feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define SMC_PARAM_EHSRUN(x) (((uint32_t)(((uint32_t)(x)) << SMC_PARAM_EHSRUN_SHIFT)) & SMC_PARAM_EHSRUN_MASK)
#define SMC_PARAM_ELLS_MASK (0x8U)
#define SMC_PARAM_ELLS_SHIFT (3U)
/*! ELLS - Existence of LLS feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define SMC_PARAM_ELLS(x) (((uint32_t)(((uint32_t)(x)) << SMC_PARAM_ELLS_SHIFT)) & SMC_PARAM_ELLS_MASK)
#define SMC_PARAM_ELLS2_MASK (0x20U)
#define SMC_PARAM_ELLS2_SHIFT (5U)
/*! ELLS2 - Existence of LLS2 feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define SMC_PARAM_ELLS2(x) (((uint32_t)(((uint32_t)(x)) << SMC_PARAM_ELLS2_SHIFT)) & SMC_PARAM_ELLS2_MASK)
#define SMC_PARAM_EVLLS0_MASK (0x40U)
#define SMC_PARAM_EVLLS0_SHIFT (6U)
/*! EVLLS0 - Existence of VLLS0 feature
 *  0b0..The feature is not available.
 *  0b1..The feature is available.
 */
#define SMC_PARAM_EVLLS0(x) (((uint32_t)(((uint32_t)(x)) << SMC_PARAM_EVLLS0_SHIFT)) & SMC_PARAM_EVLLS0_MASK)
/*! @} */

/*! @name PMPROT - Power Mode Protection register */
/*! @{ */
#define SMC_PMPROT_AVLLS_MASK (0x2U)
#define SMC_PMPROT_AVLLS_SHIFT (1U)
/*! AVLLS - Allow Very-Low-Leakage Stop Mode
 *  0b0..Any VLLSx mode is not allowed
 *  0b1..Any VLLSx mode is allowed
 */
#define SMC_PMPROT_AVLLS(x) (((uint32_t)(((uint32_t)(x)) << SMC_PMPROT_AVLLS_SHIFT)) & SMC_PMPROT_AVLLS_MASK)
#define SMC_PMPROT_ALLS_MASK (0x8U)
#define SMC_PMPROT_ALLS_SHIFT (3U)
/*! ALLS - Allow Low-Leakage Stop Mode
 *  0b0..Any LLSx mode is not allowed
 *  0b1..Any LLSx mode is allowed
 */
#define SMC_PMPROT_ALLS(x) (((uint32_t)(((uint32_t)(x)) << SMC_PMPROT_ALLS_SHIFT)) & SMC_PMPROT_ALLS_MASK)
#define SMC_PMPROT_AVLP_MASK (0x20U)
#define SMC_PMPROT_AVLP_SHIFT (5U)
/*! AVLP - Allow Very-Low-Power Modes
 *  0b0..VLPR, VLPW, and VLPS are not allowed.
 *  0b1..VLPR, VLPW, and VLPS are allowed.
 */
#define SMC_PMPROT_AVLP(x) (((uint32_t)(((uint32_t)(x)) << SMC_PMPROT_AVLP_SHIFT)) & SMC_PMPROT_AVLP_MASK)
#define SMC_PMPROT_AHSRUN_MASK (0x80U)
#define SMC_PMPROT_AHSRUN_SHIFT (7U)
/*! AHSRUN - Allow High Speed Run mode
 *  0b0..HSRUN is not allowed
 *  0b1..HSRUN is allowed
 */
#define SMC_PMPROT_AHSRUN(x) (((uint32_t)(((uint32_t)(x)) << SMC_PMPROT_AHSRUN_SHIFT)) & SMC_PMPROT_AHSRUN_MASK)
/*! @} */

/*! @name PMCTRL - Power Mode Control register */
/*! @{ */
#define SMC_PMCTRL_STOPM_MASK (0x7U)
#define SMC_PMCTRL_STOPM_SHIFT (0U)
/*! STOPM - Stop Mode Control
 *  0b000..Normal Stop (STOP)
 *  0b001..Reserved
 *  0b010..Very-Low-Power Stop (VLPS)
 *  0b011..Low-Leakage Stop (LLSx)
 *  0b100..Very-Low-Leakage Stop (VLLSx)
 *  0b101..Reserved
 *  0b110..Reseved
 *  0b111..Reserved
 */
#define SMC_PMCTRL_STOPM(x) (((uint32_t)(((uint32_t)(x)) << SMC_PMCTRL_STOPM_SHIFT)) & SMC_PMCTRL_STOPM_MASK)
#define SMC_PMCTRL_STOPA_MASK (0x8U)
#define SMC_PMCTRL_STOPA_SHIFT (3U)
/*! STOPA - Stop Aborted
 *  0b0..The previous stop mode entry was successful.
 *  0b1..The previous stop mode entry was aborted.
 */
#define SMC_PMCTRL_STOPA(x) (((uint32_t)(((uint32_t)(x)) << SMC_PMCTRL_STOPA_SHIFT)) & SMC_PMCTRL_STOPA_MASK)
#define SMC_PMCTRL_RUNM_MASK (0x60U)
#define SMC_PMCTRL_RUNM_SHIFT (5U)
/*! RUNM - Run Mode Control
 *  0b00..Normal Run mode (RUN)
 *  0b01..Reserved
 *  0b10..Very-Low-Power Run mode (VLPR)
 *  0b11..High Speed Run mode (HSRUN)
 */
#define SMC_PMCTRL_RUNM(x) (((uint32_t)(((uint32_t)(x)) << SMC_PMCTRL_RUNM_SHIFT)) & SMC_PMCTRL_RUNM_MASK)
/*! @} */

/*! @name STOPCTRL - Stop Control Register */
/*! @{ */
#define SMC_STOPCTRL_LLSM_MASK (0x7U)
#define SMC_STOPCTRL_LLSM_SHIFT (0U)
/*! LLSM - LLS or VLLS Mode Control
 *  0b000..VLLS0 if PMCTRL[STOPM]=VLLSx, reserved if PMCTRL[STOPM]=LLSx
 *  0b001..VLLS1 if PMCTRL[STOPM]=VLLSx, reserved if PMCTRL[STOPM]=LLSx
 *  0b010..VLLS2 if PMCTRL[STOPM]=VLLSx, LLS2 if PMCTRL[STOPM]=LLSx
 *  0b011..VLLS3 if PMCTRL[STOPM]=VLLSx, LLS3 if PMCTRL[STOPM]=LLSx
 *  0b100..Reserved
 *  0b101..Reserved
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define SMC_STOPCTRL_LLSM(x) (((uint32_t)(((uint32_t)(x)) << SMC_STOPCTRL_LLSM_SHIFT)) & SMC_STOPCTRL_LLSM_MASK)
#define SMC_STOPCTRL_LPOPO_MASK (0x8U)
#define SMC_STOPCTRL_LPOPO_SHIFT (3U)
/*! LPOPO - LPO Power Option
 *  0b0..LPO clock is enabled in LLS/VLLSx
 *  0b1..LPO clock is disabled in LLS/VLLSx
 */
#define SMC_STOPCTRL_LPOPO(x) (((uint32_t)(((uint32_t)(x)) << SMC_STOPCTRL_LPOPO_SHIFT)) & SMC_STOPCTRL_LPOPO_MASK)
#define SMC_STOPCTRL_PORPO_MASK (0x20U)
#define SMC_STOPCTRL_PORPO_SHIFT (5U)
/*! PORPO - POR Power Option
 *  0b0..POR detect circuit is enabled in VLLS0
 *  0b1..POR detect circuit is disabled in VLLS0
 */
#define SMC_STOPCTRL_PORPO(x) (((uint32_t)(((uint32_t)(x)) << SMC_STOPCTRL_PORPO_SHIFT)) & SMC_STOPCTRL_PORPO_MASK)
#define SMC_STOPCTRL_PSTOPO_MASK (0xC0U)
#define SMC_STOPCTRL_PSTOPO_SHIFT (6U)
/*! PSTOPO - Partial Stop Option
 *  0b00..STOP - Normal Stop mode
 *  0b01..PSTOP1 - Partial Stop with both system and bus clocks disabled
 *  0b10..PSTOP2 - Partial Stop with system clock disabled and bus clock enabled
 *  0b11..Reserved
 */
#define SMC_STOPCTRL_PSTOPO(x) (((uint32_t)(((uint32_t)(x)) << SMC_STOPCTRL_PSTOPO_SHIFT)) & SMC_STOPCTRL_PSTOPO_MASK)
/*! @} */

/*! @name PMSTAT - Power Mode Status register */
/*! @{ */
#define SMC_PMSTAT_PMSTAT_MASK (0xFFU)
#define SMC_PMSTAT_PMSTAT_SHIFT (0U)
/*! PMSTAT - Power Mode Status
 */
#define SMC_PMSTAT_PMSTAT(x) (((uint32_t)(((uint32_t)(x)) << SMC_PMSTAT_PMSTAT_SHIFT)) & SMC_PMSTAT_PMSTAT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group SMC_Register_Masks */

/* SMC - Peripheral instance base addresses */
/** Peripheral SMC base address */
#define SMC_BASE (0x4007E000u)
/** Peripheral SMC base pointer */
#define SMC ((SMC_Type *)SMC_BASE)
/** Array initializer of SMC peripheral base addresses */
#define SMC_BASE_ADDRS \
    {                  \
        SMC_BASE       \
    }
/** Array initializer of SMC peripheral base pointers */
#define SMC_BASE_PTRS \
    {                 \
        SMC           \
    }

/*!
 * @}
 */ /* end of group SMC_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- TPM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TPM_Peripheral_Access_Layer TPM Peripheral Access Layer
 * @{
 */

/** TPM - Register Layout Typedef */
typedef struct
{
    __I uint32_t VERID;   /**< Version ID Register, offset: 0x0 */
    __I uint32_t PARAM;   /**< Parameter Register, offset: 0x4 */
    __IO uint32_t GLOBAL; /**< TPM Global Register, offset: 0x8 */
    uint8_t RESERVED_0[4];
    __IO uint32_t SC;     /**< Status and Control, offset: 0x10 */
    __IO uint32_t CNT;    /**< Counter, offset: 0x14 */
    __IO uint32_t MOD;    /**< Modulo, offset: 0x18 */
    __IO uint32_t STATUS; /**< Capture and Compare Status, offset: 0x1C */
    struct
    {                       /* offset: 0x20, array step: 0x8 */
        __IO uint32_t CnSC; /**< Channel (n) Status and Control, array offset: 0x20, array step: 0x8 */
        __IO uint32_t CnV;  /**< Channel (n) Value, array offset: 0x24, array step: 0x8 */
    } CONTROLS[6];
    uint8_t RESERVED_1[20];
    __IO uint32_t COMBINE; /**< Combine Channel Register, offset: 0x64 */
    uint8_t RESERVED_2[4];
    __IO uint32_t TRIG; /**< Channel Trigger, offset: 0x6C */
    __IO uint32_t POL;  /**< Channel Polarity, offset: 0x70 */
    uint8_t RESERVED_3[4];
    __IO uint32_t FILTER; /**< Filter Control, offset: 0x78 */
    uint8_t RESERVED_4[4];
    __IO uint32_t QDCTRL; /**< Quadrature Decoder Control and Status, offset: 0x80 */
    __IO uint32_t CONF;   /**< Configuration, offset: 0x84 */
} TPM_Type;

/* ----------------------------------------------------------------------------
   -- TPM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TPM_Register_Masks TPM Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */
#define TPM_VERID_FEATURE_MASK (0xFFFFU)
#define TPM_VERID_FEATURE_SHIFT (0U)
/*! FEATURE - Feature Identification Number
 *  0b0000000000000001..Standard feature set.
 *  0b0000000000000011..Standard feature set with Filter and Combine registers implemented.
 *  0b0000000000000111..Standard feature set with Filter, Combine and Quadrature registers implemented.
 */
#define TPM_VERID_FEATURE(x) (((uint32_t)(((uint32_t)(x)) << TPM_VERID_FEATURE_SHIFT)) & TPM_VERID_FEATURE_MASK)
#define TPM_VERID_MINOR_MASK (0xFF0000U)
#define TPM_VERID_MINOR_SHIFT (16U)
/*! MINOR - Minor Version Number
 */
#define TPM_VERID_MINOR(x) (((uint32_t)(((uint32_t)(x)) << TPM_VERID_MINOR_SHIFT)) & TPM_VERID_MINOR_MASK)
#define TPM_VERID_MAJOR_MASK (0xFF000000U)
#define TPM_VERID_MAJOR_SHIFT (24U)
/*! MAJOR - Major Version Number
 */
#define TPM_VERID_MAJOR(x) (((uint32_t)(((uint32_t)(x)) << TPM_VERID_MAJOR_SHIFT)) & TPM_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */
#define TPM_PARAM_CHAN_MASK (0xFFU)
#define TPM_PARAM_CHAN_SHIFT (0U)
/*! CHAN - Channel Count
 */
#define TPM_PARAM_CHAN(x) (((uint32_t)(((uint32_t)(x)) << TPM_PARAM_CHAN_SHIFT)) & TPM_PARAM_CHAN_MASK)
#define TPM_PARAM_TRIG_MASK (0xFF00U)
#define TPM_PARAM_TRIG_SHIFT (8U)
/*! TRIG - Trigger Count
 */
#define TPM_PARAM_TRIG(x) (((uint32_t)(((uint32_t)(x)) << TPM_PARAM_TRIG_SHIFT)) & TPM_PARAM_TRIG_MASK)
#define TPM_PARAM_WIDTH_MASK (0xFF0000U)
#define TPM_PARAM_WIDTH_SHIFT (16U)
/*! WIDTH - Counter Width
 */
#define TPM_PARAM_WIDTH(x) (((uint32_t)(((uint32_t)(x)) << TPM_PARAM_WIDTH_SHIFT)) & TPM_PARAM_WIDTH_MASK)
/*! @} */

/*! @name GLOBAL - TPM Global Register */
/*! @{ */
#define TPM_GLOBAL_RST_MASK (0x2U)
#define TPM_GLOBAL_RST_SHIFT (1U)
/*! RST - Software Reset
 *  0b0..Module is not reset.
 *  0b1..Module is reset.
 */
#define TPM_GLOBAL_RST(x) (((uint32_t)(((uint32_t)(x)) << TPM_GLOBAL_RST_SHIFT)) & TPM_GLOBAL_RST_MASK)
/*! @} */

/*! @name SC - Status and Control */
/*! @{ */
#define TPM_SC_PS_MASK (0x7U)
#define TPM_SC_PS_SHIFT (0U)
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
#define TPM_SC_PS(x) (((uint32_t)(((uint32_t)(x)) << TPM_SC_PS_SHIFT)) & TPM_SC_PS_MASK)
#define TPM_SC_CMOD_MASK (0x18U)
#define TPM_SC_CMOD_SHIFT (3U)
/*! CMOD - Clock Mode Selection
 *  0b00..TPM counter is disabled
 *  0b01..TPM counter increments on every TPM counter clock
 *  0b10..TPM counter increments on rising edge of TPM_EXTCLK synchronized to the TPM counter clock
 *  0b11..TPM counter increments on rising edge of the selected external input trigger.
 */
#define TPM_SC_CMOD(x) (((uint32_t)(((uint32_t)(x)) << TPM_SC_CMOD_SHIFT)) & TPM_SC_CMOD_MASK)
#define TPM_SC_CPWMS_MASK (0x20U)
#define TPM_SC_CPWMS_SHIFT (5U)
/*! CPWMS - Center-Aligned PWM Select
 *  0b0..TPM counter operates in up counting mode.
 *  0b1..TPM counter operates in up-down counting mode.
 */
#define TPM_SC_CPWMS(x) (((uint32_t)(((uint32_t)(x)) << TPM_SC_CPWMS_SHIFT)) & TPM_SC_CPWMS_MASK)
#define TPM_SC_TOIE_MASK (0x40U)
#define TPM_SC_TOIE_SHIFT (6U)
/*! TOIE - Timer Overflow Interrupt Enable
 *  0b0..Disable TOF interrupts. Use software polling or DMA request.
 *  0b1..Enable TOF interrupts. An interrupt is generated when TOF equals one.
 */
#define TPM_SC_TOIE(x) (((uint32_t)(((uint32_t)(x)) << TPM_SC_TOIE_SHIFT)) & TPM_SC_TOIE_MASK)
#define TPM_SC_TOF_MASK (0x80U)
#define TPM_SC_TOF_SHIFT (7U)
/*! TOF - Timer Overflow Flag
 *  0b0..TPM counter has not overflowed.
 *  0b1..TPM counter has overflowed.
 */
#define TPM_SC_TOF(x) (((uint32_t)(((uint32_t)(x)) << TPM_SC_TOF_SHIFT)) & TPM_SC_TOF_MASK)
#define TPM_SC_DMA_MASK (0x100U)
#define TPM_SC_DMA_SHIFT (8U)
/*! DMA - DMA Enable
 *  0b0..Disables DMA transfers.
 *  0b1..Enables DMA transfers.
 */
#define TPM_SC_DMA(x) (((uint32_t)(((uint32_t)(x)) << TPM_SC_DMA_SHIFT)) & TPM_SC_DMA_MASK)
/*! @} */

/*! @name CNT - Counter */
/*! @{ */
#define TPM_CNT_COUNT_MASK (0xFFFFU)
#define TPM_CNT_COUNT_SHIFT (0U)
/*! COUNT - Counter value
 */
#define TPM_CNT_COUNT(x) (((uint32_t)(((uint32_t)(x)) << TPM_CNT_COUNT_SHIFT)) & TPM_CNT_COUNT_MASK)
/*! @} */

/*! @name MOD - Modulo */
/*! @{ */
#define TPM_MOD_MOD_MASK (0xFFFFU)
#define TPM_MOD_MOD_SHIFT (0U)
/*! MOD - Modulo value
 */
#define TPM_MOD_MOD(x) (((uint32_t)(((uint32_t)(x)) << TPM_MOD_MOD_SHIFT)) & TPM_MOD_MOD_MASK)
/*! @} */

/*! @name STATUS - Capture and Compare Status */
/*! @{ */
#define TPM_STATUS_CH0F_MASK (0x1U)
#define TPM_STATUS_CH0F_SHIFT (0U)
/*! CH0F - Channel 0 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_STATUS_CH0F(x) (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_CH0F_SHIFT)) & TPM_STATUS_CH0F_MASK)
#define TPM_STATUS_CH1F_MASK (0x2U)
#define TPM_STATUS_CH1F_SHIFT (1U)
/*! CH1F - Channel 1 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_STATUS_CH1F(x) (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_CH1F_SHIFT)) & TPM_STATUS_CH1F_MASK)
#define TPM_STATUS_CH2F_MASK (0x4U)
#define TPM_STATUS_CH2F_SHIFT (2U)
/*! CH2F - Channel 2 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_STATUS_CH2F(x) (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_CH2F_SHIFT)) & TPM_STATUS_CH2F_MASK)
#define TPM_STATUS_CH3F_MASK (0x8U)
#define TPM_STATUS_CH3F_SHIFT (3U)
/*! CH3F - Channel 3 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_STATUS_CH3F(x) (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_CH3F_SHIFT)) & TPM_STATUS_CH3F_MASK)
#define TPM_STATUS_CH4F_MASK (0x10U)
#define TPM_STATUS_CH4F_SHIFT (4U)
/*! CH4F - Channel 4 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_STATUS_CH4F(x) (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_CH4F_SHIFT)) & TPM_STATUS_CH4F_MASK)
#define TPM_STATUS_CH5F_MASK (0x20U)
#define TPM_STATUS_CH5F_SHIFT (5U)
/*! CH5F - Channel 5 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_STATUS_CH5F(x) (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_CH5F_SHIFT)) & TPM_STATUS_CH5F_MASK)
#define TPM_STATUS_TOF_MASK (0x100U)
#define TPM_STATUS_TOF_SHIFT (8U)
/*! TOF - Timer Overflow Flag
 *  0b0..TPM counter has not overflowed.
 *  0b1..TPM counter has overflowed.
 */
#define TPM_STATUS_TOF(x) (((uint32_t)(((uint32_t)(x)) << TPM_STATUS_TOF_SHIFT)) & TPM_STATUS_TOF_MASK)
/*! @} */

/*! @name CnSC - Channel (n) Status and Control */
/*! @{ */
#define TPM_CnSC_DMA_MASK (0x1U)
#define TPM_CnSC_DMA_SHIFT (0U)
/*! DMA - DMA Enable
 *  0b0..Disable DMA transfers.
 *  0b1..Enable DMA transfers.
 */
#define TPM_CnSC_DMA(x) (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_DMA_SHIFT)) & TPM_CnSC_DMA_MASK)
#define TPM_CnSC_ELSA_MASK (0x4U)
#define TPM_CnSC_ELSA_SHIFT (2U)
/*! ELSA - Edge or Level Select
 */
#define TPM_CnSC_ELSA(x) (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_ELSA_SHIFT)) & TPM_CnSC_ELSA_MASK)
#define TPM_CnSC_ELSB_MASK (0x8U)
#define TPM_CnSC_ELSB_SHIFT (3U)
/*! ELSB - Edge or Level Select
 */
#define TPM_CnSC_ELSB(x) (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_ELSB_SHIFT)) & TPM_CnSC_ELSB_MASK)
#define TPM_CnSC_MSA_MASK (0x10U)
#define TPM_CnSC_MSA_SHIFT (4U)
/*! MSA - Channel Mode Select
 */
#define TPM_CnSC_MSA(x) (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_MSA_SHIFT)) & TPM_CnSC_MSA_MASK)
#define TPM_CnSC_MSB_MASK (0x20U)
#define TPM_CnSC_MSB_SHIFT (5U)
/*! MSB - Channel Mode Select
 */
#define TPM_CnSC_MSB(x) (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_MSB_SHIFT)) & TPM_CnSC_MSB_MASK)
#define TPM_CnSC_CHIE_MASK (0x40U)
#define TPM_CnSC_CHIE_SHIFT (6U)
/*! CHIE - Channel Interrupt Enable
 *  0b0..Disable channel interrupts.
 *  0b1..Enable channel interrupts.
 */
#define TPM_CnSC_CHIE(x) (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_CHIE_SHIFT)) & TPM_CnSC_CHIE_MASK)
#define TPM_CnSC_CHF_MASK (0x80U)
#define TPM_CnSC_CHF_SHIFT (7U)
/*! CHF - Channel Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define TPM_CnSC_CHF(x) (((uint32_t)(((uint32_t)(x)) << TPM_CnSC_CHF_SHIFT)) & TPM_CnSC_CHF_MASK)
/*! @} */

/* The count of TPM_CnSC */
#define TPM_CnSC_COUNT (6U)

/*! @name CnV - Channel (n) Value */
/*! @{ */
#define TPM_CnV_VAL_MASK (0xFFFFU)
#define TPM_CnV_VAL_SHIFT (0U)
/*! VAL - Channel Value
 */
#define TPM_CnV_VAL(x) (((uint32_t)(((uint32_t)(x)) << TPM_CnV_VAL_SHIFT)) & TPM_CnV_VAL_MASK)
/*! @} */

/* The count of TPM_CnV */
#define TPM_CnV_COUNT (6U)

/*! @name COMBINE - Combine Channel Register */
/*! @{ */
#define TPM_COMBINE_COMBINE0_MASK (0x1U)
#define TPM_COMBINE_COMBINE0_SHIFT (0U)
/*! COMBINE0 - Combine Channels 0 and 1
 *  0b0..Channels 0 and 1 are independent.
 *  0b1..Channels 0 and 1 are combined.
 */
#define TPM_COMBINE_COMBINE0(x) \
    (((uint32_t)(((uint32_t)(x)) << TPM_COMBINE_COMBINE0_SHIFT)) & TPM_COMBINE_COMBINE0_MASK)
#define TPM_COMBINE_COMSWAP0_MASK (0x2U)
#define TPM_COMBINE_COMSWAP0_SHIFT (1U)
/*! COMSWAP0 - Combine Channel 0 and 1 Swap
 *  0b0..Even channel is used for input capture and 1st compare.
 *  0b1..Odd channel is used for input capture and 1st compare.
 */
#define TPM_COMBINE_COMSWAP0(x) \
    (((uint32_t)(((uint32_t)(x)) << TPM_COMBINE_COMSWAP0_SHIFT)) & TPM_COMBINE_COMSWAP0_MASK)
#define TPM_COMBINE_COMBINE1_MASK (0x100U)
#define TPM_COMBINE_COMBINE1_SHIFT (8U)
/*! COMBINE1 - Combine Channels 2 and 3
 *  0b0..Channels 2 and 3 are independent.
 *  0b1..Channels 2 and 3 are combined.
 */
#define TPM_COMBINE_COMBINE1(x) \
    (((uint32_t)(((uint32_t)(x)) << TPM_COMBINE_COMBINE1_SHIFT)) & TPM_COMBINE_COMBINE1_MASK)
#define TPM_COMBINE_COMSWAP1_MASK (0x200U)
#define TPM_COMBINE_COMSWAP1_SHIFT (9U)
/*! COMSWAP1 - Combine Channels 2 and 3 Swap
 *  0b0..Even channel is used for input capture and 1st compare.
 *  0b1..Odd channel is used for input capture and 1st compare.
 */
#define TPM_COMBINE_COMSWAP1(x) \
    (((uint32_t)(((uint32_t)(x)) << TPM_COMBINE_COMSWAP1_SHIFT)) & TPM_COMBINE_COMSWAP1_MASK)
#define TPM_COMBINE_COMBINE2_MASK (0x10000U)
#define TPM_COMBINE_COMBINE2_SHIFT (16U)
/*! COMBINE2 - Combine Channels 4 and 5
 *  0b0..Channels 4 and 5 are independent.
 *  0b1..Channels 4 and 5 are combined.
 */
#define TPM_COMBINE_COMBINE2(x) \
    (((uint32_t)(((uint32_t)(x)) << TPM_COMBINE_COMBINE2_SHIFT)) & TPM_COMBINE_COMBINE2_MASK)
#define TPM_COMBINE_COMSWAP2_MASK (0x20000U)
#define TPM_COMBINE_COMSWAP2_SHIFT (17U)
/*! COMSWAP2 - Combine Channels 4 and 5 Swap
 *  0b0..Even channel is used for input capture and 1st compare.
 *  0b1..Odd channel is used for input capture and 1st compare.
 */
#define TPM_COMBINE_COMSWAP2(x) \
    (((uint32_t)(((uint32_t)(x)) << TPM_COMBINE_COMSWAP2_SHIFT)) & TPM_COMBINE_COMSWAP2_MASK)
/*! @} */

/*! @name TRIG - Channel Trigger */
/*! @{ */
#define TPM_TRIG_TRIG0_MASK (0x1U)
#define TPM_TRIG_TRIG0_SHIFT (0U)
/*! TRIG0 - Channel 0 Trigger
 *  0b0..No effect.
 *  0b1..The input trigger is used for input capture and modulates output (for output compare and PWM).
 */
#define TPM_TRIG_TRIG0(x) (((uint32_t)(((uint32_t)(x)) << TPM_TRIG_TRIG0_SHIFT)) & TPM_TRIG_TRIG0_MASK)
#define TPM_TRIG_TRIG1_MASK (0x2U)
#define TPM_TRIG_TRIG1_SHIFT (1U)
/*! TRIG1 - Channel 1 Trigger
 *  0b0..No effect.
 *  0b1..The input trigger is used for input capture and modulates output (for output compare and PWM).
 */
#define TPM_TRIG_TRIG1(x) (((uint32_t)(((uint32_t)(x)) << TPM_TRIG_TRIG1_SHIFT)) & TPM_TRIG_TRIG1_MASK)
#define TPM_TRIG_TRIG2_MASK (0x4U)
#define TPM_TRIG_TRIG2_SHIFT (2U)
/*! TRIG2 - Channel 2 Trigger
 *  0b0..No effect.
 *  0b1..The input trigger is used for input capture and modulates output (for output compare and PWM).
 */
#define TPM_TRIG_TRIG2(x) (((uint32_t)(((uint32_t)(x)) << TPM_TRIG_TRIG2_SHIFT)) & TPM_TRIG_TRIG2_MASK)
#define TPM_TRIG_TRIG3_MASK (0x8U)
#define TPM_TRIG_TRIG3_SHIFT (3U)
/*! TRIG3 - Channel 3 Trigger
 *  0b0..No effect.
 *  0b1..The input trigger is used for input capture and modulates output (for output compare and PWM).
 */
#define TPM_TRIG_TRIG3(x) (((uint32_t)(((uint32_t)(x)) << TPM_TRIG_TRIG3_SHIFT)) & TPM_TRIG_TRIG3_MASK)
#define TPM_TRIG_TRIG4_MASK (0x10U)
#define TPM_TRIG_TRIG4_SHIFT (4U)
/*! TRIG4 - Channel 4 Trigger
 *  0b0..No effect.
 *  0b1..The input trigger is used for input capture and modulates output (for output compare and PWM).
 */
#define TPM_TRIG_TRIG4(x) (((uint32_t)(((uint32_t)(x)) << TPM_TRIG_TRIG4_SHIFT)) & TPM_TRIG_TRIG4_MASK)
#define TPM_TRIG_TRIG5_MASK (0x20U)
#define TPM_TRIG_TRIG5_SHIFT (5U)
/*! TRIG5 - Channel 5 Trigger
 *  0b0..No effect.
 *  0b1..The input trigger is used for input capture and modulates output (for output compare and PWM).
 */
#define TPM_TRIG_TRIG5(x) (((uint32_t)(((uint32_t)(x)) << TPM_TRIG_TRIG5_SHIFT)) & TPM_TRIG_TRIG5_MASK)
/*! @} */

/*! @name POL - Channel Polarity */
/*! @{ */
#define TPM_POL_POL0_MASK (0x1U)
#define TPM_POL_POL0_SHIFT (0U)
/*! POL0 - Channel 0 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define TPM_POL_POL0(x) (((uint32_t)(((uint32_t)(x)) << TPM_POL_POL0_SHIFT)) & TPM_POL_POL0_MASK)
#define TPM_POL_POL1_MASK (0x2U)
#define TPM_POL_POL1_SHIFT (1U)
/*! POL1 - Channel 1 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define TPM_POL_POL1(x) (((uint32_t)(((uint32_t)(x)) << TPM_POL_POL1_SHIFT)) & TPM_POL_POL1_MASK)
#define TPM_POL_POL2_MASK (0x4U)
#define TPM_POL_POL2_SHIFT (2U)
/*! POL2 - Channel 2 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define TPM_POL_POL2(x) (((uint32_t)(((uint32_t)(x)) << TPM_POL_POL2_SHIFT)) & TPM_POL_POL2_MASK)
#define TPM_POL_POL3_MASK (0x8U)
#define TPM_POL_POL3_SHIFT (3U)
/*! POL3 - Channel 3 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define TPM_POL_POL3(x) (((uint32_t)(((uint32_t)(x)) << TPM_POL_POL3_SHIFT)) & TPM_POL_POL3_MASK)
#define TPM_POL_POL4_MASK (0x10U)
#define TPM_POL_POL4_SHIFT (4U)
/*! POL4 - Channel 4 Polarity
 *  0b0..The channel polarity is active high
 *  0b1..The channel polarity is active low.
 */
#define TPM_POL_POL4(x) (((uint32_t)(((uint32_t)(x)) << TPM_POL_POL4_SHIFT)) & TPM_POL_POL4_MASK)
#define TPM_POL_POL5_MASK (0x20U)
#define TPM_POL_POL5_SHIFT (5U)
/*! POL5 - Channel 5 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define TPM_POL_POL5(x) (((uint32_t)(((uint32_t)(x)) << TPM_POL_POL5_SHIFT)) & TPM_POL_POL5_MASK)
/*! @} */

/*! @name FILTER - Filter Control */
/*! @{ */
#define TPM_FILTER_CH0FVAL_MASK (0xFU)
#define TPM_FILTER_CH0FVAL_SHIFT (0U)
/*! CH0FVAL - Channel 0 Filter Value
 */
#define TPM_FILTER_CH0FVAL(x) (((uint32_t)(((uint32_t)(x)) << TPM_FILTER_CH0FVAL_SHIFT)) & TPM_FILTER_CH0FVAL_MASK)
#define TPM_FILTER_CH1FVAL_MASK (0xF0U)
#define TPM_FILTER_CH1FVAL_SHIFT (4U)
/*! CH1FVAL - Channel 1 Filter Value
 */
#define TPM_FILTER_CH1FVAL(x) (((uint32_t)(((uint32_t)(x)) << TPM_FILTER_CH1FVAL_SHIFT)) & TPM_FILTER_CH1FVAL_MASK)
#define TPM_FILTER_CH2FVAL_MASK (0xF00U)
#define TPM_FILTER_CH2FVAL_SHIFT (8U)
/*! CH2FVAL - Channel 2 Filter Value
 */
#define TPM_FILTER_CH2FVAL(x) (((uint32_t)(((uint32_t)(x)) << TPM_FILTER_CH2FVAL_SHIFT)) & TPM_FILTER_CH2FVAL_MASK)
#define TPM_FILTER_CH3FVAL_MASK (0xF000U)
#define TPM_FILTER_CH3FVAL_SHIFT (12U)
/*! CH3FVAL - Channel 3 Filter Value
 */
#define TPM_FILTER_CH3FVAL(x) (((uint32_t)(((uint32_t)(x)) << TPM_FILTER_CH3FVAL_SHIFT)) & TPM_FILTER_CH3FVAL_MASK)
#define TPM_FILTER_CH4FVAL_MASK (0xF0000U)
#define TPM_FILTER_CH4FVAL_SHIFT (16U)
/*! CH4FVAL - Channel 4 Filter Value
 */
#define TPM_FILTER_CH4FVAL(x) (((uint32_t)(((uint32_t)(x)) << TPM_FILTER_CH4FVAL_SHIFT)) & TPM_FILTER_CH4FVAL_MASK)
#define TPM_FILTER_CH5FVAL_MASK (0xF00000U)
#define TPM_FILTER_CH5FVAL_SHIFT (20U)
/*! CH5FVAL - Channel 5 Filter Value
 */
#define TPM_FILTER_CH5FVAL(x) (((uint32_t)(((uint32_t)(x)) << TPM_FILTER_CH5FVAL_SHIFT)) & TPM_FILTER_CH5FVAL_MASK)
/*! @} */

/*! @name QDCTRL - Quadrature Decoder Control and Status */
/*! @{ */
#define TPM_QDCTRL_QUADEN_MASK (0x1U)
#define TPM_QDCTRL_QUADEN_SHIFT (0U)
/*! QUADEN
 *  0b0..Quadrature decoder mode is disabled.
 *  0b1..Quadrature decoder mode is enabled.
 */
#define TPM_QDCTRL_QUADEN(x) (((uint32_t)(((uint32_t)(x)) << TPM_QDCTRL_QUADEN_SHIFT)) & TPM_QDCTRL_QUADEN_MASK)
#define TPM_QDCTRL_TOFDIR_MASK (0x2U)
#define TPM_QDCTRL_TOFDIR_SHIFT (1U)
/*! TOFDIR
 *  0b0..TOF bit was set on the bottom of counting. There was an FTM counter decrement and FTM counter changes
 *       from its minimum value (zero) to its maximum value (MOD register).
 *  0b1..TOF bit was set on the top of counting. There was an FTM counter increment and FTM counter changes from
 *       its maximum value (MOD register) to its minimum value (zero).
 */
#define TPM_QDCTRL_TOFDIR(x) (((uint32_t)(((uint32_t)(x)) << TPM_QDCTRL_TOFDIR_SHIFT)) & TPM_QDCTRL_TOFDIR_MASK)
#define TPM_QDCTRL_QUADIR_MASK (0x4U)
#define TPM_QDCTRL_QUADIR_SHIFT (2U)
/*! QUADIR - Counter Direction in Quadrature Decode Mode
 *  0b0..Counter direction is decreasing (counter decrement).
 *  0b1..Counter direction is increasing (counter increment).
 */
#define TPM_QDCTRL_QUADIR(x) (((uint32_t)(((uint32_t)(x)) << TPM_QDCTRL_QUADIR_SHIFT)) & TPM_QDCTRL_QUADIR_MASK)
#define TPM_QDCTRL_QUADMODE_MASK (0x8U)
#define TPM_QDCTRL_QUADMODE_SHIFT (3U)
/*! QUADMODE - Quadrature Decoder Mode
 *  0b0..Phase encoding mode.
 *  0b1..Count and direction encoding mode.
 */
#define TPM_QDCTRL_QUADMODE(x) (((uint32_t)(((uint32_t)(x)) << TPM_QDCTRL_QUADMODE_SHIFT)) & TPM_QDCTRL_QUADMODE_MASK)
/*! @} */

/*! @name CONF - Configuration */
/*! @{ */
#define TPM_CONF_DOZEEN_MASK (0x20U)
#define TPM_CONF_DOZEEN_SHIFT (5U)
/*! DOZEEN - Doze Enable
 *  0b0..Internal TPM counter continues in Doze mode.
 *  0b1..Internal TPM counter is paused and does not increment during Doze mode. Trigger inputs and input capture events
 * are also ignored.
 */
#define TPM_CONF_DOZEEN(x) (((uint32_t)(((uint32_t)(x)) << TPM_CONF_DOZEEN_SHIFT)) & TPM_CONF_DOZEEN_MASK)
#define TPM_CONF_DBGMODE_MASK (0xC0U)
#define TPM_CONF_DBGMODE_SHIFT (6U)
/*! DBGMODE - Debug Mode
 *  0b00..TPM counter is paused and does not increment during debug mode. Trigger inputs and input capture events are
 * also ignored. 0b11..TPM counter continues in debug mode.
 */
#define TPM_CONF_DBGMODE(x) (((uint32_t)(((uint32_t)(x)) << TPM_CONF_DBGMODE_SHIFT)) & TPM_CONF_DBGMODE_MASK)
#define TPM_CONF_GTBSYNC_MASK (0x100U)
#define TPM_CONF_GTBSYNC_SHIFT (8U)
/*! GTBSYNC - Global Time Base Synchronization
 *  0b0..Global timebase synchronization disabled.
 *  0b1..Global timebase synchronization enabled.
 */
#define TPM_CONF_GTBSYNC(x) (((uint32_t)(((uint32_t)(x)) << TPM_CONF_GTBSYNC_SHIFT)) & TPM_CONF_GTBSYNC_MASK)
#define TPM_CONF_GTBEEN_MASK (0x200U)
#define TPM_CONF_GTBEEN_SHIFT (9U)
/*! GTBEEN - Global time base enable
 *  0b0..All channels use the internally generated TPM counter as their timebase
 *  0b1..All channels use an externally generated global timebase as their timebase
 */
#define TPM_CONF_GTBEEN(x) (((uint32_t)(((uint32_t)(x)) << TPM_CONF_GTBEEN_SHIFT)) & TPM_CONF_GTBEEN_MASK)
#define TPM_CONF_CSOT_MASK (0x10000U)
#define TPM_CONF_CSOT_SHIFT (16U)
/*! CSOT - Counter Start on Trigger
 *  0b0..TPM counter starts to increment immediately, once it is enabled.
 *  0b1..TPM counter only starts to increment when it a rising edge on the selected input trigger is detected,
 *       after it has been enabled or after it has stopped due to overflow.
 */
#define TPM_CONF_CSOT(x) (((uint32_t)(((uint32_t)(x)) << TPM_CONF_CSOT_SHIFT)) & TPM_CONF_CSOT_MASK)
#define TPM_CONF_CSOO_MASK (0x20000U)
#define TPM_CONF_CSOO_SHIFT (17U)
/*! CSOO - Counter Stop On Overflow
 *  0b0..TPM counter continues incrementing or decrementing after overflow
 *  0b1..TPM counter stops incrementing or decrementing after overflow.
 */
#define TPM_CONF_CSOO(x) (((uint32_t)(((uint32_t)(x)) << TPM_CONF_CSOO_SHIFT)) & TPM_CONF_CSOO_MASK)
#define TPM_CONF_CROT_MASK (0x40000U)
#define TPM_CONF_CROT_SHIFT (18U)
/*! CROT - Counter Reload On Trigger
 *  0b0..Counter is not reloaded due to a rising edge on the selected input trigger
 *  0b1..Counter is reloaded when a rising edge is detected on the selected input trigger
 */
#define TPM_CONF_CROT(x) (((uint32_t)(((uint32_t)(x)) << TPM_CONF_CROT_SHIFT)) & TPM_CONF_CROT_MASK)
#define TPM_CONF_CPOT_MASK (0x80000U)
#define TPM_CONF_CPOT_SHIFT (19U)
/*! CPOT - Counter Pause On Trigger
 */
#define TPM_CONF_CPOT(x) (((uint32_t)(((uint32_t)(x)) << TPM_CONF_CPOT_SHIFT)) & TPM_CONF_CPOT_MASK)
#define TPM_CONF_TRGPOL_MASK (0x400000U)
#define TPM_CONF_TRGPOL_SHIFT (22U)
/*! TRGPOL - Trigger Polarity
 *  0b0..Trigger is active high.
 *  0b1..Trigger is active low.
 */
#define TPM_CONF_TRGPOL(x) (((uint32_t)(((uint32_t)(x)) << TPM_CONF_TRGPOL_SHIFT)) & TPM_CONF_TRGPOL_MASK)
#define TPM_CONF_TRGSRC_MASK (0x800000U)
#define TPM_CONF_TRGSRC_SHIFT (23U)
/*! TRGSRC - Trigger Source
 *  0b0..Trigger source selected by TRGSEL is external.
 *  0b1..Trigger source selected by TRGSEL is internal (channel pin input capture).
 */
#define TPM_CONF_TRGSRC(x) (((uint32_t)(((uint32_t)(x)) << TPM_CONF_TRGSRC_SHIFT)) & TPM_CONF_TRGSRC_MASK)
#define TPM_CONF_TRGSEL_MASK (0x3000000U)
#define TPM_CONF_TRGSEL_SHIFT (24U)
/*! TRGSEL - Trigger Select
 */
#define TPM_CONF_TRGSEL(x) (((uint32_t)(((uint32_t)(x)) << TPM_CONF_TRGSEL_SHIFT)) & TPM_CONF_TRGSEL_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group TPM_Register_Masks */

/* TPM - Peripheral instance base addresses */
/** Peripheral TPM0 base address */
#define TPM0_BASE (0x400AC000u)
/** Peripheral TPM0 base pointer */
#define TPM0 ((TPM_Type *)TPM0_BASE)
/** Peripheral TPM1 base address */
#define TPM1_BASE (0x400AD000u)
/** Peripheral TPM1 base pointer */
#define TPM1 ((TPM_Type *)TPM1_BASE)
/** Peripheral TPM2 base address */
#define TPM2_BASE (0x4002E000u)
/** Peripheral TPM2 base pointer */
#define TPM2 ((TPM_Type *)TPM2_BASE)
/** Array initializer of TPM peripheral base addresses */
#define TPM_BASE_ADDRS                  \
    {                                   \
        TPM0_BASE, TPM1_BASE, TPM2_BASE \
    }
/** Array initializer of TPM peripheral base pointers */
#define TPM_BASE_PTRS    \
    {                    \
        TPM0, TPM1, TPM2 \
    }
/** Interrupt vectors for the TPM peripheral type */
#define TPM_IRQS                        \
    {                                   \
        TPM0_IRQn, TPM1_IRQn, TPM2_IRQn \
    }

/*!
 * @}
 */ /* end of group TPM_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- TRGMUX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TRGMUX_Peripheral_Access_Layer TRGMUX Peripheral Access Layer
 * @{
 */

/** TRGMUX - Register Layout Typedef */
typedef struct
{
    __IO uint32_t TRGCFG[14]; /**< TRGMUX TRGCFG Register, array offset: 0x0, array step: 0x4 */
} TRGMUX_Type;

/* ----------------------------------------------------------------------------
   -- TRGMUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TRGMUX_Register_Masks TRGMUX Register Masks
 * @{
 */

/*! @name TRGCFG - TRGMUX TRGCFG Register */
/*! @{ */
#define TRGMUX_TRGCFG_SEL0_MASK (0x3FU)
#define TRGMUX_TRGCFG_SEL0_SHIFT (0U)
/*! SEL0 - Trigger MUX Input 0 Source Select
 *  0b000000..Trigger function is disabled.
 *  0b000001..Port pin trigger input is selected.
 *  0b000010..FlexIO Timer 0 input is selected.
 *  0b000011..FlexIO Timer 1 input is selected.
 *  0b000100..FlexIO Timer 2 input is selected.
 *  0b000101..FlexIO Timer 3 input is selected.
 *  0b000110..FlexIO Timer 4 input is selected.
 *  0b000111..FlexIO Timer 5 input is selected.
 *  0b001000..FlexIO Timer 6 input is selected.
 *  0b001001..FlexIO Timer 7 input is selected.
 *  0b001010..TPM0 Overflow is selected
 *  0b001011..TPM0 Channel 0 is selected
 *  0b001100..TPM0 Channel 1 is selected
 *  0b001101..TPM1 Overflow is selected
 *  0b001110..TPM1 Channel 0 is selected
 *  0b001111..TPM1 Channel 1 is selected
 *  0b010000..LPIT1 Channel 0 is selected
 *  0b010001..LPIT1 Channel 1 is selected
 *  0b010010..LPIT1 Channel 2 is selected
 *  0b010011..LPIT1 Channel 3 is selected
 *  0b010100..LPUART0 RX Data is selected.
 *  0b010101..LPUART0 TX Data is selected.
 *  0b010110..LPUART0 RX Idle is selected.
 *  0b010111..LPUART1 RX Data is selected.
 *  0b011000..LPUART1 TX Data is selected.
 *  0b011001..LPUART1 RX Idle is selected.
 *  0b011010..LPI2C0 Master STOP is selected.
 *  0b011011..LPI2C0 Slave STOP is selected.
 *  0b011100..LPI2C1 Master STOP is selected.
 *  0b011101..LPI2C1 Slave STOP is selected.
 *  0b011110..LPSPI0 Frame is selected.
 *  0b011111..LPSPI0 RX data is selected.
 *  0b100000..LPSPI1 Frame is selected.
 *  0b100001..LPSPI1 RX data is selected.
 *  0b100010..RTC Seconds Counter is selected.
 *  0b100011..RTC Alarm is selected.
 *  0b100100..LPTMR0 Trigger is selected.
 *  0b100101..LPTMR1 Trigger is selected.
 *  0b100110..CMP0 Output is selected.
 *  0b100111..CMP1 Output is selected.
 *  0b101000..ADC0 Conversion A Complete is selected.
 *  0b101001..ADC0 Conversion B Complete is selected.
 *  0b101010..Port A Pin Trigger is selected.
 *  0b101011..Port B Pin Trigger is selected.
 *  0b101100..Port C Pin Trigger is selected.
 *  0b101101..Port D Pin Trigger is selected.
 *  0b101110..Port E Pin Trigger is selected.
 *  0b101111..TPM2 Overflow selected.
 *  0b110000..TPM2 Channel 0 is selected.
 *  0b110001..TPM2 Channel 1 is selected.
 *  0b110010..LPIT0 Channel 0 is selected.
 *  0b110011..LPIT0 Channel 1 is selected.
 *  0b110100..LPIT0 Channel 2 is selected.
 *  0b110101..LPIT0 Channel 3 is selected.
 *  0b110110..USB Start-of-Frame is selected.
 *  0b110111..LPUART2 RX Data is selected.
 *  0b111000..LPUART2 TX Data is selected.
 *  0b111001..LPUART2 RX Idle is selected.
 *  0b111010..LPI2C2 Master STOP is selected.
 *  0b111011..LPI2C2 Slave STOP is selected.
 *  0b111100..LPSPI2 Frame is selected.
 *  0b111101..LPSPI2 RX Data is selected.
 */
#define TRGMUX_TRGCFG_SEL0(x) (((uint32_t)(((uint32_t)(x)) << TRGMUX_TRGCFG_SEL0_SHIFT)) & TRGMUX_TRGCFG_SEL0_MASK)
#define TRGMUX_TRGCFG_SEL1_MASK (0x3F00U)
#define TRGMUX_TRGCFG_SEL1_SHIFT (8U)
/*! SEL1 - Trigger MUX Input 1 Source Select
 *  0b000000..Trigger function is disabled.
 *  0b000001..Port pin trigger input is selected.
 *  0b000010..FlexIO Timer 0 input is selected.
 *  0b000011..FlexIO Timer 1 input is selected.
 *  0b000100..FlexIO Timer 2 input is selected.
 *  0b000101..FlexIO Timer 3 input is selected.
 *  0b000110..FlexIO Timer 4 input is selected.
 *  0b000111..FlexIO Timer 5 input is selected.
 *  0b001000..FlexIO Timer 6 input is selected.
 *  0b001001..FlexIO Timer 7 input is selected.
 *  0b001010..TPM0 Overflow is selected
 *  0b001011..TPM0 Channel 0 is selected
 *  0b001100..TPM0 Channel 1 is selected
 *  0b001101..TPM1 Overflow is selected
 *  0b001110..TPM1 Channel 0 is selected
 *  0b001111..TPM1 Channel 1 is selected
 *  0b010000..LPIT1 Channel 0 is selected
 *  0b010001..LPIT1 Channel 1 is selected
 *  0b010010..LPIT1 Channel 2 is selected
 *  0b010011..LPIT1 Channel 3 is selected
 *  0b010100..LPUART0 RX Data is selected.
 *  0b010101..LPUART0 TX Data is selected.
 *  0b010110..LPUART0 RX Idle is selected.
 *  0b010111..LPUART1 RX Data is selected.
 *  0b011000..LPUART1 TX Data is selected.
 *  0b011001..LPUART1 RX Idle is selected.
 *  0b011010..LPI2C0 Master STOP is selected.
 *  0b011011..LPI2C0 Slave STOP is selected.
 *  0b011100..LPI2C1 Master STOP is selected.
 *  0b011101..LPI2C1 Slave STOP is selected.
 *  0b011110..LPSPI0 Frame is selected.
 *  0b011111..LPSPI0 RX data is selected.
 *  0b100000..LPSPI1 Frame is selected.
 *  0b100001..LPSPI1 RX data is selected.
 *  0b100010..RTC Seconds Counter is selected.
 *  0b100011..RTC Alarm is selected.
 *  0b100100..LPTMR0 Trigger is selected.
 *  0b100101..LPTMR1 Trigger is selected.
 *  0b100110..CMP0 Output is selected.
 *  0b100111..CMP1 Output is selected.
 *  0b101000..ADC0 Conversion A Complete is selected.
 *  0b101001..ADC0 Conversion B Complete is selected.
 *  0b101010..Port A Pin Trigger is selected.
 *  0b101011..Port B Pin Trigger is selected.
 *  0b101100..Port C Pin Trigger is selected.
 *  0b101101..Port D Pin Trigger is selected.
 *  0b101110..Port E Pin Trigger is selected.
 *  0b101111..TPM2 Overflow selected.
 *  0b110000..TPM2 Channel 0 is selected.
 *  0b110001..TPM2 Channel 1 is selected.
 *  0b110010..LPIT0 Channel 0 is selected.
 *  0b110011..LPIT0 Channel 1 is selected.
 *  0b110100..LPIT0 Channel 2 is selected.
 *  0b110101..LPIT0 Channel 3 is selected.
 *  0b110110..USB Start-of-Frame is selected.
 *  0b110111..LPUART2 RX Data is selected.
 *  0b111000..LPUART2 TX Data is selected.
 *  0b111001..LPUART2 RX Idle is selected.
 *  0b111010..LPI2C2 Master STOP is selected.
 *  0b111011..LPI2C2 Slave STOP is selected.
 *  0b111100..LPSPI2 Frame is selected.
 *  0b111101..LPSPI2 RX Data is selected.
 */
#define TRGMUX_TRGCFG_SEL1(x) (((uint32_t)(((uint32_t)(x)) << TRGMUX_TRGCFG_SEL1_SHIFT)) & TRGMUX_TRGCFG_SEL1_MASK)
#define TRGMUX_TRGCFG_SEL2_MASK (0x3F0000U)
#define TRGMUX_TRGCFG_SEL2_SHIFT (16U)
/*! SEL2 - Trigger MUX Input 2 Source Select
 *  0b000000..Trigger function is disabled.
 *  0b000001..Port pin trigger input is selected.
 *  0b000010..FlexIO Timer 0 input is selected.
 *  0b000011..FlexIO Timer 1 input is selected.
 *  0b000100..FlexIO Timer 2 input is selected.
 *  0b000101..FlexIO Timer 3 input is selected.
 *  0b000110..FlexIO Timer 4 input is selected.
 *  0b000111..FlexIO Timer 5 input is selected.
 *  0b001000..FlexIO Timer 6 input is selected.
 *  0b001001..FlexIO Timer 7 input is selected.
 *  0b001010..TPM0 Overflow is selected
 *  0b001011..TPM0 Channel 0 is selected
 *  0b001100..TPM0 Channel 1 is selected
 *  0b001101..TPM1 Overflow is selected
 *  0b001110..TPM1 Channel 0 is selected
 *  0b001111..TPM1 Channel 1 is selected
 *  0b010000..LPIT1 Channel 0 is selected
 *  0b010001..LPIT1 Channel 1 is selected
 *  0b010010..LPIT1 Channel 2 is selected
 *  0b010011..LPIT1 Channel 3 is selected
 *  0b010100..LPUART0 RX Data is selected.
 *  0b010101..LPUART0 TX Data is selected.
 *  0b010110..LPUART0 RX Idle is selected.
 *  0b010111..LPUART1 RX Data is selected.
 *  0b011000..LPUART1 TX Data is selected.
 *  0b011001..LPUART1 RX Idle is selected.
 *  0b011010..LPI2C0 Master STOP is selected.
 *  0b011011..LPI2C0 Slave STOP is selected.
 *  0b011100..LPI2C1 Master STOP is selected.
 *  0b011101..LPI2C1 Slave STOP is selected.
 *  0b011110..LPSPI0 Frame is selected.
 *  0b011111..LPSPI0 RX data is selected.
 *  0b100000..LPSPI1 Frame is selected.
 *  0b100001..LPSPI1 RX data is selected.
 *  0b100010..RTC Seconds Counter is selected.
 *  0b100011..RTC Alarm is selected.
 *  0b100100..LPTMR0 Trigger is selected.
 *  0b100101..LPTMR1 Trigger is selected.
 *  0b100110..CMP0 Output is selected.
 *  0b100111..CMP1 Output is selected.
 *  0b101000..ADC0 Conversion A Complete is selected.
 *  0b101001..ADC0 Conversion B Complete is selected.
 *  0b101010..Port A Pin Trigger is selected.
 *  0b101011..Port B Pin Trigger is selected.
 *  0b101100..Port C Pin Trigger is selected.
 *  0b101101..Port D Pin Trigger is selected.
 *  0b101110..Port E Pin Trigger is selected.
 *  0b101111..TPM2 Overflow selected.
 *  0b110000..TPM2 Channel 0 is selected.
 *  0b110001..TPM2 Channel 1 is selected.
 *  0b110010..LPIT0 Channel 0 is selected.
 *  0b110011..LPIT0 Channel 1 is selected.
 *  0b110100..LPIT0 Channel 2 is selected.
 *  0b110101..LPIT0 Channel 3 is selected.
 *  0b110110..USB Start-of-Frame is selected.
 *  0b110111..LPUART2 RX Data is selected.
 *  0b111000..LPUART2 TX Data is selected.
 *  0b111001..LPUART2 RX Idle is selected.
 *  0b111010..LPI2C2 Master STOP is selected.
 *  0b111011..LPI2C2 Slave STOP is selected.
 *  0b111100..LPSPI2 Frame is selected.
 *  0b111101..LPSPI2 RX Data is selected.
 */
#define TRGMUX_TRGCFG_SEL2(x) (((uint32_t)(((uint32_t)(x)) << TRGMUX_TRGCFG_SEL2_SHIFT)) & TRGMUX_TRGCFG_SEL2_MASK)
#define TRGMUX_TRGCFG_SEL3_MASK (0x3F000000U)
#define TRGMUX_TRGCFG_SEL3_SHIFT (24U)
/*! SEL3 - Trigger MUX Input 3 Source Select
 *  0b000000..Trigger function is disabled.
 *  0b000001..Port pin trigger input is selected.
 *  0b000010..FlexIO Timer 0 input is selected.
 *  0b000011..FlexIO Timer 1 input is selected.
 *  0b000100..FlexIO Timer 2 input is selected.
 *  0b000101..FlexIO Timer 3 input is selected.
 *  0b000110..FlexIO Timer 4 input is selected.
 *  0b000111..FlexIO Timer 5 input is selected.
 *  0b001000..FlexIO Timer 6 input is selected.
 *  0b001001..FlexIO Timer 7 input is selected.
 *  0b001010..TPM0 Overflow is selected
 *  0b001011..TPM0 Channel 0 is selected
 *  0b001100..TPM0 Channel 1 is selected
 *  0b001101..TPM1 Overflow is selected
 *  0b001110..TPM1 Channel 0 is selected
 *  0b001111..TPM1 Channel 1 is selected
 *  0b010000..LPIT1 Channel 0 is selected
 *  0b010001..LPIT1 Channel 1 is selected
 *  0b010010..LPIT1 Channel 2 is selected
 *  0b010011..LPIT1 Channel 3 is selected
 *  0b010100..LPUART0 RX Data is selected.
 *  0b010101..LPUART0 TX Data is selected.
 *  0b010110..LPUART0 RX Idle is selected.
 *  0b010111..LPUART1 RX Data is selected.
 *  0b011000..LPUART1 TX Data is selected.
 *  0b011001..LPUART1 RX Idle is selected.
 *  0b011010..LPI2C0 Master STOP is selected.
 *  0b011011..LPI2C0 Slave STOP is selected.
 *  0b011100..LPI2C1 Master STOP is selected.
 *  0b011101..LPI2C1 Slave STOP is selected.
 *  0b011110..LPSPI0 Frame is selected.
 *  0b011111..LPSPI0 RX data is selected.
 *  0b100000..LPSPI1 Frame is selected.
 *  0b100001..LPSPI1 RX data is selected.
 *  0b100010..RTC Seconds Counter is selected.
 *  0b100011..RTC Alarm is selected.
 *  0b100100..LPTMR0 Trigger is selected.
 *  0b100101..LPTMR1 Trigger is selected.
 *  0b100110..CMP0 Output is selected.
 *  0b100111..CMP1 Output is selected.
 *  0b101000..ADC0 Conversion A Complete is selected.
 *  0b101001..ADC0 Conversion B Complete is selected.
 *  0b101010..Port A Pin Trigger is selected.
 *  0b101011..Port B Pin Trigger is selected.
 *  0b101100..Port C Pin Trigger is selected.
 *  0b101101..Port D Pin Trigger is selected.
 *  0b101110..Port E Pin Trigger is selected.
 *  0b101111..TPM2 Overflow selected.
 *  0b110000..TPM2 Channel 0 is selected.
 *  0b110001..TPM2 Channel 1 is selected.
 *  0b110010..LPIT0 Channel 0 is selected.
 *  0b110011..LPIT0 Channel 1 is selected.
 *  0b110100..LPIT0 Channel 2 is selected.
 *  0b110101..LPIT0 Channel 3 is selected.
 *  0b110110..USB Start-of-Frame is selected.
 *  0b110111..LPUART2 RX Data is selected.
 *  0b111000..LPUART2 TX Data is selected.
 *  0b111001..LPUART2 RX Idle is selected.
 *  0b111010..LPI2C2 Master STOP is selected.
 *  0b111011..LPI2C2 Slave STOP is selected.
 *  0b111100..LPSPI2 Frame is selected.
 *  0b111101..LPSPI2 RX Data is selected.
 */
#define TRGMUX_TRGCFG_SEL3(x) (((uint32_t)(((uint32_t)(x)) << TRGMUX_TRGCFG_SEL3_SHIFT)) & TRGMUX_TRGCFG_SEL3_MASK)
#define TRGMUX_TRGCFG_LK_MASK (0x80000000U)
#define TRGMUX_TRGCFG_LK_SHIFT (31U)
/*! LK - Enable
 *  0b0..Register can be written.
 *  0b1..Register cannot be written until the next system Reset.
 */
#define TRGMUX_TRGCFG_LK(x) (((uint32_t)(((uint32_t)(x)) << TRGMUX_TRGCFG_LK_SHIFT)) & TRGMUX_TRGCFG_LK_MASK)
/*! @} */

/* The count of TRGMUX_TRGCFG */
#define TRGMUX_TRGCFG_COUNT (14U)

/*!
 * @}
 */ /* end of group TRGMUX_Register_Masks */

/* TRGMUX - Peripheral instance base addresses */
/** Peripheral TRGMUX0 base address */
#define TRGMUX0_BASE (0x40027000u)
/** Peripheral TRGMUX0 base pointer */
#define TRGMUX0 ((TRGMUX_Type *)TRGMUX0_BASE)
/** Peripheral TRGMUX1 base address */
#define TRGMUX1_BASE (0x400A7000u)
/** Peripheral TRGMUX1 base pointer */
#define TRGMUX1 ((TRGMUX_Type *)TRGMUX1_BASE)
/** Array initializer of TRGMUX peripheral base addresses */
#define TRGMUX_BASE_ADDRS          \
    {                              \
        TRGMUX0_BASE, TRGMUX1_BASE \
    }
/** Array initializer of TRGMUX peripheral base pointers */
#define TRGMUX_BASE_PTRS \
    {                    \
        TRGMUX0, TRGMUX1 \
    }
#define TRGMUX_INSTANCE_MASK 0xF
#define TRGMUX_INSTANCE_SHIFT 12
#define TRGMUX_PERIPHERAL_MASK 0xFFF
#define TRGMUX_PERIPHERAL_SHIFT 0
#define TRGMUX_INSTANCE_0 0
#define TRGMUX_INSTANCE_1 1

#define TRGMUX_DMAMUX0_INDEX ((uint16_t)((TRGMUX_INSTANCE_0 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 0)
#define TRGMUX_LPIT0_INDEX ((uint16_t)((TRGMUX_INSTANCE_0 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 1)
#define TRGMUX_TPM2_INDEX ((uint16_t)((TRGMUX_INSTANCE_0 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 2)
#define TRGMUX_ADC0_INDEX ((uint16_t)((TRGMUX_INSTANCE_0 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 4)
#define TRGMUX_LPUART2_INDEX ((uint16_t)((TRGMUX_INSTANCE_0 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 5)
#define TRGMUX_LPI2C2_INDEX ((uint16_t)((TRGMUX_INSTANCE_0 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 7)
#define TRGMUX_LPSPI2_INDEX ((uint16_t)((TRGMUX_INSTANCE_0 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 9)
#define TRGMUX_CMP0_INDEX ((uint16_t)((TRGMUX_INSTANCE_0 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 11)
#define TRGMUX_CMP1_INDEX ((uint16_t)((TRGMUX_INSTANCE_0 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 12)
#define TRGMUX_DAC0_INDEX ((uint16_t)((TRGMUX_INSTANCE_0 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 13)
#define TRGMUX_DMAMUX0 (TRGMUX0->TRGCFG[0])
#define TRGMUX_LPIT0 (TRGMUX0->TRGCFG[1])
#define TRGMUX_TPM2 (TRGMUX0->TRGCFG[2])
#define TRGMUX_ADC0 (TRGMUX0->TRGCFG[4])
#define TRGMUX_LPUART2 (TRGMUX0->TRGCFG[5])
#define TRGMUX_LPI2C2 (TRGMUX0->TRGCFG[7])
#define TRGMUX_LPSPI2 (TRGMUX0->TRGCFG[9])
#define TRGMUX_CMP0 (TRGMUX0->TRGCFG[11])
#define TRGMUX_CMP1 (TRGMUX0->TRGCFG[12])
#define TRGMUX_DAC0 (TRGMUX0->TRGCFG[13])

#define TRGMUX_TPM0_INDEX ((uint16_t)((TRGMUX_INSTANCE_1 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 2)
#define TRGMUX_TPM1_INDEX ((uint16_t)((TRGMUX_INSTANCE_1 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 3)
#define TRGMUX_FLEXIO_INDEX ((uint16_t)((TRGMUX_INSTANCE_1 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 4)
#define TRGMUX_LPUART0_INDEX ((uint16_t)((TRGMUX_INSTANCE_1 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 5)
#define TRGMUX_LPUART1_INDEX ((uint16_t)((TRGMUX_INSTANCE_1 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 6)
#define TRGMUX_LPI2C0_INDEX ((uint16_t)((TRGMUX_INSTANCE_1 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 7)
#define TRGMUX_LPI2C1_INDEX ((uint16_t)((TRGMUX_INSTANCE_1 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 8)
#define TRGMUX_LPSPI0_INDEX ((uint16_t)((TRGMUX_INSTANCE_1 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 9)
#define TRGMUX_LPSPI1_INDEX ((uint16_t)((TRGMUX_INSTANCE_1 & TRGMUX_INSTANCE_MASK) << TRGMUX_INSTANCE_SHIFT) | 10)
#define TRGMUX_TPM0 (TRGMUX1->TRGCFG[2])
#define TRGMUX_TPM1 (TRGMUX1->TRGCFG[3])
#define TRGMUX_FLEXIO (TRGMUX1->TRGCFG[4])
#define TRGMUX_LPUART0 (TRGMUX1->TRGCFG[5])
#define TRGMUX_LPUART1 (TRGMUX1->TRGCFG[6])
#define TRGMUX_LPI2C0 (TRGMUX1->TRGCFG[7])
#define TRGMUX_LPI2C1 (TRGMUX1->TRGCFG[8])
#define TRGMUX_LPSPI0 (TRGMUX1->TRGCFG[9])
#define TRGMUX_LPSPI1 (TRGMUX1->TRGCFG[10])

/*!
 * @}
 */ /* end of group TRGMUX_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- TRNG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TRNG_Peripheral_Access_Layer TRNG Peripheral Access Layer
 * @{
 */

/** TRNG - Register Layout Typedef */
typedef struct
{
    __IO uint32_t MCTL;   /**< TRNG Miscellaneous Control Register, offset: 0x0 */
    __IO uint32_t SCMISC; /**< TRNG Statistical Check Miscellaneous Register, offset: 0x4 */
    __IO uint32_t PKRRNG; /**< TRNG Poker Range Register, offset: 0x8 */
    union
    {                         /* offset: 0xC */
        __IO uint32_t PKRMAX; /**< TRNG Poker Maximum Limit Register, offset: 0xC */
        __I uint32_t PKRSQ;   /**< TRNG Poker Square Calculation Result Register, offset: 0xC */
    };
    __IO uint32_t SDCTL; /**< TRNG Seed Control Register, offset: 0x10 */
    union
    {                        /* offset: 0x14 */
        __IO uint32_t SBLIM; /**< TRNG Sparse Bit Limit Register, offset: 0x14 */
        __I uint32_t TOTSAM; /**< TRNG Total Samples Register, offset: 0x14 */
    };
    __IO uint32_t FRQMIN; /**< TRNG Frequency Count Minimum Limit Register, offset: 0x18 */
    union
    {                         /* offset: 0x1C */
        __I uint32_t FRQCNT;  /**< TRNG Frequency Count Register, offset: 0x1C */
        __IO uint32_t FRQMAX; /**< TRNG Frequency Count Maximum Limit Register, offset: 0x1C */
    };
    union
    {                       /* offset: 0x20 */
        __I uint32_t SCMC;  /**< TRNG Statistical Check Monobit Count Register, offset: 0x20 */
        __IO uint32_t SCML; /**< TRNG Statistical Check Monobit Limit Register, offset: 0x20 */
    };
    union
    {                        /* offset: 0x24 */
        __I uint32_t SCR1C;  /**< TRNG Statistical Check Run Length 1 Count Register, offset: 0x24 */
        __IO uint32_t SCR1L; /**< TRNG Statistical Check Run Length 1 Limit Register, offset: 0x24 */
    };
    union
    {                        /* offset: 0x28 */
        __I uint32_t SCR2C;  /**< TRNG Statistical Check Run Length 2 Count Register, offset: 0x28 */
        __IO uint32_t SCR2L; /**< TRNG Statistical Check Run Length 2 Limit Register, offset: 0x28 */
    };
    union
    {                        /* offset: 0x2C */
        __I uint32_t SCR3C;  /**< TRNG Statistical Check Run Length 3 Count Register, offset: 0x2C */
        __IO uint32_t SCR3L; /**< TRNG Statistical Check Run Length 3 Limit Register, offset: 0x2C */
    };
    union
    {                        /* offset: 0x30 */
        __I uint32_t SCR4C;  /**< TRNG Statistical Check Run Length 4 Count Register, offset: 0x30 */
        __IO uint32_t SCR4L; /**< TRNG Statistical Check Run Length 4 Limit Register, offset: 0x30 */
    };
    union
    {                        /* offset: 0x34 */
        __I uint32_t SCR5C;  /**< TRNG Statistical Check Run Length 5 Count Register, offset: 0x34 */
        __IO uint32_t SCR5L; /**< TRNG Statistical Check Run Length 5 Limit Register, offset: 0x34 */
    };
    union
    {                         /* offset: 0x38 */
        __I uint32_t SCR6PC;  /**< TRNG Statistical Check Run Length 6+ Count Register, offset: 0x38 */
        __IO uint32_t SCR6PL; /**< TRNG Statistical Check Run Length 6+ Limit Register, offset: 0x38 */
    };
    __I uint32_t STATUS;      /**< TRNG Status Register, offset: 0x3C */
    __I uint32_t ENT[16];     /**< TRNG Entropy Read Register, array offset: 0x40, array step: 0x4 */
    __I uint32_t PKRCNT10;    /**< TRNG Statistical Check Poker Count 1 and 0 Register, offset: 0x80 */
    __I uint32_t PKRCNT32;    /**< TRNG Statistical Check Poker Count 3 and 2 Register, offset: 0x84 */
    __I uint32_t PKRCNT54;    /**< TRNG Statistical Check Poker Count 5 and 4 Register, offset: 0x88 */
    __I uint32_t PKRCNT76;    /**< TRNG Statistical Check Poker Count 7 and 6 Register, offset: 0x8C */
    __I uint32_t PKRCNT98;    /**< TRNG Statistical Check Poker Count 9 and 8 Register, offset: 0x90 */
    __I uint32_t PKRCNTBA;    /**< TRNG Statistical Check Poker Count B and A Register, offset: 0x94 */
    __I uint32_t PKRCNTDC;    /**< TRNG Statistical Check Poker Count D and C Register, offset: 0x98 */
    __I uint32_t PKRCNTFE;    /**< TRNG Statistical Check Poker Count F and E Register, offset: 0x9C */
    __IO uint32_t SEC_CFG;    /**< TRNG Security Configuration Register, offset: 0xA0 */
    __IO uint32_t INT_CTRL;   /**< TRNG Interrupt Control Register, offset: 0xA4 */
    __IO uint32_t INT_MASK;   /**< TRNG Mask Register, offset: 0xA8 */
    __IO uint32_t INT_STATUS; /**< TRNG Interrupt Status Register, offset: 0xAC */
    uint8_t RESERVED_0[64];
    __I uint32_t VID1; /**< TRNG Version ID Register (MS), offset: 0xF0 */
    __I uint32_t VID2; /**< TRNG Version ID Register (LS), offset: 0xF4 */
} TRNG_Type;

/* ----------------------------------------------------------------------------
   -- TRNG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TRNG_Register_Masks TRNG Register Masks
 * @{
 */

/*! @name MCTL - TRNG Miscellaneous Control Register */
/*! @{ */
#define TRNG_MCTL_SAMP_MODE_MASK (0x3U)
#define TRNG_MCTL_SAMP_MODE_SHIFT (0U)
/*! SAMP_MODE
 *  0b00..use Von Neumann data into both Entropy shifter and Statistical Checker
 *  0b01..use raw data into both Entropy shifter and Statistical Checker
 *  0b10..use Von Neumann data into Entropy shifter. Use raw data into Statistical Checker
 *  0b11..undefined/reserved.
 */
#define TRNG_MCTL_SAMP_MODE(x) (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_SAMP_MODE_SHIFT)) & TRNG_MCTL_SAMP_MODE_MASK)
#define TRNG_MCTL_OSC_DIV_MASK (0xCU)
#define TRNG_MCTL_OSC_DIV_SHIFT (2U)
/*! OSC_DIV
 *  0b00..use ring oscillator with no divide
 *  0b01..use ring oscillator divided-by-2
 *  0b10..use ring oscillator divided-by-4
 *  0b11..use ring oscillator divided-by-8
 */
#define TRNG_MCTL_OSC_DIV(x) (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_OSC_DIV_SHIFT)) & TRNG_MCTL_OSC_DIV_MASK)
#define TRNG_MCTL_UNUSED_MASK (0x10U)
#define TRNG_MCTL_UNUSED_SHIFT (4U)
#define TRNG_MCTL_UNUSED(x) (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_UNUSED_SHIFT)) & TRNG_MCTL_UNUSED_MASK)
#define TRNG_MCTL_TRNG_ACC_MASK (0x20U)
#define TRNG_MCTL_TRNG_ACC_SHIFT (5U)
#define TRNG_MCTL_TRNG_ACC(x) (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_TRNG_ACC_SHIFT)) & TRNG_MCTL_TRNG_ACC_MASK)
#define TRNG_MCTL_RST_DEF_MASK (0x40U)
#define TRNG_MCTL_RST_DEF_SHIFT (6U)
#define TRNG_MCTL_RST_DEF(x) (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_RST_DEF_SHIFT)) & TRNG_MCTL_RST_DEF_MASK)
#define TRNG_MCTL_FOR_SCLK_MASK (0x80U)
#define TRNG_MCTL_FOR_SCLK_SHIFT (7U)
#define TRNG_MCTL_FOR_SCLK(x) (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_FOR_SCLK_SHIFT)) & TRNG_MCTL_FOR_SCLK_MASK)
#define TRNG_MCTL_FCT_FAIL_MASK (0x100U)
#define TRNG_MCTL_FCT_FAIL_SHIFT (8U)
#define TRNG_MCTL_FCT_FAIL(x) (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_FCT_FAIL_SHIFT)) & TRNG_MCTL_FCT_FAIL_MASK)
#define TRNG_MCTL_FCT_VAL_MASK (0x200U)
#define TRNG_MCTL_FCT_VAL_SHIFT (9U)
#define TRNG_MCTL_FCT_VAL(x) (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_FCT_VAL_SHIFT)) & TRNG_MCTL_FCT_VAL_MASK)
#define TRNG_MCTL_ENT_VAL_MASK (0x400U)
#define TRNG_MCTL_ENT_VAL_SHIFT (10U)
#define TRNG_MCTL_ENT_VAL(x) (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_ENT_VAL_SHIFT)) & TRNG_MCTL_ENT_VAL_MASK)
#define TRNG_MCTL_TST_OUT_MASK (0x800U)
#define TRNG_MCTL_TST_OUT_SHIFT (11U)
#define TRNG_MCTL_TST_OUT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_TST_OUT_SHIFT)) & TRNG_MCTL_TST_OUT_MASK)
#define TRNG_MCTL_ERR_MASK (0x1000U)
#define TRNG_MCTL_ERR_SHIFT (12U)
#define TRNG_MCTL_ERR(x) (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_ERR_SHIFT)) & TRNG_MCTL_ERR_MASK)
#define TRNG_MCTL_TSTOP_OK_MASK (0x2000U)
#define TRNG_MCTL_TSTOP_OK_SHIFT (13U)
#define TRNG_MCTL_TSTOP_OK(x) (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_TSTOP_OK_SHIFT)) & TRNG_MCTL_TSTOP_OK_MASK)
#define TRNG_MCTL_PRGM_MASK (0x10000U)
#define TRNG_MCTL_PRGM_SHIFT (16U)
#define TRNG_MCTL_PRGM(x) (((uint32_t)(((uint32_t)(x)) << TRNG_MCTL_PRGM_SHIFT)) & TRNG_MCTL_PRGM_MASK)
/*! @} */

/*! @name SCMISC - TRNG Statistical Check Miscellaneous Register */
/*! @{ */
#define TRNG_SCMISC_LRUN_MAX_MASK (0xFFU)
#define TRNG_SCMISC_LRUN_MAX_SHIFT (0U)
#define TRNG_SCMISC_LRUN_MAX(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_SCMISC_LRUN_MAX_SHIFT)) & TRNG_SCMISC_LRUN_MAX_MASK)
#define TRNG_SCMISC_RTY_CT_MASK (0xF0000U)
#define TRNG_SCMISC_RTY_CT_SHIFT (16U)
#define TRNG_SCMISC_RTY_CT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCMISC_RTY_CT_SHIFT)) & TRNG_SCMISC_RTY_CT_MASK)
/*! @} */

/*! @name PKRRNG - TRNG Poker Range Register */
/*! @{ */
#define TRNG_PKRRNG_PKR_RNG_MASK (0xFFFFU)
#define TRNG_PKRRNG_PKR_RNG_SHIFT (0U)
#define TRNG_PKRRNG_PKR_RNG(x) (((uint32_t)(((uint32_t)(x)) << TRNG_PKRRNG_PKR_RNG_SHIFT)) & TRNG_PKRRNG_PKR_RNG_MASK)
/*! @} */

/*! @name PKRMAX - TRNG Poker Maximum Limit Register */
/*! @{ */
#define TRNG_PKRMAX_PKR_MAX_MASK (0xFFFFFFU)
#define TRNG_PKRMAX_PKR_MAX_SHIFT (0U)
#define TRNG_PKRMAX_PKR_MAX(x) (((uint32_t)(((uint32_t)(x)) << TRNG_PKRMAX_PKR_MAX_SHIFT)) & TRNG_PKRMAX_PKR_MAX_MASK)
/*! @} */

/*! @name PKRSQ - TRNG Poker Square Calculation Result Register */
/*! @{ */
#define TRNG_PKRSQ_PKR_SQ_MASK (0xFFFFFFU)
#define TRNG_PKRSQ_PKR_SQ_SHIFT (0U)
#define TRNG_PKRSQ_PKR_SQ(x) (((uint32_t)(((uint32_t)(x)) << TRNG_PKRSQ_PKR_SQ_SHIFT)) & TRNG_PKRSQ_PKR_SQ_MASK)
/*! @} */

/*! @name SDCTL - TRNG Seed Control Register */
/*! @{ */
#define TRNG_SDCTL_SAMP_SIZE_MASK (0xFFFFU)
#define TRNG_SDCTL_SAMP_SIZE_SHIFT (0U)
#define TRNG_SDCTL_SAMP_SIZE(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_SDCTL_SAMP_SIZE_SHIFT)) & TRNG_SDCTL_SAMP_SIZE_MASK)
#define TRNG_SDCTL_ENT_DLY_MASK (0xFFFF0000U)
#define TRNG_SDCTL_ENT_DLY_SHIFT (16U)
#define TRNG_SDCTL_ENT_DLY(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SDCTL_ENT_DLY_SHIFT)) & TRNG_SDCTL_ENT_DLY_MASK)
/*! @} */

/*! @name SBLIM - TRNG Sparse Bit Limit Register */
/*! @{ */
#define TRNG_SBLIM_SB_LIM_MASK (0x3FFU)
#define TRNG_SBLIM_SB_LIM_SHIFT (0U)
#define TRNG_SBLIM_SB_LIM(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SBLIM_SB_LIM_SHIFT)) & TRNG_SBLIM_SB_LIM_MASK)
/*! @} */

/*! @name TOTSAM - TRNG Total Samples Register */
/*! @{ */
#define TRNG_TOTSAM_TOT_SAM_MASK (0xFFFFFU)
#define TRNG_TOTSAM_TOT_SAM_SHIFT (0U)
#define TRNG_TOTSAM_TOT_SAM(x) (((uint32_t)(((uint32_t)(x)) << TRNG_TOTSAM_TOT_SAM_SHIFT)) & TRNG_TOTSAM_TOT_SAM_MASK)
/*! @} */

/*! @name FRQMIN - TRNG Frequency Count Minimum Limit Register */
/*! @{ */
#define TRNG_FRQMIN_FRQ_MIN_MASK (0x3FFFFFU)
#define TRNG_FRQMIN_FRQ_MIN_SHIFT (0U)
#define TRNG_FRQMIN_FRQ_MIN(x) (((uint32_t)(((uint32_t)(x)) << TRNG_FRQMIN_FRQ_MIN_SHIFT)) & TRNG_FRQMIN_FRQ_MIN_MASK)
/*! @} */

/*! @name FRQCNT - TRNG Frequency Count Register */
/*! @{ */
#define TRNG_FRQCNT_FRQ_CT_MASK (0x3FFFFFU)
#define TRNG_FRQCNT_FRQ_CT_SHIFT (0U)
#define TRNG_FRQCNT_FRQ_CT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_FRQCNT_FRQ_CT_SHIFT)) & TRNG_FRQCNT_FRQ_CT_MASK)
/*! @} */

/*! @name FRQMAX - TRNG Frequency Count Maximum Limit Register */
/*! @{ */
#define TRNG_FRQMAX_FRQ_MAX_MASK (0x3FFFFFU)
#define TRNG_FRQMAX_FRQ_MAX_SHIFT (0U)
#define TRNG_FRQMAX_FRQ_MAX(x) (((uint32_t)(((uint32_t)(x)) << TRNG_FRQMAX_FRQ_MAX_SHIFT)) & TRNG_FRQMAX_FRQ_MAX_MASK)
/*! @} */

/*! @name SCMC - TRNG Statistical Check Monobit Count Register */
/*! @{ */
#define TRNG_SCMC_MONO_CT_MASK (0xFFFFU)
#define TRNG_SCMC_MONO_CT_SHIFT (0U)
#define TRNG_SCMC_MONO_CT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCMC_MONO_CT_SHIFT)) & TRNG_SCMC_MONO_CT_MASK)
/*! @} */

/*! @name SCML - TRNG Statistical Check Monobit Limit Register */
/*! @{ */
#define TRNG_SCML_MONO_MAX_MASK (0xFFFFU)
#define TRNG_SCML_MONO_MAX_SHIFT (0U)
#define TRNG_SCML_MONO_MAX(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCML_MONO_MAX_SHIFT)) & TRNG_SCML_MONO_MAX_MASK)
#define TRNG_SCML_MONO_RNG_MASK (0xFFFF0000U)
#define TRNG_SCML_MONO_RNG_SHIFT (16U)
#define TRNG_SCML_MONO_RNG(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCML_MONO_RNG_SHIFT)) & TRNG_SCML_MONO_RNG_MASK)
/*! @} */

/*! @name SCR1C - TRNG Statistical Check Run Length 1 Count Register */
/*! @{ */
#define TRNG_SCR1C_R1_0_CT_MASK (0x7FFFU)
#define TRNG_SCR1C_R1_0_CT_SHIFT (0U)
#define TRNG_SCR1C_R1_0_CT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR1C_R1_0_CT_SHIFT)) & TRNG_SCR1C_R1_0_CT_MASK)
#define TRNG_SCR1C_R1_1_CT_MASK (0x7FFF0000U)
#define TRNG_SCR1C_R1_1_CT_SHIFT (16U)
#define TRNG_SCR1C_R1_1_CT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR1C_R1_1_CT_SHIFT)) & TRNG_SCR1C_R1_1_CT_MASK)
/*! @} */

/*! @name SCR1L - TRNG Statistical Check Run Length 1 Limit Register */
/*! @{ */
#define TRNG_SCR1L_RUN1_MAX_MASK (0x7FFFU)
#define TRNG_SCR1L_RUN1_MAX_SHIFT (0U)
#define TRNG_SCR1L_RUN1_MAX(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR1L_RUN1_MAX_SHIFT)) & TRNG_SCR1L_RUN1_MAX_MASK)
#define TRNG_SCR1L_RUN1_RNG_MASK (0x7FFF0000U)
#define TRNG_SCR1L_RUN1_RNG_SHIFT (16U)
#define TRNG_SCR1L_RUN1_RNG(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR1L_RUN1_RNG_SHIFT)) & TRNG_SCR1L_RUN1_RNG_MASK)
/*! @} */

/*! @name SCR2C - TRNG Statistical Check Run Length 2 Count Register */
/*! @{ */
#define TRNG_SCR2C_R2_0_CT_MASK (0x3FFFU)
#define TRNG_SCR2C_R2_0_CT_SHIFT (0U)
#define TRNG_SCR2C_R2_0_CT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR2C_R2_0_CT_SHIFT)) & TRNG_SCR2C_R2_0_CT_MASK)
#define TRNG_SCR2C_R2_1_CT_MASK (0x3FFF0000U)
#define TRNG_SCR2C_R2_1_CT_SHIFT (16U)
#define TRNG_SCR2C_R2_1_CT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR2C_R2_1_CT_SHIFT)) & TRNG_SCR2C_R2_1_CT_MASK)
/*! @} */

/*! @name SCR2L - TRNG Statistical Check Run Length 2 Limit Register */
/*! @{ */
#define TRNG_SCR2L_RUN2_MAX_MASK (0x3FFFU)
#define TRNG_SCR2L_RUN2_MAX_SHIFT (0U)
#define TRNG_SCR2L_RUN2_MAX(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR2L_RUN2_MAX_SHIFT)) & TRNG_SCR2L_RUN2_MAX_MASK)
#define TRNG_SCR2L_RUN2_RNG_MASK (0x3FFF0000U)
#define TRNG_SCR2L_RUN2_RNG_SHIFT (16U)
#define TRNG_SCR2L_RUN2_RNG(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR2L_RUN2_RNG_SHIFT)) & TRNG_SCR2L_RUN2_RNG_MASK)
/*! @} */

/*! @name SCR3C - TRNG Statistical Check Run Length 3 Count Register */
/*! @{ */
#define TRNG_SCR3C_R3_0_CT_MASK (0x1FFFU)
#define TRNG_SCR3C_R3_0_CT_SHIFT (0U)
#define TRNG_SCR3C_R3_0_CT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR3C_R3_0_CT_SHIFT)) & TRNG_SCR3C_R3_0_CT_MASK)
#define TRNG_SCR3C_R3_1_CT_MASK (0x1FFF0000U)
#define TRNG_SCR3C_R3_1_CT_SHIFT (16U)
#define TRNG_SCR3C_R3_1_CT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR3C_R3_1_CT_SHIFT)) & TRNG_SCR3C_R3_1_CT_MASK)
/*! @} */

/*! @name SCR3L - TRNG Statistical Check Run Length 3 Limit Register */
/*! @{ */
#define TRNG_SCR3L_RUN3_MAX_MASK (0x1FFFU)
#define TRNG_SCR3L_RUN3_MAX_SHIFT (0U)
#define TRNG_SCR3L_RUN3_MAX(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR3L_RUN3_MAX_SHIFT)) & TRNG_SCR3L_RUN3_MAX_MASK)
#define TRNG_SCR3L_RUN3_RNG_MASK (0x1FFF0000U)
#define TRNG_SCR3L_RUN3_RNG_SHIFT (16U)
#define TRNG_SCR3L_RUN3_RNG(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR3L_RUN3_RNG_SHIFT)) & TRNG_SCR3L_RUN3_RNG_MASK)
/*! @} */

/*! @name SCR4C - TRNG Statistical Check Run Length 4 Count Register */
/*! @{ */
#define TRNG_SCR4C_R4_0_CT_MASK (0xFFFU)
#define TRNG_SCR4C_R4_0_CT_SHIFT (0U)
#define TRNG_SCR4C_R4_0_CT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR4C_R4_0_CT_SHIFT)) & TRNG_SCR4C_R4_0_CT_MASK)
#define TRNG_SCR4C_R4_1_CT_MASK (0xFFF0000U)
#define TRNG_SCR4C_R4_1_CT_SHIFT (16U)
#define TRNG_SCR4C_R4_1_CT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR4C_R4_1_CT_SHIFT)) & TRNG_SCR4C_R4_1_CT_MASK)
/*! @} */

/*! @name SCR4L - TRNG Statistical Check Run Length 4 Limit Register */
/*! @{ */
#define TRNG_SCR4L_RUN4_MAX_MASK (0xFFFU)
#define TRNG_SCR4L_RUN4_MAX_SHIFT (0U)
#define TRNG_SCR4L_RUN4_MAX(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR4L_RUN4_MAX_SHIFT)) & TRNG_SCR4L_RUN4_MAX_MASK)
#define TRNG_SCR4L_RUN4_RNG_MASK (0xFFF0000U)
#define TRNG_SCR4L_RUN4_RNG_SHIFT (16U)
#define TRNG_SCR4L_RUN4_RNG(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR4L_RUN4_RNG_SHIFT)) & TRNG_SCR4L_RUN4_RNG_MASK)
/*! @} */

/*! @name SCR5C - TRNG Statistical Check Run Length 5 Count Register */
/*! @{ */
#define TRNG_SCR5C_R5_0_CT_MASK (0x7FFU)
#define TRNG_SCR5C_R5_0_CT_SHIFT (0U)
#define TRNG_SCR5C_R5_0_CT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR5C_R5_0_CT_SHIFT)) & TRNG_SCR5C_R5_0_CT_MASK)
#define TRNG_SCR5C_R5_1_CT_MASK (0x7FF0000U)
#define TRNG_SCR5C_R5_1_CT_SHIFT (16U)
#define TRNG_SCR5C_R5_1_CT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR5C_R5_1_CT_SHIFT)) & TRNG_SCR5C_R5_1_CT_MASK)
/*! @} */

/*! @name SCR5L - TRNG Statistical Check Run Length 5 Limit Register */
/*! @{ */
#define TRNG_SCR5L_RUN5_MAX_MASK (0x7FFU)
#define TRNG_SCR5L_RUN5_MAX_SHIFT (0U)
#define TRNG_SCR5L_RUN5_MAX(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR5L_RUN5_MAX_SHIFT)) & TRNG_SCR5L_RUN5_MAX_MASK)
#define TRNG_SCR5L_RUN5_RNG_MASK (0x7FF0000U)
#define TRNG_SCR5L_RUN5_RNG_SHIFT (16U)
#define TRNG_SCR5L_RUN5_RNG(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SCR5L_RUN5_RNG_SHIFT)) & TRNG_SCR5L_RUN5_RNG_MASK)
/*! @} */

/*! @name SCR6PC - TRNG Statistical Check Run Length 6+ Count Register */
/*! @{ */
#define TRNG_SCR6PC_R6P_0_CT_MASK (0x7FFU)
#define TRNG_SCR6PC_R6P_0_CT_SHIFT (0U)
#define TRNG_SCR6PC_R6P_0_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR6PC_R6P_0_CT_SHIFT)) & TRNG_SCR6PC_R6P_0_CT_MASK)
#define TRNG_SCR6PC_R6P_1_CT_MASK (0x7FF0000U)
#define TRNG_SCR6PC_R6P_1_CT_SHIFT (16U)
#define TRNG_SCR6PC_R6P_1_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR6PC_R6P_1_CT_SHIFT)) & TRNG_SCR6PC_R6P_1_CT_MASK)
/*! @} */

/*! @name SCR6PL - TRNG Statistical Check Run Length 6+ Limit Register */
/*! @{ */
#define TRNG_SCR6PL_RUN6P_MAX_MASK (0x7FFU)
#define TRNG_SCR6PL_RUN6P_MAX_SHIFT (0U)
#define TRNG_SCR6PL_RUN6P_MAX(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR6PL_RUN6P_MAX_SHIFT)) & TRNG_SCR6PL_RUN6P_MAX_MASK)
#define TRNG_SCR6PL_RUN6P_RNG_MASK (0x7FF0000U)
#define TRNG_SCR6PL_RUN6P_RNG_SHIFT (16U)
#define TRNG_SCR6PL_RUN6P_RNG(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_SCR6PL_RUN6P_RNG_SHIFT)) & TRNG_SCR6PL_RUN6P_RNG_MASK)
/*! @} */

/*! @name STATUS - TRNG Status Register */
/*! @{ */
#define TRNG_STATUS_TF1BR0_MASK (0x1U)
#define TRNG_STATUS_TF1BR0_SHIFT (0U)
#define TRNG_STATUS_TF1BR0(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF1BR0_SHIFT)) & TRNG_STATUS_TF1BR0_MASK)
#define TRNG_STATUS_TF1BR1_MASK (0x2U)
#define TRNG_STATUS_TF1BR1_SHIFT (1U)
#define TRNG_STATUS_TF1BR1(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF1BR1_SHIFT)) & TRNG_STATUS_TF1BR1_MASK)
#define TRNG_STATUS_TF2BR0_MASK (0x4U)
#define TRNG_STATUS_TF2BR0_SHIFT (2U)
#define TRNG_STATUS_TF2BR0(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF2BR0_SHIFT)) & TRNG_STATUS_TF2BR0_MASK)
#define TRNG_STATUS_TF2BR1_MASK (0x8U)
#define TRNG_STATUS_TF2BR1_SHIFT (3U)
#define TRNG_STATUS_TF2BR1(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF2BR1_SHIFT)) & TRNG_STATUS_TF2BR1_MASK)
#define TRNG_STATUS_TF3BR0_MASK (0x10U)
#define TRNG_STATUS_TF3BR0_SHIFT (4U)
#define TRNG_STATUS_TF3BR0(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF3BR0_SHIFT)) & TRNG_STATUS_TF3BR0_MASK)
#define TRNG_STATUS_TF3BR1_MASK (0x20U)
#define TRNG_STATUS_TF3BR1_SHIFT (5U)
#define TRNG_STATUS_TF3BR1(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF3BR1_SHIFT)) & TRNG_STATUS_TF3BR1_MASK)
#define TRNG_STATUS_TF4BR0_MASK (0x40U)
#define TRNG_STATUS_TF4BR0_SHIFT (6U)
#define TRNG_STATUS_TF4BR0(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF4BR0_SHIFT)) & TRNG_STATUS_TF4BR0_MASK)
#define TRNG_STATUS_TF4BR1_MASK (0x80U)
#define TRNG_STATUS_TF4BR1_SHIFT (7U)
#define TRNG_STATUS_TF4BR1(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF4BR1_SHIFT)) & TRNG_STATUS_TF4BR1_MASK)
#define TRNG_STATUS_TF5BR0_MASK (0x100U)
#define TRNG_STATUS_TF5BR0_SHIFT (8U)
#define TRNG_STATUS_TF5BR0(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF5BR0_SHIFT)) & TRNG_STATUS_TF5BR0_MASK)
#define TRNG_STATUS_TF5BR1_MASK (0x200U)
#define TRNG_STATUS_TF5BR1_SHIFT (9U)
#define TRNG_STATUS_TF5BR1(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF5BR1_SHIFT)) & TRNG_STATUS_TF5BR1_MASK)
#define TRNG_STATUS_TF6PBR0_MASK (0x400U)
#define TRNG_STATUS_TF6PBR0_SHIFT (10U)
#define TRNG_STATUS_TF6PBR0(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF6PBR0_SHIFT)) & TRNG_STATUS_TF6PBR0_MASK)
#define TRNG_STATUS_TF6PBR1_MASK (0x800U)
#define TRNG_STATUS_TF6PBR1_SHIFT (11U)
#define TRNG_STATUS_TF6PBR1(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TF6PBR1_SHIFT)) & TRNG_STATUS_TF6PBR1_MASK)
#define TRNG_STATUS_TFSB_MASK (0x1000U)
#define TRNG_STATUS_TFSB_SHIFT (12U)
#define TRNG_STATUS_TFSB(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TFSB_SHIFT)) & TRNG_STATUS_TFSB_MASK)
#define TRNG_STATUS_TFLR_MASK (0x2000U)
#define TRNG_STATUS_TFLR_SHIFT (13U)
#define TRNG_STATUS_TFLR(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TFLR_SHIFT)) & TRNG_STATUS_TFLR_MASK)
#define TRNG_STATUS_TFP_MASK (0x4000U)
#define TRNG_STATUS_TFP_SHIFT (14U)
#define TRNG_STATUS_TFP(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TFP_SHIFT)) & TRNG_STATUS_TFP_MASK)
#define TRNG_STATUS_TFMB_MASK (0x8000U)
#define TRNG_STATUS_TFMB_SHIFT (15U)
#define TRNG_STATUS_TFMB(x) (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_TFMB_SHIFT)) & TRNG_STATUS_TFMB_MASK)
#define TRNG_STATUS_RETRY_CT_MASK (0xF0000U)
#define TRNG_STATUS_RETRY_CT_SHIFT (16U)
#define TRNG_STATUS_RETRY_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_STATUS_RETRY_CT_SHIFT)) & TRNG_STATUS_RETRY_CT_MASK)
/*! @} */

/*! @name ENT - TRNG Entropy Read Register */
/*! @{ */
#define TRNG_ENT_ENT_MASK (0xFFFFFFFFU)
#define TRNG_ENT_ENT_SHIFT (0U)
#define TRNG_ENT_ENT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_ENT_ENT_SHIFT)) & TRNG_ENT_ENT_MASK)
/*! @} */

/* The count of TRNG_ENT */
#define TRNG_ENT_COUNT (16U)

/*! @name PKRCNT10 - TRNG Statistical Check Poker Count 1 and 0 Register */
/*! @{ */
#define TRNG_PKRCNT10_PKR_0_CT_MASK (0xFFFFU)
#define TRNG_PKRCNT10_PKR_0_CT_SHIFT (0U)
#define TRNG_PKRCNT10_PKR_0_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT10_PKR_0_CT_SHIFT)) & TRNG_PKRCNT10_PKR_0_CT_MASK)
#define TRNG_PKRCNT10_PKR_1_CT_MASK (0xFFFF0000U)
#define TRNG_PKRCNT10_PKR_1_CT_SHIFT (16U)
#define TRNG_PKRCNT10_PKR_1_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT10_PKR_1_CT_SHIFT)) & TRNG_PKRCNT10_PKR_1_CT_MASK)
/*! @} */

/*! @name PKRCNT32 - TRNG Statistical Check Poker Count 3 and 2 Register */
/*! @{ */
#define TRNG_PKRCNT32_PKR_2_CT_MASK (0xFFFFU)
#define TRNG_PKRCNT32_PKR_2_CT_SHIFT (0U)
#define TRNG_PKRCNT32_PKR_2_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT32_PKR_2_CT_SHIFT)) & TRNG_PKRCNT32_PKR_2_CT_MASK)
#define TRNG_PKRCNT32_PKR_3_CT_MASK (0xFFFF0000U)
#define TRNG_PKRCNT32_PKR_3_CT_SHIFT (16U)
#define TRNG_PKRCNT32_PKR_3_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT32_PKR_3_CT_SHIFT)) & TRNG_PKRCNT32_PKR_3_CT_MASK)
/*! @} */

/*! @name PKRCNT54 - TRNG Statistical Check Poker Count 5 and 4 Register */
/*! @{ */
#define TRNG_PKRCNT54_PKR_4_CT_MASK (0xFFFFU)
#define TRNG_PKRCNT54_PKR_4_CT_SHIFT (0U)
#define TRNG_PKRCNT54_PKR_4_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT54_PKR_4_CT_SHIFT)) & TRNG_PKRCNT54_PKR_4_CT_MASK)
#define TRNG_PKRCNT54_PKR_5_CT_MASK (0xFFFF0000U)
#define TRNG_PKRCNT54_PKR_5_CT_SHIFT (16U)
#define TRNG_PKRCNT54_PKR_5_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT54_PKR_5_CT_SHIFT)) & TRNG_PKRCNT54_PKR_5_CT_MASK)
/*! @} */

/*! @name PKRCNT76 - TRNG Statistical Check Poker Count 7 and 6 Register */
/*! @{ */
#define TRNG_PKRCNT76_PKR_6_CT_MASK (0xFFFFU)
#define TRNG_PKRCNT76_PKR_6_CT_SHIFT (0U)
#define TRNG_PKRCNT76_PKR_6_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT76_PKR_6_CT_SHIFT)) & TRNG_PKRCNT76_PKR_6_CT_MASK)
#define TRNG_PKRCNT76_PKR_7_CT_MASK (0xFFFF0000U)
#define TRNG_PKRCNT76_PKR_7_CT_SHIFT (16U)
#define TRNG_PKRCNT76_PKR_7_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT76_PKR_7_CT_SHIFT)) & TRNG_PKRCNT76_PKR_7_CT_MASK)
/*! @} */

/*! @name PKRCNT98 - TRNG Statistical Check Poker Count 9 and 8 Register */
/*! @{ */
#define TRNG_PKRCNT98_PKR_8_CT_MASK (0xFFFFU)
#define TRNG_PKRCNT98_PKR_8_CT_SHIFT (0U)
#define TRNG_PKRCNT98_PKR_8_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT98_PKR_8_CT_SHIFT)) & TRNG_PKRCNT98_PKR_8_CT_MASK)
#define TRNG_PKRCNT98_PKR_9_CT_MASK (0xFFFF0000U)
#define TRNG_PKRCNT98_PKR_9_CT_SHIFT (16U)
#define TRNG_PKRCNT98_PKR_9_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNT98_PKR_9_CT_SHIFT)) & TRNG_PKRCNT98_PKR_9_CT_MASK)
/*! @} */

/*! @name PKRCNTBA - TRNG Statistical Check Poker Count B and A Register */
/*! @{ */
#define TRNG_PKRCNTBA_PKR_A_CT_MASK (0xFFFFU)
#define TRNG_PKRCNTBA_PKR_A_CT_SHIFT (0U)
#define TRNG_PKRCNTBA_PKR_A_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNTBA_PKR_A_CT_SHIFT)) & TRNG_PKRCNTBA_PKR_A_CT_MASK)
#define TRNG_PKRCNTBA_PKR_B_CT_MASK (0xFFFF0000U)
#define TRNG_PKRCNTBA_PKR_B_CT_SHIFT (16U)
#define TRNG_PKRCNTBA_PKR_B_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNTBA_PKR_B_CT_SHIFT)) & TRNG_PKRCNTBA_PKR_B_CT_MASK)
/*! @} */

/*! @name PKRCNTDC - TRNG Statistical Check Poker Count D and C Register */
/*! @{ */
#define TRNG_PKRCNTDC_PKR_C_CT_MASK (0xFFFFU)
#define TRNG_PKRCNTDC_PKR_C_CT_SHIFT (0U)
#define TRNG_PKRCNTDC_PKR_C_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNTDC_PKR_C_CT_SHIFT)) & TRNG_PKRCNTDC_PKR_C_CT_MASK)
#define TRNG_PKRCNTDC_PKR_D_CT_MASK (0xFFFF0000U)
#define TRNG_PKRCNTDC_PKR_D_CT_SHIFT (16U)
#define TRNG_PKRCNTDC_PKR_D_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNTDC_PKR_D_CT_SHIFT)) & TRNG_PKRCNTDC_PKR_D_CT_MASK)
/*! @} */

/*! @name PKRCNTFE - TRNG Statistical Check Poker Count F and E Register */
/*! @{ */
#define TRNG_PKRCNTFE_PKR_E_CT_MASK (0xFFFFU)
#define TRNG_PKRCNTFE_PKR_E_CT_SHIFT (0U)
#define TRNG_PKRCNTFE_PKR_E_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNTFE_PKR_E_CT_SHIFT)) & TRNG_PKRCNTFE_PKR_E_CT_MASK)
#define TRNG_PKRCNTFE_PKR_F_CT_MASK (0xFFFF0000U)
#define TRNG_PKRCNTFE_PKR_F_CT_SHIFT (16U)
#define TRNG_PKRCNTFE_PKR_F_CT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_PKRCNTFE_PKR_F_CT_SHIFT)) & TRNG_PKRCNTFE_PKR_F_CT_MASK)
/*! @} */

/*! @name SEC_CFG - TRNG Security Configuration Register */
/*! @{ */
#define TRNG_SEC_CFG_SH0_MASK (0x1U)
#define TRNG_SEC_CFG_SH0_SHIFT (0U)
/*! SH0
 *  0b0..See DRNG version.
 *  0b1..See DRNG version.
 */
#define TRNG_SEC_CFG_SH0(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SEC_CFG_SH0_SHIFT)) & TRNG_SEC_CFG_SH0_MASK)
#define TRNG_SEC_CFG_NO_PRGM_MASK (0x2U)
#define TRNG_SEC_CFG_NO_PRGM_SHIFT (1U)
/*! NO_PRGM
 *  0b0..Programability of registers controlled only by the TRNG Miscellaneous Control Register's access mode bit.
 *  0b1..Overides TRNG Miscellaneous Control Register access mode and prevents TRNG register programming.
 */
#define TRNG_SEC_CFG_NO_PRGM(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_SEC_CFG_NO_PRGM_SHIFT)) & TRNG_SEC_CFG_NO_PRGM_MASK)
#define TRNG_SEC_CFG_SK_VAL_MASK (0x4U)
#define TRNG_SEC_CFG_SK_VAL_SHIFT (2U)
/*! SK_VAL
 *  0b0..See DRNG version.
 *  0b1..See DRNG version.
 */
#define TRNG_SEC_CFG_SK_VAL(x) (((uint32_t)(((uint32_t)(x)) << TRNG_SEC_CFG_SK_VAL_SHIFT)) & TRNG_SEC_CFG_SK_VAL_MASK)
/*! @} */

/*! @name INT_CTRL - TRNG Interrupt Control Register */
/*! @{ */
#define TRNG_INT_CTRL_HW_ERR_MASK (0x1U)
#define TRNG_INT_CTRL_HW_ERR_SHIFT (0U)
/*! HW_ERR
 *  0b0..Corresponding bit of INT_STATUS cleared.
 *  0b1..Corresponding bit of INT_STATUS active.
 */
#define TRNG_INT_CTRL_HW_ERR(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_INT_CTRL_HW_ERR_SHIFT)) & TRNG_INT_CTRL_HW_ERR_MASK)
#define TRNG_INT_CTRL_ENT_VAL_MASK (0x2U)
#define TRNG_INT_CTRL_ENT_VAL_SHIFT (1U)
/*! ENT_VAL
 *  0b0..Same behavior as bit 0 above.
 *  0b1..Same behavior as bit 0 above.
 */
#define TRNG_INT_CTRL_ENT_VAL(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_INT_CTRL_ENT_VAL_SHIFT)) & TRNG_INT_CTRL_ENT_VAL_MASK)
#define TRNG_INT_CTRL_FRQ_CT_FAIL_MASK (0x4U)
#define TRNG_INT_CTRL_FRQ_CT_FAIL_SHIFT (2U)
/*! FRQ_CT_FAIL
 *  0b0..Same behavior as bit 0 above.
 *  0b1..Same behavior as bit 0 above.
 */
#define TRNG_INT_CTRL_FRQ_CT_FAIL(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_INT_CTRL_FRQ_CT_FAIL_SHIFT)) & TRNG_INT_CTRL_FRQ_CT_FAIL_MASK)
#define TRNG_INT_CTRL_UNUSED_MASK (0xFFFFFFF8U)
#define TRNG_INT_CTRL_UNUSED_SHIFT (3U)
#define TRNG_INT_CTRL_UNUSED(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_INT_CTRL_UNUSED_SHIFT)) & TRNG_INT_CTRL_UNUSED_MASK)
/*! @} */

/*! @name INT_MASK - TRNG Mask Register */
/*! @{ */
#define TRNG_INT_MASK_HW_ERR_MASK (0x1U)
#define TRNG_INT_MASK_HW_ERR_SHIFT (0U)
/*! HW_ERR
 *  0b0..Corresponding interrupt of INT_STATUS is masked.
 *  0b1..Corresponding bit of INT_STATUS is active.
 */
#define TRNG_INT_MASK_HW_ERR(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_INT_MASK_HW_ERR_SHIFT)) & TRNG_INT_MASK_HW_ERR_MASK)
#define TRNG_INT_MASK_ENT_VAL_MASK (0x2U)
#define TRNG_INT_MASK_ENT_VAL_SHIFT (1U)
/*! ENT_VAL
 *  0b0..Same behavior as bit 0 above.
 *  0b1..Same behavior as bit 0 above.
 */
#define TRNG_INT_MASK_ENT_VAL(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_INT_MASK_ENT_VAL_SHIFT)) & TRNG_INT_MASK_ENT_VAL_MASK)
#define TRNG_INT_MASK_FRQ_CT_FAIL_MASK (0x4U)
#define TRNG_INT_MASK_FRQ_CT_FAIL_SHIFT (2U)
/*! FRQ_CT_FAIL
 *  0b0..Same behavior as bit 0 above.
 *  0b1..Same behavior as bit 0 above.
 */
#define TRNG_INT_MASK_FRQ_CT_FAIL(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_INT_MASK_FRQ_CT_FAIL_SHIFT)) & TRNG_INT_MASK_FRQ_CT_FAIL_MASK)
/*! @} */

/*! @name INT_STATUS - TRNG Interrupt Status Register */
/*! @{ */
#define TRNG_INT_STATUS_HW_ERR_MASK (0x1U)
#define TRNG_INT_STATUS_HW_ERR_SHIFT (0U)
/*! HW_ERR
 *  0b0..no error
 *  0b1..error detected.
 */
#define TRNG_INT_STATUS_HW_ERR(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_INT_STATUS_HW_ERR_SHIFT)) & TRNG_INT_STATUS_HW_ERR_MASK)
#define TRNG_INT_STATUS_ENT_VAL_MASK (0x2U)
#define TRNG_INT_STATUS_ENT_VAL_SHIFT (1U)
/*! ENT_VAL
 *  0b0..Busy generation entropy. Any value read is invalid.
 *  0b1..TRNG can be stopped and entropy is valid if read.
 */
#define TRNG_INT_STATUS_ENT_VAL(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_INT_STATUS_ENT_VAL_SHIFT)) & TRNG_INT_STATUS_ENT_VAL_MASK)
#define TRNG_INT_STATUS_FRQ_CT_FAIL_MASK (0x4U)
#define TRNG_INT_STATUS_FRQ_CT_FAIL_SHIFT (2U)
/*! FRQ_CT_FAIL
 *  0b0..No hardware nor self test frequency errors.
 *  0b1..The frequency counter has detected a failure.
 */
#define TRNG_INT_STATUS_FRQ_CT_FAIL(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_INT_STATUS_FRQ_CT_FAIL_SHIFT)) & TRNG_INT_STATUS_FRQ_CT_FAIL_MASK)
/*! @} */

/*! @name VID1 - TRNG Version ID Register (MS) */
/*! @{ */
#define TRNG_VID1_MIN_REV_MASK (0xFFU)
#define TRNG_VID1_MIN_REV_SHIFT (0U)
/*! MIN_REV
 *  0b00000000..Minor revision number for TRNG.
 */
#define TRNG_VID1_MIN_REV(x) (((uint32_t)(((uint32_t)(x)) << TRNG_VID1_MIN_REV_SHIFT)) & TRNG_VID1_MIN_REV_MASK)
#define TRNG_VID1_MAJ_REV_MASK (0xFF00U)
#define TRNG_VID1_MAJ_REV_SHIFT (8U)
/*! MAJ_REV
 *  0b00000001..Major revision number for TRNG.
 */
#define TRNG_VID1_MAJ_REV(x) (((uint32_t)(((uint32_t)(x)) << TRNG_VID1_MAJ_REV_SHIFT)) & TRNG_VID1_MAJ_REV_MASK)
#define TRNG_VID1_IP_ID_MASK (0xFFFF0000U)
#define TRNG_VID1_IP_ID_SHIFT (16U)
/*! IP_ID
 *  0b0000000000110000..ID for TRNG.
 */
#define TRNG_VID1_IP_ID(x) (((uint32_t)(((uint32_t)(x)) << TRNG_VID1_IP_ID_SHIFT)) & TRNG_VID1_IP_ID_MASK)
/*! @} */

/*! @name VID2 - TRNG Version ID Register (LS) */
/*! @{ */
#define TRNG_VID2_CONFIG_OPT_MASK (0xFFU)
#define TRNG_VID2_CONFIG_OPT_SHIFT (0U)
/*! CONFIG_OPT
 *  0b00000000..TRNG_CONFIG_OPT for TRNG.
 */
#define TRNG_VID2_CONFIG_OPT(x) \
    (((uint32_t)(((uint32_t)(x)) << TRNG_VID2_CONFIG_OPT_SHIFT)) & TRNG_VID2_CONFIG_OPT_MASK)
#define TRNG_VID2_ECO_REV_MASK (0xFF00U)
#define TRNG_VID2_ECO_REV_SHIFT (8U)
/*! ECO_REV
 *  0b00000000..TRNG_ECO_REV for TRNG.
 */
#define TRNG_VID2_ECO_REV(x) (((uint32_t)(((uint32_t)(x)) << TRNG_VID2_ECO_REV_SHIFT)) & TRNG_VID2_ECO_REV_MASK)
#define TRNG_VID2_INTG_OPT_MASK (0xFF0000U)
#define TRNG_VID2_INTG_OPT_SHIFT (16U)
/*! INTG_OPT
 *  0b00000000..INTG_OPT for TRNG.
 */
#define TRNG_VID2_INTG_OPT(x) (((uint32_t)(((uint32_t)(x)) << TRNG_VID2_INTG_OPT_SHIFT)) & TRNG_VID2_INTG_OPT_MASK)
#define TRNG_VID2_ERA_MASK (0xFF000000U)
#define TRNG_VID2_ERA_SHIFT (24U)
/*! ERA
 *  0b00000000..COMPILE_OPT for TRNG.
 */
#define TRNG_VID2_ERA(x) (((uint32_t)(((uint32_t)(x)) << TRNG_VID2_ERA_SHIFT)) & TRNG_VID2_ERA_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group TRNG_Register_Masks */

/* TRNG - Peripheral instance base addresses */
/** Peripheral TRNG base address */
#define TRNG_BASE (0x400A5000u)
/** Peripheral TRNG base pointer */
#define TRNG ((TRNG_Type *)TRNG_BASE)
/** Array initializer of TRNG peripheral base addresses */
#define TRNG_BASE_ADDRS \
    {                   \
        TRNG_BASE       \
    }
/** Array initializer of TRNG peripheral base pointers */
#define TRNG_BASE_PTRS \
    {                  \
        TRNG           \
    }
/** Interrupt vectors for the TRNG peripheral type */
#define TRNG_IRQS \
    {             \
        TRNG_IRQn \
    }

/*!
 * @}
 */ /* end of group TRNG_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- TSI Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TSI_Peripheral_Access_Layer TSI Peripheral Access Layer
 * @{
 */

/** TSI - Register Layout Typedef */
typedef struct
{
    __IO uint32_t GENCS; /**< TSI General Control and Status Register, offset: 0x0 */
    __IO uint32_t DATA;  /**< TSI DATA Register, offset: 0x4 */
    __IO uint32_t TSHD;  /**< TSI Threshold Register, offset: 0x8 */
} TSI_Type;

/* ----------------------------------------------------------------------------
   -- TSI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TSI_Register_Masks TSI Register Masks
 * @{
 */

/*! @name GENCS - TSI General Control and Status Register */
/*! @{ */
#define TSI_GENCS_EOSDMEO_MASK (0x1U)
#define TSI_GENCS_EOSDMEO_SHIFT (0U)
/*! EOSDMEO - End-of-Scan DMA Transfer Request Enable Only
 *  0b0..Do not enable the End-of-Scan DMA transfer request only. Depending on ESOR state, either Out-of-Range or
 *       End-of-Scan can trigger a DMA transfer request and interrupt.
 *  0b1..Only the End-of-Scan event can trigger a DMA transfer request. The Out-of-Range event only and always triggers
 * an interrupt if TSIIE is set.
 */
#define TSI_GENCS_EOSDMEO(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_EOSDMEO_SHIFT)) & TSI_GENCS_EOSDMEO_MASK)
#define TSI_GENCS_CURSW_MASK (0x2U)
#define TSI_GENCS_CURSW_SHIFT (1U)
/*! CURSW - CURSW
 *  0b0..The current source pair are not swapped.
 *  0b1..The current source pair are swapped.
 */
#define TSI_GENCS_CURSW(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_CURSW_SHIFT)) & TSI_GENCS_CURSW_MASK)
#define TSI_GENCS_EOSF_MASK (0x4U)
#define TSI_GENCS_EOSF_SHIFT (2U)
/*! EOSF - End of Scan Flag
 *  0b0..Scan not complete.
 *  0b1..Scan complete.
 */
#define TSI_GENCS_EOSF(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_EOSF_SHIFT)) & TSI_GENCS_EOSF_MASK)
#define TSI_GENCS_SCNIP_MASK (0x8U)
#define TSI_GENCS_SCNIP_SHIFT (3U)
/*! SCNIP - Scan In Progress Status
 *  0b0..No scan in progress.
 *  0b1..Scan in progress.
 */
#define TSI_GENCS_SCNIP(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_SCNIP_SHIFT)) & TSI_GENCS_SCNIP_MASK)
#define TSI_GENCS_STM_MASK (0x10U)
#define TSI_GENCS_STM_SHIFT (4U)
/*! STM - Scan Trigger Mode
 *  0b0..Software trigger scan.
 *  0b1..Hardware trigger scan.
 */
#define TSI_GENCS_STM(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_STM_SHIFT)) & TSI_GENCS_STM_MASK)
#define TSI_GENCS_STPE_MASK (0x20U)
#define TSI_GENCS_STPE_SHIFT (5U)
/*! STPE - TSI STOP Enable
 *  0b0..TSI is disabled when MCU goes into low power mode.
 *  0b1..Allows TSI to continue running in all low power modes.
 */
#define TSI_GENCS_STPE(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_STPE_SHIFT)) & TSI_GENCS_STPE_MASK)
#define TSI_GENCS_TSIIEN_MASK (0x40U)
#define TSI_GENCS_TSIIEN_SHIFT (6U)
/*! TSIIEN - Touch Sensing Input Interrupt Enable
 *  0b0..TSI interrupt is disabled.
 *  0b1..TSI interrupt is enabled.
 */
#define TSI_GENCS_TSIIEN(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_TSIIEN_SHIFT)) & TSI_GENCS_TSIIEN_MASK)
#define TSI_GENCS_TSIEN_MASK (0x80U)
#define TSI_GENCS_TSIEN_SHIFT (7U)
/*! TSIEN - Touch Sensing Input Module Enable
 *  0b0..TSI module disabled.
 *  0b1..TSI module enabled.
 */
#define TSI_GENCS_TSIEN(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_TSIEN_SHIFT)) & TSI_GENCS_TSIEN_MASK)
#define TSI_GENCS_NSCN_MASK (0x1F00U)
#define TSI_GENCS_NSCN_SHIFT (8U)
/*! NSCN - NSCN
 *  0b00000..Once per electrode
 *  0b00001..Twice per electrode
 *  0b00010..3 times per electrode
 *  0b00011..4 times per electrode
 *  0b00100..5 times per electrode
 *  0b00101..6 times per electrode
 *  0b00110..7 times per electrode
 *  0b00111..8 times per electrode
 *  0b01000..9 times per electrode
 *  0b01001..10 times per electrode
 *  0b01010..11 times per electrode
 *  0b01011..12 times per electrode
 *  0b01100..13 times per electrode
 *  0b01101..14 times per electrode
 *  0b01110..15 times per electrode
 *  0b01111..16 times per electrode
 *  0b10000..17 times per electrode
 *  0b10001..18 times per electrode
 *  0b10010..19 times per electrode
 *  0b10011..20 times per electrode
 *  0b10100..21 times per electrode
 *  0b10101..22 times per electrode
 *  0b10110..23 times per electrode
 *  0b10111..24 times per electrode
 *  0b11000..25 times per electrode
 *  0b11001..26 times per electrode
 *  0b11010..27 times per electrode
 *  0b11011..28 times per electrode
 *  0b11100..29 times per electrode
 *  0b11101..30 times per electrode
 *  0b11110..31 times per electrode
 *  0b11111..32 times per electrode
 */
#define TSI_GENCS_NSCN(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_NSCN_SHIFT)) & TSI_GENCS_NSCN_MASK)
#define TSI_GENCS_PS_MASK (0xE000U)
#define TSI_GENCS_PS_SHIFT (13U)
/*! PS - PS
 *  0b000..Electrode Oscillator Frequency divided by 1
 *  0b001..Electrode Oscillator Frequency divided by 2
 *  0b010..Electrode Oscillator Frequency divided by 4
 *  0b011..Electrode Oscillator Frequency divided by 8
 *  0b100..Electrode Oscillator Frequency divided by 16
 *  0b101..Electrode Oscillator Frequency divided by 32
 *  0b110..Electrode Oscillator Frequency divided by 64
 *  0b111..Electrode Oscillator Frequency divided by 128
 */
#define TSI_GENCS_PS(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_PS_SHIFT)) & TSI_GENCS_PS_MASK)
#define TSI_GENCS_EXTCHRG_MASK (0x70000U)
#define TSI_GENCS_EXTCHRG_SHIFT (16U)
/*! EXTCHRG - EXTCHRG
 *  0b000..500 nA.
 *  0b001..1 uA.
 *  0b010..2 uA.
 *  0b011..4 uA.
 *  0b100..8 uA.
 *  0b101..16 uA.
 *  0b110..32 uA.
 *  0b111..64 uA.
 */
#define TSI_GENCS_EXTCHRG(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_EXTCHRG_SHIFT)) & TSI_GENCS_EXTCHRG_MASK)
#define TSI_GENCS_DVOLT_MASK (0x180000U)
#define TSI_GENCS_DVOLT_SHIFT (19U)
/*! DVOLT - DVOLT
 *  0b00..DV = 1.026 V; VP = 1.328 V; Vm = 0.302 V.
 *  0b01..DV = 0.592 V; VP = 1.111 V; Vm = 0.519 V.
 *  0b10..DV = 0.342 V; VP = 0.986 V; Vm = 0.644 V.
 *  0b11..DV = 0.197 V; VP = 0.914 V; Vm = 0.716 V.
 */
#define TSI_GENCS_DVOLT(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_DVOLT_SHIFT)) & TSI_GENCS_DVOLT_MASK)
#define TSI_GENCS_REFCHRG_MASK (0xE00000U)
#define TSI_GENCS_REFCHRG_SHIFT (21U)
/*! REFCHRG - REFCHRG
 *  0b000..500 nA.
 *  0b001..1 uA.
 *  0b010..2 uA.
 *  0b011..4 uA.
 *  0b100..8 uA.
 *  0b101..16 uA.
 *  0b110..32 uA.
 *  0b111..64 uA.
 */
#define TSI_GENCS_REFCHRG(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_REFCHRG_SHIFT)) & TSI_GENCS_REFCHRG_MASK)
#define TSI_GENCS_MODE_MASK (0xF000000U)
#define TSI_GENCS_MODE_SHIFT (24U)
/*! MODE - TSI analog modes setup and status
 *  0b0000..Set TSI in capacitive sensing(non-noise detection) mode.
 *  0b0100..Set TSI analog to work in single threshold noise detection mode and the frequency limitation circuit is
 * disabled. 0b1000..Set TSI analog to work in single threshold noise detection mode and the frequency limitation
 * circuit is enabled to work in higher frequencies operations. 0b1100..Set TSI analog to work in automatic noise
 * detection mode.
 */
#define TSI_GENCS_MODE(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_MODE_SHIFT)) & TSI_GENCS_MODE_MASK)
#define TSI_GENCS_ESOR_MASK (0x10000000U)
#define TSI_GENCS_ESOR_SHIFT (28U)
/*! ESOR - End-of-scan or Out-of-Range Interrupt Selection
 *  0b0..Out-of-range interrupt is allowed.
 *  0b1..End-of-scan interrupt is allowed.
 */
#define TSI_GENCS_ESOR(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_ESOR_SHIFT)) & TSI_GENCS_ESOR_MASK)
#define TSI_GENCS_OUTRGF_MASK (0x80000000U)
#define TSI_GENCS_OUTRGF_SHIFT (31U)
/*! OUTRGF - Out of Range Flag.
 */
#define TSI_GENCS_OUTRGF(x) (((uint32_t)(((uint32_t)(x)) << TSI_GENCS_OUTRGF_SHIFT)) & TSI_GENCS_OUTRGF_MASK)
/*! @} */

/*! @name DATA - TSI DATA Register */
/*! @{ */
#define TSI_DATA_TSICNT_MASK (0xFFFFU)
#define TSI_DATA_TSICNT_SHIFT (0U)
/*! TSICNT - TSI Conversion Counter Value
 */
#define TSI_DATA_TSICNT(x) (((uint32_t)(((uint32_t)(x)) << TSI_DATA_TSICNT_SHIFT)) & TSI_DATA_TSICNT_MASK)
#define TSI_DATA_SWTS_MASK (0x400000U)
#define TSI_DATA_SWTS_SHIFT (22U)
/*! SWTS - Software Trigger Start
 *  0b0..No effect.
 *  0b1..Start a scan to determine which channel is specified by TSI_DATA[TSICH].
 */
#define TSI_DATA_SWTS(x) (((uint32_t)(((uint32_t)(x)) << TSI_DATA_SWTS_SHIFT)) & TSI_DATA_SWTS_MASK)
#define TSI_DATA_DMAEN_MASK (0x800000U)
#define TSI_DATA_DMAEN_SHIFT (23U)
/*! DMAEN - DMA Transfer Enabled
 *  0b0..Interrupt is selected when the interrupt enable bit is set and the corresponding TSI events assert.
 *  0b1..DMA transfer request is selected when the interrupt enable bit is set and the corresponding TSI events assert.
 */
#define TSI_DATA_DMAEN(x) (((uint32_t)(((uint32_t)(x)) << TSI_DATA_DMAEN_SHIFT)) & TSI_DATA_DMAEN_MASK)
#define TSI_DATA_TSICH_MASK (0xF0000000U)
#define TSI_DATA_TSICH_SHIFT (28U)
/*! TSICH - TSICH
 *  0b0000..Channel 0.
 *  0b0001..Channel 1.
 *  0b0010..Channel 2.
 *  0b0011..Channel 3.
 *  0b0100..Channel 4.
 *  0b0101..Channel 5.
 *  0b0110..Channel 6.
 *  0b0111..Channel 7.
 *  0b1000..Channel 8.
 *  0b1001..Channel 9.
 *  0b1010..Channel 10.
 *  0b1011..Channel 11.
 *  0b1100..Channel 12.
 *  0b1101..Channel 13.
 *  0b1110..Channel 14.
 *  0b1111..Channel 15.
 */
#define TSI_DATA_TSICH(x) (((uint32_t)(((uint32_t)(x)) << TSI_DATA_TSICH_SHIFT)) & TSI_DATA_TSICH_MASK)
/*! @} */

/*! @name TSHD - TSI Threshold Register */
/*! @{ */
#define TSI_TSHD_THRESL_MASK (0xFFFFU)
#define TSI_TSHD_THRESL_SHIFT (0U)
/*! THRESL - TSI Wakeup Channel Low-threshold
 */
#define TSI_TSHD_THRESL(x) (((uint32_t)(((uint32_t)(x)) << TSI_TSHD_THRESL_SHIFT)) & TSI_TSHD_THRESL_MASK)
#define TSI_TSHD_THRESH_MASK (0xFFFF0000U)
#define TSI_TSHD_THRESH_SHIFT (16U)
/*! THRESH - TSI Wakeup Channel High-threshold
 */
#define TSI_TSHD_THRESH(x) (((uint32_t)(((uint32_t)(x)) << TSI_TSHD_THRESH_SHIFT)) & TSI_TSHD_THRESH_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group TSI_Register_Masks */

/* TSI - Peripheral instance base addresses */
/** Peripheral TSI0 base address */
#define TSI0_BASE (0x40062000u)
/** Peripheral TSI0 base pointer */
#define TSI0 ((TSI_Type *)TSI0_BASE)
/** Array initializer of TSI peripheral base addresses */
#define TSI_BASE_ADDRS \
    {                  \
        TSI0_BASE      \
    }
/** Array initializer of TSI peripheral base pointers */
#define TSI_BASE_PTRS \
    {                 \
        TSI0          \
    }
/** Interrupt vectors for the TSI peripheral type */
#define TSI_IRQS  \
    {             \
        TSI0_IRQn \
    }

/*!
 * @}
 */ /* end of group TSI_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- TSTMR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TSTMR_Peripheral_Access_Layer TSTMR Peripheral Access Layer
 * @{
 */

/** TSTMR - Register Layout Typedef */
typedef struct
{
    __I uint32_t L; /**< Time Stamp Timer Register Low, offset: 0x0 */
    __I uint32_t H; /**< Time Stamp Timer Register High, offset: 0x4 */
} TSTMR_Type;

/* ----------------------------------------------------------------------------
   -- TSTMR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TSTMR_Register_Masks TSTMR Register Masks
 * @{
 */

/*! @name L - Time Stamp Timer Register Low */
/*! @{ */
#define TSTMR_L_VALUE_MASK (0xFFFFFFFFU)
#define TSTMR_L_VALUE_SHIFT (0U)
/*! VALUE - Time Stamp Timer Low
 */
#define TSTMR_L_VALUE(x) (((uint32_t)(((uint32_t)(x)) << TSTMR_L_VALUE_SHIFT)) & TSTMR_L_VALUE_MASK)
/*! @} */

/*! @name H - Time Stamp Timer Register High */
/*! @{ */
#define TSTMR_H_VALUE_MASK (0xFFFFFFU)
#define TSTMR_H_VALUE_SHIFT (0U)
/*! VALUE - Time Stamp Timer High
 */
#define TSTMR_H_VALUE(x) (((uint32_t)(((uint32_t)(x)) << TSTMR_H_VALUE_SHIFT)) & TSTMR_H_VALUE_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group TSTMR_Register_Masks */

/* TSTMR - Peripheral instance base addresses */
/** Peripheral TSTMR0 base address */
#define TSTMR0_BASE (0x400750F0u)
/** Peripheral TSTMR0 base pointer */
#define TSTMR0 ((TSTMR_Type *)TSTMR0_BASE)
/** Array initializer of TSTMR peripheral base addresses */
#define TSTMR_BASE_ADDRS \
    {                    \
        TSTMR0_BASE      \
    }
/** Array initializer of TSTMR peripheral base pointers */
#define TSTMR_BASE_PTRS \
    {                   \
        TSTMR0          \
    }

/*!
 * @}
 */ /* end of group TSTMR_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- USB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Peripheral_Access_Layer USB Peripheral Access Layer
 * @{
 */

/** USB - Register Layout Typedef */
typedef struct
{
    __I uint8_t PERID; /**< Peripheral ID register, offset: 0x0 */
    uint8_t RESERVED_0[3];
    __I uint8_t IDCOMP; /**< Peripheral ID Complement register, offset: 0x4 */
    uint8_t RESERVED_1[3];
    __I uint8_t REV; /**< Peripheral Revision register, offset: 0x8 */
    uint8_t RESERVED_2[3];
    __I uint8_t ADDINFO; /**< Peripheral Additional Info register, offset: 0xC */
    uint8_t RESERVED_3[3];
    __IO uint8_t OTGISTAT; /**< OTG Interrupt Status register, offset: 0x10 */
    uint8_t RESERVED_4[3];
    __IO uint8_t OTGICR; /**< OTG Interrupt Control register, offset: 0x14 */
    uint8_t RESERVED_5[3];
    __IO uint8_t OTGSTAT; /**< OTG Status register, offset: 0x18 */
    uint8_t RESERVED_6[3];
    __IO uint8_t OTGCTL; /**< OTG Control register, offset: 0x1C */
    uint8_t RESERVED_7[99];
    __IO uint8_t ISTAT; /**< Interrupt Status register, offset: 0x80 */
    uint8_t RESERVED_8[3];
    __IO uint8_t INTEN; /**< Interrupt Enable register, offset: 0x84 */
    uint8_t RESERVED_9[3];
    __IO uint8_t ERRSTAT; /**< Error Interrupt Status register, offset: 0x88 */
    uint8_t RESERVED_10[3];
    __IO uint8_t ERREN; /**< Error Interrupt Enable register, offset: 0x8C */
    uint8_t RESERVED_11[3];
    __I uint8_t STAT; /**< Status register, offset: 0x90 */
    uint8_t RESERVED_12[3];
    __IO uint8_t CTL; /**< Control register, offset: 0x94 */
    uint8_t RESERVED_13[3];
    __IO uint8_t ADDR; /**< Address register, offset: 0x98 */
    uint8_t RESERVED_14[3];
    __IO uint8_t BDTPAGE1; /**< BDT Page register 1, offset: 0x9C */
    uint8_t RESERVED_15[3];
    __IO uint8_t FRMNUML; /**< Frame Number register Low, offset: 0xA0 */
    uint8_t RESERVED_16[3];
    __IO uint8_t FRMNUMH; /**< Frame Number register High, offset: 0xA4 */
    uint8_t RESERVED_17[3];
    __IO uint8_t TOKEN; /**< Token register, offset: 0xA8 */
    uint8_t RESERVED_18[3];
    __IO uint8_t SOFTHLD; /**< SOF Threshold register, offset: 0xAC */
    uint8_t RESERVED_19[3];
    __IO uint8_t BDTPAGE2; /**< BDT Page Register 2, offset: 0xB0 */
    uint8_t RESERVED_20[3];
    __IO uint8_t BDTPAGE3; /**< BDT Page Register 3, offset: 0xB4 */
    uint8_t RESERVED_21[11];
    struct
    {                       /* offset: 0xC0, array step: 0x4 */
        __IO uint8_t ENDPT; /**< Endpoint Control register, array offset: 0xC0, array step: 0x4 */
        uint8_t RESERVED_0[3];
    } ENDPOINT[16];
    __IO uint8_t USBCTRL; /**< USB Control register, offset: 0x100 */
    uint8_t RESERVED_22[3];
    __I uint8_t OBSERVE; /**< USB OTG Observe register, offset: 0x104 */
    uint8_t RESERVED_23[3];
    __IO uint8_t CONTROL; /**< USB OTG Control register, offset: 0x108 */
    uint8_t RESERVED_24[3];
    __IO uint8_t USBTRC0; /**< USB Transceiver Control register 0, offset: 0x10C */
    uint8_t RESERVED_25[7];
    __IO uint8_t USBFRMADJUST; /**< Frame Adjust Register, offset: 0x114 */
    uint8_t RESERVED_26[23];
    __IO uint8_t MISCCTRL; /**< Miscellaneous Control register, offset: 0x12C */
    uint8_t RESERVED_27[19];
    __IO uint8_t CLK_RECOVER_CTRL; /**< USB Clock recovery control, offset: 0x140 */
    uint8_t RESERVED_28[19];
    __IO uint8_t CLK_RECOVER_INT_EN; /**< Clock recovery combined interrupt enable, offset: 0x154 */
    uint8_t RESERVED_29[7];
    __IO uint8_t CLK_RECOVER_INT_STATUS; /**< Clock recovery separated interrupt status, offset: 0x15C */
} USB_Type;

/* ----------------------------------------------------------------------------
   -- USB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Register_Masks USB Register Masks
 * @{
 */

/*! @name PERID - Peripheral ID register */
/*! @{ */
#define USB_PERID_ID_MASK (0x3FU)
#define USB_PERID_ID_SHIFT (0U)
/*! ID - Peripheral Identification
 */
#define USB_PERID_ID(x) (((uint8_t)(((uint8_t)(x)) << USB_PERID_ID_SHIFT)) & USB_PERID_ID_MASK)
/*! @} */

/*! @name IDCOMP - Peripheral ID Complement register */
/*! @{ */
#define USB_IDCOMP_NID_MASK (0x3FU)
#define USB_IDCOMP_NID_SHIFT (0U)
#define USB_IDCOMP_NID(x) (((uint8_t)(((uint8_t)(x)) << USB_IDCOMP_NID_SHIFT)) & USB_IDCOMP_NID_MASK)
/*! @} */

/*! @name REV - Peripheral Revision register */
/*! @{ */
#define USB_REV_REV_MASK (0xFFU)
#define USB_REV_REV_SHIFT (0U)
/*! REV - Revision
 */
#define USB_REV_REV(x) (((uint8_t)(((uint8_t)(x)) << USB_REV_REV_SHIFT)) & USB_REV_REV_MASK)
/*! @} */

/*! @name ADDINFO - Peripheral Additional Info register */
/*! @{ */
#define USB_ADDINFO_IEHOST_MASK (0x1U)
#define USB_ADDINFO_IEHOST_SHIFT (0U)
#define USB_ADDINFO_IEHOST(x) (((uint8_t)(((uint8_t)(x)) << USB_ADDINFO_IEHOST_SHIFT)) & USB_ADDINFO_IEHOST_MASK)
/*! @} */

/*! @name OTGISTAT - OTG Interrupt Status register */
/*! @{ */
#define USB_OTGISTAT_LINE_STATE_CHG_MASK (0x20U)
#define USB_OTGISTAT_LINE_STATE_CHG_SHIFT (5U)
#define USB_OTGISTAT_LINE_STATE_CHG(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_OTGISTAT_LINE_STATE_CHG_SHIFT)) & USB_OTGISTAT_LINE_STATE_CHG_MASK)
#define USB_OTGISTAT_ONEMSEC_MASK (0x40U)
#define USB_OTGISTAT_ONEMSEC_SHIFT (6U)
#define USB_OTGISTAT_ONEMSEC(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGISTAT_ONEMSEC_SHIFT)) & USB_OTGISTAT_ONEMSEC_MASK)
/*! @} */

/*! @name OTGICR - OTG Interrupt Control register */
/*! @{ */
#define USB_OTGICR_LINESTATEEN_MASK (0x20U)
#define USB_OTGICR_LINESTATEEN_SHIFT (5U)
/*! LINESTATEEN - Line State Change Interrupt Enable
 *  0b0..Disables the LINE_STAT_CHG interrupt.
 *  0b1..Enables the LINE_STAT_CHG interrupt.
 */
#define USB_OTGICR_LINESTATEEN(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_OTGICR_LINESTATEEN_SHIFT)) & USB_OTGICR_LINESTATEEN_MASK)
#define USB_OTGICR_ONEMSECEN_MASK (0x40U)
#define USB_OTGICR_ONEMSECEN_SHIFT (6U)
/*! ONEMSECEN - One Millisecond Interrupt Enable
 *  0b0..Diables the 1ms timer interrupt.
 *  0b1..Enables the 1ms timer interrupt.
 */
#define USB_OTGICR_ONEMSECEN(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGICR_ONEMSECEN_SHIFT)) & USB_OTGICR_ONEMSECEN_MASK)
/*! @} */

/*! @name OTGSTAT - OTG Status register */
/*! @{ */
#define USB_OTGSTAT_LINESTATESTABLE_MASK (0x20U)
#define USB_OTGSTAT_LINESTATESTABLE_SHIFT (5U)
/*! LINESTATESTABLE
 *  0b0..The LINE_STAT_CHG bit is not yet stable.
 *  0b1..The LINE_STAT_CHG bit has been debounced and is stable.
 */
#define USB_OTGSTAT_LINESTATESTABLE(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_OTGSTAT_LINESTATESTABLE_SHIFT)) & USB_OTGSTAT_LINESTATESTABLE_MASK)
#define USB_OTGSTAT_ONEMSECEN_MASK (0x40U)
#define USB_OTGSTAT_ONEMSECEN_SHIFT (6U)
#define USB_OTGSTAT_ONEMSECEN(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_OTGSTAT_ONEMSECEN_SHIFT)) & USB_OTGSTAT_ONEMSECEN_MASK)
/*! @} */

/*! @name OTGCTL - OTG Control register */
/*! @{ */
#define USB_OTGCTL_OTGEN_MASK (0x4U)
#define USB_OTGCTL_OTGEN_SHIFT (2U)
/*! OTGEN - On-The-Go pullup/pulldown resistor enable
 *  0b0..If USB_EN is 1 and HOST_MODE is 0 in the Control Register (CTL), then the D+ Data Line pull-up resistors
 *       are enabled. If HOST_MODE is 1 the D+ and D- Data Line pull-down resistors are engaged.
 *  0b1..The pull-up and pull-down controls in this register are used.
 */
#define USB_OTGCTL_OTGEN(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGCTL_OTGEN_SHIFT)) & USB_OTGCTL_OTGEN_MASK)
#define USB_OTGCTL_DMLOW_MASK (0x10U)
#define USB_OTGCTL_DMLOW_SHIFT (4U)
/*! DMLOW - D- Data Line pull-down resistor enable
 *  0b0..D- pulldown resistor is not enabled.
 *  0b1..D- pulldown resistor is enabled.
 */
#define USB_OTGCTL_DMLOW(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGCTL_DMLOW_SHIFT)) & USB_OTGCTL_DMLOW_MASK)
#define USB_OTGCTL_DPLOW_MASK (0x20U)
#define USB_OTGCTL_DPLOW_SHIFT (5U)
/*! DPLOW - D+ Data Line pull-down resistor enable
 *  0b0..D+ pulldown resistor is not enabled.
 *  0b1..D+ pulldown resistor is enabled.
 */
#define USB_OTGCTL_DPLOW(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGCTL_DPLOW_SHIFT)) & USB_OTGCTL_DPLOW_MASK)
#define USB_OTGCTL_DPHIGH_MASK (0x80U)
#define USB_OTGCTL_DPHIGH_SHIFT (7U)
/*! DPHIGH - D+ Data Line pullup resistor enable
 *  0b0..D+ pullup resistor is not enabled
 *  0b1..D+ pullup resistor is enabled
 */
#define USB_OTGCTL_DPHIGH(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGCTL_DPHIGH_SHIFT)) & USB_OTGCTL_DPHIGH_MASK)
/*! @} */

/*! @name ISTAT - Interrupt Status register */
/*! @{ */
#define USB_ISTAT_USBRST_MASK (0x1U)
#define USB_ISTAT_USBRST_SHIFT (0U)
#define USB_ISTAT_USBRST(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_USBRST_SHIFT)) & USB_ISTAT_USBRST_MASK)
#define USB_ISTAT_ERROR_MASK (0x2U)
#define USB_ISTAT_ERROR_SHIFT (1U)
#define USB_ISTAT_ERROR(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_ERROR_SHIFT)) & USB_ISTAT_ERROR_MASK)
#define USB_ISTAT_SOFTOK_MASK (0x4U)
#define USB_ISTAT_SOFTOK_SHIFT (2U)
#define USB_ISTAT_SOFTOK(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_SOFTOK_SHIFT)) & USB_ISTAT_SOFTOK_MASK)
#define USB_ISTAT_TOKDNE_MASK (0x8U)
#define USB_ISTAT_TOKDNE_SHIFT (3U)
#define USB_ISTAT_TOKDNE(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_TOKDNE_SHIFT)) & USB_ISTAT_TOKDNE_MASK)
#define USB_ISTAT_SLEEP_MASK (0x10U)
#define USB_ISTAT_SLEEP_SHIFT (4U)
#define USB_ISTAT_SLEEP(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_SLEEP_SHIFT)) & USB_ISTAT_SLEEP_MASK)
#define USB_ISTAT_RESUME_MASK (0x20U)
#define USB_ISTAT_RESUME_SHIFT (5U)
#define USB_ISTAT_RESUME(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_RESUME_SHIFT)) & USB_ISTAT_RESUME_MASK)
#define USB_ISTAT_ATTACH_MASK (0x40U)
#define USB_ISTAT_ATTACH_SHIFT (6U)
/*! ATTACH - Attach Interrupt
 *  0b0..No Attach is detected since the last time the ATTACH bit was cleared.
 *  0b1..A peripheral is now present and must be configured (a stable non-SE0 state is detected for more than 2.5 us).
 */
#define USB_ISTAT_ATTACH(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_ATTACH_SHIFT)) & USB_ISTAT_ATTACH_MASK)
#define USB_ISTAT_STALL_MASK (0x80U)
#define USB_ISTAT_STALL_SHIFT (7U)
/*! STALL - Stall Interrupt
 */
#define USB_ISTAT_STALL(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_STALL_SHIFT)) & USB_ISTAT_STALL_MASK)
/*! @} */

/*! @name INTEN - Interrupt Enable register */
/*! @{ */
#define USB_INTEN_USBRSTEN_MASK (0x1U)
#define USB_INTEN_USBRSTEN_SHIFT (0U)
/*! USBRSTEN - USBRST Interrupt Enable
 *  0b0..Disables the USBRST interrupt.
 *  0b1..Enables the USBRST interrupt.
 */
#define USB_INTEN_USBRSTEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_USBRSTEN_SHIFT)) & USB_INTEN_USBRSTEN_MASK)
#define USB_INTEN_ERROREN_MASK (0x2U)
#define USB_INTEN_ERROREN_SHIFT (1U)
/*! ERROREN - ERROR Interrupt Enable
 *  0b0..Disables the ERROR interrupt.
 *  0b1..Enables the ERROR interrupt.
 */
#define USB_INTEN_ERROREN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_ERROREN_SHIFT)) & USB_INTEN_ERROREN_MASK)
#define USB_INTEN_SOFTOKEN_MASK (0x4U)
#define USB_INTEN_SOFTOKEN_SHIFT (2U)
/*! SOFTOKEN - SOFTOK Interrupt Enable
 *  0b0..Disbles the SOFTOK interrupt.
 *  0b1..Enables the SOFTOK interrupt.
 */
#define USB_INTEN_SOFTOKEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_SOFTOKEN_SHIFT)) & USB_INTEN_SOFTOKEN_MASK)
#define USB_INTEN_TOKDNEEN_MASK (0x8U)
#define USB_INTEN_TOKDNEEN_SHIFT (3U)
/*! TOKDNEEN - TOKDNE Interrupt Enable
 *  0b0..Disables the TOKDNE interrupt.
 *  0b1..Enables the TOKDNE interrupt.
 */
#define USB_INTEN_TOKDNEEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_TOKDNEEN_SHIFT)) & USB_INTEN_TOKDNEEN_MASK)
#define USB_INTEN_SLEEPEN_MASK (0x10U)
#define USB_INTEN_SLEEPEN_SHIFT (4U)
/*! SLEEPEN - SLEEP Interrupt Enable
 *  0b0..Disables the SLEEP interrupt.
 *  0b1..Enables the SLEEP interrupt.
 */
#define USB_INTEN_SLEEPEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_SLEEPEN_SHIFT)) & USB_INTEN_SLEEPEN_MASK)
#define USB_INTEN_RESUMEEN_MASK (0x20U)
#define USB_INTEN_RESUMEEN_SHIFT (5U)
/*! RESUMEEN - RESUME Interrupt Enable
 *  0b0..Disables the RESUME interrupt.
 *  0b1..Enables the RESUME interrupt.
 */
#define USB_INTEN_RESUMEEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_RESUMEEN_SHIFT)) & USB_INTEN_RESUMEEN_MASK)
#define USB_INTEN_ATTACHEN_MASK (0x40U)
#define USB_INTEN_ATTACHEN_SHIFT (6U)
/*! ATTACHEN - ATTACH Interrupt Enable
 *  0b0..Disables the ATTACH interrupt.
 *  0b1..Enables the ATTACH interrupt.
 */
#define USB_INTEN_ATTACHEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_ATTACHEN_SHIFT)) & USB_INTEN_ATTACHEN_MASK)
#define USB_INTEN_STALLEN_MASK (0x80U)
#define USB_INTEN_STALLEN_SHIFT (7U)
/*! STALLEN - STALL Interrupt Enable
 *  0b0..Diasbles the STALL interrupt.
 *  0b1..Enables the STALL interrupt.
 */
#define USB_INTEN_STALLEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_STALLEN_SHIFT)) & USB_INTEN_STALLEN_MASK)
/*! @} */

/*! @name ERRSTAT - Error Interrupt Status register */
/*! @{ */
#define USB_ERRSTAT_PIDERR_MASK (0x1U)
#define USB_ERRSTAT_PIDERR_SHIFT (0U)
#define USB_ERRSTAT_PIDERR(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_PIDERR_SHIFT)) & USB_ERRSTAT_PIDERR_MASK)
#define USB_ERRSTAT_CRC5EOF_MASK (0x2U)
#define USB_ERRSTAT_CRC5EOF_SHIFT (1U)
#define USB_ERRSTAT_CRC5EOF(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_CRC5EOF_SHIFT)) & USB_ERRSTAT_CRC5EOF_MASK)
#define USB_ERRSTAT_CRC16_MASK (0x4U)
#define USB_ERRSTAT_CRC16_SHIFT (2U)
#define USB_ERRSTAT_CRC16(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_CRC16_SHIFT)) & USB_ERRSTAT_CRC16_MASK)
#define USB_ERRSTAT_DFN8_MASK (0x8U)
#define USB_ERRSTAT_DFN8_SHIFT (3U)
#define USB_ERRSTAT_DFN8(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_DFN8_SHIFT)) & USB_ERRSTAT_DFN8_MASK)
#define USB_ERRSTAT_BTOERR_MASK (0x10U)
#define USB_ERRSTAT_BTOERR_SHIFT (4U)
#define USB_ERRSTAT_BTOERR(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_BTOERR_SHIFT)) & USB_ERRSTAT_BTOERR_MASK)
#define USB_ERRSTAT_DMAERR_MASK (0x20U)
#define USB_ERRSTAT_DMAERR_SHIFT (5U)
#define USB_ERRSTAT_DMAERR(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_DMAERR_SHIFT)) & USB_ERRSTAT_DMAERR_MASK)
#define USB_ERRSTAT_OWNERR_MASK (0x40U)
#define USB_ERRSTAT_OWNERR_SHIFT (6U)
#define USB_ERRSTAT_OWNERR(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_OWNERR_SHIFT)) & USB_ERRSTAT_OWNERR_MASK)
#define USB_ERRSTAT_BTSERR_MASK (0x80U)
#define USB_ERRSTAT_BTSERR_SHIFT (7U)
#define USB_ERRSTAT_BTSERR(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_BTSERR_SHIFT)) & USB_ERRSTAT_BTSERR_MASK)
/*! @} */

/*! @name ERREN - Error Interrupt Enable register */
/*! @{ */
#define USB_ERREN_PIDERREN_MASK (0x1U)
#define USB_ERREN_PIDERREN_SHIFT (0U)
/*! PIDERREN - PIDERR Interrupt Enable
 *  0b0..Disables the PIDERR interrupt.
 *  0b1..Enters the PIDERR interrupt.
 */
#define USB_ERREN_PIDERREN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_PIDERREN_SHIFT)) & USB_ERREN_PIDERREN_MASK)
#define USB_ERREN_CRC5EOFEN_MASK (0x2U)
#define USB_ERREN_CRC5EOFEN_SHIFT (1U)
/*! CRC5EOFEN - CRC5/EOF Interrupt Enable
 *  0b0..Disables the CRC5/EOF interrupt.
 *  0b1..Enables the CRC5/EOF interrupt.
 */
#define USB_ERREN_CRC5EOFEN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_CRC5EOFEN_SHIFT)) & USB_ERREN_CRC5EOFEN_MASK)
#define USB_ERREN_CRC16EN_MASK (0x4U)
#define USB_ERREN_CRC16EN_SHIFT (2U)
/*! CRC16EN - CRC16 Interrupt Enable
 *  0b0..Disables the CRC16 interrupt.
 *  0b1..Enables the CRC16 interrupt.
 */
#define USB_ERREN_CRC16EN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_CRC16EN_SHIFT)) & USB_ERREN_CRC16EN_MASK)
#define USB_ERREN_DFN8EN_MASK (0x8U)
#define USB_ERREN_DFN8EN_SHIFT (3U)
/*! DFN8EN - DFN8 Interrupt Enable
 *  0b0..Disables the DFN8 interrupt.
 *  0b1..Enables the DFN8 interrupt.
 */
#define USB_ERREN_DFN8EN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_DFN8EN_SHIFT)) & USB_ERREN_DFN8EN_MASK)
#define USB_ERREN_BTOERREN_MASK (0x10U)
#define USB_ERREN_BTOERREN_SHIFT (4U)
/*! BTOERREN - BTOERR Interrupt Enable
 *  0b0..Disables the BTOERR interrupt.
 *  0b1..Enables the BTOERR interrupt.
 */
#define USB_ERREN_BTOERREN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_BTOERREN_SHIFT)) & USB_ERREN_BTOERREN_MASK)
#define USB_ERREN_DMAERREN_MASK (0x20U)
#define USB_ERREN_DMAERREN_SHIFT (5U)
/*! DMAERREN - DMAERR Interrupt Enable
 *  0b0..Disables the DMAERR interrupt.
 *  0b1..Enables the DMAERR interrupt.
 */
#define USB_ERREN_DMAERREN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_DMAERREN_SHIFT)) & USB_ERREN_DMAERREN_MASK)
#define USB_ERREN_OWNERREN_MASK (0x40U)
#define USB_ERREN_OWNERREN_SHIFT (6U)
/*! OWNERREN - OWNERR Interrupt Enable
 *  0b0..Disables the OWNERR interrupt.
 *  0b1..Enables the OWNERR interrupt.
 */
#define USB_ERREN_OWNERREN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_OWNERREN_SHIFT)) & USB_ERREN_OWNERREN_MASK)
#define USB_ERREN_BTSERREN_MASK (0x80U)
#define USB_ERREN_BTSERREN_SHIFT (7U)
/*! BTSERREN - BTSERR Interrupt Enable
 *  0b0..Disables the BTSERR interrupt.
 *  0b1..Enables the BTSERR interrupt.
 */
#define USB_ERREN_BTSERREN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_BTSERREN_SHIFT)) & USB_ERREN_BTSERREN_MASK)
/*! @} */

/*! @name STAT - Status register */
/*! @{ */
#define USB_STAT_ODD_MASK (0x4U)
#define USB_STAT_ODD_SHIFT (2U)
#define USB_STAT_ODD(x) (((uint8_t)(((uint8_t)(x)) << USB_STAT_ODD_SHIFT)) & USB_STAT_ODD_MASK)
#define USB_STAT_TX_MASK (0x8U)
#define USB_STAT_TX_SHIFT (3U)
/*! TX - Transmit Indicator
 *  0b0..The most recent transaction was a receive operation.
 *  0b1..The most recent transaction was a transmit operation.
 */
#define USB_STAT_TX(x) (((uint8_t)(((uint8_t)(x)) << USB_STAT_TX_SHIFT)) & USB_STAT_TX_MASK)
#define USB_STAT_ENDP_MASK (0xF0U)
#define USB_STAT_ENDP_SHIFT (4U)
#define USB_STAT_ENDP(x) (((uint8_t)(((uint8_t)(x)) << USB_STAT_ENDP_SHIFT)) & USB_STAT_ENDP_MASK)
/*! @} */

/*! @name CTL - Control register */
/*! @{ */
#define USB_CTL_USBENSOFEN_MASK (0x1U)
#define USB_CTL_USBENSOFEN_SHIFT (0U)
/*! USBENSOFEN - USB Enable
 *  0b0..Disables the USB Module.
 *  0b1..Enables the USB Module.
 */
#define USB_CTL_USBENSOFEN(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_USBENSOFEN_SHIFT)) & USB_CTL_USBENSOFEN_MASK)
#define USB_CTL_ODDRST_MASK (0x2U)
#define USB_CTL_ODDRST_SHIFT (1U)
#define USB_CTL_ODDRST(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_ODDRST_SHIFT)) & USB_CTL_ODDRST_MASK)
#define USB_CTL_RESUME_MASK (0x4U)
#define USB_CTL_RESUME_SHIFT (2U)
#define USB_CTL_RESUME(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_RESUME_SHIFT)) & USB_CTL_RESUME_MASK)
#define USB_CTL_HOSTMODEEN_MASK (0x8U)
#define USB_CTL_HOSTMODEEN_SHIFT (3U)
#define USB_CTL_HOSTMODEEN(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_HOSTMODEEN_SHIFT)) & USB_CTL_HOSTMODEEN_MASK)
#define USB_CTL_RESET_MASK (0x10U)
#define USB_CTL_RESET_SHIFT (4U)
#define USB_CTL_RESET(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_RESET_SHIFT)) & USB_CTL_RESET_MASK)
#define USB_CTL_TXSUSPENDTOKENBUSY_MASK (0x20U)
#define USB_CTL_TXSUSPENDTOKENBUSY_SHIFT (5U)
#define USB_CTL_TXSUSPENDTOKENBUSY(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_CTL_TXSUSPENDTOKENBUSY_SHIFT)) & USB_CTL_TXSUSPENDTOKENBUSY_MASK)
#define USB_CTL_SE0_MASK (0x40U)
#define USB_CTL_SE0_SHIFT (6U)
/*! SE0 - Live USB Single Ended Zero signal
 */
#define USB_CTL_SE0(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_SE0_SHIFT)) & USB_CTL_SE0_MASK)
#define USB_CTL_JSTATE_MASK (0x80U)
#define USB_CTL_JSTATE_SHIFT (7U)
/*! JSTATE - Live USB differential receiver JSTATE signal
 */
#define USB_CTL_JSTATE(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_JSTATE_SHIFT)) & USB_CTL_JSTATE_MASK)
/*! @} */

/*! @name ADDR - Address register */
/*! @{ */
#define USB_ADDR_ADDR_MASK (0x7FU)
#define USB_ADDR_ADDR_SHIFT (0U)
/*! ADDR - USB Address
 */
#define USB_ADDR_ADDR(x) (((uint8_t)(((uint8_t)(x)) << USB_ADDR_ADDR_SHIFT)) & USB_ADDR_ADDR_MASK)
#define USB_ADDR_LSEN_MASK (0x80U)
#define USB_ADDR_LSEN_SHIFT (7U)
/*! LSEN - Low Speed Enable bit
 */
#define USB_ADDR_LSEN(x) (((uint8_t)(((uint8_t)(x)) << USB_ADDR_LSEN_SHIFT)) & USB_ADDR_LSEN_MASK)
/*! @} */

/*! @name BDTPAGE1 - BDT Page register 1 */
/*! @{ */
#define USB_BDTPAGE1_BDTBA_MASK (0xFEU)
#define USB_BDTPAGE1_BDTBA_SHIFT (1U)
#define USB_BDTPAGE1_BDTBA(x) (((uint8_t)(((uint8_t)(x)) << USB_BDTPAGE1_BDTBA_SHIFT)) & USB_BDTPAGE1_BDTBA_MASK)
/*! @} */

/*! @name FRMNUML - Frame Number register Low */
/*! @{ */
#define USB_FRMNUML_FRM_MASK (0xFFU)
#define USB_FRMNUML_FRM_SHIFT (0U)
#define USB_FRMNUML_FRM(x) (((uint8_t)(((uint8_t)(x)) << USB_FRMNUML_FRM_SHIFT)) & USB_FRMNUML_FRM_MASK)
/*! @} */

/*! @name FRMNUMH - Frame Number register High */
/*! @{ */
#define USB_FRMNUMH_FRM_MASK (0x7U)
#define USB_FRMNUMH_FRM_SHIFT (0U)
#define USB_FRMNUMH_FRM(x) (((uint8_t)(((uint8_t)(x)) << USB_FRMNUMH_FRM_SHIFT)) & USB_FRMNUMH_FRM_MASK)
/*! @} */

/*! @name TOKEN - Token register */
/*! @{ */
#define USB_TOKEN_TOKENENDPT_MASK (0xFU)
#define USB_TOKEN_TOKENENDPT_SHIFT (0U)
#define USB_TOKEN_TOKENENDPT(x) (((uint8_t)(((uint8_t)(x)) << USB_TOKEN_TOKENENDPT_SHIFT)) & USB_TOKEN_TOKENENDPT_MASK)
#define USB_TOKEN_TOKENPID_MASK (0xF0U)
#define USB_TOKEN_TOKENPID_SHIFT (4U)
/*! TOKENPID
 *  0b0001..OUT Token. USB Module performs an OUT (TX) transaction.
 *  0b1001..IN Token. USB Module performs an In (RX) transaction.
 *  0b1101..SETUP Token. USB Module performs a SETUP (TX) transaction
 */
#define USB_TOKEN_TOKENPID(x) (((uint8_t)(((uint8_t)(x)) << USB_TOKEN_TOKENPID_SHIFT)) & USB_TOKEN_TOKENPID_MASK)
/*! @} */

/*! @name SOFTHLD - SOF Threshold register */
/*! @{ */
#define USB_SOFTHLD_CNT_MASK (0xFFU)
#define USB_SOFTHLD_CNT_SHIFT (0U)
#define USB_SOFTHLD_CNT(x) (((uint8_t)(((uint8_t)(x)) << USB_SOFTHLD_CNT_SHIFT)) & USB_SOFTHLD_CNT_MASK)
/*! @} */

/*! @name BDTPAGE2 - BDT Page Register 2 */
/*! @{ */
#define USB_BDTPAGE2_BDTBA_MASK (0xFFU)
#define USB_BDTPAGE2_BDTBA_SHIFT (0U)
#define USB_BDTPAGE2_BDTBA(x) (((uint8_t)(((uint8_t)(x)) << USB_BDTPAGE2_BDTBA_SHIFT)) & USB_BDTPAGE2_BDTBA_MASK)
/*! @} */

/*! @name BDTPAGE3 - BDT Page Register 3 */
/*! @{ */
#define USB_BDTPAGE3_BDTBA_MASK (0xFFU)
#define USB_BDTPAGE3_BDTBA_SHIFT (0U)
#define USB_BDTPAGE3_BDTBA(x) (((uint8_t)(((uint8_t)(x)) << USB_BDTPAGE3_BDTBA_SHIFT)) & USB_BDTPAGE3_BDTBA_MASK)
/*! @} */

/*! @name ENDPT - Endpoint Control register */
/*! @{ */
#define USB_ENDPT_EPHSHK_MASK (0x1U)
#define USB_ENDPT_EPHSHK_SHIFT (0U)
#define USB_ENDPT_EPHSHK(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPHSHK_SHIFT)) & USB_ENDPT_EPHSHK_MASK)
#define USB_ENDPT_EPSTALL_MASK (0x2U)
#define USB_ENDPT_EPSTALL_SHIFT (1U)
#define USB_ENDPT_EPSTALL(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPSTALL_SHIFT)) & USB_ENDPT_EPSTALL_MASK)
#define USB_ENDPT_EPTXEN_MASK (0x4U)
#define USB_ENDPT_EPTXEN_SHIFT (2U)
#define USB_ENDPT_EPTXEN(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPTXEN_SHIFT)) & USB_ENDPT_EPTXEN_MASK)
#define USB_ENDPT_EPRXEN_MASK (0x8U)
#define USB_ENDPT_EPRXEN_SHIFT (3U)
#define USB_ENDPT_EPRXEN(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPRXEN_SHIFT)) & USB_ENDPT_EPRXEN_MASK)
#define USB_ENDPT_EPCTLDIS_MASK (0x10U)
#define USB_ENDPT_EPCTLDIS_SHIFT (4U)
#define USB_ENDPT_EPCTLDIS(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPCTLDIS_SHIFT)) & USB_ENDPT_EPCTLDIS_MASK)
#define USB_ENDPT_RETRYDIS_MASK (0x40U)
#define USB_ENDPT_RETRYDIS_SHIFT (6U)
#define USB_ENDPT_RETRYDIS(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_RETRYDIS_SHIFT)) & USB_ENDPT_RETRYDIS_MASK)
#define USB_ENDPT_HOSTWOHUB_MASK (0x80U)
#define USB_ENDPT_HOSTWOHUB_SHIFT (7U)
/*! HOSTWOHUB
 *  0b0..Low-speed device connected to Host through a hub. PRE_PID will be generated as required.
 *  0b1..Low-speed device directly connected. No hub, or no low-speed device attached.
 */
#define USB_ENDPT_HOSTWOHUB(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_HOSTWOHUB_SHIFT)) & USB_ENDPT_HOSTWOHUB_MASK)
/*! @} */

/* The count of USB_ENDPT */
#define USB_ENDPT_COUNT (16U)

/*! @name USBCTRL - USB Control register */
/*! @{ */
#define USB_USBCTRL_UARTSEL_MASK (0x10U)
#define USB_USBCTRL_UARTSEL_SHIFT (4U)
/*! UARTSEL
 *  0b0..USB signals not used as UART signals.
 *  0b1..USB signals used as UART signals.
 */
#define USB_USBCTRL_UARTSEL(x) (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_UARTSEL_SHIFT)) & USB_USBCTRL_UARTSEL_MASK)
#define USB_USBCTRL_UARTCHLS_MASK (0x20U)
#define USB_USBCTRL_UARTCHLS_SHIFT (5U)
/*! UARTCHLS - UART Signal Channel Select
 *  0b0..USB DP/DM signals used as UART TX/RX.
 *  0b1..USB DP/DM signals used as UART RX/TX.
 */
#define USB_USBCTRL_UARTCHLS(x) (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_UARTCHLS_SHIFT)) & USB_USBCTRL_UARTCHLS_MASK)
#define USB_USBCTRL_PDE_MASK (0x40U)
#define USB_USBCTRL_PDE_SHIFT (6U)
/*! PDE
 *  0b0..Weak pulldowns are disabled on D+ and D-.
 *  0b1..Weak pulldowns are enabled on D+ and D-.
 */
#define USB_USBCTRL_PDE(x) (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_PDE_SHIFT)) & USB_USBCTRL_PDE_MASK)
#define USB_USBCTRL_SUSP_MASK (0x80U)
#define USB_USBCTRL_SUSP_SHIFT (7U)
/*! SUSP
 *  0b0..USB transceiver is not in suspend state.
 *  0b1..USB transceiver is in suspend state.
 */
#define USB_USBCTRL_SUSP(x) (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_SUSP_SHIFT)) & USB_USBCTRL_SUSP_MASK)
/*! @} */

/*! @name OBSERVE - USB OTG Observe register */
/*! @{ */
#define USB_OBSERVE_DMPD_MASK (0x10U)
#define USB_OBSERVE_DMPD_SHIFT (4U)
/*! DMPD
 *  0b0..D- pulldown disabled.
 *  0b1..D- pulldown enabled.
 */
#define USB_OBSERVE_DMPD(x) (((uint8_t)(((uint8_t)(x)) << USB_OBSERVE_DMPD_SHIFT)) & USB_OBSERVE_DMPD_MASK)
#define USB_OBSERVE_DPPD_MASK (0x40U)
#define USB_OBSERVE_DPPD_SHIFT (6U)
/*! DPPD
 *  0b0..D+ pulldown disabled.
 *  0b1..D+ pulldown enabled.
 */
#define USB_OBSERVE_DPPD(x) (((uint8_t)(((uint8_t)(x)) << USB_OBSERVE_DPPD_SHIFT)) & USB_OBSERVE_DPPD_MASK)
#define USB_OBSERVE_DPPU_MASK (0x80U)
#define USB_OBSERVE_DPPU_SHIFT (7U)
/*! DPPU
 *  0b0..D+ pullup disabled.
 *  0b1..D+ pullup enabled.
 */
#define USB_OBSERVE_DPPU(x) (((uint8_t)(((uint8_t)(x)) << USB_OBSERVE_DPPU_SHIFT)) & USB_OBSERVE_DPPU_MASK)
/*! @} */

/*! @name CONTROL - USB OTG Control register */
/*! @{ */
#define USB_CONTROL_DPPULLUPNONOTG_MASK (0x10U)
#define USB_CONTROL_DPPULLUPNONOTG_SHIFT (4U)
/*! DPPULLUPNONOTG
 *  0b0..DP Pullup in non-OTG device mode is not enabled.
 *  0b1..DP Pullup in non-OTG device mode is enabled.
 */
#define USB_CONTROL_DPPULLUPNONOTG(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_CONTROL_DPPULLUPNONOTG_SHIFT)) & USB_CONTROL_DPPULLUPNONOTG_MASK)
/*! @} */

/*! @name USBTRC0 - USB Transceiver Control register 0 */
/*! @{ */
#define USB_USBTRC0_USB_RESUME_INT_MASK (0x1U)
#define USB_USBTRC0_USB_RESUME_INT_SHIFT (0U)
/*! USB_RESUME_INT - USB Asynchronous Interrupt
 *  0b0..No interrupt was generated.
 *  0b1..Interrupt was generated because of the USB asynchronous interrupt.
 */
#define USB_USBTRC0_USB_RESUME_INT(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USB_RESUME_INT_SHIFT)) & USB_USBTRC0_USB_RESUME_INT_MASK)
#define USB_USBTRC0_SYNC_DET_MASK (0x2U)
#define USB_USBTRC0_SYNC_DET_SHIFT (1U)
/*! SYNC_DET - Synchronous USB Interrupt Detect
 *  0b0..Synchronous interrupt has not been detected.
 *  0b1..Synchronous interrupt has been detected.
 */
#define USB_USBTRC0_SYNC_DET(x) (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_SYNC_DET_SHIFT)) & USB_USBTRC0_SYNC_DET_MASK)
#define USB_USBTRC0_USB_CLK_RECOVERY_INT_MASK (0x4U)
#define USB_USBTRC0_USB_CLK_RECOVERY_INT_SHIFT (2U)
/*! USB_CLK_RECOVERY_INT - Combined USB Clock Recovery interrupt status
 */
#define USB_USBTRC0_USB_CLK_RECOVERY_INT(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USB_CLK_RECOVERY_INT_SHIFT)) & USB_USBTRC0_USB_CLK_RECOVERY_INT_MASK)
#define USB_USBTRC0_VREDG_DET_MASK (0x8U)
#define USB_USBTRC0_VREDG_DET_SHIFT (3U)
/*! VREDG_DET - VREGIN Rising Edge Interrupt Detect
 *  0b0..VREGIN rising edge interrupt has not been detected.
 *  0b1..VREGIN rising edge interrupt has been detected.
 */
#define USB_USBTRC0_VREDG_DET(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_VREDG_DET_SHIFT)) & USB_USBTRC0_VREDG_DET_MASK)
#define USB_USBTRC0_VFEDG_DET_MASK (0x10U)
#define USB_USBTRC0_VFEDG_DET_SHIFT (4U)
/*! VFEDG_DET - VREGIN Falling Edge Interrupt Detect
 *  0b0..VREGIN falling edge interrupt has not been detected.
 *  0b1..VREGIN falling edge interrupt has been detected.
 */
#define USB_USBTRC0_VFEDG_DET(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_VFEDG_DET_SHIFT)) & USB_USBTRC0_VFEDG_DET_MASK)
#define USB_USBTRC0_USBRESMEN_MASK (0x20U)
#define USB_USBTRC0_USBRESMEN_SHIFT (5U)
/*! USBRESMEN - Asynchronous Resume Interrupt Enable
 *  0b0..USB asynchronous wakeup from suspend mode disabled.
 *  0b1..USB asynchronous wakeup from suspend mode enabled. The asynchronous resume interrupt differs from the
 *       synchronous resume interrupt in that it asynchronously detects K-state using the unfiltered state of the D+
 *       and D- pins. This interrupt should only be enabled when the Transceiver is suspended.
 */
#define USB_USBTRC0_USBRESMEN(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USBRESMEN_SHIFT)) & USB_USBTRC0_USBRESMEN_MASK)
#define USB_USBTRC0_USBRESET_MASK (0x80U)
#define USB_USBTRC0_USBRESET_SHIFT (7U)
/*! USBRESET - USB Reset
 *  0b0..Normal USB module operation.
 *  0b1..Returns the USB module to its reset state.
 */
#define USB_USBTRC0_USBRESET(x) (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USBRESET_SHIFT)) & USB_USBTRC0_USBRESET_MASK)
/*! @} */

/*! @name USBFRMADJUST - Frame Adjust Register */
/*! @{ */
#define USB_USBFRMADJUST_ADJ_MASK (0xFFU)
#define USB_USBFRMADJUST_ADJ_SHIFT (0U)
/*! ADJ - Frame Adjustment
 */
#define USB_USBFRMADJUST_ADJ(x) (((uint8_t)(((uint8_t)(x)) << USB_USBFRMADJUST_ADJ_SHIFT)) & USB_USBFRMADJUST_ADJ_MASK)
/*! @} */

/*! @name MISCCTRL - Miscellaneous Control register */
/*! @{ */
#define USB_MISCCTRL_SOFDYNTHLD_MASK (0x1U)
#define USB_MISCCTRL_SOFDYNTHLD_SHIFT (0U)
/*! SOFDYNTHLD - Dynamic SOF Threshold Compare mode
 *  0b0..SOF_TOK interrupt is set when byte times SOF threshold is reached.
 *  0b1..SOF_TOK interrupt is set when 8 byte times SOF threshold is reached or overstepped.
 */
#define USB_MISCCTRL_SOFDYNTHLD(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_SOFDYNTHLD_SHIFT)) & USB_MISCCTRL_SOFDYNTHLD_MASK)
#define USB_MISCCTRL_SOFBUSSET_MASK (0x2U)
#define USB_MISCCTRL_SOFBUSSET_SHIFT (1U)
/*! SOFBUSSET - SOF_TOK Interrupt Generation Mode Select
 *  0b0..SOF_TOK interrupt is set according to SOF threshold value.
 *  0b1..SOF_TOK interrupt is set when SOF counter reaches 0.
 */
#define USB_MISCCTRL_SOFBUSSET(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_SOFBUSSET_SHIFT)) & USB_MISCCTRL_SOFBUSSET_MASK)
#define USB_MISCCTRL_OWNERRISODIS_MASK (0x4U)
#define USB_MISCCTRL_OWNERRISODIS_SHIFT (2U)
/*! OWNERRISODIS - OWN Error Detect for ISO IN / ISO OUT Disable
 *  0b0..OWN error detect for ISO IN / ISO OUT is not disabled.
 *  0b1..OWN error detect for ISO IN / ISO OUT is disabled.
 */
#define USB_MISCCTRL_OWNERRISODIS(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_OWNERRISODIS_SHIFT)) & USB_MISCCTRL_OWNERRISODIS_MASK)
#define USB_MISCCTRL_VREDG_EN_MASK (0x8U)
#define USB_MISCCTRL_VREDG_EN_SHIFT (3U)
/*! VREDG_EN - VREGIN Rising Edge Interrupt Enable
 *  0b0..VREGIN rising edge interrupt disabled.
 *  0b1..VREGIN rising edge interrupt enabled.
 */
#define USB_MISCCTRL_VREDG_EN(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_VREDG_EN_SHIFT)) & USB_MISCCTRL_VREDG_EN_MASK)
#define USB_MISCCTRL_VFEDG_EN_MASK (0x10U)
#define USB_MISCCTRL_VFEDG_EN_SHIFT (4U)
/*! VFEDG_EN - VREGIN Falling Edge Interrupt Enable
 *  0b0..VREGIN falling edge interrupt disabled.
 *  0b1..VREGIN falling edge interrupt enabled.
 */
#define USB_MISCCTRL_VFEDG_EN(x) \
    (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_VFEDG_EN_SHIFT)) & USB_MISCCTRL_VFEDG_EN_MASK)
/*! @} */

/*! @name CLK_RECOVER_CTRL - USB Clock recovery control */
/*! @{ */
#define USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_MASK (0x20U)
#define USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_SHIFT (5U)
/*! RESTART_IFRTRIM_EN - Restart from IFR trim value
 *  0b0..Trim fine adjustment always works based on the previous updated trim fine value (default)
 *  0b1..Trim fine restarts from the IFR trim value whenever bus_reset/bus_resume is detected or module enable is
 * desasserted
 */
#define USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN(x)                                  \
    (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_SHIFT)) & \
     USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_MASK)
#define USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_MASK (0x40U)
#define USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_SHIFT (6U)
/*! RESET_RESUME_ROUGH_EN - Reset/resume to rough phase enable
 *  0b0..Always works in tracking phase after the first time rough to track transition (default)
 *  0b1..Go back to rough stage whenever bus reset or bus resume occurs
 */
#define USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN(x)                                  \
    (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_SHIFT)) & \
     USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_MASK)
#define USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK (0x80U)
#define USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_SHIFT (7U)
/*! CLOCK_RECOVER_EN - Crystal-less USB enable
 *  0b0..Disable clock recovery block (default)
 *  0b1..Enable clock recovery block
 */
#define USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN(x)                                  \
    (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_SHIFT)) & \
     USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK)
/*! @} */

/*! @name CLK_RECOVER_INT_EN - Clock recovery combined interrupt enable */
/*! @{ */
#define USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_MASK (0x10U)
#define USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_SHIFT (4U)
/*! OVF_ERROR_EN
 *  0b0..The interrupt will be masked
 *  0b1..The interrupt will be enabled (default)
 */
#define USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN(x)                                  \
    (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_SHIFT)) & \
     USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_MASK)
/*! @} */

/*! @name CLK_RECOVER_INT_STATUS - Clock recovery separated interrupt status */
/*! @{ */
#define USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_MASK (0x10U)
#define USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_SHIFT (4U)
/*! OVF_ERROR
 *  0b0..No interrupt is reported
 *  0b1..Unmasked interrupt has been generated
 */
#define USB_CLK_RECOVER_INT_STATUS_OVF_ERROR(x)                                  \
    (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_SHIFT)) & \
     USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group USB_Register_Masks */

/* USB - Peripheral instance base addresses */
/** Peripheral USB0 base address */
#define USB0_BASE (0x40055000u)
/** Peripheral USB0 base pointer */
#define USB0 ((USB_Type *)USB0_BASE)
/** Array initializer of USB peripheral base addresses */
#define USB_BASE_ADDRS \
    {                  \
        USB0_BASE      \
    }
/** Array initializer of USB peripheral base pointers */
#define USB_BASE_PTRS \
    {                 \
        USB0          \
    }
/** Interrupt vectors for the USB peripheral type */
#define USB_IRQS  \
    {             \
        USB0_IRQn \
    }

/*!
 * @}
 */ /* end of group USB_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- VREF Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Peripheral_Access_Layer VREF Peripheral Access Layer
 * @{
 */

/** VREF - Register Layout Typedef */
typedef struct
{
    __IO uint8_t TRM; /**< VREF Trim Register, offset: 0x0 */
    __IO uint8_t SC;  /**< VREF Status and Control Register, offset: 0x1 */
    uint8_t RESERVED_0[3];
    __IO uint8_t TRM4; /**< VREF Trim Register 4, offset: 0x5 */
} VREF_Type;

/* ----------------------------------------------------------------------------
   -- VREF Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Register_Masks VREF Register Masks
 * @{
 */

/*! @name TRM - VREF Trim Register */
/*! @{ */
#define VREF_TRM_TRIM_MASK (0x3FU)
#define VREF_TRM_TRIM_SHIFT (0U)
/*! TRIM - Trim bits
 *  0b000000..Min
 *  0b000001..Max-(31 mV)
 *  0b111111..Max
 */
#define VREF_TRM_TRIM(x) (((uint8_t)(((uint8_t)(x)) << VREF_TRM_TRIM_SHIFT)) & VREF_TRM_TRIM_MASK)
#define VREF_TRM_CHOPEN_MASK (0x40U)
#define VREF_TRM_CHOPEN_SHIFT (6U)
/*! CHOPEN - Chop oscillator enable. When set, the internal chopping operation is enabled and the
 *    internal analog offset will be minimized.
 *  0b0..Chop oscillator is disabled.
 *  0b1..Chop oscillator is enabled.
 */
#define VREF_TRM_CHOPEN(x) (((uint8_t)(((uint8_t)(x)) << VREF_TRM_CHOPEN_SHIFT)) & VREF_TRM_CHOPEN_MASK)
#define VREF_TRM_FLIP_MASK (0x80U)
#define VREF_TRM_FLIP_SHIFT (7U)
#define VREF_TRM_FLIP(x) (((uint8_t)(((uint8_t)(x)) << VREF_TRM_FLIP_SHIFT)) & VREF_TRM_FLIP_MASK)
/*! @} */

/*! @name SC - VREF Status and Control Register */
/*! @{ */
#define VREF_SC_MODE_LV_MASK (0x3U)
#define VREF_SC_MODE_LV_SHIFT (0U)
/*! MODE_LV - Buffer Mode selection
 *  0b00..Bandgap on only, for stabilization and startup
 *  0b01..High power buffer mode enabled
 *  0b10..Low-power buffer mode enabled
 *  0b11..Reserved
 */
#define VREF_SC_MODE_LV(x) (((uint8_t)(((uint8_t)(x)) << VREF_SC_MODE_LV_SHIFT)) & VREF_SC_MODE_LV_MASK)
#define VREF_SC_VREFST_MASK (0x4U)
#define VREF_SC_VREFST_SHIFT (2U)
/*! VREFST - Internal Voltage Reference stable
 *  0b0..The module is disabled or not stable.
 *  0b1..The module is stable.
 */
#define VREF_SC_VREFST(x) (((uint8_t)(((uint8_t)(x)) << VREF_SC_VREFST_SHIFT)) & VREF_SC_VREFST_MASK)
#define VREF_SC_TMUXEN_MASK (0x8U)
#define VREF_SC_TMUXEN_SHIFT (3U)
/*! TMUXEN - Test MUX enable
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define VREF_SC_TMUXEN(x) (((uint8_t)(((uint8_t)(x)) << VREF_SC_TMUXEN_SHIFT)) & VREF_SC_TMUXEN_MASK)
#define VREF_SC_TRESEN_MASK (0x10U)
#define VREF_SC_TRESEN_SHIFT (4U)
/*! TRESEN - Test second order curvature compensation enable
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define VREF_SC_TRESEN(x) (((uint8_t)(((uint8_t)(x)) << VREF_SC_TRESEN_SHIFT)) & VREF_SC_TRESEN_MASK)
#define VREF_SC_ICOMPEN_MASK (0x20U)
#define VREF_SC_ICOMPEN_SHIFT (5U)
/*! ICOMPEN - Second order curvature compensation enable
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define VREF_SC_ICOMPEN(x) (((uint8_t)(((uint8_t)(x)) << VREF_SC_ICOMPEN_SHIFT)) & VREF_SC_ICOMPEN_MASK)
#define VREF_SC_REGEN_MASK (0x40U)
#define VREF_SC_REGEN_SHIFT (6U)
/*! REGEN - Regulator enable
 *  0b0..Internal 1.75 V regulator is disabled.
 *  0b1..Internal 1.75 V regulator is enabled.
 */
#define VREF_SC_REGEN(x) (((uint8_t)(((uint8_t)(x)) << VREF_SC_REGEN_SHIFT)) & VREF_SC_REGEN_MASK)
#define VREF_SC_VREFEN_MASK (0x80U)
#define VREF_SC_VREFEN_SHIFT (7U)
/*! VREFEN - Internal Voltage Reference enable
 *  0b0..The module is disabled.
 *  0b1..The module is enabled.
 */
#define VREF_SC_VREFEN(x) (((uint8_t)(((uint8_t)(x)) << VREF_SC_VREFEN_SHIFT)) & VREF_SC_VREFEN_MASK)
/*! @} */

/*! @name TRM4 - VREF Trim Register 4 */
/*! @{ */
#define VREF_TRM4_TRIM2V1_MASK (0x3FU)
#define VREF_TRM4_TRIM2V1_SHIFT (0U)
/*! TRIM2V1 - VREF 2.1V Trim Bits
 */
#define VREF_TRM4_TRIM2V1(x) (((uint8_t)(((uint8_t)(x)) << VREF_TRM4_TRIM2V1_SHIFT)) & VREF_TRM4_TRIM2V1_MASK)
#define VREF_TRM4_VREF2V1_EN_MASK (0x80U)
#define VREF_TRM4_VREF2V1_EN_SHIFT (7U)
/*! VREF2V1_EN - Internal Voltage Reference (2.1V) Enable
 *  0b0..VREF 2.1V is enabled
 *  0b1..VREF 2.1V is disabled
 */
#define VREF_TRM4_VREF2V1_EN(x) (((uint8_t)(((uint8_t)(x)) << VREF_TRM4_VREF2V1_EN_SHIFT)) & VREF_TRM4_VREF2V1_EN_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group VREF_Register_Masks */

/* VREF - Peripheral instance base addresses */
/** Peripheral VREF base address */
#define VREF_BASE (0x40072000u)
/** Peripheral VREF base pointer */
#define VREF ((VREF_Type *)VREF_BASE)
/** Array initializer of VREF peripheral base addresses */
#define VREF_BASE_ADDRS \
    {                   \
        VREF_BASE       \
    }
/** Array initializer of VREF peripheral base pointers */
#define VREF_BASE_PTRS \
    {                  \
        VREF           \
    }

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
typedef struct
{
    __IO uint32_t CS;    /**< Watchdog Control and Status Register, offset: 0x0 */
    __IO uint32_t CNT;   /**< Watchdog Counter Register, offset: 0x4 */
    __IO uint32_t TOVAL; /**< Watchdog Timeout Value Register, offset: 0x8 */
    __IO uint32_t WIN;   /**< Watchdog Window Register, offset: 0xC */
} WDOG_Type;

/* ----------------------------------------------------------------------------
   -- WDOG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Masks WDOG Register Masks
 * @{
 */

/*! @name CS - Watchdog Control and Status Register */
/*! @{ */
#define WDOG_CS_STOP_MASK (0x1U)
#define WDOG_CS_STOP_SHIFT (0U)
/*! STOP - Stop Enable
 *  0b0..Watchdog disabled in chip stop mode.
 *  0b1..Watchdog enabled in chip stop mode.
 */
#define WDOG_CS_STOP(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CS_STOP_SHIFT)) & WDOG_CS_STOP_MASK)
#define WDOG_CS_WAIT_MASK (0x2U)
#define WDOG_CS_WAIT_SHIFT (1U)
/*! WAIT - Wait Enable
 *  0b0..Watchdog disabled in chip wait mode.
 *  0b1..Watchdog enabled in chip wait mode.
 */
#define WDOG_CS_WAIT(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CS_WAIT_SHIFT)) & WDOG_CS_WAIT_MASK)
#define WDOG_CS_DBG_MASK (0x4U)
#define WDOG_CS_DBG_SHIFT (2U)
/*! DBG - Debug Enable
 *  0b0..Watchdog disabled in chip debug mode.
 *  0b1..Watchdog enabled in chip debug mode.
 */
#define WDOG_CS_DBG(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CS_DBG_SHIFT)) & WDOG_CS_DBG_MASK)
#define WDOG_CS_TST_MASK (0x18U)
#define WDOG_CS_TST_SHIFT (3U)
/*! TST - Watchdog Test
 *  0b00..Watchdog test mode disabled.
 *  0b01..Watchdog user mode enabled. (Watchdog test mode disabled.) After testing the watchdog, software should
 *        use this setting to indicate that the watchdog is functioning normally in user mode.
 *  0b10..Watchdog test mode enabled, only the low byte is used. CNT[CNTLOW] is compared with TOVAL[TOVALLOW].
 *  0b11..Watchdog test mode enabled, only the high byte is used. CNT[CNTHIGH] is compared with TOVAL[TOVALHIGH].
 */
#define WDOG_CS_TST(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CS_TST_SHIFT)) & WDOG_CS_TST_MASK)
#define WDOG_CS_UPDATE_MASK (0x20U)
#define WDOG_CS_UPDATE_SHIFT (5U)
/*! UPDATE - Allow updates
 *  0b0..Updates not allowed. After the initial configuration, the watchdog cannot be later modified without forcing a
 * reset. 0b1..Updates allowed. Software can modify the watchdog configuration registers within 128 bus clocks after
 * performing the unlock write sequence.
 */
#define WDOG_CS_UPDATE(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CS_UPDATE_SHIFT)) & WDOG_CS_UPDATE_MASK)
#define WDOG_CS_INT_MASK (0x40U)
#define WDOG_CS_INT_SHIFT (6U)
/*! INT - Watchdog Interrupt
 *  0b0..Watchdog interrupts are disabled. Watchdog resets are not delayed.
 *  0b1..Watchdog interrupts are enabled. Watchdog resets are delayed by 128 bus clocks from the interrupt vector fetch.
 */
#define WDOG_CS_INT(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CS_INT_SHIFT)) & WDOG_CS_INT_MASK)
#define WDOG_CS_EN_MASK (0x80U)
#define WDOG_CS_EN_SHIFT (7U)
/*! EN - Watchdog Enable
 *  0b0..Watchdog disabled.
 *  0b1..Watchdog enabled.
 */
#define WDOG_CS_EN(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CS_EN_SHIFT)) & WDOG_CS_EN_MASK)
#define WDOG_CS_CLK_MASK (0x300U)
#define WDOG_CS_CLK_SHIFT (8U)
/*! CLK - Watchdog Clock
 *  0b00..Bus clock.
 *  0b01..Internal low-power oscillator (LPOCLK).
 *  0b10..8 MHz internal reference clock.
 *  0b11..External clock source.
 */
#define WDOG_CS_CLK(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CS_CLK_SHIFT)) & WDOG_CS_CLK_MASK)
#define WDOG_CS_PRES_MASK (0x1000U)
#define WDOG_CS_PRES_SHIFT (12U)
/*! PRES - Watchdog Prescalar
 *  0b0..256 prescalar disabled.
 *  0b1..256 prescalar enabled.
 */
#define WDOG_CS_PRES(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CS_PRES_SHIFT)) & WDOG_CS_PRES_MASK)
#define WDOG_CS_CMD32EN_MASK (0x2000U)
#define WDOG_CS_CMD32EN_SHIFT (13U)
/*! CMD32EN
 *  0b0..Disables support for 32-bit (or 16-bit or 8-bit) refresh/unlock command write words
 *  0b1..Enables support for 32-bit (or 16-bit or 8-bit) refresh/unlock command write words
 */
#define WDOG_CS_CMD32EN(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CS_CMD32EN_SHIFT)) & WDOG_CS_CMD32EN_MASK)
#define WDOG_CS_FLG_MASK (0x4000U)
#define WDOG_CS_FLG_SHIFT (14U)
/*! FLG - Watchdog Interrupt Flag
 *  0b0..No interrupt occurred.
 *  0b1..An interrupt occurred.
 */
#define WDOG_CS_FLG(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CS_FLG_SHIFT)) & WDOG_CS_FLG_MASK)
#define WDOG_CS_WIN_MASK (0x8000U)
#define WDOG_CS_WIN_SHIFT (15U)
/*! WIN - Watchdog Window
 *  0b0..Window mode disabled.
 *  0b1..Window mode enabled.
 */
#define WDOG_CS_WIN(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CS_WIN_SHIFT)) & WDOG_CS_WIN_MASK)
/*! @} */

/*! @name CNT - Watchdog Counter Register */
/*! @{ */
#define WDOG_CNT_CNTLOW_MASK (0xFFU)
#define WDOG_CNT_CNTLOW_SHIFT (0U)
/*! CNTLOW - Low byte of the Watchdog Counter
 */
#define WDOG_CNT_CNTLOW(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CNT_CNTLOW_SHIFT)) & WDOG_CNT_CNTLOW_MASK)
#define WDOG_CNT_CNTHIGH_MASK (0xFF00U)
#define WDOG_CNT_CNTHIGH_SHIFT (8U)
/*! CNTHIGH - High byte of the Watchdog Counter
 */
#define WDOG_CNT_CNTHIGH(x) (((uint32_t)(((uint32_t)(x)) << WDOG_CNT_CNTHIGH_SHIFT)) & WDOG_CNT_CNTHIGH_MASK)
/*! @} */

/*! @name TOVAL - Watchdog Timeout Value Register */
/*! @{ */
#define WDOG_TOVAL_TOVALLOW_MASK (0xFFU)
#define WDOG_TOVAL_TOVALLOW_SHIFT (0U)
/*! TOVALLOW - Low byte of the timeout value
 */
#define WDOG_TOVAL_TOVALLOW(x) (((uint32_t)(((uint32_t)(x)) << WDOG_TOVAL_TOVALLOW_SHIFT)) & WDOG_TOVAL_TOVALLOW_MASK)
#define WDOG_TOVAL_TOVALHIGH_MASK (0xFF00U)
#define WDOG_TOVAL_TOVALHIGH_SHIFT (8U)
/*! TOVALHIGH - High byte of the timeout value;
 */
#define WDOG_TOVAL_TOVALHIGH(x) \
    (((uint32_t)(((uint32_t)(x)) << WDOG_TOVAL_TOVALHIGH_SHIFT)) & WDOG_TOVAL_TOVALHIGH_MASK)
/*! @} */

/*! @name WIN - Watchdog Window Register */
/*! @{ */
#define WDOG_WIN_WINLOW_MASK (0xFFU)
#define WDOG_WIN_WINLOW_SHIFT (0U)
/*! WINLOW - Low byte of Watchdog Window
 */
#define WDOG_WIN_WINLOW(x) (((uint32_t)(((uint32_t)(x)) << WDOG_WIN_WINLOW_SHIFT)) & WDOG_WIN_WINLOW_MASK)
#define WDOG_WIN_WINHIGH_MASK (0xFF00U)
#define WDOG_WIN_WINHIGH_SHIFT (8U)
/*! WINHIGH - High byte of Watchdog Window
 */
#define WDOG_WIN_WINHIGH(x) (((uint32_t)(((uint32_t)(x)) << WDOG_WIN_WINHIGH_SHIFT)) & WDOG_WIN_WINHIGH_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group WDOG_Register_Masks */

/* WDOG - Peripheral instance base addresses */
/** Peripheral WDOG0 base address */
#define WDOG0_BASE (0x40076000u)
/** Peripheral WDOG0 base pointer */
#define WDOG0 ((WDOG_Type *)WDOG0_BASE)
/** Array initializer of WDOG peripheral base addresses */
#define WDOG_BASE_ADDRS \
    {                   \
        WDOG0_BASE      \
    }
/** Array initializer of WDOG peripheral base pointers */
#define WDOG_BASE_PTRS \
    {                  \
        WDOG0          \
    }
/** Interrupt vectors for the WDOG peripheral type */
#define WDOG_IRQS  \
    {              \
        WDOG0_IRQn \
    }
#define WDOG_UPDATE_KEY (0xD928C520U)
#define WDOG_REFRESH_KEY (0xB480A602U)

/*!
 * @}
 */ /* end of group WDOG_Peripheral_Access_Layer */

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
#pragma language = default
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
#define NXP_VAL2FLD(field, value) (((value) << (field##_SHIFT)) & (field##_MASK))
/**
 * @brief Mask and right-shift a register value to extract a bit field value.
 * @param field Name of the register bit field.
 * @param value Value of the register.
 * @return Masked and shifted bit field value.
 */
#define NXP_FLD2VAL(field, value) (((value) & (field##_MASK)) >> (field##_SHIFT))

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

#define FPTA_BASE FGPIOA_BASE
#define FPTA FGPIOA
#define PTA_BASE GPIOA_BASE
#define PTA GPIOA
#define PTB_BASE GPIOB_BASE
#define PTB GPIOB
#define PTC_BASE GPIOC_BASE
#define PTC GPIOC
#define PTD_BASE GPIOD_BASE
#define PTD GPIOD
#define PTE_BASE GPIOE_BASE
#define PTE GPIOE
#define LPTimer_IRQn LPTMR0_IRQn
#define LPTimer_IRQHandler LPTMR0_IRQHandler
#define TRNG0 TRNG
#define CAU CAU0
#define CAU_BASE CAU0_BASE

/*!
 * @}
 */ /* end of group SDK_Compatibility_Symbols */

#endif /* _K32L2A41A_H_ */
