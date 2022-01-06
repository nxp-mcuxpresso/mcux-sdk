/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#include "fsl_device_registers.h"
#include "fsl_common.h"
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
/*! @brief CLOCK driver version 2.0.1. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*@}*/

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (800000000UL)
#endif

/*!
 * @brief XTAL 24M clock frequency.
 */
#define OSC24M_CLK_FREQ 24000000U
/*!
 * @brief pad clock frequency.
 */
#define CLKPAD_FREQ 0U

/*! @brief Clock ip name array for ECSPI. */
#define ECSPI_CLOCKS                                                   \
    {                                                                  \
        kCLOCK_IpInvalid, kCLOCK_Ecspi1, kCLOCK_Ecspi2, kCLOCK_Ecspi3, \
    }

/*! @brief Clock ip name array for EDMA. */
#define EDMA_CLOCKS  \
    {                \
        kCLOCK_Edma, \
    }

/*! @brief Clock ip name array for ENET. */
#define ENET_CLOCKS   \
    {                 \
        kCLOCK_Enet1, \
    }

/*! @brief Clock ip name array for ENET_QOS. */
#define ENETQOS_CLOCKS  \
    {                   \
        kCLOCK_Enet_Qos \
    }

/*! @brief Clock ip name array for FLEXCAN. */
#define FLEXCAN_CLOCKS                              \
    {                                               \
        kCLOCK_IpInvalid, kCLOCK_Can1, kCLOCK_Can2, \
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
#define I2C_CLOCKS                                                                                      \
    {                                                                                                   \
        kCLOCK_IpInvalid, kCLOCK_I2c1, kCLOCK_I2c2, kCLOCK_I2c3, kCLOCK_I2c4, kCLOCK_I2c5, kCLOCK_I2c6, \
    }

/*! @brief Clock ip name array for IOMUX. */
#define IOMUX_CLOCKS  \
    {                 \
        kCLOCK_Iomux, \
    }

/*! @brief Clock ip name array for IPMUX. */
#define IPMUX_CLOCKS                                 \
    {                                                \
        kCLOCK_Ipmux1, kCLOCK_Ipmux2, kCLOCK_Ipmux3, \
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
#define SAI_CLOCKS                                                                                           \
    {                                                                                                        \
        kCLOCK_IpInvalid, kCLOCK_Sai1, kCLOCK_Sai2, kCLOCK_Sai3, kCLOCK_IpInvalid, kCLOCK_Sai5, kCLOCK_Sai6, \
            kCLOCK_Sai7                                                                                      \
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
#define USDHC_CLOCKS                                                  \
    {                                                                 \
        kCLOCK_IpInvalid, kCLOCK_Usdhc1, kCLOCK_Usdhc2, kCLOCK_Usdhc3 \
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
#define SDMA_CLOCKS                               \
    {                                             \
        kCLOCK_Sdma1, kCLOCK_Sdma2, kCLOCK_Sdma3, \
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

/*! @brief Clock ip name array for PDM. */
#define PDM_CLOCKS \
    {              \
        kCLOCK_Pdm \
    }

/*! @brief Clock ip name array for ASRC. */
#define ASRC_CLOCKS \
    {               \
        kCLOCK_Asrc \
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
#define AUDIO_PLL1_GEN_CTRL_OFFSET 0x00
#define AUDIO_PLL2_GEN_CTRL_OFFSET 0x14
#define VIDEO_PLL1_GEN_CTRL_OFFSET 0x28
#define GPU_PLL_GEN_CTRL_OFFSET    0x64
#define VPU_PLL_GEN_CTRL_OFFSET    0x74
#define ARM_PLL_GEN_CTRL_OFFSET    0x84
#define SYS_PLL1_GEN_CTRL_OFFSET   0x94
#define SYS_PLL2_GEN_CTRL_OFFSET   0x104
#define SYS_PLL3_GEN_CTRL_OFFSET   0x114
#define DRAM_PLL_GEN_CTRL_OFFSET   0x50

/*!
 * @brief CCM ANALOG tuple macros to map corresponding registers and bit fields.
 */
#define CCM_ANALOG_TUPLE(reg, shift)  ((((reg)&0xFFFFU) << 16U) | ((shift)))
#define CCM_ANALOG_TUPLE_SHIFT(tuple) (((uint32_t)(tuple)) & 0x1FU)
#define CCM_ANALOG_TUPLE_REG_OFF(base, tuple, off) \
    (*((volatile uint32_t *)((uint32_t)(base) + (((uint32_t)(tuple) >> 16U) & 0xFFFFU) + (off))))
#define CCM_ANALOG_TUPLE_REG(base, tuple) CCM_ANALOG_TUPLE_REG_OFF(base, tuple, 0U)

/*!
 * @brief CCM CCGR and root tuple
 */
#define CLOCK_GATE_IN_AUDIOMIX (1U)
#define CLOCK_GATE_IN_CCM      (0U)
#define CLOCK_GATE_TYPE(tuple) ((uint32_t)(tuple) >> 28U)
#define CCM_TUPLE(ccgr, root)  ((((ccgr)&0xFFFFU) << 16U) | (root))
#define CCM_TUPLE_CCGR(tuple)  ((uint32_t)(&(CCM)->CCGR[(uint32_t)(tuple) >> 16U].CCGR))
#define CCM_TUPLE_ROOT(tuple)  ((uint32_t)(&(CCM)->ROOT[(uint32_t)(tuple)&0xFFFFU].TARGET_ROOT))
/*!@brief audio mix CCGR */
#define AUDIOMIX_TUPLE(offset, gate, root) \
    (((CLOCK_GATE_IN_AUDIOMIX) << 28U) | (((offset)&0xFU) << 24U) | (((gate)&0xFFU) << 16U) | ((root)&0xFFFFU))
#define AUDIOMIX_TUPLE_OFFSET(tuple) (((uint32_t)(tuple) >> 24U) & 0xFU)
#define AUDIOMIX_TUPLE_GATE(tuple)   (((uint32_t)(tuple) >> 16U) & 0xFFU)
#define AUDIOMIX_TUPLE_ROOT(tuple)   ((uint32_t)(tuple)&0xFFFFU)

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{
    kCLOCK_CoreM7Clk, /*!< ARM M7 Core clock                          */

    kCLOCK_AxiClk, /*!< Main AXI bus clock.                         */
    kCLOCK_AhbClk, /*!< AHB bus clock.                         */
    kCLOCK_IpgClk, /*!< IPG bus clock.                         */

    /* -------------------------------- Other clock --------------------------*/
} clock_name_t;

#define kCLOCK_CoreSysClk       kCLOCK_CoreM7Clk    /*!< For compatible with other platforms without CCM. */
#define CLOCK_GetCoreSysClkFreq CLOCK_GetCoreM7Freq /*!< For compatible with other platforms without CCM. */

/*! @brief CCM CCGR gate control. */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = -1,

    kCLOCK_Debug = CCM_TUPLE(4U, 32U), /*!< DEBUG Clock Gate.*/

    kCLOCK_Dram = CCM_TUPLE(5U, 64U), /*!< DRAM Clock Gate.*/

    kCLOCK_Ecspi1 = CCM_TUPLE(7U, 101U), /*!< ECSPI1 Clock Gate.*/
    kCLOCK_Ecspi2 = CCM_TUPLE(8U, 102U), /*!< ECSPI2 Clock Gate.*/
    kCLOCK_Ecspi3 = CCM_TUPLE(9U, 131U), /*!< ECSPI3 Clock Gate.*/

    kCLOCK_Enet1 = CCM_TUPLE(10U, 17U), /*!< ENET1 Clock Gate.*/

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
    kCLOCK_I2c5 = CCM_TUPLE(51U, 73U), /*!< I2C5 Clock Gate.*/
    kCLOCK_I2c6 = CCM_TUPLE(52U, 74U), /*!< I2C6 Clock Gate.*/

    kCLOCK_Can1 = CCM_TUPLE(53U, 68U), /*!< FlexCAN1 Clock Gate.*/
    kCLOCK_Can2 = CCM_TUPLE(54U, 69U), /*!< FlexCAN2 Clock Gate.*/

    kCLOCK_Enet_Qos = CCM_TUPLE(59U, 81U), /*!< ENET QOS Clock Gate.*/

    kCLOCK_Iomux  = CCM_TUPLE(27U, 33U), /*!< IOMUX Clock Gate.*/
    kCLOCK_Ipmux1 = CCM_TUPLE(28U, 33U), /*!< IPMUX1 Clock Gate.*/
    kCLOCK_Ipmux2 = CCM_TUPLE(29U, 33U), /*!< IPMUX2 Clock Gate.*/
    kCLOCK_Ipmux3 = CCM_TUPLE(30U, 33U), /*!< IPMUX3 Clock Gate.*/

    kCLOCK_Mu = CCM_TUPLE(33U, 33U), /*!< MU Clock Gate.*/

    kCLOCK_Ocram  = CCM_TUPLE(35U, 33U), /*!< OCRAM Clock Gate.*/
    kCLOCK_OcramS = CCM_TUPLE(36U, 32U), /*!< OCRAM S Clock Gate.*/

    kCLOCK_Pwm1 = CCM_TUPLE(40U, 103U), /*!< PWM1 Clock Gate.*/
    kCLOCK_Pwm2 = CCM_TUPLE(41U, 104U), /*!< PWM2 Clock Gate.*/
    kCLOCK_Pwm3 = CCM_TUPLE(42U, 105U), /*!< PWM3 Clock Gate.*/
    kCLOCK_Pwm4 = CCM_TUPLE(43U, 106U), /*!< PWM4 Clock Gate.*/

    kCLOCK_Qspi = CCM_TUPLE(47U, 87U), /*!< QSPI Clock Gate.*/
    kCLOCK_Nand = CCM_TUPLE(48U, 86U), /*!< NAND Clock Gate.*/

    kCLOCK_Rdc = CCM_TUPLE(49U, 33U), /*!< RDC Clock Gate.*/

    kCLOCK_Sdma1 = CCM_TUPLE(58U, 33U), /*!< SDMA1 Clock Gate.*/

    kCLOCK_Sec_Debug = CCM_TUPLE(60U, 33U), /*!< SEC_DEBUG Clock Gate.*/

    kCLOCK_Sema42_1 = CCM_TUPLE(61U, 33U), /*!< RDC SEMA42 Clock Gate.*/
    kCLOCK_Sema42_2 = CCM_TUPLE(62U, 33U), /*!< RDC SEMA42 Clock Gate.*/

    kCLOCK_Sim_enet   = CCM_TUPLE(64U, 17U), /*!< SIM_ENET Clock Gate.*/
    kCLOCK_Sim_m      = CCM_TUPLE(65U, 32U), /*!< SIM_M Clock Gate.*/
    kCLOCK_Sim_main   = CCM_TUPLE(66U, 16U), /*!< SIM_MAIN Clock Gate.*/
    kCLOCK_Sim_s      = CCM_TUPLE(67U, 32U), /*!< SIM_S Clock Gate.*/
    kCLOCK_Sim_wakeup = CCM_TUPLE(68U, 32U), /*!< SIM_WAKEUP Clock Gate.*/

    kCLOCK_Gpu2D = CCM_TUPLE(69U, 5U), /*!< GPU2D Clock Gate.*/
    kCLOCK_Gpu3D = CCM_TUPLE(70U, 3U), /*!< GPU3D Clock Gate.*/

    kCLOCK_Uart1 = CCM_TUPLE(73U, 94U), /*!< UART1 Clock Gate.*/
    kCLOCK_Uart2 = CCM_TUPLE(74U, 95U), /*!< UART2 Clock Gate.*/
    kCLOCK_Uart3 = CCM_TUPLE(75U, 96U), /*!< UART3 Clock Gate.*/
    kCLOCK_Uart4 = CCM_TUPLE(76U, 97U), /*!< UART4 Clock Gate.*/

    kCLOCK_Usdhc1 = CCM_TUPLE(81U, 88U),  /*!< USDHC1 Clock Gate.*/
    kCLOCK_Usdhc2 = CCM_TUPLE(82U, 89U),  /*!< USDHC2 Clock Gate.*/
    kCLOCK_Wdog1  = CCM_TUPLE(83U, 114U), /*!< WDOG1 Clock Gate.*/
    kCLOCK_Wdog2  = CCM_TUPLE(84U, 114U), /*!< WDOG2 Clock Gate.*/
    kCLOCK_Wdog3  = CCM_TUPLE(85U, 114U), /*!< WDOG3 Clock Gate.*/

    kCLOCK_Vpu_G1    = CCM_TUPLE(86U, 66U),  /*!< VPU_G1 Clock Gate.*/
    kCLOCK_Gpu       = CCM_TUPLE(87U, 25U),  /*!< GPU Clock Gate.*/
    kCLOCK_Vpu_Vc8ke = CCM_TUPLE(89U, 133U), /*!< VPU_VC8KE Clock Gate.*/
    kCLOCK_Vpu_G2    = CCM_TUPLE(90U, 67U),  /*!< VPU_G2 Clock Gate.*/

    kCLOCK_Npu    = CCM_TUPLE(91U, 2U),   /*!< NPU Clock Gate.*/
    kCLOCK_Hsio   = CCM_TUPLE(92U, 7U),   /*!< HSIO Clock Gate.*/
    kCLOCK_Media  = CCM_TUPLE(93U, 20U),  /*!< MEDIA Clock Gate.*/
    kCLOCK_Usdhc3 = CCM_TUPLE(94U, 121U), /*!< USDHC3 Clock Gate.*/
    kCLOCK_Hdmi   = CCM_TUPLE(95U, 120U), /*!< HDMI Clock Gate.*/

    kCLOCK_TempSensor = CCM_TUPLE(98U, 0xFFFF), /*!< TempSensor Clock Gate.*/

    kCLOCK_Audio = CCM_TUPLE(101U, 6U), /*!< AUDIO Clock Gate.*/

    kCLOCK_Earc          = AUDIOMIX_TUPLE(0U, 31U, 0xFFFF), /*!< EARC clock gate */
    kCLOCK_AudioDspDebug = AUDIOMIX_TUPLE(0U, 30U, 0xFFFF), /*!< AUDIO DSP DEBUG clock gate*/
    kCLOCK_AudioDsp      = AUDIOMIX_TUPLE(0U, 29U, 0xFFFF), /*!< audio dsp clock gate */
    kCLOCK_Spba2         = AUDIOMIX_TUPLE(0U, 28U, 0xFFFF), /*!< SPBA2 clock gate */
    kCLOCK_Sdma3         = AUDIOMIX_TUPLE(0U, 27U, 0xFFFF), /*!< SDMA3 clock gate */
    kCLOCK_Sdma2         = AUDIOMIX_TUPLE(0U, 26U, 0xFFFF), /*!< SDMA2 clock gate */
    kCLOCK_Pdm           = AUDIOMIX_TUPLE(0U, 25U, 132),    /*!< PDM clock gate */
    kCLOCK_Asrc          = AUDIOMIX_TUPLE(0U, 24U, 0xFFFF), /*!< ASRC clock gate */
    kCLOCK_Sai7_Mclk3    = AUDIOMIX_TUPLE(0U, 23U, 0xFFFF), /*!< SAI7 MCLK3 clock gate */
    kCLOCK_Sai7_Mclk2    = AUDIOMIX_TUPLE(0U, 22U, 0xFFFF), /*!< SAI7 MCLK2 clock gate */
    kCLOCK_Sai7_Mclk1    = AUDIOMIX_TUPLE(0U, 21U, 0xFFFF), /*!< SAI7 MCLK1 clock gate */
    kCLOCK_Sai7          = AUDIOMIX_TUPLE(0U, 20U, 134U),   /*!< SAI7 clock gate */

    kCLOCK_Sai6_Mclk3 = AUDIOMIX_TUPLE(0U, 19U, 0xFFFF), /*!< SAI6 MCLK3 clock gate */
    kCLOCK_Sai6_Mclk2 = AUDIOMIX_TUPLE(0U, 18U, 0xFFFF), /*!< SAI6 MCLK2 clock gate */
    kCLOCK_Sai6_Mclk1 = AUDIOMIX_TUPLE(0U, 17U, 0xFFFF), /*!< SAI6 MCLK1 clock gate */
    kCLOCK_Sai6       = AUDIOMIX_TUPLE(0U, 16U, 80U),    /*!< SAI6 clock gate */

    kCLOCK_Sai5_Mclk3 = AUDIOMIX_TUPLE(0U, 15U, 0xFFFF), /*!< SAI5 MCLK3 clock gate */
    kCLOCK_Sai5_Mclk2 = AUDIOMIX_TUPLE(0U, 14U, 0xFFFF), /*!< sai5 MCLK2 clock gate */
    kCLOCK_Sai5_Mclk1 = AUDIOMIX_TUPLE(0U, 13U, 0xFFFF), /*!< SAI5 MCLK1 clock gate */
    kCLOCK_Sai5       = AUDIOMIX_TUPLE(0U, 12U, 79U),    /*!< SAI5 clock gate */

    kCLOCK_Sai3_Mclk3 = AUDIOMIX_TUPLE(0U, 11U, 0xFFFF), /*!< SAI3 MCLK3 clock gate */
    kCLOCK_Sai3_Mclk2 = AUDIOMIX_TUPLE(0U, 10U, 0xFFFF), /*!< SAI3 MCLK2 clock gate */
    kCLOCK_Sai3_Mclk1 = AUDIOMIX_TUPLE(0U, 9U, 0xFFFF),  /*!< SAI3 MCLK1 clock gate */
    kCLOCK_Sai3       = AUDIOMIX_TUPLE(0U, 8U, 77U),     /*!< SAI3 clock gate */

    kCLOCK_Sai2_Mclk3 = AUDIOMIX_TUPLE(0U, 7U, 0xFFFF), /*!< SAI2 MCLK3 clock gate */
    kCLOCK_Sai2_Mclk2 = AUDIOMIX_TUPLE(0U, 6U, 0xFFFF), /*!< SAI2 MCLK2 clock gate */
    kCLOCK_Sai2_Mclk1 = AUDIOMIX_TUPLE(0U, 5U, 0xFFFF), /*!< SAI2 MCLK1 clock gate */
    kCLOCK_Sai2       = AUDIOMIX_TUPLE(0U, 4U, 76U),    /*!< SAI2 clock gate */

    kCLOCK_Sai1_Mclk3 = AUDIOMIX_TUPLE(0U, 3U, 0xFFFF), /*!< SAI1 MCLK3 clock gate */
    kCLOCK_Sai1_Mclk2 = AUDIOMIX_TUPLE(0U, 2U, 0xFFFF), /*!< SAI1 MCLK2 clock gate */
    kCLOCK_Sai1_Mclk1 = AUDIOMIX_TUPLE(0U, 1U, 0xFFFF), /*!< SAI1 MCLK1 clock gate */
    kCLOCK_Sai1       = AUDIOMIX_TUPLE(0U, 0U, 75U),    /*!< SAI1 clock gate */

    kCLOCK_EarcPhy = AUDIOMIX_TUPLE(4U, 6U, 0xFFFF), /*!< EARC PHY clock gate */
    kCLOCK_Mu3     = AUDIOMIX_TUPLE(4U, 5U, 0xFFFF), /*!< MU3 clock gate */
    kCLOCK_Mu2     = AUDIOMIX_TUPLE(4U, 4U, 0xFFFF), /*!< MU2 clock gate */
    kCLOCK_Pll     = AUDIOMIX_TUPLE(4U, 3U, 0xFFFF), /*!< PLL clock gate */
    kCLOCK_Edma    = AUDIOMIX_TUPLE(4U, 2U, 0xFFFF), /*!< EDMA clock gate */
    kCLOCK_Aud2htx = AUDIOMIX_TUPLE(4U, 1U, 0xFFFF), /*!< AUD2HTX clock gate */
    kCLOCK_Ocram_A = AUDIOMIX_TUPLE(4U, 0U, 0xFFFF), /*!< OCRAM A clock gate */
} clock_ip_name_t;

/*! @brief ccm root name used to get clock frequency. */
typedef enum _clock_root_control
{
    kCLOCK_RootM7           = (uint32_t)(&(CCM)->ROOT[1].TARGET_ROOT),  /*!< ARM Cortex-M7 Clock control name.*/
    kCLOCK_RootHsioAxi      = (uint32_t)(&(CCM)->ROOT[7].TARGET_ROOT),  /*!< HSIO AXI Clock control name.*/
    kCLOCK_RootMainAxi      = (uint32_t)(&(CCM)->ROOT[16].TARGET_ROOT), /*!< MAIN AXI Clock control name.*/
    kCLOCK_RootEnetAxi      = (uint32_t)(&(CCM)->ROOT[17].TARGET_ROOT), /*!< ENET AXI Clock control name.*/
    kCLOCK_RootNandUsdhcBus = (uint32_t)(&(CCM)->ROOT[18].TARGET_ROOT), /*!< NAND USDHC BUS Clock control name.*/
    kCLOCK_RootVpuBus       = (uint32_t)(&(CCM)->ROOT[19].TARGET_ROOT), /*!< VPU BUS Clock control name.*/
    kCLOCK_RootMediaAxi     = (uint32_t)(&(CCM)->ROOT[20].TARGET_ROOT), /*!< MEDIA AXI Clock control name.*/
    kCLOCK_RootMediaApb     = (uint32_t)(&(CCM)->ROOT[21].TARGET_ROOT), /*!< MEDIA APB Clock control name.*/
    kCLOCK_RootHdmiApb      = (uint32_t)(&(CCM)->ROOT[22].TARGET_ROOT), /*!< HDMI APB Clock control name.*/
    kCLOCK_RootNoc          = (uint32_t)(&(CCM)->ROOT[26].TARGET_ROOT), /*!< NOC Clock control name.*/
    kCLOCK_RootAhb          = (uint32_t)(&(CCM)->ROOT[32].TARGET_ROOT), /*!< AHB Clock control name.*/
    kCLOCK_RootIpg          = (uint32_t)(&(CCM)->ROOT[33].TARGET_ROOT), /*!< IPG Clock control name.*/
    kCLOCK_RootAudioAhb     = (uint32_t)(&(CCM)->ROOT[34].TARGET_ROOT), /*!< Audio AHB Clock control name.*/
    kCLOCK_RootAudioIpg     = (uint32_t)(&(CCM)->ROOT[35].TARGET_ROOT), /*!< Audio IPG Clock control name.*/
    kCLOCK_RootDramAlt      = (uint32_t)(&(CCM)->ROOT[64].TARGET_ROOT), /*!< DRAM ALT Clock control name.*/
    kCLOCK_RootFlexCan1     = (uint32_t)(&(CCM)->ROOT[68].TARGET_ROOT), /*!< FLEXCAN1 Clock control name.*/
    kCLOCK_RootFlexCan2     = (uint32_t)(&(CCM)->ROOT[69].TARGET_ROOT), /*!< FLEXCAN2 Clock control name.*/

    kCLOCK_RootSai1 = (uint32_t)(&(CCM)->ROOT[75].TARGET_ROOT),  /*!< SAI1 Clock control name.*/
    kCLOCK_RootSai2 = (uint32_t)(&(CCM)->ROOT[76].TARGET_ROOT),  /*!< SAI2 Clock control name.*/
    kCLOCK_RootSai3 = (uint32_t)(&(CCM)->ROOT[77].TARGET_ROOT),  /*!< SAI3 Clock control name.*/
    kCLOCK_RootSai5 = (uint32_t)(&(CCM)->ROOT[79].TARGET_ROOT),  /*!< SAI5 Clock control name.*/
    kCLOCK_RootSai6 = (uint32_t)(&(CCM)->ROOT[80].TARGET_ROOT),  /*!< SAI6 Clock control name.*/
    kCLOCK_RootSai7 = (uint32_t)(&(CCM)->ROOT[134].TARGET_ROOT), /*!< SAI7 Clock control name.*/

    kCLOCK_RootEnetQos      = (uint32_t)(&(CCM)->ROOT[81].TARGET_ROOT), /*!< ENET QOS Clock control name.*/
    kCLOCK_RootEnetQosTimer = (uint32_t)(&(CCM)->ROOT[82].TARGET_ROOT), /*!< ENET QOS TIMER Clock control name.*/
    kCLOCK_RootEnetRef      = (uint32_t)(&(CCM)->ROOT[83].TARGET_ROOT), /*!< ENET Clock control name.*/
    kCLOCK_RootEnetTimer    = (uint32_t)(&(CCM)->ROOT[84].TARGET_ROOT), /*!< ENET TIMER Clock control name.*/
    kCLOCK_RootEnetPhy      = (uint32_t)(&(CCM)->ROOT[85].TARGET_ROOT), /*!< ENET PHY Clock control name.*/

    kCLOCK_RootNand   = (uint32_t)(&(CCM)->ROOT[86].TARGET_ROOT),  /*!< NAND Clock control name.*/
    kCLOCK_RootQspi   = (uint32_t)(&(CCM)->ROOT[87].TARGET_ROOT),  /*!< QSPI Clock control name.*/
    kCLOCK_RootUsdhc1 = (uint32_t)(&(CCM)->ROOT[88].TARGET_ROOT),  /*!< USDHC1 Clock control name.*/
    kCLOCK_RootUsdhc2 = (uint32_t)(&(CCM)->ROOT[89].TARGET_ROOT),  /*!< USDHC2 Clock control name.*/
    kCLOCK_RootUsdhc3 = (uint32_t)(&(CCM)->ROOT[121].TARGET_ROOT), /*!< USDHC3 Clock control name.*/

    kCLOCK_RootI2c1 = (uint32_t)(&(CCM)->ROOT[90].TARGET_ROOT), /*!< I2C1 Clock control name.*/
    kCLOCK_RootI2c2 = (uint32_t)(&(CCM)->ROOT[91].TARGET_ROOT), /*!< I2C2 Clock control name.*/
    kCLOCK_RootI2c3 = (uint32_t)(&(CCM)->ROOT[92].TARGET_ROOT), /*!< I2C3 Clock control name.*/
    kCLOCK_RootI2c4 = (uint32_t)(&(CCM)->ROOT[93].TARGET_ROOT), /*!< I2C4 Clock control name.*/
    kCLOCK_RootI2c5 = (uint32_t)(&(CCM)->ROOT[73].TARGET_ROOT), /*!< I2C5 Clock control name.*/
    kCLOCK_RootI2c6 = (uint32_t)(&(CCM)->ROOT[74].TARGET_ROOT), /*!< I2C6 Clock control name.*/

    kCLOCK_RootUart1 = (uint32_t)(&(CCM)->ROOT[94].TARGET_ROOT), /*!< UART1 Clock control name.*/
    kCLOCK_RootUart2 = (uint32_t)(&(CCM)->ROOT[95].TARGET_ROOT), /*!< UART2 Clock control name.*/
    kCLOCK_RootUart3 = (uint32_t)(&(CCM)->ROOT[96].TARGET_ROOT), /*!< UART3 Clock control name.*/
    kCLOCK_RootUart4 = (uint32_t)(&(CCM)->ROOT[97].TARGET_ROOT), /*!< UART4 Clock control name.*/

    kCLOCK_RootGic    = (uint32_t)(&(CCM)->ROOT[100].TARGET_ROOT), /*!< GIC Clock control name.*/
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

    kCLOCK_RootPdm = (uint32_t)(&(CCM)->ROOT[132].TARGET_ROOT), /*!< PDM Clock control name.*/

} clock_root_control_t;

/*! @brief Root clock select enumeration for ARM Cortex-M7 core. */
typedef enum _clock_rootmux_m7_clk_sel
{
    kCLOCK_M7RootmuxOsc24M      = 0U, /*!< ARM Cortex-M7 Clock from OSC 24M.*/
    kCLOCK_M7RootmuxSysPll2Div5 = 1U, /*!< ARM Cortex-M7 Clock from SYSTEM PLL2 divided by 5.*/
    kCLOCK_M7RootmuxSysPll2Div4 = 2U, /*!< ARM Cortex-M7 Clock from SYSTEM PLL2 divided by 4.*/
    kCLOCK_M7RootmuxSysVpuPll   = 3U, /*!< ARM Cortex-M7 Clock from VPU PLL.*/
    kCLOCK_M7RootmuxSysPll1     = 4U, /*!< ARM Cortex-M7 Clock from SYSTEM PLL1.*/
    kCLOCK_M7RootmuxAudioPll1   = 5U, /*!< ARM Cortex-M7 Clock from AUDIO PLL1.*/
    kCLOCK_M7RootmuxVideoPll1   = 6U, /*!< ARM Cortex-M7 Clock from VIDEO PLL1.*/
    kCLOCK_M7RootmuxSysPll3     = 7U, /*!< ARM Cortex-M7 Clock from SYSTEM PLL3.*/
} clock_rootmux_m7_clk_sel_t;

/*! @brief Root clock select enumeration for MAIN AXI bus. */
typedef enum _clock_rootmux_axi_clk_sel
{
    kCLOCK_AxiRootmuxOsc24M      = 0U, /*!< ARM MAIN AXI Clock from OSC 24M.*/
    kCLOCK_AxiRootmuxSysPll2Div3 = 1U, /*!< ARM MAIN AXI Clock from SYSTEM PLL2 divided by 3.*/
    kCLOCK_AxiRootmuxSysPll1     = 2U, /*!< ARM MAIN AXI Clock from SYSTEM PLL1.*/
    kCLOCK_AxiRootmuxSysPll2Div4 = 3U, /*!< ARM MAIN AXI Clock from SYSTEM PLL2 divided by 4.*/
    kCLOCK_AxiRootmuxSysPll2     = 4U, /*!< ARM MAIN AXI Clock from SYSTEM PLL2.*/
    kCLOCK_AxiRootmuxAudioPll1   = 5U, /*!< ARM MAIN AXI Clock from AUDIO PLL1.*/
    kCLOCK_AxiRootmuxVideoPll1   = 6U, /*!< ARM MAIN AXI Clock from VIDEO PLL1.*/
    kCLOCK_AxiRootmuxSysPll1Div8 = 7U, /*!< ARM MAIN AXI Clock from SYSTEM PLL1 divided by 8.*/
} clock_rootmux_axi_clk_sel_t;

/*! @brief Root clock select enumeration for AHB bus. */
typedef enum _clock_rootmux_ahb_clk_sel
{
    kCLOCK_AhbRootmuxOsc24M      = 0U, /*!< ARM AHB Clock from OSC 24M.*/
    kCLOCK_AhbRootmuxSysPll1Div6 = 1U, /*!< ARM AHB Clock from SYSTEM PLL1 divided by 6.*/
    kCLOCK_AhbRootmuxSysPll1     = 2U, /*!< ARM AHB Clock from SYSTEM PLL1.*/
    kCLOCK_AhbRootmuxSysPll1Div2 = 3U, /*!< ARM AHB Clock from SYSTEM PLL1 divided by 2.*/
    kCLOCK_AhbRootmuxSysPll2Div8 = 4U, /*!< ARM AHB Clock from SYSTEM PLL2 divided by 8.*/
    kCLOCK_AhbRootmuxSysPll3     = 5U, /*!< ARM AHB Clock from SYSTEM PLL3.*/
    kCLOCK_AhbRootmuxAudioPll1   = 6U, /*!< ARM AHB Clock from AUDIO PLL1.*/
    kCLOCK_AhbRootmuxVideoPll1   = 7U, /*!< ARM AHB Clock from VIDEO PLL1.*/
} clock_rootmux_ahb_clk_sel_t;

/*! @brief Root clock select enumeration for Audio AHB bus. */
typedef enum _clock_rootmux_audio_ahb_clk_sel
{
    kCLOCK_AudioAhbRootmuxOsc24M      = 0U, /*!< ARM Audio AHB Clock from OSC 24M.*/
    kCLOCK_AudioAhbRootmuxSysPll2Div2 = 1U, /*!< ARM Audio AHB Clock from SYSTEM PLL2 divided by 2.*/
    kCLOCK_AudioAhbRootmuxSysPll1     = 2U, /*!< ARM Audio AHB Clock from SYSTEM PLL1.*/
    kCLOCK_AudioAhbRootmuxSysPll2     = 3U, /*!< ARM Audio AHB Clock from SYSTEM PLL2.*/
    kCLOCK_AudioAhbRootmuxSysPll2Div6 = 4U, /*!< ARM Audio AHB Clock from SYSTEM PLL2 divided by 6.*/
    kCLOCK_AudioAhbRootmuxSysPll3     = 5U, /*!< ARM Audio AHB Clock from SYSTEM PLL3.*/
    kCLOCK_AudioAhbRootmuxAudioPll1   = 6U, /*!< ARM Audio AHB Clock from AUDIO PLL1.*/
    kCLOCK_AudioAhbRootmuxVideoPll1   = 7U, /*!< ARM Audio AHB Clock from VIDEO PLL1.*/
} clock_rootmux_audio_ahb_clk_sel_t;
/*! @brief Root clock select enumeration for QSPI peripheral. */
typedef enum _clock_rootmux_qspi_clk_sel
{
    kCLOCK_QspiRootmuxOsc24M      = 0U, /*!< ARM QSPI Clock from OSC 24M.*/
    kCLOCK_QspiRootmuxSysPll1Div2 = 1U, /*!< ARM QSPI Clock from SYSTEM PLL1 divided by 2.*/
    kCLOCK_QspiRootmuxSysPll2Div3 = 2U, /*!< ARM QSPI Clock from SYSTEM PLL2 divided by 3.*/
    kCLOCK_QspiRootmuxSysPll2Div2 = 3U, /*!< ARM QSPI Clock from SYSTEM PLL2 divided by 2.*/
    kCLOCK_QspiRootmuxAudioPll2   = 4U, /*!< ARM QSPI Clock from AUDIO PLL2.*/
    kCLOCK_QspiRootmuxSysPll1Div3 = 5U, /*!< ARM QSPI Clock from SYSTEM PLL1 divided by 3 */
    kCLOCK_QspiRootmuxSysPll3     = 6,  /*!< ARM QSPI Clock from SYSTEM PLL3.*/
    kCLOCK_QspiRootmuxSysPll1Div8 = 7U, /*!< ARM QSPI Clock from SYSTEM PLL1 divided by 8.*/
} clock_rootmux_qspi_clk_sel_t;

/*! @brief Root clock select enumeration for ECSPI peripheral. */
typedef enum _clock_rootmux_ecspi_clk_sel
{
    kCLOCK_EcspiRootmuxOsc24M       = 0U, /*!< ECSPI Clock from OSC 24M.*/
    kCLOCK_EcspiRootmuxSysPll2Div5  = 1U, /*!< ECSPI Clock from SYSTEM PLL2 divided by 5.*/
    kCLOCK_EcspiRootmuxSysPll1Div20 = 2U, /*!< ECSPI Clock from SYSTEM PLL1 divided by 20.*/
    kCLOCK_EcspiRootmuxSysPll1Div5  = 3U, /*!< ECSPI Clock from SYSTEM PLL1 divided by 5.*/
    kCLOCK_EcspiRootmuxSysPll1      = 4U, /*!< ECSPI Clock from SYSTEM PLL1.*/
    kCLOCK_EcspiRootmuxSysPll3      = 5U, /*!< ECSPI Clock from SYSTEM PLL3.*/
    kCLOCK_EcspiRootmuxSysPll2Div4  = 6U, /*!< ECSPI Clock from SYSTEM PLL2 divided by 4.*/
    kCLOCK_EcspiRootmuxAudioPll2    = 7U, /*!< ECSPI Clock from AUDIO PLL2.*/
} clock_rootmux_ecspi_clk_sel_t;

/*! @brief Root clock select enumeration for ENET AXI bus. */
typedef enum _clock_rootmux_enet_axi_clk_sel
{
    kCLOCK_EnetAxiRootmuxOsc24M      = 0U, /*!< ENET AXI Clock from OSC 24M.*/
    kCLOCK_EnetAxiRootmuxSysPll1Div3 = 1U, /*!< ENET AXI Clock from SYSTEM PLL1 divided by 3.*/
    kCLOCK_EnetAxiRootmuxSysPll1     = 2U, /*!< ENET AXI Clock from SYSTEM PLL1.*/
    kCLOCK_EnetAxiRootmuxSysPll2Div4 = 3U, /*!< ENET AXI Clock from SYSTEM PLL2 divided by 4.*/
    kCLOCK_EnetAxiRootmuxSysPll2Div5 = 4U, /*!< ENET AXI Clock from SYSTEM PLL2 divided by 5.*/
    kCLOCK_EnetAxiRootmuxAudioPll1   = 5U, /*!< ENET AXI Clock from AUDIO PLL1.*/
    kCLOCK_EnetAxiRootmuxVideoPll1   = 6U, /*!< ENET AXI Clock from VIDEO PLL1.*/
    kCLOCK_EnetAxiRootmuxSysPll3     = 7U, /*!< ENET AXI Clock from SYSTEM PLL3.*/
} clock_rootmux_enet_axi_clk_sel_t;

/*! @brief Root clock select enumeration for ENET QOS Clcok. */
typedef enum _clock_rootmux_enet_qos_clk_sel
{
    kCLOCK_EnetQosRootmuxOsc24M       = 0U, /*!< ENET QOS Clock from OSC 24M.*/
    kCLOCK_EnetQosRootmuxSysPll2Div8  = 1U, /*!< ENET QOS Clock from SYSTEM PLL2 divided by 8.*/
    kCLOCK_EnetQosRootmuxSysPll2Div20 = 2U, /*!< ENET QOS Clock from SYSTEM PLL2 divided by 20.*/
    kCLOCK_EnetQosRootmuxSysPll2Div10 = 3U, /*!< ENET QOS Clock from SYSTEM PLL2 divided by 10.*/
    kCLOCK_EnetQosRootmuxSysPll1Div5  = 4U, /*!< ENET QOS Clock from SYSTEM PLL1 divided by 5.*/
    kCLOCK_EnetQosRootmuxAudioPll1    = 5U, /*!< ENET QOS Clock from AUDIO PLL1.*/
    kCLOCK_EnetQosRootmuxVideoPll1    = 6U, /*!< ENET QOS Clock from VIDEO PLL1.*/
    kCLOCK_EnetQosRootmuxExtClk4      = 7U, /*!< ENET QOS Clock from External Clock 4.*/
} clock_rootmux_enet_qos_clk_sel_t;

/*! @brief Root clock select enumeration for ENET REF Clcok. */
typedef enum _clock_rootmux_enet_ref_clk_sel
{
    kCLOCK_EnetRefRootmuxOsc24M       = 0U, /*!< ENET REF Clock from OSC 24M.*/
    kCLOCK_EnetRefRootmuxSysPll2Div8  = 1U, /*!< ENET REF Clock from SYSTEM PLL2 divided by 8.*/
    kCLOCK_EnetRefRootmuxSysPll2Div20 = 2U, /*!< ENET REF Clock from SYSTEM PLL2 divided by 20.*/
    kCLOCK_EnetRefRootmuxSysPll2Div10 = 3U, /*!< ENET REF Clock from SYSTEM PLL2 divided by 10.*/
    kCLOCK_EnetRefRootmuxSysPll1Div5  = 4U, /*!< ENET REF Clock from SYSTEM PLL1 divided by 5.*/
    kCLOCK_EnetRefRootmuxAudioPll1    = 5U, /*!< ENET REF Clock from AUDIO PLL1.*/
    kCLOCK_EnetRefRootmuxVideoPll1    = 6U, /*!< ENET REF Clock from VIDEO PLL1.*/
    kCLOCK_EnetRefRootmuxExtClk4      = 7U, /*!< ENET REF Clock from External Clock 4.*/
} clock_rootmux_enet_ref_clk_sel_t;

/*! @brief Root clock select enumeration for ENET QOS TIMER Clcok. */
typedef enum _clock_rootmux_enet_qos_timer_clk_sel
{
    kCLOCK_EnetQosTimerRootmuxOsc24M       = 0U, /*!< ENET QOS TIMER Clock from OSC 24M.*/
    kCLOCK_EnetQosTimerRootmuxSysPll2Div10 = 1U, /*!< ENET QOS TIMER Clock from SYSTEM PLL2 divided by 10.*/
    kCLOCK_EnetQosTimerRootmuxAudioPll1    = 2U, /*!< ENET QOS TIMER Clock from AUDIO PLL1.*/
    kCLOCK_EnetQosTimerRootmuxExtClk1      = 3U, /*!< ENET QOS TIMER Clock from External Clock 1.*/
    kCLOCK_EnetQosTimerRootmuxExtClk2      = 4U, /*!< ENET QOS TIMER Clock External Clock 2.*/
    kCLOCK_EnetQosTimerRootmuxExtClk3      = 5U, /*!< ENET QOS TIMER Clock from External Clock 3.*/
    kCLOCK_EnetQosTimerRootmuxExtClk4      = 6U, /*!< ENET QOS TIMER Clock from External Clock 4.*/
    kCLOCK_EnetQosTimerRootmuxVideoPll1    = 7U, /*!< ENET QOS TIMER Clock from VIDEO PLL1.*/
} clock_rootmux_enet_qos_timer_clk_sel_t;

/*! @brief Root clock select enumeration for ENET TIMER Clcok. */
typedef enum _clock_rootmux_enet_timer_clk_sel
{
    kCLOCK_EnetTimerRootmuxOsc24M       = 0U, /*!< ENET TIMER Clock from OSC 24M.*/
    kCLOCK_EnetTimerRootmuxSysPll2Div10 = 1U, /*!< ENET TIMER Clock from SYSTEM PLL2 divided by 10.*/
    kCLOCK_EnetTimerRootmuxAudioPll1    = 2U, /*!< ENET TIMER Clock from AUDIO PLL1.*/
    kCLOCK_EnetTimerRootmuxExtClk1      = 3U, /*!< ENET TIMER Clock from External Clock 1.*/
    kCLOCK_EnetTimerRootmuxExtClk2      = 4U, /*!< ENET TIMER Clock External Clock 2.*/
    kCLOCK_EnetTimerRootmuxExtClk3      = 5U, /*!< ENET TIMER Clock from External Clock 3.*/
    kCLOCK_EnetTimerRootmuxExtClk4      = 6U, /*!< ENET TIMER Clock from External Clock 4.*/
    kCLOCK_EnetTimerRootmuxVideoPll1    = 7U, /*!< ENET TIMER Clock from VIDEO PLL1.*/
} clock_rootmux_enet_timer_clk_sel_t;

/*! @brief Root clock select enumeration for ENET PHY Clcok. */
typedef enum _clock_rootmux_enet_phy_clk_sel
{
    kCLOCK_EnetPhyRootmuxOsc24M       = 0U, /*!< ENET PHY Clock from OSC 24M.*/
    kCLOCK_EnetPhyRootmuxSysPll2Div20 = 1U, /*!< ENET PHY Clock from SYSTEM PLL2 divided by 20.*/
    kCLOCK_EnetPhyRootmuxSysPll2Div8  = 2U, /*!< ENET PHY Clock from SYSTEM PLL2 divided by 8.*/
    kCLOCK_EnetPhyRootmuxSysPll2Div5  = 3U, /*!< ENET PHY Clock from SYSTEM PLL2 divided by 5.*/
    kCLOCK_EnetPhyRootmuxSysPll2Div2  = 4U, /*!< ENET PHY Clock from SYSTEM PLL2 divided by 2.*/
    kCLOCK_EnetPhyRootmuxAudioPll1    = 5U, /*!< ENET PHY Clock from AUDIO PLL1.*/
    kCLOCK_EnetPhyRootmuxVideoPll1    = 6U, /*!< ENET PHY Clock from VIDEO PLL1.*/
    kCLOCK_EnetPhyRootmuxAudioPll2    = 7U, /*!< ENET PHY Clock from AUDIO PLL2.*/
} clock_rootmux_enet_phy_clk_sel_t;

/*! @brief Root clock select enumeration for FLEXCAN peripheral. */
typedef enum _clock_rootmux_flexcan_clk_sel
{
    kCLOCK_FlexCanRootmuxOsc24M       = 0U, /*!< FLEXCAN Clock from OSC 24M.*/
    kCLOCK_FlexCanRootmuxSysPll2Div5  = 1U, /*!< FLEXCAN Clock from SYSTEM PLL2 divided by 5.*/
    kCLOCK_FlexCanRootmuxSysPll1Div20 = 2U, /*!< FLEXCAN Clock from SYSTEM PLL1 divided by 20.*/
    kCLOCK_FlexCanRootmuxSysPll1Div5  = 3U, /*!< FLEXCAN Clock from SYSTEM PLL1 divided by 5.*/
    kCLOCK_FlexCanRootmuxSysPll1      = 4U, /*!< FLEXCAN Clock from SYSTEM PLL1.*/
    kCLOCK_FlexCanRootmuxSysPll3      = 5U, /*!< FLEXCAN Clock from SYSTEM PLL3.*/
    kCLOCK_FlexCanRootmuxSysPll2Div4  = 6U, /*!< FLEXCAN Clock from SYSTEM PLL2 divided by 4.*/
    kCLOCK_FlexCanRootmuxAudioPll2    = 7U, /*!< FLEXCAN Clock from AUDIO PLL2.*/
} clock_rootmux_flexcan_clk_sel_t;

/*! @brief Root clock select enumeration for I2C peripheral. */
typedef enum _clock_rootmux_i2c_clk_sel
{
    kCLOCK_I2cRootmuxOsc24M       = 0U, /*!< I2C Clock from OSC 24M.*/
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
    kCLOCK_UartRootmuxOsc24M       = 0U, /*!< UART Clock from OSC 24M.*/
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
    kCLOCK_GptRootmuxOsc24M          = 0U, /*!< GPT Clock from OSC 24M.*/
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
    kCLOCK_WdogRootmuxOsc24M          = 0U, /*!< WDOG Clock from OSC 24M.*/
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
    kCLOCK_PwmRootmuxOsc24M          = 0U, /*!< PWM Clock from OSC 24M.*/
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
    kCLOCK_SaiRootmuxOsc24M      = 0U, /*!< SAI Clock from OSC 24M.*/
    kCLOCK_SaiRootmuxAudioPll1   = 1U, /*!< SAI Clock from AUDIO PLL1.*/
    kCLOCK_SaiRootmuxAudioPll2   = 2U, /*!< SAI Clock from AUDIO PLL2.*/
    kCLOCK_SaiRootmuxVideoPll1   = 3U, /*!< SAI Clock from VIDEO PLL1.*/
    kCLOCK_SaiRootmuxSysPll1Div6 = 4U, /*!< SAI Clock from SYSTEM PLL1 divided by 6.*/
    kCLOCK_SaiRootmuxOsc26m      = 5U, /*!< SAI Clock from OSC HDMI 26M.*/
    kCLOCK_SaiRootmuxExtClk1     = 6U, /*!< SAI Clock from External Clock1, External Clock2, External Clock3.*/
    kCLOCK_SaiRootmuxExtClk2     = 7U, /*!< SAI Clock from External Clock2, External Clock3, External Clock4.*/
} clock_rootmux_sai_clk_sel_t;

/*! @brief Root clock select enumeration for PDM peripheral. */
typedef enum _clock_rootmux_pdm_clk_sel
{
    kCLOCK_PdmRootmuxOsc24M       = 0U, /*!< PDM Clock from OSC 24M.*/
    kCLOCK_PdmRootmuxSysPll2Div10 = 1U, /*!< PDM Clock from SYSTEM PLL2 divided by 10.*/
    kCLOCK_PdmRootmuxAudioPll1    = 2U, /*!< PDM Clock from AUDIO PLL1.*/
    kCLOCK_PdmRootmuxSysPll1      = 3U, /*!< PDM Clock from SYSTEM PLL1.*/
    kCLOCK_PdmRootmuxSysPll2      = 4U, /*!< PDM Clock from SYSTEM PLL2.*/
    kCLOCK_PdmRootmuxSysPll3      = 5U, /*!< PDM Clock from SYSTEM PLL3.*/
    kCLOCK_PdmRootmuxExtClk3      = 6U, /*!< PDM Clock from External Clock3.*/
    kCLOCK_PdmRootmuxAudioPll2    = 7U, /*!< PDM Clock from AUDIO PLL2.*/
} clock_rootmux_pdm_clk_sel_t;

/*! @brief Root clock select enumeration for NOC CLK. */
typedef enum _clock_rootmux_noc_clk_sel
{
    kCLOCK_NocRootmuxOsc24M      = 0U, /*!< NOC Clock from OSC 24M.*/
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
    kCLOCK_AudioPll1BypassCtrl =
        CCM_ANALOG_TUPLE(AUDIO_PLL1_GEN_CTRL_OFFSET,
                         CCM_ANALOG_AUDIO_PLL1_GEN_CTRL_PLL_BYPASS_SHIFT), /*!< CCM Audio PLL1 bypass Control.*/

    kCLOCK_AudioPll2BypassCtrl =
        CCM_ANALOG_TUPLE(AUDIO_PLL2_GEN_CTRL_OFFSET,
                         CCM_ANALOG_AUDIO_PLL2_GEN_CTRL_PLL_BYPASS_SHIFT), /*!< CCM Audio PLL2 bypass Control.*/

    kCLOCK_VideoPll1BypassCtrl =
        CCM_ANALOG_TUPLE(VIDEO_PLL1_GEN_CTRL_OFFSET,
                         CCM_ANALOG_VIDEO_PLL1_GEN_CTRL_PLL_BYPASS_SHIFT), /*!< CCM Video Pll1 bypass Control.*/

    kCLOCK_DramPllInternalPll1BypassCtrl = CCM_ANALOG_TUPLE(
        DRAM_PLL_GEN_CTRL_OFFSET, CCM_ANALOG_DRAM_PLL_GEN_CTRL_PLL_BYPASS_SHIFT), /*!< CCM DRAM PLL bypass Control.*/

    kCLOCK_ArmPllPwrBypassCtrl = CCM_ANALOG_TUPLE(
        ARM_PLL_GEN_CTRL_OFFSET, CCM_ANALOG_ARM_PLL_GEN_CTRL_PLL_BYPASS_SHIFT), /*!< CCM Arm PLL bypass Control.*/

    kCLOCK_SysPll1InternalPll1BypassCtrl = CCM_ANALOG_TUPLE(
        SYS_PLL1_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_BYPASS_SHIFT), /*!< CCM System PLL1 bypass Control.*/

    kCLOCK_SysPll2InternalPll1BypassCtrl = CCM_ANALOG_TUPLE(
        SYS_PLL2_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL2_GEN_CTRL_PLL_BYPASS_SHIFT), /*!< CCM System PLL2 bypass Control.*/

    kCLOCK_SysPll3InternalPll1BypassCtrl = CCM_ANALOG_TUPLE(
        SYS_PLL3_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL3_GEN_CTRL_PLL_BYPASS_SHIFT), /*!< CCM System PLL3 bypass Control.*/
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
    kCLOCK_AudioPll1Clke = CCM_ANALOG_TUPLE(AUDIO_PLL1_GEN_CTRL_OFFSET,
                                            CCM_ANALOG_AUDIO_PLL1_GEN_CTRL_PLL_CLKE_SHIFT), /*!< Audio pll1 clke */
    kCLOCK_AudioPll2Clke = CCM_ANALOG_TUPLE(AUDIO_PLL2_GEN_CTRL_OFFSET,
                                            CCM_ANALOG_AUDIO_PLL2_GEN_CTRL_PLL_CLKE_SHIFT), /*!< Audio pll2 clke */
    kCLOCK_VideoPll1Clke = CCM_ANALOG_TUPLE(VIDEO_PLL1_GEN_CTRL_OFFSET,
                                            CCM_ANALOG_VIDEO_PLL1_GEN_CTRL_PLL_CLKE_SHIFT), /*!< Video pll1 clke */
    kCLOCK_DramPllClke =
        CCM_ANALOG_TUPLE(DRAM_PLL_GEN_CTRL_OFFSET, CCM_ANALOG_DRAM_PLL_GEN_CTRL_PLL_CLKE_SHIFT), /*!< Dram pll clke */

    kCLOCK_ArmPllClke =
        CCM_ANALOG_TUPLE(ARM_PLL_GEN_CTRL_OFFSET, CCM_ANALOG_ARM_PLL_GEN_CTRL_PLL_CLKE_SHIFT), /*!< Arm pll clke */

    kCLOCK_SystemPll1Clke     = CCM_ANALOG_TUPLE(SYS_PLL1_GEN_CTRL_OFFSET,
                                             CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_CLKE_SHIFT), /*!< System pll1 clke */
    kCLOCK_SystemPll1Div2Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_DIV2_CLKE_SHIFT), /*!< System pll1 Div2 clke */
    kCLOCK_SystemPll1Div3Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_DIV3_CLKE_SHIFT), /*!< System pll1 Div3 clke */
    kCLOCK_SystemPll1Div4Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_DIV4_CLKE_SHIFT), /*!< System pll1 Div4 clke */
    kCLOCK_SystemPll1Div5Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_DIV5_CLKE_SHIFT), /*!< System pll1 Div5 clke */
    kCLOCK_SystemPll1Div6Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_DIV6_CLKE_SHIFT), /*!< System pll1 Div6 clke */
    kCLOCK_SystemPll1Div8Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_DIV8_CLKE_SHIFT), /*!< System pll1 Div8 clke */
    kCLOCK_SystemPll1Div10Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_DIV10_CLKE_SHIFT), /*!< System pll1 Div10 clke */
    kCLOCK_SystemPll1Div20Clke = CCM_ANALOG_TUPLE(
        SYS_PLL1_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_DIV20_CLKE_SHIFT), /*!< System pll1 Div20 clke */

    kCLOCK_SystemPll2Clke     = CCM_ANALOG_TUPLE(SYS_PLL2_GEN_CTRL_OFFSET,
                                             CCM_ANALOG_SYS_PLL2_GEN_CTRL_PLL_CLKE_SHIFT), /*!< System pll2 clke */
    kCLOCK_SystemPll2Div2Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL2_GEN_CTRL_PLL_DIV2_CLKE_SHIFT), /*!< System pll2 Div2 clke */
    kCLOCK_SystemPll2Div3Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL2_GEN_CTRL_PLL_DIV3_CLKE_SHIFT), /*!< System pll2 Div3 clke */
    kCLOCK_SystemPll2Div4Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL2_GEN_CTRL_PLL_DIV4_CLKE_SHIFT), /*!< System pll2 Div4 clke */
    kCLOCK_SystemPll2Div5Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL2_GEN_CTRL_PLL_DIV5_CLKE_SHIFT), /*!< System pll2 Div5 clke */
    kCLOCK_SystemPll2Div6Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL2_GEN_CTRL_PLL_DIV6_CLKE_SHIFT), /*!< System pll2 Div6 clke */
    kCLOCK_SystemPll2Div8Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL2_GEN_CTRL_PLL_DIV8_CLKE_SHIFT), /*!< System pll2 Div8 clke */
    kCLOCK_SystemPll2Div10Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL2_GEN_CTRL_PLL_DIV10_CLKE_SHIFT), /*!< System pll2 Div10 clke */
    kCLOCK_SystemPll2Div20Clke = CCM_ANALOG_TUPLE(
        SYS_PLL2_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL2_GEN_CTRL_PLL_DIV20_CLKE_SHIFT), /*!< System pll2 Div20 clke */

    kCLOCK_SystemPll3Clke = CCM_ANALOG_TUPLE(SYS_PLL3_GEN_CTRL_OFFSET,
                                             CCM_ANALOG_SYS_PLL3_GEN_CTRL_PLL_CLKE_SHIFT), /*!< System pll3 clke */
} clock_pll_clke_t;

/*!
 * @brief ANALOG Power down override control.
 */
typedef enum _clock_pll_ctrl
{
    /* Fractional PLL frequency */
    kCLOCK_AudioPll1Ctrl = CCM_ANALOG_TUPLE(AUDIO_PLL1_GEN_CTRL_OFFSET, CCM_ANALOG_AUDIO_PLL1_GEN_CTRL_PLL_RST_SHIFT),
    kCLOCK_AudioPll2Ctrl = CCM_ANALOG_TUPLE(AUDIO_PLL2_GEN_CTRL_OFFSET, CCM_ANALOG_AUDIO_PLL2_GEN_CTRL_PLL_RST_SHIFT),
    kCLOCK_VideoPll1Ctrl = CCM_ANALOG_TUPLE(VIDEO_PLL1_GEN_CTRL_OFFSET, CCM_ANALOG_VIDEO_PLL1_GEN_CTRL_PLL_RST_SHIFT),
    kCLOCK_DramPllCtrl   = CCM_ANALOG_TUPLE(DRAM_PLL_GEN_CTRL_OFFSET, CCM_ANALOG_DRAM_PLL_GEN_CTRL_PLL_RST_SHIFT),
    /* Integer PLL frequency */
    kCLOCK_VpuPllCtrl     = CCM_ANALOG_TUPLE(VPU_PLL_GEN_CTRL_OFFSET, CCM_ANALOG_VPU_PLL_GEN_CTRL_PLL_RST_SHIFT),
    kCLOCK_ArmPllCtrl     = CCM_ANALOG_TUPLE(ARM_PLL_GEN_CTRL_OFFSET, CCM_ANALOG_ARM_PLL_GEN_CTRL_PLL_RST_SHIFT),
    kCLOCK_SystemPll1Ctrl = CCM_ANALOG_TUPLE(SYS_PLL1_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_RST_SHIFT),
    kCLOCK_SystemPll2Ctrl = CCM_ANALOG_TUPLE(SYS_PLL2_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL2_GEN_CTRL_PLL_RST_SHIFT),
    kCLOCK_SystemPll3Ctrl = CCM_ANALOG_TUPLE(SYS_PLL3_GEN_CTRL_OFFSET, CCM_ANALOG_SYS_PLL3_GEN_CTRL_PLL_RST_SHIFT),
} clock_pll_ctrl_t;

/*! @brief PLL reference clock select. */
enum
{
    kANALOG_PllRefOsc24M = 0U, /*!< reference OSC 24M */
    kANALOG_PllPadClk    = 1U, /*!< reference PAD CLK */
};

/*!
 * @brief Fractional-N PLL configuration.
 * Note: all the dividers in this configuration structure are the actually divider, software will map it to register
 * value
 */
typedef struct _ccm_analog_frac_pll_config
{
    uint8_t refSel; /*!< pll reference clock sel */

    uint32_t mainDiv; /*!< Value of the 10-bit programmable main-divider, range must be 64~1023 */

    uint32_t dsm; /*!< Value of 16-bit DSM */

    uint8_t preDiv; /*!< Value of the 6-bit programmable pre-divider, range must be 1~63 */

    uint8_t postDiv; /*!< Value of the 3-bit programmable Scaler, range must be 0~6 */
} ccm_analog_frac_pll_config_t;

/*!
 * @brief Integer PLL configuration.
 * Note: all the dividers in this configuration structure are the actually divider, software will map it to register
 * value
 */
typedef struct _ccm_analog_integer_pll_config
{
    uint8_t refSel; /*!< pll reference clock sel */

    uint32_t mainDiv; /*!< Value of the 10-bit programmable main-divider, range must be 64~1023 */

    uint8_t preDiv; /*!< Value of the 6-bit programmable pre-divider, range must be 1~63 */

    uint8_t postDiv; /*!< Value of the 3-bit programmable Scaler, range must be 0~6 */

} ccm_analog_integer_pll_config_t;

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
 * @param mux mux value (see _ccm_rootmux_xxx enumeration)
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
    CCM_ANALOG_TUPLE_REG(base, pllControl) |= (1UL << CCM_ANALOG_TUPLE_SHIFT(pllControl));
}

/*!
 * @brief Power down PLL
 *
 * @param base CCM_ANALOG base pointer.
 * @param pllControl PLL control name (see @ref clock_pll_ctrl_t enumeration)
 */
static inline void CLOCK_PowerDownPll(CCM_ANALOG_Type *base, clock_pll_ctrl_t pllControl)
{
    CCM_ANALOG_TUPLE_REG(base, pllControl) &= ~(1UL << CCM_ANALOG_TUPLE_SHIFT(pllControl));
}

/*!
 * @brief PLL bypass setting
 *
 * @param base CCM_ANALOG base pointer.
 * @param pllControl PLL control name (see @ref clock_pll_bypass_ctrl_t enumeration)
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
 * @param pllControl PLL control name (see @ref clock_pll_bypass_ctrl_t enumeration)
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
    return (bool)(CCM_ANALOG_TUPLE_REG(base, pllControl) & CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_LOCK_MASK);
}

/*!
 * @brief Enable PLL clock
 *
 * @param base CCM_ANALOG base pointer.
 * @param pllClock PLL clock name (see @ref clock_pll_clke_t enumeration)
 */
static inline void CLOCK_EnableAnalogClock(CCM_ANALOG_Type *base, clock_pll_clke_t pllClock)
{
    CCM_ANALOG_TUPLE_REG(base, pllClock) |= 1UL << CCM_ANALOG_TUPLE_SHIFT(pllClock);
}

/*!
 * @brief Disable PLL clock
 *
 * @param base CCM_ANALOG base pointer.
 * @param pllClock PLL clock name (see @ref clock_pll_clke_t enumeration)
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
static inline void CLOCK_OverridePllClke(CCM_ANALOG_Type *base, clock_pll_clke_t ovClock, bool override)
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
 * @param config Pointer to the configuration structure(see @ref ccm_analog_integer_pll_config_t enumeration).
 *
 * @note This function can't detect whether the Arm PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitArmPll(const ccm_analog_integer_pll_config_t *config);

/*!
 * @brief De-initialize the ARM PLL.
 */
void CLOCK_DeinitArmPll(void);

/*!
 * @brief Initializes the ANALOG SYS PLL1.
 *
 * @param config Pointer to the configuration structure(see @ref ccm_analog_integer_pll_config_t enumeration).
 *
 * @note This function can't detect whether the SYS PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitSysPll1(const ccm_analog_integer_pll_config_t *config);

/*!
 * @brief De-initialize the System PLL1.
 */
void CLOCK_DeinitSysPll1(void);

/*!
 * @brief Initializes the ANALOG SYS PLL2.
 *
 * @param config Pointer to the configuration structure(see @ref ccm_analog_integer_pll_config_t enumeration).
 *
 * @note This function can't detect whether the SYS PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitSysPll2(const ccm_analog_integer_pll_config_t *config);

/*!
 * @brief De-initialize the System PLL2.
 */
void CLOCK_DeinitSysPll2(void);

/*!
 * @brief Initializes the ANALOG SYS PLL3.
 *
 * @param config Pointer to the configuration structure(see @ref ccm_analog_integer_pll_config_t enumeration).
 *
 * @note This function can't detect whether the SYS PLL has been enabled and
 * used by some IPs.
 */
void CLOCK_InitSysPll3(const ccm_analog_integer_pll_config_t *config);

/*!
 * @brief De-initialize the System PLL3.
 */
void CLOCK_DeinitSysPll3(void);

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
 * @brief Initializes the ANALOG Integer PLL.
 *
 * @param base CCM ANALOG base address
 * @param config Pointer to the configuration structure(see @ref ccm_analog_integer_pll_config_t enumeration).
 * @param type integer pll type
 *
 */
void CLOCK_InitIntegerPll(CCM_ANALOG_Type *base, const ccm_analog_integer_pll_config_t *config, clock_pll_ctrl_t type);

/*!
 * @brief Get the ANALOG Integer PLL clock frequency.
 *
 * @param base CCM ANALOG base address.
 * @param type integer pll type
 * @param refClkFreq Reference clock frequency.
 * @param pll1Bypass pll1 bypass flag
 *
 * @return  Clock frequency
 */
uint32_t CLOCK_GetIntegerPllFreq(CCM_ANALOG_Type *base, clock_pll_ctrl_t type, uint32_t refClkFreq, bool pll1Bypass);

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
 * @param refClkFreq Reference clock frequency.
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
 * @brief Get the CCM Cortex M7 core frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetCoreM7Freq(void);

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
