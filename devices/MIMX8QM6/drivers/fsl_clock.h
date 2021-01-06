/*
 * Copyright 2017-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#include "fsl_device_registers.h"
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "svc/pm/pm_api.h"

/*! @addtogroup clock */
/*! @{ */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Configure whether driver controls clock
 *
 * When set to 0, peripheral drivers will enable clock in initialize function
 * and disable clock in de-initialize function. When set to 1, peripheral
 * driver will not control the clock, application could control the clock out of
 * the driver.
 *
 * @note All drivers share this feature switcher. If it is set to 1, application
 * should handle clock enable and disable for all drivers.
 */
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL))
#define FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL 0
#endif

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.4.0. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 4, 0))
/*@}*/

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (400000000UL)
#endif

/*! @brief Clock ip name array for MU. */
#define MU_CLOCKS                                                                                                     \
    {                                                                                                                 \
        kCLOCK_M4_0_Mu0B, kCLOCK_M4_0_Mu0B, kCLOCK_M4_0_Mu0B, kCLOCK_M4_0_Mu0B, kCLOCK_M4_0_Mu0A0, kCLOCK_M4_0_Mu0A1, \
            kCLOCK_M4_0_Mu0A2, kCLOCK_M4_0_Mu0A3, kCLOCK_M4_0_Mu1A, kCLOCK_M4_1_Mu0B, kCLOCK_M4_1_Mu0B,               \
            kCLOCK_M4_1_Mu0B, kCLOCK_M4_1_Mu0B, kCLOCK_M4_1_Mu0A0, kCLOCK_M4_1_Mu0A1, kCLOCK_M4_1_Mu0A2,              \
            kCLOCK_M4_1_Mu0A3, kCLOCK_M4_1_Mu1A, kCLOCK_LSIO_Mu0A, kCLOCK_LSIO_Mu1A, kCLOCK_LSIO_Mu2A,                \
            kCLOCK_LSIO_Mu3A, kCLOCK_LSIO_Mu4A, kCLOCK_LSIO_Mu5A, kCLOCK_LSIO_Mu6A, kCLOCK_LSIO_Mu7A,                 \
            kCLOCK_LSIO_Mu8A, kCLOCK_LSIO_Mu9A, kCLOCK_LSIO_Mu10A, kCLOCK_LSIO_Mu11A, kCLOCK_LSIO_Mu12A,              \
            kCLOCK_LSIO_Mu13A, kCLOCK_LSIO_Mu5B, kCLOCK_LSIO_Mu6B, kCLOCK_LSIO_Mu7B, kCLOCK_LSIO_Mu8B,                \
            kCLOCK_LSIO_Mu9B, kCLOCK_LSIO_Mu10B, kCLOCK_LSIO_Mu11B, kCLOCK_LSIO_Mu12B, kCLOCK_LSIO_Mu13B,             \
    }

/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS                                                                                                 \
    {                                                                                                               \
        kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_HSIO_Gpio, \
            kCLOCK_LSIO_Gpio0, kCLOCK_LSIO_Gpio1, kCLOCK_LSIO_Gpio2, kCLOCK_LSIO_Gpio3, kCLOCK_LSIO_Gpio4,          \
            kCLOCK_LSIO_Gpio5, kCLOCK_LSIO_Gpio6, kCLOCK_LSIO_Gpio7, kCLOCK_IpInvalid, kCLOCK_IpInvalid,            \
            kCLOCK_IpInvalid,                                                                                       \
    }

/*! @brief Clock ip name array for RGPIO. */
#define RGPIO_CLOCKS                          \
    {                                         \
        kCLOCK_M4_0_Rgpio, kCLOCK_M4_1_Rgpio, \
    }

/*! @brief Clock ip name array for FTM. */
#define FTM_CLOCKS                        \
    {                                     \
        kCLOCK_DMA_Ftm0, kCLOCK_DMA_Ftm1, \
    }

/*! @brief Clock ip name array for GPT. */
#define GPT_CLOCKS                                                                                     \
    {                                                                                                  \
        kCLOCK_AUDIO_Gpt0, kCLOCK_AUDIO_Gpt1, kCLOCK_AUDIO_Gpt2, kCLOCK_AUDIO_Gpt3, kCLOCK_AUDIO_Gpt4, \
            kCLOCK_AUDIO_Gpt5, kCLOCK_LSIO_Gpt0, kCLOCK_LSIO_Gpt1, kCLOCK_LSIO_Gpt2, kCLOCK_LSIO_Gpt3, \
            kCLOCK_LSIO_Gpt4,                                                                          \
    }
/*! @brief Clock ip name array for FLEXCAN. */
#define FLEXCAN_CLOCKS                                     \
    {                                                      \
        kCLOCK_DMA_Can0, kCLOCK_DMA_Can1, kCLOCK_DMA_Can2, \
    }
/*! @brief Clock ip name array for FLEXSPI. */
#define FLEXSPI_CLOCKS                              \
    {                                               \
        kCLOCK_LSIO_Flexspi0, kCLOCK_LSIO_Flexspi1, \
    }
/*! @brief Clock ip name array for LPUART. */
#define LPUART_CLOCKS                                                                                       \
    {                                                                                                       \
        kCLOCK_M4_0_Lpuart, kCLOCK_M4_1_Lpuart, kCLOCK_DMA_Lpuart0, kCLOCK_DMA_Lpuart1, kCLOCK_DMA_Lpuart2, \
            kCLOCK_DMA_Lpuart3, kCLOCK_DMA_Lpuart4, kCLOCK_SCU_Lpuart,                                      \
    }

/*! @brief Clock ip name array for LPADC. */
#define LPADC_CLOCKS                          \
    {                                         \
        kCLOCK_DMA_Lpadc0, kCLOCK_DMA_Lpadc1, \
    }

/*! @brief Clock ip name array for INTMUX. */
#define INTMUX_CLOCKS                                             \
    {                                                             \
        kCLOCK_M4_0_Intmux, kCLOCK_M4_1_Intmux, kCLOCK_IpInvalid, \
    }

/*! @brief Clock ip name array for SAI. */
#define SAI_CLOCKS                                                                                     \
    {                                                                                                  \
        kCLOCK_AUDIO_Sai0, kCLOCK_AUDIO_Sai1, kCLOCK_AUDIO_Sai2, kCLOCK_AUDIO_Sai3, kCLOCK_AUDIO_Sai4, \
            kCLOCK_AUDIO_Sai5, kCLOCK_AUDIO_Sai6, kCLOCK_AUDIO_Sai7,                                   \
    }

/*! @brief Clock ip name array for SEMA42. */
#define SEMA42_CLOCKS                                              \
    {                                                              \
        kCLOCK_M4_0_Sema42, kCLOCK_M4_1_Sema42, kCLOCK_SCU_Sema42, \
    }

/*! @brief Clock ip name array for TPM. */
#define TPM_CLOCKS                                        \
    {                                                     \
        kCLOCK_M4_0_Tpm, kCLOCK_M4_1_Tpm, kCLOCK_SCU_Tpm, \
    }

/*! @brief Clock ip name array for LPIT. */
#define LPIT_CLOCKS                                          \
    {                                                        \
        kCLOCK_M4_0_Lpit, kCLOCK_M4_1_Lpit, kCLOCK_SCU_Lpit, \
    }

/*! @brief Clock ip name array for LPI2C. */
#define LPI2C_CLOCKS                                                                                               \
    {                                                                                                              \
        kCLOCK_M4_0_Lpi2c, kCLOCK_M4_1_Lpi2c, kCLOCK_HDMI_Lpi2c0, kCLOCK_LVDS_0_Lpi2c1, kCLOCK_LVDS_0_Lpi2c0,      \
            kCLOCK_LVDS_1_Lpi2c1, kCLOCK_LVDS_1_Lpi2c0, kCLOCK_MIPI_0_Lpi2c0, kCLOCK_MIPI_0_Lpi2c1,                \
            kCLOCK_MIPI_1_Lpi2c0, kCLOCK_MIPI_1_Lpi2c1, kCLOCK_DMA_Lpi2c0, kCLOCK_DMA_Lpi2c1, kCLOCK_DMA_Lpi2c2,   \
            kCLOCK_DMA_Lpi2c3, kCLOCK_DMA_Lpi2c4, kCLOCK_CSI_0_Lpi2c0, kCLOCK_CSI_1_Lpi2c0, kCLOCK_HDMI_RX_Lpi2c0, \
            kCLOCK_SCU_Lpi2c,                                                                                      \
    }

/*! @brief Clock ip name array for LPSPI. */
#define LPSPI_CLOCKS                                                                \
    {                                                                               \
        kCLOCK_DMA_Lpspi0, kCLOCK_DMA_Lpspi1, kCLOCK_DMA_Lpspi2, kCLOCK_DMA_Lpspi3, \
    }
#if defined(MIMX8QM_CM4_CORE0)
#define IRQSTEER_CLOCKS       \
    {                         \
        kCLOCK_M4_0_Irqsteer, \
    }
#elif defined(MIMX8QM_CM4_CORE1)
#define IRQSTEER_CLOCKS       \
    {                         \
        kCLOCK_M4_1_Irqsteer, \
    }
#endif

/*! @brief Clock ip name array for EDMA. */
#define EDMA_CLOCKS      \
    {                    \
        kCLOCK_DMA_Dma0, \
    }

/*! @brief Clock ip name array for ESAI. */
#define ESAI_CLOCKS                            \
    {                                          \
        kCLOCK_AUDIO_Esai0, kCLOCK_AUDIO_Esai1 \
    }

/*! @brief Clock ip name array for ISI. */
#define ISI_CLOCKS                                                                                               \
    {                                                                                                            \
        kCLOCK_IMAGING_Isi0, kCLOCK_IMAGING_Isi1, kCLOCK_IMAGING_Isi2, kCLOCK_IMAGING_Isi3, kCLOCK_IMAGING_Isi4, \
            kCLOCK_IMAGING_Isi5, kCLOCK_IMAGING_Isi6, kCLOCK_IMAGING_Isi7,                                       \
    }

/*! @brief Clock ip name array for MIPI CSI2 RX. */
#define MIPI_CSI2RX_CLOCKS                     \
    {                                          \
        kCLOCK_MipiCsi2Rx0, kCLOCK_MipiCsi2Rx1 \
    }

/*! @brief Clock ip name array for MIPI DSI host. */
#define MIPI_DSI_HOST_CLOCKS                     \
    {                                            \
        kCLOCK_MipiDsiHost0, kCLOCK_MipiDsiHost1 \
    }

/*! @brief Clock ip name array for ENET. */
#define ENET_CLOCKS                                          \
    {                                                        \
        kCLOCK_CONNECTIVITY_Enet0, kCLOCK_CONNECTIVITY_Enet1 \
    }

/*! @brief Clock ip name array for EMVSIM. */
#define EMVSIM_CLOCKS                           \
    {                                           \
        kCLOCK_DMA_EmvSim0, kCLOCK_DMA_EmvSim1, \
    }

/*! @brief Clock ip name array for DPU. */
#define DPU_CLOCKS                \
    {                             \
        kCLOCK_Dpu0, kCLOCK_Dpu1, \
    }

/*! @brief Clock ip name array for LVDS display bridge(LDB). */
#define LDB_CLOCKS               \
    {                            \
        kCLOCK_Ldb0, kCLOCK_Ldb1 \
    }

/*!
 * @brief Clock source for peripherals that support various clock selections.
 */
typedef enum _clock_ip_src
{
    kCLOCK_IpSrcNone  = 0U, /*!< Clock is off. */
    kCLOCK_IpSrcDummy = 1U, /*!< Clock option 1. */
} clock_ip_src_t;

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{
    /* ----------------------------- System layer clock ---------------------- */
    kCLOCK_CoreSysClk, /*!< Core/system clock for M4                           */

    /* --------------------------------- Other clock ------------------------- */
    kCLOCK_CONECTIVITY_AhbClk, /*!< AHB clock in Connectivity subsystem        */
} clock_name_t;

/*!
 * @brief LPCG TUPLE macors to map corresponding ip clock name, SCFW API resource index and LPCG Register base address.
 * The LPCG base should be 4KB aligned, if not it will be truncated.
 */
#define LPCG_TUPLE(rsrc, base) ((uint32_t)((((base) >> 12U) << 10U) | (rsrc)))
/*! @brief Get the LPCG REG base address. */
#define LPCG_TUPLE_REG_BASE(tuple) ((volatile uint32_t *)((((uint32_t)(tuple) >> 10U) & 0xFFFFFU) << 12U))
/*! @brief Get the resource index. */
#define LPCG_TUPLE_RSRC(tuple) ((sc_rsrc_t)((uint32_t)(tuple)&0x3FFU))
/*! @brief LPCG Cell not available. */
#define NV (0U)

/*!
 * @brief Peripheral clock name difinition used for clock gate, clock source
 * and clock divider setting. It is defined as the corresponding register address.
 */
typedef enum _clock_ip_name
{
    kCLOCK_M4_0_Irqsteer      = LPCG_TUPLE(SC_R_IRQSTR_M4_0, NV),
    kCLOCK_M4_1_Irqsteer      = LPCG_TUPLE(SC_R_IRQSTR_M4_1, NV),
    kCLOCK_DMA_Lpspi0         = LPCG_TUPLE(SC_R_SPI_0, DMA__LPCG_LPSPI0_BASE),
    kCLOCK_DMA_Lpspi1         = LPCG_TUPLE(SC_R_SPI_1, DMA__LPCG_LPSPI1_BASE),
    kCLOCK_DMA_Lpspi2         = LPCG_TUPLE(SC_R_SPI_2, DMA__LPCG_LPSPI2_BASE),
    kCLOCK_DMA_Lpspi3         = LPCG_TUPLE(SC_R_SPI_3, DMA__LPCG_LPSPI3_BASE),
    kCLOCK_DMA_Lpuart0        = LPCG_TUPLE(SC_R_UART_0, DMA__LPCG_LPUART0_BASE),
    kCLOCK_DMA_Lpuart1        = LPCG_TUPLE(SC_R_UART_1, DMA__LPCG_LPUART1_BASE),
    kCLOCK_DMA_Lpuart2        = LPCG_TUPLE(SC_R_UART_2, DMA__LPCG_LPUART2_BASE),
    kCLOCK_DMA_Lpuart3        = LPCG_TUPLE(SC_R_UART_3, DMA__LPCG_LPUART3_BASE),
    kCLOCK_DMA_Lpuart4        = LPCG_TUPLE(SC_R_UART_4, DMA__LPCG_LPUART4_BASE),
    kCLOCK_DMA_EmvSim0        = LPCG_TUPLE(SC_R_EMVSIM_0, DMA__LPCG_EMV_SIM0_BASE),
    kCLOCK_DMA_EmvSim1        = LPCG_TUPLE(SC_R_EMVSIM_1, DMA__LPCG_EMV_SIM1_BASE),
    kCLOCK_DMA_Dma0           = LPCG_TUPLE(SC_R_DMA_0_CH0, NV),
    kCLOCK_DMA_Lpi2c0         = LPCG_TUPLE(SC_R_I2C_0, DMA__LPCG_LPI2C0_BASE),
    kCLOCK_DMA_Lpi2c1         = LPCG_TUPLE(SC_R_I2C_1, DMA__LPCG_LPI2C1_BASE),
    kCLOCK_DMA_Lpi2c2         = LPCG_TUPLE(SC_R_I2C_2, DMA__LPCG_LPI2C2_BASE),
    kCLOCK_DMA_Lpi2c3         = LPCG_TUPLE(SC_R_I2C_3, DMA__LPCG_LPI2C3_BASE),
    kCLOCK_DMA_Lpi2c4         = LPCG_TUPLE(SC_R_I2C_4, DMA__LPCG_LPI2C4_BASE),
    kCLOCK_DMA_Lpadc0         = LPCG_TUPLE(SC_R_ADC_0, DMA__LPCG_ADC0_BASE),
    kCLOCK_DMA_Lpadc1         = LPCG_TUPLE(SC_R_ADC_1, DMA__LPCG_ADC1_BASE),
    kCLOCK_DMA_Ftm0           = LPCG_TUPLE(SC_R_FTM_0, DMA__LPCG_FTM0_BASE),
    kCLOCK_DMA_Ftm1           = LPCG_TUPLE(SC_R_FTM_1, DMA__LPCG_FTM1_BASE),
    kCLOCK_DMA_Can0           = LPCG_TUPLE(SC_R_CAN_0, DMA__LPCG_CAN0_BASE),
    kCLOCK_DMA_Can1           = LPCG_TUPLE(SC_R_CAN_1, DMA__LPCG_CAN1_BASE),
    kCLOCK_DMA_Can2           = LPCG_TUPLE(SC_R_CAN_2, DMA__LPCG_CAN2_BASE),
    kCLOCK_HSIO_Gpio          = LPCG_TUPLE(SC_R_HSIO_GPIO, HSIO__LPCG_GPIO_BASE),
    kCLOCK_LVDS_0_Lpi2c0      = LPCG_TUPLE(SC_R_LVDS_0_I2C_0, DI_LVDS_0__LPCG_CLK_BASE),
    kCLOCK_LVDS_0_Lpi2c1      = LPCG_TUPLE(SC_R_LVDS_0_I2C_1, DI_LVDS_0__LPCG_CLK_BASE),
    kCLOCK_LVDS_1_Lpi2c0      = LPCG_TUPLE(SC_R_LVDS_1_I2C_0, DI_LVDS_1__LPCG_CLK_BASE),
    kCLOCK_LVDS_1_Lpi2c1      = LPCG_TUPLE(SC_R_LVDS_1_I2C_1, DI_LVDS_1__LPCG_CLK_BASE),
    kCLOCK_LSIO_Gpio0         = LPCG_TUPLE(SC_R_GPIO_0, LSIO__LPCG_GPIO0_BASE),
    kCLOCK_LSIO_Gpio1         = LPCG_TUPLE(SC_R_GPIO_1, LSIO__LPCG_GPIO1_BASE),
    kCLOCK_LSIO_Gpio2         = LPCG_TUPLE(SC_R_GPIO_2, LSIO__LPCG_GPIO2_BASE),
    kCLOCK_LSIO_Gpio3         = LPCG_TUPLE(SC_R_GPIO_3, LSIO__LPCG_GPIO3_BASE),
    kCLOCK_LSIO_Gpio4         = LPCG_TUPLE(SC_R_GPIO_4, LSIO__LPCG_GPIO4_BASE),
    kCLOCK_LSIO_Gpio5         = LPCG_TUPLE(SC_R_GPIO_5, LSIO__LPCG_GPIO5_BASE),
    kCLOCK_LSIO_Gpio6         = LPCG_TUPLE(SC_R_GPIO_6, LSIO__LPCG_GPIO6_BASE),
    kCLOCK_LSIO_Gpio7         = LPCG_TUPLE(SC_R_GPIO_7, LSIO__LPCG_GPIO7_BASE),
    kCLOCK_AUDIO_Gpt0         = LPCG_TUPLE(SC_R_GPT_5, AUDIO__LPCG_GPT0_BASE),
    kCLOCK_AUDIO_Gpt1         = LPCG_TUPLE(SC_R_GPT_6, AUDIO__LPCG_GPT1_BASE),
    kCLOCK_AUDIO_Gpt2         = LPCG_TUPLE(SC_R_GPT_7, AUDIO__LPCG_GPT2_BASE),
    kCLOCK_AUDIO_Gpt3         = LPCG_TUPLE(SC_R_GPT_8, AUDIO__LPCG_GPT3_BASE),
    kCLOCK_AUDIO_Gpt4         = LPCG_TUPLE(SC_R_GPT_9, AUDIO__LPCG_GPT4_BASE),
    kCLOCK_AUDIO_Gpt5         = LPCG_TUPLE(SC_R_GPT_10, AUDIO__LPCG_GPT5_BASE),
    kCLOCK_LSIO_Gpt0          = LPCG_TUPLE(SC_R_GPT_0, LSIO__LPCG_GPT0_BASE),
    kCLOCK_LSIO_Gpt1          = LPCG_TUPLE(SC_R_GPT_1, LSIO__LPCG_GPT1_BASE),
    kCLOCK_LSIO_Gpt2          = LPCG_TUPLE(SC_R_GPT_2, LSIO__LPCG_GPT2_BASE),
    kCLOCK_LSIO_Gpt3          = LPCG_TUPLE(SC_R_GPT_3, LSIO__LPCG_GPT3_BASE),
    kCLOCK_LSIO_Gpt4          = LPCG_TUPLE(SC_R_GPT_4, LSIO__LPCG_GPT4_BASE),
    kCLOCK_LSIO_Mu0A          = LPCG_TUPLE(SC_R_MU_0A, NV),
    kCLOCK_LSIO_Mu1A          = LPCG_TUPLE(SC_R_MU_1A, NV),
    kCLOCK_LSIO_Mu2A          = LPCG_TUPLE(SC_R_MU_2A, NV),
    kCLOCK_LSIO_Mu3A          = LPCG_TUPLE(SC_R_MU_3A, NV),
    kCLOCK_LSIO_Mu4A          = LPCG_TUPLE(SC_R_MU_4A, NV),
    kCLOCK_LSIO_Mu5A          = LPCG_TUPLE(SC_R_MU_5A, LSIO__LPCG_MU5_MCU_BASE),
    kCLOCK_LSIO_Mu6A          = LPCG_TUPLE(SC_R_MU_6A, LSIO__LPCG_MU6_MCU_BASE),
    kCLOCK_LSIO_Mu7A          = LPCG_TUPLE(SC_R_MU_7A, LSIO__LPCG_MU7_MCU_BASE),
    kCLOCK_LSIO_Mu8A          = LPCG_TUPLE(SC_R_MU_8A, LSIO__LPCG_MU8_MCU_BASE),
    kCLOCK_LSIO_Mu9A          = LPCG_TUPLE(SC_R_MU_9A, LSIO__LPCG_MU9_MCU_BASE),
    kCLOCK_LSIO_Mu10A         = LPCG_TUPLE(SC_R_MU_10A, LSIO__LPCG_MU10_MCU_BASE),
    kCLOCK_LSIO_Mu11A         = LPCG_TUPLE(SC_R_MU_11A, LSIO__LPCG_MU11_MCU_BASE),
    kCLOCK_LSIO_Mu12A         = LPCG_TUPLE(SC_R_MU_12A, LSIO__LPCG_MU12_MCU_BASE),
    kCLOCK_LSIO_Mu13A         = LPCG_TUPLE(SC_R_MU_13A, LSIO__LPCG_MU13_MCU_BASE),
    kCLOCK_LSIO_Mu5B          = LPCG_TUPLE(SC_R_MU_5B, LSIO__LPCG_MU5_DSP_BASE),
    kCLOCK_LSIO_Mu6B          = LPCG_TUPLE(SC_R_MU_6B, LSIO__LPCG_MU6_DSP_BASE),
    kCLOCK_LSIO_Mu7B          = LPCG_TUPLE(SC_R_MU_7B, LSIO__LPCG_MU7_DSP_BASE),
    kCLOCK_LSIO_Mu8B          = LPCG_TUPLE(SC_R_MU_8B, LSIO__LPCG_MU8_DSP_BASE),
    kCLOCK_LSIO_Mu9B          = LPCG_TUPLE(SC_R_MU_9B, LSIO__LPCG_MU9_DSP_BASE),
    kCLOCK_LSIO_Mu10B         = LPCG_TUPLE(SC_R_MU_10B, LSIO__LPCG_MU10_DSP_BASE),
    kCLOCK_LSIO_Mu11B         = LPCG_TUPLE(SC_R_MU_11B, LSIO__LPCG_MU11_DSP_BASE),
    kCLOCK_LSIO_Mu12B         = LPCG_TUPLE(SC_R_MU_12B, LSIO__LPCG_MU12_DSP_BASE),
    kCLOCK_LSIO_Mu13B         = LPCG_TUPLE(SC_R_MU_13B, LSIO__LPCG_MU13_DSP_BASE),
    kCLOCK_LSIO_Flexspi0      = LPCG_TUPLE(SC_R_FSPI_0, LSIO__LPCG_QSPI0_BASE),
    kCLOCK_LSIO_Flexspi1      = LPCG_TUPLE(SC_R_FSPI_1, LSIO__LPCG_QSPI1_BASE),
    kCLOCK_M4_0_Rgpio         = LPCG_TUPLE(SC_R_M4_0_RGPIO, NV),
    kCLOCK_M4_0_Sema42        = LPCG_TUPLE(SC_R_M4_0_SEMA42, NV),
    kCLOCK_M4_0_Tpm           = LPCG_TUPLE(SC_R_M4_0_TPM, CM4_0__LPCG_TPM_BASE),
    kCLOCK_M4_0_Lpit          = LPCG_TUPLE(SC_R_M4_0_PIT, CM4_0__LPCG_LPIT_BASE),
    kCLOCK_M4_0_Lpuart        = LPCG_TUPLE(SC_R_M4_0_UART, CM4_0__LPCG_LPUART_BASE),
    kCLOCK_M4_0_Lpi2c         = LPCG_TUPLE(SC_R_M4_0_I2C, CM4_0__LPCG_LPI2C_BASE),
    kCLOCK_M4_0_Intmux        = LPCG_TUPLE(SC_R_M4_0_INTMUX, NV),
    kCLOCK_M4_0_Mu0B          = LPCG_TUPLE(SC_R_M4_0_MU_0B, NV),
    kCLOCK_M4_0_Mu0A0         = LPCG_TUPLE(SC_R_M4_0_MU_0A0, NV),
    kCLOCK_M4_0_Mu0A1         = LPCG_TUPLE(SC_R_M4_0_MU_0A1, NV),
    kCLOCK_M4_0_Mu0A2         = LPCG_TUPLE(SC_R_M4_0_MU_0A2, NV),
    kCLOCK_M4_0_Mu0A3         = LPCG_TUPLE(SC_R_M4_0_MU_0A3, NV),
    kCLOCK_M4_0_Mu1A          = LPCG_TUPLE(SC_R_M4_0_MU_1A, NV),
    kCLOCK_M4_1_Rgpio         = LPCG_TUPLE(SC_R_M4_1_RGPIO, NV),
    kCLOCK_M4_1_Sema42        = LPCG_TUPLE(SC_R_M4_1_SEMA42, NV),
    kCLOCK_M4_1_Tpm           = LPCG_TUPLE(SC_R_M4_1_TPM, CM4_1__LPCG_TPM_BASE),
    kCLOCK_M4_1_Lpit          = LPCG_TUPLE(SC_R_M4_1_PIT, CM4_1__LPCG_LPIT_BASE),
    kCLOCK_M4_1_Lpuart        = LPCG_TUPLE(SC_R_M4_1_UART, CM4_1__LPCG_LPUART_BASE),
    kCLOCK_SCU_Lpuart         = LPCG_TUPLE(SC_R_SC_UART, SCU__LPCG_LPUART_BASE),
    kCLOCK_M4_1_Lpi2c         = LPCG_TUPLE(SC_R_M4_1_I2C, CM4_1__LPCG_LPI2C_BASE),
    kCLOCK_M4_1_Intmux        = LPCG_TUPLE(SC_R_M4_1_INTMUX, NV),
    kCLOCK_M4_1_Mu0B          = LPCG_TUPLE(SC_R_M4_1_MU_0B, NV),
    kCLOCK_M4_1_Mu0A0         = LPCG_TUPLE(SC_R_M4_1_MU_0A0, NV),
    kCLOCK_M4_1_Mu0A1         = LPCG_TUPLE(SC_R_M4_1_MU_0A1, NV),
    kCLOCK_M4_1_Mu0A2         = LPCG_TUPLE(SC_R_M4_1_MU_0A2, NV),
    kCLOCK_M4_1_Mu0A3         = LPCG_TUPLE(SC_R_M4_1_MU_0A3, NV),
    kCLOCK_M4_1_Mu1A          = LPCG_TUPLE(SC_R_M4_1_MU_1A, NV),
    kCLOCK_SCU_Lpi2c          = LPCG_TUPLE(SC_R_SC_I2C, SCU__LPCG_LPI2C_BASE),
    kCLOCK_SCU_Sema42         = LPCG_TUPLE(SC_R_SC_SEMA42, NV),
    kCLOCK_SCU_Lpit           = LPCG_TUPLE(SC_R_SC_PIT, SCU__LPCG_LPIT_BASE),
    kCLOCK_SCU_Tpm            = LPCG_TUPLE(SC_R_SC_TPM, SCU__LPCG_TPM_BASE),
    kCLOCK_AUDIO_Sai0         = LPCG_TUPLE(SC_R_SAI_0, AUDIO__LPCG_SAI0_BASE),
    kCLOCK_AUDIO_Sai1         = LPCG_TUPLE(SC_R_SAI_1, AUDIO__LPCG_SAI1_BASE),
    kCLOCK_AUDIO_Sai2         = LPCG_TUPLE(SC_R_SAI_2, AUDIO__LPCG_SAI2_BASE),
    kCLOCK_AUDIO_Sai3         = LPCG_TUPLE(SC_R_SAI_3, AUDIO__LPCG_SAI3_BASE),
    kCLOCK_AUDIO_Sai4         = LPCG_TUPLE(SC_R_SAI_4, AUDIO__LPCG_SAI_HDMIRX0_BASE),
    kCLOCK_AUDIO_Sai5         = LPCG_TUPLE(SC_R_SAI_5, AUDIO__LPCG_SAI_HDMITX0_BASE),
    kCLOCK_AUDIO_Sai6         = LPCG_TUPLE(SC_R_SAI_6, AUDIO__LPCG_SAI6_BASE),
    kCLOCK_AUDIO_Sai7         = LPCG_TUPLE(SC_R_SAI_7, AUDIO__LPCG_SAI7_BASE),
    kCLOCK_AUDIO_Esai0        = LPCG_TUPLE(SC_R_ESAI_0, AUDIO__LPCG_ESAI0_BASE),
    kCLOCK_AUDIO_Esai1        = LPCG_TUPLE(SC_R_ESAI_1, AUDIO__LPCG_ESAI1_BASE),
    kCLOCK_IMAGING_Isi0       = LPCG_TUPLE(SC_R_ISI_CH0, NV),
    kCLOCK_IMAGING_Isi1       = LPCG_TUPLE(SC_R_ISI_CH1, NV),
    kCLOCK_IMAGING_Isi2       = LPCG_TUPLE(SC_R_ISI_CH2, NV),
    kCLOCK_IMAGING_Isi3       = LPCG_TUPLE(SC_R_ISI_CH3, NV),
    kCLOCK_IMAGING_Isi4       = LPCG_TUPLE(SC_R_ISI_CH4, NV),
    kCLOCK_IMAGING_Isi5       = LPCG_TUPLE(SC_R_ISI_CH5, NV),
    kCLOCK_IMAGING_Isi6       = LPCG_TUPLE(SC_R_ISI_CH6, NV),
    kCLOCK_IMAGING_Isi7       = LPCG_TUPLE(SC_R_ISI_CH7, NV),
    kCLOCK_MIPI_0_Lpi2c0      = LPCG_TUPLE(SC_R_MIPI_0_I2C_0, DI_MIPI_0__LPCG_CLK_BASE),
    kCLOCK_MIPI_0_Lpi2c1      = LPCG_TUPLE(SC_R_MIPI_0_I2C_1, DI_MIPI_0__LPCG_CLK_BASE),
    kCLOCK_MIPI_1_Lpi2c0      = LPCG_TUPLE(SC_R_MIPI_1_I2C_0, DI_MIPI_1__LPCG_CLK_BASE),
    kCLOCK_MIPI_1_Lpi2c1      = LPCG_TUPLE(SC_R_MIPI_1_I2C_1, DI_MIPI_1__LPCG_CLK_BASE),
    kCLOCK_CSI_0_Lpi2c0       = LPCG_TUPLE(SC_R_CSI_0_I2C_0, MIPI_CSI_0__LPCG_CLK_BASE),
    kCLOCK_CSI_1_Lpi2c0       = LPCG_TUPLE(SC_R_CSI_1_I2C_0, MIPI_CSI_1__LPCG_CLK_BASE),
    kCLOCK_Dpu0               = LPCG_TUPLE(SC_R_DC_0, DC_0__LPCG_DSP0_CLK_BASE),
    kCLOCK_Dpu1               = LPCG_TUPLE(SC_R_DC_1, DC_1__LPCG_DSP0_CLK_BASE),
    kCLOCK_HDMI_Lpi2c0        = LPCG_TUPLE(SC_R_HDMI_I2C_0, DI_HDMI__LPCG_CLK_BASE),
    kCLOCK_HDMI_RX_Lpi2c0     = LPCG_TUPLE(SC_R_HDMI_RX_I2C_0, RX_HDMI__LPCG_GPIO_IPG_CLK_S_BASE),
    kCLOCK_MipiCsi2Rx0        = LPCG_TUPLE(SC_R_CSI_0, MIPI_CSI_0__LPCG_CLK_BASE),
    kCLOCK_MipiCsi2Rx1        = LPCG_TUPLE(SC_R_CSI_1, MIPI_CSI_1__LPCG_CLK_BASE),
    kCLOCK_MipiDsiHost0       = LPCG_TUPLE(SC_R_MIPI_0, DI_MIPI_0__LPCG_CLK_BASE),
    kCLOCK_MipiDsiHost1       = LPCG_TUPLE(SC_R_MIPI_1, DI_MIPI_1__LPCG_CLK_BASE),
    kCLOCK_Ldb0               = LPCG_TUPLE(SC_R_LVDS_0, NV),
    kCLOCK_Ldb1               = LPCG_TUPLE(SC_R_LVDS_1, NV),
    kCLOCK_CONNECTIVITY_Enet0 = LPCG_TUPLE(SC_R_ENET_0, CONNECTIVITY__LPCG_ENET0_BASE),
    kCLOCK_CONNECTIVITY_Enet1 = LPCG_TUPLE(SC_R_ENET_1, CONNECTIVITY__LPCG_ENET1_BASE),
    kCLOCK_AUDIO_Pll0         = LPCG_TUPLE(SC_R_AUDIO_PLL_0, NV),
    kCLOCK_AUDIO_Pll1         = LPCG_TUPLE(SC_R_AUDIO_PLL_1, NV),
    kCLOCK_IpInvalid          = LPCG_TUPLE(SC_R_LAST, NV) /* The selected IP does not support clock control. */
} clock_ip_name_t;

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @brief Initialize Clock module.
 *
 * @param ipc  IPC handle for communication with SCU, see sc_ipc_t.
 */
void CLOCK_Init(sc_ipc_t ipc);

/*!
 * @brief Deinitialize Clock module.
 */
void CLOCK_Deinit(void);

/*!
 * @brief Enable the clock for specific IP, with gate setting.
 *
 * @param name  Which clock to enable, see \ref clock_ip_name_t.
 * @param gate  0: clock always on, 1: HW auto clock gating.
 * @return true if success, false if failure.
 */
bool CLOCK_EnableClockExt(clock_ip_name_t name, uint32_t gate);

/*!
 * @brief Enable the clock for specific IP.
 *
 * @param name  Which clock to enable, see \ref clock_ip_name_t.
 * @return true for success, false for failure.
 */
static inline bool CLOCK_EnableClock(clock_ip_name_t name)
{
    return CLOCK_EnableClockExt(name, 0);
}

/*!
 * @brief Disable the clock for specific IP.
 *
 * @param name  Which clock to disable, see \ref clock_ip_name_t.
 * @return true for success, false for failure.
 */
bool CLOCK_DisableClock(clock_ip_name_t name);

/*!
 * @brief Set the clock frequency for specific IP module.
 *
 * This function sets the IP module clock frequency.
 *
 * @param name Which peripheral to check, see \ref clock_ip_name_t.
 * @param freq Target clock frequency value in hertz.
 * @return the Real clock frequency value in hertz, or 0 if failed
 */
uint32_t CLOCK_SetIpFreq(clock_ip_name_t name, uint32_t freq);

/*!
 * @brief Get the clock frequency for a specific IP module.
 *
 * This function gets the IP module clock frequency.
 *
 * @param name Which peripheral to get, see \ref clock_ip_name_t.
 * @return Clock frequency value in hertz, or 0 if failed
 */
uint32_t CLOCK_GetIpFreq(clock_ip_name_t name);

/*!
 * @brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_name_t.
 *
 * @param name Clock names defined in clock_name_t
 * @return Clock frequency value in hertz
 */
uint32_t CLOCK_GetFreq(clock_name_t name);

/*!
 * @brief Get the core clock or system clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetCoreSysClkFreq(void);

/*!
 * @brief Config the LPCG cell for specific IP.
 *
 * @param name  Which clock to enable, see \ref clock_ip_name_t.
 * @param swGate Software clock gating. false: clock is gated;  true: clock is enabled
 * @param hwGate Hardware auto gating. false: disable the HW clock gate control;  true: HW clock gating is enabled
 */
void CLOCK_ConfigLPCG(clock_ip_name_t name, bool swGate, bool hwGate);

/*!
 * @brief Set LPCG gate for specific LPCG.
 *
 * @param regBase LPCG register base address.
 * @param swGate Software clock gating. false: clock is gated;  true: clock is enabled
 * @param hwGate Hardware auto gating. false: disable the HW clock gate control;  true: HW clock gating is enabled
 * @param bitsMask The available bits in LPCG register. Each bit indicate the corresponding bit is available or not.
 */
void CLOCK_SetLpcgGate(volatile uint32_t *regBase, bool swGate, bool hwGate, uint32_t bitsMask);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
