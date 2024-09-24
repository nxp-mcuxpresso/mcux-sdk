/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_CLOCK_H_
#define FSL_CLOCK_H_

#include "fsl_common.h"
#include "fsl_device_registers.h"
#include "fsl_reset.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

/*! @addtogroup clock */
/*! @{ */

/*! @file */

/*******************************************************************************
 * Definitions
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.3.1 */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 3, 1))
/*@}*/

#if defined(MIMXRT798S_hifi1_SERIES) || defined(MIMXRT798S_cm33_core1_SERIES) || \
    defined(MIMXRT758S_cm33_core1_SERIES) || defined(MIMXRT735S_cm33_core1_SERIES)
#define FSL_CLOCK_DRIVER_SENSE
#elif defined(MIMXRT798S_hifi4_SERIES) || defined(MIMXRT798S_cm33_core0_SERIES) || \
    defined(MIMXRT758S_cm33_core0_SERIES) || defined(MIMXRT735S_cm33_core0_SERIES)
#define FSL_CLOCK_DRIVER_COMPUTE
#elif defined(MIMXRT798S_ezhv_SERIES) || defined(MIMXRT758S_ezhv_SERIES) || defined(MIMXRT735S_ezhv_SERIES)
#define FSL_CLOCK_DRIVER_MEDIA
#else
#error "Unsupported core!"
#endif

/* Definition for delay API in clock driver, users can redefine it to the real
 * application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#if defined(FSL_CLOCK_DRIVER_SENSE)
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (100000000UL)
#elif defined(FSL_CLOCK_DRIVER_COMPUTE)
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (300000000UL)
#elif defined(FSL_CLOCK_DRIVER_MEDIA)
/* EZHV process clock is m_clk. */
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (300UL * 1000UL * 1000UL)
#endif /* FSL_CLOCK_DRIVER_SENSE */
#endif /* SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY */

/* Definition for compatiblity. */
#define CLOCK_DeinitSysPfd CLOCK_DeinitMainPfd
#define CLOCK_InitSysPfd   CLOCK_InitMainPfd

/*! @brief External XTAL (SYSOSC) clock frequency.
 *
 * The XTAL (SYSOSC) clock frequency in Hz, when the clock is setup, use the
 * function CLOCK_SetXtalFreq to set the value in to clock driver. For example,
 * if XTAL is 16MHz,
 * @code
 * CLOCK_SetXtalFreq(160000000);
 * @endcode
 */
extern volatile uint32_t g_xtalFreq;

/*! @brief External CLK_IN pin clock frequency (clkin).
 *
 * The CLK_IN pin (clkin) clock frequency in Hz, when the clock is setup, use
 * the function CLOCK_SetClkinFreq to set the value in to clock driver. For
 * example, if CLK_IN is 16MHz,
 * @code
 * CLOCK_SetClkinFreq(160000000);
 * @endcode
 */
extern volatile uint32_t g_clkinFreq;

/*! @brief External 32KHz input clock frequency.
 *
 * The External 32KHz input clock frequency in Hz, used when OSC32KNP in bypass mode, use
 * the function CLOCK_Set32kClkinFreq to set the value in to clock driver. For
 * example, if EXTALIN32K input is 32768,
 * @code
 * CLOCK_Set32kClkinFreq(32768);
 * @endcode
 */
extern volatile uint32_t g_32kClkinFreq;

/*! @brief External MCLK IN clock frequency.
 *
 * The MCLK IN clock frequency in Hz, when the clock is setup, use the
 * function CLOCK_SetMclkFreq to set the value in to clock driver. For example,
 * if MCLK IN is 16MHz,
 * @code
 * CLOCK_SetMclkFreq(160000000);
 * @endcode
 */
extern volatile uint32_t g_mclkFreq;

#if defined(FSL_CLOCK_DRIVER_COMPUTE)
/*! @brief VDD1(Sense) audio_clk clock frequency.
 *
 *NOTE, The compute domain can't read the Sense VDD1 audio_clk selection. The compute domain need call
 *CLOCK_SetSenseAudioClkFreq() to tell the clock driver the frequncy of current VDD1 audio_clk, and then
 *CLOCK_GetSenseAudioClkFreq() can return the correct value.
 * @code
 * CLOCK_SetSenseAudioClkFreq(24000000);
 * @endcode
 */
extern volatile uint32_t g_senseAudioClkFreq;
#endif

/*! @brief Clock ip name array for CDOG. */
#define CDOG_CLOCKS                                                          \
    {                                                                        \
        kCLOCK_Cdog0, kCLOCK_Cdog1, kCLOCK_Cdog2, kCLOCK_Cdog3, kCLOCK_Cdog4 \
    }

/*! @brief Clock ip name array for FREQME. */
#define FREQME_CLOCKS  \
    {                  \
        kCLOCK_Freqme0 \
    }

/*! @brief Clock ip name array for GPU. */
#define GPU_CLOCKS \
    {              \
        kCLOCK_Gpu \
    }

/*! @brief Clock ip name array for MIPI DSI. */
#define MIPI_DSI_HOST_CLOCKS \
    {                        \
        kCLOCK_MipiDsiCtrl   \
    }

/*! @brief Clock ip name array for LCDIF. */
#define LCDIF_CLOCKS \
    {                \
        kCLOCK_Lcdif \
    }

/*! @brief Clock ip name array for SCT. */
#define SCT_CLOCKS  \
    {               \
        kCLOCK_Sct0 \
    }

/*! @brief Clock ip name array for USB. */
#define USB_CLOCKS               \
    {                            \
        kCLOCK_Usb0, kCLOCK_Usb1 \
    }

/*! @brief Clock ip name array for USBPHY. */
#define USBPHY_CLOCKS                  \
    {                                  \
        kCLOCK_Usbphy0, kCLOCK_Usbphy1 \
    }

/*! @brief Clock ip name array for FlexSPI */
#define XSPI_CLOCKS                              \
    {                                            \
        kCLOCK_Xspi0, kCLOCK_Xspi1, kCLOCK_Xspi2 \
    }

/*! @brief Clock ip name array for MMU */
#define MMU_CLOCKS                            \
    {                                         \
        kCLOCK_Mmu0, kCLOCK_Mmu1, kCLOCK_Mmu2 \
    }

/*! @brief Clock ip name array for CACHE64 */
#define CACHE64_CLOCKS                           \
    {                                            \
        kCLOCK_Cache64ctrl0, kCLOCK_Cache64ctrl1 \
    }

/*! @brief Clock ip name array for CACHE64_POLSEL */
#define CACHE64POLSEL_CLOCKS                         \
    {                                                \
        kCLOCK_Cache64Polsel0, kCLOCK_Cache64Polsel1 \
    }

/*! @brief Clock ip name array for ADC. */
#define LPADC_CLOCKS \
    {                \
        kCLOCK_Adc0  \
    }

/*! @brief Clock ip name array for SDADC. */
#define SDADC_CLOCKS  \
    {                 \
        kCLOCK_Sdadc0 \
    }

/*! @brief Clock ip name array for ACMP. */
#define CMP_CLOCKS   \
    {                \
        kCLOCK_Acmp0 \
    }

/*! @brief Clock ip name array for uSDHC */
#define USDHC_CLOCKS                 \
    {                                \
        kCLOCK_Usdhc0, kCLOCK_Usdhc1 \
    }

/*! @brief Clock ip name array for WWDT. */
#define WWDT_CLOCKS                                            \
    {                                                          \
        kCLOCK_Wwdt0, kCLOCK_Wwdt1, kCLOCK_Wwdt2, kCLOCK_Wwdt3 \
    }

/*! @brief Clock ip name array for UTICK. */
#define UTICK_CLOCKS                 \
    {                                \
        kCLOCK_Utick0, kCLOCK_Utick1 \
    }

/*! @brief Clock ip name array for FlexIO. */
#define FLEXIO_CLOCKS \
    {                 \
        kCLOCK_Flexio \
    }

/*! @brief Clock ip name array for LP_FLEXCOMM. */
#define LP_FLEXCOMM_CLOCKS                                                                                        \
    {                                                                                                             \
        kCLOCK_LPFlexComm0, kCLOCK_LPFlexComm1, kCLOCK_LPFlexComm2, kCLOCK_LPFlexComm3, kCLOCK_LPFlexComm4,       \
            kCLOCK_LPFlexComm5, kCLOCK_LPFlexComm6, kCLOCK_LPFlexComm7, kCLOCK_LPFlexComm8, kCLOCK_LPFlexComm9,   \
            kCLOCK_LPFlexComm10, kCLOCK_LPFlexComm11, kCLOCK_LPFlexComm12, kCLOCK_LPFlexComm13, kCLOCK_IpInvalid, \
            kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_LPFlexComm17, kCLOCK_LPFlexComm18, kCLOCK_LPFlexComm19,    \
            kCLOCK_LPFlexComm20                                                                                   \
    }
/*! @brief Clock ip name array for LPUART. */
#define LPUART_CLOCKS                                                                                                \
    {                                                                                                                \
        kCLOCK_LPUart0, kCLOCK_LPUart1, kCLOCK_LPUart2, kCLOCK_LPUart3, kCLOCK_LPUart4, kCLOCK_LPUart5,              \
            kCLOCK_LPUart6, kCLOCK_LPUart7, kCLOCK_LPUart8, kCLOCK_LPUart9, kCLOCK_LPUart10, kCLOCK_LPUart11,        \
            kCLOCK_LPUart12, kCLOCK_LPUart13, kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_LPUart17, \
            kCLOCK_LPUart18, kCLOCK_LPUart19, kCLOCK_LPUart20                                                        \
    }
/*! @brief Clock ip name array for LPI2C. */
#define LPI2C_CLOCKS                                                                                             \
    {                                                                                                            \
        kCLOCK_LPI2c0, kCLOCK_LPI2c1, kCLOCK_LPI2c2, kCLOCK_LPI2c3, kCLOCK_LPI2c4, kCLOCK_LPI2c5, kCLOCK_LPI2c6, \
            kCLOCK_LPI2c7, kCLOCK_LPI2c8, kCLOCK_LPI2c9, kCLOCK_LPI2c10, kCLOCK_LPI2c11, kCLOCK_LPI2c12,         \
            kCLOCK_LPI2c13, kCLOCK_IpInvalid, kCLOCK_LPI2c15, kCLOCK_IpInvalid, kCLOCK_LPI2c17, kCLOCK_LPI2c18,  \
            kCLOCK_LPI2c19, kCLOCK_LPI2c20                                                                       \
    }
/*! @brief Clock ip name array for LSPI. */
#define LPSPI_CLOCKS                                                                                             \
    {                                                                                                            \
        kCLOCK_LPSpi0, kCLOCK_LPSpi1, kCLOCK_LPSpi2, kCLOCK_LPSpi3, kCLOCK_LPSpi4, kCLOCK_LPSpi5, kCLOCK_LPSpi6, \
            kCLOCK_LPSpi7, kCLOCK_LPSpi8, kCLOCK_LPSpi9, kCLOCK_LPSpi10, kCLOCK_LPSpi11, kCLOCK_LPSpi12,         \
            kCLOCK_LPSpi13, kCLOCK_LPSpi14, kCLOCK_IpInvalid, kCLOCK_LPSpi16, kCLOCK_LPSpi17, kCLOCK_LPSpi18,    \
            kCLOCK_LPSpi19, kCLOCK_LPSpi20                                                                       \
    }
/*! @brief Clock ip name array for SAI. */
#define SAI_CLOCKS                                         \
    {                                                      \
        kCLOCK_Sai0, kCLOCK_Sai1, kCLOCK_Sai2, kCLOCK_Sai3 \
    }

/*! @brief Clock ip name array for SEMA */
#define SEMA42_CLOCKS                                                                      \
    {                                                                                      \
        kCLOCK_Sema420, kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_Sema423, kCLOCK_Sema424 \
    }

/*! @brief Clock ip name array for MU */
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
#ifndef __XTENSA__
#define MU_CLOCKS                          \
    {                                      \
        kCLOCK_Mu0, kCLOCK_Mu1, kCLOCK_Mu4 \
    }
#else
#define MU_CLOCKS              \
    {                          \
        kCLOCK_Mu2, kCLOCK_Mu4 \
    }
#endif /* __XTENSA__ */

/*! @brief Clock ip name array for DMA. */
#define EDMA_CLOCKS              \
    {                            \
        kCLOCK_Dma0, kCLOCK_Dma1 \
    }

/*! @brief Clock ip name array for SYSPM. */
#define SYSPM_CLOCKS                                                     \
    {                                                                    \
        kCLOCK_Syspm0, kCLOCK_Syspm1, kCLOCK_IpInvalid, kCLOCK_IpInvalid \
    }

/*! @brief Clock ip name array for TRNG. */
#define TRNG_CLOCKS    \
    {                  \
        kCLOCK_TrngRef \
    }

#endif /* FSL_CLOCK_DRIVER_COMPUTE */

#if defined(FSL_CLOCK_DRIVER_SENSE)
#ifndef __XTENSA__
#define MU_CLOCKS                          \
    {                                      \
        kCLOCK_Mu1, kCLOCK_Mu2, kCLOCK_Mu3 \
    }
#else
#define MU_CLOCKS              \
    {                          \
        kCLOCK_Mu0, kCLOCK_Mu3 \
    }
#endif /* __XTENSA__ */

/*! @brief Clock ip name array for DMA. */
#define EDMA_CLOCKS              \
    {                            \
        kCLOCK_Dma2, kCLOCK_Dma3 \
    }
#endif /* FSL_CLOCK_DRIVER_SENSE */

/*! @brief Clock ip name array for CRC. */
#define CRC_CLOCKS  \
    {               \
        kCLOCK_Crc0 \
    }

#if defined(FSL_CLOCK_DRIVER_COMPUTE)
/*! @brief Clock ip name array for GDET. */
#define GDET_CLOCKS                                            \
    {                                                          \
        kCLOCK_Gdet0, kCLOCK_Gdet1, kCLOCK_Gdet2, kCLOCK_Gdet3 \
    }

/*! @brief Clock ip name array for GDET_REF. */
#define GDET_REF_CLOCKS                                                    \
    {                                                                      \
        kCLOCK_Gdet0Ref, kCLOCK_Gdet1Ref, kCLOCK_Gdet2Ref, kCLOCK_Gdet3Ref \
    }
#endif
#if defined(FSL_CLOCK_DRIVER_SENSE)
/*! @brief Clock ip name array for GDET. */
#define GDET_CLOCKS                                                    \
    {                                                                  \
        kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_Gdet2, kCLOCK_Gdet3 \
    }

/*! @brief Clock ip name array for GDET_REF. */
#define GDET_REF_CLOCKS                                                      \
    {                                                                        \
        kCLOCK_IpInvalid, kCLOCK_IpInvalid, kCLOCK_Gdet2Ref, kCLOCK_Gdet3Ref \
    }
#endif

/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS                                                                                            \
    {                                                                                                          \
        kCLOCK_Gpio0, kCLOCK_Gpio1, kCLOCK_Gpio2, kCLOCK_Gpio3, kCLOCK_Gpio4, kCLOCK_Gpio5, kCLOCK_Gpio6,      \
            kCLOCK_Gpio7, kCLOCK_Gpio8, kCLOCK_Gpio9, kCLOCK_Gpio10, kCLOCK_Gpio0, kCLOCK_Gpio1, kCLOCK_Gpio2, \
            kCLOCK_Gpio3, kCLOCK_Gpio4, kCLOCK_Gpio5, kCLOCK_Gpio6, kCLOCK_Gpio7, kCLOCK_Gpio8, kCLOCK_Gpio9,  \
            kCLOCK_Gpio10                                                                                      \
    }

/*! @brief Clock ip name array for PDM. */
#define PDM_CLOCKS \
    {              \
        kCLOCK_Pdm \
    }

/*! @brief Clock ip name array for PINT. */
#define PINT_CLOCKS \
    {               \
        kCLOCK_Pint \
    }

/*! @brief Clock ip name array for PNGDEC. */
#define PNGDEC_CLOCKS     \
    {                     \
        kCLOCK_PngDecoder \
    }

/*! @brief Clock ip name array for JPEGDEC. */
#define JPEGDEC_CLOCKS    \
    {                     \
        kCLOCK_JpgDecoder \
    }

/*! @brief Clock ip name array for I3C. */
#define I3C_CLOCKS                                         \
    {                                                      \
        kCLOCK_I3c0, kCLOCK_I3c1, kCLOCK_I3c2, kCLOCK_I3c3 \
    }

/*! @brief Clock ip name array for MRT. */
#define MRT_CLOCKS               \
    {                            \
        kCLOCK_Mrt0, kCLOCK_Mrt1 \
    }

/*! @brief Clock ip name array for CT32B. */
#define CTIMER_CLOCKS                                                                                            \
    {                                                                                                            \
        kCLOCK_Ct32b0, kCLOCK_Ct32b1, kCLOCK_Ct32b2, kCLOCK_Ct32b3, kCLOCK_Ct32b4, kCLOCK_Ct32b5, kCLOCK_Ct32b6, \
            kCLOCK_Ct32b7                                                                                        \
    }

/*! @brief Clock ip name array for OSTIMER. */
#define OSTIMER_CLOCKS \
    {                  \
        kCLOCK_OsTimer \
    }

/*! @brief Clock ip name array for RTC. */
#define RTC_CLOCKS \
    {              \
        kCLOCK_Rtc \
    }

/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
/*------------------------------------------------------------------------------
 clock_ip_name_t definition:
------------------------------------------------------------------------------*/
#define CLK_GATE_REG_OFFSET_SHIFT 8U
#define CLK_GATE_REG_OFFSET_MASK  0xFF00U
#define CLK_GATE_BIT_SHIFT_SHIFT  0U
#define CLK_GATE_BIT_SHIFT_MASK   0x00FFU

#define CLK_GATE_DEFINE(reg_offset, bit_shift)                                  \
    ((((reg_offset) << CLK_GATE_REG_OFFSET_SHIFT) & CLK_GATE_REG_OFFSET_MASK) | \
     (((bit_shift) << CLK_GATE_BIT_SHIFT_SHIFT) & CLK_GATE_BIT_SHIFT_MASK))

#define CLK_GATE_ABSTRACT_REG_OFFSET(x) (((uint32_t)(x) & CLK_GATE_REG_OFFSET_MASK) >> CLK_GATE_REG_OFFSET_SHIFT)
#define CLK_GATE_ABSTRACT_BITS_SHIFT(x) (((uint32_t)(x) & CLK_GATE_BIT_SHIFT_MASK) >> CLK_GATE_BIT_SHIFT_SHIFT)

#define CLK_CTL0_PSCCTL0 0 /* CLKCTL_COM_VDD2 PSCCTL0 */
#define CLK_CTL0_PSCCTL1 1
#define CLK_CTL0_PSCCTL2 2
#define CLK_CTL0_PSCCTL3 3
#define CLK_CTL0_PSCCTL4 4
#define CLK_CTL0_PSCCTL5 5
#define CLK_CTL1_PSCCTL0 6  /* CLKCTL_VDD1_SENSE PSCCTL0 */
#define CLK_CTL1_PSCCTL1 7
#define CLK_CTL2_PSCCTL0 8  /* CLKCTL_VDD1_COM PSCCTL0 */
#define CLK_CTL3_PSCCTL0 9  /* CLKCTL2 PSCCTL0 */
#define CLK_CTL4_PSCCTL0 10 /* CLKCTL_MED_VDD2 PSCCTL0 */
#define CLK_CTL4_PSCCTL1 11 /* CLKCTL_MED_VDD2 PSCCTL1 */
#if defined(FSL_CLOCK_DRIVER_COMPUTE) || defined(FSL_CLOCK_DRIVER_MEDIA)
#define SYSCON0_SEC_CLK_CTRL 12
#endif
#define SYSCON3_SEC_CLK_CTRL            13
#define CLKCTL0_ONE_SRC_CLKSLICE_ENABLE 14
#define CLKCTL3_ONE_SRC_CLKSLICE_ENABLE 15
#define CLKCTL4_ONE_SRC_CLKSLICE_ENABLE 16

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

/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = 0U,                                         /*!< Invalid Ip Name. */

    kCLOCK_Xcache1   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL0, 1),       /*!< Clock gate name: Code cache*/
    kCLOCK_Xcache0   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL0, 2),       /*!< Clock gate name: System cache*/
    kCLOCK_Ocotp0    = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL0, 5),       /*!< Clock gate name: VDD2 OTP0*/
    kCLOCK_Sleepcon0 = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL0, 12),      /*!< Clock gate name: SLEEPCON_CMPT*/
    kCLOCK_Syscon0   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL0, 13),      /*!< Clock gate name: SYSCON_CMPT*/
    kCLOCK_Glikey0   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL0, 14),      /*!< Clock gate name: GLIKEY0*/
    kCLOCK_Glikey3   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL0, 15),      /*!< Clock gate name: GLIKEY3*/

    kCLOCK_TpiuTraceClkin = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 2),  /*!< Clock gate name: TPIU_TRACECLKIN*/
    kCLOCK_SWOTraceClkin  = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 3),  /*!< Clock gate name: SWO_TRACECLKIN*/
    kCLOCK_Tsclk          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 4),  /*!< Clock gate name: TRACE*/
    kCLOCK_Dma0           = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 5),  /*!< Clock gate name: DMA0*/
    kCLOCK_Dma1           = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 6),  /*!< Clock gate name: DMA1*/
    kCLOCK_PkcRam         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 7),  /*!< Clock gate name: PKC RAM */
    kCLOCK_Pkc            = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 8),  /*!< Clock gate name: PKC*/
    kCLOCK_Romcp          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 9),  /*!< Clock gate name: ROMCP*/
    kCLOCK_Xspi0          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 10), /*!< Clock gate name: XSPI0*/
    kCLOCK_Xspi1          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 11), /*!< Clock gate name: XSPI1*/
    kCLOCK_Cache64ctrl0   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 12), /*!< Clock gate name: CACHE64_0*/
    kCLOCK_Cache64ctrl1   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 13), /*!< Clock gate name: CACHE64_1*/
    kCLOCK_Puf            = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 14), /*!< Clock gate name: QK_SUBSYS*/
    kCLOCK_Mmu0           = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 16), /*!< Clock gate name: MMU0*/
    kCLOCK_Mmu1           = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 17), /*!< Clock gate name: MMU1*/
    kCLOCK_Gpio0          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 18), /*!< Clock gate name: GPIO0*/
    kCLOCK_Gpio1          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 19), /*!< Clock gate name: GPIO1*/
    kCLOCK_Gpio2          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 20), /*!< Clock gate name: GPIO2*/
    kCLOCK_Gpio3          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 21), /*!< Clock gate name: GPIO3*/
    kCLOCK_Gpio4          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 22), /*!< Clock gate name: GPIO4*/
    kCLOCK_Gpio5          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 23), /*!< Clock gate name: GPIO5*/
    kCLOCK_Gpio6          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 24), /*!< Clock gate name: GPIO6*/
    kCLOCK_Gpio7          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 25), /*!< Clock gate name: GPIO7*/
    kCLOCK_Sct0           = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 26), /*!< Clock gate name: SCT0*/
    kCLOCK_Cdog0          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 27), /*!< Clock gate name: CDOG0*/
    kCLOCK_Cdog1          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 28), /*!< Clock gate name: CDOG1*/
    kCLOCK_Cdog2          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 29), /*!< Clock gate name: CDOG2*/
    kCLOCK_LPFlexComm0    = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 30), /*!< Clock gate name: LP_Flexcomm0*/
    kCLOCK_LPFlexComm1    = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 31), /*!< Clock gate name: LP_Flexcomm1*/
    kCLOCK_LPUart0        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 30), /*!< Clock gate name: LPUART0*/
    kCLOCK_LPUart1        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 31), /*!< Clock gate name: LPUART1*/
    kCLOCK_LPI2c0         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 30), /*!< Clock gate name: LPI2C0*/
    kCLOCK_LPI2c1         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 31), /*!< Clock gate name: LPI2C1*/
    kCLOCK_LPSpi0         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 30), /*!< Clock gate name: LPSPI0*/
    kCLOCK_LPSpi1         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL1, 31), /*!< Clock gate name: LPSPI1*/
    kCLOCK_LPFlexComm2    = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 0),  /*!< Clock gate name: LP_Flexcomm2*/
    kCLOCK_LPFlexComm3    = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 1),  /*!< Clock gate name: LP_Flexcomm3*/
    kCLOCK_LPFlexComm4    = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 2),  /*!< Clock gate name: LP_Flexcomm4*/
    kCLOCK_LPFlexComm5    = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 3),  /*!< Clock gate name: LP_Flexcomm5*/
    kCLOCK_LPFlexComm6    = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 4),  /*!< Clock gate name: LP_Flexcomm6*/
    kCLOCK_LPFlexComm7    = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 5),  /*!< Clock gate name: LP_Flexcomm7*/
    kCLOCK_LPFlexComm8    = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 6),  /*!< Clock gate name: LP_Flexcomm8*/
    kCLOCK_LPFlexComm9    = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 7),  /*!< Clock gate name: LP_Flexcomm9*/
    kCLOCK_LPFlexComm10   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 8),  /*!< Clock gate name: LP_Flexcomm10*/
    kCLOCK_LPFlexComm11   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 9),  /*!< Clock gate name: LP_Flexcomm11*/
    kCLOCK_LPFlexComm12   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 10), /*!< Clock gate name: LP_Flexcomm12*/
    kCLOCK_LPFlexComm13   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 11), /*!< Clock gate name: LP_Flexcomm13*/
    kCLOCK_LPUart2        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 0),  /*!< Clock gate name: LPUART2*/
    kCLOCK_LPUart3        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 1),  /*!< Clock gate name: LPUART3*/
    kCLOCK_LPUart4        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 2),  /*!< Clock gate name: LPUART4*/
    kCLOCK_LPUart5        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 3),  /*!< Clock gate name: LPUART5*/
    kCLOCK_LPUart6        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 4),  /*!< Clock gate name: LPUART6*/
    kCLOCK_LPUart7        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 5),  /*!< Clock gate name: LPUART7*/
    kCLOCK_LPUart8        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 6),  /*!< Clock gate name: LPUART8*/
    kCLOCK_LPUart9        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 7),  /*!< Clock gate name: LPUART9*/
    kCLOCK_LPUart10       = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 8),  /*!< Clock gate name: LPUART10*/
    kCLOCK_LPUart11       = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 9),  /*!< Clock gate name: LPUART11*/
    kCLOCK_LPUart12       = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 10), /*!< Clock gate name: LPUART12*/
    kCLOCK_LPUart13       = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 11), /*!< Clock gate name: LPUART13*/
    kCLOCK_LPI2c2         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 0),  /*!< Clock gate name: LPI2C2*/
    kCLOCK_LPI2c3         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 1),  /*!< Clock gate name: LPI2C3*/
    kCLOCK_LPI2c4         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 2),  /*!< Clock gate name: LPI2C4*/
    kCLOCK_LPI2c5         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 3),  /*!< Clock gate name: LPI2C5*/
    kCLOCK_LPI2c6         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 4),  /*!< Clock gate name: LPI2C6*/
    kCLOCK_LPI2c7         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 5),  /*!< Clock gate name: LPI2C7*/
    kCLOCK_LPI2c8         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 6),  /*!< Clock gate name: LPI2C8*/
    kCLOCK_LPI2c9         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 7),  /*!< Clock gate name: LPI2C9*/
    kCLOCK_LPI2c10        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 8),  /*!< Clock gate name: LPI2C10*/
    kCLOCK_LPI2c11        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 9),  /*!< Clock gate name: LPI2C11*/
    kCLOCK_LPI2c12        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 10), /*!< Clock gate name: LPI2C12*/
    kCLOCK_LPI2c13        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 11), /*!< Clock gate name: LPI2C13*/
    kCLOCK_LPSpi2         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 0),  /*!< Clock gate name: LPSPI2*/
    kCLOCK_LPSpi3         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 1),  /*!< Clock gate name: LPSPI3*/
    kCLOCK_LPSpi4         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 2),  /*!< Clock gate name: LPSPI4*/
    kCLOCK_LPSpi5         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 3),  /*!< Clock gate name: LPSPI5*/
    kCLOCK_LPSpi6         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 4),  /*!< Clock gate name: LPSPI6*/
    kCLOCK_LPSpi7         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 5),  /*!< Clock gate name: LPSPI7*/
    kCLOCK_LPSpi8         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 6),  /*!< Clock gate name: LPSPI8*/
    kCLOCK_LPSpi9         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 7),  /*!< Clock gate name: LPSPI9*/
    kCLOCK_LPSpi10        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 8),  /*!< Clock gate name: LPSPI10*/
    kCLOCK_LPSpi11        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 9),  /*!< Clock gate name: LPSPI11*/
    kCLOCK_LPSpi12        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 10), /*!< Clock gate name: LPSPI12*/
    kCLOCK_LPSpi13        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 11), /*!< Clock gate name: LPSPI13*/
    kCLOCK_Sai0           = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 13), /*!< Clock gate name: SAI0*/
    kCLOCK_Sai1           = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 14), /*!< Clock gate name: SAI1*/
    kCLOCK_Sai2           = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 15), /*!< Clock gate name: SAI2*/
    kCLOCK_I3c0           = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 16), /*!< Clock gate name: I3C0*/
    kCLOCK_I3c1           = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 17), /*!< Clock gate name: I3C1*/
    kCLOCK_Crc0           = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 18), /*!< Clock gate name: CRC0*/
    kCLOCK_Wwdt0          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 19), /*!< Clock gate name: WWDT0*/
    kCLOCK_Wwdt1          = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 20), /*!< Clock gate name: WWDT1*/
    kCLOCK_Ct32b0         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 21), /*!< Clock gate name: CTIMER0*/
    kCLOCK_Ct32b1         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 22), /*!< Clock gate name: CTIMER1*/
    kCLOCK_Ct32b2         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 23), /*!< Clock gate name: CTIMER2*/
    kCLOCK_Ct32b3         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 24), /*!< Clock gate name: CTIMER3*/
    kCLOCK_Ct32b4         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 25), /*!< Clock gate name: CTIMER4*/
    kCLOCK_Mrt0           = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 26), /*!< Clock gate name: Mrt0*/
    kCLOCK_Utick0         = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 27), /*!< Clock gate name: Utick0*/
    kCLOCK_Sema424        = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 30), /*!< Clock gate name: SEMA42_4*/
    kCLOCK_Mu4            = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL2, 31), /*!< Clock gate name: MU4*/
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    kCLOCK_Pint     = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL3, 5),        /*!< Clock gate name: PINT0*/
    kCLOCK_InputMux = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL3, 10),       /*!< Clock gate name: PMUX_CMPT_SPLITTER*/
#endif
    kCLOCK_Freqme0   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL3, 8),       /*!< Clock gate name: FREQME0*/
    kCLOCK_SafoSgi   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL3, 12),      /*!< Clock gate name: SAFO_SGI*/
    kCLOCK_Trace     = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL3, 13),      /*!< Clock gate name: TRACE*/
    kCLOCK_Prince0   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL3, 15),      /*!< Clock gate name: PRINCE0*/
    kCLOCK_Prince1   = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL3, 16),      /*!< Clock gate name: PRINCE1*/
    kCLOCK_PrinceExe = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL3, 17),      /*!< Clock gate name: PRINCE_EXE*/
    kCLOCK_Syspm0    = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL3, 18),      /*!< Clock gate name: CMX_PERFMON0*/
    kCLOCK_Syspm1    = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL3, 19),      /*!< Clock gate name: CMX_PERFMON1*/
    kCLOCK_Hifi4     = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL4, 0),       /*!< Clock gate name: HIFI4*/
    kCLOCK_Npu0      = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL5, 0),       /*!< Clock gate name: NPU0*/
    kCLOCK_CompAccessRamArbiter1 =
        CLK_GATE_DEFINE(CLK_CTL0_PSCCTL5, 2),                      /*!< Clock gate name: COMP_ACCESS_RAM_ARBITER1*/
    kCLOCK_Iopctl0 = CLK_GATE_DEFINE(CLK_CTL0_PSCCTL5, 3),         /*!< Clock gate name: IOMUXC_VDD2*/
    kCLOCK_Hifi4AccessRamArbiter1 =
        CLK_GATE_DEFINE(CLK_CTL0_PSCCTL5, 4),                      /*!< Clock gate name: HIFI4_ACCESS_RAM_ARBITER1*/
    kCLOCK_MediaAccessRamArbiter0 =
        CLK_GATE_DEFINE(CLK_CTL0_PSCCTL5, 5),                      /*!< Clock gate name: MEDIA_ACCESS_RAM_ARBITER0*/

    kCLOCK_Sleepcon1 = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL0, 6),       /*!< Clock gate name: SLEEPCONCPU1*/
    kCLOCK_Syscon1   = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL0, 7),       /*!< Clock gate name: SYSCONSENSE1*/
    kCLOCK_SenseAccessRamArbiter0 =
        CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 0),                      /*!< Clock gate name: SENSE_ACCESS_RAM_ARBITER0*/
    kCLOCK_Hifi1        = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 1),    /*!< Clock gate name: HIFI1*/
    kCLOCK_Dma2         = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 4),    /*!< Clock gate name: DMA2*/
    kCLOCK_Dma3         = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 5),    /*!< Clock gate name: DMA3*/
    kCLOCK_LPFlexComm17 = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 6),    /*!< Clock gate name: LP_Flexcomm17*/
    kCLOCK_LPFlexComm18 = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 7),    /*!< Clock gate name: LP_Flexcomm18*/
    kCLOCK_LPFlexComm19 = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 8),    /*!< Clock gate name: LP_Flexcomm19*/
    kCLOCK_LPFlexComm20 = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 9),    /*!< Clock gate name: LP_Flexcomm20*/
    kCLOCK_LPI2c17      = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 6),    /*!< Clock gate name: LPI2C17*/
    kCLOCK_LPI2c18      = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 7),    /*!< Clock gate name: LPI2C18*/
    kCLOCK_LPI2c19      = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 8),    /*!< Clock gate name: LPI2C19*/
    kCLOCK_LPI2c20      = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 9),    /*!< Clock gate name: LPI2C20*/
    kCLOCK_LPSpi17      = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 6),    /*!< Clock gate name: LPSPI17*/
    kCLOCK_LPSpi18      = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 7),    /*!< Clock gate name: LPSPI18*/
    kCLOCK_LPSpi19      = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 8),    /*!< Clock gate name: LPSPI19*/
    kCLOCK_LPSpi20      = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 9),    /*!< Clock gate name: LPSPI20*/
    kCLOCK_LPUart17     = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 6),    /*!< Clock gate name: LPUART17*/
    kCLOCK_LPUart18     = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 7),    /*!< Clock gate name: LPUART18*/
    kCLOCK_LPUart19     = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 8),    /*!< Clock gate name: LPUART19*/
    kCLOCK_LPUart20     = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 9),    /*!< Clock gate name: LPUART20*/
    kCLOCK_Sai3         = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 10),   /*!< Clock gate name: SAI3*/
    kCLOCK_I3c2         = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 11),   /*!< Clock gate name: I3C2*/
    kCLOCK_I3c3         = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 12),   /*!< Clock gate name: I3C3*/
    kCLOCK_Gpio8        = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 13),   /*!< Clock gate name: GPIO8*/
    kCLOCK_Gpio9        = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 14),   /*!< Clock gate name: GPIO9*/
    kCLOCK_Gpio10       = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 15),   /*!< Clock gate name: GPIO10*/
#if defined(FSL_CLOCK_DRIVER_SENSE)
    kCLOCK_Pint     = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 16),       /*!< Clock gate name: PINT1*/
    kCLOCK_InputMux = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 30),       /*!< Clock gate name: PMUX_SNS_SPLITTER*/
#endif
    kCLOCK_Ct32b5  = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 17),        /*!< Clock gate name: CTIMER5*/
    kCLOCK_Ct32b6  = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 18),        /*!< Clock gate name: CTIMER6*/
    kCLOCK_Ct32b7  = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 19),        /*!< Clock gate name: CTIMER7*/
    kCLOCK_Mrt1    = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 20),        /*!< Clock gate name: Mrt1*/
    kCLOCK_Utick1  = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 21),        /*!< Clock gate name: Utick1*/
    kCLOCK_Cdog3   = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 22),        /*!< Clock gate name: CDOG3*/
    kCLOCK_Cdog4   = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 23),        /*!< Clock gate name: CDOG4*/
    kCLOCK_Mu3     = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 24),        /*!< Clock gate name: MU3*/
    kCLOCK_Sema423 = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 25),        /*!< Clock gate name: SEMA42_3*/
    kCLOCK_Wwdt2   = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 26),        /*!< Clock gate name: WWDT2*/
    kCLOCK_Wwdt3   = CLK_GATE_DEFINE(CLK_CTL1_PSCCTL1, 27),        /*!< Clock gate name: WWDT3*/

    kCLOCK_Syscon2 = CLK_GATE_DEFINE(CLK_CTL2_PSCCTL0, 3),         /*!< Clock gate name: SYSCON_COMM */
    kCLOCK_Iopctl2 = CLK_GATE_DEFINE(CLK_CTL2_PSCCTL0, 4),         /*!< Clock gate name: IOMUXC_VDDN */

    kCLOCK_Cpu1    = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 0),         /*!< Clock gate name: CPU1*/
    kCLOCK_Mu0     = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 4),         /*!< Clock gate name: MU0*/
    kCLOCK_Mu1     = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 5),         /*!< Clock gate name: MU1*/
    kCLOCK_Mu2     = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 6),         /*!< Clock gate name: MU2*/
    kCLOCK_OsTimer = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 7),         /*!< Clock gate name: OsTimer*/
    kCLOCK_Sema420 = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 8),         /*!< Clock gate name: SEMA42_0*/
    kCLOCK_Sdadc0  = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 9),         /*!< Clock gate name: SDADC0*/
    kCLOCK_Adc0    = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 10),        /*!< Clock gate name: SARADC0*/
    kCLOCK_Acmp0   = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 11),        /*!< Clock gate name: Acmp0*/
    kCLOCK_Pdm     = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 12),        /*!< Clock gate name: MICFIL(PDM)*/
    kCLOCK_Glikey4 = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 13),        /*!< Clock gate name: GLIKEY_SYSCON1*/
    kCLOCK_Dbg     = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 20),        /*!< Clock gate name: DBG*/
    kCLOCK_Syscon3 = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 21),        /*!< Clock gate name: SYSCON_SENSE0*/
    kCLOCK_Iopctl1 = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 22),        /*!< Clock gate name: IOMUXC_VDD1*/
    kCLOCK_Glikey1 = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 23),        /*!< Clock gate name: GLIKEY1*/
    kCLOCK_LPI2c15 = CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 24),        /*!< Clock gate name: LPI2C*/
    kCLOCK_MediaAccessRamArbiter1 =
        CLK_GATE_DEFINE(CLK_CTL3_PSCCTL0, 25),                     /*!< Clock gate name: MEDIA_ACCESS_RAM_ARBITER1*/
    kCLOCK_Axi0        = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 0),     /*!< Clock gate name: AXI0*/
    kCLOCK_Gpu         = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 2),     /*!< Clock gate name: VGPU*/
    kCLOCK_MipiDsiCtrl = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 4),     /*!< Clock gate name: MIPIDSI*/
    kCLOCK_LPSpi16     = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 5),     /*!< Clock gate name: LPSPI16*/
    kCLOCK_LPSpi14     = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 6),     /*!< Clock gate name: LPSPI14*/
    kCLOCK_Xspi2       = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 8),     /*!< Clock gate name: XSPI2*/
    kCLOCK_Mmu2        = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 11),    /*!< Clock gate name: MMU2*/
    kCLOCK_Glikey5     = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 13),    /*!< Clock gate name: GLIKEY_SYSCON2*/
    kCLOCK_Flexio      = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 15),    /*!< Clock gate name: FLEXIO0*/
    kCLOCK_Lcdif       = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 22),    /*!< Clock gate name: LCDIF(DCN)*/
    kCLOCK_Syscon4     = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 23),    /*!< Clock gate name: SYSCONMEDIA*/
    kCLOCK_JpgDecoder  = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 24),    /*!< Clock gate name: JPG_DECODER*/
    kCLOCK_PngDecoder  = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 25),    /*!< Clock gate name: PNG_DECODER*/
    kCLOCK_Ezhv        = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 26),    /*!< Clock gate name: EZHV*/
    kCLOCK_AxbsEzh     = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 28),    /*!< Clock gate name: AXBS_EZH*/
    kCLOCK_Glikey2     = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL0, 29),    /*!< Clock gate name: GLIKEY2*/
    kCLOCK_Usb0        = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL1, 0),     /*!< Clock gate name: USB0*/
    kCLOCK_Usb1        = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL1, 2),     /*!< Clock gate name: USB1*/
    kCLOCK_Usdhc0      = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL1, 4),     /*!< Clock gate name: USHDC0*/
    kCLOCK_Usdhc1      = CLK_GATE_DEFINE(CLK_CTL4_PSCCTL1, 5),     /*!< Clock gate name: USDHC1*/

/* Control bits in SYSCON. */
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    kCLOCK_Gdet0Ref = CLK_GATE_DEFINE(SYSCON0_SEC_CLK_CTRL, 0),          /*!< Clock gate name: GDET0 Reference clock*/
    kCLOCK_Gdet1Ref = CLK_GATE_DEFINE(SYSCON0_SEC_CLK_CTRL, 1),          /*!< Clock gate name: GDET1 Reference clock*/
    kCLOCK_TrngRef  = CLK_GATE_DEFINE(SYSCON0_SEC_CLK_CTRL, 2),          /*!< Clock gate name: TRNG Reference clock*/
    kCLOCK_Els      = CLK_GATE_DEFINE(SYSCON0_SEC_CLK_CTRL, 3),          /*!< Clock gate name: ELS clock*/
    kCLOCK_ItrcRef  = CLK_GATE_DEFINE(SYSCON0_SEC_CLK_CTRL, 4),          /*!< Clock gate name: ITRC Reference clock*/

    kCLOCK_Gdet0 = CLK_GATE_DEFINE(CLKCTL0_ONE_SRC_CLKSLICE_ENABLE, 0U), /*!< Clock gate name: GDET0. */
    kCLOCK_Gdet1 = CLK_GATE_DEFINE(CLKCTL0_ONE_SRC_CLKSLICE_ENABLE, 1U), /*!< Clock gate name: GDET1. */
#endif
    kCLOCK_Gdet2Ref = CLK_GATE_DEFINE(SYSCON3_SEC_CLK_CTRL, 0),          /*!< Clock gate name: GDET2 Reference clock*/
    kCLOCK_Gdet3Ref = CLK_GATE_DEFINE(SYSCON3_SEC_CLK_CTRL, 1),          /*!< Clock gate name: GDET3 Reference clock*/

    kCLOCK_Rtc       = CLK_GATE_DEFINE(CLKCTL3_ONE_SRC_CLKSLICE_ENABLE, 0U), /*!< RTC functional clock gating. */
    kCLOCK_Gdet2     = CLK_GATE_DEFINE(CLKCTL3_ONE_SRC_CLKSLICE_ENABLE, 1U), /*!< GDET2 functional clock gating. */
    kCLOCK_Gdet3     = CLK_GATE_DEFINE(CLKCTL3_ONE_SRC_CLKSLICE_ENABLE, 2U), /*!< GDET3 functional clock gating. */
    kCLOCK_UsbphyRef = CLK_GATE_DEFINE(CLKCTL4_ONE_SRC_CLKSLICE_ENABLE, 0U), /*!< USBPHY referrence clock gating. */
} clock_ip_name_t;

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{
    kCLOCK_CoreSysClk,      /*!< Core clock  (aka system clock)                                 */
    kCLOCK_BusClk,          /*!< Bus clock (AHB/APB clock, aka HCLK)                    */
    kCLOCK_MclkClk,         /*!< MCLK, to MCLK pin                                      */
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    kCLOCK_Vdd2ClockOutClk, /*!< VDD2 CLOCKOUT                                               */
    kCLOCK_Xspi0Clk,        /*!< XSPI0                                               */
    kCLOCK_Xspi1Clk,        /*!< XSPI1                                               */
    kCLOCK_Wdt0Clk,         /*!< Watchdog0                                              */
    kCLOCK_Wdt1Clk,         /*!< Watchdog1                                              */
    kCLOCK_Hifi4CpuClk,     /*!< Hifi4 DSP  clock                                             */
    kCLOCK_LPFlexComm0Clk,  /*!< Flexcomm0Clock                                         */
    kCLOCK_LPFlexComm1Clk,  /*!< Flexcomm1Clock                                         */
    kCLOCK_LPFlexComm2Clk,  /*!< Flexcomm2Clock                                         */
    kCLOCK_LPFlexComm3Clk,  /*!< Flexcomm3Clock                                         */
    kCLOCK_LPFlexComm4Clk,  /*!< Flexcomm4Clock                                         */
    kCLOCK_LPFlexComm5Clk,  /*!< Flexcomm5Clock                                         */
    kCLOCK_LPFlexComm6Clk,  /*!< Flexcomm6Clock                                         */
    kCLOCK_LPFlexComm7Clk,  /*!< Flexcomm7Clock                                         */
    kCLOCK_LPFlexComm8Clk,  /*!< Flexcomm8Clock                                         */
    kCLOCK_LPFlexComm9Clk,  /*!< Flexcomm9Clock                                         */
    kCLOCK_LPFlexComm10Clk, /*!< Flexcomm10Clock                                        */
    kCLOCK_LPFlexComm11Clk, /*!< Flexcomm11Clock                                        */
    kCLOCK_LPFlexComm12Clk, /*!< Flexcomm12Clock                                        */
    kCLOCK_LPFlexComm13Clk, /*!< Flexcomm13Clock                                        */
#else
    kCLOCK_Wdt2Clk,         /*!< Watchdog1                                              */
    kCLOCK_Wdt3Clk,         /*!< Watchdog1                                              */
    kCLOCK_Hifi1CpuClk,     /*!< Hifi1 DSP  clock                                             */
    kCLOCK_LPFlexComm17Clk, /*!< Flexcomm17Clock                                        */
    kCLOCK_LPFlexComm18Clk, /*!< Flexcomm18Clock                                        */
    kCLOCK_LPFlexComm19Clk, /*!< Flexcomm19Clock                                        */
    kCLOCK_LPFlexComm20Clk, /*!< Flexcomm20Clock                                        */
#endif
    kCLOCK_Vdd1ClockOutClk,  /*!< VDD1 CLOCKOUT                                               */
    kCLOCK_AdcClk,           /*!< ADC                                                    */
    kCLOCK_Xspi2Clk,         /*!< XSPI1                                               */
    kCLOCK_SctClk,           /*!< SCT                                                    */
    kCLOCK_SystickClk,       /*!< Systick                                                */
    kCLOCK_Sdio0Clk,         /*!< SDIO0                                                  */
    kCLOCK_Sdio1Clk,         /*!< SDIO1                                                  */
    kCLOCK_I3cClk,           /*!< I3C                                          */
    kCLOCK_Usb0Clk,          /*!< USB0                                          */
    kCLOCK_Usb1Clk,          /*!< USB1                                          */
    kCLOCK_PdmClk,           /*!< Digital Mic clock                                      */
    kCLOCK_AcmpClk,          /*!< Acmp clock                                             */
    kCLOCK_FlexioClk,        /*!< FlexIO                                                 */
    kCLOCK_LPSpi14Clk,       /*!< LPSPI14                                                 */
    kCLOCK_LPI2c15Clk,       /*!< LPI2C15                                                 */
    kCLOCK_LPSpi16Clk,       /*!< LPSPI16                                                 */
    kCLOCK_VgpuClk,          /*!< VGPU Core                                               */
    kCLOCK_LcdifClk,         /*!< LCDIF Clock                                     */
    kCLOCK_MipiDphyClk,      /*!< MIPI D-PHY Bit Clock                                   */
    kCLOCK_MipiDphyEscRxClk, /*!< MIPI D-PHY RX Clock                                    */
    kCLOCK_MipiDphyEscTxClk, /*!< MIPI D-PHY TX Clock                                    */
} clock_name_t;

/*! @brief Clock Mux Switches
 *  The encoding is as follows each connection identified is 32bits wide
 *  starting from LSB upwards
 *
 *  [    31-29                14             12:11         10:0    ]
   [CLKCTL index]: [Disable MUX output]: [MUXA choice]:[MUXA offset]. MUX offset 0 means end of
 descriptor.
 */
#define CLK_MUX_INST_INDEX_SHIFT    29U
#define CLK_MUX_CHOICE_OFFSET_SHIFT 11U
#define CLK_MUX_DISABLE_OUTPUT_MASK (1UL << 14U)

/* CLKCTL0 CLKCTL_COM_VDD2*/
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
#define CMPTMAINCLKDIV_OFFSET    0x400
#define CMPTBASECLKSEL_OFFSET    0x420
#define DSPBASECLKSEL_OFFSET     0x424
#define VDD2COMBASECLKSEL_OFFSET 0x428
#define MAINCLKSEL_OFFSET        0x434
#define DSPCPUCLKDIV_OFFSET      0x440
#define DSPCPUCLKSEL_OFFSET      0x444
#define RAMCLKSEL_OFFSET         0x450
#define RAMCLKDIV_OFFSET         0x45C
#define TPIUFCLKSEL_OFFSET       0x560
#define TPIUCLKDIV_OFFSET        0x564
#define XSPI0FCLKSEL_OFFSET      0x600
#define XSPI0FCLKDIV_OFFSET      0x604
#define XSPI1FCLKSEL_OFFSET      0x620
#define XSPI1FCLKDIV_OFFSET      0x624
#define SCTFCLKSEL_OFFSET        0x640
#define SCTFCLKDIV_OFFSET        0x644
#define UTICK0FCLKSEL_OFFSET     0x700
#define UTICK0CLKDIV_OFFSET      0x704
#define WWDT0FCLKSEL_OFFSET      0x720
#define WWDT1FCLKSEL_OFFSET      0x740
#define SYSTICKFCLKSEL_OFFSET    0x760
#define SYSTICKFCLKDIV_OFFSET    0x764
#define FCCLK0SEL_OFFSET         0x800
#define FC0FCLKSEL_OFFSET        0x808
#define FCCLK1SEL_OFFSET         0x820
#define FC1FCLKSEL_OFFSET        0x828
#define FCCLK2SEL_OFFSET         0x840
#define FC2FCLKSEL_OFFSET        0x848
#define FCCLK3SEL_OFFSET         0x860
#define FC3FCLKSEL_OFFSET        0x868
#define FC4FCLKSEL_OFFSET        0x888
#define FC5FCLKSEL_OFFSET        0x8A8
#define FC6FCLKSEL_OFFSET        0x8C8
#define FC7FCLKSEL_OFFSET        0x8E8
#define FC8FCLKSEL_OFFSET        0x908
#define FC9FCLKSEL_OFFSET        0x928
#define FC10FCLKSEL_OFFSET       0x948
#define FC11FCLKSEL_OFFSET       0x968
#define FC12FCLKSEL_OFFSET       0x988
#define FC13FCLKSEL_OFFSET       0x9A8
#define FCCLK0DIV_OFFSET         0x804
#define FCCLK1DIV_OFFSET         0x824
#define FCCLK2DIV_OFFSET         0x844
#define FCCLK3DIV_OFFSET         0x864
#define SAI012FCLKSEL_OFFSET     0x9C8
#define SAI012CLKDIV_OFFSET      0x9CC
#define CTIMER0CLKDIV_OFFSET     0xA00
#define CTIMER1CLKDIV_OFFSET     0xA04
#define CTIMER2CLKDIV_OFFSET     0xA08
#define CTIMER3CLKDIV_OFFSET     0xA0C
#define CTIMER4CLKDIV_OFFSET     0xA10
#define CTIMER0FCLKSEL_OFFSET    0xAA0
#define CTIMER1FCLKSEL_OFFSET    0xAA4
#define CTIMER2FCLKSEL_OFFSET    0xAA8
#define CTIMER3FCLKSEL_OFFSET    0xAAC
#define CTIMER4FCLKSEL_OFFSET    0xAB0
#define TRNGFCLKSEL_OFFSET       0xAC0
#define TRNGFCLKDIV_OFFSET       0xAC4
#define I3C01FCLKSEL_OFFSET      0xB00
#define I3C01PCLKSEL_OFFSET      0xB04
#define I3C01PCLKDIV_OFFSET      0xB08
#define I3C01FCLKDIV_OFFSET      0xB10
#define CLKOUTCLKSEL_OFFSET      0xB20
#define CLKOUTCLKDIV_OFFSET      0xB24
#define AUDIOVDD2CLKSEL_OFFSET   0xB30

#else

#define SENSEBASECLKSEL_OFFSET   0x438
#define SENSEDSPCPUCLKDIV_OFFSET 0x440
#define SENSEDSPCPUCLKSEL_OFFSET 0x444
#define SAI3FCLKSEL_OFFSET       0x500
#define SAI3CLKDIV_OFFSET        0x504
#define UTICK1FCLKSEL_OFFSET     0x700
#define UTICK1CLKDIV_OFFSET      0x704
#define WWDT2FCLKSEL_OFFSET      0x720
#define WWDT3FCLKSEL_OFFSET      0x740
#define SYSTICKFCLKSEL_OFFSET    0x760
#define SYSTICKFCLKDIV_OFFSET    0x764
#define CTIMER5FCLKSEL_OFFSET    0x7A0
#define CTIMER6FCLKSEL_OFFSET    0x7A4
#define CTIMER7FCLKSEL_OFFSET    0x7A8
#define CTIMER5CLKDIV_OFFSET     0x7B0
#define CTIMER6CLKDIV_OFFSET     0x7B4
#define CTIMER7CLKDIV_OFFSET     0x7B8
#define I3C23FCLKSEL_OFFSET      0x800
#define I3C23FCLKDIV_OFFSET      0x810
#define FC17FCLKSEL_OFFSET       0xA00
#define FC18FCLKSEL_OFFSET       0xA20
#define FC19FCLKSEL_OFFSET       0xA40
#define FC20FCLKSEL_OFFSET       0xA60
#define FC17FCLKDIV_OFFSET       0xA04
#define FC18FCLKDIV_OFFSET       0xA24
#define FC19FCLKDIV_OFFSET       0xA44
#define FC20FCLKDIV_OFFSET       0xA64
#define AUDIOVDD1CLKSEL_OFFSET   0xAA0
#endif

/* CLKCTL2 */
#define USBCLKSRC24MCLKSEL_OFFSET    0x10C
#define COMMONVDDNCLKSEL_OFFSET      0xA4
#define COMMONVDDNCLKDIV_OFFSET      0xAC
#define USBCLKSRC24MCLKSEL_OFFSET    0x10C
#define COMNBASECLKSEL_OFFSET        0x110
#define EUSBCLKSRC24MCLKSEL_OFFSET   0x11C
#define MAINPLL0CLKSEL_OFFSET        0x200
#define MAINPLL0LOCKTIMEDIV2_OFFSET  0x20C
#define AUDIOPLL0CLKSEL_OFFSET       0x400
#define AUDIOPLL0LOCKTIMEDIV2_OFFSET 0x40C

/* CLKCTL3 CLKCTL_VDD1_COM */
#define SENSEMAINCLKDIV_OFFSET    0x400
#define SENSE_MAINCLKSEL_OFFSET   0x434
#define SENSERAMCLKSEL_OFFSET     0x450
#define SENSERAMCLKDIV_OFFSET     0x45C
#define OSEVENTTFCLKSEL_OFFSET    0x480
#define OSEVENTFCLKDIV_OFFSET     0x484
#define SDADCFCLKSEL_OFFSET       0x600
#define SDADCFCLKDIV_OFFSET       0x604
#define SARADCFCLKSEL_OFFSET      0x620
#define SARADCFCLKDIV_OFFSET      0x624
#define WAKE32KCLKSEL_OFFSET      0x750
#define A32KHZWAKECLKDIV_OFFSET   0x754
#define MICFIL0FCLKSEL_OFFSET     0x780
#define MICFIL0FCLKDIV_OFFSET     0x784
#define LPI2CFCLKSEL_OFFSET       0x788
#define LPI2CFCLKDIV_OFFSET       0x78C
#define SENSE_CLKOUTCLKSEL_OFFSET 0x800
#define SENSE_CLKOUTCLKDIV_OFFSET 0x804

/* CLKCTL4 CLKCTL_MED_VDD2 */
#define MEDIAVDDNCLKSEL_OFFSET  0xA4
#define MEDIAVDDNCLKDIV_OFFSET  0xAC
#define MEDIAMAINCLKSEL_OFFSET  0x104
#define MEDIAMAINCLKDIV_OFFSET  0x10C
#define MDNBASECLKSEL_OFFSET    0x110
#define MD2BASECLKSEL_OFFSET    0x114
#define XSPI2FCLKSEL_OFFSET     0x200
#define XSPI2FCLKDIV_OFFSET     0x204
#define USBFCLKSEL_OFFSET       0x220
#define EUSBFCLKSEL_OFFSET      0x240
#define SDIO0FCLKSEL_OFFSET     0x260
#define SDIO0FCLKDIV_OFFSET     0x264
#define SDIO1FCLKSEL_OFFSET     0x280
#define SDIO1FCLKDIV_OFFSET     0x284
#define DPHYCLKSEL_OFFSET       0x300
#define DPHYCLKDIV_OFFSET       0x304
#define DPHYESCCLKSEL_OFFSET    0x308
#define DPHYESCRXCLKDIV_OFFSET  0x30C
#define DPHYESCTXCLKDIV_OFFSET  0x310
#define VGPUCLKSEL_OFFSET       0x320
#define VGPUCLKDIV_OFFSET       0x324
#define LPSPI14CLKSEL_OFFSET    0x328
#define LPSPI14CLKDIV_OFFSET    0x32C
#define LPSPI16CLKSEL_OFFSET    0x330
#define LPSPI16CLKDIV_OFFSET    0x334
#define FLEXIOCLKSEL_OFFSET     0x338
#define FLEXIOCLKDIV_OFFSET     0x33C
#define LCDIFPIXELCLKSEL_OFFSET 0x340
#define LCDIFPIXELCLKDIV_OFFSET 0x344
#define LOWFREQCLKDIV_OFFSET    0x700

#define CLKCTL0_INDEX (0UL << CLK_MUX_INST_INDEX_SHIFT)
#define CLKCTL1_INDEX (1UL << CLK_MUX_INST_INDEX_SHIFT)
#define CLKCTL2_INDEX (2UL << CLK_MUX_INST_INDEX_SHIFT)
#define CLKCTL3_INDEX (3UL << CLK_MUX_INST_INDEX_SHIFT)
#define CLKCTL4_INDEX (4UL << CLK_MUX_INST_INDEX_SHIFT)

#define CLKCTL0_TUPLE_MUXA(reg, choice) ((((reg) >> 2U) & 0x7FFU) | (((choice) & 0x3U) << CLK_MUX_CHOICE_OFFSET_SHIFT))
#define CLKCTL1_TUPLE_MUXA(reg, choice) \
    (CLKCTL1_INDEX | (((reg) >> 2U) & 0x7FFU) | (((choice) & 0x3U) << CLK_MUX_CHOICE_OFFSET_SHIFT))
#define CLKCTL2_TUPLE_MUXA(reg, choice) \
    (CLKCTL2_INDEX | (((reg) >> 2U) & 0x7FFU) | (((choice) & 0x3U) << CLK_MUX_CHOICE_OFFSET_SHIFT))
#define CLKCTL3_TUPLE_MUXA(reg, choice) \
    (CLKCTL3_INDEX | (((reg) >> 2U) & 0x7FFU) | (((choice) & 0x3U) << CLK_MUX_CHOICE_OFFSET_SHIFT))
#define CLKCTL4_TUPLE_MUXA(reg, choice) \
    (CLKCTL4_INDEX | (((reg) >> 2U) & 0x7FFU) | (((choice) & 0x3U) << CLK_MUX_CHOICE_OFFSET_SHIFT))
/*! Macro for gated clock mux */
#define CLKCTL0_TUPLE_MUXA_NONE(reg, choice) (CLKCTL0_TUPLE_MUXA(reg, choice) | CLK_MUX_DISABLE_OUTPUT_MASK)
#define CLKCTL1_TUPLE_MUXA_NONE(reg, choice) (CLKCTL1_TUPLE_MUXA(reg, choice) | CLK_MUX_DISABLE_OUTPUT_MASK)
#define CLKCTL2_TUPLE_MUXA_NONE(reg, choice) (CLKCTL2_TUPLE_MUXA(reg, choice) | CLK_MUX_DISABLE_OUTPUT_MASK)
#define CLKCTL3_TUPLE_MUXA_NONE(reg, choice) (CLKCTL3_TUPLE_MUXA(reg, choice) | CLK_MUX_DISABLE_OUTPUT_MASK)
#define CLKCTL4_TUPLE_MUXA_NONE(reg, choice) (CLKCTL4_TUPLE_MUXA(reg, choice) | CLK_MUX_DISABLE_OUTPUT_MASK)

#define CLKCTL_TUPLE_REG(base, tuple) ((volatile uint32_t *)(((uint32_t)(base)) + (((uint32_t)(tuple) & 0x7FFU) << 2U)))
#define CLKCTL_TUPLE_SEL(tuple)       (((uint32_t)(tuple) >> CLK_MUX_CHOICE_OFFSET_SHIFT) & 0x3U)

/*!
 * @brief The enumerator of clock attach Id for multi sources clock slices. Not all Muxer has MUX output enable control,
 * if no mux output enable control, the mux output will be always enabled.
 */
typedef enum _clock_attach_id
{
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    kFRO1_DIV3_to_COMPUTE_BASE =
        CLKCTL0_TUPLE_MUXA(CMPTBASECLKSEL_OFFSET, 0), /*!< Attach Fro1 Divided-by-3 to Compute Base Clock. */
    kFRO1_DIV1_to_COMPUTE_BASE =
        CLKCTL0_TUPLE_MUXA(CMPTBASECLKSEL_OFFSET, 1), /*!< Attach Fro1 Divided-by-1 to Compute Base Clock. */
    kFRO0_DIV3_to_COMPUTE_BASE =
        CLKCTL0_TUPLE_MUXA(CMPTBASECLKSEL_OFFSET, 2), /*!< Attach Fro0 Divided-by-3 to Compute Base Clock. */
    kLPOSC_to_COMPUTE_BASE = CLKCTL0_TUPLE_MUXA(CMPTBASECLKSEL_OFFSET, 3), /*!< Attach LPOSC to Compute Base Clock. */

    kFRO1_DIV3_to_DSP_BASE =
        CLKCTL0_TUPLE_MUXA(DSPBASECLKSEL_OFFSET, 0), /*!< Attach Fro1 Divided-by-3 to DSP Base Clock. */
    kFRO1_DIV1_to_DSP_BASE =
        CLKCTL0_TUPLE_MUXA(DSPBASECLKSEL_OFFSET, 1), /*!< Attach Fro1 Divided-by-1 to DSP Base Clock. */
    kFRO0_DIV3_to_DSP_BASE =
        CLKCTL0_TUPLE_MUXA(DSPBASECLKSEL_OFFSET, 2), /*!< Attach Fro0 Divided-by-3 to DSP Base Clock. */
    kLPOSC_to_DSP_BASE = CLKCTL0_TUPLE_MUXA(DSPBASECLKSEL_OFFSET, 3), /*!< Attach LPOSC to DSP Base Clock. */

    kFRO1_DIV3_to_COMMON_VDD2_BASE =
        CLKCTL0_TUPLE_MUXA(VDD2COMBASECLKSEL_OFFSET, 0), /*!< Attach Fro1 Divided-by-3 to VDD2_COM Base Clock. */
    kFRO1_DIV1_to_COMMON_VDD2_BASE =
        CLKCTL0_TUPLE_MUXA(VDD2COMBASECLKSEL_OFFSET, 1), /*!< Attach Fro1 Divided-by-1 to VDD2_COM Base Clock. */
    kFRO0_DIV3_to_COMMON_VDD2_BASE =
        CLKCTL0_TUPLE_MUXA(VDD2COMBASECLKSEL_OFFSET, 2), /*!< Attach Fro0 Divided-by-3 to VDD2_COM Base Clock. */
    kLPOSC_to_COMMON_VDD2_BASE =
        CLKCTL0_TUPLE_MUXA(VDD2COMBASECLKSEL_OFFSET, 3), /*!< Attach LPOSC to VDD2_COM Base Clock. */

    kCOMPUTE_BASE_to_COMPUTE_MAIN =
        CLKCTL0_TUPLE_MUXA(MAINCLKSEL_OFFSET, 0), /*!< Attach Compute base clock to Compute Main Clock. */
    kMAIN_PLL_PFD0_to_COMPUTE_MAIN =
        CLKCTL0_TUPLE_MUXA(MAINCLKSEL_OFFSET, 1), /*!< Attach MAIN PLL PFD0 to Compute Main Clock. */
    kFRO0_DIV1_to_COMPUTE_MAIN =
        CLKCTL0_TUPLE_MUXA(MAINCLKSEL_OFFSET, 2), /*!< Attach FRO0 Max clock to Compute Main Clock. */
    kAUDIO_PLL_PFD1_to_COMPUTE_MAIN =
        CLKCTL0_TUPLE_MUXA(MAINCLKSEL_OFFSET, 3), /*!< Attach AUDIO_PLL_PFD1 to Compute Main Clock. */

    kDSP_BASE_to_DSP      = CLKCTL0_TUPLE_MUXA(DSPCPUCLKSEL_OFFSET, 0),      /*!< Attach DSP base clock to DSP Clock. */
    kMAIN_PLL_PFD0_to_DSP = CLKCTL0_TUPLE_MUXA(DSPCPUCLKSEL_OFFSET, 1),      /*!< Attach MAIN PLL PFD0 to DSP Clock. */
    kFRO0_DIV1_to_DSP     = CLKCTL0_TUPLE_MUXA(DSPCPUCLKSEL_OFFSET, 2),      /*!< Attach FRO0 Max clock to DSP Clock. */
    kMAIN_PLL_PFD1_to_DSP = CLKCTL0_TUPLE_MUXA(DSPCPUCLKSEL_OFFSET, 3),      /*!< Attach MAIN PLL PFD1 to DSP Clock. */
    kNONE_to_DSP          = CLKCTL0_TUPLE_MUXA_NONE(DSPCPUCLKSEL_OFFSET, 0), /*!< Attach NONE to DSP Clock. */

    kCOMMON_VDD2_BASE_to_RAM = CLKCTL0_TUPLE_MUXA(RAMCLKSEL_OFFSET, 0), /*!< Attach baseclk_com2 clock to RAM Clock. */
    kMAIN_PLL_PFD0_to_RAM    = CLKCTL0_TUPLE_MUXA(RAMCLKSEL_OFFSET, 1), /*!< Attach Main PLL PFD0 to RAM Clock. */
    kFRO0_DIV1_to_RAM        = CLKCTL0_TUPLE_MUXA(RAMCLKSEL_OFFSET, 2), /*!< Attach FRO0 Max to RAM Clock. */
    kFRO1_DIV1_to_RAM        = CLKCTL0_TUPLE_MUXA(RAMCLKSEL_OFFSET, 3), /*!< Attach FRO1 Max to RAM Clock. */

    kCOMPUTE_BASE_to_TPIU = CLKCTL0_TUPLE_MUXA(
        TPIUFCLKSEL_OFFSET, 0), /*!< Attach Compute base clock to TPIU (TRACE_RT700) Functional Clock. */
    kMAIN_PLL_PFD0_to_TPIU =
        CLKCTL0_TUPLE_MUXA(TPIUFCLKSEL_OFFSET, 1), /*!< Attach main_pll_pfd0 to TPIU (TRACE_RT700) Functional Clock. */
    kFRO0_DIV1_to_TPIU =
        CLKCTL0_TUPLE_MUXA(TPIUFCLKSEL_OFFSET, 2), /*!< Attach FRO0 Max to TPIU (TRACE_RT700) Functional Clock. */
    kFRO0_DIV6_to_TPIU =
        CLKCTL0_TUPLE_MUXA(TPIUFCLKSEL_OFFSET, 3), /*!< Attach OSC_CLK clock to TPIU (TRACE_RT700) Functional Clock. */
    kNONE_to_TPIU =
        CLKCTL0_TUPLE_MUXA_NONE(TPIUFCLKSEL_OFFSET, 0), /*!< Attach NONE to TPIU (TRACE_RT700) Functional Clock. */

    kCOMMON_BASE_to_XSPI0 =
        CLKCTL0_TUPLE_MUXA(XSPI0FCLKSEL_OFFSET, 0), /*!< Attach Common base clock to XSPI0 Functional Clock. */
    kAUDIO_PLL_PFD0_to_XSPI0 =
        CLKCTL0_TUPLE_MUXA(XSPI0FCLKSEL_OFFSET, 1), /*!< Attach Audio PLL PFD0 clock to XSPI0 Functional Clock. */
    kFRO0_DIV1_to_XSPI0 =
        CLKCTL0_TUPLE_MUXA(XSPI0FCLKSEL_OFFSET, 2), /*!< Attach FRO0 Max clock to XSPI0 Functional Clock. */
    kMAIN_PLL_PFD1_to_XSPI0 =
        CLKCTL0_TUPLE_MUXA(XSPI0FCLKSEL_OFFSET, 3), /*!< Attach MAIN PLL PFD1 clock to XSPI0 Functional Clock. */
    kNONE_to_XSPI0 = CLKCTL0_TUPLE_MUXA_NONE(XSPI0FCLKSEL_OFFSET, 0), /*!< Attach NONE to XSPI0 Functional Clock. */

    kCOMMON_BASE_to_XSPI1 =
        CLKCTL0_TUPLE_MUXA(XSPI1FCLKSEL_OFFSET, 0), /*!< Attach Common base clock to XSPI1 Functional Clock. */
    kAUDIO_PLL_PFD1_to_XSPI1 =
        CLKCTL0_TUPLE_MUXA(XSPI1FCLKSEL_OFFSET, 1), /*!< Attach Audio PLL PFD1 clock to XSPI1 Functional Clock. */
    kFRO0_DIV1_to_XSPI1 =
        CLKCTL0_TUPLE_MUXA(XSPI1FCLKSEL_OFFSET, 2), /*!< Attach FRO0 Max clock to XSPI1 Functional Clock. */
    kMAIN_PLL_PFD2_to_XSPI1 =
        CLKCTL0_TUPLE_MUXA(XSPI1FCLKSEL_OFFSET, 3), /*!< Attach MAIN PLL PFD2 clock to XSPI1 Functional Clock. */
    kNONE_to_XSPI1 = CLKCTL0_TUPLE_MUXA_NONE(XSPI1FCLKSEL_OFFSET, 2), /*!< Attach NONE to XSPI1 Functional Clock. */

    kCOMPUTE_BASE_to_SCT =
        CLKCTL0_TUPLE_MUXA(SCTFCLKSEL_OFFSET, 0), /*!< Attach Compute base clock to SCT Functional Clock. */
    kMAIN_PLL_PFD0_SCT = CLKCTL0_TUPLE_MUXA(SCTFCLKSEL_OFFSET, 1), /*!< Attach main_pll_pfd0 to SCT Functional Clock. */
    kFRO0_DIV1_to_SCT = CLKCTL0_TUPLE_MUXA(SCTFCLKSEL_OFFSET, 2), /*!< Attach FRO0 Max clock to SCT Functional Clock. */
    kFRO0_DIV6_to_SCT =
        CLKCTL0_TUPLE_MUXA(SCTFCLKSEL_OFFSET, 3), /*!< Attach FRO0_DIV6 clock to SCT Functional Clock. */
    kNONE_to_SCT = CLKCTL0_TUPLE_MUXA_NONE(SCTFCLKSEL_OFFSET, 0), /*!< Attach NONE to SCT Functional Clock. */

    kCOMPUTE_BASE_to_UTICK0_CLK =
        CLKCTL0_TUPLE_MUXA(UTICK0FCLKSEL_OFFSET, 0),                        /*!< Attach compute base clock to UTICK0. */
    kLPOSC_to_UTICK0_CLK     = CLKCTL0_TUPLE_MUXA(UTICK0FCLKSEL_OFFSET, 1), /*!< Attach main_pll_pfd0 to UTICK0. */
    kFRO0_DIV1_to_UTICK0_CLK = CLKCTL0_TUPLE_MUXA(UTICK0FCLKSEL_OFFSET, 2), /*!< Attach FRO0 Max to UTICK0. */
    kFRO1_DIV2_to_UTICK0_CLK = CLKCTL0_TUPLE_MUXA(UTICK0FCLKSEL_OFFSET, 3), /*!< Attach FRO1_DIV2 to UTICK0. */
    kNONE_to_UTICK0_CLK      = CLKCTL0_TUPLE_MUXA_NONE(UTICK0FCLKSEL_OFFSET, 0), /*!< Attach NONE to UTICK0. */

    kLPOSC_to_WWDT0 = CLKCTL0_TUPLE_MUXA(WWDT0FCLKSEL_OFFSET, 0),      /*!< Attach LPOSC to WWDT0 Functional Clock. */
    kNONE_to_WWDT0  = CLKCTL0_TUPLE_MUXA_NONE(WWDT0FCLKSEL_OFFSET, 0), /*!< Attach NONE to WWDT0 Functional Clock. */

    kLPOSC_to_WWDT1 = CLKCTL0_TUPLE_MUXA(WWDT1FCLKSEL_OFFSET, 0),      /*!< Attach LPOSC to WWDT1 Functional Clock. */
    kNONE_to_WWDT1  = CLKCTL0_TUPLE_MUXA_NONE(WWDT1FCLKSEL_OFFSET, 0), /*!< Attach NONE to WWDT1 Functional Clock. */

    kCOMPUTE_BASE_to_SYSTICK =
        CLKCTL0_TUPLE_MUXA(SYSTICKFCLKSEL_OFFSET, 0), /*!< Attach Compute base clock to SYSTICK Functional Clock. */
    kLPOSC_to_SYSTICK = CLKCTL0_TUPLE_MUXA(SYSTICKFCLKSEL_OFFSET, 1), /*!< Attach LPOSC to SYSTICK Functional Clock. */
    k32KHZ_WAKE_to_SYSTICK =
        CLKCTL0_TUPLE_MUXA(SYSTICKFCLKSEL_OFFSET, 2), /*!< Attach 32 KHz wake clock(switch to other clock source before
                                                 compute vdd2 enter SRPG mode.) to SYSTICK Functional Clock. */
    kOSC_CLK_to_SYSTICK =
        CLKCTL0_TUPLE_MUXA(SYSTICKFCLKSEL_OFFSET, 3), /*!< Attach OSC_CLK clock to SYSTICK Functional Clock. */
    kNONE_to_SYSTICK =
        CLKCTL0_TUPLE_MUXA_NONE(SYSTICKFCLKSEL_OFFSET, 0), /*!< Attach NONE to SYSTICK Functional Clock. */

    kCOMPUTE_BASE_to_SAI012 =
        CLKCTL0_TUPLE_MUXA(SAI012FCLKSEL_OFFSET, 0), /*!< Attach Compute base clock to SAI012 Clock. */
    kFRO2_DIV8_to_SAI012 = CLKCTL0_TUPLE_MUXA(SAI012FCLKSEL_OFFSET, 1), /*!< Attach FRO2_DIV8 to SAI012 Clock. */
    kFRO0_DIV1_to_SAI012 = CLKCTL0_TUPLE_MUXA(SAI012FCLKSEL_OFFSET, 2), /*!< Attach FRO0 max clock to SAI012 Clock. */
    kAUDIO_VDD2_to_SAI012 =
        CLKCTL0_TUPLE_MUXA(SAI012FCLKSEL_OFFSET, 3), /*!< Attach audio_clk_cmpt clock to SAI012 Clock. */
    kNONE_to_SAI012 = CLKCTL0_TUPLE_MUXA_NONE(SAI012FCLKSEL_OFFSET, 0), /*!< Attach NONE to SAI012 Clock. */

    kCOMPUTE_BASE_to_FCCLK0  = CLKCTL0_TUPLE_MUXA(FCCLK0SEL_OFFSET, 0), /*!< Attach compute base clock to FCCLK0. */
    kFRO0_DIV1_to_FCCLK0     = CLKCTL0_TUPLE_MUXA(FCCLK0SEL_OFFSET, 1), /*!< Attach FRO0 max clock to FCCLK0. */
    kMAIN_PLL_PFD3_to_FCCLK0 = CLKCTL0_TUPLE_MUXA(FCCLK0SEL_OFFSET, 2), /*!< Attach MAIN PLL PFD3 clock to FCCLK0. */
    kOSC_CLK_to_FCCLK0       = CLKCTL0_TUPLE_MUXA(FCCLK0SEL_OFFSET, 3), /*!< Attach OSC clock to FCCLK0. */
    kNONE_to_FCCLK0          = CLKCTL0_TUPLE_MUXA_NONE(FCCLK0SEL_OFFSET, 0), /*!< Attach NONE to FCCLK0. */

    kCOMPUTE_BASE_to_FCCLK1  = CLKCTL0_TUPLE_MUXA(FCCLK1SEL_OFFSET, 0), /*!< Attach compute base clock to FCCLK1. */
    kFRO0_DIV1_to_FCCLK1     = CLKCTL0_TUPLE_MUXA(FCCLK1SEL_OFFSET, 1), /*!< Attach FRO0 max clock to FCCLK1. */
    kMAIN_PLL_PFD3_to_FCCLK1 = CLKCTL0_TUPLE_MUXA(FCCLK1SEL_OFFSET, 2), /*!< Attach MAIN PLL PFD3 clock to FCCLK1. */
    kOSC_CLK_to_FCCLK1       = CLKCTL0_TUPLE_MUXA(FCCLK1SEL_OFFSET, 3), /*!< Attach OSC clock to FCCLK1. */
    kNONE_to_FCCLK1          = CLKCTL0_TUPLE_MUXA_NONE(FCCLK1SEL_OFFSET, 0), /*!< Attach NONE to FCCLK1. */

    kCOMPUTE_BASE_to_FCCLK2  = CLKCTL0_TUPLE_MUXA(FCCLK2SEL_OFFSET, 0), /*!< Attach compute base clock to FCCLK2. */
    kFRO0_DIV1_to_FCCLK2     = CLKCTL0_TUPLE_MUXA(FCCLK2SEL_OFFSET, 1), /*!< Attach FRO0 max clock to FCCLK2. */
    kMAIN_PLL_PFD3_to_FCCLK2 = CLKCTL0_TUPLE_MUXA(FCCLK2SEL_OFFSET, 2), /*!< Attach MAIN PLL PFD3 clock to FCCLK2. */
    kOSC_CLK_to_FCCLK2       = CLKCTL0_TUPLE_MUXA(FCCLK2SEL_OFFSET, 3), /*!< Attach OSC clock to FCCLK2. */
    kNONE_to_FCCLK2          = CLKCTL0_TUPLE_MUXA_NONE(FCCLK2SEL_OFFSET, 0), /*!< Attach NONE to FCCLK2. */

    kCOMPUTE_BASE_to_FCCLK3  = CLKCTL0_TUPLE_MUXA(FCCLK3SEL_OFFSET, 0), /*!< Attach compute base clock to FCCLK3. */
    kFRO0_DIV1_to_FCCLK3     = CLKCTL0_TUPLE_MUXA(FCCLK3SEL_OFFSET, 1), /*!< Attach FRO0 max clock to FCCLK3. */
    kMAIN_PLL_PFD3_to_FCCLK3 = CLKCTL0_TUPLE_MUXA(FCCLK3SEL_OFFSET, 2), /*!< Attach MAIN PLL PFD3 clock to FCCLK3. */
    kOSC_CLK_to_FCCLK3       = CLKCTL0_TUPLE_MUXA(FCCLK3SEL_OFFSET, 3), /*!< Attach OSC clock to FCCLK3. */
    kNONE_to_FCCLK3          = CLKCTL0_TUPLE_MUXA_NONE(FCCLK3SEL_OFFSET, 0), /*!< Attach NONE to FCCLK3. */

    kFCCLK0_to_FLEXCOMM0 = CLKCTL0_TUPLE_MUXA(FC0FCLKSEL_OFFSET, 0),         /*!< Attach FCCLK0 to FLEXCOMM0. */
    kFCCLK1_to_FLEXCOMM0 = CLKCTL0_TUPLE_MUXA(FC0FCLKSEL_OFFSET, 1),         /*!< Attach FCCLK1 to FLEXCOMM0. */
    kFCCLK2_to_FLEXCOMM0 = CLKCTL0_TUPLE_MUXA(FC0FCLKSEL_OFFSET, 2),         /*!< Attach FCCLK2 to FLEXCOMM0. */
    kFCCLK3_to_FLEXCOMM0 = CLKCTL0_TUPLE_MUXA(FC0FCLKSEL_OFFSET, 3),         /*!< Attach FCCLK3 to FLEXCOMM0. */
    kNONE_to_FLEXCOMM0   = CLKCTL0_TUPLE_MUXA_NONE(FC0FCLKSEL_OFFSET, 0),    /*!< Attach NONE to FLEXCOMM0. */

    kFCCLK0_to_FLEXCOMM1 = CLKCTL0_TUPLE_MUXA(FC1FCLKSEL_OFFSET, 0),         /*!< Attach FCCLK0 to FLEXCOMM1. */
    kFCCLK1_to_FLEXCOMM1 = CLKCTL0_TUPLE_MUXA(FC1FCLKSEL_OFFSET, 1),         /*!< Attach FCCLK1 to FLEXCOMM1. */
    kFCCLK2_to_FLEXCOMM1 = CLKCTL0_TUPLE_MUXA(FC1FCLKSEL_OFFSET, 2),         /*!< Attach FCCLK2 to FLEXCOMM1. */
    kFCCLK3_to_FLEXCOMM1 = CLKCTL0_TUPLE_MUXA(FC1FCLKSEL_OFFSET, 3),         /*!< Attach FCCLK3 to FLEXCOMM1. */
    kNONE_to_FLEXCOMM1   = CLKCTL0_TUPLE_MUXA_NONE(FC1FCLKSEL_OFFSET, 0),    /*!< Attach NONE to FLEXCOMM1. */

    kFCCLK0_to_FLEXCOMM2 = CLKCTL0_TUPLE_MUXA(FC2FCLKSEL_OFFSET, 0),         /*!< Attach FCCLK0 to FLEXCOMM2. */
    kFCCLK1_to_FLEXCOMM2 = CLKCTL0_TUPLE_MUXA(FC2FCLKSEL_OFFSET, 1),         /*!< Attach FCCLK1 to FLEXCOMM2. */
    kFCCLK2_to_FLEXCOMM2 = CLKCTL0_TUPLE_MUXA(FC2FCLKSEL_OFFSET, 2),         /*!< Attach FCCLK2 to FLEXCOMM2. */
    kFCCLK3_to_FLEXCOMM2 = CLKCTL0_TUPLE_MUXA(FC2FCLKSEL_OFFSET, 3),         /*!< Attach FCCLK3 to FLEXCOMM2. */
    kNONE_to_FLEXCOMM2   = CLKCTL0_TUPLE_MUXA_NONE(FC2FCLKSEL_OFFSET, 0),    /*!< Attach NONE to FLEXCOMM2. */

    kFCCLK0_to_FLEXCOMM3 = CLKCTL0_TUPLE_MUXA(FC3FCLKSEL_OFFSET, 0),         /*!< Attach FCCLK0 to FLEXCOMM3. */
    kFCCLK1_to_FLEXCOMM3 = CLKCTL0_TUPLE_MUXA(FC3FCLKSEL_OFFSET, 1),         /*!< Attach FCCLK1 to FLEXCOMM3. */
    kFCCLK2_to_FLEXCOMM3 = CLKCTL0_TUPLE_MUXA(FC3FCLKSEL_OFFSET, 2),         /*!< Attach FCCLK2 to FLEXCOMM3. */
    kFCCLK3_to_FLEXCOMM3 = CLKCTL0_TUPLE_MUXA(FC3FCLKSEL_OFFSET, 3),         /*!< Attach FCCLK3 to FLEXCOMM3. */
    kNONE_to_FLEXCOMM3   = CLKCTL0_TUPLE_MUXA_NONE(FC3FCLKSEL_OFFSET, 0),    /*!< Attach NONE to FLEXCOMM3. */

    kFCCLK0_to_FLEXCOMM4 = CLKCTL0_TUPLE_MUXA(FC4FCLKSEL_OFFSET, 0),         /*!< Attach FCCLK0 to FLEXCOMM4. */
    kFCCLK1_to_FLEXCOMM4 = CLKCTL0_TUPLE_MUXA(FC4FCLKSEL_OFFSET, 1),         /*!< Attach FCCLK1 to FLEXCOMM4. */
    kFCCLK2_to_FLEXCOMM4 = CLKCTL0_TUPLE_MUXA(FC4FCLKSEL_OFFSET, 2),         /*!< Attach FCCLK2 to FLEXCOMM4. */
    kFCCLK3_to_FLEXCOMM4 = CLKCTL0_TUPLE_MUXA(FC4FCLKSEL_OFFSET, 3),         /*!< Attach FCCLK3 to FLEXCOMM4. */
    kNONE_to_FLEXCOMM4   = CLKCTL0_TUPLE_MUXA_NONE(FC4FCLKSEL_OFFSET, 0),    /*!< Attach NONE to FLEXCOMM4. */

    kFCCLK0_to_FLEXCOMM5 = CLKCTL0_TUPLE_MUXA(FC5FCLKSEL_OFFSET, 0),         /*!< Attach FCCLK0 to FLEXCOMM5. */
    kFCCLK1_to_FLEXCOMM5 = CLKCTL0_TUPLE_MUXA(FC5FCLKSEL_OFFSET, 1),         /*!< Attach FCCLK1 to FLEXCOMM5. */
    kFCCLK2_to_FLEXCOMM5 = CLKCTL0_TUPLE_MUXA(FC5FCLKSEL_OFFSET, 2),         /*!< Attach FCCLK2 to FLEXCOMM5. */
    kFCCLK3_to_FLEXCOMM5 = CLKCTL0_TUPLE_MUXA(FC5FCLKSEL_OFFSET, 3),         /*!< Attach FCCLK3 to FLEXCOMM5. */
    kNONE_to_FLEXCOMM5   = CLKCTL0_TUPLE_MUXA_NONE(FC5FCLKSEL_OFFSET, 0),    /*!< Attach NONE to FLEXCOMM5. */

    kFCCLK0_to_FLEXCOMM6 = CLKCTL0_TUPLE_MUXA(FC6FCLKSEL_OFFSET, 0),         /*!< Attach FCCLK0 to FLEXCOMM6. */
    kFCCLK1_to_FLEXCOMM6 = CLKCTL0_TUPLE_MUXA(FC6FCLKSEL_OFFSET, 1),         /*!< Attach FCCLK1 to FLEXCOMM6. */
    kFCCLK2_to_FLEXCOMM6 = CLKCTL0_TUPLE_MUXA(FC6FCLKSEL_OFFSET, 2),         /*!< Attach FCCLK2 to FLEXCOMM6. */
    kFCCLK3_to_FLEXCOMM6 = CLKCTL0_TUPLE_MUXA(FC6FCLKSEL_OFFSET, 3),         /*!< Attach FCCLK3 to FLEXCOMM6. */
    kNONE_to_FLEXCOMM6   = CLKCTL0_TUPLE_MUXA_NONE(FC6FCLKSEL_OFFSET, 0),    /*!< Attach NONE to FLEXCOMM6. */

    kFCCLK0_to_FLEXCOMM7 = CLKCTL0_TUPLE_MUXA(FC7FCLKSEL_OFFSET, 0),         /*!< Attach FCCLK0 to FLEXCOMM7. */
    kFCCLK1_to_FLEXCOMM7 = CLKCTL0_TUPLE_MUXA(FC7FCLKSEL_OFFSET, 1),         /*!< Attach FCCLK1 to FLEXCOMM7. */
    kFCCLK2_to_FLEXCOMM7 = CLKCTL0_TUPLE_MUXA(FC7FCLKSEL_OFFSET, 2),         /*!< Attach FCCLK2 to FLEXCOMM7. */
    kFCCLK3_to_FLEXCOMM7 = CLKCTL0_TUPLE_MUXA(FC7FCLKSEL_OFFSET, 3),         /*!< Attach FCCLK3 to FLEXCOMM7. */
    kNONE_to_FLEXCOMM7   = CLKCTL0_TUPLE_MUXA_NONE(FC7FCLKSEL_OFFSET, 0),    /*!< Attach NONE to FLEXCOMM7. */

    kFCCLK0_to_FLEXCOMM8 = CLKCTL0_TUPLE_MUXA(FC8FCLKSEL_OFFSET, 0),         /*!< Attach FCCLK0 to FLEXCOMM8. */
    kFCCLK1_to_FLEXCOMM8 = CLKCTL0_TUPLE_MUXA(FC8FCLKSEL_OFFSET, 1),         /*!< Attach FCCLK1 to FLEXCOMM8. */
    kFCCLK2_to_FLEXCOMM8 = CLKCTL0_TUPLE_MUXA(FC8FCLKSEL_OFFSET, 2),         /*!< Attach FCCLK2 to FLEXCOMM8. */
    kFCCLK3_to_FLEXCOMM8 = CLKCTL0_TUPLE_MUXA(FC8FCLKSEL_OFFSET, 3),         /*!< Attach FCCLK3 to FLEXCOMM8. */
    kNONE_to_FLEXCOMM8   = CLKCTL0_TUPLE_MUXA_NONE(FC8FCLKSEL_OFFSET, 0),    /*!< Attach NONE to FLEXCOMM8. */

    kFCCLK0_to_FLEXCOMM9 = CLKCTL0_TUPLE_MUXA(FC9FCLKSEL_OFFSET, 0),         /*!< Attach FCCLK0 to FLEXCOMM9. */
    kFCCLK1_to_FLEXCOMM9 = CLKCTL0_TUPLE_MUXA(FC9FCLKSEL_OFFSET, 1),         /*!< Attach FCCLK1 to FLEXCOMM9. */
    kFCCLK2_to_FLEXCOMM9 = CLKCTL0_TUPLE_MUXA(FC9FCLKSEL_OFFSET, 2),         /*!< Attach FCCLK2 to FLEXCOMM9. */
    kFCCLK3_to_FLEXCOMM9 = CLKCTL0_TUPLE_MUXA(FC9FCLKSEL_OFFSET, 3),         /*!< Attach FCCLK3 to FLEXCOMM9. */
    kNONE_to_FLEXCOMM9   = CLKCTL0_TUPLE_MUXA_NONE(FC9FCLKSEL_OFFSET, 0),    /*!< Attach NONE to FLEXCOMM9. */

    kFCCLK0_to_FLEXCOMM10 = CLKCTL0_TUPLE_MUXA(FC10FCLKSEL_OFFSET, 0),       /*!< Attach FCCLK0 to FLEXCOMM10. */
    kFCCLK1_to_FLEXCOMM10 = CLKCTL0_TUPLE_MUXA(FC10FCLKSEL_OFFSET, 1),       /*!< Attach FCCLK1 to FLEXCOMM10. */
    kFCCLK2_to_FLEXCOMM10 = CLKCTL0_TUPLE_MUXA(FC10FCLKSEL_OFFSET, 2),       /*!< Attach FCCLK2 to FLEXCOMM10. */
    kFCCLK3_to_FLEXCOMM10 = CLKCTL0_TUPLE_MUXA(FC10FCLKSEL_OFFSET, 3),       /*!< Attach FCCLK3 to FLEXCOMM10. */
    kNONE_to_FLEXCOMM10   = CLKCTL0_TUPLE_MUXA_NONE(FC10FCLKSEL_OFFSET, 0),  /*!< Attach NONE to FLEXCOMM10. */

    kFCCLK0_to_FLEXCOMM11 = CLKCTL0_TUPLE_MUXA(FC11FCLKSEL_OFFSET, 0),       /*!< Attach FCCLK0 to FLEXCOMM11. */
    kFCCLK1_to_FLEXCOMM11 = CLKCTL0_TUPLE_MUXA(FC11FCLKSEL_OFFSET, 1),       /*!< Attach FCCLK1 to FLEXCOMM11. */
    kFCCLK2_to_FLEXCOMM11 = CLKCTL0_TUPLE_MUXA(FC11FCLKSEL_OFFSET, 2),       /*!< Attach FCCLK2 to FLEXCOMM11. */
    kFCCLK3_to_FLEXCOMM11 = CLKCTL0_TUPLE_MUXA(FC11FCLKSEL_OFFSET, 3),       /*!< Attach FCCLK3 to FLEXCOMM11. */
    kNONE_to_FLEXCOMM11   = CLKCTL0_TUPLE_MUXA_NONE(FC11FCLKSEL_OFFSET, 0),  /*!< Attach NONE to FLEXCOMM11. */

    kFCCLK0_to_FLEXCOMM12 = CLKCTL0_TUPLE_MUXA(FC12FCLKSEL_OFFSET, 0),       /*!< Attach FCCLK0 to FLEXCOMM12. */
    kFCCLK1_to_FLEXCOMM12 = CLKCTL0_TUPLE_MUXA(FC12FCLKSEL_OFFSET, 1),       /*!< Attach FCCLK1 to FLEXCOMM12. */
    kFCCLK2_to_FLEXCOMM12 = CLKCTL0_TUPLE_MUXA(FC12FCLKSEL_OFFSET, 2),       /*!< Attach FCCLK2 to FLEXCOMM12. */
    kFCCLK3_to_FLEXCOMM12 = CLKCTL0_TUPLE_MUXA(FC12FCLKSEL_OFFSET, 3),       /*!< Attach FCCLK3 to FLEXCOMM12. */
    kNONE_to_FLEXCOMM12   = CLKCTL0_TUPLE_MUXA_NONE(FC12FCLKSEL_OFFSET, 0),  /*!< Attach NONE to FLEXCOMM12. */

    kFCCLK0_to_FLEXCOMM13 = CLKCTL0_TUPLE_MUXA(FC13FCLKSEL_OFFSET, 0),       /*!< Attach FCCLK0 to FLEXCOMM13. */
    kFCCLK1_to_FLEXCOMM13 = CLKCTL0_TUPLE_MUXA(FC13FCLKSEL_OFFSET, 1),       /*!< Attach FCCLK1 to FLEXCOMM13. */
    kFCCLK2_to_FLEXCOMM13 = CLKCTL0_TUPLE_MUXA(FC13FCLKSEL_OFFSET, 2),       /*!< Attach FCCLK2 to FLEXCOMM13. */
    kFCCLK3_to_FLEXCOMM13 = CLKCTL0_TUPLE_MUXA(FC13FCLKSEL_OFFSET, 3),       /*!< Attach FCCLK3 to FLEXCOMM13. */
    kNONE_to_FLEXCOMM13   = CLKCTL0_TUPLE_MUXA_NONE(FC13FCLKSEL_OFFSET, 0),  /*!< Attach NONE to FLEXCOMM13. */

    kCOMPUTE_BASE_to_CTIMER0 =
        CLKCTL0_TUPLE_MUXA(CTIMER0FCLKSEL_OFFSET, 0), /*!< Attach Compute base clock to CTIMER0 Clock. */
    kAUDIO_VDD2_to_CTIMER0 =
        CLKCTL0_TUPLE_MUXA(CTIMER0FCLKSEL_OFFSET, 1), /*!< Attach audio_clk_cmpt clock to CTIMER0 Clock. */
    kFRO0_DIV1_to_CTIMER0 =
        CLKCTL0_TUPLE_MUXA(CTIMER0FCLKSEL_OFFSET, 2), /*!< Attach FRO0 max clock to CTIMER0 Clock. */
    k32KHZ_WAKE_to_CTIMER0 =
        CLKCTL0_TUPLE_MUXA(CTIMER0FCLKSEL_OFFSET, 3), /*!< Attach 32KHz wake clock to CTIMER0 Clock. */
    kNONE_to_CTIMER0 = CLKCTL0_TUPLE_MUXA_NONE(CTIMER0FCLKSEL_OFFSET, 0), /*!< Attach NONE to CTIMER0 Clock. */

    kCOMPUTE_BASE_to_CTIMER1 =
        CLKCTL0_TUPLE_MUXA(CTIMER1FCLKSEL_OFFSET, 0), /*!< Attach Compute base clock to CTIMER1 Clock. */
    kAUDIO_VDD2_to_CTIMER1 =
        CLKCTL0_TUPLE_MUXA(CTIMER1FCLKSEL_OFFSET, 1), /*!< Attach audio_clk_cmpt clock to CTIMER1  Clock. */
    kFRO0_DIV1_to_CTIMER1 =
        CLKCTL0_TUPLE_MUXA(CTIMER1FCLKSEL_OFFSET, 2), /*!< Attach FRO0 max clock to CTIMER1  Clock. */
    k32KHZ_WAKE_to_CTIMER1 =
        CLKCTL0_TUPLE_MUXA(CTIMER1FCLKSEL_OFFSET, 3), /*!< Attach 32KHz wake clock to CTIMER1 Clock. */
    kNONE_to_CTIMER1 = CLKCTL0_TUPLE_MUXA_NONE(CTIMER1FCLKSEL_OFFSET, 0), /*!< Attach NONE to CTIMER1 Clock. */

    kCOMPUTE_BASE_to_CTIMER2 =
        CLKCTL0_TUPLE_MUXA(CTIMER2FCLKSEL_OFFSET, 0), /*!< Attach Compute base clock to CTIMER2 Clock. */
    kAUDIO_VDD2_to_CTIMER2 =
        CLKCTL0_TUPLE_MUXA(CTIMER2FCLKSEL_OFFSET, 1), /*!< Attach audio_clk_cmpt clock to CTIMER2  Clock. */
    kFRO0_DIV1_to_CTIMER2 =
        CLKCTL0_TUPLE_MUXA(CTIMER2FCLKSEL_OFFSET, 2), /*!< Attach FRO0 max clock to CTIMER2  Clock. */
    k32KHZ_WAKE_to_CTIMER2 =
        CLKCTL0_TUPLE_MUXA(CTIMER2FCLKSEL_OFFSET, 3), /*!< Attach 32KHz wake clock to CTIMER2 Clock. */
    kNONE_to_CTIMER2 = CLKCTL0_TUPLE_MUXA_NONE(CTIMER2FCLKSEL_OFFSET, 0), /*!< Attach NONE to CTIMER2 Clock. */

    kCOMPUTE_BASE_to_CTIMER3 =
        CLKCTL0_TUPLE_MUXA(CTIMER3FCLKSEL_OFFSET, 0), /*!< Attach Compute base clock to CTIMER3 Clock. */
    kAUDIO_VDD2_to_CTIMER3 =
        CLKCTL0_TUPLE_MUXA(CTIMER3FCLKSEL_OFFSET, 1), /*!< Attach audio_clk_cmpt clock to CTIMER3  Clock. */
    kFRO0_DIV1_to_CTIMER3 =
        CLKCTL0_TUPLE_MUXA(CTIMER3FCLKSEL_OFFSET, 2), /*!< Attach FRO0 max clock to CTIMER3  Clock. */
    k32KHZ_WAKE_to_CTIMER3 =
        CLKCTL0_TUPLE_MUXA(CTIMER3FCLKSEL_OFFSET, 3), /*!< Attach 32KHz wake clock to CTIMER3 Clock. */
    kNONE_to_CTIMER3 = CLKCTL0_TUPLE_MUXA_NONE(CTIMER3FCLKSEL_OFFSET, 0), /*!< Attach NONE to CTIMER3 Clock. */

    kCOMPUTE_BASE_to_CTIMER4 =
        CLKCTL0_TUPLE_MUXA(CTIMER4FCLKSEL_OFFSET, 0), /*!< Attach Compute base clock to CTIMER4 Clock. */
    kAUDIO_VDD2_to_CTIMER4 =
        CLKCTL0_TUPLE_MUXA(CTIMER4FCLKSEL_OFFSET, 1), /*!< Attach audio_clk_cmpt clock to CTIMER4  Clock. */
    kFRO0_DIV1_to_CTIMER4 =
        CLKCTL0_TUPLE_MUXA(CTIMER4FCLKSEL_OFFSET, 2), /*!< Attach FRO0 max clock to CTIMER4  Clock. */
    k32KHZ_WAKE_to_CTIMER4 =
        CLKCTL0_TUPLE_MUXA(CTIMER4FCLKSEL_OFFSET, 3), /*!< Attach 32KHz wake clock to CTIMER4 Clock. */
    kNONE_to_CTIMER4 = CLKCTL0_TUPLE_MUXA_NONE(CTIMER4FCLKSEL_OFFSET, 0), /*!< Attach NONE to CTIMER4 Clock. */

    kCOMPUTE_BASE_to_TRNG =
        CLKCTL0_TUPLE_MUXA(TRNGFCLKSEL_OFFSET, 0), /*!< Attach Compute base clock to TRNG Functional Clock. */
    kFRO1_DIV2_to_TRNG =
        CLKCTL0_TUPLE_MUXA(TRNGFCLKSEL_OFFSET, 1), /*!< Attach FRO1_DIV2 clock to TRNG Functional Clock. */
    kFRO1_DIV8_to_TRNG =
        CLKCTL0_TUPLE_MUXA(TRNGFCLKSEL_OFFSET, 2), /*!< Attach FRO1_DIV8 clock to TRNG Functional Clock. */
    kFRO1_DIV3_to_TRNG =
        CLKCTL0_TUPLE_MUXA(TRNGFCLKSEL_OFFSET, 3), /*!< Attach FRO1_DIV3 clock to TRNG Functional Clock. */
    kNONE_to_TRNG = CLKCTL0_TUPLE_MUXA_NONE(TRNGFCLKSEL_OFFSET, 0), /*!< Attach NONE to TRNG Functional Clock. */

    kCOMPUTE_BASE_to_I3C01 =
        CLKCTL0_TUPLE_MUXA(I3C01FCLKSEL_OFFSET, 0), /*!< Attach Compute base clock to I3C0 and I3C1 Functional Clock. */
    kFRO0_DIV1_to_I3C01 =
        CLKCTL0_TUPLE_MUXA(I3C01FCLKSEL_OFFSET, 1), /*!< Attach FRO0 MAX to I3C0 and I3C1 Functional Clock. */
    kFRO1_DIV8_to_I3C01 =
        CLKCTL0_TUPLE_MUXA(I3C01FCLKSEL_OFFSET, 2), /*!< Attach FRO1_DIV8 clock to I3C0 and I3C1 Functional Clock. */
    kOSC_CLK_to_I3C01 =
        CLKCTL0_TUPLE_MUXA(I3C01FCLKSEL_OFFSET, 3), /*!< Attach OSC_CLK clock to I3C0 and I3C1 Functional Clock. */
    kNONE_to_I3C01 =
        CLKCTL0_TUPLE_MUXA_NONE(I3C01FCLKSEL_OFFSET, 0), /*!< Attach NONE to I3C0 and I3C1 Functional Clock. */

    kCOMPUTE_BASE_to_I3C01_PCLK =
        CLKCTL0_TUPLE_MUXA(I3C01PCLKSEL_OFFSET, 0), /*!< Attach Compute base clock to I3C0 and I3C1 P-CLK. */
    kMAIN_PLL_PFD0_to_I3C01_PCLK =
        CLKCTL0_TUPLE_MUXA(I3C01PCLKSEL_OFFSET, 1), /*!< Attach MAIN PLL PFD0 to I3C0 and I3C1 P-CLK. */
    kFRO0_DIV1_to_I3C01_PCLK =
        CLKCTL0_TUPLE_MUXA(I3C01PCLKSEL_OFFSET, 2), /*!< Attach FRO0 MAX to I3C0 and I3C1 P-CLK. */
    kFRO1_DIV1_to_I3C01_PCLK =
        CLKCTL0_TUPLE_MUXA(I3C01PCLKSEL_OFFSET, 3), /*!< Attach FRO1 MAX to I3C0 and I3C1 P-CLK. */
    kNONE_to_I3C01_PCLK = CLKCTL0_TUPLE_MUXA_NONE(I3C01PCLKSEL_OFFSET, 0), /*!< Attach NONE to I3C0 and I3C1 P-CLK. */

    kCOMMON_VDD2_BASE_to_VDD2_CLKOUT =
        CLKCTL0_TUPLE_MUXA(CLKOUTCLKSEL_OFFSET, 0), /*!< Attach Common VDD2 Base Clock to VDD2 CLKOUT Clock. */
    kMAIN_PLL_PFD0_to_VDD2_CLKOUT =
        CLKCTL0_TUPLE_MUXA(CLKOUTCLKSEL_OFFSET, 1), /*!< Attach MAIN PLL PFD0 Clock to VDD2 CLKOUT Clock. */
    kFRO0_DIV1_to_VDD2_CLKOUT =
        CLKCTL0_TUPLE_MUXA(CLKOUTCLKSEL_OFFSET, 2), /*!< Attach FRO0 Max Clock to VDD2 CLKOUT Clock. */
    kFRO1_DIV1_to_VDD2_CLKOUT =
        CLKCTL0_TUPLE_MUXA(CLKOUTCLKSEL_OFFSET, 3), /*!< Attach FRO1 Max Clock to VDD2 CLKOUT Clock. */
    kNONE_to_VDD2_CLKOUT = CLKCTL0_TUPLE_MUXA_NONE(CLKOUTCLKSEL_OFFSET, 0), /*!< Attach NONE to VDD2 CLKOUT Clock. */

    kMCLK_to_AUDIO_VDD2 =
        CLKCTL0_TUPLE_MUXA(AUDIOVDD2CLKSEL_OFFSET, 0), /*!< Attach MCLK IN from Pad to Audio VDD2 Clock. */
    kOSC_CLK_to_AUDIO_VDD2 =
        CLKCTL0_TUPLE_MUXA(AUDIOVDD2CLKSEL_OFFSET, 1), /*!< Attach OSC clock to Audio VDD2 Clock. */
    kFRO2_DIV8_to_AUDIO_VDD2 =
        CLKCTL0_TUPLE_MUXA(AUDIOVDD2CLKSEL_OFFSET, 2), /*!< Attach FRO2_DIV8 clock to Audio VDD2 Clock. */
    kAUDIO_PLL_PFD3_to_AUDIO_VDD2 =
        CLKCTL0_TUPLE_MUXA(AUDIOVDD2CLKSEL_OFFSET, 3), /*!< Attach AUDIO PLL PFD3 clock to Audio VDD2 Clock. */

#else                                                  /* Dedicated defination for sense domain */
    kFRO1_DIV3_to_SENSE_BASE =
        CLKCTL1_TUPLE_MUXA(SENSEBASECLKSEL_OFFSET, 0), /*!< Attach FRO1 divided-by-3 clock to Sense Base Clock. */
    kFRO1_DIV1_to_SENSE_BASE =
        CLKCTL1_TUPLE_MUXA(SENSEBASECLKSEL_OFFSET, 1), /*!< Attach FRO1 max clock to Sense Base Clock. */
    kFRO2_DIV3_to_SENSE_BASE =
        CLKCTL1_TUPLE_MUXA(SENSEBASECLKSEL_OFFSET, 2), /*!< Attach FRO2 divided-by-3 clock to Sense Base Clock. */
    kLPOSC_to_SENSE_BASE = CLKCTL1_TUPLE_MUXA(SENSEBASECLKSEL_OFFSET, 3), /*!< Attach LPOSC to Sense Base Clock. */

    kSENSE_BASE_to_SENSE_DSP =
        CLKCTL1_TUPLE_MUXA(SENSEDSPCPUCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to Sense DSP Clock. */
    kFRO2_DIV1_to_SENSE_DSP =
        CLKCTL1_TUPLE_MUXA(SENSEDSPCPUCLKSEL_OFFSET, 1), /*!< Attach FRO2 max clock to Sense DSP Clock. */
    kAUDIO_PLL_PFD1_to_SENSE_DSP =
        CLKCTL1_TUPLE_MUXA(SENSEDSPCPUCLKSEL_OFFSET, 2), /*!< Attach Audio PLL PFD1 clock to Sense DSP Clock. */
    kFRO1_DIV1_to_SENSE_DSP =
        CLKCTL1_TUPLE_MUXA(SENSEDSPCPUCLKSEL_OFFSET, 3), /*!< Attach FRO1 max clock to Sense DSP Clock. */
    kNONE_to_SENSE_DSP = CLKCTL1_TUPLE_MUXA_NONE(SENSEDSPCPUCLKSEL_OFFSET, 0), /*!< Attach NONE to Sense DSP Clock. */

    kSENSE_BASE_to_SAI3 = CLKCTL1_TUPLE_MUXA(SAI3FCLKSEL_OFFSET, 0),      /*!< Attach Sense base clock to SAI3 Clock. */
    kFRO2_DIV8_to_SAI3  = CLKCTL1_TUPLE_MUXA(SAI3FCLKSEL_OFFSET, 1),      /*!< Attach FRO2_DIV8 clock to SAI3 Clock. */
    kFRO2_DIV1_to_SAI3  = CLKCTL1_TUPLE_MUXA(SAI3FCLKSEL_OFFSET, 2),      /*!< Attach FRO2 clock to SAI3 Clock. */
    kAUDIO_VDD1_to_SAI3 = CLKCTL1_TUPLE_MUXA(SAI3FCLKSEL_OFFSET, 3),      /*!< Attach audio_clk to SAI3 Clock. */
    kNONE_to_SAI3       = CLKCTL1_TUPLE_MUXA_NONE(SAI3FCLKSEL_OFFSET, 0), /*!< Attach NONE to SAI3 Clock. */

    kSENSE_BASE_to_UTICK =
        CLKCTL1_TUPLE_MUXA(UTICK1FCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to UTICK Functional Clock. */
    kLPOSC_to_UTICK = CLKCTL1_TUPLE_MUXA(UTICK1FCLKSEL_OFFSET, 1), /*!< Attach LPOSC clock to UTICK Functional Clock. */
    kFRO2_DIV1_to_UTICK =
        CLKCTL1_TUPLE_MUXA(UTICK1FCLKSEL_OFFSET, 2), /*!< Attach FRO2 max clock to UTICK Functional Clock. */
    kFRO1_DIV2_to_UTICK =
        CLKCTL1_TUPLE_MUXA(UTICK1FCLKSEL_OFFSET, 3), /*!< Attach FRO1_DIV2 clock to UTICK Functional Clock. */
    kNONE_to_UTICK = CLKCTL1_TUPLE_MUXA_NONE(UTICK1FCLKSEL_OFFSET, 0), /*!< Attach NONE to UTICK Functional Clock. */

    kLPOSC_to_WWDT2 = CLKCTL1_TUPLE_MUXA(WWDT2FCLKSEL_OFFSET, 0), /*!< Attach LPOSC clock to WWDT2 Functional Clock. */
    kNONE_to_WWDT2  = CLKCTL1_TUPLE_MUXA_NONE(WWDT2FCLKSEL_OFFSET, 0), /*!< Attach NONE to WWDT2 Functional Clock. */

    kLPOSC_to_WWDT3 = CLKCTL1_TUPLE_MUXA(WWDT3FCLKSEL_OFFSET, 0), /*!< Attach LPOSC clock to WWDT3 Functional Clock. */
    kNONE_to_WWDT3  = CLKCTL1_TUPLE_MUXA_NONE(WWDT3FCLKSEL_OFFSET, 0), /*!< Attach NONE to WWDT3 Functional Clock. */

    kSENSE_BASE_to_SYSTICK =
        CLKCTL1_TUPLE_MUXA(SYSTICKFCLKSEL_OFFSET, 0),      /*!< Attach Sense base clock to SYSTICK Functional Clock. */
    kLPOSC_to_SYSTICK =
        CLKCTL1_TUPLE_MUXA(SYSTICKFCLKSEL_OFFSET, 1),      /*!< Attach LPOSC clock to SYSTICK Functional Clock. */
    k32KHZ_WAKE_to_SYSTICK =
        CLKCTL1_TUPLE_MUXA(SYSTICKFCLKSEL_OFFSET, 2),      /*!< Attach 32 kHz wake clock(switch to other clock source
                                                          before sense vdd1 enter SRPG mode.) to SYSTICK Functional Clock. */
    kOSC_CLK_to_SYSTICK =
        CLKCTL1_TUPLE_MUXA(SYSTICKFCLKSEL_OFFSET, 3),      /*!< Attach OSC clock to SYSTICK Functional Clock. */
    kNONE_to_SYSTICK =
        CLKCTL1_TUPLE_MUXA_NONE(SYSTICKFCLKSEL_OFFSET, 0), /*!< Attach NONE to SYSTICK Functional Clock. */

    kSENSE_BASE_to_CTIMER5 =
        CLKCTL1_TUPLE_MUXA(CTIMER5FCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to CTIMER5 Clock. */
    kAUDIO_VDD1_to_CTIMER5 = CLKCTL1_TUPLE_MUXA(CTIMER5FCLKSEL_OFFSET, 1), /*!< Attach audio_clk to CTIMER5 Clock. */
    kFRO2_DIV1_to_CTIMER5 =
        CLKCTL1_TUPLE_MUXA(CTIMER5FCLKSEL_OFFSET, 2), /*!< Attach FRO2 Max clock to CTIMER5 Clock. */
    k32KHZ_WAKE_to_CTIMER5 =
        CLKCTL1_TUPLE_MUXA(CTIMER5FCLKSEL_OFFSET, 3), /*!< Attach 32KHz wake clock to CTIMER5 Clock. */
    kNONE_to_CTIMER5 = CLKCTL1_TUPLE_MUXA_NONE(CTIMER5FCLKSEL_OFFSET, 0), /*!< Attach NONE to CTIMER5 Clock. */

    kSENSE_BASE_to_CTIMER6 =
        CLKCTL1_TUPLE_MUXA(CTIMER6FCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to CTIMER6 Clock. */
    kAUDIO_VDD1_to_CTIMER6 = CLKCTL1_TUPLE_MUXA(CTIMER6FCLKSEL_OFFSET, 1), /*!< Attach audio_clk to CTIMER6 Clock. */
    kFRO2_DIV1_to_CTIMER6 =
        CLKCTL1_TUPLE_MUXA(CTIMER6FCLKSEL_OFFSET, 2), /*!< Attach FRO2 Max clock to CTIMER6 Clock. */
    k32KHZ_WAKE_to_CTIMER6 =
        CLKCTL1_TUPLE_MUXA(CTIMER6FCLKSEL_OFFSET, 3), /*!< Attach 32KHz wake clock to CTIMER6 Clock. */
    kNONE_to_CTIMER6 = CLKCTL1_TUPLE_MUXA_NONE(CTIMER6FCLKSEL_OFFSET, 0), /*!< Attach NONE to CTIMER6 Clock. */

    kSENSE_BASE_to_CTIMER7 =
        CLKCTL1_TUPLE_MUXA(CTIMER7FCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to CTIMER7 Clock. */
    kAUDIO_VDD1_to_CTIMER7 = CLKCTL1_TUPLE_MUXA(CTIMER7FCLKSEL_OFFSET, 1), /*!< Attach audio_clk to CTIMER7 Clock. */
    kFRO2_DIV1_to_CTIMER7 =
        CLKCTL1_TUPLE_MUXA(CTIMER7FCLKSEL_OFFSET, 2), /*!< Attach FRO2 Max clock to CTIMER7 Clock. */
    k32KHZ_WAKE_to_CTIMER7 =
        CLKCTL1_TUPLE_MUXA(CTIMER7FCLKSEL_OFFSET, 3), /*!< Attach 32KHz wake clock to CTIMER7 Clock. */
    kNONE_to_CTIMER7 = CLKCTL1_TUPLE_MUXA_NONE(CTIMER7FCLKSEL_OFFSET, 0), /*!< Attach NONE to CTIMER7 Clock. */

    kSENSE_BASE_to_I3C23 =
        CLKCTL1_TUPLE_MUXA(I3C23FCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to I3C2 and I3C3 Functional Clock. */
    kFRO2_DIV1_to_I3C23 =
        CLKCTL1_TUPLE_MUXA(I3C23FCLKSEL_OFFSET, 1), /*!< Attach FRO2 max clock to I3C2 and I3C3 Functional Clock. */
    kFRO1_DIV8_to_I3C23 =
        CLKCTL1_TUPLE_MUXA(I3C23FCLKSEL_OFFSET, 2), /*!< Attach FRO2_DIV8 clock to I3C2 and I3C3 Functional Clock. */
    kOSC_CLK_to_I3C23 =
        CLKCTL1_TUPLE_MUXA(I3C23FCLKSEL_OFFSET, 3), /*!< Attach OSC clock to I3C2 and I3C3 Functional Clock. */
    kNONE_to_I3C23 =
        CLKCTL1_TUPLE_MUXA_NONE(I3C23FCLKSEL_OFFSET, 0), /*!< Attach NONE to I3C2 and I3C3 Functional Clock. */

    kMCLK_to_AUDIO_VDD1 =
        CLKCTL1_TUPLE_MUXA(AUDIOVDD1CLKSEL_OFFSET, 0), /*!< Attach MCLK IN from Pad to Audio VDD1 Clock. */
    kOSC_to_AUDIO_VDD1 = CLKCTL1_TUPLE_MUXA(AUDIOVDD1CLKSEL_OFFSET, 1), /*!< Attach OSC clock to Audio VDD1 Clock. */
    kFRO2_DIV8_to_AUDIO_VDD1 =
        CLKCTL1_TUPLE_MUXA(AUDIOVDD1CLKSEL_OFFSET, 2), /*!< Attach FRO2_DIV8 clock to Audio VDD1 Clock. */
    kAUDIO_PLL_PFD3_to_AUDIO_VDD1 =
        CLKCTL1_TUPLE_MUXA(AUDIOVDD1CLKSEL_OFFSET, 3), /*!< Attach AUDIO PLL PFD3 clock to Audio VDD1 Clock. */

    kSENSE_BASE_to_FLEXCOMM17 =
        CLKCTL1_TUPLE_MUXA(FC17FCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to FLEXCOMM17. */
    kFRO2_DIV1_to_FLEXCOMM17  = CLKCTL1_TUPLE_MUXA(FC17FCLKSEL_OFFSET, 1), /*!< Attach FRO2 max clock to FLEXCOMM17. */
    kFRO1_DIV1_to_FLEXCOMM17  = CLKCTL1_TUPLE_MUXA(FC17FCLKSEL_OFFSET, 2), /*!< Attach FRO1 max clock to FLEXCOMM17. */
    k32KHZ_WAKE_to_FLEXCOMM17 = CLKCTL1_TUPLE_MUXA(FC17FCLKSEL_OFFSET, 3), /*!< Attach 32k_wake_clk to FLEXCOMM17. */
    kNONE_to_FLEXCOMM17       = CLKCTL1_TUPLE_MUXA_NONE(FC17FCLKSEL_OFFSET, 0), /*!< Attach NONE to FLEXCOMM17. */

    kSENSE_BASE_to_FLEXCOMM18 =
        CLKCTL1_TUPLE_MUXA(FC18FCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to FLEXCOMM18. */
    kFRO2_DIV1_to_FLEXCOMM18  = CLKCTL1_TUPLE_MUXA(FC18FCLKSEL_OFFSET, 1), /*!< Attach FRO2 max clock to FLEXCOMM18. */
    kFRO1_DIV1_to_FLEXCOMM18  = CLKCTL1_TUPLE_MUXA(FC18FCLKSEL_OFFSET, 2), /*!< Attach FRO1 max clock to FLEXCOMM18. */
    k32KHZ_WAKE_to_FLEXCOMM18 = CLKCTL1_TUPLE_MUXA(FC18FCLKSEL_OFFSET, 3), /*!< Attach 32k_wake_clk to FLEXCOMM18. */
    kNONE_to_FLEXCOMM18       = CLKCTL1_TUPLE_MUXA_NONE(FC18FCLKSEL_OFFSET, 0), /*!< Attach NONE to FLEXCOMM18. */

    kSENSE_BASE_to_FLEXCOMM19 =
        CLKCTL1_TUPLE_MUXA(FC19FCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to FLEXCOMM19. */
    kFRO2_DIV1_to_FLEXCOMM19  = CLKCTL1_TUPLE_MUXA(FC19FCLKSEL_OFFSET, 1), /*!< Attach FRO2 max clock to FLEXCOMM19. */
    kFRO1_DIV1_to_FLEXCOMM19  = CLKCTL1_TUPLE_MUXA(FC19FCLKSEL_OFFSET, 2), /*!< Attach FRO1 max clock to FLEXCOMM19. */
    k32KHZ_WAKE_to_FLEXCOMM19 = CLKCTL1_TUPLE_MUXA(FC19FCLKSEL_OFFSET, 3), /*!< Attach 32k_wake_clk to FLEXCOMM19. */
    kNONE_to_FLEXCOMM19       = CLKCTL1_TUPLE_MUXA_NONE(FC19FCLKSEL_OFFSET, 0), /*!< Attach NONE to FLEXCOMM19. */

    kSENSE_BASE_to_FLEXCOMM20 =
        CLKCTL1_TUPLE_MUXA(FC20FCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to FLEXCOMM20. */
    kFRO2_DIV1_to_FLEXCOMM20  = CLKCTL1_TUPLE_MUXA(FC20FCLKSEL_OFFSET, 1), /*!< Attach FRO2 max clock to FLEXCOMM20. */
    kFRO1_DIV1_to_FLEXCOMM20  = CLKCTL1_TUPLE_MUXA(FC20FCLKSEL_OFFSET, 2), /*!< Attach FRO1 max clock to FLEXCOMM20. */
    k32KHZ_WAKE_to_FLEXCOMM20 = CLKCTL1_TUPLE_MUXA(FC20FCLKSEL_OFFSET, 3), /*!< Attach 32k_wake_clk to FLEXCOMM20. */
    kNONE_to_FLEXCOMM20       = CLKCTL1_TUPLE_MUXA_NONE(FC20FCLKSEL_OFFSET, 0), /*!< Attach NONE to FLEXCOMM20. */

#endif                                                 /* FSL_CLOCK_DRIVER_COMPUTE */

    kCOMMON_BASE_to_COMMON_VDDN =
        CLKCTL2_TUPLE_MUXA(COMMONVDDNCLKSEL_OFFSET, 0), /*!< Attach Common base clock to Common VDDN Clock. */
    kMAIN_PLL_PFD3_to_COMMON_VDDN =
        CLKCTL2_TUPLE_MUXA(COMMONVDDNCLKSEL_OFFSET, 1), /*!< Attach Main PLL PFD3 clock to Common VDDN Clock. */
    kFRO1_DIV1_to_COMMON_VDDN =
        CLKCTL2_TUPLE_MUXA(COMMONVDDNCLKSEL_OFFSET, 2), /*!< Attach FRO1 max clock to Common VDDN Clock. */
    kOSC_CLK_to_COMMON_VDDN =
        CLKCTL2_TUPLE_MUXA(COMMONVDDNCLKSEL_OFFSET, 3), /*!< Attach OSC clock to Common VDDN Clock. */

    kOSC_CLK_to_USB_24MHZ =
        CLKCTL2_TUPLE_MUXA(USBCLKSRC24MCLKSEL_OFFSET, 0), /*!< Attach OSC_CLK clock to 24MHz USB OSC Clock. */
    kFRO1_DIV8_to_USB_24MHZ =
        CLKCTL2_TUPLE_MUXA(USBCLKSRC24MCLKSEL_OFFSET, 1), /*!< Attach FRO1_DIV8 clock to 24MHz USB OSC Clock. */

    kFRO1_DIV3_to_COMMON_BASE =
        CLKCTL2_TUPLE_MUXA(COMNBASECLKSEL_OFFSET, 0), /*!< Attach Fro1 divided-by-3 to Common Base Clock. */
    kFRO1_DIV1_to_COMMON_BASE =
        CLKCTL2_TUPLE_MUXA(COMNBASECLKSEL_OFFSET, 1), /*!< Attach Fro1 divided-by-1 to Common Base Clock. */
    kFRO0_DIV3_to_COMMON_BASE =
        CLKCTL2_TUPLE_MUXA(COMNBASECLKSEL_OFFSET, 2), /*!< Attach Fro0 divided-by-3 to Common Base Clock. */
    kLPOSC_to_COMMON_BASE = CLKCTL2_TUPLE_MUXA(COMNBASECLKSEL_OFFSET, 3), /*!< Attach LPOSC to Common Base Clock. */

    kOSC_CLK_to_EUSB_24MHZ =
        CLKCTL2_TUPLE_MUXA(EUSBCLKSRC24MCLKSEL_OFFSET, 0), /*!< Attach OSC_CLK clock to 24MHz eUSB OSC Clock. */
    kFRO1_DIV8_to_EUSB_24MHZ =
        CLKCTL2_TUPLE_MUXA(EUSBCLKSRC24MCLKSEL_OFFSET, 1), /*!< Attach FRO1_DIV8 clock to 24MHz eUSB OSC Clock. */

    kFRO1_DIV8_to_MAIN_PLL0 =
        CLKCTL2_TUPLE_MUXA(MAINPLL0CLKSEL_OFFSET, 0), /*!< Attach FRO1_DIV8 clock to Main PLL0 Clock. */
    kOSC_CLK_to_MAIN_PLL0 =
        CLKCTL2_TUPLE_MUXA(MAINPLL0CLKSEL_OFFSET, 1), /*!< Attach OSC_CLK clock to Main PLL0 Clock. */

    kFRO1_DIV8_to_AUDIO_PLL0 =
        CLKCTL2_TUPLE_MUXA(AUDIOPLL0CLKSEL_OFFSET, 0), /*!< Attach FRO1_DIV8 to Audio PLL0 Clock. */
    kOSC_CLK_to_AUDIO_PLL0 = CLKCTL2_TUPLE_MUXA(AUDIOPLL0CLKSEL_OFFSET,
                                                1), /*!< Attach OSC_CLK clock (User-Selectable) to Audio PLL0 Clock. */
    kSENSE_BASE_to_SENSE_MAIN =
        CLKCTL3_TUPLE_MUXA(SENSE_MAINCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to Sense main clock. */
    kFRO2_DIV1_to_SENSE_MAIN =
        CLKCTL3_TUPLE_MUXA(SENSE_MAINCLKSEL_OFFSET, 1), /*!< Attach FRO2 max clock to Sense main clock. */
    kAUDIO_PLL_PFD3_to_SENSE_MAIN =
        CLKCTL3_TUPLE_MUXA(SENSE_MAINCLKSEL_OFFSET, 2), /*!< Attach Audio PLL PFD3 clock to Sense main clock. */
    kFRO1_DIV1_to_SENSE_MAIN =
        CLKCTL3_TUPLE_MUXA(SENSE_MAINCLKSEL_OFFSET, 3), /*!< Attach FRO1 max clock to Sense main clock. */

    kSENSE_BASE_to_SENSE_RAM =
        CLKCTL3_TUPLE_MUXA(SENSERAMCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to Sense RAM clock. */
    kFRO2_DIV1_to_SENSE_RAM =
        CLKCTL3_TUPLE_MUXA(SENSERAMCLKSEL_OFFSET, 1), /*!< Attach FRO2 max clock to Sense RAM clock. */
    kAUDIO_PLL_PFD2_to_SENSE_RAM =
        CLKCTL3_TUPLE_MUXA(SENSERAMCLKSEL_OFFSET, 2), /*!< Attach Audio PLL PFD2 clock to Sense RAM clock. */
    kFRO1_DIV1_to_SENSE_RAM =
        CLKCTL3_TUPLE_MUXA(SENSERAMCLKSEL_OFFSET, 3), /*!< Attach FRO1 max clock to Sense RAM clock. */

    kSENSE_BASE_to_OSTIMER = CLKCTL3_TUPLE_MUXA(OSEVENTTFCLKSEL_OFFSET, 0),      /*!< Attach Sense Base to OSTIMER. */
    k32KHZ_WAKE_to_OSTIMER = CLKCTL3_TUPLE_MUXA(OSEVENTTFCLKSEL_OFFSET, 1),      /*!< Attach 32k_wake_clk to OSTIMER. */
    kLPOSC_to_OSTIMER      = CLKCTL3_TUPLE_MUXA(OSEVENTTFCLKSEL_OFFSET, 2),      /*!< Attach LPOSC to OSTIMER. */
    kOSC_CLK_to_OSTIMER    = CLKCTL3_TUPLE_MUXA(OSEVENTTFCLKSEL_OFFSET, 3),      /*!< Attach OSC clock to OSTIMER. */
    kNONE_to_OSTIMER       = CLKCTL3_TUPLE_MUXA_NONE(OSEVENTTFCLKSEL_OFFSET, 0), /*!< Attach NONE to OSTIMER. */

    kSENSE_BASE_to_SDADC =
        CLKCTL3_TUPLE_MUXA(SDADCFCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to SDADC Functional Clock. */
    kFRO2_DIV8_to_SDADC =
        CLKCTL3_TUPLE_MUXA(SDADCFCLKSEL_OFFSET, 1), /*!< Attach FRO2_DIV8 clock to SDADC Functional Clock. */
    kAUDIO_PLL_to_SDADC =
        CLKCTL3_TUPLE_MUXA(SDADCFCLKSEL_OFFSET, 2), /*!< Attach Audio PLL VCO clock to SDADC Functional Clock. */
    kAUDIO_VDD1_to_SDADC =
        CLKCTL3_TUPLE_MUXA(SDADCFCLKSEL_OFFSET, 3), /*!< Attach audio_clk to SDADC Functional Clock. */
    kNONE_to_SDADC = CLKCTL3_TUPLE_MUXA_NONE(SDADCFCLKSEL_OFFSET, 0), /*!< Attach NONE to SDADC Functional Clock. */

    kSENSE_BASE_to_ADC =
        CLKCTL3_TUPLE_MUXA(SARADCFCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to SARADC Functional Clock. */
    kMAIN_PLL_PFD1_to_ADC =
        CLKCTL3_TUPLE_MUXA(SARADCFCLKSEL_OFFSET, 1), /*!< Attach main_pll_pfd1 to SARADC Functional Clock. */
    kFRO2_DIV1_to_ADC =
        CLKCTL3_TUPLE_MUXA(SARADCFCLKSEL_OFFSET, 2), /*!< Attach FRO0 max clock to SARADC Functional Clock. */
    kOSC_CLK_to_ADC = CLKCTL3_TUPLE_MUXA(SARADCFCLKSEL_OFFSET, 3), /*!< Attach osc_clk to SARADC Functional Clock. */
    kNONE_to_ADC    = CLKCTL3_TUPLE_MUXA_NONE(SARADCFCLKSEL_OFFSET, 0), /*!< Attach NONE to SARADC Functional Clock. */

    kOSC32K_to_32K_WAKE      = CLKCTL3_TUPLE_MUXA(WAKE32KCLKSEL_OFFSET, 0), /*!< Attach OSC 32K to Wake 32k Clock. */
    kLPOSC_DIV32_to_32K_WAKE = CLKCTL3_TUPLE_MUXA(
        WAKE32KCLKSEL_OFFSET, 1), /*!< Attach LPOSC clock divided by 32 by default to Wake 32k Clock. */
    kNONE_to_32K_WAKE = CLKCTL3_TUPLE_MUXA(WAKE32KCLKSEL_OFFSET, 3), /*!< Attach NONE to Wake 32k Clock. */

    kSENSE_BASE_to_MICFIL0 =
        CLKCTL3_TUPLE_MUXA(MICFIL0FCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to MICFIL0 Functional Clock. */
    kAUDIO_PLL_PFD3_to_MICFIL0 =
        CLKCTL3_TUPLE_MUXA(MICFIL0FCLKSEL_OFFSET, 1), /*!< Attach Audio PLL PFD3 clock to MICFIL0 Functional Clock. */
    kFRO2_DIV1_to_MICFIL0 =
        CLKCTL3_TUPLE_MUXA(MICFIL0FCLKSEL_OFFSET, 2), /*!< Attach FRO2 MAX clock to MICFIL0 Functional Clock. */
    kAUDIO_VDD1_to_MICFIL0 =
        CLKCTL3_TUPLE_MUXA(MICFIL0FCLKSEL_OFFSET, 3), /*!< Attach Audio clock to MICFIL0 Functional Clock. */
    kNONE_to_MICFIL0 =
        CLKCTL3_TUPLE_MUXA_NONE(MICFIL0FCLKSEL_OFFSET, 0), /*!< Attach NONE to MICFIL0 Functional Clock. */

    kSENSE_BASE_to_LPI2C15 =
        CLKCTL3_TUPLE_MUXA(LPI2CFCLKSEL_OFFSET, 0), /*!< Attach Sense base clock to LPI2C15 Functional Clock. */
    kFRO1_DIV1_to_LPI2C15 =
        CLKCTL3_TUPLE_MUXA(LPI2CFCLKSEL_OFFSET, 1), /*!< Attach FRO1 max clock to LPI2C15 Functional Clock. */
    kFRO1_DIV2_to_LPI2C15 =
        CLKCTL3_TUPLE_MUXA(LPI2CFCLKSEL_OFFSET, 2), /*!< Attach FRO1 divided-by-2 to LPI2C15 Functional Clock. */
    kFRO2_DIV1_to_LPI2C15 =
        CLKCTL3_TUPLE_MUXA(LPI2CFCLKSEL_OFFSET, 3), /*!< Attach FRO2 max clock to LPI2C15 Functional Clock. */
    kNONE_to_LPI2C15 = CLKCTL3_TUPLE_MUXA_NONE(LPI2CFCLKSEL_OFFSET, 0), /*!< Attach NONE to LPI2C15 Functional Clock. */

    kSENSE_BASE_to_VDD1_CLKOUT =
        CLKCTL3_TUPLE_MUXA(SENSE_CLKOUTCLKSEL_OFFSET, 0), /*!< Attach Sense VDD1 Base Clock to VDD1 CLKOUT Clock. */
    kAUDIO_PLL_PFD3_to_VDD1_CLKOUT =
        CLKCTL3_TUPLE_MUXA(SENSE_CLKOUTCLKSEL_OFFSET, 1), /*!< Attach AUDIO PLL PFD3 Clock to VDD1 CLKOUT Clock. */
    kFRO2_DIV1_to_VDD1_CLKOUT =
        CLKCTL3_TUPLE_MUXA(SENSE_CLKOUTCLKSEL_OFFSET, 2), /*!< Attach FRO2 Max Clock to VDD1 CLKOUT Clock. */
    kFRO1_DIV1_to_VDD1_CLKOUT =
        CLKCTL3_TUPLE_MUXA(SENSE_CLKOUTCLKSEL_OFFSET, 3), /*!< Attach FRO1 Max Clock to VDD1 CLKOUT Clock. */
    kNONE_to_VDD1_CLKOUT =
        CLKCTL3_TUPLE_MUXA_NONE(SENSE_CLKOUTCLKSEL_OFFSET, 0), /*!< Attach NONE to VDD1 CLKOUT Clock. */

    kMEDIA_VDDN_BASE_to_MEDIA_VDDN =
        CLKCTL4_TUPLE_MUXA(MEDIAVDDNCLKSEL_OFFSET, 0), /*!< Attach MEDIA VDDN base clock to MEDIA VDDN clock. */
    kMAIN_PLL_PFD0_to_MEDIA_VDDN =
        CLKCTL4_TUPLE_MUXA(MEDIAVDDNCLKSEL_OFFSET, 1), /*!< Attach MAIN PLL PFD0 to MEDIA VDDN clock. */
    kFRO0_DIV1_to_MEDIA_VDDN =
        CLKCTL4_TUPLE_MUXA(MEDIAVDDNCLKSEL_OFFSET, 2), /*!< Attach FRO0 max to MEDIA VDDN clock. */
    kMAIN_PLL_PFD2_to_MEDIA_VDDN =
        CLKCTL4_TUPLE_MUXA(MEDIAVDDNCLKSEL_OFFSET, 3), /*!< Attach MAIN PLL PFD2 to MEDIA VDDN clock. */

    kMEDIA_VDD2_BASE_to_MEDIA_MAIN =
        CLKCTL4_TUPLE_MUXA(MEDIAMAINCLKSEL_OFFSET, 0), /*!< Attach MEDIA VDD2 base clock to MEDIA MAIN clock. */
    kMAIN_PLL_PFD0_to_MEDIA_MAIN =
        CLKCTL4_TUPLE_MUXA(MEDIAMAINCLKSEL_OFFSET, 1), /*!< Attach Main PLL PFD0 clock to MEDIA MAIN clock. */
    kFRO0_DIV1_to_MEDIA_MAIN = CLKCTL4_TUPLE_MUXA(MEDIAMAINCLKSEL_OFFSET, 2), /*!< Attach FRO0 to MEDIA MAIN clock. */
    kMAIN_PLL_PFD2_to_MEDIA_MAIN =
        CLKCTL4_TUPLE_MUXA(MEDIAMAINCLKSEL_OFFSET, 3), /*!< Attach Main PLL PFD2 clock to MEDIA MAIN clock. */

    kFRO1_DIV3_to_MEDIA_VDDN_BASE =
        CLKCTL4_TUPLE_MUXA(MDNBASECLKSEL_OFFSET, 0), /*!< Attach Fro1 divided-by-3 to Media VDDN Base Clock. */
    kFRO1_DIV1_to_MEDIA_VDDN_BASE =
        CLKCTL4_TUPLE_MUXA(MDNBASECLKSEL_OFFSET, 1), /*!< Attach Fro1 divided-by-1 to Media VDDN Base Clock. */
    kFRO0_DIV3_to_MEDIA_VDDN_BASE =
        CLKCTL4_TUPLE_MUXA(MDNBASECLKSEL_OFFSET, 2), /*!< Attach Fro0 divided-by-3 to Media VDDN Base Clock. */
    kLPOSC_to_MEDIA_VDDN_BASE =
        CLKCTL4_TUPLE_MUXA(MDNBASECLKSEL_OFFSET, 3), /*!< Attach LPOSC clock to Media VDDN Base Clock. */

    kFRO1_DIV3_to_MEDIA_VDD2_BASE =
        CLKCTL4_TUPLE_MUXA(MD2BASECLKSEL_OFFSET, 0), /*!< Attach Fro1 divided-by-3 to Media VDD2 Base Clock. */
    kFRO1_DIV1_to_MEDIA_VDD2_BASE =
        CLKCTL4_TUPLE_MUXA(MD2BASECLKSEL_OFFSET, 1), /*!< Attach Fro1 divided-by-1 to Media VDD2 Base Clock. */
    kFRO0_DIV3_to_MEDIA_VDD2_BASE =
        CLKCTL4_TUPLE_MUXA(MD2BASECLKSEL_OFFSET, 2), /*!< Attach Fro0 divided-by-3 to Media VDD2 Base Clock. */
    kLPOSC_to_MEDIA_VDD2_BASE =
        CLKCTL4_TUPLE_MUXA(MD2BASECLKSEL_OFFSET, 3), /*!< Attach LPOSC clock to Media VDD2 Base Clock. */

    kCOMMON_BASE_to_XSPI2 =
        CLKCTL4_TUPLE_MUXA(XSPI2FCLKSEL_OFFSET, 0), /*!< Attach Common VDDN base clock to XSPI2 Functional Clock. */
    kAUDIO_PLL_PFD1_to_XSPI2 =
        CLKCTL4_TUPLE_MUXA(XSPI2FCLKSEL_OFFSET, 1), /*!< Attach Audio PLL PFD1 clock to XSPI2 Functional Clock. */
    kFRO0_DIV1_to_XSPI2 =
        CLKCTL4_TUPLE_MUXA(XSPI2FCLKSEL_OFFSET, 2), /*!< Attach FRO0 max clock to XSPI2 Functional Clock. */
    kMAIN_PLL_PFD3_to_XSPI2 =
        CLKCTL4_TUPLE_MUXA(XSPI2FCLKSEL_OFFSET, 3), /*!< Attach Main PLL PFD3 clock to XSPI2 Functional Clock. */
    kNONE_to_XSPI2 = CLKCTL4_TUPLE_MUXA_NONE(XSPI2FCLKSEL_OFFSET, 0), /*!< Attach NONE to XSPI2 Functional Clock. */

    k32KHZ_WAKE_to_USB = CLKCTL4_TUPLE_MUXA(USBFCLKSEL_OFFSET, 0),    /*!< Attach Wakeup 32K to USB Functional Clock. */
    kLPOSC_to_USB      = CLKCTL4_TUPLE_MUXA(USBFCLKSEL_OFFSET, 1),    /*!< Attach LPOSC_1M to USB Functional Clock. */
    kUSB_24MHZ_to_USB =
        CLKCTL4_TUPLE_MUXA(USBFCLKSEL_OFFSET, 2), /*!< Attach 24MHz USB OSC clock to USB Functional Clock. */
    kNONE_to_USB = CLKCTL4_TUPLE_MUXA_NONE(USBFCLKSEL_OFFSET, 0),    /*!< Attach NONE to USB Functional Clock. */

    k32KHZ_WAKE_to_EUSB = CLKCTL4_TUPLE_MUXA(EUSBFCLKSEL_OFFSET, 0), /*!< Attach Wakeup 32K to eUSB Functional Clock. */
    kLPOSC_to_EUSB      = CLKCTL4_TUPLE_MUXA(EUSBFCLKSEL_OFFSET, 1), /*!< Attach LPOSC_1M to eUSB Functional Clock. */
    kEUSB_24MHZ_to_EUSB =
        CLKCTL4_TUPLE_MUXA(EUSBFCLKSEL_OFFSET, 2), /*!< Attach 24MHz eUSB OSC clock to eUSB Functional Clock. */
    kNONE_to_EUSB = CLKCTL4_TUPLE_MUXA_NONE(EUSBFCLKSEL_OFFSET, 0), /*!< Attach NONE to eUSB Functional Clock. */

    kMEDIA_VDDN_BASE_to_SDIO0 =
        CLKCTL4_TUPLE_MUXA(SDIO0FCLKSEL_OFFSET, 0), /*!< Attach Media VDDN base clock to SDIO0 Functional Clock. */
    kAUDIO_PLL_PFD0_to_SDIO0 =
        CLKCTL4_TUPLE_MUXA(SDIO0FCLKSEL_OFFSET, 1), /*!< Attach Audio PLL PFD0 clock to SDIO0 Functional Clock. */
    kFRO0_DIV1_to_SDIO0 =
        CLKCTL4_TUPLE_MUXA(SDIO0FCLKSEL_OFFSET, 2), /*!< Attach FRO0 max clock to SDIO0 Functional Clock. */
    kMAIN_PLL_PFD2_to_SDIO0 =
        CLKCTL4_TUPLE_MUXA(SDIO0FCLKSEL_OFFSET, 3), /*!< Attach Main PLL PFD2 clock to SDIO0 Functional Clock. */
    kNONE_to_SDIO0 = CLKCTL4_TUPLE_MUXA_NONE(SDIO0FCLKSEL_OFFSET, 0), /*!< Attach NONE to SDIO0 Functional Clock. */

    kMEDIA_VDDN_BASE_to_SDIO1 =
        CLKCTL4_TUPLE_MUXA(SDIO1FCLKSEL_OFFSET, 0), /*!< Attach Media VDDN base clock to SDIO1 Functional Clock. */
    kAUDIO_PLL_PFD0_to_SDIO1 =
        CLKCTL4_TUPLE_MUXA(SDIO1FCLKSEL_OFFSET, 1), /*!< Attach Audio PLL PFD0 clock to SDIO1 Functional Clock. */
    kFRO0_DIV1_to_SDIO1 =
        CLKCTL4_TUPLE_MUXA(SDIO1FCLKSEL_OFFSET, 2), /*!< Attach FRO0 max clock to SDIO1 Functional Clock. */
    kMAIN_PLL_PFD1_to_SDIO1 =
        CLKCTL4_TUPLE_MUXA(SDIO1FCLKSEL_OFFSET, 3), /*!< Attach Main PLL PFD1 clock to SDIO1 Functional Clock. */
    kNONE_to_SDIO1 = CLKCTL4_TUPLE_MUXA_NONE(SDIO1FCLKSEL_OFFSET, 0), /*!< Attach NONE to SDIO1 Functional Clock. */

    kMEDIA_VDD2_BASE_to_MIPI_DSI_HOST_PHY =
        CLKCTL4_TUPLE_MUXA(DPHYCLKSEL_OFFSET, 0),      /*!< Attach Media VDD2 base clock to MIPI_DSI_Host PHY Clock. */
    kFRO0_DIV1_to_MIPI_DSI_HOST_PHY =
        CLKCTL4_TUPLE_MUXA(DPHYCLKSEL_OFFSET, 2),      /*!< Attach FRO0 max clock to MIPI_DSI_Host PHY Clock. */
    kAUDIO_PLL_PFD2_to_MIPI_DSI_HOST_PHY =
        CLKCTL4_TUPLE_MUXA(DPHYCLKSEL_OFFSET, 3),      /*!< Attach Audio PLL PFD2 clock to MIPI_DSI_Host PHY Clock. */
    kNONE_to_MIPI_DSI_HOST_PHY =
        CLKCTL4_TUPLE_MUXA_NONE(DPHYCLKSEL_OFFSET, 0), /*!< Attach NONE to MIPI_DSI_Host PHY Clock. */

    kMEDIA_VDD2_BASE_to_MIPI_DPHYESC_CLK = CLKCTL4_TUPLE_MUXA(
        DPHYESCCLKSEL_OFFSET, 0), /*!< Attach Media VDD2 base clock to MIPI_DSI_Host DPHY Escape Mode Clock. */
    kMAIN_PLL_PFD1_to_MIPI_DPHYESC_CLK = CLKCTL4_TUPLE_MUXA(
        DPHYESCCLKSEL_OFFSET, 1), /*!< Attach Main PLL PFD1 clock to MIPI_DSI_Host DPHY Escape Mode Clock. */
    kFRO0_DIV1_to_MIPI_DPHYESC_CLK = CLKCTL4_TUPLE_MUXA(
        DPHYESCCLKSEL_OFFSET, 2), /*!< Attach FRO0 max clock to MIPI_DSI_Host DPHY Escape Mode Clock. */
    kAUDIO_PLL_PFD2_to_MIPI_DPHYESC_CLK = CLKCTL4_TUPLE_MUXA(
        DPHYESCCLKSEL_OFFSET, 3), /*!< Attach Audio PLL PFD2 clock to MIPI_DSI_Host DPHY Escape Mode Clock. */
    kNONE_to_MIPI_DPHYESC_CLK =
        CLKCTL4_TUPLE_MUXA_NONE(DPHYESCCLKSEL_OFFSET, 0), /*!< Attach NONE to MIPI_DSI_Host DPHY Escape Mode Clock. */

    kMEDIA_VDD2_BASE_to_VGPU =
        CLKCTL4_TUPLE_MUXA(VGPUCLKSEL_OFFSET, 0), /*!< Attach Media VDD2 base clock to VGPU Clock. */
    kMAIN_PLL_PFD0_to_VGPU = CLKCTL4_TUPLE_MUXA(VGPUCLKSEL_OFFSET, 1), /*!< Attach Main PLL PFD0 clock to VGPU Clock. */
    kFRO0_DIV1_to_VGPU     = CLKCTL4_TUPLE_MUXA(VGPUCLKSEL_OFFSET, 2), /*!< Attach FRO0 max clock to VGPU Clock. */
    kMAIN_PLL_PFD2_to_VGPU = CLKCTL4_TUPLE_MUXA(VGPUCLKSEL_OFFSET, 3), /*!< Attach Main PLL PFD2 clock to VGPU Clock. */
    kNONE_to_VGPU          = CLKCTL4_TUPLE_MUXA_NONE(VGPUCLKSEL_OFFSET, 0), /*!< Attach NONE to VGPU Clock. */

    kMEDIA_VDD2_BASE_to_LPSPI14 =
        CLKCTL4_TUPLE_MUXA(LPSPI14CLKSEL_OFFSET, 0), /*!< Attach Media VDD2 base clock to LPSPI14 Clock. */
    kFRO0_DIV1_to_LPSPI14 = CLKCTL4_TUPLE_MUXA(LPSPI14CLKSEL_OFFSET, 1), /*!< Attach FRO0 max clock to LPSPI14 Clock. */
    kMAIN_PLL_PFD0_to_LPSPI14 =
        CLKCTL4_TUPLE_MUXA(LPSPI14CLKSEL_OFFSET, 2), /*!< Attach Main PLL PFD0 clock to LPSPI14 Clock. */
    kFRO1_DIV1_to_LPSPI14 = CLKCTL4_TUPLE_MUXA(LPSPI14CLKSEL_OFFSET, 3), /*!< Attach FRO1 max clock to LPSPI14 Clock. */
    kNONE_to_LPSPI14      = CLKCTL4_TUPLE_MUXA_NONE(LPSPI14CLKSEL_OFFSET, 0), /*!< Attach NONE to LPSPI14 Clock. */

    kMEDIA_VDD2_BASE_to_LPSPI16 =
        CLKCTL4_TUPLE_MUXA(LPSPI16CLKSEL_OFFSET, 0), /*!< Attach Media VDD2 base clock to LPSPI16 Clock. */
    kFRO0_DIV1_to_LPSPI16 = CLKCTL4_TUPLE_MUXA(LPSPI16CLKSEL_OFFSET, 1), /*!< Attach FRO0 max clock to LPSPI16 Clock. */
    kMAIN_PLL_PFD0_to_LPSPI16 =
        CLKCTL4_TUPLE_MUXA(LPSPI16CLKSEL_OFFSET, 2), /*!< Attach Main PLL PFD0 clock to LPSPI16 Clock. */
    kFRO1_DIV1_to_LPSPI16 = CLKCTL4_TUPLE_MUXA(LPSPI16CLKSEL_OFFSET, 3), /*!< Attach FRO1 max clock to LPSPI16 Clock. */
    kNONE_to_LPSPI16      = CLKCTL4_TUPLE_MUXA_NONE(LPSPI16CLKSEL_OFFSET, 0), /*!< Attach NONE to LPSPI16 Clock. */

    kMEDIA_VDD2_BASE_to_FLEXIO =
        CLKCTL4_TUPLE_MUXA(FLEXIOCLKSEL_OFFSET, 0), /*!< Attach MEDIA VDD2 base clock to FLEXIO. */
    kFRO0_DIV1_to_FLEXIO     = CLKCTL4_TUPLE_MUXA(FLEXIOCLKSEL_OFFSET, 1), /*!< Attach FRO0 max clock to FLEXIO. */
    kFRO1_DIV1_to_FLEXIO     = CLKCTL4_TUPLE_MUXA(FLEXIOCLKSEL_OFFSET, 2), /*!< Attach FRO1 max clock to FLEXIO. */
    kMAIN_PLL_PFD3_to_FLEXIO = CLKCTL4_TUPLE_MUXA(FLEXIOCLKSEL_OFFSET, 3), /*!< Attach Main PLL PFD3 clock to FLEXIO. */
    kNONE_to_FLEXIO          = CLKCTL4_TUPLE_MUXA_NONE(FLEXIOCLKSEL_OFFSET, 0), /*!< Attach NONE to FLEXIO. */

    kMEDIA_VDD2_BASE_to_LCDIF =
        CLKCTL4_TUPLE_MUXA(LCDIFPIXELCLKSEL_OFFSET, 0), /*!< Attach MEDIA VDD2 base clock to LCDIF. */
    kMAIN_PLL_PFD2_to_LCDIF =
        CLKCTL4_TUPLE_MUXA(LCDIFPIXELCLKSEL_OFFSET, 1), /*!< Attach Main PLL PFD0 clock to LCDIF. */
    kFRO0_DIV1_to_LCDIF      = CLKCTL4_TUPLE_MUXA(LCDIFPIXELCLKSEL_OFFSET, 2), /*!< Attach FRO0 max clock to LCDIF. */
    kAUDIO_PLL_PFD1_to_LCDIF = CLKCTL4_TUPLE_MUXA(LCDIFPIXELCLKSEL_OFFSET, 3), /*!< Attach Audio PLL PFD1 to LCDIF. */
    kNONE_to_LCDIF           = CLKCTL4_TUPLE_MUXA_NONE(LCDIFPIXELCLKSEL_OFFSET, 0), /*!< Attach NONE to LCDIF. */
} clock_attach_id_t;

/*! @brief Clock dividers */
typedef enum _clock_div_name
{
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    kCLOCK_DivCmptMainClk   = CLKCTL0_TUPLE_MUXA(CMPTMAINCLKDIV_OFFSET, 0), /*!< VDD2_COMP Main clock Divider. */
    kCLOCK_DivDspClk        = CLKCTL0_TUPLE_MUXA(DSPCPUCLKDIV_OFFSET, 0),   /*!< DSP CPU Clk Divider. */
    kCLOCK_DivComputeRamClk = CLKCTL0_TUPLE_MUXA(RAMCLKDIV_OFFSET, 0),      /*!< RAM Clk Divider. */
    kCLOCK_DivTpiuClk       = CLKCTL0_TUPLE_MUXA(TPIUCLKDIV_OFFSET, 0),     /*!< TIPU Clk Divider. */
    kCLOCK_DivXspi0Clk      = CLKCTL0_TUPLE_MUXA(XSPI0FCLKDIV_OFFSET, 0),   /*!< XSPI0 Clk Divider. */
    kCLOCK_DivXspi1Clk      = CLKCTL0_TUPLE_MUXA(XSPI1FCLKDIV_OFFSET, 0),   /*!< XSPI1 Clk Divider. */
    kCLOCK_DivSctClk        = CLKCTL0_TUPLE_MUXA(SCTFCLKDIV_OFFSET, 0),     /*!< SCT functional Clk Divider. */
    kCLOCK_DivUtick0Clk     = CLKCTL0_TUPLE_MUXA(UTICK0CLKDIV_OFFSET, 0),   /*!< UTICK0 Clk Divider. */
    kCLOCK_DivSystickClk    = CLKCTL0_TUPLE_MUXA(SYSTICKFCLKDIV_OFFSET, 0), /*!< SYSTICK Clk Divider. */
    kCLOCK_DivSai012Clk     = CLKCTL0_TUPLE_MUXA(SAI012CLKDIV_OFFSET, 0),   /*!< SAI0, SAI1 and SAI2 Clk Divider. */
    kCLOCK_DivTrngClk       = CLKCTL0_TUPLE_MUXA(TRNGFCLKDIV_OFFSET, 0),    /*!< TRNG Clk Divider. */
    kCLOCK_DivI3c01PClk     = CLKCTL0_TUPLE_MUXA(I3C01PCLKDIV_OFFSET, 0),   /*!< I3C01 P-Clk Divider. */
    kCLOCK_DivI3c01Clk      = CLKCTL0_TUPLE_MUXA(I3C01FCLKDIV_OFFSET, 0),   /*!< I3C01 functional Clk Divider. */
    kCLOCK_DivClockOut      = CLKCTL0_TUPLE_MUXA(CLKOUTCLKDIV_OFFSET, 0),   /*!< CLKOUT Divider. */
    kCLOCK_DivFcclk0Clk     = CLKCTL0_TUPLE_MUXA(FCCLK0DIV_OFFSET, 0),      /*!< FCCLK0 Clk Divider. */
    kCLOCK_DivFcclk1Clk     = CLKCTL0_TUPLE_MUXA(FCCLK1DIV_OFFSET, 0),      /*!< FCCLK1 Clk Divider. */
    kCLOCK_DivFcclk2Clk     = CLKCTL0_TUPLE_MUXA(FCCLK2DIV_OFFSET, 0),      /*!< FCCLK2 Clk Divider. */
    kCLOCK_DivFcclk3Clk     = CLKCTL0_TUPLE_MUXA(FCCLK3DIV_OFFSET, 0),      /*!< FCCLK3 Clk Divider. */
    kCLOCK_DivCtimer0Clk    = CLKCTL0_TUPLE_MUXA(CTIMER0CLKDIV_OFFSET, 0),  /*!< CTimer0 Clk Divider. */
    kCLOCK_DivCtimer1Clk    = CLKCTL0_TUPLE_MUXA(CTIMER1CLKDIV_OFFSET, 0),  /*!< CTimer1 Clk Divider. */
    kCLOCK_DivCtimer2Clk    = CLKCTL0_TUPLE_MUXA(CTIMER2CLKDIV_OFFSET, 0),  /*!< CTimer2 Clk Divider. */
    kCLOCK_DivCtimer3Clk    = CLKCTL0_TUPLE_MUXA(CTIMER3CLKDIV_OFFSET, 0),  /*!< CTimer3 Clk Divider. */
    kCLOCK_DivCtimer4Clk    = CLKCTL0_TUPLE_MUXA(CTIMER4CLKDIV_OFFSET, 0),  /*!< CTimer4 Clk Divider. */
#else
    kCLOCK_DivLPFlexComm17Clk = CLKCTL1_TUPLE_MUXA(FC17FCLKDIV_OFFSET, 0),       /*!< LP_FLEXCOMM17 Clk Divider. */
    kCLOCK_DivLPFlexComm18Clk = CLKCTL1_TUPLE_MUXA(FC18FCLKDIV_OFFSET, 0),       /*!< LP_FLEXCOMM18 Clk Divider. */
    kCLOCK_DivLPFlexComm19Clk = CLKCTL1_TUPLE_MUXA(FC19FCLKDIV_OFFSET, 0),       /*!< LP_FLEXCOMM19 Clk Divider. */
    kCLOCK_DivLPFlexComm20Clk = CLKCTL1_TUPLE_MUXA(FC20FCLKDIV_OFFSET, 0),       /*!< LP_FLEXCOMM20 Clk Divider. */
    kCLOCK_DivSenseDspClk     = CLKCTL1_TUPLE_MUXA(SENSEDSPCPUCLKDIV_OFFSET, 0), /*!< Sense DSP Clk Divider. */
    kCLOCK_DivSai3Clk         = CLKCTL1_TUPLE_MUXA(SAI3CLKDIV_OFFSET, 0),        /*!< SAI3 FCLK Clk Divider. */
    kCLOCK_DivUtick1Clk       = CLKCTL1_TUPLE_MUXA(UTICK1CLKDIV_OFFSET, 0),      /*!< UTICK1 Functional Clk Divider. */
    kCLOCK_DivSystickClk      = CLKCTL1_TUPLE_MUXA(SYSTICKFCLKDIV_OFFSET, 0),    /*!< SYSTICK Functional Clk Divider. */
    kCLOCK_DivCtimer5Clk      = CLKCTL1_TUPLE_MUXA(CTIMER5CLKDIV_OFFSET, 0),     /*!< CTIMER5 FCLK Clk Divider. */
    kCLOCK_DivCtimer6Clk      = CLKCTL1_TUPLE_MUXA(CTIMER6CLKDIV_OFFSET, 0),     /*!< CTIMER6 FCLK Clk Divider. */
    kCLOCK_DivCtimer7Clk      = CLKCTL1_TUPLE_MUXA(CTIMER7CLKDIV_OFFSET, 0),     /*!< CTIMER7 FCLK Clk Divider. */
    kCLOCK_DivI3c23Clk = CLKCTL1_TUPLE_MUXA(I3C23FCLKDIV_OFFSET, 0), /*!< I3C2 and I3C3 Functional Clk Divider. */
#endif
    kCLOCK_DivCommonVddnClk = CLKCTL2_TUPLE_MUXA(COMMONVDDNCLKDIV_OFFSET, 0),   /*!< Common VDDN Clk Divider. */
    kCLOCK_DivSenseMainClk  = CLKCTL3_TUPLE_MUXA(SENSEMAINCLKDIV_OFFSET, 0),    /*!< VDD1_SENSE Main Clock Divider. */
    kCLOCK_DivSenseRamClk   = CLKCTL3_TUPLE_MUXA(SENSERAMCLKDIV_OFFSET, 0),     /*!< Senese RAM Clk Divider. */
    kCLOCK_DivOstimerClk    = CLKCTL3_TUPLE_MUXA(OSEVENTFCLKDIV_OFFSET, 0),     /*!< OSTIMER Clk Divider. */
    kCLOCK_DivSdadcClk      = CLKCTL3_TUPLE_MUXA(SDADCFCLKDIV_OFFSET, 0),       /*!< SDADC Clk Divider. */
    kCLOCK_DivAdcClk        = CLKCTL3_TUPLE_MUXA(SARADCFCLKDIV_OFFSET, 0),      /*!< SARADC Clk Divider. */
    kCLOCK_Div32KhzWakeClk  = CLKCTL3_TUPLE_MUXA(A32KHZWAKECLKDIV_OFFSET, 0),   /*!< 32KHZ Wakeup Clk Divider. */
    kCLOCK_DivMicfil0Clk    = CLKCTL3_TUPLE_MUXA(MICFIL0FCLKDIV_OFFSET, 0),     /*!< DMIC0 Clk Divider. */
    kCLOCK_DivLpi2c15Clk    = CLKCTL3_TUPLE_MUXA(LPI2CFCLKDIV_OFFSET, 0),       /*!< PMIC LPI2C Clk Divider. */
    kCLOCK_DivVdd1ClockOut  = CLKCTL3_TUPLE_MUXA(SENSE_CLKOUTCLKDIV_OFFSET, 0), /*!< CLKOUT_VDD1 Clk Divider. */

    kCLOCK_DivMediaVddnClk = CLKCTL4_TUPLE_MUXA(MEDIAVDDNCLKDIV_OFFSET, 0),     /*!< Media VDDN Clk Divider. */
    kCLOCK_DivMediaMainClk = CLKCTL4_TUPLE_MUXA(MEDIAMAINCLKDIV_OFFSET, 0),     /*!< Media Main Clk Divider. */
    kCLOCK_DivXspi2Clk     = CLKCTL4_TUPLE_MUXA(XSPI2FCLKDIV_OFFSET, 0),        /*!< XSPI2 Clk Divider. */
    kCLOCK_DivSdio0Clk     = CLKCTL4_TUPLE_MUXA(SDIO0FCLKDIV_OFFSET, 0),        /*!< SDIO0 Clk Divider. */
    kCLOCK_DivSdio1Clk     = CLKCTL4_TUPLE_MUXA(SDIO1FCLKDIV_OFFSET, 0),        /*!< SDIO1 Clk Divider. */
    kCLOCK_DivDphyClk      = CLKCTL4_TUPLE_MUXA(DPHYCLKDIV_OFFSET, 0),          /*!< DPHY Clk Divider. */
    kCLOCK_DivDphyEscRxClk = CLKCTL4_TUPLE_MUXA(DPHYESCRXCLKDIV_OFFSET, 0),     /*!< DphyEscRx Clk Divider. */
    kCLOCK_DivDphyEscTxClk = CLKCTL4_TUPLE_MUXA(DPHYESCTXCLKDIV_OFFSET, 0),     /*!< DphyEscTx Clk Divider. */
    kCLOCK_DivVgpuClk      = CLKCTL4_TUPLE_MUXA(VGPUCLKDIV_OFFSET, 0),          /*!< VGPU Clk Divider. */
    kCLOCK_DivLpspi14Clk   = CLKCTL4_TUPLE_MUXA(LPSPI14CLKDIV_OFFSET, 0),       /*!< LPSPI14 Clk Divider. */
    kCLOCK_DivLpspi16Clk   = CLKCTL4_TUPLE_MUXA(LPSPI16CLKDIV_OFFSET, 0),       /*!< LPSPI16 Clk Divider. */
    kCLOCK_DivFlexioClk    = CLKCTL4_TUPLE_MUXA(FLEXIOCLKDIV_OFFSET, 0),        /*!< FLEXIO Clk Divider. */
    kCLOCK_DivLcdifClk     = CLKCTL4_TUPLE_MUXA(LCDIFPIXELCLKDIV_OFFSET, 0),    /*!< LCDIF Pixel Clk Divider. */
    kCLOCK_DivLowFreqClk   = CLKCTL4_TUPLE_MUXA(LOWFREQCLKDIV_OFFSET, 0),       /*!< Low frequency Clk Divider. */
} clock_div_name_t;

/*! @brief FRO output enable. */
typedef enum _clock_fro_output_en
{
    kCLOCK_FroDiv1OutEn = FRO_CSR_CLKGATE(0x1U),  /*!< Enable Fro Div1 output. */
    kCLOCK_FroDiv2OutEn = FRO_CSR_CLKGATE(0x2U),  /*!< Enable Fro Div2 output. */
    kCLOCK_FroDiv3OutEn = FRO_CSR_CLKGATE(0x4U),  /*!< Enable Fro Div3 output. */
    kCLOCK_FroDiv6OutEn = FRO_CSR_CLKGATE(0x8U),  /*!< Enable Fro Div6 output. */
    kCLOCK_FroDiv8OutEn = FRO_CSR_CLKGATE(0x10U), /*!< Enable Fro Div8 output. */
    kCLOCK_FroAllOutEn  = FRO_CSR_CLKGATE_MASK,   /*!< Enable all Fro output. */
} clock_fro_output_en_t;

/*! @brief FRO Interrupt control. */
enum _clock_fro_interrupt
{
    kCLOCK_FroTrimUpdateReqInt = FRO_CNFG1_TRUPREQ_IE_MASK,  /*!< Trim Update Request Interrupt Enable. */
    kCLOCK_FroTuneErrInt       = FRO_CNFG1_TUNE_ERR_IE_MASK, /*!< Tune Error Interrupt Enable. */
    kCLOCK_FroLossOfLockInt    = FRO_CNFG1_LOL_ERR_IE_MASK,  /*!< Loss-of-Lock Error Interrupt Enable. */
    kCLOCK_FroAllIntterrupt =
        kCLOCK_FroTrimUpdateReqInt | kCLOCK_FroTuneErrInt | kCLOCK_FroLossOfLockInt, /*!< All Interrupt Enable. */
};

/*! @brief FRO flags. */
enum _clock_fro_flag
{
    kCLOCK_FroTuneOnceDone  = FRO_CSR_TUNEONCE_DONE_MASK, /*!< FRO Tune Once Done Flag. */
    kCLOCK_FroTrimLock      = FRO_CSR_TRIM_LOCK_MASK,     /*!< FRO Trim Lock Flag. */
    kCLOCK_FroTrimUpdateReq = FRO_CSR_TRUPREQ_MASK,       /*!< FRO Trim Update Request Flag. */
    kCLOCK_FroTuneErr       = FRO_CSR_TUNE_ERR_MASK,      /*!< FRO Tune Error Flag. */
    kCLOCK_FroLossOfLockErr = FRO_CSR_LOL_ERR_MASK,       /*!< FRO Loss-of-lock Error Flag. */
};

/*! @brief FRO configuration. */
typedef struct _clock_fro_config
{
    uint32_t targetFreq;   /*!< Target frequency. */
    uint16_t refDiv;       /*!< OSC Reference clock divider. 1 for divide ratio 1.*/
    uint16_t trim1DelayUs; /*!< Trim 1 delay in us, minimum is 15us. Used when running in Closed Loop mode and trim
                              values are updated by 1 decimal unit.*/
    uint16_t trim2DelayUs; /*!< Trim 2 delay in us. Used at start of closed loop mode when auto tuner is updating trim
                              values by 16 decimal unit steps */
    uint8_t range; /*!< Trim Expected Count Range. Specifies the + or - counts that the FRO frequency can be off from
                      TEXPCNT to be considerred locked. The value/100 is the % deviation. */
    uint32_t enableInt; /*!< Enable interrupts. Bit mask of #_clock_fro_interrupt. */
    bool coarseTrimEn;  /*!< Coarse Trim Enable. Set to true to allow autotrimming of the FRO high-byte trim bits. */
} clock_fro_config_t;

/*! @brief Clock Control for each power domain. */
typedef enum _clock_domain_enable
{
    kCLOCK_Vdd2CompDomainEnable  = 0x1U,  /*!<  Clock Control of VDD2_COMP Domain. */
    kCLOCK_Vdd1SenseDomainEnable = 0x2U,  /*!< Clock Control of VDD1_SENSE Domain. */
    kCLOCK_Vdd2DspDomainEnable   = 0x4U,  /*!< Clock Control of VDD2_DSP Domain. */
    kCLOCK_Vdd2MediaDomainEnable = 0x8U,  /*!< Clock Control of VDD2_MEDIA Domain. */
    kCLOCK_VddnMediaDomainEnable = 0x10U, /*!< Clock Control of VDDN_MEDIA Domain. */
    kCLOCK_Vdd2ComDomainEnable   = 0x20U, /*!< Clock Control of VDD2_COM Domain. */
    kCLOCK_VddnComDomainEnable   = 0x40U, /*!< Clock Control of VDDN_COM Domain. */
    kCLOCK_AllDomainEnable       = 0x7FU  /*!< Clock Control of all Domain. */
} clock_domain_enable_t;

/*!
 * @brief PLL PFD clock name
 */
typedef enum _clock_pfd
{
    kCLOCK_Pfd0 = 0U, /*!< PLL PFD0 */
    kCLOCK_Pfd1 = 1U, /*!< PLL PFD1 */
    kCLOCK_Pfd2 = 2U, /*!< PLL PFD2 */
    kCLOCK_Pfd3 = 3U, /*!< PLL PFD3 */
} clock_pfd_t;

/*! @brief MainPLL Reference Input Clock Source */
typedef enum _main_pll_src
{
    kCLOCK_MainPllFro1Div8 = 0, /*!< FRO1_DIV8 clock */
    kCLOCK_MainPllOscClk   = 1, /*!< OSC clock */
} main_pll_src_t;

/*! @brief MainPLL Multiplication Factor */
typedef enum _main_pll_mult
{
    kCLOCK_MainPllMult16 = 16U, /*!< Divide by 16 */
    kCLOCK_MainPllMult17 = 17U, /*!< Divide by 17 */
    kCLOCK_MainPllMult18 = 18U, /*!< Divide by 18 */
    kCLOCK_MainPllMult19 = 19U, /*!< Divide by 19 */
    kCLOCK_MainPllMult20 = 20U, /*!< Divide by 20 */
    kCLOCK_MainPllMult21 = 21U, /*!< Divide by 21 */
    kCLOCK_MainPllMult22 = 22U, /*!< Divide by 22 */
} main_pll_mult_t;

/*! @brief PLL configuration for MAINPLL */
typedef struct _clock_main_pll_config
{
    main_pll_src_t main_pll_src;   /*!< Reference Input Clock Source. */
    uint32_t numerator;            /*!< 30 bit numerator of fractional loop divider. */
    uint32_t denominator;          /*!< 30 bit numerator of fractional loop divider. */
    main_pll_mult_t main_pll_mult; /*!< Multiplication Factor. */
} clock_main_pll_config_t;

/*! @brief AudioPll Reference Input Clock Source */
typedef enum _audio_pll_src
{
    kCLOCK_AudioPllFro1Div8 = 0, /*!< FRO1_DIV8 clock */
    kCLOCK_AudioPllOscClk   = 1, /*!< OSC clock */
} audio_pll_src_t;

/*! @brief AudioPll Multiplication Factor */
typedef enum _audio_pll_mult
{
    kCLOCK_AudioPllMult16 = 16U, /*!< Divide by 16 */
    kCLOCK_AudioPllMult17 = 17U, /*!< Divide by 17 */
    kCLOCK_AudioPllMult18 = 18U, /*!< Divide by 18 */
    kCLOCK_AudioPllMult19 = 19U, /*!< Divide by 19 */
    kCLOCK_AudioPllMult20 = 20U, /*!< Divide by 20 */
    kCLOCK_AudioPllMult21 = 21U, /*!< Divide by 21 */
    kCLOCK_AudioPllMult22 = 22U, /*!< Divide by 22 */
} audio_pll_mult_t;

/*! @brief PLL configuration for Audio PLL */
typedef struct _clock_audio_pll_config
{
    audio_pll_src_t audio_pll_src;   /*!< Reference Input Clock Source. */
    uint32_t numerator;              /*!< 30 bit numerator of fractional loop divider. */
    uint32_t denominator;            /*!< 30 bit numerator of fractional loop divider. */
    audio_pll_mult_t audio_pll_mult; /*!< Multiplication Factor. */
    bool enableVcoOut;               /*!< Enable VCO output */
} clock_audio_pll_config_t;

/*! @brief Capacitor Trim Value for OSC32KNP */
typedef enum _osc32k_cap_trim
{
    kCLOCK_Osc32kCapPf0 = 0U, /*!< Capacitor Trim Value 0pF. */
    kCLOCK_Osc32kCapPf2,      /*!< Capacitor Trim Value 2pF. */
    kCLOCK_Osc32kCapPf4,      /*!< Capacitor Trim Value 4pF. */
    kCLOCK_Osc32kCapPf6,      /*!< Capacitor Trim Value 6pF. */
    kCLOCK_Osc32kCapPf8,      /*!< Capacitor Trim Value 8pF. */
    kCLOCK_Osc32kCapPf10,     /*!< Capacitor Trim Value 10pF. */
    kCLOCK_Osc32kCapPf12,     /*!< Capacitor Trim Value 12pF. */
    kCLOCK_Osc32kCapPf14,     /*!< Capacitor Trim Value 14pF. */
    kCLOCK_Osc32kCapPf16,     /*!< Capacitor Trim Value 16pF. */
    kCLOCK_Osc32kCapPf18,     /*!< Capacitor Trim Value 18pF. */
    kCLOCK_Osc32kCapPf20,     /*!< Capacitor Trim Value 20pF. */
    kCLOCK_Osc32kCapPf22,     /*!< Capacitor Trim Value 22pF. */
    kCLOCK_Osc32kCapPf24,     /*!< Capacitor Trim Value 24pF. */
    kCLOCK_Osc32kCapPf26,     /*!< Capacitor Trim Value 26pF. */
    kCLOCK_Osc32kCapPf28,     /*!< Capacitor Trim Value 28pF. */
    kCLOCK_Osc32kCapPf30,     /*!< Capacitor Trim Value 30pF. */
} osc32k_cap_trim_t;

/*! @brief configuration for 32K OSC */
typedef struct _clock_osc32k_config_t
{
    bool bypass;        /*!< Bypass enable. */
    bool monitorEnable; /*!< Clock Monitor Enable. */
    bool lowPowerMode; /*!< Low-Power (Nano-Power) mode enable. NOTE, can only change from High-Power mode to Nano-Power
                          mode, and not vice versa. */
    osc32k_cap_trim_t cap; /*!< Capacitor Trim Value. */
} clock_osc32k_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Enable the clock for specific IP.
 * @param clk : Clock to be enabled.
 * @return  Nothing
 */
void CLOCK_EnableClock(clock_ip_name_t clk);

/**
 * @brief Disable the clock for specific IP.
 * @param clk : Clock to be disabled.
 * @return  Nothing
 */
void CLOCK_DisableClock(clock_ip_name_t clk);

/**
 * brief   Configure the clock selection muxes.
 *
 * For some of the muxes, there's SEL_EN bit to gate the mux ouput to reduce power, using kNONT_to_XXX to gate the mux
 * oupput. used by any peripheral.
 * @param   connection  : Clock to be configured.
 * @return  Nothing
 */
void CLOCK_AttachClk(clock_attach_id_t connection);

/**
 * @brief   Setup peripheral clock dividers.
 * @param   div_name    : Clock divider name
 * @param   divider     : Value to be divided. Divided clock frequency =
 * Undivided clock frequency / divider.
 * @return  Nothing
 */
void CLOCK_SetClkDiv(clock_div_name_t div_name, uint32_t divider);

/*! @brief  Return Frequency of selected clock
 *  @return Frequency of selected clock
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName);

#if defined(FSL_CLOCK_DRIVER_COMPUTE) /* Compute domain specific APIs */

/*! @brief  Return clock frequency of LP_FLEXCOMM 0 to 13 Clock Source FCCLK
 *  @param  id : index of FCCLK
 *  @return Frequency of FCCLK
 */
uint32_t CLOCK_GetFCClkFreq(uint32_t id);

/*! @brief  Return Frequency of compute main clk
 *  @return Frequency of main clk
 */
uint32_t CLOCK_GetComputeMainClkFreq(void);

/*! @brief  Return Frequency of compute audio clk
 *  @return Frequency of audio_clk_cmpt
 */
uint32_t CLOCK_GetComputeAudioClkFreq(void);

/*! @brief  Return Frequency of Compute DSP clk
 *  @return Frequency of DSP clk
 */
uint32_t CLOCK_GetHifi4ClkFreq(void);

/*! @brief  Return Frequency of Compute Base clock
 *  @return Frequency of compute base clk
 */
uint32_t CLOCK_GetComputeBaseClkFreq(void);

/*! @brief  Return Frequency of Compute DSP Base clock
 *  @return Frequency of compute dsp base clk
 */
uint32_t CLOCK_GetComputeDspBaseClkFreq(void);

/*! @brief  Return Frequency of VDD2_COM Base Clock
 *  @return Frequency of baseclk_com2
 */
uint32_t CLOCK_GetVdd2ComBaseClkFreq(void);

/*! @brief  Enable/Disable FRO0 clock for various domains.
 *  @param  domainEnable : Or'ed value of #clock_domain_enable_t to enable
 * DRFO0 max clock for certain domain.
 */
void CLOCK_EnableFro0ClkForDomain(uint32_t domainEnable);

/*! @brief  Return Frequency of sct
 *  @return Frequency of sct clk
 */
uint32_t CLOCK_GetSctClkFreq(void);

/*! @brief Set the Sense AUDIO clock frequency based on the setting from Sense Domain.
 *
 * This API is used to tell the driver of compute domain about the clcok frequency of sense base clock.
 * @param freq : The sense base clock frequency in Hz.
 */
static inline void CLOCK_SetSenseAudioClkFreq(uint32_t freq)
{
    g_senseAudioClkFreq = freq;
}

/*! @brief  Return Frequency of VDD1 audio clk.
 * NOTE, when called from Compute Domain, need to use CLOCK_SetSenseAudioClkFreq to tell the clock driver the audio_clk
 * frequency before the API is called.
 *  @return Frequency of audio_clk
 */
uint32_t CLOCK_GetSenseAudioClkFreq(void);

/*! @brief  Return Frequency of TPIU clk
 *  @return Frequency of SAI clk
 */
uint32_t CLOCK_GetTpiuClkFreq(void);

/*! @brief  Return Frequency of TRNG clk
 *  @return Frequency of SAI clk
 */
uint32_t CLOCK_GetTrngClkFreq(void);

#else  /* Sense domain specific APIs */

/*! @brief  Return Frequency of VDD1 audio clk
 *  @return Frequency of audio_clk
 */
uint32_t CLOCK_GetSenseAudioClkFreq(void);

/*! @brief  Return Frequency of Sense DSP clk
 *  @return Frequency of Sense DSP clk
 */
uint32_t CLOCK_GetHifi1ClkFreq(void);

#endif /* FSL_CLOCK_DRIVER_COMPUTE */

/*! @brief  Enable/Disable FRO clock output.
 *  @param  base : base address of FRO.
 *  @param  divOutEnable : Or'ed value of #clock_fro_output_en_t to enable certain clock freq output.
 */
void CLOCK_EnableFroClkOutput(FRO_Type *base, uint32_t divOutEnable);

/*! @brief  Configure FRO trim values when FRO is configured in Open loop mode.
 *  @param  base : base address of FRO.
 *  @param  trimVal : 12bits trim value.
 */
void CLOCK_ConfigFroTrim(FRO_Type *base, uint16_t trimVal);

/*! @brief  Disable the FRO clock. This API will disable the FRO clock output and power off FRO.
 *  @param  base : base address of FRO.
 */
void CLOCK_DisableFro(FRO_Type *base);

/*! @brief  Enable/Disable FRO for close loop mode(autotuner).
 *  @param  base : base address of FRO.
 *  @param  config : The configuration for FRO.
 *  @param  enable: Enable auto tuning mode or not.
 *  @retval kStatus_Success successfully tuned to the target configuration.
 *  @retval kStatus_InvalidArgument Invalid arguement.
 *  @retval kStatus_Fail failed to lock to the target frequency.
 */
status_t CLOCK_EnableFroAutoTuning(FRO_Type *base, const clock_fro_config_t *config, bool enable);

/*! @brief  Enable FRO clock output with specified frequency.
 *  @param  base : base address of FRO.
 *  @param  targetFreq target fro frequency.
 *  @param  divOutEnable Or'ed value of #clock_fro_output_en_t to enable certain clock freq output.
 */
void CLOCK_EnableFroClkFreq(FRO_Type *base, uint32_t targetFreq, uint32_t divOutEnable);

/*! @brief  Enable FRO clock output with target frequency using FRO close loop mode.
 * For example, to enable FRO2 to ouput 200MHZ:
 * @code
 *     const clock_fro_config_t config = {
 *      .targetFreq = 200000000U,
 *      .range = 50U,
 *      .trim1DelayUs = 15U,
 *      .trim2DelayUs = 150U,
 *      .refDiv = 0U,
 *      .enableInt = 0U,
 *      .coarseTrimEn = true,
 *  };
 *  CLOCK_EnableFroClkFreqCloseLoop(FRO2, &config, kCLOCK_FroAllOutEn);
 * @endcode
 *  @param  base : base address of FRO.
 *  @param  config : The configuration for FRO.
 *  @param  divOutEnable : Or'ed value of clock_fro_output_en_t to enable certain clock freq output.
 *  @retval kStatus_Success successfully tuned to the target configuration.
 *  @retval kStatus_InvalidArgument Invalid arguement.
 *  @retval kStatus_Fail failed to lock to the target frequency.
 */
status_t CLOCK_EnableFroClkFreqCloseLoop(FRO_Type *base, const clock_fro_config_t *config, uint32_t divOutEnable);

/*! @brief  Get FRO flags.
 *  @param  base : base address of FRO.
 *  @param  flags Or'ed value of #_clock_fro_flag.
 */
uint32_t CLOCK_GetFroFlags(FRO_Type *base);

/*! @brief  Clear FRO flags.
 *  @param  base : base address of FRO.
 *  @param  flags Or'ed value of #_clock_fro_flag to clear.
 */
inline static void CLOCK_ClearFroFlags(FRO_Type *base, uint32_t flags)
{
    base->CSR.CLR = flags;
}

/*! @brief  Return Frequency of FRO clk
 *  @param id FRO index
 *  @return Frequency of FRO clk
 */
uint32_t CLOCK_GetFroClkFreq(uint32_t id);

/*! @brief  Return Frequency of sense main clk
 *  @return Frequency of main clk
 */
uint32_t CLOCK_GetSenseMainClkFreq(void);

/*! @brief  Return Frequency of MAINPLL
 *  @return Frequency of MAINPLL
 */
uint32_t CLOCK_GetMainPllFreq(void);

/*! @brief  Get current output frequency of specific Main PLL PFD.
 *  @param   pfd    : pfd name to get frequency.
 *  @return  Frequency of MainPLL PFD.
 */
uint32_t CLOCK_GetMainPfdFreq(clock_pfd_t pfd);

/*! @brief  Return Frequency of AUDIO PLL
 *  @return Frequency of AUDIO PLL
 */
uint32_t CLOCK_GetAudioPllFreq(void);

/*! @brief  Get current output frequency of specific Audio PLL PFD.
 *  @param   pfd    : pfd name to get frequency.
 *  @return  Frequency of AUDIO PLL PFD.
 */

uint32_t CLOCK_GetAudioPfdFreq(clock_pfd_t pfd);
/*! @brief  Return Frequency of High-Freq output of FRO
 *  @return Frequency of High-Freq output of FRO
 */

/*! @brief  Return Frequency of sys osc Clock
 *  @return Frequency of sys osc Clock. Or CLK_IN pin frequency.
 */
static inline uint32_t CLOCK_GetXtalInClkFreq(void)
{
    return ((g_xtalFreq != 0U) ? g_xtalFreq : g_clkinFreq);
}

/*! @brief  Return Frequency of Sense Base clock
 *  @return Frequency of sense base clk
 */
uint32_t CLOCK_GetSenseBaseClkFreq(void);

/*! @brief  Enable/Disable sys osc clock from external crystal clock.
 *  @param  enable : true to enable system osc clock, false to bypass system
 * osc.
 *  @param  enableLowPower : true to enable low power mode, false to enable high
 * gain mode.
 *  @param  delay_us : Delay time after OSC power up.
 */
void CLOCK_EnableSysOscClk(bool enable, bool enableLowPower, uint32_t delay_us);

/*! @brief  Return Frequency of VDDN_COM Base Clock
 *  @return Frequency of baseclk_comn
 */
uint32_t CLOCK_GetVddnComBaseClkFreq(void);

/*! @brief  Return Frequency of VDDN_MEDIA Base Clock
 *  @return Frequency of baseclk_mdn
 */
uint32_t CLOCK_GetVddnMediaBaseClkFreq(void);

/*! @brief  Return Frequency of VDD2_MEDIA Base Clock
 *  @return Frequency of baseclk_md2
 */
uint32_t CLOCK_GetVdd2MediaBaseClkFreq(void);

/*! @brief  Return Frequency of MEDIA_MAIN Clock
 *  @return Frequency of media_main_clk
 */
uint32_t CLOCK_GetMediaMainClkFreq(void);

/*! @brief  Return Frequency of MEDIA_VDDN Clock
 *  @return Frequency of media_vddn_clk
 */
uint32_t CLOCK_GetMediaVddnClkFreq(void);

/*! @brief  Enable/Disable FRO2 clock for various domains.
 *  @param  domainEnable : Or'ed value of #clock_domain_enable_t to enable
 * DRFO2 max clock for certain domain.
 */
void CLOCK_EnableFro2ClkForDomain(uint32_t domainEnable);

/*! @brief  Enable/Disable MainPLL PFD clock for various domains.
 *
 * Enables PFD clock of MainPLL for various domains. Each PFD clock of MainPLL can be sent to various domain. To reduce
 * power consumption, turn off the PFD in the domain when this PFD is not configured.
 *  @param pfd  : Which PFD clock to control.
 *  @param  domainEnable : Or'ed value of #clock_domain_enable_t to enable
 * clock for certain domain.
 */
void CLOCK_EnableMainPllPfdClkForDomain(clock_pfd_t pfd, uint32_t domainEnable);

/*! @brief  Enable/Disable AUDIO PFD clock for various domains.
 *
 * Enables PFD clock of AUDIO for various domains. Each PFD clock of AUDIO can be sent to various domain. To reduce
 * power consumption, turn off the PFD in the domain when this PFD is not configured.
 *  @param pfd  : Which PFD clock to control.
 *  @param  domainEnable : Or'ed value of #clock_domain_enable_t to enable
 * clock for certain domain.
 */
void CLOCK_EnableAudioPllPfdClkForDomain(clock_pfd_t pfd, uint32_t domainEnable);

/*! @brief  Enable/Disable AUDIO VCO clock for various domains.
 *
 * VCO clock of Audio PLL can be sent to various domains to reduce power consumption when VCO is not set to use in such
 * domain. This VCO can be disabled for such domain.
 *  @param  domainEnable : Or'ed value of #clock_domain_enable_t to enable
 * clock for certain domain.
 */
void CLOCK_EnableAudioPllVcoClkForDomain(uint32_t domainEnable);

/*! @brief  Initialize the Main PLL.
 *  @param  config    : Configuration to set to PLL.
 */
void CLOCK_InitMainPll(const clock_main_pll_config_t *config);

/*! brief  Deinit the Main PLL.
 *  param  none.
 */
static inline void CLOCK_DeinitMainPll(void)
{
    /* Set Main PLL Reset & HOLDRING_OFF_ENA */
    CLKCTL2->MAINPLL0CTL0 |= CLKCTL2_MAINPLL0CTL0_HOLD_RING_OFF_ENA_MASK | CLKCTL2_MAINPLL0CTL0_RESET_MASK;
    /* Power down Main PLL*/
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    SLEEPCON0->RUNCFG_SET = SLEEPCON0_RUNCFG_PLLLDO_PD_MASK | SLEEPCON0_RUNCFG_PLLANA_PD_MASK;
#else
    SLEEPCON1->RUNCFG_SET = SLEEPCON1_RUNCFG_PLLLDO_PD_MASK | SLEEPCON1_RUNCFG_PLLANA_PD_MASK;
#endif
}
/*! @brief Initialize the Main PLL PFD.
 *  @param pfd    : Which PFD clock to enable.
 *  @param divider    : The PFD divider value.
 *  @note It is recommended that PFD settings are kept between 12-35.
 */
void CLOCK_InitMainPfd(clock_pfd_t pfd, uint8_t divider);

/*! brief Disable the Main PLL PFD.
 *  param pfd    : Which PFD clock to disable.
 */
static inline void CLOCK_DeinitMainPfd(clock_pfd_t pfd)
{
    CLKCTL2->MAINPLL0PFD |= ((uint32_t)CLKCTL2_AUDIOPLL0PFD_PFD0_CLKGATE_MASK << (8UL * (uint32_t)pfd));
}

/*! @brief  Initialize the audio PLL.
 *  @param  config    : Configuration to set to PLL.
 */
void CLOCK_InitAudioPll(const clock_audio_pll_config_t *config);

/*! brief  Deinit the Audio PLL.
 *  param  none.
 */
static inline void CLOCK_DeinitAudioPll(void)
{
    /* Set Audio PLL Reset & HOLDRINGOFF_ENA */
    CLKCTL2->AUDIOPLL0CTL0 |= CLKCTL2_AUDIOPLL0CTL0_HOLD_RING_OFF_ENA_MASK | CLKCTL2_AUDIOPLL0CTL0_RESET_MASK;
    /* Power down Audio PLL */
#if defined(FSL_CLOCK_DRIVER_COMPUTE)
    /* Power down Audio PLL before change fractional settings */
    SLEEPCON0->RUNCFG_SET = SLEEPCON0_RUNCFG_AUDPLLLDO_PD_MASK | SLEEPCON0_RUNCFG_AUDPLLANA_PD_MASK;
#else
    SLEEPCON1->RUNCFG_SET = SLEEPCON1_RUNCFG_AUDPLLLDO_PD_MASK | SLEEPCON1_RUNCFG_AUDPLLANA_PD_MASK;
#endif
}

/*! @brief Initialize the audio PLL PFD.
 *  @param pfd    : Which PFD clock to enable.
 *  @param divider    : The PFD divider value.
 *  @note It is recommended that PFD settings are kept between 12-35.
 */
void CLOCK_InitAudioPfd(clock_pfd_t pfd, uint8_t divider);
/*! brief Disable the audio PLL PFD.
 *  param pfd    : Which PFD clock to disable.
 */
static inline void CLOCK_DeinitAudioPfd(uint32_t pfd)
{
    CLKCTL2->AUDIOPLL0PFD |= ((uint32_t)CLKCTL2_AUDIOPLL0PFD_PFD0_CLKGATE_MASK << (8UL * (uint32_t)pfd));
}

/*! @brief  Return Frequency of Lower power osc
 *  @return Frequency of LPOSC
 */
static inline uint32_t CLOCK_GetLpOscFreq(void)
{
    return CLK_LPOSC_1MHZ;
}

/*! @brief  Return Frequency of sys osc Clock
 *  @return Frequency of sys osc Clock. Or CLK_IN pin frequency.
 */
static inline uint32_t CLOCK_GetSysOscFreq(void)
{
    return (CLKCTL2->SYSOSCBYPASS == 0U) ? g_xtalFreq : ((CLKCTL2->SYSOSCBYPASS == 1U) ? g_clkinFreq : 0U);
}

/*! @brief  Return Frequency of MCLK Input Clock
 *  @return Frequency of MCLK input Clock.
 */
static inline uint32_t CLOCK_GetMclkInClkFreq(void)
{
    return g_mclkFreq;
}

/*! @brief  Return Frequency of 32kHz osc
 *  @return Frequency of 32kHz osc
 */
uint32_t CLOCK_GetOsc32KFreq(void);

/*! @brief  Enables OSC32KNP
 *  @param  config : configuration set to OSC32KNP
 */
void CLOCK_EnableOsc32K(clock_osc32k_config_t *config);

/*! @brief  Disable OSC32KNP
 */
static inline void CLOCK_DisableOsc32K(void)
{
    OSC32KNP->CTRL |= OSC32KNP_CTRL_OSC_DIS_MASK;
}

/*! @brief  Return Frequency of 32khz wake clk
 *  @return Frequency of 32kHz wake clk
 */
uint32_t CLOCK_GetWakeClk32KFreq(void);

/*!
 * @brief Set the XTALIN (system OSC) frequency based on board setting.
 * NOTE, when SOSC is used, either CLOCK_SetXtalFreq or CLOCK_SetClkinFreq(But NOT both.) should be called to tell
 * driver the clock frequency connected to SOSC module.
 *
 * @param freq : The XTAL input clock frequency in Hz.
 */
static inline void CLOCK_SetXtalFreq(uint32_t freq)
{
    g_xtalFreq  = freq;
    g_clkinFreq = 0U;
}

/*!
 * @brief Set the CLKIN (CLKIN pin) frequency based on board setting.
 *
 * @param freq : The CLK_IN pin input clock frequency in Hz.
 */
static inline void CLOCK_SetClkinFreq(uint32_t freq)
{
    g_clkinFreq = freq;
    g_xtalFreq  = 0U;
}

/*!
 * @brief Set the 32KHz external input frequency based on board setting.
 *
 * @param freq : The 32KHz external pin input clock frequency in Hz.
 */
static inline void CLOCK_Set32kClkinFreq(uint32_t freq)
{
    g_32kClkinFreq = freq;
}

/*!
 * @brief Set the MCLK IN frequency based on board setting.
 *
 * @param freq : The MCLK input clock frequency in Hz.
 */
static inline void CLOCK_SetMclkFreq(uint32_t freq)
{
    g_mclkFreq = freq;
}

/*! @brief  Return Frequency of Core/system clock
 *  @return Frequency of core or system Clock
 */
static inline uint32_t CLOCK_GetCoreSysClkFreq(void)
{
    return CLOCK_GetFreq(kCLOCK_CoreSysClk);
}

/*! @brief  Return Frequency of XSPI function clock
 *  @param  id : XSPI index to get frequency.
 *  @return Frequency of XSPI functional Clock
 */
uint32_t CLOCK_GetXspiClkFreq(uint32_t id);

/*! @brief  Return Frequency of UTICK function clock
 *  @return Frequency of UTICK functional Clock
 */
uint32_t CLOCK_GetUtickClkFreq(void);

/*! @brief  Return Frequency of systick clk
 *  @return Frequency of systick clk
 */
uint32_t CLOCK_GetSystickClkFreq(void);

/*! @brief  Return Frequency of WDT clk
 *  @param  id : WDT index to get frequency.
 *  @return Frequency of WDT clk
 */
uint32_t CLOCK_GetWdtClkFreq(uint32_t id);

/*! @brief  Return Frequency of ACMP clk
 *  @return Frequency of ACMP clk
 */
uint32_t CLOCK_GetAcmpClkFreq(void);

/*! @brief  Return Frequency of SAI clk
 *  @return Frequency of SAI clk
 */
uint32_t CLOCK_GetSaiClkFreq(void);

/*! @brief  Return Frequency of USB clk
 *  @return Frequency of USB clk
 */
uint32_t CLOCK_GetUsbClkFreq(void);

/*! @brief  Return Frequency of I3C clk
 *  @return Frequency of I3C clk
 */
uint32_t CLOCK_GetI3cClkFreq(void);

/*! @brief  Return Frequency of Flexcomm functional Clock
 *  @param  id : flexcomm index to get frequency.
 *  @return Frequency of Flexcomm functional Clock
 */
uint32_t CLOCK_GetLPFlexCommClkFreq(uint32_t id);

/*! @brief  Return Frequency of LPI2C functional Clock
 *  @param  id : LPI2C index to get frequency.
 *  @return Frequency of LPI2C functional Clock
 */
uint32_t CLOCK_GetLPI2cClkFreq(uint32_t id);

/*! @brief  Return Frequency of LPSPI functional Clock
 *  @param  id : LPSPI index to get frequency.
 *  @return Frequency of LPSPI functional Clock
 */
uint32_t CLOCK_GetLPSpiClkFreq(uint32_t id);

/*! @brief  Return Frequency of Flexio functional Clock
 *  @return Frequency of Flexcomm functional Clock
 */
uint32_t CLOCK_GetFlexioClkFreq(void);

/*! @brief  Return Frequency of OSTIMER functional Clock
 *  @return Frequency of OSTIMER functional Clock
 */
uint32_t CLOCK_GetOSTimerClkFreq(void);

/*! @brief  Return Frequency of MICFIL functional Clock
 *  @return Frequency of MICFIL functional Clock
 */
uint32_t CLOCK_GetMicfilClkFreq(void);

/*! @brief  Return Frequency of Ctimer Clock
 *  @param  id : ctimer index to get frequency.
 *  @return Frequency of Ctimer Clock
 */
uint32_t CLOCK_GetCTimerClkFreq(uint32_t id);

/*! @brief  Return Frequency of VDD2 ClockOut
 *  @return Frequency of ClockOut
 */
uint32_t CLOCK_GetClockOutClkFreq(void);

/*! @brief  Return Frequency of VDD1 Clock Out
 *  @return Frequency of ClockOut of sense domain
 */
uint32_t CLOCK_GetVdd1ClockOutClkFreq(void);

/*! @brief  Return Frequency of Adc Clock
 *  @return Frequency of Adc Clock.
 */
uint32_t CLOCK_GetAdcClkFreq(void);

/*! @brief  Return Frequency of SDADC Clock
 *  @return Frequency of SDADC Clock.
 */
uint32_t CLOCK_GetSdAdcClkFreq(void);

/*! @brief  Return Frequency of VGPU functional Clock
 *  @return Frequency of VGPU functional Clock
 */
uint32_t CLOCK_GetVgpuClkFreq(void);

/*! @brief  Return Frequency of LCDIF pixel Clock
 *  @return Frequency of LCDIF pixel Clock
 */
uint32_t CLOCK_GetLcdifClkFreq(void);

/*! @brief  Return Frequency of MIPI DPHY functional Clock
 *  @return Frequency of MIPI DPHY functional Clock
 */
uint32_t CLOCK_GetMipiDphyClkFreq(void);

/*! @brief  Return Frequency of MIPI DPHY Esc RX functional Clock
 *  @return Frequency of MIPI DPHY Esc RX functional Clock
 */
uint32_t CLOCK_GetMipiDphyEscRxClkFreq(void);

/*! @brief  Return Frequency of MIPI DPHY Esc Tx functional Clock
 *  @return Frequency of MIPI DPHY Esc Tx functional Clock
 */
uint32_t CLOCK_GetMipiDphyEscTxClkFreq(void);

/*! @brief  Return Frequency of USDHC Clock
 *  @param  id : uSDHC index to get frequency.
 *  @return Frequency of USDHC Clock
 */
uint32_t CLOCK_GetUsdhcClkFreq(uint32_t id);

/*! brief Enable USB HS PHY PLL clock.
 *
 * This function enables the internal 480MHz USB PHY PLL clock.
 *
 * param src  USB HS PHY PLL clock source.
 * param freq The frequency specified by src.
 * retval true The clock is set successfully.
 * retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs0PhyPllClock(clock_usb_phy_src_t src, uint32_t freq);

/*! brief Enable USB HS clock.
 *
 * This function only enables the access to USB HS prepheral, upper layer
 * should first call the ref CLOCK_EnableUsbhs0PhyPllClock to enable the PHY
 * clock to use USB HS.
 *
 * param src  USB HS does not care about the clock source, here must be ref kCLOCK_UsbSrcUnused.
 * param freq USB HS does not care about the clock source, so this parameter is ignored.
 * retval true The clock is set successfully.
 * retval false The clock source is invalid to get proper USB HS clock.
 */
bool CLOCK_EnableUsbhs0Clock(clock_usb_src_t src, uint32_t freq);

/*! brief Disable USB HS PHY PLL clock.
 *
 * This function disables USB HS PHY PLL clock.
 */
void CLOCK_DisableUsbhs0PhyPllClock(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* FSL_CLOCK_H_ */
