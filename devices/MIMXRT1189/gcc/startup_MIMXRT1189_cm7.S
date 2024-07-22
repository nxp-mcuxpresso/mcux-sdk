/* ------------------------------------------------------------------------- */
/*  @file:    startup_MIMXRT1189_cm7.s                                       */
/*  @purpose: CMSIS Cortex-M7 Core Device Startup File                       */
/*            MIMXRT1189_cm7                                                 */
/*  @version: 0.1                                                            */
/*  @date:    2021-3-9                                                       */
/*  @build:   b231213                                                        */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright 1997-2016 Freescale Semiconductor, Inc.                         */
/* Copyright 2016-2023 NXP                                                   */
/* SPDX-License-Identifier: BSD-3-Clause                                     */
/*****************************************************************************/
/* Version: GCC for ARM Embedded Processors                                  */
/*****************************************************************************/
    .syntax unified
    .arch armv7-m

    .section .isr_vector, "a"
    .align 2
    .globl __isr_vector
__isr_vector:
    .long   __StackTop                                      /* Top of Stack */
    .long   Reset_Handler                                   /* Reset Handler */
    .long   NMI_Handler                                     /* NMI Handler*/
    .long   HardFault_Handler                               /* Hard Fault Handler*/
    .long   MemManage_Handler                               /* MPU Fault Handler*/
    .long   BusFault_Handler                                /* Bus Fault Handler*/
    .long   UsageFault_Handler                              /* Usage Fault Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   SVC_Handler                                     /* SVCall Handler*/
    .long   DebugMon_Handler                                /* Debug Monitor Handler*/
    .long   0                                               /* Reserved*/
    .long   PendSV_Handler                                  /* PendSV Handler*/
    .long   SysTick_Handler                                 /* SysTick Handler*/

                                                            /* External Interrupts*/
    .long   TMR1_IRQHandler                                 /* TMR1 interrupt*/
    .long   DAP_IRQHandler                                  /* DAP interrupt*/
    .long   M7_CTI_TRIGGER_OUTPUT_IRQHandler                /* CTI trigger outputs from CM7*/
    .long   M33_CTI_TRIGGER_OUTPUT_IRQHandler               /* CTI trigger outputs from CM33*/
    .long   TMR5_IRQHandler                                 /* TMR5 interrupt*/
    .long   TMR6_IRQHandler                                 /* TMR6 interrupt*/
    .long   TMR7_IRQHandler                                 /* TMR7 interrupt*/
    .long   TMR8_IRQHandler                                 /* TMR8 interrupt*/
    .long   CAN1_IRQHandler                                 /* CAN1 interrupt*/
    .long   CAN1_ERROR_IRQHandler                           /* CAN1 error interrupt*/
    .long   GPIO1_0_IRQHandler                              /* GPIO1 interrupt 0*/
    .long   GPIO1_1_IRQHandler                              /* GPIO1 interrupt 1*/
    .long   I3C1_IRQHandler                                 /* I3C1 interrupt*/
    .long   LPI2C1_IRQHandler                               /* LPI2C1 interrupt*/
    .long   LPI2C2_IRQHandler                               /* LPI2C2 interrupt*/
    .long   LPIT1_IRQHandler                                /* LPIT1 interrupt*/
    .long   LPSPI1_IRQHandler                               /* LPSPI1 interrupt*/
    .long   LPSPI2_IRQHandler                               /* LPSPI2 interrupt*/
    .long   LPTMR1_IRQHandler                               /* LPTMR1 interrupt*/
    .long   LPUART1_IRQHandler                              /* LPUART1 interrupt*/
    .long   LPUART2_IRQHandler                              /* LPUART2 interrupt*/
    .long   MU1_IRQHandler                                  /* MU1 interrupt*/
    .long   MU2_IRQHandler                                  /* MU2 interrupt*/
    .long   PWM1_FAULT_IRQHandler                           /* PWM1 fault or reload error interrupt*/
    .long   PWM1_0_IRQHandler                               /* PWM1 capture 0, compare 0, or reload 0 interrupt*/
    .long   PWM1_1_IRQHandler                               /* PWM1 capture 1, compare 1, or reload 1 interrupt*/
    .long   PWM1_2_IRQHandler                               /* PWM1 capture 2, compare 2, or reload 2 interrupt*/
    .long   PWM1_3_IRQHandler                               /* PWM1 capture 3, compare 3, or reload 3 interrupt*/
    .long   EDGELOCK_TRUST_MUA_RX_FULL_IRQHandler           /* Edgelock Trust MUA RX full interrupt*/
    .long   EDGELOCK_TRUST_MUA_TX_EMPTY_IRQHandler          /* Edgelock Trust MUA TX empty interrupt*/
    .long   EDGELOCK_APPS_CORE_MUA_RX_FULL_IRQHandler       /* Edgelock Apps Core MUA RX full interrupt*/
    .long   EDGELOCK_APPS_CORE_MUA_TX_EMPTY_IRQHandler      /* Edgelock Apps Core MUA TX empty interrupt*/
    .long   EDGELOCK_REALTIME_CORE_MUA_RX_FULL_IRQHandler   /* Edgelock Realtime Core MUA RX full interrupt*/
    .long   EDGELOCK_REALTIME_CORE_MUA_TX_EMPTY_IRQHandler  /* Edgelock Realtime Core MUA TX empty interrupt*/
    .long   EDGELOCK_SECURE_IRQHandler                      /* Edgelock secure interrupt*/
    .long   EDGELOCK_NONSECURE_IRQHandler                   /* Edgelock non-secure interrupt*/
    .long   TPM1_IRQHandler                                 /* TPM1 interrupt*/
    .long   TPM2_IRQHandler                                 /* TPM2 interrupt*/
    .long   RTWDOG1_IRQHandler                              /* RTWDOG1 interrupt*/
    .long   RTWDOG2_IRQHandler                              /* RTWDOG2 interrupt*/
    .long   TRDC_MGR_AON_IRQHandler                         /* AONMIX TRDC transfer error interrupt*/
    .long   PDM_HWVAD_EVENT_IRQHandler                      /* HWVAD event interrupt*/
    .long   PDM_HWVAD_ERROR_IRQHandler                      /* HWVAD error interrupt*/
    .long   PDM_EVENT_IRQHandler                            /* PDM event interrupt*/
    .long   PDM_ERROR_IRQHandler                            /* PDM error interrupt*/
    .long   SAI1_IRQHandler                                 /* SAI interrupt*/
    .long   CM33_PS_IRQHandler                              /* M33 PS Tag/Data Parity Error*/
    .long   CM33_TCM_ECC_IRQHandler                         /* M33 TCM ECC interrupt*/
    .long   CM33_TCM_ERROR_IRQHandler                       /* M33 TCM Error interrupt*/
    .long   CM7_TCM_ECC_IRQHandler                          /* M7 TCM ECC interrupt*/
    .long   CM7_TCM_ERROR_IRQHandler                        /* M7 TCM Error interrupt*/
    .long   CAN2_IRQHandler                                 /* CAN2 interrupt*/
    .long   CAN2_ERROR_IRQHandler                           /* CAN2 error interrupt*/
    .long   FLEXIO1_IRQHandler                              /* FLEXIO1 interrupt*/
    .long   FLEXIO2_IRQHandler                              /* FLEXIO2 interrupt*/
    .long   FLEXSPI1_IRQHandler                             /* FLEXSPI1 interrupt*/
    .long   FLEXSPI2_IRQHandler                             /* FLEXSPI2 interrupt*/
    .long   GPIO2_0_IRQHandler                              /* GPIO2 interrupt 0*/
    .long   GPIO2_1_IRQHandler                              /* GPIO2 interrupt 1*/
    .long   GPIO3_0_IRQHandler                              /* GPIO3 interrupt 0*/
    .long   GPIO3_1_IRQHandler                              /* GPIO3 interrupt 1*/
    .long   I3C2_IRQHandler                                 /* I3C2 interrupt*/
    .long   LPI2C3_IRQHandler                               /* LPI2C3 interrupt*/
    .long   LPI2C4_IRQHandler                               /* LPI2C4 interrput*/
    .long   LPIT2_IRQHandler                                /* LPIT2 interrupt*/
    .long   LPSPI3_IRQHandler                               /* LPSPI3 interrupt*/
    .long   LPSPI4_IRQHandler                               /* LPSPI4 interrupt*/
    .long   LPTMR2_IRQHandler                               /* LPTMR2 interrupt*/
    .long   LPUART3_IRQHandler                              /* LPUART3 interrupt*/
    .long   LPUART4_IRQHandler                              /* LPUART4 interrupt*/
    .long   LPUART5_IRQHandler                              /* LPUART5 interrupt*/
    .long   LPUART6_IRQHandler                              /* LPUART6 interrupt*/
    .long   Reserved88_IRQHandler                           /* Reserved interrupt 88*/
    .long   BBNSM_IRQHandler                                /* BBNSM iterrupt*/
    .long   SYS_CTR1_IRQHandler                             /* System Counter compare interrupt 0 and 1*/
    .long   TPM3_IRQHandler                                 /* TPM3 interrupt*/
    .long   TPM4_IRQHandler                                 /* TPM4 interrupt*/
    .long   TPM5_IRQHandler                                 /* TPM5 interrupt*/
    .long   TPM6_IRQHandler                                 /* TPM6 interrupt*/
    .long   RTWDOG3_IRQHandler                              /* RTWDOG3 interrupt*/
    .long   RTWDOG4_IRQHandler                              /* RTWDOG4 interrupt*/
    .long   RTWDOG5_IRQHandler                              /* RTWDOG5 interrupt*/
    .long   TRDC_MGR_WKUP_IRQHandler                        /* WAKEUPMIX TRDC transfer error interrupt*/
    .long   TMPSNS_INT_IRQHandler                           /* Temperature alarm interrupt*/
    .long   BBSM_IRQHandler                                 /* BBSM wakeup alarm interrupt*/
    .long   LDO_AON_ANA_IRQHandler                          /* Brown out interrupt*/
    .long   USDHC1_IRQHandler                               /* USDHC1*/
    .long   USDHC2_IRQHandler                               /* USDHC2*/
    .long   TRDC_MGR_MEGA_IRQHandler                        /* MEGAMIX TRDC transfer error interrupt*/
    .long   SFA_IRQHandler                                  /* Signal Frequency Analyzer interrupt*/
    .long   LDO_AON_DIG_IRQHandler                          /* Brown out interrupt*/
    .long   MECC1_IRQHandler                                /* MECC1 interrupt*/
    .long   MECC2_IRQHandler                                /* MECC2 interrupt*/
    .long   ADC1_IRQHandler                                 /* ADC1 interrupt*/
    .long   DMA_ERROR_IRQHandler                            /* AON Domain eDMA error interrupt*/
    .long   DMA3_CH0_IRQHandler                             /* AON Domain eDMA channel 0 interrupt*/
    .long   DMA3_CH1_IRQHandler                             /* AON Domain eDMA channel 1 interrupt*/
    .long   DMA3_CH2_IRQHandler                             /* AON Domain eDMA channel 2 interrupt*/
    .long   DMA3_CH3_IRQHandler                             /* AON Domain eDMA channel 3 interrupt*/
    .long   DMA3_CH4_IRQHandler                             /* AON Domain eDMA channel 4 interrupt*/
    .long   DMA3_CH5_IRQHandler                             /* AON Domain eDMA channel 5 interrupt*/
    .long   DMA3_CH6_IRQHandler                             /* AON Domain eDMA channel 6 interrupt*/
    .long   DMA3_CH7_IRQHandler                             /* AON Domain eDMA channel 7 interrupt*/
    .long   DMA3_CH8_IRQHandler                             /* AON Domain eDMA channel 8 interrupt*/
    .long   DMA3_CH9_IRQHandler                             /* AON Domain eDMA channel 9 interrupt*/
    .long   DMA3_CH10_IRQHandler                            /* AON Domain eDMA channel 10 interrupt*/
    .long   DMA3_CH11_IRQHandler                            /* AON Domain eDMA channel 11 interrupt*/
    .long   DMA3_CH12_IRQHandler                            /* AON Domain eDMA channel 12 interrupt*/
    .long   DMA3_CH13_IRQHandler                            /* AON Domain eDMA channel 13 interrupt*/
    .long   DMA3_CH14_IRQHandler                            /* AON Domain eDMA channel 14 interrupt*/
    .long   DMA3_CH15_IRQHandler                            /* AON Domain eDMA channel 15 interrupt*/
    .long   DMA3_CH16_IRQHandler                            /* AON Domain eDMA channel 16 interrupt*/
    .long   DMA3_CH17_IRQHandler                            /* AON Domain eDMA channel 17 interrupt*/
    .long   DMA3_CH18_IRQHandler                            /* AON Domain eDMA channel 18 interrupt*/
    .long   DMA3_CH19_IRQHandler                            /* AON Domain eDMA channel 19 interrupt*/
    .long   DMA3_CH20_IRQHandler                            /* AON Domain eDMA channel 20 interrupt*/
    .long   DMA3_CH21_IRQHandler                            /* AON Domain eDMA channel 21 interrupt*/
    .long   DMA3_CH22_IRQHandler                            /* AON Domain eDMA channel 22 interrupt*/
    .long   DMA3_CH23_IRQHandler                            /* AON Domain eDMA channel 23 interrupt*/
    .long   DMA3_CH24_IRQHandler                            /* AON Domain eDMA channel 24 interrupt*/
    .long   DMA3_CH25_IRQHandler                            /* AON Domain eDMA channel 25 interrupt*/
    .long   DMA3_CH26_IRQHandler                            /* AON Domain eDMA channel 26 interrupt*/
    .long   DMA3_CH27_IRQHandler                            /* AON Domain eDMA channel 27 interrupt*/
    .long   DMA3_CH28_IRQHandler                            /* AON Domain eDMA channel 28 interrupt*/
    .long   DMA3_CH29_IRQHandler                            /* AON Domain eDMA channel 29 interrupt*/
    .long   DMA3_CH30_IRQHandler                            /* AON Domain eDMA channel 30 interrupt*/
    .long   DMA3_CH31_IRQHandler                            /* AON Domain eDMA channel 31 interrupt*/
    .long   DMA4_ERROR_IRQHandler                           /* WAKEUP Domain eDMA error interrupt*/
    .long   DMA4_CH0_CH1_CH32_CH33_IRQHandler               /* WAKEUP Domain eDMA channel 0/1/32/33 interrupt*/
    .long   DMA4_CH2_CH3_CH34_CH35_IRQHandler               /* WAKEUP Domain eDMA channel 2/3/34/35 interrupt*/
    .long   DMA4_CH4_CH5_CH36_CH37_IRQHandler               /* WAKEUP Domain eDMA channel 4/5/36/37 interrupt*/
    .long   DMA4_CH6_CH7_CH38_CH39_IRQHandler               /* WAKEUP Domain eDMA channel 6/7/38/39 interrupt*/
    .long   DMA4_CH8_CH9_CH40_CH41_IRQHandler               /* WAKEUP Domain eDMA channel 8/9/40/41 interrupt*/
    .long   DMA4_CH10_CH11_CH42_CH43_IRQHandler             /* WAKEUP Domain eDMA channel 10/11/42/43 interrupt*/
    .long   DMA4_CH12_CH13_CH44_CH45_IRQHandler             /* WAKEUP Domain eDMA channel 12/13/44/45 interrupt*/
    .long   DMA4_CH14_CH15_CH46_CH47_IRQHandler             /* WAKEUP Domain eDMA channel 14/15/46/47 interrupt*/
    .long   DMA4_CH16_CH17_CH48_CH49_IRQHandler             /* WAKEUP Domain eDMA channel 16/17/48/49 interrupt*/
    .long   DMA4_CH18_CH19_CH50_CH51_IRQHandler             /* WAKEUP Domain eDMA channel 18/19/50/51 interrupt*/
    .long   DMA4_CH20_CH21_CH52_CH53_IRQHandler             /* WAKEUP Domain eDMA channel 20/21/52/53 interrupt*/
    .long   DMA4_CH22_CH23_CH54_CH55_IRQHandler             /* WAKEUP Domain eDMA channel 22/23/54/55 interrupt*/
    .long   DMA4_CH24_CH25_CH56_CH57_IRQHandler             /* WAKEUP Domain eDMA channel 24/25/56/57 interrupt*/
    .long   DMA4_CH26_CH27_CH58_CH59_IRQHandler             /* WAKEUP Domain eDMA channel 26/27/58/59 interrupt*/
    .long   DMA4_CH28_CH29_CH60_CH61_IRQHandler             /* WAKEUP Domain eDMA channel 28/29/60/61 interrupt*/
    .long   DMA4_CH30_CH31_CH62_CH63_IRQHandler             /* WAKEUP Domain eDMA channel 30/31/62/63 interrupt*/
    .long   XBAR1_CH0_CH1_IRQHandler                        /* XBAR1 channel 0/1 interrupt*/
    .long   XBAR1_CH2_CH3_IRQHandler                        /* XBAR1 channel 2/3 interrupt*/
    .long   SINC3_CH0_CH1_CH2_CH3_IRQHandler                /* SINC Filter Glue 3 channel 0/1/2/3*/
    .long   EWM_IRQHandler                                  /* EWM reset out interrupt*/
    .long   SEMC_IRQHandler                                 /* SEMC interrupt*/
    .long   LPIT3_IRQHandler                                /* LPIT3 interrupt*/
    .long   LPTMR3_IRQHandler                               /* LPTMR3 interrupt*/
    .long   TMR4_IRQHandler                                 /* TMR4 interrupt*/
    .long   LPI2C5_IRQHandler                               /* LPI2C5 interrupt*/
    .long   LPI2C6_IRQHandler                               /* LPI2C6 interrupt*/
    .long   SAI4_IRQHandler                                 /* SAI4 interrupt*/
    .long   SPDIF_IRQHandler                                /* SPDIF interrupt*/
    .long   LPUART9_IRQHandler                              /* LPUART9 interrupt*/
    .long   LPUART10_IRQHandler                             /* LPUART10 interrupt*/
    .long   LPUART11_IRQHandler                             /* LPUART11 interrupt*/
    .long   LPUART12_IRQHandler                             /* LPUART12 interrupt*/
    .long   INTG_BOOTROM_DEBUG_CTRL_IRQHandler              /* CM33, CM7, DAP access IRQ*/
    .long   EDGELOCK_REQ1_IRQHandler                        /* Edgelock reuqest 1 interrupt*/
    .long   EDGELOCK_REQ2_IRQHandler                        /* Edgelock reuqest 2 interrupt*/
    .long   EDGELOCK_REQ3_IRQHandler                        /* Edgelock reuqest 3 interrupt*/
    .long   TMR3_IRQHandler                                 /* TMR3 interrupt*/
    .long   JTAGC_IRQHandler                                /* JTAGC SRC reset source*/
    .long   M33_SYSRESET_REQ_IRQHandler                     /* CM33 SYSREQRST SRC reset source*/
    .long   M33_LOCKUP_IRQHandler                           /* CM33 LOCKUP SRC reset source*/
    .long   M7_SYSRESET_REQ_IRQHandler                      /* CM33 SYSREQRST SRC reset source*/
    .long   M7_LOCKUP_IRQHandler                            /* CM33 LOCKUP SRC reset source*/
    .long   PWM2_FAULT_IRQHandler                           /* PWM2 fault or reload error interrupt*/
    .long   PWM2_0_IRQHandler                               /* PWM2 capture 0, compare 0, or reload 0 interrupt*/
    .long   PWM2_1_IRQHandler                               /* PWM2 capture 1, compare 1, or reload 1 interrupt*/
    .long   PWM2_2_IRQHandler                               /* PWM2 capture 2, compare 2, or reload 2 interrupt*/
    .long   PWM2_3_IRQHandler                               /* PWM2 capture 3, compare 3, or reload 3 interrupt*/
    .long   PWM3_FAULT_IRQHandler                           /* PWM3 fault or reload error interrupt*/
    .long   PWM3_0_IRQHandler                               /* PWM3 capture 0, compare 0, or reload 0 interrupt*/
    .long   PWM3_1_IRQHandler                               /* PWM3 capture 1, compare 1, or reload 1 interrupt*/
    .long   PWM3_2_IRQHandler                               /* PWM3 capture 2, compare 2, or reload 2 interrupt*/
    .long   PWM3_3_IRQHandler                               /* PWM3 capture 3, compare 3, or reload 3 interrupt*/
    .long   PWM4_FAULT_IRQHandler                           /* PWM4 fault or reload error interrupt*/
    .long   PWM4_0_IRQHandler                               /* PWM4 capture 0, compare 0, or reload 0 interrupt*/
    .long   PWM4_1_IRQHandler                               /* PWM4 capture 1, compare 1, or reload 1 interrupt*/
    .long   PWM4_2_IRQHandler                               /* PWM4 capture 2, compare 2, or reload 2 interrupt*/
    .long   PWM4_3_IRQHandler                               /* PWM4 capture 3, compare 3, or reload 3 interrupt*/
    .long   EQDC1_IRQHandler                                /* EQDC1 interrupt*/
    .long   EQDC2_IRQHandler                                /* EQDC2 interrupt*/
    .long   EQDC3_IRQHandler                                /* EQDC3 interrupt*/
    .long   EQDC4_IRQHandler                                /* EQDC4 interrupt*/
    .long   ADC2_IRQHandler                                 /* ADC2 interrupt*/
    .long   DCDC_IRQHandler                                 /* DCDC brown out interrupt*/
    .long   CAN3_IRQHandler                                 /* CAN3 interrupt*/
    .long   CAN3_ERROR_IRQHandler                           /* CAN3 error interrupt*/
    .long   DAC_IRQHandler                                  /* DAC interrupt*/
    .long   LPSPI5_IRQHandler                               /* LPSPI5 interrupt*/
    .long   LPSPI6_IRQHandler                               /* LPSPI6 interrupt*/
    .long   LPUART7_IRQHandler                              /* LPUART7 interrupt*/
    .long   LPUART8_IRQHandler                              /* LPUART8 interrupt*/
    .long   SAI2_IRQHandler                                 /* SAI2 interrupt*/
    .long   SAI3_IRQHandler                                 /* SAI3 interrupt*/
    .long   ACMP1_IRQHandler                                /* CMP1 interrupt*/
    .long   ACMP2_IRQHandler                                /* CMP2 interrupt*/
    .long   ACMP3_IRQHandler                                /* CMP3 interrupt*/
    .long   ACMP4_IRQHandler                                /* CMP4 interrupt*/
    .long   CM7_PS_IRQHandler                               /* M7 PS Tag/Data Parity Error*/
    .long   CM7_MCM_IRQHandler                              /* M7 MCM interrupt*/
    .long   CM33_MCM_IRQHandler                             /* M33 MCM interrupt*/
    .long   ECAT_INT_IRQHandler                             /* EtherCAT interrupt*/
    .long   SAFETY_CLK_MON_IRQHandler                       /* Safety clock monitor interrupt*/
    .long   GPT1_IRQHandler                                 /* GPT1 interrupt*/
    .long   GPT2_IRQHandler                                 /* GPT2 interrupt*/
    .long   KPP_IRQHandler                                  /* KPP interrupt*/
    .long   USBPHY1_IRQHandler                              /* USBPHY1 interrupt*/
    .long   USBPHY2_IRQHandler                              /* USBPHY2 interrupt*/
    .long   USB_OTG2_IRQHandler                             /* USBOTG2 interrupt*/
    .long   USB_OTG1_IRQHandler                             /* USBOTG1 interrupt*/
    .long   FLEXSPI_SLV_IRQHandler                          /* FLEXSPI follower interrupt*/
    .long   NETC_IRQHandler                                 /* NETC interrupt*/
    .long   MSGINTR1_IRQHandler                             /* MSGINTR1 interrupt*/
    .long   MSGINTR2_IRQHandler                             /* MSGINTR2 interrupt*/
    .long   MSGINTR3_IRQHandler                             /* MSGINTR3 interrupt*/
    .long   MSGINTR4_IRQHandler                             /* MSGINTR4 interrupt*/
    .long   MSGINTR5_IRQHandler                             /* MSGINTR5 interrupt*/
    .long   MSGINTR6_IRQHandler                             /* MSGINTR6 interrupt*/
    .long   SINC1_CH0_IRQHandler                            /* SINC Filter Glue 1 channel 0*/
    .long   SINC1_CH1_IRQHandler                            /* SINC Filter Glue 1 channel 1*/
    .long   SINC1_CH2_IRQHandler                            /* SINC Filter Glue 1 channel 2*/
    .long   SINC1_CH3_IRQHandler                            /* SINC Filter Glue 1 channel 3*/
    .long   SINC2_CH0_IRQHandler                            /* SINC Filter Glue 2 channel 0*/
    .long   SINC2_CH1_IRQHandler                            /* SINC Filter Glue 2 channel 1*/
    .long   SINC2_CH2_IRQHandler                            /* SINC Filter Glue 2 channel 2*/
    .long   SINC2_CH3_IRQHandler                            /* SINC Filter Glue 2 channel 3*/
    .long   GPIO4_IRQHandler                                /* GPIO4 interrupt*/
    .long   TMR2_IRQHandler                                 /* TMR2 interrupt*/
    .long   GPIO5_IRQHandler                                /* GPIO5 interrupt*/
    .long   ASRC_IRQHandler                                 /* ASRC interrupt*/
    .long   GPIO6_IRQHandler                                /* GPIO6 interrupt*/
    .long   DBG_TRACE_IRQHandler                            /* JTAGSW DAP MDM-AP SRC reset source*/
    .long   ECAT_RST_OUT_IRQHandler                         /* ECAT reset out interrupt*/
    .long   0xFFFFFFFF                                      /*  Reserved for user TRIM value*/

    .size   __isr_vector, . - __isr_vector

    .text
    .thumb

#if defined (__cplusplus)
#ifdef __REDLIB__
#error Redlib does not support C++
#endif
#endif
/* Reset Handler */

    .thumb_func
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    cpsid   i               /* Mask interrupts */
    .equ    VTOR, 0xE000ED08
    ldr     r0, =VTOR
    ldr     r1, =__isr_vector
    str     r1, [r0]
    ldr     r2, [r1]
    msr     msp, r2
#ifndef __NO_SYSTEM_INIT
    ldr   r0,=SystemInit
    blx   r0
#endif
/*    Loop to copy data from read only memory to RAM. The ranges of copy
 *    from/to are specified by following symbols evaluated in linker script.
 *      1. __data_flash_start/__data_start__/__data_end__
 *      2. __ram_function_flash_start/__ram_function_start__/__ram_function_end__
 *      3. __noncache_data_flash_start/__noncache_data_start__/__noncache_data_end__
 *      4. __qadata_flash_start/__qadata_start__/__qadata_end__
 *
 *      Note: All must be aligned to 4 bytes boundary.
 */

    ldr    r1, =__data_flash_start
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__
#ifdef __PERFORMANCE_IMPLEMENTATION
/* Here are two copies of loop implementations. First one favors performance
 * and the second one favors code size. Default uses the second one.
 * Define macro "__PERFORMANCE_IMPLEMENTATION" in project to use the first one */
    subs   r3, r2
    ble    .LC1
.LC0:
    subs   r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .LC0
.LC1:
#else  /* code size implemenation */
.LC0:
    cmp    r2, r3
    ittt   lt
    ldrlt  r0, [r1], #4
    strlt  r0, [r2], #4
    blt    .LC0
#endif

#ifdef __STARTUP_INITIALIZE_RAMFUNCTION
    ldr    r1, =__ram_function_flash_start
    ldr    r2, =__ram_function_start__
    ldr    r3, =__ram_function_end__
#ifdef __PERFORMANCE_IMPLEMENTATION
/* Here are two copies of loop implementations. First one favors performance
 * and the second one favors code size. Default uses the second one.
 * Define macro "__PERFORMANCE_IMPLEMENTATION" in project to use the first one */
    subs   r3, r2
    ble    .LC_ramfunc_copy_end
.LC_ramfunc_copy_start:
    subs   r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .LC_ramfunc_copy_start
.LC_ramfunc_copy_end:
#else  /* code size implemenation */
.LC_ramfunc_copy_start:
    cmp    r2, r3
    ittt   lt
    ldrlt  r0, [r1], #4
    strlt  r0, [r2], #4
    blt    .LC_ramfunc_copy_start
#endif
#endif /* __STARTUP_INITIALIZE_RAMFUNCTION */

#ifdef __STARTUP_INITIALIZE_NONCACHEDATA
    ldr    r1, =__noncache_data_flash_start
    ldr    r2, =__noncache_data_start__
    ldr    r3, =__noncache_data_end__
#ifdef __PERFORMANCE_IMPLEMENTATION
/* Here are two copies of loop implementations. First one favors performance
 * and the second one favors code size. Default uses the second one.
 * Define macro "__PERFORMANCE_IMPLEMENTATION" in project to use the first one */
    subs   r3, r2
    ble    .LC3
.LC2:
    subs   r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .LC2
.LC3:
#else  /* code size implemenation */
.LC2:
    cmp    r2, r3
    ittt   lt
    ldrlt  r0, [r1], #4
    strlt  r0, [r2], #4
    blt    .LC2
#endif
/* zero inited ncache section initialization */
    ldr    r2, =__noncache_bss_start__
    ldr    r3, =__noncache_bss_end__
    movs   r0,0
.LC4:
    cmp    r2,r3
    itt    lt
    strlt  r0,[r2],#4
    blt    .LC4
#endif /* __STARTUP_INITIALIZE_NONCACHEDATA */

#ifdef __STARTUP_INITIALIZE_QADATA
    ldr    r1, =__qadata_flash_start
    ldr    r2, =__qadata_start__
    ldr    r3, =__qadata_end__
#ifdef __PERFORMANCE_IMPLEMENTATION
/* Here are two copies of loop implementations. First one favors performance
 * and the second one favors code size. Default uses the second one.
 * Define macro "__PERFORMANCE_IMPLEMENTATION" in project to use the first one */
    subs   r3, r2
    ble    .LC_qadata_copy_end
.LC_qadata_copy_start:
    subs   r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .LC_qadata_copy_start
.LC_qadata_copy_end:
#else  /* code size implemenation */
.LC_qadata_copy_start:
    cmp    r2, r3
    ittt   lt
    ldrlt  r0, [r1], #4
    strlt  r0, [r2], #4
    blt    .LC_qadata_copy_start
#endif
#endif /* __STARTUP_INITIALIZE_QADATA */

#ifdef __STARTUP_CLEAR_BSS
/*     This part of work usually is done in C library startup code. Otherwise,
 *     define this macro to enable it in this startup.
 *
 *     Loop to zero out BSS section, which uses following symbols
 *     in linker script:
 *      __bss_start__: start of BSS section. Must align to 4
 *      __bss_end__: end of BSS section. Must align to 4
 */
    ldr    r1, =__bss_start__
    ldr    r2, =__bss_end__
    movs   r0, 0
.LC5:
    cmp    r1, r2
    itt    lt
    strlt  r0, [r1], #4
    blt    .LC5
#endif /* __STARTUP_CLEAR_BSS */

/* Start stack / heap initializaiton */
    movs   r0, 0
    ldr    r1, =__HeapBase
    ldr    r2, =__HeapLimit
.LC6:
    cmp    r1, r2
    itt    lt
    strlt  r0, [r1], #4
    blt    .LC6

    ldr    r1, =__StackLimit
    ldr    r2, =__StackTop
.LC7:
    cmp    r1, r2
    itt    lt
    strlt  r0, [r1], #4
    blt    .LC7
/* End of stack / heap initializaiton */

    cpsie   i               /* Unmask interrupts */
#ifndef __START
#ifdef __REDLIB__
#define __START __main
#else
#define __START _start
#endif
#endif
#ifndef __ATOLLIC__
    ldr   r0,=__START
    blx   r0
#else
    ldr   r0,=__libc_init_array
    blx   r0
    ldr   r0,=main
    bx    r0
#endif
    .pool
    .size Reset_Handler, . - Reset_Handler

    .align  1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    b DefaultISR
    .size DefaultISR, . - DefaultISR

    .align 1
    .thumb_func
    .weak NMI_Handler
    .type NMI_Handler, %function
NMI_Handler:
    ldr   r0,=NMI_Handler
    bx    r0
    .size NMI_Handler, . - NMI_Handler

    .align 1
    .thumb_func
    .weak HardFault_Handler
    .type HardFault_Handler, %function
HardFault_Handler:
    ldr   r0,=HardFault_Handler
    bx    r0
    .size HardFault_Handler, . - HardFault_Handler

    .align 1
    .thumb_func
    .weak SVC_Handler
    .type SVC_Handler, %function
SVC_Handler:
    ldr   r0,=SVC_Handler
    bx    r0
    .size SVC_Handler, . - SVC_Handler

    .align 1
    .thumb_func
    .weak PendSV_Handler
    .type PendSV_Handler, %function
PendSV_Handler:
    ldr   r0,=PendSV_Handler
    bx    r0
    .size PendSV_Handler, . - PendSV_Handler

    .align 1
    .thumb_func
    .weak SysTick_Handler
    .type SysTick_Handler, %function
SysTick_Handler:
    ldr   r0,=SysTick_Handler
    bx    r0
    .size SysTick_Handler, . - SysTick_Handler

    .align 1
    .thumb_func
    .weak CAN1_IRQHandler
    .type CAN1_IRQHandler, %function
CAN1_IRQHandler:
    ldr   r0,=CAN1_DriverIRQHandler
    bx    r0
    .size CAN1_IRQHandler, . - CAN1_IRQHandler

    .align 1
    .thumb_func
    .weak CAN1_ERROR_IRQHandler
    .type CAN1_ERROR_IRQHandler, %function
CAN1_ERROR_IRQHandler:
    ldr   r0,=CAN1_ERROR_DriverIRQHandler
    bx    r0
    .size CAN1_ERROR_IRQHandler, . - CAN1_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak I3C1_IRQHandler
    .type I3C1_IRQHandler, %function
I3C1_IRQHandler:
    ldr   r0,=I3C1_DriverIRQHandler
    bx    r0
    .size I3C1_IRQHandler, . - I3C1_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C1_IRQHandler
    .type LPI2C1_IRQHandler, %function
LPI2C1_IRQHandler:
    ldr   r0,=LPI2C1_DriverIRQHandler
    bx    r0
    .size LPI2C1_IRQHandler, . - LPI2C1_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C2_IRQHandler
    .type LPI2C2_IRQHandler, %function
LPI2C2_IRQHandler:
    ldr   r0,=LPI2C2_DriverIRQHandler
    bx    r0
    .size LPI2C2_IRQHandler, . - LPI2C2_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI1_IRQHandler
    .type LPSPI1_IRQHandler, %function
LPSPI1_IRQHandler:
    ldr   r0,=LPSPI1_DriverIRQHandler
    bx    r0
    .size LPSPI1_IRQHandler, . - LPSPI1_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI2_IRQHandler
    .type LPSPI2_IRQHandler, %function
LPSPI2_IRQHandler:
    ldr   r0,=LPSPI2_DriverIRQHandler
    bx    r0
    .size LPSPI2_IRQHandler, . - LPSPI2_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART1_IRQHandler
    .type LPUART1_IRQHandler, %function
LPUART1_IRQHandler:
    ldr   r0,=LPUART1_DriverIRQHandler
    bx    r0
    .size LPUART1_IRQHandler, . - LPUART1_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART2_IRQHandler
    .type LPUART2_IRQHandler, %function
LPUART2_IRQHandler:
    ldr   r0,=LPUART2_DriverIRQHandler
    bx    r0
    .size LPUART2_IRQHandler, . - LPUART2_IRQHandler

    .align 1
    .thumb_func
    .weak PDM_HWVAD_EVENT_IRQHandler
    .type PDM_HWVAD_EVENT_IRQHandler, %function
PDM_HWVAD_EVENT_IRQHandler:
    ldr   r0,=PDM_HWVAD_EVENT_DriverIRQHandler
    bx    r0
    .size PDM_HWVAD_EVENT_IRQHandler, . - PDM_HWVAD_EVENT_IRQHandler

    .align 1
    .thumb_func
    .weak PDM_HWVAD_ERROR_IRQHandler
    .type PDM_HWVAD_ERROR_IRQHandler, %function
PDM_HWVAD_ERROR_IRQHandler:
    ldr   r0,=PDM_HWVAD_ERROR_DriverIRQHandler
    bx    r0
    .size PDM_HWVAD_ERROR_IRQHandler, . - PDM_HWVAD_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak PDM_EVENT_IRQHandler
    .type PDM_EVENT_IRQHandler, %function
PDM_EVENT_IRQHandler:
    ldr   r0,=PDM_EVENT_DriverIRQHandler
    bx    r0
    .size PDM_EVENT_IRQHandler, . - PDM_EVENT_IRQHandler

    .align 1
    .thumb_func
    .weak PDM_ERROR_IRQHandler
    .type PDM_ERROR_IRQHandler, %function
PDM_ERROR_IRQHandler:
    ldr   r0,=PDM_ERROR_DriverIRQHandler
    bx    r0
    .size PDM_ERROR_IRQHandler, . - PDM_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak SAI1_IRQHandler
    .type SAI1_IRQHandler, %function
SAI1_IRQHandler:
    ldr   r0,=SAI1_DriverIRQHandler
    bx    r0
    .size SAI1_IRQHandler, . - SAI1_IRQHandler

    .align 1
    .thumb_func
    .weak CAN2_IRQHandler
    .type CAN2_IRQHandler, %function
CAN2_IRQHandler:
    ldr   r0,=CAN2_DriverIRQHandler
    bx    r0
    .size CAN2_IRQHandler, . - CAN2_IRQHandler

    .align 1
    .thumb_func
    .weak CAN2_ERROR_IRQHandler
    .type CAN2_ERROR_IRQHandler, %function
CAN2_ERROR_IRQHandler:
    ldr   r0,=CAN2_ERROR_DriverIRQHandler
    bx    r0
    .size CAN2_ERROR_IRQHandler, . - CAN2_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXIO1_IRQHandler
    .type FLEXIO1_IRQHandler, %function
FLEXIO1_IRQHandler:
    ldr   r0,=FLEXIO1_DriverIRQHandler
    bx    r0
    .size FLEXIO1_IRQHandler, . - FLEXIO1_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXIO2_IRQHandler
    .type FLEXIO2_IRQHandler, %function
FLEXIO2_IRQHandler:
    ldr   r0,=FLEXIO2_DriverIRQHandler
    bx    r0
    .size FLEXIO2_IRQHandler, . - FLEXIO2_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXSPI1_IRQHandler
    .type FLEXSPI1_IRQHandler, %function
FLEXSPI1_IRQHandler:
    ldr   r0,=FLEXSPI1_DriverIRQHandler
    bx    r0
    .size FLEXSPI1_IRQHandler, . - FLEXSPI1_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXSPI2_IRQHandler
    .type FLEXSPI2_IRQHandler, %function
FLEXSPI2_IRQHandler:
    ldr   r0,=FLEXSPI2_DriverIRQHandler
    bx    r0
    .size FLEXSPI2_IRQHandler, . - FLEXSPI2_IRQHandler

    .align 1
    .thumb_func
    .weak I3C2_IRQHandler
    .type I3C2_IRQHandler, %function
I3C2_IRQHandler:
    ldr   r0,=I3C2_DriverIRQHandler
    bx    r0
    .size I3C2_IRQHandler, . - I3C2_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C3_IRQHandler
    .type LPI2C3_IRQHandler, %function
LPI2C3_IRQHandler:
    ldr   r0,=LPI2C3_DriverIRQHandler
    bx    r0
    .size LPI2C3_IRQHandler, . - LPI2C3_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C4_IRQHandler
    .type LPI2C4_IRQHandler, %function
LPI2C4_IRQHandler:
    ldr   r0,=LPI2C4_DriverIRQHandler
    bx    r0
    .size LPI2C4_IRQHandler, . - LPI2C4_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI3_IRQHandler
    .type LPSPI3_IRQHandler, %function
LPSPI3_IRQHandler:
    ldr   r0,=LPSPI3_DriverIRQHandler
    bx    r0
    .size LPSPI3_IRQHandler, . - LPSPI3_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI4_IRQHandler
    .type LPSPI4_IRQHandler, %function
LPSPI4_IRQHandler:
    ldr   r0,=LPSPI4_DriverIRQHandler
    bx    r0
    .size LPSPI4_IRQHandler, . - LPSPI4_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART3_IRQHandler
    .type LPUART3_IRQHandler, %function
LPUART3_IRQHandler:
    ldr   r0,=LPUART3_DriverIRQHandler
    bx    r0
    .size LPUART3_IRQHandler, . - LPUART3_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART4_IRQHandler
    .type LPUART4_IRQHandler, %function
LPUART4_IRQHandler:
    ldr   r0,=LPUART4_DriverIRQHandler
    bx    r0
    .size LPUART4_IRQHandler, . - LPUART4_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART5_IRQHandler
    .type LPUART5_IRQHandler, %function
LPUART5_IRQHandler:
    ldr   r0,=LPUART5_DriverIRQHandler
    bx    r0
    .size LPUART5_IRQHandler, . - LPUART5_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART6_IRQHandler
    .type LPUART6_IRQHandler, %function
LPUART6_IRQHandler:
    ldr   r0,=LPUART6_DriverIRQHandler
    bx    r0
    .size LPUART6_IRQHandler, . - LPUART6_IRQHandler

    .align 1
    .thumb_func
    .weak USDHC1_IRQHandler
    .type USDHC1_IRQHandler, %function
USDHC1_IRQHandler:
    ldr   r0,=USDHC1_DriverIRQHandler
    bx    r0
    .size USDHC1_IRQHandler, . - USDHC1_IRQHandler

    .align 1
    .thumb_func
    .weak USDHC2_IRQHandler
    .type USDHC2_IRQHandler, %function
USDHC2_IRQHandler:
    ldr   r0,=USDHC2_DriverIRQHandler
    bx    r0
    .size USDHC2_IRQHandler, . - USDHC2_IRQHandler

    .align 1
    .thumb_func
    .weak DMA_ERROR_IRQHandler
    .type DMA_ERROR_IRQHandler, %function
DMA_ERROR_IRQHandler:
    ldr   r0,=DMA_ERROR_DriverIRQHandler
    bx    r0
    .size DMA_ERROR_IRQHandler, . - DMA_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH0_IRQHandler
    .type DMA3_CH0_IRQHandler, %function
DMA3_CH0_IRQHandler:
    ldr   r0,=DMA3_CH0_DriverIRQHandler
    bx    r0
    .size DMA3_CH0_IRQHandler, . - DMA3_CH0_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH1_IRQHandler
    .type DMA3_CH1_IRQHandler, %function
DMA3_CH1_IRQHandler:
    ldr   r0,=DMA3_CH1_DriverIRQHandler
    bx    r0
    .size DMA3_CH1_IRQHandler, . - DMA3_CH1_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH2_IRQHandler
    .type DMA3_CH2_IRQHandler, %function
DMA3_CH2_IRQHandler:
    ldr   r0,=DMA3_CH2_DriverIRQHandler
    bx    r0
    .size DMA3_CH2_IRQHandler, . - DMA3_CH2_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH3_IRQHandler
    .type DMA3_CH3_IRQHandler, %function
DMA3_CH3_IRQHandler:
    ldr   r0,=DMA3_CH3_DriverIRQHandler
    bx    r0
    .size DMA3_CH3_IRQHandler, . - DMA3_CH3_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH4_IRQHandler
    .type DMA3_CH4_IRQHandler, %function
DMA3_CH4_IRQHandler:
    ldr   r0,=DMA3_CH4_DriverIRQHandler
    bx    r0
    .size DMA3_CH4_IRQHandler, . - DMA3_CH4_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH5_IRQHandler
    .type DMA3_CH5_IRQHandler, %function
DMA3_CH5_IRQHandler:
    ldr   r0,=DMA3_CH5_DriverIRQHandler
    bx    r0
    .size DMA3_CH5_IRQHandler, . - DMA3_CH5_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH6_IRQHandler
    .type DMA3_CH6_IRQHandler, %function
DMA3_CH6_IRQHandler:
    ldr   r0,=DMA3_CH6_DriverIRQHandler
    bx    r0
    .size DMA3_CH6_IRQHandler, . - DMA3_CH6_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH7_IRQHandler
    .type DMA3_CH7_IRQHandler, %function
DMA3_CH7_IRQHandler:
    ldr   r0,=DMA3_CH7_DriverIRQHandler
    bx    r0
    .size DMA3_CH7_IRQHandler, . - DMA3_CH7_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH8_IRQHandler
    .type DMA3_CH8_IRQHandler, %function
DMA3_CH8_IRQHandler:
    ldr   r0,=DMA3_CH8_DriverIRQHandler
    bx    r0
    .size DMA3_CH8_IRQHandler, . - DMA3_CH8_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH9_IRQHandler
    .type DMA3_CH9_IRQHandler, %function
DMA3_CH9_IRQHandler:
    ldr   r0,=DMA3_CH9_DriverIRQHandler
    bx    r0
    .size DMA3_CH9_IRQHandler, . - DMA3_CH9_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH10_IRQHandler
    .type DMA3_CH10_IRQHandler, %function
DMA3_CH10_IRQHandler:
    ldr   r0,=DMA3_CH10_DriverIRQHandler
    bx    r0
    .size DMA3_CH10_IRQHandler, . - DMA3_CH10_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH11_IRQHandler
    .type DMA3_CH11_IRQHandler, %function
DMA3_CH11_IRQHandler:
    ldr   r0,=DMA3_CH11_DriverIRQHandler
    bx    r0
    .size DMA3_CH11_IRQHandler, . - DMA3_CH11_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH12_IRQHandler
    .type DMA3_CH12_IRQHandler, %function
DMA3_CH12_IRQHandler:
    ldr   r0,=DMA3_CH12_DriverIRQHandler
    bx    r0
    .size DMA3_CH12_IRQHandler, . - DMA3_CH12_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH13_IRQHandler
    .type DMA3_CH13_IRQHandler, %function
DMA3_CH13_IRQHandler:
    ldr   r0,=DMA3_CH13_DriverIRQHandler
    bx    r0
    .size DMA3_CH13_IRQHandler, . - DMA3_CH13_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH14_IRQHandler
    .type DMA3_CH14_IRQHandler, %function
DMA3_CH14_IRQHandler:
    ldr   r0,=DMA3_CH14_DriverIRQHandler
    bx    r0
    .size DMA3_CH14_IRQHandler, . - DMA3_CH14_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH15_IRQHandler
    .type DMA3_CH15_IRQHandler, %function
DMA3_CH15_IRQHandler:
    ldr   r0,=DMA3_CH15_DriverIRQHandler
    bx    r0
    .size DMA3_CH15_IRQHandler, . - DMA3_CH15_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH16_IRQHandler
    .type DMA3_CH16_IRQHandler, %function
DMA3_CH16_IRQHandler:
    ldr   r0,=DMA3_CH16_DriverIRQHandler
    bx    r0
    .size DMA3_CH16_IRQHandler, . - DMA3_CH16_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH17_IRQHandler
    .type DMA3_CH17_IRQHandler, %function
DMA3_CH17_IRQHandler:
    ldr   r0,=DMA3_CH17_DriverIRQHandler
    bx    r0
    .size DMA3_CH17_IRQHandler, . - DMA3_CH17_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH18_IRQHandler
    .type DMA3_CH18_IRQHandler, %function
DMA3_CH18_IRQHandler:
    ldr   r0,=DMA3_CH18_DriverIRQHandler
    bx    r0
    .size DMA3_CH18_IRQHandler, . - DMA3_CH18_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH19_IRQHandler
    .type DMA3_CH19_IRQHandler, %function
DMA3_CH19_IRQHandler:
    ldr   r0,=DMA3_CH19_DriverIRQHandler
    bx    r0
    .size DMA3_CH19_IRQHandler, . - DMA3_CH19_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH20_IRQHandler
    .type DMA3_CH20_IRQHandler, %function
DMA3_CH20_IRQHandler:
    ldr   r0,=DMA3_CH20_DriverIRQHandler
    bx    r0
    .size DMA3_CH20_IRQHandler, . - DMA3_CH20_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH21_IRQHandler
    .type DMA3_CH21_IRQHandler, %function
DMA3_CH21_IRQHandler:
    ldr   r0,=DMA3_CH21_DriverIRQHandler
    bx    r0
    .size DMA3_CH21_IRQHandler, . - DMA3_CH21_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH22_IRQHandler
    .type DMA3_CH22_IRQHandler, %function
DMA3_CH22_IRQHandler:
    ldr   r0,=DMA3_CH22_DriverIRQHandler
    bx    r0
    .size DMA3_CH22_IRQHandler, . - DMA3_CH22_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH23_IRQHandler
    .type DMA3_CH23_IRQHandler, %function
DMA3_CH23_IRQHandler:
    ldr   r0,=DMA3_CH23_DriverIRQHandler
    bx    r0
    .size DMA3_CH23_IRQHandler, . - DMA3_CH23_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH24_IRQHandler
    .type DMA3_CH24_IRQHandler, %function
DMA3_CH24_IRQHandler:
    ldr   r0,=DMA3_CH24_DriverIRQHandler
    bx    r0
    .size DMA3_CH24_IRQHandler, . - DMA3_CH24_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH25_IRQHandler
    .type DMA3_CH25_IRQHandler, %function
DMA3_CH25_IRQHandler:
    ldr   r0,=DMA3_CH25_DriverIRQHandler
    bx    r0
    .size DMA3_CH25_IRQHandler, . - DMA3_CH25_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH26_IRQHandler
    .type DMA3_CH26_IRQHandler, %function
DMA3_CH26_IRQHandler:
    ldr   r0,=DMA3_CH26_DriverIRQHandler
    bx    r0
    .size DMA3_CH26_IRQHandler, . - DMA3_CH26_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH27_IRQHandler
    .type DMA3_CH27_IRQHandler, %function
DMA3_CH27_IRQHandler:
    ldr   r0,=DMA3_CH27_DriverIRQHandler
    bx    r0
    .size DMA3_CH27_IRQHandler, . - DMA3_CH27_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH28_IRQHandler
    .type DMA3_CH28_IRQHandler, %function
DMA3_CH28_IRQHandler:
    ldr   r0,=DMA3_CH28_DriverIRQHandler
    bx    r0
    .size DMA3_CH28_IRQHandler, . - DMA3_CH28_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH29_IRQHandler
    .type DMA3_CH29_IRQHandler, %function
DMA3_CH29_IRQHandler:
    ldr   r0,=DMA3_CH29_DriverIRQHandler
    bx    r0
    .size DMA3_CH29_IRQHandler, . - DMA3_CH29_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH30_IRQHandler
    .type DMA3_CH30_IRQHandler, %function
DMA3_CH30_IRQHandler:
    ldr   r0,=DMA3_CH30_DriverIRQHandler
    bx    r0
    .size DMA3_CH30_IRQHandler, . - DMA3_CH30_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_CH31_IRQHandler
    .type DMA3_CH31_IRQHandler, %function
DMA3_CH31_IRQHandler:
    ldr   r0,=DMA3_CH31_DriverIRQHandler
    bx    r0
    .size DMA3_CH31_IRQHandler, . - DMA3_CH31_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_ERROR_IRQHandler
    .type DMA4_ERROR_IRQHandler, %function
DMA4_ERROR_IRQHandler:
    ldr   r0,=DMA4_ERROR_DriverIRQHandler
    bx    r0
    .size DMA4_ERROR_IRQHandler, . - DMA4_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH0_CH1_CH32_CH33_IRQHandler
    .type DMA4_CH0_CH1_CH32_CH33_IRQHandler, %function
DMA4_CH0_CH1_CH32_CH33_IRQHandler:
    ldr   r0,=DMA4_CH0_CH1_CH32_CH33_DriverIRQHandler
    bx    r0
    .size DMA4_CH0_CH1_CH32_CH33_IRQHandler, . - DMA4_CH0_CH1_CH32_CH33_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH2_CH3_CH34_CH35_IRQHandler
    .type DMA4_CH2_CH3_CH34_CH35_IRQHandler, %function
DMA4_CH2_CH3_CH34_CH35_IRQHandler:
    ldr   r0,=DMA4_CH2_CH3_CH34_CH35_DriverIRQHandler
    bx    r0
    .size DMA4_CH2_CH3_CH34_CH35_IRQHandler, . - DMA4_CH2_CH3_CH34_CH35_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH4_CH5_CH36_CH37_IRQHandler
    .type DMA4_CH4_CH5_CH36_CH37_IRQHandler, %function
DMA4_CH4_CH5_CH36_CH37_IRQHandler:
    ldr   r0,=DMA4_CH4_CH5_CH36_CH37_DriverIRQHandler
    bx    r0
    .size DMA4_CH4_CH5_CH36_CH37_IRQHandler, . - DMA4_CH4_CH5_CH36_CH37_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH6_CH7_CH38_CH39_IRQHandler
    .type DMA4_CH6_CH7_CH38_CH39_IRQHandler, %function
DMA4_CH6_CH7_CH38_CH39_IRQHandler:
    ldr   r0,=DMA4_CH6_CH7_CH38_CH39_DriverIRQHandler
    bx    r0
    .size DMA4_CH6_CH7_CH38_CH39_IRQHandler, . - DMA4_CH6_CH7_CH38_CH39_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH8_CH9_CH40_CH41_IRQHandler
    .type DMA4_CH8_CH9_CH40_CH41_IRQHandler, %function
DMA4_CH8_CH9_CH40_CH41_IRQHandler:
    ldr   r0,=DMA4_CH8_CH9_CH40_CH41_DriverIRQHandler
    bx    r0
    .size DMA4_CH8_CH9_CH40_CH41_IRQHandler, . - DMA4_CH8_CH9_CH40_CH41_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH10_CH11_CH42_CH43_IRQHandler
    .type DMA4_CH10_CH11_CH42_CH43_IRQHandler, %function
DMA4_CH10_CH11_CH42_CH43_IRQHandler:
    ldr   r0,=DMA4_CH10_CH11_CH42_CH43_DriverIRQHandler
    bx    r0
    .size DMA4_CH10_CH11_CH42_CH43_IRQHandler, . - DMA4_CH10_CH11_CH42_CH43_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH12_CH13_CH44_CH45_IRQHandler
    .type DMA4_CH12_CH13_CH44_CH45_IRQHandler, %function
DMA4_CH12_CH13_CH44_CH45_IRQHandler:
    ldr   r0,=DMA4_CH12_CH13_CH44_CH45_DriverIRQHandler
    bx    r0
    .size DMA4_CH12_CH13_CH44_CH45_IRQHandler, . - DMA4_CH12_CH13_CH44_CH45_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH14_CH15_CH46_CH47_IRQHandler
    .type DMA4_CH14_CH15_CH46_CH47_IRQHandler, %function
DMA4_CH14_CH15_CH46_CH47_IRQHandler:
    ldr   r0,=DMA4_CH14_CH15_CH46_CH47_DriverIRQHandler
    bx    r0
    .size DMA4_CH14_CH15_CH46_CH47_IRQHandler, . - DMA4_CH14_CH15_CH46_CH47_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH16_CH17_CH48_CH49_IRQHandler
    .type DMA4_CH16_CH17_CH48_CH49_IRQHandler, %function
DMA4_CH16_CH17_CH48_CH49_IRQHandler:
    ldr   r0,=DMA4_CH16_CH17_CH48_CH49_DriverIRQHandler
    bx    r0
    .size DMA4_CH16_CH17_CH48_CH49_IRQHandler, . - DMA4_CH16_CH17_CH48_CH49_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH18_CH19_CH50_CH51_IRQHandler
    .type DMA4_CH18_CH19_CH50_CH51_IRQHandler, %function
DMA4_CH18_CH19_CH50_CH51_IRQHandler:
    ldr   r0,=DMA4_CH18_CH19_CH50_CH51_DriverIRQHandler
    bx    r0
    .size DMA4_CH18_CH19_CH50_CH51_IRQHandler, . - DMA4_CH18_CH19_CH50_CH51_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH20_CH21_CH52_CH53_IRQHandler
    .type DMA4_CH20_CH21_CH52_CH53_IRQHandler, %function
DMA4_CH20_CH21_CH52_CH53_IRQHandler:
    ldr   r0,=DMA4_CH20_CH21_CH52_CH53_DriverIRQHandler
    bx    r0
    .size DMA4_CH20_CH21_CH52_CH53_IRQHandler, . - DMA4_CH20_CH21_CH52_CH53_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH22_CH23_CH54_CH55_IRQHandler
    .type DMA4_CH22_CH23_CH54_CH55_IRQHandler, %function
DMA4_CH22_CH23_CH54_CH55_IRQHandler:
    ldr   r0,=DMA4_CH22_CH23_CH54_CH55_DriverIRQHandler
    bx    r0
    .size DMA4_CH22_CH23_CH54_CH55_IRQHandler, . - DMA4_CH22_CH23_CH54_CH55_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH24_CH25_CH56_CH57_IRQHandler
    .type DMA4_CH24_CH25_CH56_CH57_IRQHandler, %function
DMA4_CH24_CH25_CH56_CH57_IRQHandler:
    ldr   r0,=DMA4_CH24_CH25_CH56_CH57_DriverIRQHandler
    bx    r0
    .size DMA4_CH24_CH25_CH56_CH57_IRQHandler, . - DMA4_CH24_CH25_CH56_CH57_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH26_CH27_CH58_CH59_IRQHandler
    .type DMA4_CH26_CH27_CH58_CH59_IRQHandler, %function
DMA4_CH26_CH27_CH58_CH59_IRQHandler:
    ldr   r0,=DMA4_CH26_CH27_CH58_CH59_DriverIRQHandler
    bx    r0
    .size DMA4_CH26_CH27_CH58_CH59_IRQHandler, . - DMA4_CH26_CH27_CH58_CH59_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH28_CH29_CH60_CH61_IRQHandler
    .type DMA4_CH28_CH29_CH60_CH61_IRQHandler, %function
DMA4_CH28_CH29_CH60_CH61_IRQHandler:
    ldr   r0,=DMA4_CH28_CH29_CH60_CH61_DriverIRQHandler
    bx    r0
    .size DMA4_CH28_CH29_CH60_CH61_IRQHandler, . - DMA4_CH28_CH29_CH60_CH61_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_CH30_CH31_CH62_CH63_IRQHandler
    .type DMA4_CH30_CH31_CH62_CH63_IRQHandler, %function
DMA4_CH30_CH31_CH62_CH63_IRQHandler:
    ldr   r0,=DMA4_CH30_CH31_CH62_CH63_DriverIRQHandler
    bx    r0
    .size DMA4_CH30_CH31_CH62_CH63_IRQHandler, . - DMA4_CH30_CH31_CH62_CH63_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C5_IRQHandler
    .type LPI2C5_IRQHandler, %function
LPI2C5_IRQHandler:
    ldr   r0,=LPI2C5_DriverIRQHandler
    bx    r0
    .size LPI2C5_IRQHandler, . - LPI2C5_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C6_IRQHandler
    .type LPI2C6_IRQHandler, %function
LPI2C6_IRQHandler:
    ldr   r0,=LPI2C6_DriverIRQHandler
    bx    r0
    .size LPI2C6_IRQHandler, . - LPI2C6_IRQHandler

    .align 1
    .thumb_func
    .weak SAI4_IRQHandler
    .type SAI4_IRQHandler, %function
SAI4_IRQHandler:
    ldr   r0,=SAI4_DriverIRQHandler
    bx    r0
    .size SAI4_IRQHandler, . - SAI4_IRQHandler

    .align 1
    .thumb_func
    .weak SPDIF_IRQHandler
    .type SPDIF_IRQHandler, %function
SPDIF_IRQHandler:
    ldr   r0,=SPDIF_DriverIRQHandler
    bx    r0
    .size SPDIF_IRQHandler, . - SPDIF_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART9_IRQHandler
    .type LPUART9_IRQHandler, %function
LPUART9_IRQHandler:
    ldr   r0,=LPUART9_DriverIRQHandler
    bx    r0
    .size LPUART9_IRQHandler, . - LPUART9_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART10_IRQHandler
    .type LPUART10_IRQHandler, %function
LPUART10_IRQHandler:
    ldr   r0,=LPUART10_DriverIRQHandler
    bx    r0
    .size LPUART10_IRQHandler, . - LPUART10_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART11_IRQHandler
    .type LPUART11_IRQHandler, %function
LPUART11_IRQHandler:
    ldr   r0,=LPUART11_DriverIRQHandler
    bx    r0
    .size LPUART11_IRQHandler, . - LPUART11_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART12_IRQHandler
    .type LPUART12_IRQHandler, %function
LPUART12_IRQHandler:
    ldr   r0,=LPUART12_DriverIRQHandler
    bx    r0
    .size LPUART12_IRQHandler, . - LPUART12_IRQHandler

    .align 1
    .thumb_func
    .weak CAN3_IRQHandler
    .type CAN3_IRQHandler, %function
CAN3_IRQHandler:
    ldr   r0,=CAN3_DriverIRQHandler
    bx    r0
    .size CAN3_IRQHandler, . - CAN3_IRQHandler

    .align 1
    .thumb_func
    .weak CAN3_ERROR_IRQHandler
    .type CAN3_ERROR_IRQHandler, %function
CAN3_ERROR_IRQHandler:
    ldr   r0,=CAN3_ERROR_DriverIRQHandler
    bx    r0
    .size CAN3_ERROR_IRQHandler, . - CAN3_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI5_IRQHandler
    .type LPSPI5_IRQHandler, %function
LPSPI5_IRQHandler:
    ldr   r0,=LPSPI5_DriverIRQHandler
    bx    r0
    .size LPSPI5_IRQHandler, . - LPSPI5_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI6_IRQHandler
    .type LPSPI6_IRQHandler, %function
LPSPI6_IRQHandler:
    ldr   r0,=LPSPI6_DriverIRQHandler
    bx    r0
    .size LPSPI6_IRQHandler, . - LPSPI6_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART7_IRQHandler
    .type LPUART7_IRQHandler, %function
LPUART7_IRQHandler:
    ldr   r0,=LPUART7_DriverIRQHandler
    bx    r0
    .size LPUART7_IRQHandler, . - LPUART7_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART8_IRQHandler
    .type LPUART8_IRQHandler, %function
LPUART8_IRQHandler:
    ldr   r0,=LPUART8_DriverIRQHandler
    bx    r0
    .size LPUART8_IRQHandler, . - LPUART8_IRQHandler

    .align 1
    .thumb_func
    .weak SAI2_IRQHandler
    .type SAI2_IRQHandler, %function
SAI2_IRQHandler:
    ldr   r0,=SAI2_DriverIRQHandler
    bx    r0
    .size SAI2_IRQHandler, . - SAI2_IRQHandler

    .align 1
    .thumb_func
    .weak SAI3_IRQHandler
    .type SAI3_IRQHandler, %function
SAI3_IRQHandler:
    ldr   r0,=SAI3_DriverIRQHandler
    bx    r0
    .size SAI3_IRQHandler, . - SAI3_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXSPI_SLV_IRQHandler
    .type FLEXSPI_SLV_IRQHandler, %function
FLEXSPI_SLV_IRQHandler:
    ldr   r0,=FLEXSPI_SLV_DriverIRQHandler
    bx    r0
    .size FLEXSPI_SLV_IRQHandler, . - FLEXSPI_SLV_IRQHandler

    .align 1
    .thumb_func
    .weak ASRC_IRQHandler
    .type ASRC_IRQHandler, %function
ASRC_IRQHandler:
    ldr   r0,=ASRC_DriverIRQHandler
    bx    r0
    .size ASRC_IRQHandler, . - ASRC_IRQHandler


/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro def_irq_handler  handler_name
    .weak \handler_name
    .set  \handler_name, DefaultISR
    .endm

/* Exception Handlers */
    def_irq_handler    MemManage_Handler
    def_irq_handler    BusFault_Handler
    def_irq_handler    UsageFault_Handler
    def_irq_handler    DebugMon_Handler
    def_irq_handler    TMR1_IRQHandler
    def_irq_handler    DAP_IRQHandler
    def_irq_handler    M7_CTI_TRIGGER_OUTPUT_IRQHandler
    def_irq_handler    M33_CTI_TRIGGER_OUTPUT_IRQHandler
    def_irq_handler    TMR5_IRQHandler
    def_irq_handler    TMR6_IRQHandler
    def_irq_handler    TMR7_IRQHandler
    def_irq_handler    TMR8_IRQHandler
    def_irq_handler    CAN1_DriverIRQHandler
    def_irq_handler    CAN1_ERROR_DriverIRQHandler
    def_irq_handler    GPIO1_0_IRQHandler
    def_irq_handler    GPIO1_1_IRQHandler
    def_irq_handler    I3C1_DriverIRQHandler
    def_irq_handler    LPI2C1_DriverIRQHandler
    def_irq_handler    LPI2C2_DriverIRQHandler
    def_irq_handler    LPIT1_IRQHandler
    def_irq_handler    LPSPI1_DriverIRQHandler
    def_irq_handler    LPSPI2_DriverIRQHandler
    def_irq_handler    LPTMR1_IRQHandler
    def_irq_handler    LPUART1_DriverIRQHandler
    def_irq_handler    LPUART2_DriverIRQHandler
    def_irq_handler    MU1_IRQHandler
    def_irq_handler    MU2_IRQHandler
    def_irq_handler    PWM1_FAULT_IRQHandler
    def_irq_handler    PWM1_0_IRQHandler
    def_irq_handler    PWM1_1_IRQHandler
    def_irq_handler    PWM1_2_IRQHandler
    def_irq_handler    PWM1_3_IRQHandler
    def_irq_handler    EDGELOCK_TRUST_MUA_RX_FULL_IRQHandler
    def_irq_handler    EDGELOCK_TRUST_MUA_TX_EMPTY_IRQHandler
    def_irq_handler    EDGELOCK_APPS_CORE_MUA_RX_FULL_IRQHandler
    def_irq_handler    EDGELOCK_APPS_CORE_MUA_TX_EMPTY_IRQHandler
    def_irq_handler    EDGELOCK_REALTIME_CORE_MUA_RX_FULL_IRQHandler
    def_irq_handler    EDGELOCK_REALTIME_CORE_MUA_TX_EMPTY_IRQHandler
    def_irq_handler    EDGELOCK_SECURE_IRQHandler
    def_irq_handler    EDGELOCK_NONSECURE_IRQHandler
    def_irq_handler    TPM1_IRQHandler
    def_irq_handler    TPM2_IRQHandler
    def_irq_handler    RTWDOG1_IRQHandler
    def_irq_handler    RTWDOG2_IRQHandler
    def_irq_handler    TRDC_MGR_AON_IRQHandler
    def_irq_handler    PDM_HWVAD_EVENT_DriverIRQHandler
    def_irq_handler    PDM_HWVAD_ERROR_DriverIRQHandler
    def_irq_handler    PDM_EVENT_DriverIRQHandler
    def_irq_handler    PDM_ERROR_DriverIRQHandler
    def_irq_handler    SAI1_DriverIRQHandler
    def_irq_handler    CM33_PS_IRQHandler
    def_irq_handler    CM33_TCM_ECC_IRQHandler
    def_irq_handler    CM33_TCM_ERROR_IRQHandler
    def_irq_handler    CM7_TCM_ECC_IRQHandler
    def_irq_handler    CM7_TCM_ERROR_IRQHandler
    def_irq_handler    CAN2_DriverIRQHandler
    def_irq_handler    CAN2_ERROR_DriverIRQHandler
    def_irq_handler    FLEXIO1_DriverIRQHandler
    def_irq_handler    FLEXIO2_DriverIRQHandler
    def_irq_handler    FLEXSPI1_DriverIRQHandler
    def_irq_handler    FLEXSPI2_DriverIRQHandler
    def_irq_handler    GPIO2_0_IRQHandler
    def_irq_handler    GPIO2_1_IRQHandler
    def_irq_handler    GPIO3_0_IRQHandler
    def_irq_handler    GPIO3_1_IRQHandler
    def_irq_handler    I3C2_DriverIRQHandler
    def_irq_handler    LPI2C3_DriverIRQHandler
    def_irq_handler    LPI2C4_DriverIRQHandler
    def_irq_handler    LPIT2_IRQHandler
    def_irq_handler    LPSPI3_DriverIRQHandler
    def_irq_handler    LPSPI4_DriverIRQHandler
    def_irq_handler    LPTMR2_IRQHandler
    def_irq_handler    LPUART3_DriverIRQHandler
    def_irq_handler    LPUART4_DriverIRQHandler
    def_irq_handler    LPUART5_DriverIRQHandler
    def_irq_handler    LPUART6_DriverIRQHandler
    def_irq_handler    Reserved88_IRQHandler
    def_irq_handler    BBNSM_IRQHandler
    def_irq_handler    SYS_CTR1_IRQHandler
    def_irq_handler    TPM3_IRQHandler
    def_irq_handler    TPM4_IRQHandler
    def_irq_handler    TPM5_IRQHandler
    def_irq_handler    TPM6_IRQHandler
    def_irq_handler    RTWDOG3_IRQHandler
    def_irq_handler    RTWDOG4_IRQHandler
    def_irq_handler    RTWDOG5_IRQHandler
    def_irq_handler    TRDC_MGR_WKUP_IRQHandler
    def_irq_handler    TMPSNS_INT_IRQHandler
    def_irq_handler    BBSM_IRQHandler
    def_irq_handler    LDO_AON_ANA_IRQHandler
    def_irq_handler    USDHC1_DriverIRQHandler
    def_irq_handler    USDHC2_DriverIRQHandler
    def_irq_handler    TRDC_MGR_MEGA_IRQHandler
    def_irq_handler    SFA_IRQHandler
    def_irq_handler    LDO_AON_DIG_IRQHandler
    def_irq_handler    MECC1_IRQHandler
    def_irq_handler    MECC2_IRQHandler
    def_irq_handler    ADC1_IRQHandler
    def_irq_handler    DMA_ERROR_DriverIRQHandler
    def_irq_handler    DMA3_CH0_DriverIRQHandler
    def_irq_handler    DMA3_CH1_DriverIRQHandler
    def_irq_handler    DMA3_CH2_DriverIRQHandler
    def_irq_handler    DMA3_CH3_DriverIRQHandler
    def_irq_handler    DMA3_CH4_DriverIRQHandler
    def_irq_handler    DMA3_CH5_DriverIRQHandler
    def_irq_handler    DMA3_CH6_DriverIRQHandler
    def_irq_handler    DMA3_CH7_DriverIRQHandler
    def_irq_handler    DMA3_CH8_DriverIRQHandler
    def_irq_handler    DMA3_CH9_DriverIRQHandler
    def_irq_handler    DMA3_CH10_DriverIRQHandler
    def_irq_handler    DMA3_CH11_DriverIRQHandler
    def_irq_handler    DMA3_CH12_DriverIRQHandler
    def_irq_handler    DMA3_CH13_DriverIRQHandler
    def_irq_handler    DMA3_CH14_DriverIRQHandler
    def_irq_handler    DMA3_CH15_DriverIRQHandler
    def_irq_handler    DMA3_CH16_DriverIRQHandler
    def_irq_handler    DMA3_CH17_DriverIRQHandler
    def_irq_handler    DMA3_CH18_DriverIRQHandler
    def_irq_handler    DMA3_CH19_DriverIRQHandler
    def_irq_handler    DMA3_CH20_DriverIRQHandler
    def_irq_handler    DMA3_CH21_DriverIRQHandler
    def_irq_handler    DMA3_CH22_DriverIRQHandler
    def_irq_handler    DMA3_CH23_DriverIRQHandler
    def_irq_handler    DMA3_CH24_DriverIRQHandler
    def_irq_handler    DMA3_CH25_DriverIRQHandler
    def_irq_handler    DMA3_CH26_DriverIRQHandler
    def_irq_handler    DMA3_CH27_DriverIRQHandler
    def_irq_handler    DMA3_CH28_DriverIRQHandler
    def_irq_handler    DMA3_CH29_DriverIRQHandler
    def_irq_handler    DMA3_CH30_DriverIRQHandler
    def_irq_handler    DMA3_CH31_DriverIRQHandler
    def_irq_handler    DMA4_ERROR_DriverIRQHandler
    def_irq_handler    DMA4_CH0_CH1_CH32_CH33_DriverIRQHandler
    def_irq_handler    DMA4_CH2_CH3_CH34_CH35_DriverIRQHandler
    def_irq_handler    DMA4_CH4_CH5_CH36_CH37_DriverIRQHandler
    def_irq_handler    DMA4_CH6_CH7_CH38_CH39_DriverIRQHandler
    def_irq_handler    DMA4_CH8_CH9_CH40_CH41_DriverIRQHandler
    def_irq_handler    DMA4_CH10_CH11_CH42_CH43_DriverIRQHandler
    def_irq_handler    DMA4_CH12_CH13_CH44_CH45_DriverIRQHandler
    def_irq_handler    DMA4_CH14_CH15_CH46_CH47_DriverIRQHandler
    def_irq_handler    DMA4_CH16_CH17_CH48_CH49_DriverIRQHandler
    def_irq_handler    DMA4_CH18_CH19_CH50_CH51_DriverIRQHandler
    def_irq_handler    DMA4_CH20_CH21_CH52_CH53_DriverIRQHandler
    def_irq_handler    DMA4_CH22_CH23_CH54_CH55_DriverIRQHandler
    def_irq_handler    DMA4_CH24_CH25_CH56_CH57_DriverIRQHandler
    def_irq_handler    DMA4_CH26_CH27_CH58_CH59_DriverIRQHandler
    def_irq_handler    DMA4_CH28_CH29_CH60_CH61_DriverIRQHandler
    def_irq_handler    DMA4_CH30_CH31_CH62_CH63_DriverIRQHandler
    def_irq_handler    XBAR1_CH0_CH1_IRQHandler
    def_irq_handler    XBAR1_CH2_CH3_IRQHandler
    def_irq_handler    SINC3_CH0_CH1_CH2_CH3_IRQHandler
    def_irq_handler    EWM_IRQHandler
    def_irq_handler    SEMC_IRQHandler
    def_irq_handler    LPIT3_IRQHandler
    def_irq_handler    LPTMR3_IRQHandler
    def_irq_handler    TMR4_IRQHandler
    def_irq_handler    LPI2C5_DriverIRQHandler
    def_irq_handler    LPI2C6_DriverIRQHandler
    def_irq_handler    SAI4_DriverIRQHandler
    def_irq_handler    SPDIF_DriverIRQHandler
    def_irq_handler    LPUART9_DriverIRQHandler
    def_irq_handler    LPUART10_DriverIRQHandler
    def_irq_handler    LPUART11_DriverIRQHandler
    def_irq_handler    LPUART12_DriverIRQHandler
    def_irq_handler    INTG_BOOTROM_DEBUG_CTRL_IRQHandler
    def_irq_handler    EDGELOCK_REQ1_IRQHandler
    def_irq_handler    EDGELOCK_REQ2_IRQHandler
    def_irq_handler    EDGELOCK_REQ3_IRQHandler
    def_irq_handler    TMR3_IRQHandler
    def_irq_handler    JTAGC_IRQHandler
    def_irq_handler    M33_SYSRESET_REQ_IRQHandler
    def_irq_handler    M33_LOCKUP_IRQHandler
    def_irq_handler    M7_SYSRESET_REQ_IRQHandler
    def_irq_handler    M7_LOCKUP_IRQHandler
    def_irq_handler    PWM2_FAULT_IRQHandler
    def_irq_handler    PWM2_0_IRQHandler
    def_irq_handler    PWM2_1_IRQHandler
    def_irq_handler    PWM2_2_IRQHandler
    def_irq_handler    PWM2_3_IRQHandler
    def_irq_handler    PWM3_FAULT_IRQHandler
    def_irq_handler    PWM3_0_IRQHandler
    def_irq_handler    PWM3_1_IRQHandler
    def_irq_handler    PWM3_2_IRQHandler
    def_irq_handler    PWM3_3_IRQHandler
    def_irq_handler    PWM4_FAULT_IRQHandler
    def_irq_handler    PWM4_0_IRQHandler
    def_irq_handler    PWM4_1_IRQHandler
    def_irq_handler    PWM4_2_IRQHandler
    def_irq_handler    PWM4_3_IRQHandler
    def_irq_handler    EQDC1_IRQHandler
    def_irq_handler    EQDC2_IRQHandler
    def_irq_handler    EQDC3_IRQHandler
    def_irq_handler    EQDC4_IRQHandler
    def_irq_handler    ADC2_IRQHandler
    def_irq_handler    DCDC_IRQHandler
    def_irq_handler    CAN3_DriverIRQHandler
    def_irq_handler    CAN3_ERROR_DriverIRQHandler
    def_irq_handler    DAC_IRQHandler
    def_irq_handler    LPSPI5_DriverIRQHandler
    def_irq_handler    LPSPI6_DriverIRQHandler
    def_irq_handler    LPUART7_DriverIRQHandler
    def_irq_handler    LPUART8_DriverIRQHandler
    def_irq_handler    SAI2_DriverIRQHandler
    def_irq_handler    SAI3_DriverIRQHandler
    def_irq_handler    ACMP1_IRQHandler
    def_irq_handler    ACMP2_IRQHandler
    def_irq_handler    ACMP3_IRQHandler
    def_irq_handler    ACMP4_IRQHandler
    def_irq_handler    CM7_PS_IRQHandler
    def_irq_handler    CM7_MCM_IRQHandler
    def_irq_handler    CM33_MCM_IRQHandler
    def_irq_handler    ECAT_INT_IRQHandler
    def_irq_handler    SAFETY_CLK_MON_IRQHandler
    def_irq_handler    GPT1_IRQHandler
    def_irq_handler    GPT2_IRQHandler
    def_irq_handler    KPP_IRQHandler
    def_irq_handler    USBPHY1_IRQHandler
    def_irq_handler    USBPHY2_IRQHandler
    def_irq_handler    USB_OTG2_IRQHandler
    def_irq_handler    USB_OTG1_IRQHandler
    def_irq_handler    FLEXSPI_SLV_DriverIRQHandler
    def_irq_handler    NETC_IRQHandler
    def_irq_handler    MSGINTR1_IRQHandler
    def_irq_handler    MSGINTR2_IRQHandler
    def_irq_handler    MSGINTR3_IRQHandler
    def_irq_handler    MSGINTR4_IRQHandler
    def_irq_handler    MSGINTR5_IRQHandler
    def_irq_handler    MSGINTR6_IRQHandler
    def_irq_handler    SINC1_CH0_IRQHandler
    def_irq_handler    SINC1_CH1_IRQHandler
    def_irq_handler    SINC1_CH2_IRQHandler
    def_irq_handler    SINC1_CH3_IRQHandler
    def_irq_handler    SINC2_CH0_IRQHandler
    def_irq_handler    SINC2_CH1_IRQHandler
    def_irq_handler    SINC2_CH2_IRQHandler
    def_irq_handler    SINC2_CH3_IRQHandler
    def_irq_handler    GPIO4_IRQHandler
    def_irq_handler    TMR2_IRQHandler
    def_irq_handler    GPIO5_IRQHandler
    def_irq_handler    ASRC_DriverIRQHandler
    def_irq_handler    GPIO6_IRQHandler
    def_irq_handler    DBG_TRACE_IRQHandler
    def_irq_handler    ECAT_RST_OUT_IRQHandler

    .end
