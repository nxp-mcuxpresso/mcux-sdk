/*
 * Copyright 2017 - 2020, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#include "fsl_device_registers.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

/*!
 * @addtogroup clock
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.3.2. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 3, 2))
/*@}*/

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (400000000UL)
#endif

/*!
 * @brief XTAL 25M clock frequency.
 */
#define OSC25M_CLK_FREQ 25000000U

/*!
 * @brief XTAL 27M clock frequency.
 */
#define OSC27M_CLK_FREQ 27000000U

/*!
 * @brief HDMI PHY 27M clock frequency.
 */
#define HDMI_PHY_27M_FREQ 27000000U

/*!
 * @brief clock1PN frequency.
 */
#define CLKPN_FREQ 0U

/*! @brief Clock ip name array for ECSPI. */
#define ECSPI_CLOCKS                                                   \
    {                                                                  \
        kCLOCK_IpInvalid, kCLOCK_Ecspi1, kCLOCK_Ecspi2, kCLOCK_Ecspi3, \
    }

/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS                                                                             \
    {                                                                                           \
        kCLOCK_IpInvalid, kCLOCK_Gpio1, kCLOCK_Gpio2, kCLOCK_Gpio3, kCLOCK_Gpio4, kCLOCK_Gpio5, \
    }

/*! @brief Clock ip name array for GPT. */
#define GPT_CLOCKS                                                                                      \
    {                                                                                                   \
        kCLOCK_IpInvalid, kCLOCK_Gpt1, kCLOCK_Gpt2, kCLOCK_Gpt3, kCLOCK_Gpt4, kCLOCK_Gpt5, kCLOCK_Gpt6, \
    }

/*! @brief Clock ip name array for I2C. */
#define I2C_CLOCKS                                                            \
    {                                                                         \
        kCLOCK_IpInvalid, kCLOCK_I2c1, kCLOCK_I2c2, kCLOCK_I2c3, kCLOCK_I2c4, \
    }

/*! @brief Clock ip name array for IOMUX. */
#define IOMUX_CLOCKS  \
    {                 \
        kCLOCK_Iomux, \
    }

/*! @brief Clock ip name array for IPMUX. */
#define IPMUX_CLOCKS                                                \
    {                                                               \
        kCLOCK_Ipmux1, kCLOCK_Ipmux2, kCLOCK_Ipmux3, kCLOCK_Ipmux4, \
    }

/*! @brief Clock ip name array for PWM. */
#define PWM_CLOCKS                                                            \
    {                                                                         \
        kCLOCK_IpInvalid, kCLOCK_Pwm1, kCLOCK_Pwm2, kCLOCK_Pwm3, kCLOCK_Pwm4, \
    }

/*! @brief Clock ip name array for RDC. */
#define RDC_CLOCKS  \
    {               \
        kCLOCK_Rdc, \
    }

/*! @brief Clock ip name array for SAI. */
#define SAI_CLOCKS                                                                                      \
    {                                                                                                   \
        kCLOCK_IpInvalid, kCLOCK_Sai1, kCLOCK_Sai2, kCLOCK_Sai3, kCLOCK_Sai4, kCLOCK_Sai5, kCLOCK_Sai6, \
    }

/*! @brief Clock ip name array for RDC SEMA42. */
#define RDC_SEMA42_CLOCKS                                  \
    {                                                      \
        kCLOCK_IpInvalid, kCLOCK_Sema42_1, kCLOCK_Sema42_2 \
    }

/*! @brief Clock ip name array for UART. */
#define UART_CLOCKS                                                               \
    {                                                                             \
        kCLOCK_IpInvalid, kCLOCK_Uart1, kCLOCK_Uart2, kCLOCK_Uart3, kCLOCK_Uart4, \
    }

/*! @brief Clock ip name array for USDHC. */
#define USDHC_CLOCKS                                   \
    {                                                  \
        kCLOCK_IpInvalid, kCLOCK_Usdhc1, kCLOCK_Usdhc2 \
    }

/*! @brief Clock ip name array for WDOG. */
#define WDOG_CLOCKS                                                \
    {                                                              \
        kCLOCK_IpInvalid, kCLOCK_Wdog1, kCLOCK_Wdog2, kCLOCK_Wdog3 \
    }

/*! @brief Clock ip name array for TEMPSENSOR. */
#define TMU_CLOCKS         \
    {                      \
        kCLOCK_TempSensor, \
    }

/*! @brief Clock ip name array for SDMA. */
#define SDMA_CLOCKS                \
    {                              \
        kCLOCK_Sdma1, kCLOCK_Sdma2 \
    }

/*! @brief Clock ip name array for MU. */
#define MU_CLOCKS \
    {             \
        kCLOCK_Mu \
    }

/*! @brief Clock ip name array for QSPI. */
#define QSPI_CLOCKS \
    {               \
        kCLOCK_Qspi \
    }

/*!
 * @brief CCM reg macros to extract corresponding registers bit field.
 */
#define CCM_BIT_FIELD_EXTRACTION(val, mask, shift) (((val) & (mask)) >> (shift))

/*!
 * @brief CCM reg macros to map corresponding registers.
 */
#define CCM_REG_OFF(root, off) (*((volatile uint32_t *)((uint32_t)(root) + (off))))
#define CCM_REG(root)          CCM_REG_OFF(root, 0U)
#define CCM_REG_SET(root)      CCM_REG_OFF(root, 4U)
#define CCM_REG_CLR(root)      CCM_REG_OFF(root, 8U)

/*!
 * @brief CCM Analog registers offset.
 */
#define AUDIO_PLL1_CFG0_OFFSET 0x00
#define AUDIO_PLL2_CFG0_OFFSET 0x08
#define VIDEO_PLL1_CFG0_OFFSET 0x10
#define GPU_PLL_CFG0_OFFSET    0x18
#define VPU_PLL_CFG0_OFFSET    0x20
#define ARM_PLL_CFG0_OFFSET    0x28
#define SYS_PLL1_CFG0_OFFSET   0x30
#define SYS_PLL2_CFG0_OFFSET   0x3C
#define SYS_PLL3_CFG0_OFFSET   0x48
#define VIDEO_PLL2_CFG0_OFFSET 0x54
#define DRAM_PLL_CFG0_OFFSET   0x60
#define OSC_MISC_CFG_OFFSET    0x70

/*!
 * @brief CCM ANALOG tuple macros to map corresponding registers and bit fields.
 */
#define CCM_ANALOG_TUPLE(reg, shift)  ((((reg)&0xFFFFU) << 16U) | (shift))
#define CCM_ANALOG_TUPLE_SHIFT(tuple) (((uint32_t)(tuple)) & 0x1FU)
#define CCM_ANALOG_TUPLE_REG_OFF(base, tuple, off) \
    (*((volatile uint32_t *)((uint32_t)(base) + (((uint32_t)(tuple) >> 16U) & 0xFFFFU) + (off))))
#define CCM_ANALOG_TUPLE_REG(base, tuple) CCM_ANALOG_TUPLE_REG_OFF(base, tuple, 0U)

/*!
 * @brief CCM CCGR and root tuple
 */
#define CCM_TUPLE(ccgr, root) ((ccgr) << 16U | (root))
#define CCM_TUPLE_CCGR(tuple) ((uint32_t)(&(CCM)->CCGR[(uint32_t)(tuple) >> 16U].CCGR))
#define CCM_TUPLE_ROOT(tuple) ((uint32_t)(&(CCM)->ROOT[(uint32_t)(tuple)&0xFFFFU].TARGET_ROOT))

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{
    kCLOCK_CoreM4Clk, /*!< ARM M4 Core clock                          */

    kCLOCK_AxiClk, /*!< Main AXI bus clock.                         */
    kCLOCK_AhbClk, /*!< AHB bus clock.                         */
    kCLOCK_IpgClk, /*!< IPG bus clock.                         */

    /* -------------------------------- Other clock --------------------------*/
} clock_name_t;

#define kCLOCK_CoreSysClk       kCLOCK_CoreM4Clk    /*!< For compatible with other platforms without CCM. */
#define CLOCK_GetCoreSysClkFreq CLOCK_GetCoreM4Freq /*!< For compatible with other platforms without CCM. */

/*! @brief CCM CCGR gate control. */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = -1,

    kCLOCK_Debug = CCM_TUPLE(4U, 32U), /*!< DEBUG Clock Gate.*/

    kCLOCK_Dram = CCM_TUPLE(5U, 64U), /*!< DRAM Clock Gate.*/

    kCLOCK_Ecspi1 = CCM_TUPLE(7U, 101U), /*!< ECSPI1 Clock Gate.*/
    kCLOCK_Ecspi2 = CCM_TUPLE(8U, 102U), /*!< ECSPI2 Clock Gate.*/
    kCLOCK_Ecspi3 = CCM_TUPLE(9U, 131U), /*!< ECSPI3 Clock Gate.*/

    kCLOCK_Gpio1 = CCM_TUPLE(11U, 33U), /*!< GPIO1 Clock Gate.*/
    kCLOCK_Gpio2 = CCM_TUPLE(12U, 33U), /*!< GPIO2 Clock Gate.*/
    kCLOCK_Gpio3 = CCM_TUPLE(13U, 33U), /*!< GPIO3 Clock Gate.*/
    kCLOCK_Gpio4 = CCM_TUPLE(14U, 33U), /*!< GPIO4 Clock Gate.*/
    kCLOCK_Gpio5 = CCM_TUPLE(15U, 33U), /*!< GPIO5 Clock Gate.*/

    kCLOCK_Gpt1 = CCM_TUPLE(16U, 107U), /*!< GPT1 Clock Gate.*/
    kCLOCK_Gpt2 = CCM_TUPLE(17U, 108U), /*!< GPT2 Clock Gate.*/
    kCLOCK_Gpt3 = CCM_TUPLE(18U, 109U), /*!< GPT3 Clock Gate.*/
    kCLOCK_Gpt4 = CCM_TUPLE(19U, 110U), /*!< GPT4 Clock Gate.*/
    kCLOCK_Gpt5 = CCM_TUPLE(20U, 111U), /*!< GPT5 Clock Gate.*/
    kCLOCK_Gpt6 = CCM_TUPLE(21U, 112U), /*!< GPT6 Clock Gate.*/

    kCLOCK_I2c1 = CCM_TUPLE(23U, 90U), /*!< I2C1 Clock Gate.*/
    kCLOCK_I2c2 = CCM_TUPLE(24U, 91U), /*!< I2C2 Clock Gate.*/
    kCLOCK_I2c3 = CCM_TUPLE(25U, 92U), /*!< I2C3 Clock Gate.*/
    kCLOCK_I2c4 = CCM_TUPLE(26U, 93U), /*!< I2C4 Clock Gate.*/

    kCLOCK_Iomux  = CCM_TUPLE(27U, 33U), /*!< IOMUX Clock Gate.*/
    kCLOCK_Ipmux1 = CCM_TUPLE(28U, 33U), /*!< IPMUX1 Clock Gate.*/
    kCLOCK_Ipmux2 = CCM_TUPLE(29U, 33U), /*!< IPMUX2 Clock Gate.*/
    kCLOCK_Ipmux3 = CCM_TUPLE(30U, 33U), /*!< IPMUX3 Clock Gate.*/
    kCLOCK_Ipmux4 = CCM_TUPLE(31U, 33U), /*!< IPMUX4 Clock Gate.*/

    kCLOCK_M4 = CCM_TUPLE(32U, 1U), /*!< M4 Clock Gate.*/

    kCLOCK_Mu = CCM_TUPLE(33U, 33U), /*!< MU Clock Gate.*/

    kCLOCK_Ocram  = CCM_TUPLE(35U, 16U), /*!< OCRAM Clock Gate.*/
    kCLOCK_OcramS = CCM_TUPLE(36U, 32U), /*!< OCRAM S Clock Gate.*/

    kCLOCK_Pwm1 = CCM_TUPLE(40U, 103U), /*!< PWM1 Clock Gate.*/
    kCLOCK_Pwm2 = CCM_TUPLE(41U, 104U), /*!< PWM2 Clock Gate.*/
    kCLOCK_Pwm3 = CCM_TUPLE(42U, 105U), /*!< PWM3 Clock Gate.*/
    kCLOCK_Pwm4 = CCM_TUPLE(43U, 106U), /*!< PWM4 Clock Gate.*/

    kCLOCK_Qspi = CCM_TUPLE(47U, 87U), /*!< QSPI Clock Gate.*/

    kCLOCK_Rdc = CCM_TUPLE(49U, 33U), /*!< RDC Clock Gate.*/

    kCLOCK_Sai1 = CCM_TUPLE(51U, 75U), /*!< SAI1 Clock Gate.*/
    kCLOCK_Sai2 = CCM_TUPLE(52U, 76U), /*!< SAI2 Clock Gate.*/
    kCLOCK_Sai3 = CCM_TUPLE(53U, 77U), /*!< SAI3 Clock Gate.*/
    kCLOCK_Sai4 = CCM_TUPLE(54U, 78U), /*!< SAI4 Clock Gate.*/
    kCLOCK_Sai5 = CCM_TUPLE(55U, 79U), /*!< SAI5 Clock Gate.*/
    kCLOCK_Sai6 = CCM_TUPLE(56U, 80U), /*!< SAI6 Clock Gate.*/

    kCLOCK_Sdma1 = CCM_TUPLE(58U, 33U), /*!< SDMA1 Clock Gate.*/
    kCLOCK_Sdma2 = CCM_TUPLE(59U, 35U), /*!< SDMA2 Clock Gate.*/

    kCLOCK_Sec_Debug = CCM_TUPLE(60U, 33U), /*!< SEC_DEBUG Clock Gate.*/

    kCLOCK_Sema42_1 = CCM_TUPLE(61U, 33U), /*!< RDC SEMA42 Clock Gate.*/
    kCLOCK_Sema42_2 = CCM_TUPLE(62U, 33U), /*!< RDC SEMA42 Clock Gate.*/

    kCLOCK_Sim_display = CCM_TUPLE(63U, 16U), /*!< SIM_Display Clock Gate.*/
    kCLOCK_Sim_m       = CCM_TUPLE(65U, 32U), /*!< SIM_M Clock Gate.*/
    kCLOCK_Sim_main    = CCM_TUPLE(66U, 16U), /*!< SIM_MAIN Clock Gate.*/
    kCLOCK_Sim_s       = CCM_TUPLE(67U, 32U), /*!< SIM_S Clock Gate.*/
    kCLOCK_Sim_wakeup  = CCM_TUPLE(68U, 32U), /*!< SIM_WAKEUP Clock Gate.*/

    kCLOCK_Uart1 = CCM_TUPLE(73U, 94U), /*!< UART1 Clock Gate.*/
    kCLOCK_Uart2 = CCM_TUPLE(74U, 95U), /*!< UART2 Clock Gate.*/
    kCLOCK_Uart3 = CCM_TUPLE(75U, 96U), /*!< UART3 Clock Gate.*/
    kCLOCK_Uart4 = CCM_TUPLE(76U, 97U), /*!< UART4 Clock Gate.*/

    kCLOCK_Wdog1 = CCM_TUPLE(83U, 114U), /*!< WDOG1 Clock Gate.*/
    kCLOCK_Wdog2 = CCM_TUPLE(84U, 114U), /*!< WDOG2 Clock Gate.*/
    kCLOCK_Wdog3 = CCM_TUPLE(85U, 114U), /*!< WDOG3 Clock Gate.*/

    kCLOCK_TempSensor = CCM_TUPLE(98U, 0xFFFF), /*!< TempSensor Clock Gate.*/

} clock_ip_name_t;

/*! @brief ccm root name used to get clock frequency. */
typedef enum _clock_root_control
{
    kCLOCK_RootM4      = (uint32_t)(&(CCM)->ROOT[1].TARGET_ROOT),  /*!< ARM Cortex-M4 Clock control name.*/
    kCLOCK_RootAxi     = (uint32_t)(&(CCM)->ROOT[16].TARGET_ROOT), /*!< AXI Clock control name.*/
    kCLOCK_RootNoc     = (uint32_t)(&(CCM)->ROOT[26].TARGET_ROOT), /*!< NOC Clock control name.*/
    kCLOCK_RootAhb     = (uint32_t)(&(CCM)->ROOT[32].TARGET_ROOT), /*!< AHB Clock control name.*/
    kCLOCK_RootIpg     = (uint32_t)(&(CCM)->ROOT[33].TARGET_ROOT), /*!< IPG Clock control name.*/
    kCLOCK_RootDramAlt = (uint32_t)(&(CCM)->ROOT[64].TARGET_ROOT), /*!< DRAM ALT Clock control name.*/

    kCLOCK_RootSai1 = (uint32_t)(&(CCM)->ROOT[75].TARGET_ROOT), /*!< SAI1 Clock control name.*/
    kCLOCK_RootSai2 = (uint32_t)(&(CCM)->ROOT[76].TARGET_ROOT), /*!< SAI2 Clock control name.*/
    kCLOCK_RootSai3 = (uint32_t)(&(CCM)->ROOT[77].TARGET_ROOT), /*!< SAI3 Clock control name.*/
    kCLOCK_RootSai4 = (uint32_t)(&(CCM)->ROOT[78].TARGET_ROOT), /*!< SAI4 Clock control name.*/
    kCLOCK_RootSai5 = (uint32_t)(&(CCM)->ROOT[79].TARGET_ROOT), /*!< SAI5 Clock control name.*/
    kCLOCK_RootSai6 = (uint32_t)(&(CCM)->ROOT[80].TARGET_ROOT), /*!< SAI6 Clock control name.*/

    kCLOCK_RootQspi = (uint32_t)(&(CCM)->ROOT[87].TARGET_ROOT), /*!< QSPI Clock control name.*/

    kCLOCK_RootI2c1 = (uint32_t)(&(CCM)->ROOT[90].TARGET_ROOT), /*!< I2C1 Clock control name.*/
    kCLOCK_RootI2c2 = (uint32_t)(&(CCM)->ROOT[91].TARGET_ROOT), /*!< I2C2 Clock control name.*/
    kCLOCK_RootI2c3 = (uint32_t)(&(CCM)->ROOT[92].TARGET_ROOT), /*!< I2C3 Clock control name.*/
    kCLOCK_RootI2c4 = (uint32_t)(&(CCM)->ROOT[93].TARGET_ROOT), /*!< I2C4 Clock control name.*/

    kCLOCK_RootUart1 = (uint32_t)(&(CCM)->ROOT[94].TARGET_ROOT), /*!< UART1 Clock control name.*/
    kCLOCK_RootUart2 = (uint32_t)(&(CCM)->ROOT[95].TARGET_ROOT), /*!< UART2 Clock control name.*/
    kCLOCK_RootUart3 = (uint32_t)(&(CCM)->ROOT[96].TARGET_ROOT), /*!< UART3 Clock control name.*/
    kCLOCK_RootUart4 = (uint32_t)(&(CCM)->ROOT[97].TARGET_ROOT), /*!< UART4 Clock control name.*/

    kCLOCK_RootEcspi1 = (uint32_t)(&(CCM)->ROOT[101].TARGET_ROOT), /*!< ECSPI1 Clock control name.*/
    kCLOCK_RootEcspi2 = (uint32_t)(&(CCM)->ROOT[102].TARGET_ROOT), /*!< ECSPI2 Clock control name.*/
    kCLOCK_RootEcspi3 = (uint32_t)(&(CCM)->ROOT[131].TARGET_ROOT), /*!< ECSPI3 Clock control name.*/

    kCLOCK_RootPwm1 = (uint32_t)(&(CCM)->ROOT[103].TARGET_ROOT), /*!< PWM1 Clock control name.*/
    kCLOCK_RootPwm2 = (uint32_t)(&(CCM)->ROOT[104].TARGET_ROOT), /*!< PWM2 Clock control name.*/
    kCLOCK_RootPwm3 = (uint32_t)(&(CCM)->ROOT[105].TARGET_ROOT), /*!< PWM3 Clock control name.*/
    kCLOCK_RootPwm4 = (uint32_t)(&(CCM)->ROOT[106].TARGET_ROOT), /*!< PWM4 Clock control name.*/

    kCLOCK_RootGpt1 = (uint32_t)(&(CCM)->ROOT[107].TARGET_ROOT), /*!< GPT1 Clock control name.*/
    kCLOCK_RootGpt2 = (uint32_t)(&(CCM)->ROOT[108].TARGET_ROOT), /*!< GPT2 Clock control name.*/
    kCLOCK_RootGpt3 = (uint32_t)(&(CCM)->ROOT[109].TARGET_ROOT), /*!< GPT3 Clock control name.*/
    kCLOCK_RootGpt4 = (uint32_t)(&(CCM)->ROOT[110].TARGET_ROOT), /*!< GPT4 Clock control name.*/
    kCLOCK_RootGpt5 = (uint32_t)(&(CCM)->ROOT[111].TARGET_ROOT), /*!< GPT5 Clock control name.*/
    kCLOCK_RootGpt6 = (uint32_t)(&(CCM)->ROOT[112].TARGET_ROOT), /*!< GPT6 Clock control name.*/

    kCLOCK_RootWdog = (uint32_t)(&(CCM)->ROOT[114].TARGET_ROOT), /*!< WDOG Clock control name.*/
} clock_root_control_t;

/*! @brief Root clock select enumeration for ARM Cortex-M4 core. */
typedef enum _clock_rootmux_m4_clk_sel
{
    kCLOCK_M4RootmuxOsc25m      = 0U, /*!< ARM Cortex-M4 Clock from OSC 25M.*/
    kCLOCK_M4RootmuxSysPll2Div5 = 1U, /*!< ARM Cortex-M4 Clock from SYSTEM PLL2 divided by 5.*/
    kCLOCK_M4RootmuxSysPll2Div4 = 2U, /*!< ARM Cortex-M4 Clock from SYSTEM PLL2 divided by 4.*/
    kCLOCK_M4RootmuxSysPll1Div3 = 3U, /*!< ARM Cortex-M4 Clock from SYSTEM PLL1 divided by 3.*/
    kCLOCK_M4RootmuxSysPll1     = 4U, /*!< ARM Cortex-M4 Clock from SYSTEM PLL1.*/
    kCLOCK_M4RootmuxAudioPll1   = 5U, /*!< ARM Cortex-M4 Clock from AUDIO PLL1.*/
    kCLOCK_M4RootmuxVideoPll1   = 6U, /*!< ARM Cortex-M4 Clock from VIDEO PLL1.*/
    kCLOCK_M4RootmuxSysPll3     = 7U, /*!< ARM Cortex-M4 Clock from SYSTEM PLL3.*/
} clock_rootmux_m4_clk_sel_t;

/*! @brief Root clock select enumeration for AXI bus. */
typedef enum _clock_rootmux_axi_clk_sel
{
    kCLOCK_AxiRootmuxOsc25m      = 0U, /*!< ARM AXI Clock from OSC 25M.*/
    kCLOCK_AxiRootmuxSysPll2Div3 = 1U, /*!< ARM AXI Clock from SYSTEM PLL2 divided by 3.*/
    kCLOCK_AxiRootmuxSysPll1     = 2U, /*!< ARM AXI Clock from SYSTEM PLL1.*/
    kCLOCK_AxiRootmuxSysPll2Div4 = 3U, /*!< ARM AXI Clock from SYSTEM PLL2 divided by 4.*/
    kCLOCK_AxiRootmuxSysPll2     = 4U, /*!< ARM AXI Clock from SYSTEM PLL2.*/
    kCLOCK_AxiRootmuxAudioPll1   = 5U, /*!< ARM AXI Clock from AUDIO PLL1.*/
    kCLOCK_AxiRootmuxVideoPll1   = 6U, /*!< ARM AXI Clock from VIDEO PLL1.*/
    kCLOCK_AxiRootmuxSysPll1Div8 = 7U, /*!< ARM AXI Clock from SYSTEM PLL1 divided by 8.*/
} clock_rootmux_axi_clk_sel_t;

/*! @brief Root clock select enumeration for AHB bus. */
typedef enum _clock_rootmux_ahb_clk_sel
{
    kCLOCK_AhbRootmuxOsc25m      = 0U, /*!< ARM AHB Clock from OSC 25M.*/
    kCLOCK_AhbRootmuxSysPll1Div6 = 1U, /*!< ARM AHB Clock from SYSTEM PLL1 divided by 6.*/
    kCLOCK_AhbRootmuxSysPll1     = 2U, /*!< ARM AHB Clock from SYSTEM PLL1.*/
    kCLOCK_AhbRootmuxSysPll1Div2 = 3U, /*!< ARM AHB Clock from SYSTEM PLL1 divided by 2.*/
    kCLOCK_AhbRootmuxSysPll2Div8 = 4U, /*!< ARM AHB Clock from SYSTEM PLL2 divided by 8.*/
    kCLOCK_AhbRootmuxSysPll3     = 5U, /*!< ARM AHB Clock from SYSTEM PLL3.*/
    kCLOCK_AhbRootmuxAudioPll1   = 6U, /*!< ARM AHB Clock from AUDIO PLL1.*/
    kCLOCK_AhbRootmuxVideoPll1   = 7U, /*!< ARM AHB Clock from VIDEO PLL1.*/
} clock_rootmux_ahb_clk_sel_t;

/*! @brief Root clock select enumeration for QSPI peripheral. */
typedef enum _clock_rootmux_qspi_clk_sel
{
    kCLOCK_QspiRootmuxOsc25m      = 0U, /*!< ARM QSPI Clock from OSC 25M.*/
    kCLOCK_QspiRootmuxSysPll1Div2 = 1U, /*!< ARM QSPI Clock from SYSTEM PLL1 divided by 2.*/
    kCLOCK_QspiRootmuxSysPll1     = 2U, /*!< ARM QSPI Clock from SYSTEM PLL1.*/
    kCLOCK_QspiRootmuxSysPll2Div2 = 3U, /*!< ARM QSPI Clock from SYSTEM PLL2 divided by 2.*/
    kCLOCK_QspiRootmuxAudioPll2   = 4,  /*!< ARM QSPI Clock from AUDIO PLL2.*/
    kCLOCK_QspiRootmuxSysPll1Div3 = 5U, /*!< ARM QSPI Clock from SYSTEM PLL1 divided by 3 */
    kCLOCK_QspiRootmuxSysPll3     = 6U, /*!< ARM QSPI Clock from SYSTEM PLL3.*/
    kCLOCK_QspiRootmuxSysPll1Div8 = 7U, /*!< ARM QSPI Clock from SYSTEM PLL1 divided by 8.*/
} clock_rootmux_qspi_clk_sel_t;

/*! @brief Root clock select enumeration for ECSPI peripheral. */
typedef enum _clock_rootmux_ecspi_clk_sel
{
    kCLOCK_EcspiRootmuxOsc25m       = 0U, /*!< ECSPI Clock from OSC 25M.*/
    kCLOCK_EcspiRootmuxSysPll2Div5  = 1U, /*!< ECSPI Clock from SYSTEM PLL2 divided by 5.*/
    kCLOCK_EcspiRootmuxSysPll1Div20 = 2U, /*!< ECSPI Clock from SYSTEM PLL1 divided by 20.*/
    kCLOCK_EcspiRootmuxSysPll1Div5  = 3U, /*!< ECSPI Clock from SYSTEM PLL1 divided by 5.*/
    kCLOCK_EcspiRootmuxSysPll1      = 4U, /*!< ECSPI Clock from SYSTEM PLL1.*/
    kCLOCK_EcspiRootmuxSysPll3      = 5U, /*!< ECSPI Clock from SYSTEM PLL3.*/
    kCLOCK_EcspiRootmuxSysPll2Div4  = 6U, /*!< ECSPI Clock from SYSTEM PLL2 divided by 4.*/
    kCLOCK_EcspiRootmuxAudioPll2    = 7U, /*!< ECSPI Clock from AUDIO PLL2.*/
} clock_rootmux_ecspi_clk_sel_t;

/*! @brief Root clock select enumeration for I2C peripheral. */
typedef enum _clock_rootmux_i2c_clk_sel
{
    kCLOCK_I2cRootmuxOsc25m       = 0U, /*!< I2C Clock from OSC 25M.*/
    kCLOCK_I2cRootmuxSysPll1Div5  = 1U, /*!< I2C Clock from SYSTEM PLL1 divided by 5.*/
    kCLOCK_I2cRootmuxSysPll2Div20 = 2U, /*!< I2C Clock from SYSTEM PLL2 divided by 20.*/
    kCLOCK_I2cRootmuxSysPll3      = 3U, /*!< I2C Clock from SYSTEM PLL3 .*/
    kCLOCK_I2cRootmuxAudioPll1    = 4U, /*!< I2C Clock from AUDIO PLL1.*/
    kCLOCK_I2cRootmuxVideoPll1    = 5U, /*!< I2C Clock from VIDEO PLL1.*/
    kCLOCK_I2cRootmuxAudioPll2    = 6U, /*!< I2C Clock from AUDIO PLL2.*/
    kCLOCK_I2cRootmuxSysPll1Div6  = 7U, /*!< I2C Clock from SYSTEM PLL1 divided by 6.*/
} clock_rootmux_i2c_clk_sel_t;

/*! @brief Root clock select enumeration for UART peripheral. */
typedef enum _clock_rootmux_uart_clk_sel
{
    kCLOCK_UartRootmuxOsc25m       = 0U, /*!< UART Clock from OSC 25M.*/
    kCLOCK_UartRootmuxSysPll1Div10 = 1U, /*!< UART Clock from SYSTEM PLL1 divided by 10.*/
    kCLOCK_UartRootmuxSysPll2Div5  = 2U, /*!< UART Clock from SYSTEM PLL2 divided by 5.*/
    kCLOCK_UartRootmuxSysPll2Div10 = 3U, /*!< UART Clock from SYSTEM PLL2 divided by 10.*/
    kCLOCK_UartRootmuxSysPll3      = 4U, /*!< UART Clock from SYSTEM PLL3.*/
    kCLOCK_UartRootmuxExtClk2      = 5U, /*!< UART Clock from External Clock 2.*/
    kCLOCK_UartRootmuxExtClk34     = 6U, /*!< UART Clock from External Clock 3, External Clock 4.*/
    kCLOCK_UartRootmuxAudioPll2    = 7U, /*!< UART Clock from Audio PLL2.*/
} clock_rootmux_uart_clk_sel_t;

/*! @brief Root clock select enumeration for GPT peripheral. */
typedef enum _clock_rootmux_gpt
{
    kCLOCK_GptRootmuxOsc25m          = 0U, /*!< GPT Clock from OSC 25M.*/
    kCLOCK_GptRootmuxSystemPll2Div10 = 1U, /*!< GPT Clock from SYSTEM PLL2 divided by 10.*/
    kCLOCK_GptRootmuxSysPll1Div2     = 2U, /*!< GPT Clock from SYSTEM PLL1 divided by 2.*/
    kCLOCK_GptRootmuxSysPll1Div20    = 3U, /*!< GPT Clock from SYSTEM PLL1 divided by 20.*/
    kCLOCK_GptRootmuxVideoPll1       = 4U, /*!< GPT Clock from VIDEO PLL1.*/
    kCLOCK_GptRootmuxSystemPll1Div10 = 5U, /*!< GPT Clock from SYSTEM PLL1 divided by 10.*/
    kCLOCK_GptRootmuxAudioPll1       = 6U, /*!< GPT Clock from AUDIO PLL1.*/
    kCLOCK_GptRootmuxExtClk123       = 7U, /*!< GPT Clock from External Clock1, External Clock2, External Clock3.*/
} clock_rootmux_gpt_t;

/*! @brief Root clock select enumeration for WDOG peripheral. */
typedef enum _clock_rootmux_wdog_clk_sel
{
    kCLOCK_WdogRootmuxOsc25m          = 0U, /*!< WDOG Clock from OSC 25M.*/
    kCLOCK_WdogRootmuxSysPll1Div6     = 1U, /*!< WDOG Clock from SYSTEM PLL1 divided by 6.*/
    kCLOCK_WdogRootmuxSysPll1Div5     = 2U, /*!< WDOG Clock from SYSTEM PLL1 divided by 5.*/
    kCLOCK_WdogRootmuxVpuPll          = 3U, /*!< WDOG Clock from VPU DLL.*/
    kCLOCK_WdogRootmuxSystemPll2Div8  = 4U, /*!< WDOG Clock from SYSTEM PLL2 divided by 8.*/
    kCLOCK_WdogRootmuxSystemPll3      = 5U, /*!< WDOG Clock from SYSTEM PLL3.*/
    kCLOCK_WdogRootmuxSystemPll1Div10 = 6U, /*!< WDOG Clock from SYSTEM PLL1 divided by 10.*/
    kCLOCK_WdogRootmuxSystemPll2Div6  = 7U, /*!< WDOG Clock from SYSTEM PLL2 divided by 6.*/
} clock_rootmux_wdog_clk_sel_t;

/*! @brief Root clock select enumeration for PWM peripheral. */
typedef enum _clock_rootmux_pwm_clk_sel
{
    kCLOCK_PwmRootmuxOsc25m          = 0U, /*!< PWM Clock from OSC 25M.*/
    kCLOCK_PwmRootmuxSysPll2Div10    = 1U, /*!< PWM Clock from SYSTEM PLL2 divided by 10.*/
    kCLOCK_PwmRootmuxSysPll1Div5     = 2U, /*!< PWM Clock from SYSTEM PLL1 divided by 5.*/
    kCLOCK_PwmRootmuxSysPll1Div20    = 3U, /*!< PWM Clock from SYSTEM PLL1 divided by 20.*/
    kCLOCK_PwmRootmuxSystemPll3      = 4U, /*!< PWM Clock from SYSTEM PLL3.*/
    kCLOCK_PwmRootmuxExtClk12        = 5U, /*!< PWM Clock from External Clock1, External Clock2.*/
    kCLOCK_PwmRootmuxSystemPll1Div10 = 6U, /*!< PWM Clock from SYSTEM PLL1 divided by 10.*/
    kCLOCK_PwmRootmuxVideoPll1       = 7U, /*!< PWM Clock from VIDEO PLL1.*/
} clock_rootmux_Pwm_clk_sel_t;

/*! @brief Root clock select enumeration for SAI peripheral. */
typedef enum _clock_rootmux_sai_clk_sel
{
    kCLOCK_SaiRootmuxOsc25m      = 0U, /*!< SAI Clock from OSC 25M.*/
    kCLOCK_SaiRootmuxAudioPll1   = 1U, /*!< SAI Clock from AUDIO PLL1.*/
    kCLOCK_SaiRootmuxAudioPll2   = 2U, /*!< SAI Clock from AUDIO PLL2.*/
    kCLOCK_SaiRootmuxVideoPll1   = 3U, /*!< SAI Clock from VIDEO PLL1.*/
    kCLOCK_SaiRootmuxSysPll1Div6 = 4U, /*!< SAI Clock from SYSTEM PLL1 divided by 6.*/
    kCLOCK_SaiRootmuxOsc27m      = 5U, /*!< SAI Clock from OSC 27M.*/
    kCLOCK_SaiRootmuxExtClk123   = 6U, /*!< SAI Clock from External Clock1, External Clock2, External Clock3.*/
    kCLOCK_SaiRootmuxExtClk234   = 7U, /*!< SAI Clock from External Clock2, External Clock3, External Clock4.*/
} clock_rootmux_sai_clk_sel_t;

/*! @brief Root clock select enumeration for NOC CLK. */
typedef enum _clock_rootmux_noc_clk_sel
{
    kCLOCK_NocRootmuxOsc25m      = 0U, /*!< NOC Clock from OSC 25M.*/
    kCLOCK_NocRootmuxSysPll1     = 1U, /*!< NOC Clock from SYSTEM PLL1.*/
    kCLOCK_NocRootmuxSysPll3     = 2U, /*!< NOC Clock from SYSTEM PLL3.*/
    kCLOCK_NocRootmuxSysPll2     = 3U, /*!< NOC Clock from SYSTEM PLL2.*/
    kCLOCK_NocRootmuxSysPll2Div2 = 4U, /*!< NOC Clock from SYSTEM PLL2 divided by 2.*/
    kCLOCK_NocRootmuxAudioPll1   = 5U, /*!< NOC Clock from AUDIO PLL1.*/
    kCLOCK_NocRootmuxVideoPll1   = 6U, /*!< NOC Clock from VIDEO PLL1.*/
    kCLOCK_NocRootmuxAudioPll2   = 7U, /*!< NOC Clock from AUDIO PLL2.*/

} clock_rootmux_noc_clk_sel_t;

/*! @brief CCM PLL gate control. */
typedef enum _clock_pll_gate
{
    kCLOCK_ArmPllGate = (uint32_t)(&(CCM)->PLL_CTRL[12].PLL_CTRL), /*!< ARM PLL Gate.*/

    kCLOCK_GpuPllGate  = (uint32_t)(&(CCM)->PLL_CTRL[13].PLL_CTRL), /*!< GPU PLL Gate.*/
    kCLOCK_VpuPllGate  = (uint32_t)(&(CCM)->PLL_CTRL[14].PLL_CTRL), /*!< VPU PLL Gate.*/
    kCLOCK_DramPllGate = (uint32_t)(&(CCM)->PLL_CTRL[15].PLL_CTRL), /*!< DRAM PLL1 Gate.*/

    kCLOCK_SysPll1Gate      = (uint32_t)(&(CCM)->PLL_CTRL[16].PLL_CTRL), /*!< SYSTEM PLL1 Gate.*/
    kCLOCK_SysPll1Div2Gate  = (uint32_t)(&(CCM)->PLL_CTRL[17].PLL_CTRL), /*!< SYSTEM PLL1 Div2 Gate.*/
    kCLOCK_SysPll1Div3Gate  = (uint32_t)(&(CCM)->PLL_CTRL[18].PLL_CTRL), /*!< SYSTEM PLL1 Div3 Gate.*/
    kCLOCK_SysPll1Div4Gate  = (uint32_t)(&(CCM)->PLL_CTRL[19].PLL_CTRL), /*!< SYSTEM PLL1 Div4 Gate.*/
    kCLOCK_SysPll1Div5Gate  = (uint32_t)(&(CCM)->PLL_CTRL[20].PLL_CTRL), /*!< SYSTEM PLL1 Div5 Gate.*/
    kCLOCK_SysPll1Div6Gate  = (uint32_t)(&(CCM)->PLL_CTRL[21].PLL_CTRL), /*!< SYSTEM PLL1 Div6 Gate.*/
    kCLOCK_SysPll1Div8Gate  = (uint32_t)(&(CCM)->PLL_CTRL[22].PLL_CTRL), /*!< SYSTEM PLL1 Div8 Gate.*/
    kCLOCK_SysPll1Div10Gate = (uint32_t)(&(CCM)->PLL_CTRL[23].PLL_CTRL), /*!< SYSTEM PLL1 Div10 Gate.*/
    kCLOCK_SysPll1Div20Gate = (uint32_t)(&(CCM)->PLL_CTRL[24].PLL_CTRL), /*!< SYSTEM PLL1 Div20 Gate.*/

    kCLOCK_SysPll2Gate      = (uint32_t)(&(CCM)->PLL_CTRL[25].PLL_CTRL), /*!< SYSTEM PLL2 Gate.*/
    kCLOCK_SysPll2Div2Gate  = (uint32_t)(&(CCM)->PLL_CTRL[26].PLL_CTRL), /*!< SYSTEM PLL2 Div2 Gate.*/
    kCLOCK_SysPll2Div3Gate  = (uint32_t)(&(CCM)->PLL_CTRL[27].PLL_CTRL), /*!< SYSTEM PLL2 Div3 Gate.*/
    kCLOCK_SysPll2Div4Gate  = (uint32_t)(&(CCM)->PLL_CTRL[28].PLL_CTRL), /*!< SYSTEM PLL2 Div4 Gate.*/
    kCLOCK_SysPll2Div5Gate  = (uint32_t)(&(CCM)->PLL_CTRL[29].PLL_CTRL), /*!< SYSTEM PLL2 Div5 Gate.*/
    kCLOCK_SysPll2Div6Gate  = (uint32_t)(&(CCM)->PLL_CTRL[30].PLL_CTRL), /*!< SYSTEM PLL2 Div6 Gate.*/
    kCLOCK_SysPll2Div8Gate  = (uint32_t)(&(CCM)->PLL_CTRL[31].PLL_CTRL), /*!< SYSTEM PLL2 Div8 Gate.*/
    kCLOCK_SysPll2Div10Gate = (uint32_t)(&(CCM)->PLL_CTRL[32].PLL_CTRL), /*!< SYSTEM PLL2 Div10 Gate.*/
    kCLOCK_SysPll2Div20Gate = (uint32_t)(&(CCM)->PLL_CTRL[33].PLL_CTRL), /*!< SYSTEM PLL2 Div20 Gate.*/

    kCLOCK_SysPll3Gate = (uint32_t)(&(CCM)->PLL_CTRL[34].PLL_CTRL), /*!< SYSTEM PLL3 Gate.*/

    kCLOCK_AudioPll1Gate = (uint32_t)(&(CCM)->PLL_CTRL[35].PLL_CTRL), /*!< AUDIO PLL1 Gate.*/
    kCLOCK_AudioPll2Gate = (uint32_t)(&(CCM)->PLL_CTRL[36].PLL_CTRL), /*!< AUDIO PLL2 Gate.*/
    kCLOCK_VideoPll1Gate = (uint32_t)(&(CCM)->PLL_CTRL[37].PLL_CTRL), /*!< VIDEO PLL1 Gate.*/
    kCLOCK_VideoPll2Gate = (uint32_t)(&(CCM)->PLL_CTRL[38].PLL_CTRL), /*!< VIDEO PLL2 Gate.*/
} clock_pll_gate_t;

/*! @brief CCM gate control value. */
typedef enum _clock_gate_value
{
    kCLOCK_ClockNotNeeded     = 0x0U,    /*!< Clock always disabled.*/
    kCLOCK_ClockNeededRun     = 0x1111U, /*!< Clock enabled when CPU is running.*/
    kCLOCK_ClockNeededRunWait = 0x2222U, /*!< Clock enabled when CPU is running or in WAIT mode.*/
    kCLOCK_ClockNeededAll     = 0x3333U, /*!< Clock always enabled.*/
} clock_gate_value_t;

/*!
 * @brief PLL control names for PLL bypass.
 *
 * These constants define the PLL control names for PLL bypass.\n
 * - 0:15: REG offset to CCM_ANALOG_BASE in bytes.
 * - 16:20: bypass bit shift.
 */
typedef enum _clock_pll_bypass_ctrl
{
    kCLOCK_AudioPll1BypassCtrl = CCM_ANALOG_TUPLE(
        AUDIO_PLL1_CFG0_OFFSET, CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_BYPASS_SHIFT), /*!< CCM Audio PLL1 bypass Control.*/
    kCLOCK_AudioPll2BypassCtrl = CCM_ANALOG_TUPLE(
        AUDIO_PLL2_CFG0_OFFSET, CCM_ANALOG_AUDIO_PLL2_CFG0_PLL_BYPASS_SHIFT), /*!< CCM Audio PLL2 bypass Control.*/
    kCLOCK_VideoPll1BypassCtrl = CCM_ANALOG_TUPLE(
        VIDEO_PLL1_CFG0_OFFSET, CCM_ANALOG_VIDEO_PLL1_CFG0_PLL_BYPASS_SHIFT), /*!< CCM Video Pll1 bypass Control.*/
    kCLOCK_GpuPLLPwrBypassCtrl = CCM_ANALOG_TUPLE(
        GPU_PLL_CFG0_OFFSET, CCM_ANALOG_GPU_PLL_CFG0_PLL_BYPASS_SHIFT), /*!< CCM Gpu PLL bypass Control.*/
    kCLOCK_VpuPllPwrBypassCtrl = CCM_ANALOG_TUPLE(
        VPU_PLL_CFG0_OFFSET, CCM_ANALOG_VPU_PLL_CFG0_PLL_BYPASS_SHIFT), /*!< CCM Vpu PLL bypass Control.*/
    kCLOCK_ArmPllPwrBypassCtrl = CCM_ANALOG_TUPLE(
        ARM_PLL_CFG0_OFFSET, CCM_ANALOG_ARM_PLL_CFG0_PLL_BYPASS_SHIFT), /*!< CCM Arm PLL bypass Control.*/

    kCLOCK_SysPll1InternalPll1BypassCtrl = CCM_ANALOG_TUPLE(
        SYS_PLL1_CFG0_OFFSET,
        CCM_ANALOG_SYS_PLL1_CFG0_PLL_BYPASS1_SHIFT), /*!< CCM System PLL1 internal pll1 bypass Control.*/
    kCLOCK_SysPll1InternalPll2BypassCtrl = CCM_ANALOG_TUPLE(
        SYS_PLL1_CFG0_OFFSET,
        CCM_ANALOG_SYS_PLL1_CFG0_PLL_BYPASS2_SHIFT), /*!< CCM System PLL1 internal pll2 bypass Control.*/

    kCLOCK_SysPll2InternalPll1BypassCtrl = CCM_ANALOG_TUPLE(
        SYS_PLL2_CFG0_OFFSET,
        CCM_ANALOG_SYS_PLL2_CFG0_PLL_BYPASS1_SHIFT), /*!< CCM Analog System PLL1 internal pll1 bypass Control.*/
    kCLOCK_SysPll2InternalPll2BypassCtrl = CCM_ANALOG_TUPLE(
        SYS_PLL2_CFG0_OFFSET,
        CCM_ANALOG_SYS_PLL2_CFG0_PLL_BYPASS2_SHIFT), /*!< CCM Analog VIDEO System PLL1 internal pll1 bypass Control.*/

    kCLOCK_SysPll3InternalPll1BypassCtrl = CCM_ANALOG_TUPLE(
        SYS_PLL3_CFG0_OFFSET, CCM_ANALOG_SYS_PLL3_CFG0_PLL_BYPASS1_SHIFT), /*!< CCM Analog VIDEO PLL bypass Control.*/
    kCLOCK_SysPll3InternalPll2BypassCtrl = CCM_ANALOG_TUPLE(
        SYS_PLL3_CFG0_OFFSET, CCM_ANALOG_SYS_PLL3_CFG0_PLL_BYPASS2_SHIFT), /*!< CCM Analog VIDEO PLL bypass Control.*/

    kCLOCK_VideoPll2InternalPll1BypassCtrl =
        CCM_ANALOG_TUPLE(VIDEO_PLL2_CFG0_OFFSET,
                         CCM_ANALOG_VIDEO_PLL2_CFG0_PLL_BYPASS1_SHIFT), /*!< CCM Analog 480M PLL bypass Control.*/
    kCLOCK_VideoPll2InternalPll2BypassCtrl =
        CCM_ANALOG_TUPLE(VIDEO_PLL2_CFG0_OFFSET,
                         CCM_ANALOG_VIDEO_PLL2_CFG0_PLL_BYPASS2_SHIFT), /*!< CCM Analog 480M PLL bypass Control.*/

    kCLOCK_DramPllInternalPll1BypassCtrl = CCM_ANALOG_TUPLE(
        DRAM_PLL_CFG0_OFFSET, CCM_ANALOG_DRAM_PLL_CFG0_PLL_BYPASS1_SHIFT), /*!< CCM Analog 480M PLL bypass Control.*/
    kCLOCK_DramPllInternalPll2BypassCtrl = CCM_ANALOG_TUPLE(
        DRAM_PLL_CFG0_OFFSET, CCM_ANALOG_DRAM_PLL_CFG0_PLL_BYPASS2_SHIFT), /*!< CCM Analog 480M PLL bypass Control.*/
} clock_pll_bypass_ctrl_t;

/*!
 * @brief PLL clock names for clock enable/disable settings.
 *
 * These constants define the PLL clock names for PLL clock enable/disable operations.\n
 * - 0:15: REG offset to CCM_ANALOG_BASE in bytes.
 * - 16:20: Clock enable bit shift.
 */
typedef enum _ccm_analog_pll_clke
{
    kCLOCK_AudioPll1Clke =
        CCM_ANALOG_TUPLE(AUDIO_PLL1_CFG0_OFFSET, CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_CLKE_SHIFT), /*!< Audio pll1 clke */
    kCLOCK_AudioPll2Clke =
        CCM_ANALOG_TUPLE(AUDIO_PLL2_CFG0_OFFSET, CCM_ANALOG_AUDIO_PLL2_CFG0_PLL_CLKE_SHIFT), /*!< Audio pll2 clke */
    kCLOCK_VideoPll1Clke =
        CCM_ANALOG_TUPLE(VIDEO_PLL1_CFG0_OFFSET, CCM_ANALOG_VIDEO_PLL1_CFG0_PLL_CLKE_SHIFT), /*!< Video pll1 clke */
    kCLOCK_GpuPllClke =
        CCM_ANALOG_TUPLE(GPU_PLL_CFG0_OFFSET, CCM_ANALOG_GPU_PLL_CFG0_PLL_CLKE_SHIFT), /*!< Gpu pll clke */
    kCLOCK_VpuPllClke =
        CCM_ANALOG_TUPLE(VPU_PLL_CFG0_OFFSET, CCM_ANALOG_VPU_PLL_CFG0_PLL_CLKE_SHIFT), /*!< Vpu pll clke */
    kCLOCK_ArmPllClke =
        CCM_ANALOG_TUPLE(ARM_PLL_CFG0_OFFSET, CCM_ANALOG_ARM_PLL_CFG0_PLL_CLKE_SHIFT), /*!< Arm pll clke */

    kCLOCK_SystemPll1Clke =
        CCM_ANALOG_TUPLE(SYS_PLL1_CFG0_OFFSET, CCM_ANALOG_SYS_PLL1_CFG0_PLL_CLKE_SHIFT), /*!< System pll1 clke */
    kCLOCK_SystemPll1Div2Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_CFG0_OFFSET, CCM_ANALOG_SYS_PLL1_CFG0_PLL_DIV2_CLKE_SHIFT), /*!< System pll1 Div2 clke */
    kCLOCK_SystemPll1Div3Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_CFG0_OFFSET, CCM_ANALOG_SYS_PLL1_CFG0_PLL_DIV3_CLKE_SHIFT), /*!< System pll1 Div3 clke */
    kCLOCK_SystemPll1Div4Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_CFG0_OFFSET, CCM_ANALOG_SYS_PLL1_CFG0_PLL_DIV4_CLKE_SHIFT), /*!< System pll1 Div4 clke */
    kCLOCK_SystemPll1Div5Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_CFG0_OFFSET, CCM_ANALOG_SYS_PLL1_CFG0_PLL_DIV5_CLKE_SHIFT), /*!< System pll1 Div5 clke */
    kCLOCK_SystemPll1Div6Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_CFG0_OFFSET, CCM_ANALOG_SYS_PLL1_CFG0_PLL_DIV6_CLKE_SHIFT), /*!< System pll1 Div6 clke */
    kCLOCK_SystemPll1Div8Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_CFG0_OFFSET, CCM_ANALOG_SYS_PLL1_CFG0_PLL_DIV8_CLKE_SHIFT), /*!< System pll1 Div8 clke */
    kCLOCK_SystemPll1Div10Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_CFG0_OFFSET, CCM_ANALOG_SYS_PLL1_CFG0_PLL_DIV10_CLKE_SHIFT), /*!< System pll1 Div10 clke */
    kCLOCK_SystemPll1Div20Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_CFG0_OFFSET, CCM_ANALOG_SYS_PLL1_CFG0_PLL_DIV20_CLKE_SHIFT), /*!< System pll1 Div20 clke */

    kCLOCK_SystemPll2Clke =
        CCM_ANALOG_TUPLE(SYS_PLL2_CFG0_OFFSET, CCM_ANALOG_SYS_PLL2_CFG0_PLL_CLKE_SHIFT), /*!< System pll2 clke */
    kCLOCK_SystemPll2Div2Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_CFG0_OFFSET, CCM_ANALOG_SYS_PLL2_CFG0_PLL_DIV2_CLKE_SHIFT), /*!< System pll2 Div2 clke */
    kCLOCK_SystemPll2Div3Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_CFG0_OFFSET, CCM_ANALOG_SYS_PLL2_CFG0_PLL_DIV3_CLKE_SHIFT), /*!< System pll2 Div3 clke */
    kCLOCK_SystemPll2Div4Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_CFG0_OFFSET, CCM_ANALOG_SYS_PLL2_CFG0_PLL_DIV4_CLKE_SHIFT), /*!< System pll2 Div4 clke */
    kCLOCK_SystemPll2Div5Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_CFG0_OFFSET, CCM_ANALOG_SYS_PLL2_CFG0_PLL_DIV5_CLKE_SHIFT), /*!< System pll2 Div5 clke */
    kCLOCK_SystemPll2Div6Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_CFG0_OFFSET, CCM_ANALOG_SYS_PLL2_CFG0_PLL_DIV6_CLKE_SHIFT), /*!< System pll2 Div6 clke */
    kCLOCK_SystemPll2Div8Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_CFG0_OFFSET, CCM_ANALOG_SYS_PLL2_CFG0_PLL_DIV8_CLKE_SHIFT), /*!< System pll2 Div8 clke */
    kCLOCK_SystemPll2Div10Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_CFG0_OFFSET, CCM_ANALOG_SYS_PLL2_CFG0_PLL_DIV10_CLKE_SHIFT), /*!< System pll2 Div10 clke */
    kCLOCK_SystemPll2Div20Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_CFG0_OFFSET, CCM_ANALOG_SYS_PLL2_CFG0_PLL_DIV20_CLKE_SHIFT), /*!< System pll2 Div20 clke */

    kCLOCK_SystemPll3Clke =
        CCM_ANALOG_TUPLE(SYS_PLL3_CFG0_OFFSET, CCM_ANALOG_SYS_PLL3_CFG0_PLL_CLKE_SHIFT), /*!< System pll3 clke */
    kCLOCK_VideoPll2Clke =
        CCM_ANALOG_TUPLE(VIDEO_PLL2_CFG0_OFFSET, CCM_ANALOG_VIDEO_PLL2_CFG0_PLL_CLKE_SHIFT), /*!< Video pll2 clke */
    kCLOCK_DramPllClke =
        CCM_ANALOG_TUPLE(DRAM_PLL_CFG0_OFFSET, CCM_ANALOG_DRAM_PLL_CFG0_PLL_CLKE_SHIFT), /*!< Dram pll clke */
    kCLOCK_OSC25MClke =
        CCM_ANALOG_TUPLE(OSC_MISC_CFG_OFFSET, CCM_ANALOG_OSC_MISC_CFG_OSC_25M_CLKE_SHIFT), /*!< OSC25M clke */
    kCLOCK_OSC27MClke =
        CCM_ANALOG_TUPLE(OSC_MISC_CFG_OFFSET, CCM_ANALOG_OSC_MISC_CFG_OSC_27M_CLKE_SHIFT), /*!< OSC27M clke */

} clock_pll_clke_t;

/*!
 * @brief ANALOG Power down override control.
 */
typedef enum _clock_pll_ctrl
{
    kCLOCK_AudioPll1Ctrl = CCM_ANALOG_TUPLE(AUDIO_PLL1_CFG0_OFFSET, CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_PD_SHIFT),
    kCLOCK_AudioPll2Ctrl = CCM_ANALOG_TUPLE(AUDIO_PLL2_CFG0_OFFSET, CCM_ANALOG_AUDIO_PLL2_CFG0_PLL_PD_SHIFT),
    kCLOCK_VideoPll1Ctrl = CCM_ANALOG_TUPLE(VIDEO_PLL1_CFG0_OFFSET, CCM_ANALOG_VIDEO_PLL1_CFG0_PLL_PD_SHIFT),
    kCLOCK_GpuPllCtrl    = CCM_ANALOG_TUPLE(GPU_PLL_CFG0_OFFSET, CCM_ANALOG_GPU_PLL_CFG0_PLL_PD_SHIFT),
    kCLOCK_VpuPllCtrl    = CCM_ANALOG_TUPLE(VPU_PLL_CFG0_OFFSET, CCM_ANALOG_VPU_PLL_CFG0_PLL_PD_SHIFT),
    kCLOCK_ArmPllCtrl    = CCM_ANALOG_TUPLE(ARM_PLL_CFG0_OFFSET, CCM_ANALOG_ARM_PLL_CFG0_PLL_PD_SHIFT),

    kCLOCK_SystemPll1Ctrl = CCM_ANALOG_TUPLE(SYS_PLL1_CFG0_OFFSET, CCM_ANALOG_SYS_PLL1_CFG0_PLL_PD_SHIFT),
    kCLOCK_SystemPll2Ctrl = CCM_ANALOG_TUPLE(SYS_PLL2_CFG0_OFFSET, CCM_ANALOG_SYS_PLL2_CFG0_PLL_PD_SHIFT),
    kCLOCK_SystemPll3Ctrl = CCM_ANALOG_TUPLE(SYS_PLL3_CFG0_OFFSET, CCM_ANALOG_SYS_PLL3_CFG0_PLL_PD_SHIFT),
    kCLOCK_VideoPll2Ctrl  = CCM_ANALOG_TUPLE(VIDEO_PLL2_CFG0_OFFSET, CCM_ANALOG_VIDEO_PLL2_CFG0_PLL_PD_SHIFT),
    kCLOCK_DramPllCtrl    = CCM_ANALOG_TUPLE(DRAM_PLL_CFG0_OFFSET, CCM_ANALOG_DRAM_PLL_CFG0_PLL_PD_SHIFT),

} clock_pll_ctrl_t;

/*! @brief OSC work mode. */
enum _osc_mode
{
    kOSC_OscMode = 0U, /*!< OSC oscillator mode */
    kOSC_ExtMode = 1U, /*!< OSC external mode */
};

/*! @brief OSC 32K input select. */
typedef enum _osc32_src
{
    kOSC32_Src25MDiv800 = 0U, /*!< source from 25M divide 800 */
    kOSC32_SrcRTC,            /*!< source from RTC */
} osc32_src_t;

/*! @brief PLL reference clock select. */
enum _ccm_analog_pll_ref_clk
{
    kANALOG_PllRefOsc25M        = 0U, /*!< reference OSC 25M */
    kANALOG_PllRefOsc27M        = 1U, /*!< reference OSC 27M */
    kANALOG_PllRefOscHdmiPhy27M = 2U, /*!< reference HDMI PHY 27M */
    kANALOG_PllRefClkPN         = 3U, /*!< reference CLK_P_N */
};

/*!
 * @brief OSC configuration structure.
 */
typedef struct _osc_config
{
    uint8_t oscMode; /*!< ext or osc mode */
    uint8_t oscDiv;  /*!< osc divider */
} osc_config_t;

/*!
 * @brief Fractional-N PLL configuration.
 * Note: all the dividers in this configuration structure are the actually divider, software will map it to register
 * value
 */
typedef struct _ccm_analog_frac_pll_config
{
    uint8_t refSel; /*!< pll reference clock sel */

    uint8_t refDiv; /*!< A 6bit divider to make sure the REF must be within the range 10MHZ~300MHZ */

    uint32_t fractionDiv; /*!< Inlcude fraction divider(divider:1:2^24)  output clock
                              range is 2000MHZ-4000MHZ  */
    uint8_t intDiv;       /*and integer divide(divider: 1:32)*/
    uint8_t outDiv;       /*!< output clock divide, output clock range is 30MHZ to 2000MHZ, must be a even value */

} ccm_analog_frac_pll_config_t;

/*!
 * @brief SSCG PLL configuration.
 * Note: all the dividers in this configuration structure are the actually divider, software will map it to register
 * value
 */
typedef struct _ccm_analog_sscg_pll_config
{
    uint8_t refSel; /*!< pll reference clock sel */

    uint8_t refDiv1; /*!< A 3bit divider to make sure the REF must be within the range 25MHZ~235MHZ ,post_divide REF
                         must be within the range 25MHZ~54MHZ */
    uint8_t refDiv2; /*!< A 6bit divider to make sure the post_divide REF must be within the range 54MHZ~75MHZ */

    uint32_t loopDivider1; /*!< A 6bit internal PLL1 feedback clock divider, output clock range must be within the range
                              1600MHZ-2400MHZ */
    uint32_t loopDivider2; /*!< A 6bit internal PLL2 feedback clock divider, output clock range must be within the range
                              1200MHZ-2400MHZ */

    uint8_t outDiv; /*!< A 6bit output clock divide, output clock range is 20MHZ to 1200MHZ */

} ccm_analog_sscg_pll_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name CCM Root Clock Setting
 * @{
 */

/*!
 * @brief Set clock root mux.
 * User maybe need to set more than one mux ROOT according to the clock tree
 * description in the reference manual.
 *
 * @param rootClk Root clock control (see @ref clock_root_control_t enumeration).
 * @param mux Root mux value (see _ccm_rootmux_xxx enumeration).
 */
static inline void CLOCK_SetRootMux(clock_root_control_t rootClk, uint32_t mux)
{
    CCM_REG(rootClk) = (CCM_REG(rootClk) & (~CCM_TARGET_ROOT_MUX_MASK)) | CCM_TARGET_ROOT_MUX(mux);
}

/*!
 * @brief Get clock root mux.
 * In order to get the clock source of root, user maybe need to get more than one
 * ROOT's mux value to obtain the final clock source of root.
 *
 * @param rootClk Root clock control (see @ref clock_root_control_t enumeration).
 * @return Root mux value (see _ccm_rootmux_xxx enumeration).
 */
static inline uint32_t CLOCK_GetRootMux(clock_root_control_t rootClk)
{
    return (CCM_REG(rootClk) & CCM_TARGET_ROOT_MUX_MASK) >> CCM_TARGET_ROOT_MUX_SHIFT;
}

/*!
 * @brief Enable clock root
 *
 * @param rootClk Root clock control (see @ref clock_root_control_t enumeration)
 */
static inline void CLOCK_EnableRoot(clock_root_control_t rootClk)
{
    CCM_REG_SET(rootClk) = CCM_TARGET_ROOT_SET_ENABLE_MASK;
}

/*!
 * @brief Disable clock root
 *
 * @param rootClk Root control (see @ref clock_root_control_t enumeration)
 */
static inline void CLOCK_DisableRoot(clock_root_control_t rootClk)
{
    CCM_REG_CLR(rootClk) = CCM_TARGET_ROOT_CLR_ENABLE_MASK;
}

/*!
 * @brief Check whether clock root is enabled
 *
 * @param rootClk Root control (see @ref clock_root_control_t enumeration)
 * @return CCM root enabled or not.
 *         - true: Clock root is enabled.
 *         - false: Clock root is disabled.
 */
static inline bool CLOCK_IsRootEnabled(clock_root_control_t rootClk)
{
    return (bool)(CCM_REG(rootClk) & CCM_TARGET_ROOT_ENABLE_MASK);
}

/*!
 * @brief Update clock root in one step, for dynamical clock switching
 * Note: The PRE and POST dividers in this function are the actually divider, software will map it to register value
 *
 * @param ccmRootClk Root control (see @ref clock_root_control_t enumeration)
 * @param mux root mux value (see _ccm_rootmux_xxx enumeration)
 * @param pre Pre divider value (0-7, divider=n+1)
 * @param post Post divider value (0-63, divider=n+1)
 */
void CLOCK_UpdateRoot(clock_root_control_t ccmRootClk, uint32_t mux, uint32_t pre, uint32_t post);

/*!
 * @brief Set root clock divider
 * Note: The PRE and POST dividers in this function are the actually divider, software will map it to register value
 *
 * @param ccmRootClk Root control (see @ref clock_root_control_t enumeration)
 * @param pre Pre divider value (1-8)
 * @param post Post divider value (1-64)
 */
void CLOCK_SetRootDivider(clock_root_control_t ccmRootClk, uint32_t pre, uint32_t post);

/*!
 * @brief Get clock root PRE_PODF.
 * In order to get the clock source of root, user maybe need to get more than one
 * ROOT's mux value to obtain the final clock source of root.
 *
 * @param rootClk Root clock name (see @ref clock_root_control_t enumeration).
 * @return Root Pre divider value.
 */
static inline uint32_t CLOCK_GetRootPreDivider(clock_root_control_t rootClk)
{
    return ((CCM_REG(rootClk) & CCM_TARGET_ROOT_PRE_PODF_MASK) >> CCM_TARGET_ROOT_PRE_PODF_SHIFT) + 1U;
}

/*!
 * @brief Get clock root POST_PODF.
 * In order to get the clock source of root, user maybe need to get more than one
 * ROOT's mux value to obtain the final clock source of root.
 *
 * @param rootClk Root clock name (see @ref clock_root_control_t enumeration).
 * @return Root Post divider value.
 */
static inline uint32_t CLOCK_GetRootPostDivider(clock_root_control_t rootClk)
{
    return ((CCM_REG(rootClk) & CCM_TARGET_ROOT_POST_PODF_MASK) >> CCM_TARGET_ROOT_POST_PODF_SHIFT) + 1U;
}

/*!
 * @name OSC setting
 * @{
 */
/*!
 * @brief OSC25M init
 *
 * @param config osc configuration.
 */
void CLOCK_InitOSC25M(const osc_config_t *config);

/*!
 * @brief OSC25M deinit
 *
 */
void CLOCK_DeinitOSC25M(void);

/*!
 * @brief OSC27M init
 * @param config osc configuration.
 *
 */
void CLOCK_InitOSC27M(const osc_config_t *config);

/*!
 * @brief OSC27M deinit
 *
 */
void CLOCK_DeinitOSC27M(void);

/*!
 * @brief switch 32KHZ OSC input
 * @param sel OSC32 input clock select
 */
static inline void CLOCK_SwitchOSC32Src(osc32_src_t sel)
{
    CCM_ANALOG->OSC_MISC_CFG = (CCM_ANALOG->OSC_MISC_CFG & (~CCM_ANALOG_OSC_MISC_CFG_OSC_32K_SEL_MASK)) | (uint32_t)sel;
}

/*!
 * @name CCM Gate Control
 * @{
 */

/*!
 * @brief Set PLL or CCGR gate control
 *
 * @param ccmGate Gate control (see @ref clock_pll_gate_t and @ref clock_ip_name_t enumeration)
 * @param control Gate control value (see @ref clock_gate_value_t)
 */
static inline void CLOCK_ControlGate(uint32_t ccmGate, clock_gate_value_t control)
{
    CCM_REG(ccmGate) = (uint32_t)control;
}

/*!
 * @brief Enable CCGR clock gate and root clock gate for each module
 * User should set specific gate for each module according to the description
 * of the table of system clocks, gating and override in CCM chapter of
 * reference manual. Take care of that one module may need to set more than
 * one clock gate.
 *
 * @param ccmGate Gate control for each module (see @ref clock_ip_name_t enumeration).
 */
void CLOCK_EnableClock(clock_ip_name_t ccmGate);

/*!
 * @brief Disable CCGR clock gate for the each module
 * User should set specific gate for each module according to the description
 * of the table of system clocks, gating and override in CCM chapter of
 * reference manual. Take care of that one module may need to set more than
 * one clock gate.
 *
 * @param ccmGate Gate control for each module (see @ref clock_ip_name_t enumeration).
 */
void CLOCK_DisableClock(clock_ip_name_t ccmGate);

/*!
 * @name CCM Analog PLL Operatoin Functions
 * @{
 */

/*!
 * @brief Power up PLL
 *
 * @param base CCM_ANALOG base pointer.
 * @param pllControl PLL control name (see @ref clock_pll_ctrl_t enumeration)
 */
static inline void CLOCK_PowerUpPll(CCM_ANALOG_Type *base, clock_pll_ctrl_t pllControl)
{
    CCM_ANALOG_TUPLE_REG(base, pllControl) &= ~(1UL << CCM_ANALOG_TUPLE_SHIFT(pllControl));
}

/*!
 * @brief Power down PLL
 *
 * @param base CCM_ANALOG base pointer.
 * @param pllControl PLL control name (see @ref clock_pll_ctrl_t enumeration)
 */
static inline void CLOCK_PowerDownPll(CCM_ANALOG_Type *base, clock_pll_ctrl_t pllControl)
{
    CCM_ANALOG_TUPLE_REG(base, pllControl) |= 1UL << CCM_ANALOG_TUPLE_SHIFT(pllControl);
}

/*!
 * @brief PLL bypass setting
 *
 * @param base CCM_ANALOG base pointer.
 * @param pllControl PLL control name (see ccm_analog_pll_control_t enumeration)
 * @param bypass Bypass the PLL.
 *               - true: Bypass the PLL.
 *               - false: Do not bypass the PLL.
 */
static inline void CLOCK_SetPllBypass(CCM_ANALOG_Type *base, clock_pll_bypass_ctrl_t pllControl, bool bypass)
{
    if (bypass)
    {
        CCM_ANALOG_TUPLE_REG(base, pllControl) |= 1UL << CCM_ANALOG_TUPLE_SHIFT(pllControl);
    }
    else
    {
        CCM_ANALOG_TUPLE_REG(base, pllControl) &= ~(1UL << CCM_ANALOG_TUPLE_SHIFT(pllControl));
    }
}

/*!
 * @brief Check if PLL is bypassed
 *
 * @param base CCM_ANALOG base pointer.
 * @param pllControl PLL control name (see ccm_analog_pll_control_t enumeration)
 * @return PLL bypass status.
 *         - true: The PLL is bypassed.
 *         - false: The PLL is not bypassed.
 */
static inline bool CLOCK_IsPllBypassed(CCM_ANALOG_Type *base, clock_pll_bypass_ctrl_t pllControl)
{
    return (bool)(CCM_ANALOG_TUPLE_REG(base, pllControl) & (1UL << CCM_ANALOG_TUPLE_SHIFT(pllControl)));
}

/*!
 * @brief Check if PLL clock is locked
 *
 * @param base CCM_ANALOG base pointer.
 * @param pllControl PLL control name (see @ref clock_pll_ctrl_t enumeration)
 * @return PLL lock status.
 *         - true: The PLL clock is locked.
 *         - false: The PLL clock is not locked.
 */
static inline bool CLOCK_IsPllLocked(CCM_ANALOG_Type *base, clock_pll_ctrl_t pllControl)
{
    return (bool)(CCM_ANALOG_TUPLE_REG(base, pllControl) & CCM_ANALOG_AUDIO_PLL1_CFG0_PLL_LOCK_MASK);
}

/*!
 * @brief Enable PLL clock
 *
 * @param base CCM_ANALOG base pointer.
 * @param pllClock PLL clock name (see ccm_analog_pll_clock_t enumeration)
 */
static inline void CLOCK_EnableAnalogClock(CCM_ANALOG_Type *base, clock_pll_clke_t pllClock)
{
    CCM_ANALOG_TUPLE_REG(base, pllClock) |= 1UL << CCM_ANALOG_TUPLE_SHIFT(pllClock);
}

/*!
 * @brief Disable PLL clock
 *
 * @param base CCM_ANALOG base pointer.
 * @param pllClock PLL clock name (see ccm_analog_pll_clock_t enumeration)
 */
static inline void CLOCK_DisableAnalogClock(CCM_ANALOG_Type *base, clock_pll_clke_t pllClock)
{
    CCM_ANALOG_TUPLE_REG(base, pllClock) &= ~(1UL << CCM_ANALOG_TUPLE_SHIFT(pllClock));
}

/*!
 * @brief Override PLL clock output enable
 *
 * @param base CCM_ANALOG base pointer.
 * @param ovClock PLL clock name (see @ref clock_pll_clke_t enumeration)
 * @param override Override the PLL.
 *               - true: Override the PLL clke, CCM will handle it.
 *               - false: Do not override the PLL clke.
 */
static inline void CLOCK_OverrideAnalogClke(CCM_ANALOG_Type *base, clock_pll_clke_t ovClock, bool override)
{
    if (override)
    {
        CCM_ANALOG_TUPLE_REG(base, ovClock) |= 1UL << (CCM_ANALOG_TUPLE_SHIFT(ovClock) - 1UL);
    }
    else
    {
        CCM_ANALOG_TUPLE_REG(base, ovClock) &= ~(1UL << (CCM_ANALOG_TUPLE_SHIFT(ovClock) - 1UL));
    }
}

/*!
 * @brief Override PLL power down
 *
 * @param base CCM_ANALOG base pointer.
 * @param pdClock PLL clock name (see @ref clock_pll_ctrl_t enumeration)
 * @param override Override the PLL.
 *               - true: Override the PLL clke, CCM will handle it.
 *               - false: Do not override the PLL clke.
 */
static inline void CLOCK_OverridePllPd(CCM_ANALOG_Type *base, clock_pll_ctrl_t pdClock, bool override)
{
    if (override)
    {
        CCM_ANALOG_TUPLE_REG(base, pdClock) |= 1UL << (CCM_ANALOG_TUPLE_SHIFT(pdClock) - 1UL);
    }
    else
    {
        CCM_ANALOG_TUPLE_REG(base, pdClock) &= ~(1UL << (CCM_ANALOG_TUPLE_SHIFT(pdClock) - 1UL));
    }
}

/*!
 * @brief Initializes the ANALOG ARM PLL.
 *
 * @param config Pointer to the configuration structure(see @ref ccm_analog_frac_pll_config_t enumeration).
 *
 * @note This function can't detect whether the Arm PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitArmPll(const ccm_analog_frac_pll_config_t *config);

/*!
 * @brief De-initialize the ARM PLL.
 */
void CLOCK_DeinitArmPll(void);

/*!
 * @brief Initializes the ANALOG SYS PLL1.
 *
 * @param config Pointer to the configuration structure(see @ref ccm_analog_sscg_pll_config_t enumeration).
 *
 * @note This function can't detect whether the SYS PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitSysPll1(const ccm_analog_sscg_pll_config_t *config);

/*!
 * @brief De-initialize the System PLL1.
 */
void CLOCK_DeinitSysPll1(void);

/*!
 * @brief Initializes the ANALOG SYS PLL2.
 *
 * @param config Pointer to the configuration structure(see @ref ccm_analog_sscg_pll_config_t enumeration).
 *
 * @note This function can't detect whether the SYS PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitSysPll2(const ccm_analog_sscg_pll_config_t *config);

/*!
 * @brief De-initialize the System PLL2.
 */
void CLOCK_DeinitSysPll2(void);

/*!
 * @brief Initializes the ANALOG SYS PLL3.
 *
 * @param config Pointer to the configuration structure(see @ref ccm_analog_sscg_pll_config_t enumeration).
 *
 * @note This function can't detect whether the SYS PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitSysPll3(const ccm_analog_sscg_pll_config_t *config);

/*!
 * @brief De-initialize the System PLL3.
 */
void CLOCK_DeinitSysPll3(void);

/*!
 * @brief Initializes the ANALOG DDR PLL.
 *
 * @param config Pointer to the configuration structure(see @ref ccm_analog_sscg_pll_config_t enumeration).
 *
 * @note This function can't detect whether the DDR PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitDramPll(const ccm_analog_sscg_pll_config_t *config);

/*!
 * @brief De-initialize the Dram PLL.
 */
void CLOCK_DeinitDramPll(void);

/*!
 * @brief Initializes the ANALOG AUDIO PLL1.
 *
 * @param config Pointer to the configuration structure(see @ref ccm_analog_frac_pll_config_t enumeration).
 *
 * @note This function can't detect whether the AUDIO PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitAudioPll1(const ccm_analog_frac_pll_config_t *config);

/*!
 * @brief De-initialize the Audio PLL1.
 */
void CLOCK_DeinitAudioPll1(void);

/*!
 * @brief Initializes the ANALOG AUDIO PLL2.
 *
 * @param config Pointer to the configuration structure(see @ref ccm_analog_frac_pll_config_t enumeration).
 *
 * @note This function can't detect whether the AUDIO PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitAudioPll2(const ccm_analog_frac_pll_config_t *config);

/*!
 * @brief De-initialize the Audio PLL2.
 */
void CLOCK_DeinitAudioPll2(void);

/*!
 * @brief Initializes the ANALOG VIDEO PLL1.
 *
 * @param config Pointer to the configuration structure(see @ref ccm_analog_frac_pll_config_t enumeration).
 *
 */
void CLOCK_InitVideoPll1(const ccm_analog_frac_pll_config_t *config);

/*!
 * @brief De-initialize the Video PLL1.
 */
void CLOCK_DeinitVideoPll1(void);

/*!
 * @brief Initializes the ANALOG VIDEO PLL2.
 *
 * @param config Pointer to the configuration structure(see @ref ccm_analog_sscg_pll_config_t enumeration).
 *
 * @note This function can't detect whether the VIDEO PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitVideoPll2(const ccm_analog_sscg_pll_config_t *config);

/*!
 * @brief De-initialize the Video PLL2.
 */
void CLOCK_DeinitVideoPll2(void);

/*!
 * @brief Initializes the ANALOG SSCG PLL.
 *
 * @param base CCM ANALOG base address
 * @param config Pointer to the configuration structure(see @ref ccm_analog_sscg_pll_config_t enumeration).
 * @param type sscg pll type
 *
 */
void CLOCK_InitSSCGPll(CCM_ANALOG_Type *base, const ccm_analog_sscg_pll_config_t *config, clock_pll_ctrl_t type);

/*!
 * @brief Get the ANALOG SSCG PLL clock frequency.
 *
 * @param base CCM ANALOG base address.
 * @param type sscg pll type
 * @param refClkFreq reference clock frequency
 * @param pll1Bypass pll1 bypass flag
 *
 * @return  Clock frequency
 */
uint32_t CLOCK_GetSSCGPllFreq(CCM_ANALOG_Type *base, clock_pll_ctrl_t type, uint32_t refClkFreq, bool pll1Bypass);

/*!
 * @brief Initializes the ANALOG Fractional PLL.
 *
 * @param base CCM ANALOG base address.
 * @param config Pointer to the configuration structure(see @ref ccm_analog_frac_pll_config_t enumeration).
 * @param type fractional pll type.
 *
 */
void CLOCK_InitFracPll(CCM_ANALOG_Type *base, const ccm_analog_frac_pll_config_t *config, clock_pll_ctrl_t type);

/*!
 * @brief Gets the ANALOG Fractional PLL clock frequency.
 *
 * @param base CCM_ANALOG base pointer.
 * @param type fractional pll type.
 * @param refClkFreq reference clock frequency
 *
 * @return  Clock frequency
 */
uint32_t CLOCK_GetFracPllFreq(CCM_ANALOG_Type *base, clock_pll_ctrl_t type, uint32_t refClkFreq);

/*!
 * @brief Gets PLL clock frequency.
 *
 * @param pll fractional pll type.

 * @return  Clock frequency
 */
uint32_t CLOCK_GetPllFreq(clock_pll_ctrl_t pll);

/*!
 * @brief Gets PLL reference clock frequency.
 *
 * @param ctrl fractional pll type.

 * @return  Clock frequency
 */
uint32_t CLOCK_GetPllRefClkFreq(clock_pll_ctrl_t ctrl);

/*!
 * @name CCM Get frequency
 * @{
 */

/*!
 * @brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_name_t.
 *
 * @param clockName Clock names defined in clock_name_t
 * @return Clock frequency value in hertz
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName);

/*!
 * @brief Get the CCM Cortex M4 core frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetCoreM4Freq(void);

/*!
 * @brief Get the CCM Axi bus frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAxiFreq(void);

/*!
 * @brief Get the CCM Ahb bus frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetAhbFreq(void);

/* @} */

#if defined(__cplusplus)
}
#endif
/* @} */
#endif
