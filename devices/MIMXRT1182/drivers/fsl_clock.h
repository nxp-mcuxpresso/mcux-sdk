/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#include "fsl_common.h"

/*! @addtogroup clock */
/*! @{ */

/*! @file */

/*******************************************************************************
 * Configurations
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

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 1, 2))

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#if __CORTEX_M == 7
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (800000000UL)
#else
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (240000000UL)
#endif
#endif

/*@}*/

/*!
 * @brief CCM registers offset.
 */
#define CCSR_OFFSET   0x0C
#define CBCDR_OFFSET  0x14
#define CBCMR_OFFSET  0x18
#define CSCMR1_OFFSET 0x1C
#define CSCMR2_OFFSET 0x20
#define CSCDR1_OFFSET 0x24
#define CDCDR_OFFSET  0x30
#define CSCDR2_OFFSET 0x38
#define CSCDR3_OFFSET 0x3C
#define CACRR_OFFSET  0x10
#define CS1CDR_OFFSET 0x28
#define CS2CDR_OFFSET 0x2C

/*!
 * @brief CCM Analog registers offset.
 */
#define ARM_PLL_OFFSET   0x00
#define PLL_SYS_OFFSET   0x30
#define PLL_USB1_OFFSET  0x10
#define PLL_AUDIO_OFFSET 0x70
#define PLL_VIDEO_OFFSET 0xA0
#define PLL_ENET_OFFSET  0xE0
#define PLL_USB2_OFFSET  0x20

#define CCM_TUPLE(reg, shift, mask, busyShift) \
    (int)((reg & 0xFFU) | ((shift) << 8U) | ((((mask) >> (shift)) & 0x1FFFU) << 13U) | ((busyShift) << 26U))
#define CCM_TUPLE_REG(base, tuple)  (*((volatile uint32_t *)(((uint32_t)(base)) + ((tuple)&0xFFU))))
#define CCM_TUPLE_SHIFT(tuple)      (((tuple) >> 8U) & 0x1FU)
#define CCM_TUPLE_MASK(tuple)       ((uint32_t)((((tuple) >> 13U) & 0x1FFFU) << ((((tuple) >> 8U) & 0x1FU))))
#define CCM_TUPLE_BUSY_SHIFT(tuple) (((tuple) >> 26U) & 0x3FU)

#define CCM_BUSY_WAIT (0x20U)

/*!
 * @brief CCM ANALOG tuple macros to map corresponding registers and bit fields.
 */
#define CCM_ANALOG_TUPLE(reg, shift)  (((reg & 0xFFFU) << 16U) | (shift))
#define CCM_ANALOG_TUPLE_SHIFT(tuple) (((uint32_t)tuple) & 0x1FU)
#define CCM_ANALOG_TUPLE_REG_OFF(base, tuple, off) \
    (*((volatile uint32_t *)((uint32_t)base + (((uint32_t)tuple >> 16U) & 0xFFFU) + off)))
#define CCM_ANALOG_TUPLE_REG(base, tuple) CCM_ANALOG_TUPLE_REG_OFF(base, tuple, 0U)

/*!
 * @brief SYS_PLL_FREQ frequency in Hz.
 */
#define PLL_SYS1_1G_FREQ  (1000000000UL)
#define PLL_SYS2_528_MFI  (22UL)
#define PLL_SYS2_528_FREQ (XTAL_FREQ * PLL_SYS2_528_MFI)
#define PLL_SYS3_480_MFI  (20UL)
#define PLL_SYS3_480_FREQ (XTAL_FREQ * PLL_SYS3_480_MFI)
#define XTAL_FREQ         (24000000UL)

/*! @brief Clock gate name array for LPADC. */
#define LPADC_CLOCKS                               \
    {                                              \
        kCLOCK_IpInvalid, kCLOCK_Adc1, kCLOCK_Adc2 \
    }

/*! @brief Clock gate name array for AOI. */
#define AOI_CLOCKS                                                           \
    {                                                                        \
        kCLOCK_IpInvalid, kCLOCK_Aoi1, kCLOCK_Aoi2, kCLOCK_Aoi3, kCLOCK_Aoi4 \
    }

/*! @brief Clock ip name array for ASRC. */
#define ASRC_CLOCKS \
    {               \
        kCLOCK_Asrc \
    }

/*! @brief Clock ip name array for CMP. */
#define CMP_CLOCKS                                                               \
    {                                                                            \
        kCLOCK_IpInvalid, kCLOCK_Acmp1, kCLOCK_Acmp2, kCLOCK_Acmp3, kCLOCK_Acmp4 \
    }

/*! @brief Clock ip name array for DAC. */
#define DAC_CLOCKS \
    {              \
        kCLOCK_Dac \
    }

/*! @brief Clock gate name array for DCDC. */
#define DCDC_CLOCKS \
    {               \
        kCLOCK_Dcdc \
    }

/*! @brief Clock ip name array for ECAT. */
#define ECAT_CLOCKS \
    {               \
        kCLOCK_ECAT \
    }

/*! @brief Clock gate name array for EDMA. */
#define EDMA_CLOCKS                                  \
    {                                                \
        kCLOCK_IpInvalid, kCLOCK_Edma1, kCLOCK_Edma2 \
    }

/*! @brief Clock ip name array for ENC. */
#define ENC_CLOCKS                                                           \
    {                                                                        \
        kCLOCK_IpInvalid, kCLOCK_Enc1, kCLOCK_Enc2, kCLOCK_Enc3, kCLOCK_Enc4 \
    }

/*! @brief Clock gate name array for EWM. */
#define EWM_CLOCKS  \
    {               \
        kCLOCK_Ewm0 \
    }

/*! @brief Clock ip name array for FLEXCAN. */
#define FLEXCAN_CLOCKS                                          \
    {                                                           \
        kCLOCK_IpInvalid, kCLOCK_Can1, kCLOCK_Can2, kCLOCK_Can3 \
    }

/*! @brief Clock ip name array for FLEXIO. */
#define FLEXIO_CLOCKS                                    \
    {                                                    \
        kCLOCK_IpInvalid, kCLOCK_Flexio1, kCLOCK_Flexio2 \
    }

/*! @brief Clock gate name array for FLEXSPI. */
#define FLEXSPI_CLOCKS                                     \
    {                                                      \
        kCLOCK_IpInvalid, kCLOCK_Flexspi1, kCLOCK_Flexspi2 \
    }

/*! @brief Clock gate name array for FLEXSPI_SLV. */
#define FLEXSPI_SLV_CLOCKS \
    {                      \
        kCLOCK_Flexspi_Slv \
    }

/*! @brief Clock gate name array for GPC. */
#define GPC_CLOCKS \
    {              \
        kCLOCK_Gpc \
    }

/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS                                                                                          \
    {                                                                                                        \
        kCLOCK_IpInvalid, kCLOCK_Gpio1, kCLOCK_Gpio2, kCLOCK_Gpio3, kCLOCK_Gpio4, kCLOCK_Gpio5, kCLOCK_Gpio6 \
    }

/*! @brief Clock ip name array for GPT. */
#define GPT_CLOCKS                                 \
    {                                              \
        kCLOCK_IpInvalid, kCLOCK_Gpt1, kCLOCK_Gpt2 \
    }

/*! @brief Clock ip name array for I3C. */
#define I3C_CLOCKS                                 \
    {                                              \
        kCLOCK_IpInvalid, kCLOCK_I3c1, kCLOCK_I3c2 \
    }

/*! @brief Clock ip name array for IEE. */
#define IEE_CLOCKS \
    {              \
        kCLOCK_Iee \
    }

/*! @brief Clock ip name array for KPP. */
#define KPP_CLOCKS \
    {              \
        kCLOCK_Kpp \
    }

/*! @brief Clock ip name array for LPI2C. */
#define LPI2C_CLOCKS                                                                                               \
    {                                                                                                              \
        kCLOCK_IpInvalid, kCLOCK_Lpi2c1, kCLOCK_Lpi2c2, kCLOCK_Lpi2c3, kCLOCK_Lpi2c4, kCLOCK_Lpi2c5, kCLOCK_Lpi2c6 \
    }

/*! @brief Clock ip name array for LPIT. */
#define LPIT_CLOCKS                                                \
    {                                                              \
        kCLOCK_IpInvalid, kCLOCK_Lpit1, kCLOCK_Lpit2, kCLOCK_Lpit3 \
    }

/*! @brief Clock ip name array for LPSPI. */
#define LPSPI_CLOCKS                                                                                               \
    {                                                                                                              \
        kCLOCK_IpInvalid, kCLOCK_Lpspi1, kCLOCK_Lpspi2, kCLOCK_Lpspi3, kCLOCK_Lpspi4, kCLOCK_Lpspi5, kCLOCK_Lpspi6 \
    }

/*! @brief Clock ip name array for LPTMR. */
#define LPTMR_CLOCKS                                                  \
    {                                                                 \
        kCLOCK_IpInvalid, kCLOCK_Lptmr1, kCLOCK_Lptmr2, kCLOCK_Lptmr3 \
    }

/*! @brief Clock ip name array for LPUART. */
#define LPUART_CLOCKS                                                                                         \
    {                                                                                                         \
        kCLOCK_IpInvalid, kCLOCK_Lpuart1, kCLOCK_Lpuart2, kCLOCK_Lpuart3, kCLOCK_Lpuart4, kCLOCK_Lpuart5,     \
            kCLOCK_Lpuart6, kCLOCK_Lpuart7, kCLOCK_Lpuart8, kCLOCK_Lpuart9, kCLOCK_Lpuart10, kCLOCK_Lpuart11, \
            kCLOCK_Lpuart12                                                                                   \
    }

/*! @brief Clock ip name array for MIC. */
#define PDM_CLOCKS \
    {              \
        kCLOCK_Pdm \
    }

/*! @brief Clock gate name array for MU. */
#if (__CORTEX_M == 33)
#define MU_CLOCKS                \
    {                            \
        kCLOCK_Mu_A, kCLOCK_Mu_A \
    }
#else
#define MU_CLOCKS                \
    {                            \
        kCLOCK_Mu_B, kCLOCK_Mu_B \
    }
#endif

/*! @brief Clock ip name array for NETC. */
#define NETC_CLOCKS \
    {               \
        kCLOCK_Netc \
    }

/*! @brief Clock ip name array for OCOTP. */
#define OCOTP_CLOCKS \
    {                \
        kCLOCK_Ocotp \
    }

/*! @brief Clock ip name array for PWM. */
#define PWM_CLOCKS                                                                \
    {                                                                             \
        {kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_IpInvalid}, \
            {kCLOCK_Pwm1, kCLOCK_Pwm1, kCLOCK_Pwm1, kCLOCK_Pwm1},                 \
            {kCLOCK_Pwm2, kCLOCK_Pwm2, kCLOCK_Pwm2, kCLOCK_Pwm2},                 \
            {kCLOCK_Pwm3, kCLOCK_Pwm3, kCLOCK_Pwm3, kCLOCK_Pwm3},                 \
        {                                                                         \
            kCLOCK_Pwm4, kCLOCK_Pwm4, kCLOCK_Pwm4, kCLOCK_Pwm4                    \
        }                                                                         \
    }

/*! @brief Clock ip name array for SAI. */
#define SAI_CLOCKS                                                           \
    {                                                                        \
        kCLOCK_IpInvalid, kCLOCK_Sai1, kCLOCK_Sai2, kCLOCK_Sai3, kCLOCK_Sai4 \
    }

/*! @brief Clock gate name array for Sema. */
#define SEMA42_CLOCKS                                  \
    {                                                \
        kCLOCK_IpInvalid, kCLOCK_Sema1, kCLOCK_Sema2 \
    }

/*! @brief Clock ip name array for SEMC. */
#define SEMC_CLOCKS \
    {               \
        kCLOCK_Semc \
    }

/*! @brief Clock ip name array for SERDES. */
#define SERDES_CLOCKS                                                    \
    {                                                                    \
        kCLOCK_IpInvalid, kCLOCK_Serdes1, kCLOCK_Serdes2, kCLOCK_Serdes3 \
    }

/*! @brief Clock ip name array for SINC. */
#define SINC_CLOCKS                                                \
    {                                                              \
        kCLOCK_IpInvalid, kCLOCK_Sinc1, kCLOCK_Sinc2, kCLOCK_Sinc3 \
    }

/*! @brief Clock ip name array for SPDIF. */
#define SPDIF_CLOCKS \
    {                \
        kCLOCK_Spdif \
    }

/*! @brief Clock gate name array for SRC. */
#define SRC_CLOCKS \
    {              \
        kCLOCK_Src \
    }

/*! @brief Clock ip name array for QTIMER. */
#define TMR_CLOCKS                                                                                        \
    {                                                                                                     \
        kCLOCK_IpInvalid, kCLOCK_Qtimer1, kCLOCK_Qtimer2, kCLOCK_Qtimer3, kCLOCK_Qtimer4, kCLOCK_Qtimer5, \
            kCLOCK_Qtimer6, kCLOCK_Qtimer7, kCLOCK_Qtimer8                                                \
    }

/*! @brief Clock ip name array for TPM. */
#define TPM_CLOCKS                                                                                     \
    {                                                                                                  \
        kCLOCK_IpInvalid, kCLOCK_Tpm1, kCLOCK_Tpm2, kCLOCK_Tpm3, kCLOCK_Tpm4, kCLOCK_Tpm5, kCLOCK_Tpm6 \
    }

/*! @brief Clock ip name array for USB. */
#define USB_CLOCKS \
    {              \
        kCLOCK_Usb \
    }

/*! @brief Clock ip name array for USDHC. */
#define USDHC_CLOCKS                                   \
    {                                                  \
        kCLOCK_IpInvalid, kCLOCK_Usdhc1, kCLOCK_Usdhc2 \
    }

/*! @brief Clock gate name array for WDOG. */
#define WDOG_CLOCKS                                                                            \
    {                                                                                          \
        kCLOCK_IpInvalid, kCLOCK_Wdog1, kCLOCK_Wdog2, kCLOCK_Wdog3, kCLOCK_Wdog4, kCLOCK_Wdog5 \
    }

/*! @brief Clock ip name array for XBAR. */
#define XBAR_CLOCKS                                                \
    {                                                              \
        kCLOCK_IpInvalid, kCLOCK_Xbar1, kCLOCK_Xbar2, kCLOCK_Xbar3 \
    }

/*!
 * @brief Clock LPCG index
 */
typedef enum _clock_lpcg
{
    kCLOCK_M7          = 0,   /*!< Clock LPCG M7          */
    kCLOCK_M33         = 1,   /*!< Clock LPCG M33         */
    kCLOCK_Edgelock    = 2,   /*!< Clock LPCG Edgelock    */
    kCLOCK_Sim_Aon     = 3,   /*!< Clock LPCG Sim_Aon     */
    kCLOCK_Sim_Wakeup  = 4,   /*!< Clock LPCG Sim_Wakeup  */
    kCLOCK_Sim_Mega    = 5,   /*!< Clock LPCG Sim_Mega    */
    kCLOCK_Sim_R       = 6,   /*!< Clock LPCG Sim_R       */
    kCLOCK_Anadig      = 7,   /*!< Clock LPCG Anadig      */
    kCLOCK_Dcdc        = 8,   /*!< Clock LPCG Dcdc        */
    kCLOCK_Src         = 9,   /*!< Clock LPCG Src         */
    kCLOCK_Ccm         = 10,  /*!< Clock LPCG Ccm         */
    kCLOCK_Gpc         = 11,  /*!< Clock LPCG Gpc         */
    kCLOCK_Adc1        = 12,  /*!< Clock LPCG Adc1        */
    kCLOCK_Adc2        = 13,  /*!< Clock LPCG Adc2        */
    kCLOCK_Dac         = 14,  /*!< Clock LPCG Dac         */
    kCLOCK_Acmp1       = 15,  /*!< Clock LPCG Acmp1       */
    kCLOCK_Acmp2       = 16,  /*!< Clock LPCG Acmp2       */
    kCLOCK_Acmp3       = 17,  /*!< Clock LPCG Acmp3       */
    kCLOCK_Acmp4       = 18,  /*!< Clock LPCG Acmp4       */
    kCLOCK_Wdog1       = 19,  /*!< Clock LPCG Wdog1       */
    kCLOCK_Wdog2       = 20,  /*!< Clock LPCG Wdog2       */
    kCLOCK_Wdog3       = 21,  /*!< Clock LPCG Wdog3       */
    kCLOCK_Wdog4       = 22,  /*!< Clock LPCG Wdog4       */
    kCLOCK_Wdog5       = 23,  /*!< Clock LPCG Wdog5       */
    kCLOCK_Ewm0        = 24,  /*!< Clock LPCG Ewm0        */
    kCLOCK_Sema1       = 25,  /*!< Clock LPCG Sema1       */
    kCLOCK_Sema2       = 26,  /*!< Clock LPCG Sema2       */
    kCLOCK_Mu_A        = 27,  /*!< Clock LPCG Mu_A        */
    kCLOCK_Mu_B        = 28,  /*!< Clock LPCG Mu_B        */
    kCLOCK_Edma1       = 29,  /*!< Clock LPCG Edma1       */
    kCLOCK_Edma2       = 30,  /*!< Clock LPCG Edma2       */
    kCLOCK_Romcp       = 31,  /*!< Clock LPCG Romcp       */
    kCLOCK_Ocram1      = 32,  /*!< Clock LPCG Ocram1      */
    kCLOCK_Ocram2      = 33,  /*!< Clock LPCG Ocram2      */
    kCLOCK_Flexspi1    = 34,  /*!< Clock LPCG Flexspi1    */
    kCLOCK_Flexspi2    = 35,  /*!< Clock LPCG Flexspi2    */
    kCLOCK_Flexspi_Slv = 36,  /*!< Clock LPCG Flexspi_Slv */
    kCLOCK_Trdc        = 37,  /*!< Clock LPCG Trdc        */
    kCLOCK_Ocotp       = 38,  /*!< Clock LPCG Ocotp       */
    kCLOCK_Semc        = 39,  /*!< Clock LPCG Semc        */
    kCLOCK_Iee         = 40,  /*!< Clock LPCG Iee         */
    kCLOCK_Cstrace     = 41,  /*!< Clock LPCG Cstrace     */
    kCLOCK_Csswo       = 42,  /*!< Clock LPCG Csswo       */
    kCLOCK_Iomuxc1     = 43,  /*!< Clock LPCG Iomuxc1     */
    kCLOCK_Iomuxc2     = 44,  /*!< Clock LPCG Iomuxc2     */
    kCLOCK_Gpio1       = 45,  /*!< Clock LPCG Gpio1       */
    kCLOCK_Gpio2       = 46,  /*!< Clock LPCG Gpio2       */
    kCLOCK_Gpio3       = 47,  /*!< Clock LPCG Gpio3       */
    kCLOCK_Gpio4       = 48,  /*!< Clock LPCG Gpio4       */
    kCLOCK_Gpio5       = 49,  /*!< Clock LPCG Gpio5       */
    kCLOCK_Gpio6       = 50,  /*!< Clock LPCG Gpio6       */
    kCLOCK_Flexio1     = 51,  /*!< Clock LPCG Flexio1     */
    kCLOCK_Flexio2     = 52,  /*!< Clock LPCG Flexio2     */
    kCLOCK_Lpit1       = 53,  /*!< Clock LPCG Lpit1       */
    kCLOCK_Lpit2       = 54,  /*!< Clock LPCG Lpit2       */
    kCLOCK_Lpit3       = 55,  /*!< Clock LPCG Lpit3       */
    kCLOCK_Lptmr1      = 56,  /*!< Clock LPCG Lptmr1      */
    kCLOCK_Lptmr2      = 57,  /*!< Clock LPCG Lptmr2      */
    kCLOCK_Lptmr3      = 58,  /*!< Clock LPCG Lptmr3      */
    kCLOCK_Tpm1        = 59,  /*!< Clock LPCG Tpm1        */
    kCLOCK_Tpm2        = 60,  /*!< Clock LPCG Tpm2        */
    kCLOCK_Tpm3        = 61,  /*!< Clock LPCG Tpm3        */
    kCLOCK_Tpm4        = 62,  /*!< Clock LPCG Tpm4        */
    kCLOCK_Tpm5        = 63,  /*!< Clock LPCG Tpm5        */
    kCLOCK_Tpm6        = 64,  /*!< Clock LPCG Tpm6        */
    kCLOCK_Qtimer1     = 65,  /*!< Clock LPCG Qtimer1     */
    kCLOCK_Qtimer2     = 66,  /*!< Clock LPCG Qtimer2     */
    kCLOCK_Qtimer3     = 67,  /*!< Clock LPCG Qtimer3     */
    kCLOCK_Qtimer4     = 68,  /*!< Clock LPCG Qtimer4     */
    kCLOCK_Qtimer5     = 69,  /*!< Clock LPCG Qtimer5     */
    kCLOCK_Qtimer6     = 70,  /*!< Clock LPCG Qtimer6     */
    kCLOCK_Qtimer7     = 71,  /*!< Clock LPCG Qtimer7     */
    kCLOCK_Qtimer8     = 72,  /*!< Clock LPCG Qtimer8     */
    kCLOCK_Gpt1        = 73,  /*!< Clock LPCG Gpt1        */
    kCLOCK_Gpt2        = 74,  /*!< Clock LPCG Gpt2        */
    kCLOCK_Syscount    = 75,  /*!< Clock LPCG Syscount    */
    kCLOCK_Can1        = 76,  /*!< Clock LPCG Can1        */
    kCLOCK_Can2        = 77,  /*!< Clock LPCG Can2        */
    kCLOCK_Can3        = 78,  /*!< Clock LPCG Can3        */
    kCLOCK_Lpuart1     = 79,  /*!< Clock LPCG Lpuart1     */
    kCLOCK_Lpuart2     = 80,  /*!< Clock LPCG Lpuart2     */
    kCLOCK_Lpuart3     = 81,  /*!< Clock LPCG Lpuart3     */
    kCLOCK_Lpuart4     = 82,  /*!< Clock LPCG Lpuart4     */
    kCLOCK_Lpuart5     = 83,  /*!< Clock LPCG Lpuart5     */
    kCLOCK_Lpuart6     = 84,  /*!< Clock LPCG Lpuart6     */
    kCLOCK_Lpuart7     = 85,  /*!< Clock LPCG Lpuart7     */
    kCLOCK_Lpuart8     = 86,  /*!< Clock LPCG Lpuart8     */
    kCLOCK_Lpuart9     = 87,  /*!< Clock LPCG Lpuart9     */
    kCLOCK_Lpuart10    = 88,  /*!< Clock LPCG Lpuart10    */
    kCLOCK_Lpuart11    = 89,  /*!< Clock LPCG Lpuart11    */
    kCLOCK_Lpuart12    = 90,  /*!< Clock LPCG Lpuart12    */
    kCLOCK_Lpi2c1      = 91,  /*!< Clock LPCG Lpi2c1      */
    kCLOCK_Lpi2c2      = 92,  /*!< Clock LPCG Lpi2c2      */
    kCLOCK_Lpi2c3      = 93,  /*!< Clock LPCG Lpi2c3      */
    kCLOCK_Lpi2c4      = 94,  /*!< Clock LPCG Lpi2c4      */
    kCLOCK_Lpi2c5      = 95,  /*!< Clock LPCG Lpi2c5      */
    kCLOCK_Lpi2c6      = 96,  /*!< Clock LPCG Lpi2c6      */
    kCLOCK_Lpspi1      = 97,  /*!< Clock LPCG Lpspi1      */
    kCLOCK_Lpspi2      = 98,  /*!< Clock LPCG Lpspi2      */
    kCLOCK_Lpspi3      = 99,  /*!< Clock LPCG Lpspi3      */
    kCLOCK_Lpspi4      = 100, /*!< Clock LPCG Lpspi4      */
    kCLOCK_Lpspi5      = 101, /*!< Clock LPCG Lpspi5      */
    kCLOCK_Lpspi6      = 102, /*!< Clock LPCG Lpspi6      */
    kCLOCK_I3c1        = 103, /*!< Clock LPCG I3c1        */
    kCLOCK_I3c2        = 104, /*!< Clock LPCG I3c2        */
    kCLOCK_Usdhc1      = 105, /*!< Clock LPCG Usdhc1      */
    kCLOCK_Usdhc2      = 106, /*!< Clock LPCG Usdhc2      */
    kCLOCK_Usb         = 107, /*!< Clock LPCG Usb         */
    kCLOCK_Sinc1       = 108, /*!< Clock LPCG Sinc1       */
    kCLOCK_Sinc2       = 109, /*!< Clock LPCG Sinc2       */
    kCLOCK_Sinc3       = 110, /*!< Clock LPCG Sinc3       */
    kCLOCK_Xbar1       = 111, /*!< Clock LPCG Xbar1       */
    kCLOCK_Xbar2       = 112, /*!< Clock LPCG Xbar2       */
    kCLOCK_Xbar3       = 113, /*!< Clock LPCG Xbar3       */
    kCLOCK_Aoi1        = 114, /*!< Clock LPCG Aoi1        */
    kCLOCK_Aoi2        = 115, /*!< Clock LPCG Aoi2        */
    kCLOCK_Aoi3        = 116, /*!< Clock LPCG Aoi3        */
    kCLOCK_Aoi4        = 117, /*!< Clock LPCG Aoi4        */
    kCLOCK_Enc1        = 118, /*!< Clock LPCG Enc1        */
    kCLOCK_Enc2        = 119, /*!< Clock LPCG Enc2        */
    kCLOCK_Enc3        = 120, /*!< Clock LPCG Enc3        */
    kCLOCK_Enc4        = 121, /*!< Clock LPCG Enc4        */
    kCLOCK_Kpp         = 122, /*!< Clock LPCG Kpp         */
    kCLOCK_Pwm1        = 123, /*!< Clock LPCG Pwm1        */
    kCLOCK_Pwm2        = 124, /*!< Clock LPCG Pwm2        */
    kCLOCK_Pwm3        = 125, /*!< Clock LPCG Pwm3        */
    kCLOCK_Pwm4        = 126, /*!< Clock LPCG Pwm4        */
    kCLOCK_Ecat        = 127, /*!< Clock LPCG Ecat        */
    kCLOCK_Netc        = 128, /*!< Clock LPCG Netc        */
    kCLOCK_Serdes1     = 129, /*!< Clock LPCG Serdes1     */
    kCLOCK_Serdes2     = 130, /*!< Clock LPCG Serdes2     */
    kCLOCK_Serdes3     = 131, /*!< Clock LPCG Serdes3     */
    kCLOCK_Xcelbusx    = 132, /*!< Clock LPCG Xcelbusx    */
    kCLOCK_Xriocu4     = 133, /*!< Clock LPCG Xriocu4     */
    kCLOCK_Sptp        = 134, /*!< Clock LPCG Sptp        */
    kCLOCK_Mctrl       = 135, /*!< Clock LPCG Mctrl       */
    kCLOCK_Sai1        = 136, /*!< Clock LPCG Sai1        */
    kCLOCK_Sai2        = 137, /*!< Clock LPCG Sai2        */
    kCLOCK_Sai3        = 138, /*!< Clock LPCG Sai3        */
    kCLOCK_Sai4        = 139, /*!< Clock LPCG Sai4        */
    kCLOCK_Spdif       = 140, /*!< Clock LPCG Spdif       */
    kCLOCK_Asrc        = 141, /*!< Clock LPCG Asrc        */
    kCLOCK_Pdm         = 142, /*!< Clock LPCG Mic         */
    kCLOCK_Vref        = 143, /*!< Clock LPCG Vref        */
    kCLOCK_Bist        = 144, /*!< Clock LPCG Bist        */
    kCLOCK_Ssi_W2M7    = 145, /*!< Clock LPCG Ssi_W2M7    */
    kCLOCK_Ssi_M72W    = 146, /*!< Clock LPCG Ssi_M72W    */
    kCLOCK_Ssi_W2Ao    = 147, /*!< Clock LPCG Ssi_W2Ao    */
    kCLOCK_Ssi_Ao2W    = 148, /*!< Clock LPCG Ssi_Ao2W    */

    kCLOCK_IpInvalid, /*!< Invalid value. */
} clock_lpcg_t;

/*!
 * @brief Clock name.
 */
typedef enum _clock_name
{
    kCLOCK_OscRc24M    = 0,  /*!< 24MHz RC Oscillator. */
    kCLOCK_OscRc400M   = 1,  /*!< 400MHz RC Oscillator. */
    kCLOCK_Osc24M      = 2,  /*!< 24MHz Oscillator. */
    kCLOCK_Osc24MOut   = 3,  /*!< 24MHz Oscillator Out. */
    kCLOCK_ArmPll      = 4,  /*!< ARM PLL. */
    kCLOCK_ArmPllOut   = 5,  /*!< ARM PLL Out. */
    kCLOCK_SysPll2     = 6,  /*!< SYS PLL2. */
    kCLOCK_SysPll2Out  = 7,  /*!< SYS PLL2 OUT. */
    kCLOCK_SysPll2Pfd0 = 8,  /*!< SYS PLL2 PFD0. */
    kCLOCK_SysPll2Pfd1 = 9,  /*!< SYS PLL2 PFD1. */
    kCLOCK_SysPll2Pfd2 = 10, /*!< SYS PLL2 PFD2. */
    kCLOCK_SysPll2Pfd3 = 11, /*!< SYS PLL2 PFD3. */
    kCLOCK_SysPll3     = 12, /*!< SYS PLL3. */
    kCLOCK_SysPll3Out  = 13, /*!< SYS PLL3 OUT. */
    kCLOCK_SysPll3Div2 = 14, /*!< SYS PLL3 DIV2 */
    kCLOCK_SysPll3Pfd0 = 15, /*!< SYS PLL3 PFD0. */
    kCLOCK_SysPll3Pfd1 = 16, /*!< SYS PLL3 PFD1 */
    kCLOCK_SysPll3Pfd2 = 17, /*!< SYS PLL3 PFD2 */
    kCLOCK_SysPll3Pfd3 = 18, /*!< SYS PLL3 PFD3 */
    kCLOCK_SysPll1     = 19, /*!< SYS PLL1. */
    kCLOCK_SysPll1Out  = 20, /*!< SYS PLL1 OUT. */
    kCLOCK_SysPll1Div2 = 21, /*!< SYS PLL1 DIV2. */
    kCLOCK_SysPll1Div5 = 22, /*!< SYS PLL1 DIV5. */
    kCLOCK_AudioPll    = 23, /*!< SYS AUDIO PLL. */
    kCLOCK_AudioPllOut = 24, /*!< SYS AUDIO PLL OUT. */
    kCLOCK_CpuClk,           /*!< SYS CPU CLK. */
    kCLOCK_CoreSysClk,       /*!< SYS CORE SYS CLK. */
} clock_name_t;

/* Clock OBSERVE SIGNALS */
#define CCM_OBS_OSC_RC_24M           2
#define CCM_OBS_OSC_RC_400M          3
#define CCM_OBS_OSC_24M_OUT          5
#define CCM_OBS_PLL_ARM_OUT          7
#define CCM_OBS_PLL_528_OUT          9
#define CCM_OBS_PLL_528_PFD0         10
#define CCM_OBS_PLL_528_PFD1         11
#define CCM_OBS_PLL_528_PFD2         12
#define CCM_OBS_PLL_528_PFD3         13
#define CCM_OBS_PLL_480_OUT          15
#define CCM_OBS_PLL_480_DIV2         16
#define CCM_OBS_PLL_480_PFD0         17
#define CCM_OBS_PLL_480_PFD1         18
#define CCM_OBS_PLL_480_PFD2         19
#define CCM_OBS_PLL_480_PFD3         20
#define CCM_OBS_PLL_1G_OUT           22
#define CCM_OBS_PLL_1G_DIV2          23
#define CCM_OBS_PLL_1G_DIV5          24
#define CCM_OBS_PLL_AUDIO_OUT        26
#define CCM_OBS_M7_CLK_ROOT          128
#define CCM_OBS_M33_CLK_ROOT         129
#define CCM_OBS_EDGELOCK_CLK_ROOT    130
#define CCM_OBS_BUS_AON_CLK_ROOT     131
#define CCM_OBS_BUS_WAKEUP_CLK_ROOT  132
#define CCM_OBS_WAKEUP_AXI_CLK_ROOT  133
#define CCM_OBS_SWO_TRACE_CLK_ROOT   134
#define CCM_OBS_M33_SYSTICK_CLK_ROOT 135
#define CCM_OBS_M7_SYSTICK_CLK_ROOT  136
#define CCM_OBS_FLEXIO1_CLK_ROOT     137
#define CCM_OBS_FLEXIO2_CLK_ROOT     138
#define CCM_OBS_LPIT3_CLK_ROOT       139
#define CCM_OBS_LPTMR1_CLK_ROOT      140
#define CCM_OBS_LPTMR2_CLK_ROOT      141
#define CCM_OBS_LPTMR3_CLK_ROOT      142
#define CCM_OBS_TPM2_CLK_ROOT        143
#define CCM_OBS_TPM4_CLK_ROOT        144
#define CCM_OBS_TPM5_CLK_ROOT        145
#define CCM_OBS_TPM6_CLK_ROOT        146
#define CCM_OBS_GPT1_CLK_ROOT        147
#define CCM_OBS_GPT2_CLK_ROOT        148
#define CCM_OBS_FLEXSPI1_CLK_ROOT    149
#define CCM_OBS_FLEXSPI2_CLK_ROOT    150
#define CCM_OBS_FLEXSPI_SLV_CLK_ROOT 151
#define CCM_OBS_CAN1_CLK_ROOT        152
#define CCM_OBS_CAN2_CLK_ROOT        153
#define CCM_OBS_CAN3_CLK_ROOT        154
#define CCM_OBS_LPUART0102_CLK_ROOT  155
#define CCM_OBS_LPUART0304_CLK_ROOT  156
#define CCM_OBS_LPUART0506_CLK_ROOT  157
#define CCM_OBS_LPUART0708_CLK_ROOT  158
#define CCM_OBS_LPUART0910_CLK_ROOT  159
#define CCM_OBS_LPUART1112_CLK_ROOT  160
#define CCM_OBS_LPI2C0102_CLK_ROOT   161
#define CCM_OBS_LPI2C0304_CLK_ROOT   162
#define CCM_OBS_LPI2C0506_CLK_ROOT   163
#define CCM_OBS_LPSPI0102_CLK_ROOT   164
#define CCM_OBS_LPSPI0304_CLK_ROOT   165
#define CCM_OBS_LPSPI0506_CLK_ROOT   166
#define CCM_OBS_I3C1_CLK_ROOT        167
#define CCM_OBS_I3C2_CLK_ROOT        168
#define CCM_OBS_USDHC1_CLK_ROOT      169
#define CCM_OBS_USDHC2_CLK_ROOT      170
#define CCM_OBS_SEMC_CLK_ROOT        171
#define CCM_OBS_ADC1_CLK_ROOT        172
#define CCM_OBS_ADC2_CLK_ROOT        173
#define CCM_OBS_ACMP_CLK_ROOT        174
#define CCM_OBS_ECAT_CLK_ROOT        175
#define CCM_OBS_ENET_REFCLK_ROOT     176
#define CCM_OBS_TMR_1588_CLK_ROOT    177
#define CCM_OBS_NETC_CLK_ROOT        178
#define CCM_OBS_MAC0_CLK_ROOT        179
#define CCM_OBS_MAC1_CLK_ROOT        180
#define CCM_OBS_MAC2_CLK_ROOT        181
#define CCM_OBS_MAC3_CLK_ROOT        182
#define CCM_OBS_MAC4_CLK_ROOT        183
#define CCM_OBS_SERDES0_CLK_ROOT     184
#define CCM_OBS_SERDES1_CLK_ROOT     185
#define CCM_OBS_SERDES2_CLK_ROOT     186
#define CCM_OBS_SERDES0_1G_CLK_ROOT  187
#define CCM_OBS_SERDES1_1G_CLK_ROOT  188
#define CCM_OBS_SERDES2_1G_CLK_ROOT  189
#define CCM_OBS_XCELBUSX_CLK_ROOT    190
#define CCM_OBS_XRIOCU4_CLK_ROOT     191
#define CCM_OBS_MOTORCTRL_CLK_ROOT   192
#define CCM_OBS_SAI1_CLK_ROOT        193
#define CCM_OBS_SAI2_CLK_ROOT        194
#define CCM_OBS_SAI3_CLK_ROOT        195
#define CCM_OBS_SAI4_CLK_ROOT        196
#define CCM_OBS_SPDIF_CLK_ROOT       197
#define CCM_OBS_ASRC_CLK_ROOT        198
#define CCM_OBS_MIC_CLK_ROOT         199
#define CCM_OBS_CCM_CKO1_CLK_ROOT    200
#define CCM_OBS_CCM_CKO2_CLK_ROOT    201

#define CCM_OBS_DIV 3

/* Clock Source Definitions */
/* clang-format off */
static const clock_name_t s_clockSourceName[][4] = {
        /*SRC0,           SRC1,             SRC2,               SRC3,                    name        index */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_ArmPllOut,   kCLOCK_SysPll3Out  }, /* M7             0  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Out,  kCLOCK_ArmPllOut,  }, /* M33            1  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Out,  kCLOCK_SysPll2Pfd1,}, /* EDGELOCK       2  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll2Out,  kCLOCK_SysPll3Pfd2,}, /* BUS_AON        3  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll2Out,  kCLOCK_SysPll3Pfd1,}, /* BUS_WAKEUP     4  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Out,  kCLOCK_SysPll2Pfd1,}, /* WAKEUP_AXI     5  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5,}, /* SWO_TRACE      6  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_Osc24MOut,   kCLOCK_SysPll3Div2,}, /* M33_SYSTICK    7  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_Osc24MOut,   kCLOCK_SysPll3Div2,}, /* M7_SYSTICK     8  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5,}, /* FLEXIO1        9  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div5,}, /* FLEXIO2       10  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* LPIT3         11  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* LPTIMER1      12  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* LPTIMER2      13  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* LPTIMER3      14  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* TPM2          15  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* TPM4          16  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* TPM5          17  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* TPM6          18  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* GPT1          19  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* GPT2          20  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Pfd0, kCLOCK_SysPll2Pfd0,}, /* FLEXSPI1      21  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Pfd2, kCLOCK_SysPll2Pfd1,}, /* FLEXSPI2      22  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll2Out,  kCLOCK_SysPll1Out, }, /* FLEXSPI_SLV   23  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Out,  kCLOCK_Osc24MOut,  }, /* CAN1          24  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Out,  kCLOCK_Osc24MOut,  }, /* CAN2          25  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Out,  kCLOCK_Osc24MOut,  }, /* CAN3          26  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* LPUART0102    27  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* LPUART0304    28  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* LPUART0506    29  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* LPUART0708    30  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* LPUART0910    31  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* LPUART1112    32  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* LPI2C0102     33  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* LPI2C0304     34  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* LPI2C0506     35  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Pfd1, kCLOCK_SysPll2Out, }, /* LPSPI0102     36  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Pfd1, kCLOCK_SysPll2Out, }, /* LPSPI0304     37  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Pfd1, kCLOCK_SysPll2Out, }, /* LPSPI0506     38  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* I3C1          39  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* I3C2          40  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll2Pfd2, kCLOCK_SysPll1Div5,}, /* USDHC1        41  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll2Pfd2, kCLOCK_SysPll1Div5,}, /* USDHC2        42  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Out,  kCLOCK_SysPll2Pfd0,}, /* SEMC          43  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* ADC1          44  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll2Pfd3,}, /* ADC2          45  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Out,  kCLOCK_SysPll2Pfd3,}, /* ACMP          46  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Div2, kCLOCK_SysPll1Div5,}, /* ECAT          47  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Div2, kCLOCK_SysPll1Div5,}, /* ENET          48  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Out,  kCLOCK_SysPll2Pfd3,}, /* TMR_1588      49  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Pfd3, kCLOCK_SysPll2Pfd1,}, /* NETC          50  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Div2, kCLOCK_SysPll1Div5,}, /* MAC0          51  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Div2, kCLOCK_SysPll1Div5,}, /* MAC1          52  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Div2, kCLOCK_SysPll1Div5,}, /* MAC2          53  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Div2, kCLOCK_SysPll1Div5,}, /* MAC3          54  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Div2, kCLOCK_SysPll1Div5,}, /* MAC4          55  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Div2, kCLOCK_SysPll1Div5,}, /* SERDES0       56  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Div2, kCLOCK_SysPll1Div5,}, /* SERDES1       57  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Div2, kCLOCK_SysPll1Div5,}, /* SERDES2       58  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Out,  kCLOCK_AudioPllOut,}, /* SERDES0_1G    59  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Out,  kCLOCK_AudioPllOut,}, /* SERDES1_1G    60  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Out,  kCLOCK_AudioPllOut,}, /* SERDES2_1G    61  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Out,  kCLOCK_SysPll3Pfd1,}, /* XCELBUSX      62  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_Osc24MOut,   kCLOCK_SysPll3Div2,}, /* XRIOCU4       63  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Div5, kCLOCK_AudioPllOut,}, /* MCTRL         64  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_AudioPllOut, kCLOCK_SysPll3Pfd2,}, /* SAI1          65  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_AudioPllOut, kCLOCK_SysPll3Pfd2,}, /* SAI2          66  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_AudioPllOut, kCLOCK_SysPll3Pfd2,}, /* SAI3          67  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_AudioPllOut, kCLOCK_SysPll3Pfd2,}, /* SAI4          68  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_AudioPllOut, kCLOCK_SysPll3Pfd2,}, /* SPDIF         69  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Out,  kCLOCK_AudioPllOut,}, /* ASRC          70  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_AudioPllOut,}, /* MIC           71  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll3Div2, kCLOCK_SysPll1Div2,}, /* CKO1          72  */ \
        {kCLOCK_OscRc24M, kCLOCK_OscRc400M, kCLOCK_SysPll1Div5, kCLOCK_ArmPllOut,  }  /* CKO2          73  */ \
};
/* clang-format on */

/*!
 * @brief Root clock index
 *
 */
typedef enum _clock_root
{
    kCLOCK_Root_M7          = 0,  /*!< CLOCK Root M7          */
    kCLOCK_Root_M33         = 1,  /*!< CLOCK Root M33         */
    kCLOCK_Root_Edgelock    = 2,  /*!< CLOCK Root Edgelock    */
    kCLOCK_Root_Bus_Aon     = 3,  /*!< CLOCK Root Bus_Aon     */
    kCLOCK_Root_Bus_Wakeup  = 4,  /*!< CLOCK Root Bus_Wakeup  */
    kCLOCK_Root_Wakeup_Axi  = 5,  /*!< CLOCK Root Wakeup_Axi  */
    kCLOCK_Root_Swo_Trace   = 6,  /*!< CLOCK Root Swo_Trace   */
    kCLOCK_Root_M33_Systick = 7,  /*!< CLOCK Root M33_Systick */
    kCLOCK_Root_M7_Systick  = 8,  /*!< CLOCK Root M7_Systick  */
    kCLOCK_Root_Flexio1     = 9,  /*!< CLOCK Root Flexio1     */
    kCLOCK_Root_Flexio2     = 10, /*!< CLOCK Root Flexio2     */
    kCLOCK_Root_Lpit3       = 11, /*!< CLOCK Root Lpit3       */
    kCLOCK_Root_Lptimer1    = 12, /*!< CLOCK Root Lptimer1    */
    kCLOCK_Root_Lptimer2    = 13, /*!< CLOCK Root Lptimer2    */
    kCLOCK_Root_Lptimer3    = 14, /*!< CLOCK Root Lptimer3    */
    kCLOCK_Root_Tpm2        = 15, /*!< CLOCK Root Tpm2        */
    kCLOCK_Root_Tpm4        = 16, /*!< CLOCK Root Tpm4        */
    kCLOCK_Root_Tpm5        = 17, /*!< CLOCK Root Tpm5        */
    kCLOCK_Root_Tpm6        = 18, /*!< CLOCK Root Tpm6        */
    kCLOCK_Root_Gpt1        = 19, /*!< CLOCK Root Gpt1        */
    kCLOCK_Root_Gpt2        = 20, /*!< CLOCK Root Gpt2        */
    kCLOCK_Root_Flexspi1    = 21, /*!< CLOCK Root Flexspi1    */
    kCLOCK_Root_Flexspi2    = 22, /*!< CLOCK Root Flexspi2    */
    kCLOCK_Root_Flexspi_Slv = 23, /*!< CLOCK Root Flexspi_Slv */
    kCLOCK_Root_Can1        = 24, /*!< CLOCK Root Can1        */
    kCLOCK_Root_Can2        = 25, /*!< CLOCK Root Can2        */
    kCLOCK_Root_Can3        = 26, /*!< CLOCK Root Can3        */
    kCLOCK_Root_Lpuart0102  = 27, /*!< CLOCK Root Lpuart0102  */
    kCLOCK_Root_Lpuart0304  = 28, /*!< CLOCK Root Lpuart0304  */
    kCLOCK_Root_Lpuart0506  = 29, /*!< CLOCK Root Lpuart0506  */
    kCLOCK_Root_Lpuart0708  = 30, /*!< CLOCK Root Lpuart0708  */
    kCLOCK_Root_Lpuart0910  = 31, /*!< CLOCK Root Lpuart0910  */
    kCLOCK_Root_Lpuart1112  = 32, /*!< CLOCK Root Lpuart1112  */
    kCLOCK_Root_Lpi2c0102   = 33, /*!< CLOCK Root Lpi2c0102   */
    kCLOCK_Root_Lpi2c0304   = 34, /*!< CLOCK Root Lpi2c0304   */
    kCLOCK_Root_Lpi2c0506   = 35, /*!< CLOCK Root Lpi2c0506   */
    kCLOCK_Root_Lpspi0102   = 36, /*!< CLOCK Root Lpspi0102   */
    kCLOCK_Root_Lpspi0304   = 37, /*!< CLOCK Root Lpspi0304   */
    kCLOCK_Root_Lpspi0506   = 38, /*!< CLOCK Root Lpspi0506   */
    kCLOCK_Root_I3c1        = 39, /*!< CLOCK Root I3c1        */
    kCLOCK_Root_I3c2        = 40, /*!< CLOCK Root I3c2        */
    kCLOCK_Root_Usdhc1      = 41, /*!< CLOCK Root Usdhc1      */
    kCLOCK_Root_Usdhc2      = 42, /*!< CLOCK Root Usdhc2      */
    kCLOCK_Root_Semc        = 43, /*!< CLOCK Root Semc        */
    kCLOCK_Root_Adc1        = 44, /*!< CLOCK Root Adc1        */
    kCLOCK_Root_Adc2        = 45, /*!< CLOCK Root Adc2        */
    kCLOCK_Root_Acmp        = 46, /*!< CLOCK Root Acmp        */
    kCLOCK_Root_Ecat        = 47, /*!< CLOCK Root Ecat        */
    kCLOCK_Root_Enet        = 48, /*!< CLOCK Root Enet        */
    kCLOCK_Root_Tmr_1588    = 49, /*!< CLOCK Root Tmr_1588    */
    kCLOCK_Root_Netc        = 50, /*!< CLOCK Root Netc        */
    kCLOCK_Root_Mac0        = 51, /*!< CLOCK Root Mac0        */
    kCLOCK_Root_Mac1        = 52, /*!< CLOCK Root Mac1        */
    kCLOCK_Root_Mac2        = 53, /*!< CLOCK Root Mac2        */
    kCLOCK_Root_Mac3        = 54, /*!< CLOCK Root Mac3        */
    kCLOCK_Root_Mac4        = 55, /*!< CLOCK Root Mac4        */
    kCLOCK_Root_Serdes0     = 56, /*!< CLOCK Root Serdes0     */
    kCLOCK_Root_Serdes1     = 57, /*!< CLOCK Root Serdes1     */
    kCLOCK_Root_Serdes2     = 58, /*!< CLOCK Root Serdes2     */
    kCLOCK_Root_Serdes0_1G  = 59, /*!< CLOCK Root Serdes0_1G  */
    kCLOCK_Root_Serdes1_1G  = 60, /*!< CLOCK Root Serdes1_1G  */
    kCLOCK_Root_Serdes2_1G  = 61, /*!< CLOCK Root Serdes2_1G  */
    kCLOCK_Root_Xcelbusx    = 62, /*!< CLOCK Root Xcelbusx    */
    kCLOCK_Root_Xriocu4     = 63, /*!< CLOCK Root Xriocu4     */
    kCLOCK_Root_Mctrl       = 64, /*!< CLOCK Root Mctrl       */
    kCLOCK_Root_Sai1        = 65, /*!< CLOCK Root Sai1        */
    kCLOCK_Root_Sai2        = 66, /*!< CLOCK Root Sai2        */
    kCLOCK_Root_Sai3        = 67, /*!< CLOCK Root Sai3        */
    kCLOCK_Root_Sai4        = 68, /*!< CLOCK Root Sai4        */
    kCLOCK_Root_Spdif       = 69, /*!< CLOCK Root Spdif       */
    kCLOCK_Root_Asrc        = 70, /*!< CLOCK Root Asrc        */
    kCLOCK_Root_Mic         = 71, /*!< CLOCK Root Mic         */
    kCLOCK_Root_Cko1        = 72, /*!< CLOCK Root Cko1        */
    kCLOCK_Root_Cko2        = 73, /*!< CLOCK Root Cko2        */
} clock_root_t;

/*!
 * @brief The enumerator of clock roots' clock source mux value.
 */
typedef enum _clock_root_mux_source
{
    /* M7 */
    kCLOCK_M7_ClockRoot_MuxOscRc24M   = 0U, /*!< M7 mux from OscRc24M. */
    kCLOCK_M7_ClockRoot_MuxOscRc400M  = 1U, /*!< M7 mux from OscRc400M. */
    kCLOCK_M7_ClockRoot_MuxArmPllOut  = 2U, /*!< M7 mux from ArmPllOut. */
    kCLOCK_M7_ClockRoot_MuxSysPll3Out = 3U, /*!< M7 mux from SysPll3Out. */

    /* M33 */
    kCLOCK_M33_ClockRoot_MuxOscRc24M   = 0U, /*!< M33 mux from OscRc24M. */
    kCLOCK_M33_ClockRoot_MuxOscRc400M  = 1U, /*!< M33 mux from OscRc400M. */
    kCLOCK_M33_ClockRoot_MuxSysPll3Out = 2U, /*!< M33 mux from SysPll3Out. */
    kCLOCK_M33_ClockRoot_MuxArmPllOut  = 3U, /*!< M33 mux from ArmPllOut. */

    /* EDGELOCK */
    kCLOCK_EDGELOCK_ClockRoot_MuxOscRc24M    = 0U, /*!< EDGELOCK mux from OscRc24M. */
    kCLOCK_EDGELOCK_ClockRoot_MuxOscRc400M   = 1U, /*!< EDGELOCK mux from OscRc400M. */
    kCLOCK_EDGELOCK_ClockRoot_MuxSysPll1Out  = 2U, /*!< EDGELOCK mux from SysPll1Out. */
    kCLOCK_EDGELOCK_ClockRoot_MuxSysPll2Pfd1 = 3U, /*!< EDGELOCK mux from SysPll2Pfd1. */

    /* BUS_AON */
    kCLOCK_BUS_AON_ClockRoot_MuxOscRc24M    = 0U, /*!< BUS_AON mux from OscRc24M. */
    kCLOCK_BUS_AON_ClockRoot_MuxOscRc400M   = 1U, /*!< BUS_AON mux from OscRc400M. */
    kCLOCK_BUS_AON_ClockRoot_MuxSysPll2Out  = 2U, /*!< BUS_AON mux from SysPll2Out. */
    kCLOCK_BUS_AON_ClockRoot_MuxSysPll3Pfd2 = 3U, /*!< BUS_AON mux from SysPll3Pfd2. */

    /* BUS_WAKEUP */
    kCLOCK_BUS_WAKEUP_ClockRoot_MuxOscRc24M    = 0U, /*!< BUS_WAKEUP mux from OscRc24M. */
    kCLOCK_BUS_WAKEUP_ClockRoot_MuxOscRc400M   = 1U, /*!< BUS_WAKEUP mux from OscRc400M. */
    kCLOCK_BUS_WAKEUP_ClockRoot_MuxSysPll2Out  = 2U, /*!< BUS_WAKEUP mux from SysPll2Out. */
    kCLOCK_BUS_WAKEUP_ClockRoot_MuxSysPll3Pfd1 = 3U, /*!< BUS_WAKEUP mux from SysPll3Pfd1. */

    /* WAKEUP_AXI */
    kCLOCK_WAKEUP_AXI_ClockRoot_MuxOscRc24M    = 0U, /*!< WAKEUP_AXI mux from OscRc24M. */
    kCLOCK_WAKEUP_AXI_ClockRoot_MuxOscRc400M   = 1U, /*!< WAKEUP_AXI mux from OscRc400M. */
    kCLOCK_WAKEUP_AXI_ClockRoot_MuxSysPll3Out  = 2U, /*!< WAKEUP_AXI mux from SysPll3Out. */
    kCLOCK_WAKEUP_AXI_ClockRoot_MuxSysPll2Pfd1 = 3U, /*!< WAKEUP_AXI mux from SysPll2Pfd1. */

    /* SWO_TRACE */
    kCLOCK_SWO_TRACE_ClockRoot_MuxOscRc24M    = 0U, /*!< SWO_TRACE mux from OscRc24M. */
    kCLOCK_SWO_TRACE_ClockRoot_MuxOscRc400M   = 1U, /*!< SWO_TRACE mux from OscRc400M. */
    kCLOCK_SWO_TRACE_ClockRoot_MuxSysPll3Div2 = 2U, /*!< SWO_TRACE mux from SysPll3Div2. */
    kCLOCK_SWO_TRACE_ClockRoot_MuxSysPll1Div5 = 3U, /*!< SWO_TRACE mux from SysPll1Div5. */

    /* M33_SYSTICK */
    kCLOCK_M33_SYSTICK_ClockRoot_MuxOscRc24M    = 0U, /*!< M33_SYSTICK mux from OscRc24M. */
    kCLOCK_M33_SYSTICK_ClockRoot_MuxOscRc400M   = 1U, /*!< M33_SYSTICK mux from OscRc400M. */
    kCLOCK_M33_SYSTICK_ClockRoot_MuxOsc24MOut   = 2U, /*!< M33_SYSTICK mux from Osc24MOut. */
    kCLOCK_M33_SYSTICK_ClockRoot_MuxSysPll3Div2 = 3U, /*!< M33_SYSTICK mux from SysPll3Div2. */

    /* M7_SYSTICK */
    kCLOCK_M7_SYSTICK_ClockRoot_MuxOscRc24M    = 0U, /*!< M7_SYSTICK mux from OscRc24M. */
    kCLOCK_M7_SYSTICK_ClockRoot_MuxOscRc400M   = 1U, /*!< M7_SYSTICK mux from OscRc400M. */
    kCLOCK_M7_SYSTICK_ClockRoot_MuxOsc24MOut   = 2U, /*!< M7_SYSTICK mux from Osc24MOut. */
    kCLOCK_M7_SYSTICK_ClockRoot_MuxSysPll3Div2 = 3U, /*!< M7_SYSTICK mux from SysPll3Div2. */

    /* FLEXIO1 */
    kCLOCK_FLEXIO1_ClockRoot_MuxOscRc24M    = 0U, /*!< FLEXIO1 mux from OscRc24M. */
    kCLOCK_FLEXIO1_ClockRoot_MuxOscRc400M   = 1U, /*!< FLEXIO1 mux from OscRc400M. */
    kCLOCK_FLEXIO1_ClockRoot_MuxSysPll3Div2 = 2U, /*!< FLEXIO1 mux from SysPll3Div2. */
    kCLOCK_FLEXIO1_ClockRoot_MuxSysPll1Div5 = 3U, /*!< FLEXIO1 mux from SysPll1Div5. */

    /* FLEXIO2 */
    kCLOCK_FLEXIO2_ClockRoot_MuxOscRc24M    = 0U, /*!< FLEXIO2 mux from OscRc24M. */
    kCLOCK_FLEXIO2_ClockRoot_MuxOscRc400M   = 1U, /*!< FLEXIO2 mux from OscRc400M. */
    kCLOCK_FLEXIO2_ClockRoot_MuxSysPll3Div2 = 2U, /*!< FLEXIO2 mux from SysPll3Div2. */
    kCLOCK_FLEXIO2_ClockRoot_MuxSysPll1Div5 = 3U, /*!< FLEXIO2 mux from SysPll1Div5. */

    /* LPIT3 */
    kCLOCK_LPIT3_ClockRoot_MuxOscRc24M    = 0U, /*!< LPIT3 mux from OscRc24M. */
    kCLOCK_LPIT3_ClockRoot_MuxOscRc400M   = 1U, /*!< LPIT3 mux from OscRc400M. */
    kCLOCK_LPIT3_ClockRoot_MuxSysPll3Div2 = 2U, /*!< LPIT3 mux from SysPll3Div2. */
    kCLOCK_LPIT3_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< LPIT3 mux from SysPll2Pfd3. */

    /* LPTIMER1 */
    kCLOCK_LPTIMER1_ClockRoot_MuxOscRc24M    = 0U, /*!< LPTIMER1 mux from OscRc24M. */
    kCLOCK_LPTIMER1_ClockRoot_MuxOscRc400M   = 1U, /*!< LPTIMER1 mux from OscRc400M. */
    kCLOCK_LPTIMER1_ClockRoot_MuxSysPll3Div2 = 2U, /*!< LPTIMER1 mux from SysPll3Div2. */
    kCLOCK_LPTIMER1_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< LPTIMER1 mux from SysPll2Pfd3. */

    /* LPTIMER2 */
    kCLOCK_LPTIMER2_ClockRoot_MuxOscRc24M    = 0U, /*!< LPTIMER2 mux from OscRc24M. */
    kCLOCK_LPTIMER2_ClockRoot_MuxOscRc400M   = 1U, /*!< LPTIMER2 mux from OscRc400M. */
    kCLOCK_LPTIMER2_ClockRoot_MuxSysPll3Div2 = 2U, /*!< LPTIMER2 mux from SysPll3Div2. */
    kCLOCK_LPTIMER2_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< LPTIMER2 mux from SysPll2Pfd3. */

    /* LPTIMER3 */
    kCLOCK_LPTIMER3_ClockRoot_MuxOscRc24M    = 0U, /*!< LPTIMER3 mux from OscRc24M. */
    kCLOCK_LPTIMER3_ClockRoot_MuxOscRc400M   = 1U, /*!< LPTIMER3 mux from OscRc400M. */
    kCLOCK_LPTIMER3_ClockRoot_MuxSysPll3Div2 = 2U, /*!< LPTIMER3 mux from SysPll3Div2. */
    kCLOCK_LPTIMER3_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< LPTIMER3 mux from SysPll2Pfd3. */

    /* TPM2 */
    kCLOCK_TPM2_ClockRoot_MuxOscRc24M    = 0U, /*!< TPM2 mux from OscRc24M. */
    kCLOCK_TPM2_ClockRoot_MuxOscRc400M   = 1U, /*!< TPM2 mux from OscRc400M. */
    kCLOCK_TPM2_ClockRoot_MuxSysPll3Div2 = 2U, /*!< TPM2 mux from SysPll3Div2. */
    kCLOCK_TPM2_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< TPM2 mux from SysPll2Pfd3. */

    /* TPM4 */
    kCLOCK_TPM4_ClockRoot_MuxOscRc24M    = 0U, /*!< TPM4 mux from OscRc24M. */
    kCLOCK_TPM4_ClockRoot_MuxOscRc400M   = 1U, /*!< TPM4 mux from OscRc400M. */
    kCLOCK_TPM4_ClockRoot_MuxSysPll3Div2 = 2U, /*!< TPM4 mux from SysPll3Div2. */
    kCLOCK_TPM4_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< TPM4 mux from SysPll2Pfd3. */

    /* TPM5 */
    kCLOCK_TPM5_ClockRoot_MuxOscRc24M    = 0U, /*!< TPM5 mux from OscRc24M. */
    kCLOCK_TPM5_ClockRoot_MuxOscRc400M   = 1U, /*!< TPM5 mux from OscRc400M. */
    kCLOCK_TPM5_ClockRoot_MuxSysPll3Div2 = 2U, /*!< TPM5 mux from SysPll3Div2. */
    kCLOCK_TPM5_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< TPM5 mux from SysPll2Pfd3. */

    /* TPM6 */
    kCLOCK_TPM6_ClockRoot_MuxOscRc24M    = 0U, /*!< TPM6 mux from OscRc24M. */
    kCLOCK_TPM6_ClockRoot_MuxOscRc400M   = 1U, /*!< TPM6 mux from OscRc400M. */
    kCLOCK_TPM6_ClockRoot_MuxSysPll3Div2 = 2U, /*!< TPM6 mux from SysPll3Div2. */
    kCLOCK_TPM6_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< TPM6 mux from SysPll2Pfd3. */

    /* GPT1 */
    kCLOCK_GPT1_ClockRoot_MuxOscRc24M    = 0U, /*!< GPT1 mux from OscRc24M. */
    kCLOCK_GPT1_ClockRoot_MuxOscRc400M   = 1U, /*!< GPT1 mux from OscRc400M. */
    kCLOCK_GPT1_ClockRoot_MuxSysPll3Div2 = 2U, /*!< GPT1 mux from SysPll3Div2. */
    kCLOCK_GPT1_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< GPT1 mux from SysPll2Pfd3. */

    /* GPT2 */
    kCLOCK_GPT2_ClockRoot_MuxOscRc24M    = 0U, /*!< GPT2 mux from OscRc24M. */
    kCLOCK_GPT2_ClockRoot_MuxOscRc400M   = 1U, /*!< GPT2 mux from OscRc400M. */
    kCLOCK_GPT2_ClockRoot_MuxSysPll3Div2 = 2U, /*!< GPT2 mux from SysPll3Div2. */
    kCLOCK_GPT2_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< GPT2 mux from SysPll2Pfd3. */

    /* FLEXSPI1 */
    kCLOCK_FLEXSPI1_ClockRoot_MuxOscRc24M    = 0U, /*!< FLEXSPI1 mux from OscRc24M. */
    kCLOCK_FLEXSPI1_ClockRoot_MuxOscRc400M   = 1U, /*!< FLEXSPI1 mux from OscRc400M. */
    kCLOCK_FLEXSPI1_ClockRoot_MuxSysPll3Pfd0 = 2U, /*!< FLEXSPI1 mux from SysPll3Pfd0. */
    kCLOCK_FLEXSPI1_ClockRoot_MuxSysPll2Pfd0 = 3U, /*!< FLEXSPI1 mux from SysPll2Pfd0. */

    /* FLEXSPI2 */
    kCLOCK_FLEXSPI2_ClockRoot_MuxOscRc24M    = 0U, /*!< FLEXSPI2 mux from OscRc24M. */
    kCLOCK_FLEXSPI2_ClockRoot_MuxOscRc400M   = 1U, /*!< FLEXSPI2 mux from OscRc400M. */
    kCLOCK_FLEXSPI2_ClockRoot_MuxSysPll3Pfd2 = 2U, /*!< FLEXSPI2 mux from SysPll3Pfd2. */
    kCLOCK_FLEXSPI2_ClockRoot_MuxSysPll2Pfd1 = 3U, /*!< FLEXSPI2 mux from SysPll2Pfd1. */

    /* FLEXSPI_SLV */
    kCLOCK_FLEXSPI_SLV_ClockRoot_MuxOscRc24M   = 0U, /*!< FLEXSPI_SLV mux from OscRc24M. */
    kCLOCK_FLEXSPI_SLV_ClockRoot_MuxOscRc400M  = 1U, /*!< FLEXSPI_SLV mux from OscRc400M. */
    kCLOCK_FLEXSPI_SLV_ClockRoot_MuxSysPll2Out = 2U, /*!< FLEXSPI_SLV mux from SysPll2Out. */
    kCLOCK_FLEXSPI_SLV_ClockRoot_MuxSysPll1Out = 3U, /*!< FLEXSPI_SLV mux from SysPll1Out. */

    /* CAN1 */
    kCLOCK_CAN1_ClockRoot_MuxOscRc24M   = 0U, /*!< CAN1 mux from OscRc24M. */
    kCLOCK_CAN1_ClockRoot_MuxOscRc400M  = 1U, /*!< CAN1 mux from OscRc400M. */
    kCLOCK_CAN1_ClockRoot_MuxSysPll3Out = 2U, /*!< CAN1 mux from SysPll3Out. */
    kCLOCK_CAN1_ClockRoot_MuxOsc24MOut  = 3U, /*!< CAN1 mux from Osc24MOut. */

    /* CAN2 */
    kCLOCK_CAN2_ClockRoot_MuxOscRc24M   = 0U, /*!< CAN2 mux from OscRc24M. */
    kCLOCK_CAN2_ClockRoot_MuxOscRc400M  = 1U, /*!< CAN2 mux from OscRc400M. */
    kCLOCK_CAN2_ClockRoot_MuxSysPll3Out = 2U, /*!< CAN2 mux from SysPll3Out. */
    kCLOCK_CAN2_ClockRoot_MuxOsc24MOut  = 3U, /*!< CAN2 mux from Osc24MOut. */

    /* CAN3 */
    kCLOCK_CAN3_ClockRoot_MuxOscRc24M   = 0U, /*!< CAN3 mux from OscRc24M. */
    kCLOCK_CAN3_ClockRoot_MuxOscRc400M  = 1U, /*!< CAN3 mux from OscRc400M. */
    kCLOCK_CAN3_ClockRoot_MuxSysPll3Out = 2U, /*!< CAN3 mux from SysPll3Out. */
    kCLOCK_CAN3_ClockRoot_MuxOsc24MOut  = 3U, /*!< CAN3 mux from Osc24MOut. */

    /* LPUART0102 */
    kCLOCK_LPUART0102_ClockRoot_MuxOscRc24M    = 0U, /*!< LPUART0102 mux from OscRc24M. */
    kCLOCK_LPUART0102_ClockRoot_MuxOscRc400M   = 1U, /*!< LPUART0102 mux from OscRc400M. */
    kCLOCK_LPUART0102_ClockRoot_MuxSysPll3Div2 = 2U, /*!< LPUART0102 mux from SysPll3Div2. */
    kCLOCK_LPUART0102_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< LPUART0102 mux from SysPll2Pfd3. */

    /* LPUART0304 */
    kCLOCK_LPUART0304_ClockRoot_MuxOscRc24M    = 0U, /*!< LPUART0304 mux from OscRc24M. */
    kCLOCK_LPUART0304_ClockRoot_MuxOscRc400M   = 1U, /*!< LPUART0304 mux from OscRc400M. */
    kCLOCK_LPUART0304_ClockRoot_MuxSysPll3Div2 = 2U, /*!< LPUART0304 mux from SysPll3Div2. */
    kCLOCK_LPUART0304_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< LPUART0304 mux from SysPll2Pfd3. */

    /* LPUART0506 */
    kCLOCK_LPUART0506_ClockRoot_MuxOscRc24M    = 0U, /*!< LPUART0506 mux from OscRc24M. */
    kCLOCK_LPUART0506_ClockRoot_MuxOscRc400M   = 1U, /*!< LPUART0506 mux from OscRc400M. */
    kCLOCK_LPUART0506_ClockRoot_MuxSysPll3Div2 = 2U, /*!< LPUART0506 mux from SysPll3Div2. */
    kCLOCK_LPUART0506_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< LPUART0506 mux from SysPll2Pfd3. */

    /* LPUART0708 */
    kCLOCK_LPUART0708_ClockRoot_MuxOscRc24M    = 0U, /*!< LPUART0708 mux from OscRc24M. */
    kCLOCK_LPUART0708_ClockRoot_MuxOscRc400M   = 1U, /*!< LPUART0708 mux from OscRc400M. */
    kCLOCK_LPUART0708_ClockRoot_MuxSysPll3Div2 = 2U, /*!< LPUART0708 mux from SysPll3Div2. */
    kCLOCK_LPUART0708_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< LPUART0708 mux from SysPll2Pfd3. */

    /* LPUART0910 */
    kCLOCK_LPUART0910_ClockRoot_MuxOscRc24M    = 0U, /*!< LPUART0910 mux from OscRc24M. */
    kCLOCK_LPUART0910_ClockRoot_MuxOscRc400M   = 1U, /*!< LPUART0910 mux from OscRc400M. */
    kCLOCK_LPUART0910_ClockRoot_MuxSysPll3Div2 = 2U, /*!< LPUART0910 mux from SysPll3Div2. */
    kCLOCK_LPUART0910_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< LPUART0910 mux from SysPll2Pfd3. */

    /* LPUART1112 */
    kCLOCK_LPUART1112_ClockRoot_MuxOscRc24M    = 0U, /*!< LPUART1112 mux from OscRc24M. */
    kCLOCK_LPUART1112_ClockRoot_MuxOscRc400M   = 1U, /*!< LPUART1112 mux from OscRc400M. */
    kCLOCK_LPUART1112_ClockRoot_MuxSysPll3Div2 = 2U, /*!< LPUART1112 mux from SysPll3Div2. */
    kCLOCK_LPUART1112_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< LPUART1112 mux from SysPll2Pfd3. */

    /* LPI2C0102 */
    kCLOCK_LPI2C0102_ClockRoot_MuxOscRc24M    = 0U, /*!< LPI2C0102 mux from OscRc24M. */
    kCLOCK_LPI2C0102_ClockRoot_MuxOscRc400M   = 1U, /*!< LPI2C0102 mux from OscRc400M. */
    kCLOCK_LPI2C0102_ClockRoot_MuxSysPll3Div2 = 2U, /*!< LPI2C0102 mux from SysPll3Div2. */
    kCLOCK_LPI2C0102_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< LPI2C0102 mux from SysPll2Pfd3. */

    /* LPI2C0304 */
    kCLOCK_LPI2C0304_ClockRoot_MuxOscRc24M    = 0U, /*!< LPI2C0304 mux from OscRc24M. */
    kCLOCK_LPI2C0304_ClockRoot_MuxOscRc400M   = 1U, /*!< LPI2C0304 mux from OscRc400M. */
    kCLOCK_LPI2C0304_ClockRoot_MuxSysPll3Div2 = 2U, /*!< LPI2C0304 mux from SysPll3Div2. */
    kCLOCK_LPI2C0304_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< LPI2C0304 mux from SysPll2Pfd3. */

    /* LPI2C0506 */
    kCLOCK_LPI2C0506_ClockRoot_MuxOscRc24M    = 0U, /*!< LPI2C0506 mux from OscRc24M. */
    kCLOCK_LPI2C0506_ClockRoot_MuxOscRc400M   = 1U, /*!< LPI2C0506 mux from OscRc400M. */
    kCLOCK_LPI2C0506_ClockRoot_MuxSysPll3Div2 = 2U, /*!< LPI2C0506 mux from SysPll3Div2. */
    kCLOCK_LPI2C0506_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< LPI2C0506 mux from SysPll2Pfd3. */

    /* LPSPI0102 */
    kCLOCK_LPSPI0102_ClockRoot_MuxOscRc24M    = 0U, /*!< LPSPI0102 mux from OscRc24M. */
    kCLOCK_LPSPI0102_ClockRoot_MuxOscRc400M   = 1U, /*!< LPSPI0102 mux from OscRc400M. */
    kCLOCK_LPSPI0102_ClockRoot_MuxSysPll3Pfd1 = 2U, /*!< LPSPI0102 mux from SysPll3Pfd1. */
    kCLOCK_LPSPI0102_ClockRoot_MuxSysPll2Out  = 3U, /*!< LPSPI0102 mux from SysPll2Out. */

    /* LPSPI0304 */
    kCLOCK_LPSPI0304_ClockRoot_MuxOscRc24M    = 0U, /*!< LPSPI0304 mux from OscRc24M. */
    kCLOCK_LPSPI0304_ClockRoot_MuxOscRc400M   = 1U, /*!< LPSPI0304 mux from OscRc400M. */
    kCLOCK_LPSPI0304_ClockRoot_MuxSysPll3Pfd1 = 2U, /*!< LPSPI0304 mux from SysPll3Pfd1. */
    kCLOCK_LPSPI0304_ClockRoot_MuxSysPll2Out  = 3U, /*!< LPSPI0304 mux from SysPll2Out. */

    /* LPSPI0506 */
    kCLOCK_LPSPI0506_ClockRoot_MuxOscRc24M    = 0U, /*!< LPSPI0506 mux from OscRc24M. */
    kCLOCK_LPSPI0506_ClockRoot_MuxOscRc400M   = 1U, /*!< LPSPI0506 mux from OscRc400M. */
    kCLOCK_LPSPI0506_ClockRoot_MuxSysPll3Pfd1 = 2U, /*!< LPSPI0506 mux from SysPll3Pfd1. */
    kCLOCK_LPSPI0506_ClockRoot_MuxSysPll2Out  = 3U, /*!< LPSPI0506 mux from SysPll2Out. */

    /* I3C1 */
    kCLOCK_I3C1_ClockRoot_MuxOscRc24M    = 0U, /*!< I3C1 mux from OscRc24M. */
    kCLOCK_I3C1_ClockRoot_MuxOscRc400M   = 1U, /*!< I3C1 mux from OscRc400M. */
    kCLOCK_I3C1_ClockRoot_MuxSysPll3Div2 = 2U, /*!< I3C1 mux from SysPll3Div2. */
    kCLOCK_I3C1_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< I3C1 mux from SysPll2Pfd3. */

    /* I3C2 */
    kCLOCK_I3C2_ClockRoot_MuxOscRc24M    = 0U, /*!< I3C2 mux from OscRc24M. */
    kCLOCK_I3C2_ClockRoot_MuxOscRc400M   = 1U, /*!< I3C2 mux from OscRc400M. */
    kCLOCK_I3C2_ClockRoot_MuxSysPll3Div2 = 2U, /*!< I3C2 mux from SysPll3Div2. */
    kCLOCK_I3C2_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< I3C2 mux from SysPll2Pfd3. */

    /* USDHC1 */
    kCLOCK_USDHC1_ClockRoot_MuxOscRc24M    = 0U, /*!< USDHC1 mux from OscRc24M. */
    kCLOCK_USDHC1_ClockRoot_MuxOscRc400M   = 1U, /*!< USDHC1 mux from OscRc400M. */
    kCLOCK_USDHC1_ClockRoot_MuxSysPll2Pfd2 = 2U, /*!< USDHC1 mux from SysPll2Pfd2. */
    kCLOCK_USDHC1_ClockRoot_MuxSysPll1Div5 = 3U, /*!< USDHC1 mux from SysPll1Div5. */

    /* USDHC2 */
    kCLOCK_USDHC2_ClockRoot_MuxOscRc24M    = 0U, /*!< USDHC2 mux from OscRc24M. */
    kCLOCK_USDHC2_ClockRoot_MuxOscRc400M   = 1U, /*!< USDHC2 mux from OscRc400M. */
    kCLOCK_USDHC2_ClockRoot_MuxSysPll2Pfd2 = 2U, /*!< USDHC2 mux from SysPll2Pfd2. */
    kCLOCK_USDHC2_ClockRoot_MuxSysPll1Div5 = 3U, /*!< USDHC2 mux from SysPll1Div5. */

    /* SEMC */
    kCLOCK_SEMC_ClockRoot_MuxOscRc24M    = 0U, /*!< SEMC mux from OscRc24M. */
    kCLOCK_SEMC_ClockRoot_MuxOscRc400M   = 1U, /*!< SEMC mux from OscRc400M. */
    kCLOCK_SEMC_ClockRoot_MuxSysPll1Out  = 2U, /*!< SEMC mux from SysPll1Out. */
    kCLOCK_SEMC_ClockRoot_MuxSysPll2Pfd0 = 3U, /*!< SEMC mux from SysPll2Pfd0. */

    /* ADC1 */
    kCLOCK_ADC1_ClockRoot_MuxOscRc24M    = 0U, /*!< ADC1 mux from OscRc24M. */
    kCLOCK_ADC1_ClockRoot_MuxOscRc400M   = 1U, /*!< ADC1 mux from OscRc400M. */
    kCLOCK_ADC1_ClockRoot_MuxSysPll3Div2 = 2U, /*!< ADC1 mux from SysPll3Div2. */
    kCLOCK_ADC1_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< ADC1 mux from SysPll2Pfd3. */

    /* ADC2 */
    kCLOCK_ADC2_ClockRoot_MuxOscRc24M    = 0U, /*!< ADC2 mux from OscRc24M. */
    kCLOCK_ADC2_ClockRoot_MuxOscRc400M   = 1U, /*!< ADC2 mux from OscRc400M. */
    kCLOCK_ADC2_ClockRoot_MuxSysPll3Div2 = 2U, /*!< ADC2 mux from SysPll3Div2. */
    kCLOCK_ADC2_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< ADC2 mux from SysPll2Pfd3. */

    /* ACMP */
    kCLOCK_ACMP_ClockRoot_MuxOscRc24M    = 0U, /*!< ACMP mux from OscRc24M. */
    kCLOCK_ACMP_ClockRoot_MuxOscRc400M   = 1U, /*!< ACMP mux from OscRc400M. */
    kCLOCK_ACMP_ClockRoot_MuxSysPll3Out  = 2U, /*!< ACMP mux from SysPll3Out. */
    kCLOCK_ACMP_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< ACMP mux from SysPll2Pfd3. */

    /* ECAT */
    kCLOCK_ECAT_ClockRoot_MuxOscRc24M    = 0U, /*!< ECAT mux from OscRc24M. */
    kCLOCK_ECAT_ClockRoot_MuxOscRc400M   = 1U, /*!< ECAT mux from OscRc400M. */
    kCLOCK_ECAT_ClockRoot_MuxSysPll1Div2 = 2U, /*!< ECAT mux from SysPll1Div2. */
    kCLOCK_ECAT_ClockRoot_MuxSysPll1Div5 = 3U, /*!< ECAT mux from SysPll1Div5. */

    /* ENET */
    kCLOCK_ENET_ClockRoot_MuxOscRc24M    = 0U, /*!< ENET mux from OscRc24M. */
    kCLOCK_ENET_ClockRoot_MuxOscRc400M   = 1U, /*!< ENET mux from OscRc400M. */
    kCLOCK_ENET_ClockRoot_MuxSysPll1Div2 = 2U, /*!< ENET mux from SysPll1Div2. */
    kCLOCK_ENET_ClockRoot_MuxSysPll1Div5 = 3U, /*!< ENET mux from SysPll1Div5. */

    /* TMR_1588 */
    kCLOCK_TMR_1588_ClockRoot_MuxOscRc24M    = 0U, /*!< TMR_1588 mux from OscRc24M. */
    kCLOCK_TMR_1588_ClockRoot_MuxOscRc400M   = 1U, /*!< TMR_1588 mux from OscRc400M. */
    kCLOCK_TMR_1588_ClockRoot_MuxSysPll3Out  = 2U, /*!< TMR_1588 mux from SysPll3Out. */
    kCLOCK_TMR_1588_ClockRoot_MuxSysPll2Pfd3 = 3U, /*!< TMR_1588 mux from SysPll2Pfd3. */

    /* NETC */
    kCLOCK_NETC_ClockRoot_MuxOscRc24M    = 0U, /*!< NETC mux from OscRc24M. */
    kCLOCK_NETC_ClockRoot_MuxOscRc400M   = 1U, /*!< NETC mux from OscRc400M. */
    kCLOCK_NETC_ClockRoot_MuxSysPll3Pfd3 = 2U, /*!< NETC mux from SysPll3Pfd3. */
    kCLOCK_NETC_ClockRoot_MuxSysPll2Pfd1 = 3U, /*!< NETC mux from SysPll2Pfd1. */

    /* MAC0 */
    kCLOCK_MAC0_ClockRoot_MuxOscRc24M    = 0U, /*!< MAC0 mux from OscRc24M. */
    kCLOCK_MAC0_ClockRoot_MuxOscRc400M   = 1U, /*!< MAC0 mux from OscRc400M. */
    kCLOCK_MAC0_ClockRoot_MuxSysPll1Div2 = 2U, /*!< MAC0 mux from SysPll1Div2. */
    kCLOCK_MAC0_ClockRoot_MuxSysPll1Div5 = 3U, /*!< MAC0 mux from SysPll1Div5. */

    /* MAC1 */
    kCLOCK_MAC1_ClockRoot_MuxOscRc24M    = 0U, /*!< MAC1 mux from OscRc24M. */
    kCLOCK_MAC1_ClockRoot_MuxOscRc400M   = 1U, /*!< MAC1 mux from OscRc400M. */
    kCLOCK_MAC1_ClockRoot_MuxSysPll1Div2 = 2U, /*!< MAC1 mux from SysPll1Div2. */
    kCLOCK_MAC1_ClockRoot_MuxSysPll1Div5 = 3U, /*!< MAC1 mux from SysPll1Div5. */

    /* MAC2 */
    kCLOCK_MAC2_ClockRoot_MuxOscRc24M    = 0U, /*!< MAC2 mux from OscRc24M. */
    kCLOCK_MAC2_ClockRoot_MuxOscRc400M   = 1U, /*!< MAC2 mux from OscRc400M. */
    kCLOCK_MAC2_ClockRoot_MuxSysPll1Div2 = 2U, /*!< MAC2 mux from SysPll1Div2. */
    kCLOCK_MAC2_ClockRoot_MuxSysPll1Div5 = 3U, /*!< MAC2 mux from SysPll1Div5. */

    /* MAC3 */
    kCLOCK_MAC3_ClockRoot_MuxOscRc24M    = 0U, /*!< MAC3 mux from OscRc24M. */
    kCLOCK_MAC3_ClockRoot_MuxOscRc400M   = 1U, /*!< MAC3 mux from OscRc400M. */
    kCLOCK_MAC3_ClockRoot_MuxSysPll1Div2 = 2U, /*!< MAC3 mux from SysPll1Div2. */
    kCLOCK_MAC3_ClockRoot_MuxSysPll1Div5 = 3U, /*!< MAC3 mux from SysPll1Div5. */

    /* MAC4 */
    kCLOCK_MAC4_ClockRoot_MuxOscRc24M    = 0U, /*!< MAC4 mux from OscRc24M. */
    kCLOCK_MAC4_ClockRoot_MuxOscRc400M   = 1U, /*!< MAC4 mux from OscRc400M. */
    kCLOCK_MAC4_ClockRoot_MuxSysPll1Div2 = 2U, /*!< MAC4 mux from SysPll1Div2. */
    kCLOCK_MAC4_ClockRoot_MuxSysPll1Div5 = 3U, /*!< MAC4 mux from SysPll1Div5. */

    /* SERDES0 */
    kCLOCK_SERDES0_ClockRoot_MuxOscRc24M    = 0U, /*!< SERDES0 mux from OscRc24M. */
    kCLOCK_SERDES0_ClockRoot_MuxOscRc400M   = 1U, /*!< SERDES0 mux from OscRc400M. */
    kCLOCK_SERDES0_ClockRoot_MuxSysPll1Div2 = 2U, /*!< SERDES0 mux from SysPll1Div2. */
    kCLOCK_SERDES0_ClockRoot_MuxSysPll1Div5 = 3U, /*!< SERDES0 mux from SysPll1Div5. */

    /* SERDES1 */
    kCLOCK_SERDES1_ClockRoot_MuxOscRc24M    = 0U, /*!< SERDES1 mux from OscRc24M. */
    kCLOCK_SERDES1_ClockRoot_MuxOscRc400M   = 1U, /*!< SERDES1 mux from OscRc400M. */
    kCLOCK_SERDES1_ClockRoot_MuxSysPll1Div2 = 2U, /*!< SERDES1 mux from SysPll1Div2. */
    kCLOCK_SERDES1_ClockRoot_MuxSysPll1Div5 = 3U, /*!< SERDES1 mux from SysPll1Div5. */

    /* SERDES2 */
    kCLOCK_SERDES2_ClockRoot_MuxOscRc24M    = 0U, /*!< SERDES2 mux from OscRc24M. */
    kCLOCK_SERDES2_ClockRoot_MuxOscRc400M   = 1U, /*!< SERDES2 mux from OscRc400M. */
    kCLOCK_SERDES2_ClockRoot_MuxSysPll1Div2 = 2U, /*!< SERDES2 mux from SysPll1Div2. */
    kCLOCK_SERDES2_ClockRoot_MuxSysPll1Div5 = 3U, /*!< SERDES2 mux from SysPll1Div5. */

    /* SERDES0_1G */
    kCLOCK_SERDES0_1G_ClockRoot_MuxOscRc24M    = 0U, /*!< SERDES0_1G mux from OscRc24M. */
    kCLOCK_SERDES0_1G_ClockRoot_MuxOscRc400M   = 1U, /*!< SERDES0_1G mux from OscRc400M. */
    kCLOCK_SERDES0_1G_ClockRoot_MuxSysPll1Out  = 2U, /*!< SERDES0_1G mux from SysPll1Out. */
    kCLOCK_SERDES0_1G_ClockRoot_MuxAudioPllOut = 3U, /*!< SERDES0_1G mux from AudioPllOut. */

    /* SERDES1_1G */
    kCLOCK_SERDES1_1G_ClockRoot_MuxOscRc24M    = 0U, /*!< SERDES1_1G mux from OscRc24M. */
    kCLOCK_SERDES1_1G_ClockRoot_MuxOscRc400M   = 1U, /*!< SERDES1_1G mux from OscRc400M. */
    kCLOCK_SERDES1_1G_ClockRoot_MuxSysPll1Out  = 2U, /*!< SERDES1_1G mux from SysPll1Out. */
    kCLOCK_SERDES1_1G_ClockRoot_MuxAudioPllOut = 3U, /*!< SERDES1_1G mux from AudioPllOut. */

    /* SERDES2_1G */
    kCLOCK_SERDES2_1G_ClockRoot_MuxOscRc24M    = 0U, /*!< SERDES2_1G mux from OscRc24M. */
    kCLOCK_SERDES2_1G_ClockRoot_MuxOscRc400M   = 1U, /*!< SERDES2_1G mux from OscRc400M. */
    kCLOCK_SERDES2_1G_ClockRoot_MuxSysPll1Out  = 2U, /*!< SERDES2_1G mux from SysPll1Out. */
    kCLOCK_SERDES2_1G_ClockRoot_MuxAudioPllOut = 3U, /*!< SERDES2_1G mux from AudioPllOut. */

    /* XCELBUSX */
    kCLOCK_XCELBUSX_ClockRoot_MuxOscRc24M    = 0U, /*!< XCELBUSX mux from OscRc24M. */
    kCLOCK_XCELBUSX_ClockRoot_MuxOscRc400M   = 1U, /*!< XCELBUSX mux from OscRc400M. */
    kCLOCK_XCELBUSX_ClockRoot_MuxSysPll3Out  = 2U, /*!< XCELBUSX mux from SysPll3Out. */
    kCLOCK_XCELBUSX_ClockRoot_MuxSysPll3Pfd1 = 3U, /*!< XCELBUSX mux from SysPll3Pfd1. */

    /* XRIOCU4 */
    kCLOCK_XRIOCU4_ClockRoot_MuxOscRc24M    = 0U, /*!< XRIOCU4 mux from OscRc24M. */
    kCLOCK_XRIOCU4_ClockRoot_MuxOscRc400M   = 1U, /*!< XRIOCU4 mux from OscRc400M. */
    kCLOCK_XRIOCU4_ClockRoot_MuxOsc24MOut   = 2U, /*!< XRIOCU4 mux from Osc24MOut. */
    kCLOCK_XRIOCU4_ClockRoot_MuxSysPll3Div2 = 3U, /*!< XRIOCU4 mux from SysPll3Div2. */

    /* MCTRL */
    kCLOCK_MCTRL_ClockRoot_MuxOscRc24M    = 0U, /*!< MCTRL mux from OscRc24M. */
    kCLOCK_MCTRL_ClockRoot_MuxOscRc400M   = 1U, /*!< MCTRL mux from OscRc400M. */
    kCLOCK_MCTRL_ClockRoot_MuxSysPll1Div5 = 2U, /*!< MCTRL mux from SysPll1Div5. */
    kCLOCK_MCTRL_ClockRoot_MuxAudioPllOut = 3U, /*!< MCTRL mux from AudioPllOut. */

    /* SAI1 */
    kCLOCK_SAI1_ClockRoot_MuxOscRc24M    = 0U, /*!< SAI1 mux from OscRc24M. */
    kCLOCK_SAI1_ClockRoot_MuxOscRc400M   = 1U, /*!< SAI1 mux from OscRc400M. */
    kCLOCK_SAI1_ClockRoot_MuxAudioPllOut = 2U, /*!< SAI1 mux from AudioPllOut. */
    kCLOCK_SAI1_ClockRoot_MuxSysPll3Pfd2 = 3U, /*!< SAI1 mux from SysPll3Pfd2. */

    /* SAI2 */
    kCLOCK_SAI2_ClockRoot_MuxOscRc24M    = 0U, /*!< SAI2 mux from OscRc24M. */
    kCLOCK_SAI2_ClockRoot_MuxOscRc400M   = 1U, /*!< SAI2 mux from OscRc400M. */
    kCLOCK_SAI2_ClockRoot_MuxAudioPllOut = 2U, /*!< SAI2 mux from AudioPllOut. */
    kCLOCK_SAI2_ClockRoot_MuxSysPll3Pfd2 = 3U, /*!< SAI2 mux from SysPll3Pfd2. */

    /* SAI3 */
    kCLOCK_SAI3_ClockRoot_MuxOscRc24M    = 0U, /*!< SAI3 mux from OscRc24M. */
    kCLOCK_SAI3_ClockRoot_MuxOscRc400M   = 1U, /*!< SAI3 mux from OscRc400M. */
    kCLOCK_SAI3_ClockRoot_MuxAudioPllOut = 2U, /*!< SAI3 mux from AudioPllOut. */
    kCLOCK_SAI3_ClockRoot_MuxSysPll3Pfd2 = 3U, /*!< SAI3 mux from SysPll3Pfd2. */

    /* SAI4 */
    kCLOCK_SAI4_ClockRoot_MuxOscRc24M    = 0U, /*!< SAI4 mux from OscRc24M. */
    kCLOCK_SAI4_ClockRoot_MuxOscRc400M   = 1U, /*!< SAI4 mux from OscRc400M. */
    kCLOCK_SAI4_ClockRoot_MuxAudioPllOut = 2U, /*!< SAI4 mux from AudioPllOut. */
    kCLOCK_SAI4_ClockRoot_MuxSysPll3Pfd2 = 3U, /*!< SAI4 mux from SysPll3Pfd2. */

    /* SPDIF */
    kCLOCK_SPDIF_ClockRoot_MuxOscRc24M    = 0U, /*!< SPDIF mux from OscRc24M. */
    kCLOCK_SPDIF_ClockRoot_MuxOscRc400M   = 1U, /*!< SPDIF mux from OscRc400M. */
    kCLOCK_SPDIF_ClockRoot_MuxAudioPllOut = 2U, /*!< SPDIF mux from AudioPllOut. */
    kCLOCK_SPDIF_ClockRoot_MuxSysPll3Pfd2 = 3U, /*!< SPDIF mux from SysPll3Pfd2. */

    /* ASRC */
    kCLOCK_ASRC_ClockRoot_MuxOscRc24M    = 0U, /*!< ASRC mux from OscRc24M. */
    kCLOCK_ASRC_ClockRoot_MuxOscRc400M   = 1U, /*!< ASRC mux from OscRc400M. */
    kCLOCK_ASRC_ClockRoot_MuxSysPll3Out  = 2U, /*!< ASRC mux from SysPll3Out. */
    kCLOCK_ASRC_ClockRoot_MuxAudioPllOut = 3U, /*!< ASRC mux from AudioPllOut. */

    /* MIC */
    kCLOCK_MIC_ClockRoot_MuxOscRc24M    = 0U, /*!< MIC mux from OscRc24M. */
    kCLOCK_MIC_ClockRoot_MuxOscRc400M   = 1U, /*!< MIC mux from OscRc400M. */
    kCLOCK_MIC_ClockRoot_MuxSysPll3Div2 = 2U, /*!< MIC mux from SysPll3Div2. */
    kCLOCK_MIC_ClockRoot_MuxAudioPllOut = 3U, /*!< MIC mux from AudioPllOut. */

    /* CKO1 */
    kCLOCK_CKO1_ClockRoot_MuxOscRc24M    = 0U, /*!< CKO1 mux from OscRc24M. */
    kCLOCK_CKO1_ClockRoot_MuxOscRc400M   = 1U, /*!< CKO1 mux from OscRc400M. */
    kCLOCK_CKO1_ClockRoot_MuxSysPll3Div2 = 2U, /*!< CKO1 mux from SysPll3Div2. */
    kCLOCK_CKO1_ClockRoot_MuxSysPll1Div2 = 3U, /*!< CKO1 mux from SysPll1Div2. */

    /* CKO2 */
    kCLOCK_CKO2_ClockRoot_MuxOscRc24M    = 0U, /*!< CKO2 mux from OscRc24M. */
    kCLOCK_CKO2_ClockRoot_MuxOscRc400M   = 1U, /*!< CKO2 mux from OscRc400M. */
    kCLOCK_CKO2_ClockRoot_MuxSysPll1Div5 = 2U, /*!< CKO2 mux from SysPll1Div5. */
    kCLOCK_CKO2_ClockRoot_MuxArmPllOut   = 3U, /*!< CKO2 mux from ArmPllOut. */
} clock_root_mux_source_t;

#define clock_ip_name_t clock_lpcg_t

#if (__CORTEX_M == 7)
#define CLOCK_GetCpuClkFreq CLOCK_GetM7Freq
#else
#define CLOCK_GetCpuClkFreq CLOCK_GetM33Freq
#endif

#define CLOCK_GetCoreSysClkFreq CLOCK_GetCpuClkFreq /*!< For compatible with other platforms without CCM. */

/* uncomment the following line if want to use OBS to retrieve frequency */
/* #define GET_FREQ_FROM_OBS */

/*! @brief OSC 24M sorce select */
typedef enum _clock_osc
{
    kCLOCK_RcOsc   = 0U, /*!< On chip OSC. */
    kCLOCK_XtalOsc = 1U, /*!< 24M Xtal OSC */
} clock_osc_t;

/*! @brief Clock gate value */
typedef enum _clock_gate_value
{
    kCLOCK_Off = (int)~CCM_LPCG_DIRECT_ON_MASK, /*!< Clock is off. */
    kCLOCK_On  = CCM_LPCG_DIRECT_ON_MASK,       /*!< Clock is on*/
} clock_gate_value_t;

/*! @brief System clock mode */
typedef enum _clock_mode_t
{
    kCLOCK_ModeRun  = 0U, /*!< Remain in run mode. */
    kCLOCK_ModeWait = 1U, /*!< Transfer to wait mode. */
    kCLOCK_ModeStop = 2U, /*!< Transfer to stop mode. */
} clock_mode_t;

/*! @brief USB clock source definition. */
typedef enum _clock_usb_src
{
    kCLOCK_Usb480M      = 0,                /*!< Use 480M.      */
    kCLOCK_UsbSrcUnused = (int)0xFFFFFFFFU, /*!< Used when the function does not
                                            care the clock source. */
} clock_usb_src_t;

/*! @brief Source of the USB HS PHY. */
typedef enum _clock_usb_phy_src
{
    kCLOCK_Usbphy480M = 0, /*!< Use 480M.      */
} clock_usb_phy_src_t;

/*! @brief PLL clock source, bypass cloco source also */
enum _clock_pll_clk_src
{
    kCLOCK_PllClkSrc24M = 0U, /*!< Pll clock source 24M */
    kCLOCK_PllSrcClkPN  = 1U, /*!< Pll clock source CLK1_P and CLK1_N */
};

/*!
 * @brief PLL post divider enumeration.
 */
typedef enum _clock_pll_post_div
{
    kCLOCK_PllPostDiv2 = 0U, /*!< Divide by 2. */
    kCLOCK_PllPostDiv4 = 1U, /*!< Divide by 4. */
    kCLOCK_PllPostDiv8 = 2U, /*!< Divide by 8. */
    kCLOCK_PllPostDiv1 = 3U, /*!< Divide by 1. */
} clock_pll_post_div_t;

/*!
 * @brief PLL configuration for ARM.
 *
 * The output clock frequency is:
 *
 *  Fout=Fin*loopDivider /(2 * postDivider).
 *
 * Fin is always 24MHz.
 */
typedef struct _clock_arm_pll_config
{
    clock_pll_post_div_t postDivider; /*!< Post divider. */
    uint32_t loopDivider;             /*!< PLL loop divider. Valid range: 104-208. */
} clock_arm_pll_config_t;

/*! @brief PLL configuration for USB */
typedef struct _clock_usb_pll_config
{
    uint8_t loopDivider; /*!< PLL loop divider.
                              0 - Fout=Fref*20;
                              1 - Fout=Fref*22 */
    uint8_t src;         /*!< Pll clock source, reference _clock_pll_clk_src */

} clock_usb_pll_config_t;

/*! @brief Spread specturm configure Pll */
typedef struct _clock_pll_ss_config
{
    uint16_t stop; /*!< Spread spectrum stop value to get frequency change. */
    uint16_t step; /*!< Spread spectrum step value to get frequency change step. */
} clock_pll_ss_config_t;

/*! @brief PLL configure for Sys Pll2 */
typedef struct _clock_sys_pll2_config
{
    uint32_t mfd;              /*!< Denominator of spread spectrum */
    clock_pll_ss_config_t *ss; /*!< Spread spectrum parameter,
                                 it can be NULL, if ssEnable is set to false */
    bool ssEnable;             /*!< Enable spread spectrum flag */
} clock_sys_pll2_config_t;

/*! @brief PLL configure for Sys Pll1 */
typedef struct _clock_sys_pll1_config
{
    bool pllDiv2En;            /*!< Enable Sys Pll1 divide-by-2 clock or not. */
    bool pllDiv5En;            /*!< Enable Sys Pll1 divide-by-5 clock or not. */
    clock_pll_ss_config_t *ss; /*!< Spread spectrum parameter,
                                 it can be NULL, if ssEnable is set to false */
    bool ssEnable;             /*!< Enable spread spectrum flag */
} clock_sys_pll1_config_t;

/*! @brief PLL configuration for AUDIO */
typedef struct _clock_audio_pll_config
{
    uint8_t loopDivider;       /*!< PLL loop divider. Valid range for DIV_SELECT divider value: 27~54. */
    uint8_t postDivider;       /*!< Divider after the PLL, 0x0=divided by 1, 0x1=divided by 2, 0x2=divided by 4,
                                    0x3=divided by 8, 0x4=divided by 16, 0x5=divided by 32.*/
    uint32_t numerator;        /*!< 30 bit numerator of fractional loop divider.*/
    uint32_t denominator;      /*!< 30 bit denominator of fractional loop divider */
    clock_pll_ss_config_t *ss; /*!< Spread spectrum parameter,
                                 it can be NULL, if ssEnable is set to false */
    bool ssEnable;             /*!< Enable spread spectrum flag */
} clock_audio_pll_config_t;

/*! @brief Clock root configuration */
typedef struct _clock_root_config_t
{
    bool clockOff;
    uint8_t mux; /*!< See #clock_root_mux_source_t for details. */
    uint8_t div; /*!< it's the actual divider */
} clock_root_config_t;

/*! @brief PLL name */
typedef enum _clock_pll
{
    kCLOCK_PllArm,          /*!< ARM PLL. */
    kCLOCK_PllSys1,         /*!< SYS1 PLL, it has a dedicated frequency of 1GHz. */
    kCLOCK_PllSys2,         /*!< SYS2 PLL, it has a dedicated frequency of 528MHz. */
    kCLOCK_PllSys3,         /*!< SYS3 PLL, it has a dedicated frequency of 480MHz. */
    kCLOCK_PllAudio,        /*!< Audio PLL. */
    kCLOCK_PllInvalid = -1, /*!< Invalid value. */
} clock_pll_t;

#define PLL_PFD_COUNT 4

/*! @brief PLL PFD name */
typedef enum _clock_pfd
{
    kCLOCK_Pfd0 = 0U, /*!< PLL PFD0 */
    kCLOCK_Pfd1 = 1U, /*!< PLL PFD1 */
    kCLOCK_Pfd2 = 2U, /*!< PLL PFD2 */
    kCLOCK_Pfd3 = 3U, /*!< PLL PFD3 */
} clock_pfd_t;

/*!
 * @brief The enumeration of control mode.
 *
 */
typedef enum _clock_control_mode
{
    kCLOCK_SoftwareMode = 0U, /*!< Software control mode. */
    kCLOCK_GpcMode,           /*!< GPC control mode. */
} clock_control_mode_t;

/*!
 * @brief The enumeration of 24MHz crystal oscillator mode.
 */
typedef enum _clock_24MOsc_mode
{
    kCLOCK_24MOscHighGainMode = 0U, /*!< 24MHz crystal oscillator work as high gain mode. */
    kCLOCK_24MOscBypassMode   = 1U, /*!< 24MHz crystal oscillator work as bypass mode. */
    kCLOCK_24MOscLowPowerMode = 2U, /*!< 24MHz crystal oscillator work as low power mode. */
} clock_24MOsc_mode_t;

/*!
 * @brief The enumeration of 1MHz output clock behavior, including disabling 1MHz output,
 * enabling locked 1MHz clock output, and enabling free-running 1MHz clock output.
 */
typedef enum _clock_1MHzOut_behavior
{
    kCLOCK_1MHzOutDisable               = 0U, /*!< Disable 1MHz output clock. */
    kCLOCK_1MHzOutEnableLocked1Mhz      = 1U, /*!< Enable 1MHz output clock, and select locked 1MHz to output. */
    kCLOCK_1MHzOutEnableFreeRunning1Mhz = 2U, /*!< Enable 1MHZ output clock,
                                                   and select free-running 1MHz to output. */
} clock_1MHzOut_behavior_t;

/*!
 * @brief The clock dependence level.
 */
typedef enum _clock_level
{
    kCLOCK_Level0 = 0x0UL, /*!< Not needed in any mode. */
    kCLOCK_Level1 = 0x1UL, /*!< Needed in RUN mode. */
    kCLOCK_Level2 = 0x2UL, /*!< Needed in RUN and WAIT mode. */
    kCLOCK_Level3 = 0x3UL, /*!< Needed in RUN, WAIT and STOP mode. */
    kCLOCK_Level4 = 0x4UL, /*!< Always on in any mode. */
} clock_level_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Set CCM Root Clock MUX node to certain value.
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 * @param src Clock mux value to set, different mux has different value range. See \ref clock_root_mux_source_t.
 */
static inline void CLOCK_SetRootClockMux(clock_root_t root, uint8_t src)
{
    assert(src < 8U);
    CCM->CLOCK_ROOT[root].CONTROL =
        (CCM->CLOCK_ROOT[root].CONTROL & ~(CCM_CLOCK_ROOT_CONTROL_MUX_MASK)) | CCM_CLOCK_ROOT_CONTROL_MUX(src);
    __DSB();
    __ISB();
#if __CORTEX_M == 33
    (void)CCM->CLOCK_ROOT[root].CONTROL;
#endif
}

/*!
 * @brief Get CCM Root Clock MUX value.
 *
 * @param root Which root clock node to get, see \ref clock_root_t.
 * @return Clock mux value.
 */
static inline uint32_t CLOCK_GetRootClockMux(clock_root_t root)
{
    return (CCM->CLOCK_ROOT[root].CONTROL & CCM_CLOCK_ROOT_CONTROL_MUX_MASK) >> CCM_CLOCK_ROOT_CONTROL_MUX_SHIFT;
}

/*!
 * @brief Get CCM Root Clock Source.
 *
 * @param root Which root clock node to get, see \ref clock_root_t.
 * @param src Clock mux value to get, see \ref clock_root_mux_source_t.
 * @return Clock source
 */
static inline clock_name_t CLOCK_GetRootClockSource(clock_root_t root, uint32_t src)
{
    return s_clockSourceName[root][src];
}

/*!
 * @brief Set CCM Root Clock DIV certain value.
 *
 * @param root Which root clock to set, see \ref clock_root_t.
 * @param div Clock div value to set, different divider has different value range.
 */
static inline void CLOCK_SetRootClockDiv(clock_root_t root, uint32_t div)
{
    assert(div);
    CCM->CLOCK_ROOT[root].CONTROL = (CCM->CLOCK_ROOT[root].CONTROL & ~CCM_CLOCK_ROOT_CONTROL_DIV_MASK) |
                                    CCM_CLOCK_ROOT_CONTROL_DIV((uint32_t)div - 1UL);
    __DSB();
    __ISB();
#if __CORTEX_M == 33
    (void)CCM->CLOCK_ROOT[root].CONTROL;
#endif
}

/*!
 * @brief Get CCM DIV node value.
 *
 * @param root Which root clock node to get, see \ref clock_root_t.
 * @return divider set for this root
 */
static inline uint32_t CLOCK_GetRootClockDiv(clock_root_t root)
{
    return ((CCM->CLOCK_ROOT[root].CONTROL & CCM_CLOCK_ROOT_CONTROL_DIV_MASK) >> CCM_CLOCK_ROOT_CONTROL_DIV_SHIFT) +
           1UL;
}

/*!
 * @brief Power Off Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 */
static inline void CLOCK_PowerOffRootClock(clock_root_t root)
{
    if (0UL == (CCM->CLOCK_ROOT[root].CONTROL & CCM_CLOCK_ROOT_CONTROL_OFF_MASK))
    {
        CCM->CLOCK_ROOT[root].CONTROL_SET = CCM_CLOCK_ROOT_CONTROL_OFF_MASK;
        __DSB();
        __ISB();
#if __CORTEX_M == 33
        (void)CCM->CLOCK_ROOT[root].CONTROL;
#endif
    }
}

/*!
 * @brief Power On Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 */
static inline void CLOCK_PowerOnRootClock(clock_root_t root)
{
    CCM->CLOCK_ROOT[root].CONTROL_CLR = CCM_CLOCK_ROOT_CONTROL_OFF_MASK;
    __DSB();
    __ISB();
#if __CORTEX_M == 33
    (void)CCM->CLOCK_ROOT[root].CONTROL;
#endif
}

/*!
 * @brief Configure Root Clock
 *
 * @param root Which root clock node to set, see \ref clock_root_t.
 * @param config root clock config, see \ref clock_root_config_t
 */
static inline void CLOCK_SetRootClock(clock_root_t root, const clock_root_config_t *config)
{
    assert(config);
    CCM->CLOCK_ROOT[root].CONTROL = CCM_CLOCK_ROOT_CONTROL_MUX(config->mux) |
                                    CCM_CLOCK_ROOT_CONTROL_DIV((uint32_t)config->div - 1UL) |
                                    (config->clockOff ? CCM_CLOCK_ROOT_CONTROL_OFF(config->clockOff) : 0UL);
    __DSB();
    __ISB();
#if __CORTEX_M == 33
    (void)CCM->CLOCK_ROOT[root].CONTROL;
#endif
}

/*!
 * @brief Control the clock gate for specific IP.
 *
 * @note This API will not have any effect when this clock is in CPULPM or SetPoint Mode
 *
 * @param name  Which clock to enable, see \ref clock_lpcg_t.
 * @param value Clock gate value to set, see \ref clock_gate_value_t.
 */
static inline void CLOCK_ControlGate(clock_ip_name_t name, clock_gate_value_t value)
{
    if (((uint32_t)value & CCM_LPCG_DIRECT_ON_MASK) != (CCM->LPCG[name].DIRECT & CCM_LPCG_DIRECT_ON_MASK))
    {
        CCM->LPCG[name].DIRECT = ((uint32_t)value & CCM_LPCG_DIRECT_ON_MASK);
        __DSB();
        __ISB();
#if __CORTEX_M == 33
        (void)CCM->LPCG[name].DIRECT;
#endif
    }
}

/*!
 * @brief Enable the clock for specific IP.
 *
 * @param name  Which clock to enable, see \ref clock_lpcg_t.
 */
static inline void CLOCK_EnableClock(clock_ip_name_t name)
{
    CLOCK_ControlGate(name, kCLOCK_On);
}

/*!
 * @brief Disable the clock for specific IP.
 *
 * @param name  Which clock to disable, see \ref clock_lpcg_t.
 */
static inline void CLOCK_DisableClock(clock_ip_name_t name)
{
    CLOCK_ControlGate(name, kCLOCK_Off);
}

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
 * @brief Gets the clock frequency for a specific root clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_root_t.
 *
 * @param root Clock names defined in clock_root_t
 * @return Clock frequency value in hertz
 */
static inline uint32_t CLOCK_GetRootClockFreq(clock_root_t root)
{
    uint32_t freq, mux;
    mux  = CLOCK_GetRootClockMux(root);
    freq = CLOCK_GetFreq(s_clockSourceName[root][mux]) / (CLOCK_GetRootClockDiv(root));
    assert(freq);
    return freq;
}

/*!
 * @brief Get the CCM CPU/core/system frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetM7Freq(void);

/*!
 * @brief Get the CCM CPU/core/system frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
uint32_t CLOCK_GetM33Freq(void);

/*!
 * @brief Check if PLL is bypassed
 *
 * @param pll PLL control name (see @ref clock_pll_t enumeration)
 * @return PLL bypass status.
 *         - true: The PLL is bypassed.
 *         - false: The PLL is not bypassed.
 */
static inline bool CLOCK_IsPllBypassed(clock_pll_t pll)
{
    if (pll == kCLOCK_PllArm)
    {
        return (bool)((ANADIG_PLL->ARM_PLL_CTRL & ANADIG_PLL_ARM_PLL_CTRL_BYPASS_MASK) >>
                      ANADIG_PLL_ARM_PLL_CTRL_BYPASS_SHIFT);
    }
    else if (pll == kCLOCK_PllSys2)
    {
        return (bool)((ANADIG_PLL->SYS_PLL2_CTRL & ANADIG_PLL_SYS_PLL2_CTRL_BYPASS_MASK) >>
                      ANADIG_PLL_SYS_PLL2_CTRL_BYPASS_SHIFT);
    }
    else if (pll == kCLOCK_PllSys3)
    {
        return (bool)((ANADIG_PLL->SYS_PLL3_CTRL & ANADIG_PLL_SYS_PLL3_CTRL_BYPASS_MASK) >>
                      ANADIG_PLL_SYS_PLL3_CTRL_BYPASS_SHIFT);
    }
    else
    {
        return false;
    }
}

/*!
 * @brief Check if PLL is enabled
 *
 * @param pll PLL control name (see @ref clock_pll_t enumeration)
 * @return PLL bypass status.
 *         - true: The PLL is enabled.
 *         - false: The PLL is not enabled.
 */
static inline bool CLOCK_IsPllEnabled(clock_pll_t pll)
{
    if (pll == kCLOCK_PllArm)
    {
        return (bool)((ANADIG_PLL->ARM_PLL_CTRL & ANADIG_PLL_ARM_PLL_CTRL_ENABLE_CLK_MASK) >>
                      ANADIG_PLL_ARM_PLL_CTRL_ENABLE_CLK_SHIFT);
    }
    else if (pll == kCLOCK_PllSys2)
    {
        return (bool)((ANADIG_PLL->SYS_PLL2_CTRL & ANADIG_PLL_SYS_PLL2_CTRL_ENABLE_CLK_MASK) >>
                      ANADIG_PLL_SYS_PLL2_CTRL_ENABLE_CLK_SHIFT);
    }
    else if (pll == kCLOCK_PllSys3)
    {
        return (bool)((ANADIG_PLL->SYS_PLL3_CTRL & ANADIG_PLL_SYS_PLL3_CTRL_ENABLE_CLK_MASK) >>
                      ANADIG_PLL_SYS_PLL3_CTRL_ENABLE_CLK_SHIFT);
    }
    else if (pll == kCLOCK_PllSys1)
    {
        return (bool)((ANADIG_PLL->SYS_PLL1_CTRL & ANADIG_PLL_SYS_PLL1_CTRL_ENABLE_CLK_MASK) >>
                      ANADIG_PLL_SYS_PLL1_CTRL_ENABLE_CLK_SHIFT);
    }
    else if (pll == kCLOCK_PllAudio)
    {
        return (bool)((ANADIG_PLL->PLL_AUDIO_CTRL & ANADIG_PLL_PLL_AUDIO_CTRL_ENABLE_CLK_MASK) >>
                      ANADIG_PLL_PLL_AUDIO_CTRL_ENABLE_CLK_SHIFT);
    }
    else
    {
        return false;
    }
}

/*!
 * @name OSC operations
 * @{
 */

/*!
 * @brief Gets the RTC clock frequency.
 *
 * @return  Clock frequency; If the clock is invalid, returns 0.
 */
static inline uint32_t CLOCK_GetRtcFreq(void)
{
    return 32768U;
}

/*!
 * @brief Set the control mode of a specifed clock.
 *
 * @param name Clock names defined in clock_name_t
 * @param controlMode The control mode to be set, please refer to @ref clock_control_mode_t.
 */
void CLOCK_SetClockSourceControlMode(clock_name_t name, clock_control_mode_t controlMode);

/*!
 * @brief Enable/disable 24MHz RC oscillator.
 *
 * @param enable Used to enable or disable the 24MHz RC oscillator.
 *          - \b true Enable the 24MHz RC oscillator.
 *          - \b false Dissable the 24MHz RC oscillator.
 */
static inline void CLOCK_OSC_EnableOscRc24M(bool enable)
{
    if (enable)
    {
        ANADIG_OSC->OSC_RC24M_CTRL |= ANADIG_OSC_OSC_RC24M_CTRL_TEN_MASK;
    }
    else
    {
        ANADIG_OSC->OSC_RC24M_CTRL &= ~ANADIG_OSC_OSC_RC24M_CTRL_TEN_MASK;
    }
}

/*! @brief Enable OSC 24Mhz
 *
 * This function enables OSC 24Mhz.
 */
void CLOCK_OSC_EnableOsc24M(void);

/*!
 * @brief Gate/ungate the 24MHz crystal oscillator output.
 *
 * @note Gating the 24MHz crystal oscillator can save power.
 *
 * @param enableGate Used to gate/ungate the 24MHz crystal oscillator.
 *          - \b true Gate the 24MHz crystal oscillator to save power.
 *          - \b false Ungate the 24MHz crystal oscillator.
 */
static inline void CLOCK_OSC_GateOsc24M(bool enableGate)
{
    if (enableGate)
    {
        ANADIG_OSC->OSC_24M_CTRL |= ANADIG_OSC_OSC_24M_CTRL_OSC_24M_GATE_MASK;
    }
    else
    {
        ANADIG_OSC->OSC_24M_CTRL &= ~ANADIG_OSC_OSC_24M_CTRL_OSC_24M_GATE_MASK;
    }
}

/*!
 * @brief Set the work mode of 24MHz crystal oscillator, the available modes are high gian mode, low power mode, and
 * bypass mode.
 *
 * @param workMode The work mode of 24MHz crystal oscillator, please refer to @ref clock_24MOsc_mode_t for details.
 */
void CLOCK_OSC_SetOsc24MWorkMode(clock_24MOsc_mode_t workMode);

/*! @brief Enable OSC RC 400Mhz
 *
 * This function enables OSC RC 400Mhz.
 */
void CLOCK_OSC_EnableOscRc400M(void);

/*!
 * @brief Gate/ungate 400MHz RC oscillator.
 *
 * @param enableGate Used to gate/ungate 400MHz RC oscillator.
 *          - \b true Gate the 400MHz RC oscillator.
 *          - \b false Ungate the 400MHz RC oscillator.
 */
static inline void CLOCK_OSC_GateOscRc400M(bool enableGate)
{
    if (enableGate)
    {
        ANADIG_OSC->OSC_400M_CTRL1 |= ANADIG_OSC_OSC_400M_CTRL1_CLKGATE_400MEG_MASK;
    }
    else
    {
        ANADIG_OSC->OSC_400M_CTRL1 &= ~ANADIG_OSC_OSC_400M_CTRL1_CLKGATE_400MEG_MASK;
    }
}

/*!
 * @brief Trims OSC RC 400MHz.
 *
 * @param enable Used to enable trim function.
 * @param bypass Bypass the trim function.
 * @param trim Trim value.
 */
void CLOCK_OSC_TrimOscRc400M(bool enable, bool bypass, uint16_t trim);

/*!
 * @brief Set the divide value for ref_clk to generate slow clock.
 *
 * @note slow_clk = ref_clk / (divValue + 1), and the recommand divide value is 24.
 *
 * @param divValue The divide value to be set, the available range is 0~63.
 */
void CLOCK_OSC_SetOscRc400MRefClkDiv(uint8_t divValue);

/*!
 * @brief Set the target count for the fast clock.
 *
 * @param targetCount The desired target for the fast clock, should be the number of clock cycles of the fast_clk per
 * divided ref_clk.
 */
void CLOCK_OSC_SetOscRc400MFastClkCount(uint16_t targetCount);

/*!
 * @brief Set the negative and positive hysteresis value for the tuned clock.
 *
 * @note The hysteresis value should be set after the clock is tuned.
 *
 * @param negHysteresis The negative hysteresis value for the turned clock, this value in number of clock cycles of the
 * fast clock
 * @param posHysteresis The positive hysteresis value for the turned clock, this value in number of clock cycles of the
 * fast clock
 */
void CLOCK_OSC_SetOscRc400MHysteresisValue(uint8_t negHysteresis, uint8_t posHysteresis);

/*!
 * @brief Bypass/un-bypass the tune logic
 *
 * @param enableBypass Used to control whether to bypass the turn logic.
 *        - \b true Bypass the tune logic and use the programmed oscillator frequency to run the oscillator.
 *                  Function CLOCK_OSC_SetOscRc400MTuneValue() can be used to set oscillator frequency.
 *        - \b false Use the output of tune logic to run the oscillator.
 */
void CLOCK_OSC_BypassOscRc400MTuneLogic(bool enableBypass);

/*!
 * @brief Start/Stop the tune logic.
 *
 * @param enable Used to start or stop the tune logic.
 *          - \b true Start tuning
 *          - \b false Stop tuning and reset the tuning logic.
 */
void CLOCK_OSC_EnableOscRc400MTuneLogic(bool enable);

/*!
 * @brief Freeze/Unfreeze the tuning value.
 *
 * @param enableFreeze Used to control whether to freeze the tune value.
 *          - \b true Freeze the tune at the current tuned value and the oscillator runs at tje frozen tune value.
 *          - \b false Unfreezes and continues the tune operation.
 */
void CLOCK_OSC_FreezeOscRc400MTuneValue(bool enableFreeze);

/*!
 * @brief Set the 400MHz RC oscillator tune value when the tune logic is disabled.
 *
 * @param tuneValue The tune value to determine the frequency of Oscillator.
 */
void CLOCK_OSC_SetOscRc400MTuneValue(uint8_t tuneValue);

/*!
 * @brief Set the behavior of the 1MHz output clock, such as disable the 1MHz clock output,
 * enable the free-running 1MHz clock output, enable the locked 1MHz clock output.
 *
 * @note The 1MHz clock is divided from 400M RC Oscillator.
 *
 * @param behavior The behavior of 1MHz output clock, please refer to @ref clock_1MHzOut_behavior_t for details.
 */
void CLOCK_OSC_Set1MHzOutputBehavior(clock_1MHzOut_behavior_t behavior);

/*!
 * @brief Set the count for the locked 1MHz clock out.
 *
 * @param count Used to set the desired target for the locked 1MHz clock out, the value in number of clock cycles of the
 * fast clock per divided ref_clk.
 */
void CLOCK_OSC_SetLocked1MHzCount(uint16_t count);

/*!
 * @brief Check the error flag for locked 1MHz clock out.
 *
 * @return The error flag for locked 1MHz clock out.
 *      - \b true The count value has been reached within one diviced ref clock period
 *      - \b false No effect.
 */
bool CLOCK_OSC_CheckLocked1MHzErrorFlag(void);

/*!
 * @brief Clear the error flag for locked 1MHz clock out.
 */
void CLOCK_OSC_ClearLocked1MHzErrorFlag(void);

/*!
 * @brief Get current count for the fast clock during the tune process.
 *
 * @return The current count for the fast clock.
 */
uint16_t CLOCK_OSC_GetCurrentOscRc400MFastClockCount(void);

/*!
 * @brief Get current tune value used by oscillator during tune process.
 *
 * @return The current tune value.
 */
uint8_t CLOCK_OSC_GetCurrentOscRc400MTuneValue(void);

/* @} */

/*!
 * @brief Initialize the ARM PLL.
 *
 * This function initialize the ARM PLL with specific settings
 *
 * @param config   configuration to set to PLL.
 */
void CLOCK_InitArmPll(const clock_arm_pll_config_t *config);

/*!
 * @brief Calculate corresponding config values per given frequency
 *
 * This function calculates config valudes per given frequency for Arm PLL
 *
 * @param config pll config structure
 * @param freqInMhz target frequency
 */
status_t CLOCK_CalcArmPllFreq(clock_arm_pll_config_t *config, uint32_t freqInMhz);

/*!
 * @brief Initializes the Arm PLL with Specific Frequency (in Mhz).
 *
 * This function initializes the Arm PLL with specific frequency
 *
 * @param freqInMhz target frequency
 */
status_t CLOCK_InitArmPllWithFreq(uint32_t freqInMhz);

/*!
 * @brief De-initialize the ARM PLL.
 */
void CLOCK_DeinitArmPll(void);

/*!
 * @brief Calculate spread spectrum step and stop.
 *
 * This function calculate spread spectrum step and stop according to given
 * parameters. For integer PLL (syspll2) the factor is mfd, while for other
 * fractional PLLs (audio/syspll1), the factor is denominator.
 *
 * @param factor factor to calculate step/stop
 * @param range spread spectrum range
 * @param mod spread spectrum modulation frequency
 * @param ss calculated spread spectrum values
 *
 */
void CLOCK_CalcPllSpreadSpectrum(uint32_t factor, uint32_t range, uint32_t mod, clock_pll_ss_config_t *ss);

/*!
 * @brief Initialize the System PLL1.
 *
 * This function initializes the System PLL1 with specific settings
 *
 * @param config Configuration to set to PLL1.
 */
void CLOCK_InitSysPll1(const clock_sys_pll1_config_t *config);

/*!
 * @brief De-initialize the System PLL1.
 */
void CLOCK_DeinitSysPll1(void);

/*!
 * @brief Initialize the System PLL2.
 *
 * This function initializes the System PLL2 with specific settings
 *
 * @param config Configuration to configure spread spectrum. This parameter can
 *            be NULL, if no need to enabled spread spectrum
 */
void CLOCK_InitSysPll2(const clock_sys_pll2_config_t *config);

/*!
 * @brief De-initialize the System PLL2.
 */
void CLOCK_DeinitSysPll2(void);

/*!
 * @brief Check if Sys PLL2 PFD is enabled
 *
 * @param pfd PFD control name
 * @return PFD bypass status.
 *         - true: power on.
 *         - false: power off.
 * @note Only useful in software control mode.
 */
bool CLOCK_IsSysPll2PfdEnabled(clock_pfd_t pfd);

/*!
 * @brief Initialize the System PLL3.
 *
 * This function initializes the System PLL3 with specific settings
 *
 */
void CLOCK_InitSysPll3(void);

/*!
 * @brief De-initialize the System PLL3.
 */
void CLOCK_DeinitSysPll3(void);

/*!
 * @brief Check if Sys PLL3 PFD is enabled
 *
 * @param pfd PFD control name
 * @return PFD bypass status.
 *         - true: power on.
 *         - false: power off.
 * @note Only useful in software control mode.
 */
bool CLOCK_IsSysPll3PfdEnabled(clock_pfd_t pfd);

/*!
 * @name PLL/PFD operations
 * @{
 */
/*!
 * @brief PLL bypass setting
 *
 * @param pll PLL control name (see @ref clock_pll_t enumeration)
 * @param bypass Bypass the PLL.
 *               - true: Bypass the PLL.
 *               - false:Not bypass the PLL.
 */
void CLOCK_SetPllBypass(clock_pll_t pll, bool bypass);

/*!
 * @brief Calculate corresponding config values per given frequency
 *
 * This function calculates config valudes per given frequency for Audio PLL.
 *
 * @param config pll config structure
 * @param freqInMhz target frequency
 */
status_t CLOCK_CalcAudioPllFreq(clock_audio_pll_config_t *config, uint32_t freqInMhz);

/*!
 * @brief Initializes the Audio PLL with Specific Frequency (in Mhz).
 *
 * This function initializes the Audio PLL with specific frequency
 *
 * @param freqInMhz target frequency
 * @param ssEnable  enable spread spectrum or not
 * @param ssRange   range spread spectrum range
 * @param ssMod spread spectrum modulation frequency
 */
status_t CLOCK_InitAudioPllWithFreq(uint32_t freqInMhz, bool ssEnable, uint32_t ssRange, uint32_t ssMod);

/*!
 * @brief Initializes the Audio PLL.
 *
 * This function initializes the Audio PLL with specific settings
 *
 * @param config Configuration to set to PLL.
 */
void CLOCK_InitAudioPll(const clock_audio_pll_config_t *config);

/*!
 * @brief De-initialize the Audio PLL.
 */
void CLOCK_DeinitAudioPll(void);

/*!
 * @brief Get current PLL output frequency.
 *
 * This function get current output frequency of specific PLL
 *
 * @param pll   pll name to get frequency.
 * @return The PLL output frequency in hertz.
 */
uint32_t CLOCK_GetPllFreq(clock_pll_t pll);

/*!
 * @brief Initialize PLL PFD.
 *
 * This function initializes the System PLL PFD. During new value setting,
 * the clock output is disabled to prevent glitch.
 *
 * @param pll Which PLL of targeting PFD to be operated.
 * @param pfd Which PFD clock to enable.
 * @param frac The PFD FRAC value.
 * @note It is recommended that PFD settings are kept between 13-35.
 */
void CLOCK_InitPfd(clock_pll_t pll, clock_pfd_t pfd, uint8_t frac);

/*!
 * @brief De-initialize selected PLL PFD.
 *
 * @param pll Which PLL of targeting PFD to be operated.
 * @param pfd Which PFD clock to enable.
 */
void CLOCK_DeinitPfd(clock_pll_t pll, clock_pfd_t pfd);

/*!
 * @brief Get current PFD output frequency.
 *
 * This function get current output frequency of specific System PLL PFD
 *
 * @param pll Which PLL of targeting PFD to be operated.
 * @param pfd pfd name to get frequency.
 * @return The PFD output frequency in hertz.
 */
uint32_t CLOCK_GetPfdFreq(clock_pll_t pll, clock_pfd_t pfd);

uint32_t CLOCK_GetFreqFromObs(uint8_t obsIndex, uint32_t obsSigIndex);

#if !(defined(MIMXRT1181_SERIES) || defined(MIMXRT1182_SERIES))
/*! @brief Enable USB HS clock.
 *
 * This function only enables the access to USB HS prepheral, upper layer
 * should first call the @ref CLOCK_EnableUsbhs0PhyPllClock to enable the PHY
 * clock to use USB HS.
 *
 * @param src  USB HS does not care about the clock source, here must be @ref kCLOCK_UsbSrcUnused.
 * @param freq USB HS does not care about the clock source, so this parameter is ignored.
 * @retval true The clock is set successfully.
 * @retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs0Clock(clock_usb_src_t src, uint32_t freq);

/*! @brief Enable USB HS clock.
 *
 * This function only enables the access to USB HS prepheral, upper layer
 * should first call the @ref CLOCK_EnableUsbhs0PhyPllClock to enable the PHY
 * clock to use USB HS.
 *
 * @param src  USB HS does not care about the clock source, here must be @ref kCLOCK_UsbSrcUnused.
 * @param freq USB HS does not care about the clock source, so this parameter is ignored.
 * @retval true The clock is set successfully.
 * @retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs1Clock(clock_usb_src_t src, uint32_t freq);

/*! @brief Enable USB HS PHY PLL clock.
 *
 * This function enables the internal 480MHz USB PHY PLL clock.
 *
 * @param src  USB HS PHY PLL clock source.
 * @param freq The frequency specified by src.
 * @retval true The clock is set successfully.
 * @retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs0PhyPllClock(clock_usb_phy_src_t src, uint32_t freq);

/*! @brief Disable USB HS PHY PLL clock.
 *
 * This function disables USB HS PHY PLL clock.
 */
void CLOCK_DisableUsbhs0PhyPllClock(void);

/*! @brief Enable USB HS PHY PLL clock.
 *
 * This function enables the internal 480MHz USB PHY PLL clock.
 *
 * @param src  USB HS PHY PLL clock source.
 * @param freq The frequency specified by src.
 * @retval true The clock is set successfully.
 * @retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs1PhyPllClock(clock_usb_phy_src_t src, uint32_t freq);

/*! @brief Disable USB HS PHY PLL clock.
 *
 * This function disables USB HS PHY PLL clock.
 */
void CLOCK_DisableUsbhs1PhyPllClock(void);
#endif

/*!
 * @brief Lock the value of Domain ID white list for this clock.
 *
 * @note Once locked, this bit and domain ID white list can not be changed until next system reset.
 *
 * @param name Clock source name, see \ref clock_name_t.
 */
static inline void CLOCK_OSCPLL_LockWhiteList(clock_name_t name)
{
    CCM->OSCPLL[name].AUTHEN |= CCM_OSCPLL_AUTHEN_LOCK_LIST_MASK;
}

/*!
 * @brief Set domain ID that can change this clock.
 *
 * @note If LOCK_LIST bit is set, domain ID white list can not be changed until next system reset.
 *
 * @param name Clock source name, see \ref clock_name_t.
 * @param domainId Domains that on the whitelist can change this clock.
 */
static inline void CLOCK_OSCPLL_SetWhiteList(clock_name_t name, uint8_t domainId)
{
    CCM->OSCPLL[name].AUTHEN =
        (CCM->OSCPLL[name].AUTHEN & ~CCM_OSCPLL_AUTHEN_WHITE_LIST_MASK) | CCM_OSCPLL_AUTHEN_WHITE_LIST(domainId);
}

/*!
 * @brief Set this clock works in CPU Low Power Mode.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock source name, see \ref clock_name_t.
 * @param domainMap Domains that on the whitelist can change this clock.
 * @param level Depend level of this clock.
 */
void CLOCK_OSCPLL_ControlByCpuLowPowerMode(clock_name_t name, uint32_t domainMap, clock_level_t level);

/*!
 * @brief Lock the value of Domain ID white list for this clock.
 *
 * @note Once locked, this bit and domain ID white list can not be changed until next system reset.
 *
 * @param name Clock root name, see \ref clock_root_t.
 */
static inline void CLOCK_ROOT_LockWhiteList(clock_root_t name)
{
    CCM->CLOCK_ROOT[name].AUTHEN |= CCM_CLOCK_ROOT_AUTHEN_LOCK_LIST_MASK;
}

/*!
 * @brief Set domain ID that can change this clock.
 *
 * @note If LOCK_LIST bit is set, domain ID white list can not be changed until next system reset.
 *
 * @param name Clock root name, see \ref clock_root_t.
 * @param domainId Domains that on the whitelist can change this clock.
 */
static inline void CLOCK_ROOT_SetWhiteList(clock_root_t name, uint8_t domainId)
{
    CCM->CLOCK_ROOT[name].AUTHEN = (CCM->CLOCK_ROOT[name].AUTHEN & ~CCM_CLOCK_ROOT_AUTHEN_WHITE_LIST_MASK) |
                                   CCM_CLOCK_ROOT_AUTHEN_WHITE_LIST(domainId);
}

/*!
 * @brief Lock the value of Domain ID white list for this clock.
 *
 * @note Once locked, this bit and domain ID white list can not be changed until next system reset.
 *
 * @param name Clock gate name, see \ref clock_lpcg_t.
 */
static inline void CLOCK_LPCG_LockWhiteList(clock_lpcg_t name)
{
    CCM->LPCG[name].AUTHEN |= CCM_LPCG_AUTHEN_LOCK_LIST_MASK;
}

/*!
 * @brief Set domain ID that can change this clock.
 *
 * @note If LOCK_LIST bit is set, domain ID white list can not be changed until next system reset.
 *
 * @param name Clock gate name, see \ref clock_lpcg_t.
 * @param domainId Domains that on the whitelist can change this clock.
 */
static inline void CLOCK_LPCG_SetWhiteList(clock_lpcg_t name, uint8_t domainId)
{
    CCM->LPCG[name].AUTHEN =
        (CCM->LPCG[name].AUTHEN & ~CCM_LPCG_AUTHEN_WHITE_LIST_MASK) | CCM_LPCG_AUTHEN_WHITE_LIST(domainId);
}

/*!
 * @brief Set this clock works in CPU Low Power Mode.
 *
 * @note When LOCK_MODE bit is set, control mode can not be changed until next system reset.
 *
 * @param name Clock gate name, see \ref clock_lpcg_t.
 * @param domainMap Domains that on the whitelist can change this clock.
 * @param level Depend level of this clock.
 */
void CLOCK_LPCG_ControlByCpuLowPowerMode(clock_lpcg_t name, uint32_t domainMap, clock_level_t level);

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
