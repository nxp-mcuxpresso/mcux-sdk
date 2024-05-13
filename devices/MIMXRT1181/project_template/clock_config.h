/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _CLOCK_CONFIG_H_
#define _CLOCK_CONFIG_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define BOARD_XTAL0_CLK_HZ 24000000U /*!< Board xtal0 frequency in Hz */

#define BOARD_XTAL32K_CLK_HZ 32768U  /*!< Board xtal32k frequency in Hz */

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes default configuration of clocks.
 *
 */
void BOARD_InitBootClocks(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 ********************** Configuration BOARD_BootClockRUN ***********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_BootClockRUN configuration
 ******************************************************************************/
#if __CORTEX_M == 7
    #define BOARD_BOOTCLOCKRUN_CORE_CLOCK 792000000UL /*!< CM7 Core clock frequency: 792000000Hz */
#else
    #define BOARD_BOOTCLOCKRUN_CORE_CLOCK 240000000UL /*!< CM33 Core clock frequency: 240000000Hz */
#endif

/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKRUN_ACMP_CLK_ROOT              240000000UL
#define BOARD_BOOTCLOCKRUN_ADC1_CLK_ROOT              80000000UL
#define BOARD_BOOTCLOCKRUN_ADC2_CLK_ROOT              80000000UL
#define BOARD_BOOTCLOCKRUN_ARM_PLL_CLK                792000000UL
#define BOARD_BOOTCLOCKRUN_ASRC_CLK_ROOT              240000000UL
#define BOARD_BOOTCLOCKRUN_BUS_AON_CLK_ROOT           132000000UL
#define BOARD_BOOTCLOCKRUN_BUS_WAKEUP_CLK_ROOT        132000000UL
#define BOARD_BOOTCLOCKRUN_CAN1_CLK_ROOT              80000000UL
#define BOARD_BOOTCLOCKRUN_CAN2_CLK_ROOT              80000000UL
#define BOARD_BOOTCLOCKRUN_CAN3_CLK_ROOT              80000000UL
#define BOARD_BOOTCLOCKRUN_CCM_CKO1_CLK_ROOT          80000000UL
#define BOARD_BOOTCLOCKRUN_CCM_CKO2_CLK_ROOT          50000000UL
#define BOARD_BOOTCLOCKRUN_CLK_1M                     1000000UL
#define BOARD_BOOTCLOCKRUN_ECAT_CLK_ROOT              100000000UL
#define BOARD_BOOTCLOCKRUN_ECAT_PORT0_REF_CLK         50000000UL
#define BOARD_BOOTCLOCKRUN_ECAT_PORT1_REF_CLK         50000000UL
#define BOARD_BOOTCLOCKRUN_EDGELOCK_CLK_ROOT          200000000UL
#define BOARD_BOOTCLOCKRUN_ENET_REFCLK_ROOT           125000000UL
#define BOARD_BOOTCLOCKRUN_FLEXIO1_CLK_ROOT           120000000UL
#define BOARD_BOOTCLOCKRUN_FLEXIO2_CLK_ROOT           48000000UL
#define BOARD_BOOTCLOCKRUN_FLEXSPI1_CLK_ROOT          130909090UL
#define BOARD_BOOTCLOCKRUN_FLEXSPI2_CLK_ROOT          110769230UL
#define BOARD_BOOTCLOCKRUN_FLEXSPI_SLV_CLK_ROOT       132000000UL
#define BOARD_BOOTCLOCKRUN_GPT1_CLK_ROOT              240000000UL
#define BOARD_BOOTCLOCKRUN_GPT2_CLK_ROOT              240000000UL
#define BOARD_BOOTCLOCKRUN_I3C1_CLK_ROOT              24000000UL
#define BOARD_BOOTCLOCKRUN_I3C2_CLK_ROOT              24000000UL
#define BOARD_BOOTCLOCKRUN_LPI2C0102_CLK_ROOT         60000000UL
#define BOARD_BOOTCLOCKRUN_LPI2C0304_CLK_ROOT         60000000UL
#define BOARD_BOOTCLOCKRUN_LPI2C0506_CLK_ROOT         60000000UL
#define BOARD_BOOTCLOCKRUN_LPIT3_CLK_ROOT             80000000UL
#define BOARD_BOOTCLOCKRUN_LPSPI0102_CLK_ROOT         130909090UL
#define BOARD_BOOTCLOCKRUN_LPSPI0304_CLK_ROOT         130909090UL
#define BOARD_BOOTCLOCKRUN_LPSPI0506_CLK_ROOT         130909090UL
#define BOARD_BOOTCLOCKRUN_LPTMR1_CLK_ROOT            80000000UL
#define BOARD_BOOTCLOCKRUN_LPTMR2_CLK_ROOT            80000000UL
#define BOARD_BOOTCLOCKRUN_LPTMR3_CLK_ROOT            80000000UL
#define BOARD_BOOTCLOCKRUN_LPUART0102_CLK_ROOT        24000000UL
#define BOARD_BOOTCLOCKRUN_LPUART0304_CLK_ROOT        24000000UL
#define BOARD_BOOTCLOCKRUN_LPUART0506_CLK_ROOT        24000000UL
#define BOARD_BOOTCLOCKRUN_LPUART0708_CLK_ROOT        24000000UL
#define BOARD_BOOTCLOCKRUN_LPUART0910_CLK_ROOT        24000000UL
#define BOARD_BOOTCLOCKRUN_LPUART1112_CLK_ROOT        24000000UL
#define BOARD_BOOTCLOCKRUN_M33_CLK_ROOT               240000000UL
#define BOARD_BOOTCLOCKRUN_M33_SYSTICK_CLK_ROOT       100000UL
#define BOARD_BOOTCLOCKRUN_M7_CLK_ROOT                792000000UL
#define BOARD_BOOTCLOCKRUN_M7_SYSTICK_CLK_ROOT        100000UL
#define BOARD_BOOTCLOCKRUN_MAC0_CLK_ROOT              50000000UL
#define BOARD_BOOTCLOCKRUN_MAC1_CLK_ROOT              125000000UL
#define BOARD_BOOTCLOCKRUN_MAC2_CLK_ROOT              125000000UL
#define BOARD_BOOTCLOCKRUN_MAC3_CLK_ROOT              125000000UL
#define BOARD_BOOTCLOCKRUN_MAC4_CLK_ROOT              50000000UL
#define BOARD_BOOTCLOCKRUN_MIC_CLK_ROOT               80000000UL
#define BOARD_BOOTCLOCKRUN_NETC_CLK_ROOT              240000000UL
#define BOARD_BOOTCLOCKRUN_NETC_PORT0_REF_CLK         50000000UL
#define BOARD_BOOTCLOCKRUN_NETC_PORT1_REF_CLK         50000000UL
#define BOARD_BOOTCLOCKRUN_NETC_PORT2_REF_CLK         50000000UL
#define BOARD_BOOTCLOCKRUN_NETC_PORT3_REF_CLK         50000000UL
#define BOARD_BOOTCLOCKRUN_NETC_PORT4_REF_CLK         50000000UL
#define BOARD_BOOTCLOCKRUN_OSC_24M                    24000000UL
#define BOARD_BOOTCLOCKRUN_OSC_32K                    32768UL
#define BOARD_BOOTCLOCKRUN_OSC_RC_24M                 24000000UL
#define BOARD_BOOTCLOCKRUN_OSC_RC_400M                400000000UL
#define BOARD_BOOTCLOCKRUN_PLL_AUDIO_CLK              0UL
#define BOARD_BOOTCLOCKRUN_PLL_AUDIO_SS_MODULATION    0UL
#define BOARD_BOOTCLOCKRUN_PLL_AUDIO_SS_RANGE         0UL
#define BOARD_BOOTCLOCKRUN_SAI1_CLK_ROOT              0UL
#define BOARD_BOOTCLOCKRUN_SAI1_MCLK1                 0UL
#define BOARD_BOOTCLOCKRUN_SAI1_MCLK2                 0UL
#define BOARD_BOOTCLOCKRUN_SAI2_CLK_ROOT              0UL
#define BOARD_BOOTCLOCKRUN_SAI2_MCLK1                 0UL
#define BOARD_BOOTCLOCKRUN_SAI2_MCLK2                 0UL
#define BOARD_BOOTCLOCKRUN_SAI2_MCLK3                 0UL
#define BOARD_BOOTCLOCKRUN_SAI3_CLK_ROOT              0UL
#define BOARD_BOOTCLOCKRUN_SAI3_MCLK1                 0UL
#define BOARD_BOOTCLOCKRUN_SAI3_MCLK2                 0UL
#define BOARD_BOOTCLOCKRUN_SAI3_MCLK3                 0UL
#define BOARD_BOOTCLOCKRUN_SAI4_CLK_ROOT              0UL
#define BOARD_BOOTCLOCKRUN_SAI4_MCLK1                 0UL
#define BOARD_BOOTCLOCKRUN_SAI4_MCLK2                 0UL
#define BOARD_BOOTCLOCKRUN_SAI4_MCLK3                 0UL
#define BOARD_BOOTCLOCKRUN_SEMC_CLK_ROOT              200000000UL
#define BOARD_BOOTCLOCKRUN_SPDIF_CLK_ROOT             0UL
#define BOARD_BOOTCLOCKRUN_SPDIF_EXTCLK_OUT           0UL
#define BOARD_BOOTCLOCKRUN_SWO_TRACE_CLK_ROOT         80000000UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL1_CLK               1000000000UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL1_DIV2_CLK          500000000UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL1_DIV5_CLK          200000000UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL1_SS_MODULATION     0UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL1_SS_RANGE          0UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_CLK               528000000UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_PFD0_CLK          352000000UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_PFD1_CLK          594000000UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_PFD2_CLK          396000000UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_PFD3_CLK          297000000UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_SS_MODULATION     0UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_SS_RANGE          0UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_CLK               480000000UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_DIV2_CLK          240000000UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_PFD0_CLK          392727272UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_PFD1_CLK          261818181UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_PFD2_CLK          332307692UL
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_PFD3_CLK          480000000UL
#define BOARD_BOOTCLOCKRUN_TMR_1588_CLK_ROOT          240000000UL
#define BOARD_BOOTCLOCKRUN_TMR_1588_REF_CLK           240000000UL
#define BOARD_BOOTCLOCKRUN_TPM2_CLK_ROOT              80000000UL
#define BOARD_BOOTCLOCKRUN_TPM4_CLK_ROOT              80000000UL
#define BOARD_BOOTCLOCKRUN_TPM5_CLK_ROOT              80000000UL
#define BOARD_BOOTCLOCKRUN_TPM6_CLK_ROOT              80000000UL
#define BOARD_BOOTCLOCKRUN_USDHC1_CLK_ROOT            198000000UL
#define BOARD_BOOTCLOCKRUN_USDHC2_CLK_ROOT            396000000UL
#define BOARD_BOOTCLOCKRUN_WAKEUP_AXI_CLK_ROOT        240000000UL


/*******************************************************************************
 * API for BOARD_BootClockRUN configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_BootClockRUN(void);

/*FUNCTION**********************************************************************
 *
 * Function Name : EdgeLock_SetClock
 * Description   : Set EdgeLock clock via safe method
 * Note          : It requires specific sequence to change edgelock clock source,
                   otherwise the soc behavior is unpredictable.
 *END**************************************************************************/
void EdgeLock_SetClock(uint8_t mux, uint8_t div);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* _CLOCK_CONFIG_H_ */

