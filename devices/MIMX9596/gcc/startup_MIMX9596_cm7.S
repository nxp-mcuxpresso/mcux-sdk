/* ------------------------------------------------------------------------- */
/*  @file:    startup_MIMX9596_cm7.s                                         */
/*  @purpose: CMSIS Cortex-M7 Core Device Startup File                       */
/*            MIMX9596_cm7                                                   */
/*  @version: 1.0                                                            */
/*  @date:    2023-1-10                                                      */
/*  @build:   b240109                                                        */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright 1997-2016 Freescale Semiconductor, Inc.                         */
/* Copyright 2016-2024 NXP                                                   */
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
    .long   Reserved16_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved17_IRQHandler                           /* DAP interrupt*/
    .long   Reserved18_IRQHandler                           /* CTI trigger outputs from CM7 platform*/
    .long   Reserved19_IRQHandler                           /* CTI trigger outputs from CM33 platform*/
    .long   Reserved20_IRQHandler                           /* CTI trigger outputs from CA55 platform*/
    .long   Reserved21_IRQHandler                           /* Performance Unit Interrupts from CA55 platform*/
    .long   Reserved22_IRQHandler                           /* ECC error from CA55 platform cache*/
    .long   Reserved23_IRQHandler                           /* 1-bit or 2-bit ECC or Parity error from CA55 platform cache*/
    .long   CAN1_IRQHandler                                 /* CAN1 interrupt*/
    .long   CAN1_ERROR_IRQHandler                           /* CAN1 error interrupt*/
    .long   Reserved26_IRQHandler                           /* General Purpose Input/Output 1 interrupt 0*/
    .long   Reserved27_IRQHandler                           /* General Purpose Input/Output 1 interrupt 1*/
    .long   I3C1_IRQHandler                                 /* Improved Inter-Integrated Circuit 1 interrupt*/
    .long   LPI2C1_IRQHandler                               /* Low Power Inter-Integrated Circuit module 1*/
    .long   LPI2C2_IRQHandler                               /* Low Power Inter-Integrated Circuit module 2*/
    .long   LPIT1_IRQHandler                                /* Low Power Periodic Interrupt Timer 1*/
    .long   LPSPI1_IRQHandler                               /* Low Power Serial Peripheral Interface 1*/
    .long   LPSPI2_IRQHandler                               /* Low Power Serial Peripheral Interface 2*/
    .long   LPTMR1_IRQHandler                               /* Low Power Timer 1*/
    .long   LPUART1_IRQHandler                              /* Low Power UART 1*/
    .long   LPUART2_IRQHandler                              /* Low Power UART 2*/
    .long   Reserved37_IRQHandler                           /* AONMIX Sentinel MU0 SideA interrupt*/
    .long   Reserved38_IRQHandler                           /* AONMIX Sentinel MU1 SideA interrupt*/
    .long   Reserved39_IRQHandler                           /* AONMIX Sentinel MU2 SideA interrupt*/
    .long   Reserved40_IRQHandler                           /* AONMIX Sentinel MU3 SideA interrupt*/
    .long   Reserved41_IRQHandler                           /* AONMIX Sentinel MU4 SideA interrupt*/
    .long   Reserved42_IRQHandler                           /* AONMIX Sentinel MU5 SideA interrupt*/
    .long   V2X_FH_APCH0_IRQHandler                         /* V2X-FH MU APCH0 (APP0) interrupt*/
    .long   V2X_FH_APHSM1_IRQHandler                        /* V2X-FH MU APHSM1 (HSM1) interrupt*/
    .long   TPM1_IRQHandler                                 /* Timer PWM module 1*/
    .long   TPM2_IRQHandler                                 /* Timer PWM module 2*/
    .long   WDOG1_IRQHandler                                /* Watchdog 1 Interrupt*/
    .long   WDOG2_IRQHandler                                /* Watchdog 2 Interrupt*/
    .long   TRDC_MGR_A_IRQHandler                           /* AONMIX TRDC transfer error interrupt*/
    .long   SAI1_IRQHandler                                 /* Serial Audio Interface 1*/
    .long   Reserved51_IRQHandler                           /* AONMIX M33 PS Error*/
    .long   Reserved52_IRQHandler                           /* AONMIX M33 TCM Error interrupt*/
    .long   Reserved53_IRQHandler                           /* M7MIX ECC Multi-bit error*/
    .long   CAN2_IRQHandler                                 /* CAN2 interrupt*/
    .long   CAN2_ERROR_IRQHandler                           /* CAN2 error interrupt*/
    .long   CAN3_IRQHandler                                 /* CAN3 interrupt*/
    .long   CAN3_ERROR_IRQHandler                           /* CAN3 error interrupt*/
    .long   CAN4_IRQHandler                                 /* CAN4 interrupt*/
    .long   CAN4_ERROR_IRQHandler                           /* CAN4 error interrupt*/
    .long   CAN5_IRQHandler                                 /* CAN5 interrupt*/
    .long   CAN5_ERROR_IRQHandler                           /* CAN5 error interrupt*/
    .long   FLEXIO1_IRQHandler                              /* Flexible IO 1 interrupt*/
    .long   FLEXIO2_IRQHandler                              /* Flexible IO 2 interrupt*/
    .long   FlexSPI1_IRQHandler                             /* FlexSPI controller interface interrupt 1*/
    .long   Reserved65_IRQHandler                           /* General Purpose Input/Output 2 interrupt 0*/
    .long   Reserved66_IRQHandler                           /* General Purpose Input/Output 2 interrupt 1*/
    .long   Reserved67_IRQHandler                           /* General Purpose Input/Output 3 interrupt 0*/
    .long   Reserved68_IRQHandler                           /* General Purpose Input/Output 3 interrupt 1*/
    .long   Reserved69_IRQHandler                           /* General Purpose Input/Output 4 interrupt 0*/
    .long   Reserved70_IRQHandler                           /* General Purpose Input/Output 4 interrupt 1*/
    .long   Reserved71_IRQHandler                           /* General Purpose Input/Output 5 interrupt 0*/
    .long   Reserved72_IRQHandler                           /* General Purpose Input/Output 5 interrupt 1*/
    .long   I3C2_IRQHandler                                 /* Improved Inter-Integrated Circuit 2 interrupt*/
    .long   LPI2C3_IRQHandler                               /* Low Power Inter-Integrated Circuit module 3*/
    .long   LPI2C4_IRQHandler                               /* Low Power Inter-Integrated Circuit module 4*/
    .long   LPIT2_IRQHandler                                /* Low Power Periodic Interrupt Timer 2*/
    .long   LPSPI3_IRQHandler                               /* Low Power Serial Peripheral Interface 3*/
    .long   LPSPI4_IRQHandler                               /* Low Power Serial Peripheral Interface 4*/
    .long   LPTMR2_IRQHandler                               /* Low Power Timer 2*/
    .long   LPUART3_IRQHandler                              /* Low Power UART 3*/
    .long   LPUART4_IRQHandler                              /* Low Power UART 4*/
    .long   LPUART5_IRQHandler                              /* Low Power UART 5*/
    .long   LPUART6_IRQHandler                              /* Low Power UART 6*/
    .long   LPUART7_IRQHandler                              /* Low Power UART 7*/
    .long   LPUART8_IRQHandler                              /* Low Power UART 8*/
    .long   Reserved86_IRQHandler                           /* MTR Master error interrupt*/
    .long   Reserved87_IRQHandler                           /* BBNSM Non-Secure interrupt*/
    .long   Reserved88_IRQHandler                           /* System Counter compare interrupt*/
    .long   TPM3_IRQHandler                                 /* Timer PWM module 3*/
    .long   TPM4_IRQHandler                                 /* Timer PWM module 4*/
    .long   TPM5_IRQHandler                                 /* Timer PWM module 5*/
    .long   TPM6_IRQHandler                                 /* Timer PWM module 6*/
    .long   WDOG3_IRQHandler                                /* Watchdog 3 Interrupt*/
    .long   WDOG4_IRQHandler                                /* Watchdog 4 Interrupt*/
    .long   WDOG5_IRQHandler                                /* Watchdog 5 Interrupt*/
    .long   TMPSNS1_THR1_IRQHandler                         /* ANAMIX TempSensor non-secure interrupt from Threshold 1*/
    .long   TMPSNS1_THR2_IRQHandler                         /* ANAMIX TempSensor non-secure interrupt from Threshold 2*/
    .long   TMPSNS1_DRDY_IRQHandler                         /* ANAMIX TempSensor non-secure data ready interrupt*/
    .long   TMPSNS2_THR1_IRQHandler                         /* CORTEXAMIX TempSensor non-secure interrupt from Threshold 1*/
    .long   TMPSNS2_THR2_IRQHandler                         /* CORTEXAMIX TempSensor non-secure interrupt from Threshold 2*/
    .long   TMPSNS2_DRDY_IRQHandler                         /* CORTEXAMIX TempSensor non-secure data ready interrupt*/
    .long   uSDHC1_IRQHandler                               /* ultra Secure Digital Host Controller interrupt 1*/
    .long   uSDHC2_IRQHandler                               /* ultra Secure Digital Host Controller interrupt 2*/
    .long   Reserved104_IRQHandler                          /* MEGAMIX TRDC transfer error interrupt*/
    .long   Reserved105_IRQHandler                          /* NIC_WRAPPER TRDC transfer error interrupt*/
    .long   Reserved106_IRQHandler                          /* NOCMIX TRDC transfer error interrupt*/
    .long   Reserved107_IRQHandler                          /* DRAM controller Performance Monitor Interrupt*/
    .long   Reserved108_IRQHandler                          /* DRAM controller Critical Interrupt*/
    .long   Reserved109_IRQHandler                          /* DRAM Phy Critical Interrupt*/
    .long   Reserved110_IRQHandler                          /* Reserved*/
    .long   DMA3_ERROR_IRQHandler                           /* eDMA1 error interrupt*/
    .long   DMA3_0_IRQHandler                               /* eDMA1 channel 0 interrupt*/
    .long   DMA3_1_IRQHandler                               /* eDMA1 channel 1 interrupt*/
    .long   DMA3_2_IRQHandler                               /* eDMA1 channel 2 interrupt*/
    .long   DMA3_3_IRQHandler                               /* eDMA1 channel 3 interrupt*/
    .long   DMA3_4_IRQHandler                               /* eDMA1 channel 4 interrupt*/
    .long   DMA3_5_IRQHandler                               /* eDMA1 channel 5 interrupt*/
    .long   DMA3_6_IRQHandler                               /* eDMA1 channel 6 interrupt*/
    .long   DMA3_7_IRQHandler                               /* eDMA1 channel 7 interrupt*/
    .long   DMA3_8_IRQHandler                               /* eDMA1 channel 8 interrupt*/
    .long   DMA3_9_IRQHandler                               /* eDMA1 channel 9 interrupt*/
    .long   DMA3_10_IRQHandler                              /* eDMA1 channel 10 interrupt*/
    .long   DMA3_11_IRQHandler                              /* eDMA1 channel 11 interrupt*/
    .long   DMA3_12_IRQHandler                              /* eDMA1 channel 12 interrupt*/
    .long   DMA3_13_IRQHandler                              /* eDMA1 channel 13 interrupt*/
    .long   DMA3_14_IRQHandler                              /* eDMA1 channel 14 interrupt*/
    .long   DMA3_15_IRQHandler                              /* eDMA1 channel 15 interrupt*/
    .long   DMA3_16_IRQHandler                              /* eDMA1 channel 16 interrupt*/
    .long   DMA3_17_IRQHandler                              /* eDMA1 channel 17 interrupt*/
    .long   DMA3_18_IRQHandler                              /* eDMA1 channel 18 interrupt*/
    .long   DMA3_19_IRQHandler                              /* eDMA1 channel 19 interrupt*/
    .long   DMA3_20_IRQHandler                              /* eDMA1 channel 20 interrupt*/
    .long   DMA3_21_IRQHandler                              /* eDMA1 channel 21 interrupt*/
    .long   DMA3_22_IRQHandler                              /* eDMA1 channel 22 interrupt*/
    .long   DMA3_23_IRQHandler                              /* eDMA1 channel 23 interrupt*/
    .long   DMA3_24_IRQHandler                              /* eDMA1 channel 24 interrupt*/
    .long   DMA3_25_IRQHandler                              /* eDMA1 channel 25 interrupt*/
    .long   DMA3_26_IRQHandler                              /* eDMA1 channel 26 interrupt*/
    .long   DMA3_27_IRQHandler                              /* eDMA1 channel 27 interrupt*/
    .long   DMA3_28_IRQHandler                              /* eDMA1 channel 28 interrupt*/
    .long   DMA3_29_IRQHandler                              /* eDMA1 channel 29 interrupt*/
    .long   DMA3_30_IRQHandler                              /* eDMA1 channel 30 interrupt*/
    .long   DMA5_2_ERROR_IRQHandler                         /* eDMA2 error interrupt*/
    .long   DMA5_2_0_1_IRQHandler                           /* eDMA2 channel 0/1 interrupt*/
    .long   DMA5_2_2_3_IRQHandler                           /* eDMA2 channel 2/3 interrupt*/
    .long   DMA5_2_4_5_IRQHandler                           /* eDMA2 channel 4/5 interrupt*/
    .long   DMA5_2_6_7_IRQHandler                           /* eDMA2 channel 6/7 interrupt*/
    .long   DMA5_2_8_9_IRQHandler                           /* eDMA2 channel 8/9 interrupt*/
    .long   DMA5_2_10_11_IRQHandler                         /* eDMA2 channel 10/11 interrupt*/
    .long   DMA5_2_12_13_IRQHandler                         /* eDMA2 channel 12/13 interrupt*/
    .long   DMA5_2_14_15_IRQHandler                         /* eDMA2 channel 14/15 interrupt*/
    .long   DMA5_2_16_17_IRQHandler                         /* eDMA2 channel 16/17 interrupt*/
    .long   DMA5_2_18_19_IRQHandler                         /* eDMA2 channel 18/19 interrupt*/
    .long   DMA5_2_20_21_IRQHandler                         /* eDMA2 channel 20/21 interrupt*/
    .long   DMA5_2_22_23_IRQHandler                         /* eDMA2 channel 22/23 interrupt*/
    .long   DMA5_2_24_25_IRQHandler                         /* eDMA2 channel 24/25 interrupt*/
    .long   DMA5_2_26_27_IRQHandler                         /* eDMA2 channel 26/27 interrupt*/
    .long   DMA5_2_28_29_IRQHandler                         /* eDMA2 channel 28/29 interrupt*/
    .long   DMA5_2_30_31_IRQHandler                         /* eDMA2 channel 30/31 interrupt*/
    .long   DMA5_2_32_33_IRQHandler                         /* eDMA2 channel 32/33 interrupt*/
    .long   DMA5_2_34_35_IRQHandler                         /* eDMA2 channel 34/35 interrupt*/
    .long   DMA5_2_36_37_IRQHandler                         /* eDMA2 channel 36/37 interrupt*/
    .long   DMA5_2_38_39_IRQHandler                         /* eDMA2 channel 38/39 interrupt*/
    .long   DMA5_2_40_41_IRQHandler                         /* eDMA2 channel 40/41 interrupt*/
    .long   DMA5_2_42_43_IRQHandler                         /* eDMA2 channel 42/43 interrupt*/
    .long   DMA5_2_44_45_IRQHandler                         /* eDMA2 channel 44/45 interrupt*/
    .long   DMA5_2_46_47_IRQHandler                         /* eDMA2 channel 46/47 interrupt*/
    .long   DMA5_2_48_49_IRQHandler                         /* eDMA2 channel 48/49 interrupt*/
    .long   DMA5_2_50_51_IRQHandler                         /* eDMA2 channel 50/51 interrupt*/
    .long   DMA5_2_52_53_IRQHandler                         /* eDMA2 channel 52/53 interrupt*/
    .long   DMA5_2_54_55_IRQHandler                         /* eDMA2 channel 54/55 interrupt*/
    .long   DMA5_2_56_57_IRQHandler                         /* eDMA2 channel 56/57 interrupt*/
    .long   DMA5_2_58_59_IRQHandler                         /* eDMA2 channel 58/59 interrupt*/
    .long   DMA5_2_60_61_IRQHandler                         /* eDMA2 channel 60/61 interrupt*/
    .long   DMA5_2_62_63_IRQHandler                         /* eDMA2 channel 62/63 interrupt*/
    .long   Reserved176_IRQHandler                          /* Sentinel Group 1 reset source if no s500 reference clock is detected. Output synchronized to 32khz clk.*/
    .long   Reserved177_IRQHandler                          /* Sentinel Group 2 reset source s500 reference clock is not detected or too slow. Output synchronized to ref1_clk.*/
    .long   Reserved178_IRQHandler                          /* Sentinel Group 2 reset source s500 reference clock is not detected or too slow. Output synchronized to ref1_clk.*/
    .long   Reserved179_IRQHandler                          /* JTAGSW DAP MDM-AP SRC reset source*/
    .long   Reserved180_IRQHandler                          /* JTAGC SRC reset source*/
    .long   Reserved181_IRQHandler                          /* CM33 SYSREQRST SRC reset source*/
    .long   Reserved182_IRQHandler                          /* CM33 LOCKUP SRC reset source*/
    .long   Reserved183_IRQHandler                          /* CM7 SYSREQRST SRC reset source*/
    .long   Reserved184_IRQHandler                          /* CM7 LOCKUP SRC reset source*/
    .long   SAI2_IRQHandler                                 /* Serial Audio Interface 2*/
    .long   SAI3_IRQHandler                                 /* Serial Audio Interface 3*/
    .long   SAI4_IRQHandler                                 /* Serial Audio Interface 4*/
    .long   SAI5_IRQHandler                                 /* Serial Audio Interface 5*/
    .long   Reserved189_IRQHandler                          /* USB-1 Wake-up Interrupt*/
    .long   Reserved190_IRQHandler                          /* USB-2 Wake-up Interrupt*/
    .long   USB1_IRQHandler                                 /* USB-1 Interrupt*/
    .long   USB2_IRQHandler                                 /* USB-2 Interrupt*/
    .long   LPSPI5_IRQHandler                               /* Low Power Serial Peripheral Interface 5*/
    .long   LPSPI6_IRQHandler                               /* Low Power Serial Peripheral Interface 6*/
    .long   LPSPI7_IRQHandler                               /* Low Power Serial Peripheral Interface 7*/
    .long   LPSPI8_IRQHandler                               /* Low Power Serial Peripheral Interface 8*/
    .long   LPI2C5_IRQHandler                               /* Low Power Inter-Integrated Circuit module 5*/
    .long   LPI2C6_IRQHandler                               /* Low Power Inter-Integrated Circuit module 6*/
    .long   LPI2C7_IRQHandler                               /* Low Power Inter-Integrated Circuit module 7*/
    .long   LPI2C8_IRQHandler                               /* Low Power Inter-Integrated Circuit module 8*/
    .long   PDM_HWVAD_ERROR_IRQHandler                      /* PDM interrupt*/
    .long   PDM_HWVAD_EVENT_IRQHandler                      /* PDM interrupt*/
    .long   PDM_ERROR_IRQHandler                            /* PDM interrupt*/
    .long   PDM_EVENT_IRQHandler                            /* PDM interrupt*/
    .long   Reserved205_IRQHandler                          /* AUDIO XCVR interrupt*/
    .long   Reserved206_IRQHandler                          /* AUDIO XCVR interrupt*/
    .long   uSDHC3_IRQHandler                               /* ultra Secure Digital Host Controller interrupt 3*/
    .long   Reserved208_IRQHandler                          /* OCRAM MECC interrupt*/
    .long   Reserved209_IRQHandler                          /* OCRAM MECC interrupt*/
    .long   Reserved210_IRQHandler                          /* CM33 MCM interrupt*/
    .long   Reserved211_IRQHandler                          /* ANAMIX SFA interrupt*/
    .long   Reserved212_IRQHandler                          /* GIC700 Fault*/
    .long   Reserved213_IRQHandler                          /* GIC700 Error*/
    .long   Reserved214_IRQHandler                          /* GIC700 PMU Counter Overflow*/
    .long   ADC_ER_IRQHandler                               /* ADC interrupt*/
    .long   ADC_WD_IRQHandler                               /* ADC interrupt*/
    .long   ADC_EOC_IRQHandler                              /* ADC interrupt*/
    .long   Reserved218_IRQHandler                          /* s500 glue logic IRQ*/
    .long   Reserved219_IRQHandler                          /* I3C1 wakeup irq after double sync*/
    .long   Reserved220_IRQHandler                          /* I3C2 wakeup irq after double sync*/
    .long   MU5_A_IRQHandler                                /* AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA*/
    .long   MU6_A_IRQHandler                                /* AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA*/
    .long   MU7_B_IRQHandler                                /* WAKEUPMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB*/
    .long   MU8_B_IRQHandler                                /* WAKEUPMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB*/
    .long   Reserved225_IRQHandler                          /* WAKEUPMIX XSPI Responder*/
    .long   Reserved226_IRQHandler                          /* AONMIX FCCU Interrupt Reaction 0*/
    .long   Reserved227_IRQHandler                          /* AONMIX FCCU Interrupt Reaction 1*/
    .long   Reserved228_IRQHandler                          /* AONMIX FCCU Interrupt Reaction 2*/
    .long   Reserved229_IRQHandler                          /* AONMIX STCU Selftest end Interrupt*/
    .long   DISP_IRQSTEER0_IRQHandler                       /* DISPLAYMIX IRQSTEER 0*/
    .long   DISP_IRQSTEER1_IRQHandler                       /* DISPLAYMIX IRQSTEER 1*/
    .long   DISP_IRQSTEER2_IRQHandler                       /* DISPLAYMIX IRQSTEER 2*/
    .long   DISP_IRQSTEER3_IRQHandler                       /* DISPLAYMIX IRQSTEER 3*/
    .long   DISP_IRQSTEER4_IRQHandler                       /* DISPLAYMIX IRQSTEER 4*/
    .long   DISP_IRQSTEER7_IRQHandler                       /* DISPLAYMIX IRQSTEER 7*/
    .long   Reserved236_IRQHandler                          /* CAMERAMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA*/
    .long   ISI_IRQHandler                                  /* CAMERAMIX ISI interrupt Channel 0*/
    .long   Reserved238_IRQHandler                          /* ISP Processing Interrupt - Context 0*/
    .long   Reserved239_IRQHandler                          /* M7MIX MCM interrupt*/
    .long   IRQSTEER_0_IRQHandler                           /* IRQSTEER0 interrupt*/
    .long   IRQSTEER_1_IRQHandler                           /* IRQSTEER1 interrupt*/
    .long   IRQSTEER_2_IRQHandler                           /* IRQSTEER2 interrupt*/
    .long   IRQSTEER_3_IRQHandler                           /* IRQSTEER3 interrupt*/
    .long   IRQSTEER_4_IRQHandler                           /* IRQSTEER4 interrupt*/
    .long   IRQSTEER_5_IRQHandler                           /* IRQSTEER5 interrupt*/
    .long   IRQSTEER_6_IRQHandler                           /* IRQSTEER6 interrupt*/
    .long   IRQSTEER_7_IRQHandler                           /* IRQSTEER7 interrupt*/
    .long   IRQSTEER_8_IRQHandler                           /* IRQSTEER8 interrupt*/
    .long   IRQSTEER_9_IRQHandler                           /* IRQSTEER9 interrupt*/
    .long   MU1_A_IRQHandler                                /* AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA*/
    .long   MU1_B_IRQHandler                                /* AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB*/
    .long   MU2_A_IRQHandler                                /* AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA*/
    .long   MU2_B_IRQHandler                                /* AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB*/
    .long   MU3_A_IRQHandler                                /* AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA*/
    .long   MU3_B_IRQHandler                                /* AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB*/
    .long   MU4_A_IRQHandler                                /* AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA*/
    .long   MU4_B_IRQHandler                                /* AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB*/
    .long   MU5_B_IRQHandler                                /* AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB*/
    .long   MU6_B_IRQHandler                                /* AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB*/
    .long   MU7_A_IRQHandler                                /* WAKEUPMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA*/
    .long   MU8_A_IRQHandler                                /* WAKEUPMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA*/
    .long   MSGINTR1_IRQHandler                             /* MSGINTR Instance 1, Interrupt*/
    .long   MSGINTR2_IRQHandler                             /* MSGINTR Instance 2, Interrupts*/
    .long   Reserved264_IRQHandler                          /* V2X-FH MU APCH1 (APP1) interrupt*/
    .long   Reserved265_IRQHandler                          /* V2X-FH MU APHSM2 (HSM2) interrupt*/
    .long   Reserved266_IRQHandler                          /* CAMERAMIX TRDC transfer error interrupt*/
    .long   Reserved267_IRQHandler                          /* DISPLAYMIX TRDC transfer error interrupt*/
    .long   Reserved268_IRQHandler                          /* NETCMIX TRDC transfer error interrupt*/
    .long   Reserved269_IRQHandler                          /* GPUMIX TRDC transfer error interrupt*/
    .long   Reserved270_IRQHandler                          /* HSIOMIX TRDC transfer error interrupt*/
    .long   Reserved271_IRQHandler                          /* VPUMIX TRDC transfer error interrupt*/
    .long   Reserved272_IRQHandler                          /* AONMIX ERM Single bit corrected ECC Error*/
    .long   Reserved273_IRQHandler                          /* M7MIX ERM Single bit corrected ECC Error*/
    .long   Reserved274_IRQHandler                          /* WAKEUPMIX ERM Single bit corrected ECC Error*/
    .long   Reserved275_IRQHandler                          /* NPUMIX ERM Single bit corrected ECC Error*/
    .long   Reserved276_IRQHandler                          /* WAKEUPMIX ACP EDMA error interrupt*/
    .long   Reserved277_IRQHandler                          /* OCRAM_C ECC multiple bit or address error*/
    .long   Reserved278_IRQHandler                          /* CAMERAMIX Cortex-M0+ Cache write-buffer error*/
    .long   Reserved279_IRQHandler                          /* CAMERAMIX Cortex-M0+ Cache data parity error*/
    .long   Reserved280_IRQHandler                          /* V2X-FH MU APSHE (SHE) interrupt*/
    .long   Reserved281_IRQHandler                          /* V2X-FH MU SCU/APDEBUG (DEBUG) interrupt*/
    .long   DMA5_3_0_1_IRQHandler                           /* eDMA3 channel 0/1 interrupt*/
    .long   DMA5_3_2_3_IRQHandler                           /* eDMA3 channel 2/3 interrupt*/
    .long   DMA5_3_4_5_IRQHandler                           /* eDMA3 channel 4/5 interrupt*/
    .long   DMA5_3_6_7_IRQHandler                           /* eDMA3 channel 6/7 interrupt*/
    .long   DMA5_3_8_9_IRQHandler                           /* eDMA3 channel 8/9 interrupt*/
    .long   DMA5_3_10_11_IRQHandler                         /* eDMA3 channel 10/11 interrupt*/
    .long   DMA5_3_12_13_IRQHandler                         /* eDMA3 channel 12/13 interrupt*/
    .long   DMA5_3_14_15_IRQHandler                         /* eDMA3 channel 14/15 interrupt*/
    .long   DMA5_3_16_17_IRQHandler                         /* eDMA3 channel 16/17 interrupt*/
    .long   DMA5_3_18_19_IRQHandler                         /* eDMA3 channel 18/19 interrupt*/
    .long   DMA5_3_20_21_IRQHandler                         /* eDMA3 channel 20/21 interrupt*/
    .long   DMA5_3_22_23_IRQHandler                         /* eDMA3 channel 22/23 interrupt*/
    .long   DMA5_3_24_25_IRQHandler                         /* eDMA3 channel 24/25 interrupt*/
    .long   DMA5_3_26_27_IRQHandler                         /* eDMA3 channel 26/27 interrupt*/
    .long   DMA5_3_28_29_IRQHandler                         /* eDMA3 channel 29/29 interrupt*/
    .long   DMA5_3_30_31_IRQHandler                         /* eDMA3 channel 30/31 interrupt*/
    .long   DMA5_3_32_33_IRQHandler                         /* eDMA3 channel 32/33 interrupt*/
    .long   DMA5_3_34_35_IRQHandler                         /* eDMA3 channel 34/35 interrupt*/
    .long   DMA5_3_36_37_IRQHandler                         /* eDMA3 channel 36/37 interrupt*/
    .long   DMA5_3_38_39_IRQHandler                         /* eDMA3 channel 38/39 interrupt*/
    .long   DMA5_3_40_41_IRQHandler                         /* eDMA3 channel 40/41 interrupt*/
    .long   DMA5_3_42_43_IRQHandler                         /* eDMA3 channel 42/43 interrupt*/
    .long   DMA5_3_44_45_IRQHandler                         /* eDMA3 channel 44/45 interrupt*/
    .long   DMA5_3_46_47_IRQHandler                         /* eDMA3 channel 46/47 interrupt*/
    .long   DMA5_3_48_49_IRQHandler                         /* eDMA3 channel 48/49 interrupt*/
    .long   DMA5_3_50_51_IRQHandler                         /* eDMA3 channel 50/51 interrupt*/
    .long   DMA5_3_52_53_IRQHandler                         /* eDMA3 channel 52/53 interrupt*/
    .long   DMA5_3_54_55_IRQHandler                         /* eDMA3 channel 54/55 interrupt*/
    .long   DMA5_3_56_57_IRQHandler                         /* eDMA3 channel 56/57 interrupt*/
    .long   DMA5_3_58_59_IRQHandler                         /* eDMA3 channel 58/59 interrupt*/
    .long   DMA5_3_60_61_IRQHandler                         /* eDMA3 channel 60/61 interrupt*/
    .long   DMA5_3_62_63_IRQHandler                         /* eDMA3 channel 62/63 interrupt*/
    .long   Reserved314_IRQHandler                          /* GPUMIX GPU Interrupt*/
    .long   Reserved315_IRQHandler                          /* GPUMIX Job Interrupt*/
    .long   Reserved316_IRQHandler                          /* GPUMIX MMU Interrupt*/
    .long   Reserved317_IRQHandler                          /* Reserved INTERRUPT*/
    .long   Reserved318_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved319_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved320_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved321_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved322_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved323_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved324_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved325_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved326_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved327_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved328_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved329_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved330_IRQHandler                          /* NETC iEPRC PCI INT*/
    .long   Reserved331_IRQHandler                          /* NETC iEPRC PCI INT*/
    .long   Reserved332_IRQHandler                          /* PCIe Controller 1 INTA*/
    .long   Reserved333_IRQHandler                          /* PCIe Controller 1 INTB*/
    .long   Reserved334_IRQHandler                          /* PCIe Controller 1 INTC*/
    .long   Reserved335_IRQHandler                          /* PCIe Controller 1 INTD*/
    .long   Reserved336_IRQHandler                          /* PCIe interrupts*/
    .long   Reserved337_IRQHandler                          /* PCIe Controller EDMA channel interrupt*/
    .long   Reserved338_IRQHandler                          /* PCIe Controller 1 INTA*/
    .long   Reserved339_IRQHandler                          /* PCIe Controller 1 INTB*/
    .long   Reserved340_IRQHandler                          /* PCIe Controller 1 INTC*/
    .long   Reserved341_IRQHandler                          /* PCIe Controller 1 INTD*/
    .long   Reserved342_IRQHandler                          /* PCIe miscellaneous interrupts*/
    .long   Reserved343_IRQHandler                          /* PCIe Controller EDMA channel interrupt*/
    .long   Reserved344_IRQHandler                          /* Wakeup interrupt from CLKREQ#, WAKEUP#, BEACON_DET*/
    .long   Reserved345_IRQHandler                          /* NPUMIX Functional interrupt*/
    .long   Reserved346_IRQHandler                          /* DISPLAYMIX Real-time traffic TBU: Fault Handling RAS Interrupt for a contained error*/
    .long   Reserved347_IRQHandler                          /* DISPLAYMIX Real-time traffic TBU: Error Handling RAS Interrupt for an uncontained error*/
    .long   Reserved348_IRQHandler                          /* DISPLAYMIX Real-time traffic TBU: Critical Error Interrupt for an uncontainable error*/
    .long   Reserved349_IRQHandler                          /* DISPLAYMIX Real-time traffic TBU: PMU Interrupt*/
    .long   Reserved350_IRQHandler                          /* TCU Event queue, secure interrupt*/
    .long   Reserved351_IRQHandler                          /* TCU Event queue, non-secure interrupt*/
    .long   Reserved352_IRQHandler                          /* TCU SYNC complete, non-secure interrupt*/
    .long   Reserved353_IRQHandler                          /* TCU SYNC complete, secure interrupt*/
    .long   Reserved354_IRQHandler                          /* TCU global non-secure interrupt*/
    .long   Reserved355_IRQHandler                          /* TCU global secure interrupt*/
    .long   Reserved356_IRQHandler                          /* TCU fault handling RAS interrupt for a contained error*/
    .long   Reserved357_IRQHandler                          /* TCU error recovery RAS interrupt for an uncontained error*/
    .long   Reserved358_IRQHandler                          /* TCU critical error interrupt, for an uncontainable uncorrected error*/
    .long   Reserved359_IRQHandler                          /* TCU PMU interrupt*/
    .long   Reserved360_IRQHandler                          /* TCU Page Request Interface*/
    .long   Reserved361_IRQHandler                          /* SRC GPC Low Power Handshake Gasket interrupt request for system management*/
    .long   Reserved362_IRQHandler                          /* CAMERAMIX MU Ored of all*/
    .long   Reserved363_IRQHandler                          /* CAMERAMIX MU Ored of all*/
    .long   Reserved364_IRQHandler                          /* CAMERAMIX MU Ored of all*/
    .long   Reserved365_IRQHandler                          /* CAMERAMIX MU Ored of all*/
    .long   Reserved366_IRQHandler                          /* CAMERAMIX MU Ored of all*/
    .long   Reserved367_IRQHandler                          /* CAMERAMIX MU Ored of all*/
    .long   Reserved368_IRQHandler                          /* CAMERAMIX MU Ored of all*/
    .long   Reserved369_IRQHandler                          /* CAMERAMIX MU Ored of all*/
    .long   Reserved370_IRQHandler                          /* CAMERAMIX ISI interrupt Channel 1*/
    .long   Reserved371_IRQHandler                          /* CAMERAMIX ISI interrupt Channel 2*/
    .long   Reserved372_IRQHandler                          /* CAMERAMIX ISI interrupt Channel 3*/
    .long   Reserved373_IRQHandler                          /* CAMERAMIX ISI interrupt Channel 4*/
    .long   Reserved374_IRQHandler                          /* CAMERAMIX ISI interrupt Channel 5*/
    .long   Reserved375_IRQHandler                          /* CAMERAMIX ISI interrupt Channel 6*/
    .long   Reserved376_IRQHandler                          /* CAMERAMIX ISI interrupt Channel 7*/
    .long   DMA5_4_ERROR_IRQHandler                         /* CAMERAMIX EDMA error interrupt*/
    .long   DMA5_4_0_1_IRQHandler                           /* CAMERAMIX EDMA channel 0 interrupt*/
    .long   DMA5_4_2_3_IRQHandler                           /* CAMERAMIX EDMA channel 2 interrupt*/
    .long   DMA5_4_4_5_IRQHandler                           /* CAMERAMIX EDMA channel 4 interrupt*/
    .long   DMA5_4_6_7_IRQHandler                           /* CAMERAMIX EDMA channel 6 interrupt*/
    .long   DMA5_4_8_9_IRQHandler                           /* CAMERAMIX EDMA channel 8 interrupt*/
    .long   DMA5_4_10_11_IRQHandler                         /* CAMERAMIX EDMA channel 10 interrupt*/
    .long   DMA5_4_12_13_IRQHandler                         /* CAMERAMIX EDMA channel 12 interrupt*/
    .long   DMA5_4_14_15_IRQHandler                         /* CAMERAMIX EDMA channel 14 interrupt*/
    .long   DMA5_4_16_17_IRQHandler                         /* CAMERAMIX EDMA channel 16 interrupt*/
    .long   DMA5_4_18_19_IRQHandler                         /* CAMERAMIX EDMA channel 18 interrupt*/
    .long   DMA5_4_20_21_IRQHandler                         /* CAMERAMIX EDMA channel 20 interrupt*/
    .long   DMA5_4_22_23_IRQHandler                         /* CAMERAMIX EDMA channel 22 interrupt*/
    .long   DMA5_4_24_25_IRQHandler                         /* CAMERAMIX EDMA channel 24 interrupt*/
    .long   DMA5_4_26_27_IRQHandler                         /* CAMERAMIX EDMA channel 26 interrupt*/
    .long   DMA5_4_28_29_IRQHandler                         /* CAMERAMIX EDMA channel 28 interrupt*/
    .long   DMA5_4_30_31_IRQHandler                         /* CAMERAMIX EDMA channel 30 interrupt*/
    .long   Reserved394_IRQHandler                          /* CAMERAMIX CSI Formatting Unit 1: Buffer overflow*/
    .long   Reserved395_IRQHandler                          /* CAMERAMIX CSI Formatting Unit 1: Interlaced Error*/
    .long   Reserved396_IRQHandler                          /* CAMERAMIX CSI Formatting Unit 1: Pixel Data Type Error*/
    .long   Reserved397_IRQHandler                          /* CAMERAMIX CSI Formatting Unit 2: Buffer overflow*/
    .long   Reserved398_IRQHandler                          /* CAMERAMIX CSI Formatting Unit 2: Interlaced Error*/
    .long   Reserved399_IRQHandler                          /* CAMERAMIX CSI Formatting Unit 2: Pixel Data Type Error*/
    .long   Reserved400_IRQHandler                          /* CAMERAMIX CSI1*/
    .long   Reserved401_IRQHandler                          /* CAMERAMIX CSI2*/
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

/* DTCM initializaiton in case of ECC error */
    movs    r0, 0
    ldr     r1, =0x20000000
    ldr     r2, =0x2003ffff
.LC3:
    cmp     r1, r2
    dmb     0xf
    itt     lt
    strlt   r0, [r1], #4
    blt     .LC3
/* End of TCM initializaiton */

/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __etext: End of code section, i.e., begin of data sections to copy from.
 *      __data_start__/__data_end__: RAM address range that data should be
 *      __noncachedata_start__/__noncachedata_end__ : none cachable region
 *      copied to. Both must be aligned to 4 bytes boundary.  */

    ldr    r1, =__etext
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

#ifdef __PERFORMANCE_IMPLEMENTATION
/* Here are two copies of loop implementations. First one favors performance
 * and the second one favors code size. Default uses the second one.
 * Define macro "__PERFORMANCE_IMPLEMENTATION" in project to use the first one */
    subs    r3, r2
    ble    .LC1
.LC0:
    subs    r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .LC0
.LC1:
#else  /* code size implemenation */
.LC0:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC0
#endif
#ifdef __STARTUP_INITIALIZE_NONCACHEDATA
    ldr    r2, =__noncachedata_start__
    ldr    r3, =__noncachedata_init_end__
#ifdef __PERFORMANCE_IMPLEMENTATION
/* Here are two copies of loop implementations. First one favors performance
 * and the second one favors code size. Default uses the second one.
 * Define macro "__PERFORMANCE_IMPLEMENTATION" in project to use the first one */
    subs    r3, r2
    ble    .LC3
.LC2:
    subs    r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .LC2
.LC3:
#else  /* code size implemenation */
.LC2:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC2
#endif
/* zero inited ncache section initialization */
    ldr r3, =__noncachedata_end__
    movs    r0,0
.LC4:
    cmp    r2,r3
    itt    lt
    strlt   r0,[r2],#4
    blt    .LC4
#endif /* __STARTUP_INITIALIZE_NONCACHEDATA */

#ifdef __STARTUP_CLEAR_BSS
/*     This part of work usually is done in C library startup code. Otherwise,
 *     define this macro to enable it in this startup.
 *
 *     Loop to zero out BSS section, which uses following symbols
 *     in linker script:
 *      __bss_start__: start of BSS section. Must align to 4
 *      __bss_end__: end of BSS section. Must align to 4
 */
    ldr r1, =__bss_start__
    ldr r2, =__bss_end__

    movs    r0, 0
.LC5:
    cmp     r1, r2
    itt    lt
    strlt   r0, [r1], #4
    blt    .LC5
#endif /* __STARTUP_CLEAR_BSS */

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
    .weak CAN4_IRQHandler
    .type CAN4_IRQHandler, %function
CAN4_IRQHandler:
    ldr   r0,=CAN4_DriverIRQHandler
    bx    r0
    .size CAN4_IRQHandler, . - CAN4_IRQHandler

    .align 1
    .thumb_func
    .weak CAN4_ERROR_IRQHandler
    .type CAN4_ERROR_IRQHandler, %function
CAN4_ERROR_IRQHandler:
    ldr   r0,=CAN4_ERROR_DriverIRQHandler
    bx    r0
    .size CAN4_ERROR_IRQHandler, . - CAN4_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak CAN5_IRQHandler
    .type CAN5_IRQHandler, %function
CAN5_IRQHandler:
    ldr   r0,=CAN5_DriverIRQHandler
    bx    r0
    .size CAN5_IRQHandler, . - CAN5_IRQHandler

    .align 1
    .thumb_func
    .weak CAN5_ERROR_IRQHandler
    .type CAN5_ERROR_IRQHandler, %function
CAN5_ERROR_IRQHandler:
    ldr   r0,=CAN5_ERROR_DriverIRQHandler
    bx    r0
    .size CAN5_ERROR_IRQHandler, . - CAN5_ERROR_IRQHandler

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
    .weak FlexSPI1_IRQHandler
    .type FlexSPI1_IRQHandler, %function
FlexSPI1_IRQHandler:
    ldr   r0,=FlexSPI1_DriverIRQHandler
    bx    r0
    .size FlexSPI1_IRQHandler, . - FlexSPI1_IRQHandler

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
    .weak uSDHC1_IRQHandler
    .type uSDHC1_IRQHandler, %function
uSDHC1_IRQHandler:
    ldr   r0,=uSDHC1_DriverIRQHandler
    bx    r0
    .size uSDHC1_IRQHandler, . - uSDHC1_IRQHandler

    .align 1
    .thumb_func
    .weak uSDHC2_IRQHandler
    .type uSDHC2_IRQHandler, %function
uSDHC2_IRQHandler:
    ldr   r0,=uSDHC2_DriverIRQHandler
    bx    r0
    .size uSDHC2_IRQHandler, . - uSDHC2_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_ERROR_IRQHandler
    .type DMA3_ERROR_IRQHandler, %function
DMA3_ERROR_IRQHandler:
    ldr   r0,=DMA3_ERROR_DriverIRQHandler
    bx    r0
    .size DMA3_ERROR_IRQHandler, . - DMA3_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_0_IRQHandler
    .type DMA3_0_IRQHandler, %function
DMA3_0_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_0_IRQHandler, . - DMA3_0_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_1_IRQHandler
    .type DMA3_1_IRQHandler, %function
DMA3_1_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_1_IRQHandler, . - DMA3_1_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_2_IRQHandler
    .type DMA3_2_IRQHandler, %function
DMA3_2_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_2_IRQHandler, . - DMA3_2_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_3_IRQHandler
    .type DMA3_3_IRQHandler, %function
DMA3_3_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_3_IRQHandler, . - DMA3_3_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_4_IRQHandler
    .type DMA3_4_IRQHandler, %function
DMA3_4_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_4_IRQHandler, . - DMA3_4_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_5_IRQHandler
    .type DMA3_5_IRQHandler, %function
DMA3_5_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_5_IRQHandler, . - DMA3_5_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_6_IRQHandler
    .type DMA3_6_IRQHandler, %function
DMA3_6_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_6_IRQHandler, . - DMA3_6_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_7_IRQHandler
    .type DMA3_7_IRQHandler, %function
DMA3_7_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_7_IRQHandler, . - DMA3_7_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_8_IRQHandler
    .type DMA3_8_IRQHandler, %function
DMA3_8_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_8_IRQHandler, . - DMA3_8_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_9_IRQHandler
    .type DMA3_9_IRQHandler, %function
DMA3_9_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_9_IRQHandler, . - DMA3_9_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_10_IRQHandler
    .type DMA3_10_IRQHandler, %function
DMA3_10_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_10_IRQHandler, . - DMA3_10_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_11_IRQHandler
    .type DMA3_11_IRQHandler, %function
DMA3_11_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_11_IRQHandler, . - DMA3_11_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_12_IRQHandler
    .type DMA3_12_IRQHandler, %function
DMA3_12_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_12_IRQHandler, . - DMA3_12_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_13_IRQHandler
    .type DMA3_13_IRQHandler, %function
DMA3_13_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_13_IRQHandler, . - DMA3_13_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_14_IRQHandler
    .type DMA3_14_IRQHandler, %function
DMA3_14_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_14_IRQHandler, . - DMA3_14_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_15_IRQHandler
    .type DMA3_15_IRQHandler, %function
DMA3_15_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_15_IRQHandler, . - DMA3_15_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_16_IRQHandler
    .type DMA3_16_IRQHandler, %function
DMA3_16_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_16_IRQHandler, . - DMA3_16_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_17_IRQHandler
    .type DMA3_17_IRQHandler, %function
DMA3_17_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_17_IRQHandler, . - DMA3_17_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_18_IRQHandler
    .type DMA3_18_IRQHandler, %function
DMA3_18_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_18_IRQHandler, . - DMA3_18_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_19_IRQHandler
    .type DMA3_19_IRQHandler, %function
DMA3_19_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_19_IRQHandler, . - DMA3_19_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_20_IRQHandler
    .type DMA3_20_IRQHandler, %function
DMA3_20_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_20_IRQHandler, . - DMA3_20_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_21_IRQHandler
    .type DMA3_21_IRQHandler, %function
DMA3_21_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_21_IRQHandler, . - DMA3_21_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_22_IRQHandler
    .type DMA3_22_IRQHandler, %function
DMA3_22_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_22_IRQHandler, . - DMA3_22_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_23_IRQHandler
    .type DMA3_23_IRQHandler, %function
DMA3_23_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_23_IRQHandler, . - DMA3_23_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_24_IRQHandler
    .type DMA3_24_IRQHandler, %function
DMA3_24_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_24_IRQHandler, . - DMA3_24_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_25_IRQHandler
    .type DMA3_25_IRQHandler, %function
DMA3_25_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_25_IRQHandler, . - DMA3_25_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_26_IRQHandler
    .type DMA3_26_IRQHandler, %function
DMA3_26_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_26_IRQHandler, . - DMA3_26_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_27_IRQHandler
    .type DMA3_27_IRQHandler, %function
DMA3_27_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_27_IRQHandler, . - DMA3_27_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_28_IRQHandler
    .type DMA3_28_IRQHandler, %function
DMA3_28_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_28_IRQHandler, . - DMA3_28_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_29_IRQHandler
    .type DMA3_29_IRQHandler, %function
DMA3_29_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_29_IRQHandler, . - DMA3_29_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_30_IRQHandler
    .type DMA3_30_IRQHandler, %function
DMA3_30_IRQHandler:
    ldr   r0,=DMA3_DriverIRQHandler
    bx    r0
    .size DMA3_30_IRQHandler, . - DMA3_30_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_ERROR_IRQHandler
    .type DMA5_2_ERROR_IRQHandler, %function
DMA5_2_ERROR_IRQHandler:
    ldr   r0,=DMA5_2_ERROR_DriverIRQHandler
    bx    r0
    .size DMA5_2_ERROR_IRQHandler, . - DMA5_2_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_0_1_IRQHandler
    .type DMA5_2_0_1_IRQHandler, %function
DMA5_2_0_1_IRQHandler:
    ldr   r0,=DMA5_2_0_1_DriverIRQHandler
    bx    r0
    .size DMA5_2_0_1_IRQHandler, . - DMA5_2_0_1_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_2_3_IRQHandler
    .type DMA5_2_2_3_IRQHandler, %function
DMA5_2_2_3_IRQHandler:
    ldr   r0,=DMA5_2_2_3_DriverIRQHandler
    bx    r0
    .size DMA5_2_2_3_IRQHandler, . - DMA5_2_2_3_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_4_5_IRQHandler
    .type DMA5_2_4_5_IRQHandler, %function
DMA5_2_4_5_IRQHandler:
    ldr   r0,=DMA5_2_4_5_DriverIRQHandler
    bx    r0
    .size DMA5_2_4_5_IRQHandler, . - DMA5_2_4_5_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_6_7_IRQHandler
    .type DMA5_2_6_7_IRQHandler, %function
DMA5_2_6_7_IRQHandler:
    ldr   r0,=DMA5_2_6_7_DriverIRQHandler
    bx    r0
    .size DMA5_2_6_7_IRQHandler, . - DMA5_2_6_7_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_8_9_IRQHandler
    .type DMA5_2_8_9_IRQHandler, %function
DMA5_2_8_9_IRQHandler:
    ldr   r0,=DMA5_2_8_9_DriverIRQHandler
    bx    r0
    .size DMA5_2_8_9_IRQHandler, . - DMA5_2_8_9_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_10_11_IRQHandler
    .type DMA5_2_10_11_IRQHandler, %function
DMA5_2_10_11_IRQHandler:
    ldr   r0,=DMA5_2_10_11_DriverIRQHandler
    bx    r0
    .size DMA5_2_10_11_IRQHandler, . - DMA5_2_10_11_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_12_13_IRQHandler
    .type DMA5_2_12_13_IRQHandler, %function
DMA5_2_12_13_IRQHandler:
    ldr   r0,=DMA5_2_12_13_DriverIRQHandler
    bx    r0
    .size DMA5_2_12_13_IRQHandler, . - DMA5_2_12_13_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_14_15_IRQHandler
    .type DMA5_2_14_15_IRQHandler, %function
DMA5_2_14_15_IRQHandler:
    ldr   r0,=DMA5_2_14_15_DriverIRQHandler
    bx    r0
    .size DMA5_2_14_15_IRQHandler, . - DMA5_2_14_15_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_16_17_IRQHandler
    .type DMA5_2_16_17_IRQHandler, %function
DMA5_2_16_17_IRQHandler:
    ldr   r0,=DMA5_2_16_17_DriverIRQHandler
    bx    r0
    .size DMA5_2_16_17_IRQHandler, . - DMA5_2_16_17_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_18_19_IRQHandler
    .type DMA5_2_18_19_IRQHandler, %function
DMA5_2_18_19_IRQHandler:
    ldr   r0,=DMA5_2_18_19_DriverIRQHandler
    bx    r0
    .size DMA5_2_18_19_IRQHandler, . - DMA5_2_18_19_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_20_21_IRQHandler
    .type DMA5_2_20_21_IRQHandler, %function
DMA5_2_20_21_IRQHandler:
    ldr   r0,=DMA5_2_20_21_DriverIRQHandler
    bx    r0
    .size DMA5_2_20_21_IRQHandler, . - DMA5_2_20_21_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_22_23_IRQHandler
    .type DMA5_2_22_23_IRQHandler, %function
DMA5_2_22_23_IRQHandler:
    ldr   r0,=DMA5_2_22_23_DriverIRQHandler
    bx    r0
    .size DMA5_2_22_23_IRQHandler, . - DMA5_2_22_23_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_24_25_IRQHandler
    .type DMA5_2_24_25_IRQHandler, %function
DMA5_2_24_25_IRQHandler:
    ldr   r0,=DMA5_2_24_25_DriverIRQHandler
    bx    r0
    .size DMA5_2_24_25_IRQHandler, . - DMA5_2_24_25_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_26_27_IRQHandler
    .type DMA5_2_26_27_IRQHandler, %function
DMA5_2_26_27_IRQHandler:
    ldr   r0,=DMA5_2_26_27_DriverIRQHandler
    bx    r0
    .size DMA5_2_26_27_IRQHandler, . - DMA5_2_26_27_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_28_29_IRQHandler
    .type DMA5_2_28_29_IRQHandler, %function
DMA5_2_28_29_IRQHandler:
    ldr   r0,=DMA5_2_28_29_DriverIRQHandler
    bx    r0
    .size DMA5_2_28_29_IRQHandler, . - DMA5_2_28_29_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_30_31_IRQHandler
    .type DMA5_2_30_31_IRQHandler, %function
DMA5_2_30_31_IRQHandler:
    ldr   r0,=DMA5_2_30_31_DriverIRQHandler
    bx    r0
    .size DMA5_2_30_31_IRQHandler, . - DMA5_2_30_31_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_32_33_IRQHandler
    .type DMA5_2_32_33_IRQHandler, %function
DMA5_2_32_33_IRQHandler:
    ldr   r0,=DMA5_2_32_33_DriverIRQHandler
    bx    r0
    .size DMA5_2_32_33_IRQHandler, . - DMA5_2_32_33_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_34_35_IRQHandler
    .type DMA5_2_34_35_IRQHandler, %function
DMA5_2_34_35_IRQHandler:
    ldr   r0,=DMA5_2_34_35_DriverIRQHandler
    bx    r0
    .size DMA5_2_34_35_IRQHandler, . - DMA5_2_34_35_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_36_37_IRQHandler
    .type DMA5_2_36_37_IRQHandler, %function
DMA5_2_36_37_IRQHandler:
    ldr   r0,=DMA5_2_36_37_DriverIRQHandler
    bx    r0
    .size DMA5_2_36_37_IRQHandler, . - DMA5_2_36_37_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_38_39_IRQHandler
    .type DMA5_2_38_39_IRQHandler, %function
DMA5_2_38_39_IRQHandler:
    ldr   r0,=DMA5_2_38_39_DriverIRQHandler
    bx    r0
    .size DMA5_2_38_39_IRQHandler, . - DMA5_2_38_39_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_40_41_IRQHandler
    .type DMA5_2_40_41_IRQHandler, %function
DMA5_2_40_41_IRQHandler:
    ldr   r0,=DMA5_2_40_41_DriverIRQHandler
    bx    r0
    .size DMA5_2_40_41_IRQHandler, . - DMA5_2_40_41_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_42_43_IRQHandler
    .type DMA5_2_42_43_IRQHandler, %function
DMA5_2_42_43_IRQHandler:
    ldr   r0,=DMA5_2_42_43_DriverIRQHandler
    bx    r0
    .size DMA5_2_42_43_IRQHandler, . - DMA5_2_42_43_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_44_45_IRQHandler
    .type DMA5_2_44_45_IRQHandler, %function
DMA5_2_44_45_IRQHandler:
    ldr   r0,=DMA5_2_44_45_DriverIRQHandler
    bx    r0
    .size DMA5_2_44_45_IRQHandler, . - DMA5_2_44_45_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_46_47_IRQHandler
    .type DMA5_2_46_47_IRQHandler, %function
DMA5_2_46_47_IRQHandler:
    ldr   r0,=DMA5_2_46_47_DriverIRQHandler
    bx    r0
    .size DMA5_2_46_47_IRQHandler, . - DMA5_2_46_47_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_48_49_IRQHandler
    .type DMA5_2_48_49_IRQHandler, %function
DMA5_2_48_49_IRQHandler:
    ldr   r0,=DMA5_2_48_49_DriverIRQHandler
    bx    r0
    .size DMA5_2_48_49_IRQHandler, . - DMA5_2_48_49_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_50_51_IRQHandler
    .type DMA5_2_50_51_IRQHandler, %function
DMA5_2_50_51_IRQHandler:
    ldr   r0,=DMA5_2_50_51_DriverIRQHandler
    bx    r0
    .size DMA5_2_50_51_IRQHandler, . - DMA5_2_50_51_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_52_53_IRQHandler
    .type DMA5_2_52_53_IRQHandler, %function
DMA5_2_52_53_IRQHandler:
    ldr   r0,=DMA5_2_52_53_DriverIRQHandler
    bx    r0
    .size DMA5_2_52_53_IRQHandler, . - DMA5_2_52_53_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_54_55_IRQHandler
    .type DMA5_2_54_55_IRQHandler, %function
DMA5_2_54_55_IRQHandler:
    ldr   r0,=DMA5_2_54_55_DriverIRQHandler
    bx    r0
    .size DMA5_2_54_55_IRQHandler, . - DMA5_2_54_55_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_56_57_IRQHandler
    .type DMA5_2_56_57_IRQHandler, %function
DMA5_2_56_57_IRQHandler:
    ldr   r0,=DMA5_2_56_57_DriverIRQHandler
    bx    r0
    .size DMA5_2_56_57_IRQHandler, . - DMA5_2_56_57_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_58_59_IRQHandler
    .type DMA5_2_58_59_IRQHandler, %function
DMA5_2_58_59_IRQHandler:
    ldr   r0,=DMA5_2_58_59_DriverIRQHandler
    bx    r0
    .size DMA5_2_58_59_IRQHandler, . - DMA5_2_58_59_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_60_61_IRQHandler
    .type DMA5_2_60_61_IRQHandler, %function
DMA5_2_60_61_IRQHandler:
    ldr   r0,=DMA5_2_60_61_DriverIRQHandler
    bx    r0
    .size DMA5_2_60_61_IRQHandler, . - DMA5_2_60_61_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_2_62_63_IRQHandler
    .type DMA5_2_62_63_IRQHandler, %function
DMA5_2_62_63_IRQHandler:
    ldr   r0,=DMA5_2_62_63_DriverIRQHandler
    bx    r0
    .size DMA5_2_62_63_IRQHandler, . - DMA5_2_62_63_IRQHandler

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
    .weak SAI4_IRQHandler
    .type SAI4_IRQHandler, %function
SAI4_IRQHandler:
    ldr   r0,=SAI4_DriverIRQHandler
    bx    r0
    .size SAI4_IRQHandler, . - SAI4_IRQHandler

    .align 1
    .thumb_func
    .weak SAI5_IRQHandler
    .type SAI5_IRQHandler, %function
SAI5_IRQHandler:
    ldr   r0,=SAI5_DriverIRQHandler
    bx    r0
    .size SAI5_IRQHandler, . - SAI5_IRQHandler

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
    .weak LPSPI7_IRQHandler
    .type LPSPI7_IRQHandler, %function
LPSPI7_IRQHandler:
    ldr   r0,=LPSPI7_DriverIRQHandler
    bx    r0
    .size LPSPI7_IRQHandler, . - LPSPI7_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI8_IRQHandler
    .type LPSPI8_IRQHandler, %function
LPSPI8_IRQHandler:
    ldr   r0,=LPSPI8_DriverIRQHandler
    bx    r0
    .size LPSPI8_IRQHandler, . - LPSPI8_IRQHandler

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
    .weak LPI2C7_IRQHandler
    .type LPI2C7_IRQHandler, %function
LPI2C7_IRQHandler:
    ldr   r0,=LPI2C7_DriverIRQHandler
    bx    r0
    .size LPI2C7_IRQHandler, . - LPI2C7_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C8_IRQHandler
    .type LPI2C8_IRQHandler, %function
LPI2C8_IRQHandler:
    ldr   r0,=LPI2C8_DriverIRQHandler
    bx    r0
    .size LPI2C8_IRQHandler, . - LPI2C8_IRQHandler

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
    .weak uSDHC3_IRQHandler
    .type uSDHC3_IRQHandler, %function
uSDHC3_IRQHandler:
    ldr   r0,=uSDHC3_DriverIRQHandler
    bx    r0
    .size uSDHC3_IRQHandler, . - uSDHC3_IRQHandler

    .align 1
    .thumb_func
    .weak DISP_IRQSTEER0_IRQHandler
    .type DISP_IRQSTEER0_IRQHandler, %function
DISP_IRQSTEER0_IRQHandler:
    ldr   r0,=DISP_IRQSTEER0_DriverIRQHandler
    bx    r0
    .size DISP_IRQSTEER0_IRQHandler, . - DISP_IRQSTEER0_IRQHandler

    .align 1
    .thumb_func
    .weak DISP_IRQSTEER1_IRQHandler
    .type DISP_IRQSTEER1_IRQHandler, %function
DISP_IRQSTEER1_IRQHandler:
    ldr   r0,=DISP_IRQSTEER1_DriverIRQHandler
    bx    r0
    .size DISP_IRQSTEER1_IRQHandler, . - DISP_IRQSTEER1_IRQHandler

    .align 1
    .thumb_func
    .weak DISP_IRQSTEER2_IRQHandler
    .type DISP_IRQSTEER2_IRQHandler, %function
DISP_IRQSTEER2_IRQHandler:
    ldr   r0,=DISP_IRQSTEER2_DriverIRQHandler
    bx    r0
    .size DISP_IRQSTEER2_IRQHandler, . - DISP_IRQSTEER2_IRQHandler

    .align 1
    .thumb_func
    .weak DISP_IRQSTEER3_IRQHandler
    .type DISP_IRQSTEER3_IRQHandler, %function
DISP_IRQSTEER3_IRQHandler:
    ldr   r0,=DISP_IRQSTEER3_DriverIRQHandler
    bx    r0
    .size DISP_IRQSTEER3_IRQHandler, . - DISP_IRQSTEER3_IRQHandler

    .align 1
    .thumb_func
    .weak DISP_IRQSTEER4_IRQHandler
    .type DISP_IRQSTEER4_IRQHandler, %function
DISP_IRQSTEER4_IRQHandler:
    ldr   r0,=DISP_IRQSTEER4_DriverIRQHandler
    bx    r0
    .size DISP_IRQSTEER4_IRQHandler, . - DISP_IRQSTEER4_IRQHandler

    .align 1
    .thumb_func
    .weak DISP_IRQSTEER7_IRQHandler
    .type DISP_IRQSTEER7_IRQHandler, %function
DISP_IRQSTEER7_IRQHandler:
    ldr   r0,=DISP_IRQSTEER7_DriverIRQHandler
    bx    r0
    .size DISP_IRQSTEER7_IRQHandler, . - DISP_IRQSTEER7_IRQHandler

    .align 1
    .thumb_func
    .weak IRQSTEER_0_IRQHandler
    .type IRQSTEER_0_IRQHandler, %function
IRQSTEER_0_IRQHandler:
    ldr   r0,=IRQSTEER_0_DriverIRQHandler
    bx    r0
    .size IRQSTEER_0_IRQHandler, . - IRQSTEER_0_IRQHandler

    .align 1
    .thumb_func
    .weak IRQSTEER_1_IRQHandler
    .type IRQSTEER_1_IRQHandler, %function
IRQSTEER_1_IRQHandler:
    ldr   r0,=IRQSTEER_1_DriverIRQHandler
    bx    r0
    .size IRQSTEER_1_IRQHandler, . - IRQSTEER_1_IRQHandler

    .align 1
    .thumb_func
    .weak IRQSTEER_2_IRQHandler
    .type IRQSTEER_2_IRQHandler, %function
IRQSTEER_2_IRQHandler:
    ldr   r0,=IRQSTEER_2_DriverIRQHandler
    bx    r0
    .size IRQSTEER_2_IRQHandler, . - IRQSTEER_2_IRQHandler

    .align 1
    .thumb_func
    .weak IRQSTEER_3_IRQHandler
    .type IRQSTEER_3_IRQHandler, %function
IRQSTEER_3_IRQHandler:
    ldr   r0,=IRQSTEER_3_DriverIRQHandler
    bx    r0
    .size IRQSTEER_3_IRQHandler, . - IRQSTEER_3_IRQHandler

    .align 1
    .thumb_func
    .weak IRQSTEER_4_IRQHandler
    .type IRQSTEER_4_IRQHandler, %function
IRQSTEER_4_IRQHandler:
    ldr   r0,=IRQSTEER_4_DriverIRQHandler
    bx    r0
    .size IRQSTEER_4_IRQHandler, . - IRQSTEER_4_IRQHandler

    .align 1
    .thumb_func
    .weak IRQSTEER_5_IRQHandler
    .type IRQSTEER_5_IRQHandler, %function
IRQSTEER_5_IRQHandler:
    ldr   r0,=IRQSTEER_5_DriverIRQHandler
    bx    r0
    .size IRQSTEER_5_IRQHandler, . - IRQSTEER_5_IRQHandler

    .align 1
    .thumb_func
    .weak IRQSTEER_6_IRQHandler
    .type IRQSTEER_6_IRQHandler, %function
IRQSTEER_6_IRQHandler:
    ldr   r0,=IRQSTEER_6_DriverIRQHandler
    bx    r0
    .size IRQSTEER_6_IRQHandler, . - IRQSTEER_6_IRQHandler

    .align 1
    .thumb_func
    .weak IRQSTEER_7_IRQHandler
    .type IRQSTEER_7_IRQHandler, %function
IRQSTEER_7_IRQHandler:
    ldr   r0,=IRQSTEER_7_DriverIRQHandler
    bx    r0
    .size IRQSTEER_7_IRQHandler, . - IRQSTEER_7_IRQHandler

    .align 1
    .thumb_func
    .weak IRQSTEER_8_IRQHandler
    .type IRQSTEER_8_IRQHandler, %function
IRQSTEER_8_IRQHandler:
    ldr   r0,=IRQSTEER_8_DriverIRQHandler
    bx    r0
    .size IRQSTEER_8_IRQHandler, . - IRQSTEER_8_IRQHandler

    .align 1
    .thumb_func
    .weak IRQSTEER_9_IRQHandler
    .type IRQSTEER_9_IRQHandler, %function
IRQSTEER_9_IRQHandler:
    ldr   r0,=IRQSTEER_9_DriverIRQHandler
    bx    r0
    .size IRQSTEER_9_IRQHandler, . - IRQSTEER_9_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_0_1_IRQHandler
    .type DMA5_3_0_1_IRQHandler, %function
DMA5_3_0_1_IRQHandler:
    ldr   r0,=DMA5_3_0_1_DriverIRQHandler
    bx    r0
    .size DMA5_3_0_1_IRQHandler, . - DMA5_3_0_1_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_2_3_IRQHandler
    .type DMA5_3_2_3_IRQHandler, %function
DMA5_3_2_3_IRQHandler:
    ldr   r0,=DMA5_3_2_3_DriverIRQHandler
    bx    r0
    .size DMA5_3_2_3_IRQHandler, . - DMA5_3_2_3_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_4_5_IRQHandler
    .type DMA5_3_4_5_IRQHandler, %function
DMA5_3_4_5_IRQHandler:
    ldr   r0,=DMA5_3_4_5_DriverIRQHandler
    bx    r0
    .size DMA5_3_4_5_IRQHandler, . - DMA5_3_4_5_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_6_7_IRQHandler
    .type DMA5_3_6_7_IRQHandler, %function
DMA5_3_6_7_IRQHandler:
    ldr   r0,=DMA5_3_6_7_DriverIRQHandler
    bx    r0
    .size DMA5_3_6_7_IRQHandler, . - DMA5_3_6_7_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_8_9_IRQHandler
    .type DMA5_3_8_9_IRQHandler, %function
DMA5_3_8_9_IRQHandler:
    ldr   r0,=DMA5_3_8_9_DriverIRQHandler
    bx    r0
    .size DMA5_3_8_9_IRQHandler, . - DMA5_3_8_9_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_10_11_IRQHandler
    .type DMA5_3_10_11_IRQHandler, %function
DMA5_3_10_11_IRQHandler:
    ldr   r0,=DMA5_3_10_11_DriverIRQHandler
    bx    r0
    .size DMA5_3_10_11_IRQHandler, . - DMA5_3_10_11_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_12_13_IRQHandler
    .type DMA5_3_12_13_IRQHandler, %function
DMA5_3_12_13_IRQHandler:
    ldr   r0,=DMA5_3_12_13_DriverIRQHandler
    bx    r0
    .size DMA5_3_12_13_IRQHandler, . - DMA5_3_12_13_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_14_15_IRQHandler
    .type DMA5_3_14_15_IRQHandler, %function
DMA5_3_14_15_IRQHandler:
    ldr   r0,=DMA5_3_14_15_DriverIRQHandler
    bx    r0
    .size DMA5_3_14_15_IRQHandler, . - DMA5_3_14_15_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_16_17_IRQHandler
    .type DMA5_3_16_17_IRQHandler, %function
DMA5_3_16_17_IRQHandler:
    ldr   r0,=DMA5_3_16_17_DriverIRQHandler
    bx    r0
    .size DMA5_3_16_17_IRQHandler, . - DMA5_3_16_17_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_18_19_IRQHandler
    .type DMA5_3_18_19_IRQHandler, %function
DMA5_3_18_19_IRQHandler:
    ldr   r0,=DMA5_3_18_19_DriverIRQHandler
    bx    r0
    .size DMA5_3_18_19_IRQHandler, . - DMA5_3_18_19_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_20_21_IRQHandler
    .type DMA5_3_20_21_IRQHandler, %function
DMA5_3_20_21_IRQHandler:
    ldr   r0,=DMA5_3_20_21_DriverIRQHandler
    bx    r0
    .size DMA5_3_20_21_IRQHandler, . - DMA5_3_20_21_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_22_23_IRQHandler
    .type DMA5_3_22_23_IRQHandler, %function
DMA5_3_22_23_IRQHandler:
    ldr   r0,=DMA5_3_22_23_DriverIRQHandler
    bx    r0
    .size DMA5_3_22_23_IRQHandler, . - DMA5_3_22_23_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_24_25_IRQHandler
    .type DMA5_3_24_25_IRQHandler, %function
DMA5_3_24_25_IRQHandler:
    ldr   r0,=DMA5_3_24_25_DriverIRQHandler
    bx    r0
    .size DMA5_3_24_25_IRQHandler, . - DMA5_3_24_25_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_26_27_IRQHandler
    .type DMA5_3_26_27_IRQHandler, %function
DMA5_3_26_27_IRQHandler:
    ldr   r0,=DMA5_3_26_27_DriverIRQHandler
    bx    r0
    .size DMA5_3_26_27_IRQHandler, . - DMA5_3_26_27_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_28_29_IRQHandler
    .type DMA5_3_28_29_IRQHandler, %function
DMA5_3_28_29_IRQHandler:
    ldr   r0,=DMA5_3_28_29_DriverIRQHandler
    bx    r0
    .size DMA5_3_28_29_IRQHandler, . - DMA5_3_28_29_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_30_31_IRQHandler
    .type DMA5_3_30_31_IRQHandler, %function
DMA5_3_30_31_IRQHandler:
    ldr   r0,=DMA5_3_30_31_DriverIRQHandler
    bx    r0
    .size DMA5_3_30_31_IRQHandler, . - DMA5_3_30_31_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_32_33_IRQHandler
    .type DMA5_3_32_33_IRQHandler, %function
DMA5_3_32_33_IRQHandler:
    ldr   r0,=DMA5_3_32_33_DriverIRQHandler
    bx    r0
    .size DMA5_3_32_33_IRQHandler, . - DMA5_3_32_33_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_34_35_IRQHandler
    .type DMA5_3_34_35_IRQHandler, %function
DMA5_3_34_35_IRQHandler:
    ldr   r0,=DMA5_3_34_35_DriverIRQHandler
    bx    r0
    .size DMA5_3_34_35_IRQHandler, . - DMA5_3_34_35_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_36_37_IRQHandler
    .type DMA5_3_36_37_IRQHandler, %function
DMA5_3_36_37_IRQHandler:
    ldr   r0,=DMA5_3_36_37_DriverIRQHandler
    bx    r0
    .size DMA5_3_36_37_IRQHandler, . - DMA5_3_36_37_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_38_39_IRQHandler
    .type DMA5_3_38_39_IRQHandler, %function
DMA5_3_38_39_IRQHandler:
    ldr   r0,=DMA5_3_38_39_DriverIRQHandler
    bx    r0
    .size DMA5_3_38_39_IRQHandler, . - DMA5_3_38_39_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_40_41_IRQHandler
    .type DMA5_3_40_41_IRQHandler, %function
DMA5_3_40_41_IRQHandler:
    ldr   r0,=DMA5_3_40_41_DriverIRQHandler
    bx    r0
    .size DMA5_3_40_41_IRQHandler, . - DMA5_3_40_41_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_42_43_IRQHandler
    .type DMA5_3_42_43_IRQHandler, %function
DMA5_3_42_43_IRQHandler:
    ldr   r0,=DMA5_3_42_43_DriverIRQHandler
    bx    r0
    .size DMA5_3_42_43_IRQHandler, . - DMA5_3_42_43_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_44_45_IRQHandler
    .type DMA5_3_44_45_IRQHandler, %function
DMA5_3_44_45_IRQHandler:
    ldr   r0,=DMA5_3_44_45_DriverIRQHandler
    bx    r0
    .size DMA5_3_44_45_IRQHandler, . - DMA5_3_44_45_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_46_47_IRQHandler
    .type DMA5_3_46_47_IRQHandler, %function
DMA5_3_46_47_IRQHandler:
    ldr   r0,=DMA5_3_46_47_DriverIRQHandler
    bx    r0
    .size DMA5_3_46_47_IRQHandler, . - DMA5_3_46_47_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_48_49_IRQHandler
    .type DMA5_3_48_49_IRQHandler, %function
DMA5_3_48_49_IRQHandler:
    ldr   r0,=DMA5_3_48_49_DriverIRQHandler
    bx    r0
    .size DMA5_3_48_49_IRQHandler, . - DMA5_3_48_49_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_50_51_IRQHandler
    .type DMA5_3_50_51_IRQHandler, %function
DMA5_3_50_51_IRQHandler:
    ldr   r0,=DMA5_3_50_51_DriverIRQHandler
    bx    r0
    .size DMA5_3_50_51_IRQHandler, . - DMA5_3_50_51_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_52_53_IRQHandler
    .type DMA5_3_52_53_IRQHandler, %function
DMA5_3_52_53_IRQHandler:
    ldr   r0,=DMA5_3_52_53_DriverIRQHandler
    bx    r0
    .size DMA5_3_52_53_IRQHandler, . - DMA5_3_52_53_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_54_55_IRQHandler
    .type DMA5_3_54_55_IRQHandler, %function
DMA5_3_54_55_IRQHandler:
    ldr   r0,=DMA5_3_54_55_DriverIRQHandler
    bx    r0
    .size DMA5_3_54_55_IRQHandler, . - DMA5_3_54_55_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_56_57_IRQHandler
    .type DMA5_3_56_57_IRQHandler, %function
DMA5_3_56_57_IRQHandler:
    ldr   r0,=DMA5_3_56_57_DriverIRQHandler
    bx    r0
    .size DMA5_3_56_57_IRQHandler, . - DMA5_3_56_57_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_58_59_IRQHandler
    .type DMA5_3_58_59_IRQHandler, %function
DMA5_3_58_59_IRQHandler:
    ldr   r0,=DMA5_3_58_59_DriverIRQHandler
    bx    r0
    .size DMA5_3_58_59_IRQHandler, . - DMA5_3_58_59_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_60_61_IRQHandler
    .type DMA5_3_60_61_IRQHandler, %function
DMA5_3_60_61_IRQHandler:
    ldr   r0,=DMA5_3_60_61_DriverIRQHandler
    bx    r0
    .size DMA5_3_60_61_IRQHandler, . - DMA5_3_60_61_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_3_62_63_IRQHandler
    .type DMA5_3_62_63_IRQHandler, %function
DMA5_3_62_63_IRQHandler:
    ldr   r0,=DMA5_3_62_63_DriverIRQHandler
    bx    r0
    .size DMA5_3_62_63_IRQHandler, . - DMA5_3_62_63_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_ERROR_IRQHandler
    .type DMA5_4_ERROR_IRQHandler, %function
DMA5_4_ERROR_IRQHandler:
    ldr   r0,=DMA5_4_ERROR_DriverIRQHandler
    bx    r0
    .size DMA5_4_ERROR_IRQHandler, . - DMA5_4_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_0_1_IRQHandler
    .type DMA5_4_0_1_IRQHandler, %function
DMA5_4_0_1_IRQHandler:
    ldr   r0,=DMA5_4_0_1_DriverIRQHandler
    bx    r0
    .size DMA5_4_0_1_IRQHandler, . - DMA5_4_0_1_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_2_3_IRQHandler
    .type DMA5_4_2_3_IRQHandler, %function
DMA5_4_2_3_IRQHandler:
    ldr   r0,=DMA5_4_2_3_DriverIRQHandler
    bx    r0
    .size DMA5_4_2_3_IRQHandler, . - DMA5_4_2_3_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_4_5_IRQHandler
    .type DMA5_4_4_5_IRQHandler, %function
DMA5_4_4_5_IRQHandler:
    ldr   r0,=DMA5_4_4_5_DriverIRQHandler
    bx    r0
    .size DMA5_4_4_5_IRQHandler, . - DMA5_4_4_5_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_6_7_IRQHandler
    .type DMA5_4_6_7_IRQHandler, %function
DMA5_4_6_7_IRQHandler:
    ldr   r0,=DMA5_4_6_7_DriverIRQHandler
    bx    r0
    .size DMA5_4_6_7_IRQHandler, . - DMA5_4_6_7_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_8_9_IRQHandler
    .type DMA5_4_8_9_IRQHandler, %function
DMA5_4_8_9_IRQHandler:
    ldr   r0,=DMA5_4_8_9_DriverIRQHandler
    bx    r0
    .size DMA5_4_8_9_IRQHandler, . - DMA5_4_8_9_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_10_11_IRQHandler
    .type DMA5_4_10_11_IRQHandler, %function
DMA5_4_10_11_IRQHandler:
    ldr   r0,=DMA5_4_10_11_DriverIRQHandler
    bx    r0
    .size DMA5_4_10_11_IRQHandler, . - DMA5_4_10_11_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_12_13_IRQHandler
    .type DMA5_4_12_13_IRQHandler, %function
DMA5_4_12_13_IRQHandler:
    ldr   r0,=DMA5_4_12_13_DriverIRQHandler
    bx    r0
    .size DMA5_4_12_13_IRQHandler, . - DMA5_4_12_13_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_14_15_IRQHandler
    .type DMA5_4_14_15_IRQHandler, %function
DMA5_4_14_15_IRQHandler:
    ldr   r0,=DMA5_4_14_15_DriverIRQHandler
    bx    r0
    .size DMA5_4_14_15_IRQHandler, . - DMA5_4_14_15_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_16_17_IRQHandler
    .type DMA5_4_16_17_IRQHandler, %function
DMA5_4_16_17_IRQHandler:
    ldr   r0,=DMA5_4_16_17_DriverIRQHandler
    bx    r0
    .size DMA5_4_16_17_IRQHandler, . - DMA5_4_16_17_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_18_19_IRQHandler
    .type DMA5_4_18_19_IRQHandler, %function
DMA5_4_18_19_IRQHandler:
    ldr   r0,=DMA5_4_18_19_DriverIRQHandler
    bx    r0
    .size DMA5_4_18_19_IRQHandler, . - DMA5_4_18_19_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_20_21_IRQHandler
    .type DMA5_4_20_21_IRQHandler, %function
DMA5_4_20_21_IRQHandler:
    ldr   r0,=DMA5_4_20_21_DriverIRQHandler
    bx    r0
    .size DMA5_4_20_21_IRQHandler, . - DMA5_4_20_21_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_22_23_IRQHandler
    .type DMA5_4_22_23_IRQHandler, %function
DMA5_4_22_23_IRQHandler:
    ldr   r0,=DMA5_4_22_23_DriverIRQHandler
    bx    r0
    .size DMA5_4_22_23_IRQHandler, . - DMA5_4_22_23_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_24_25_IRQHandler
    .type DMA5_4_24_25_IRQHandler, %function
DMA5_4_24_25_IRQHandler:
    ldr   r0,=DMA5_4_24_25_DriverIRQHandler
    bx    r0
    .size DMA5_4_24_25_IRQHandler, . - DMA5_4_24_25_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_26_27_IRQHandler
    .type DMA5_4_26_27_IRQHandler, %function
DMA5_4_26_27_IRQHandler:
    ldr   r0,=DMA5_4_26_27_DriverIRQHandler
    bx    r0
    .size DMA5_4_26_27_IRQHandler, . - DMA5_4_26_27_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_28_29_IRQHandler
    .type DMA5_4_28_29_IRQHandler, %function
DMA5_4_28_29_IRQHandler:
    ldr   r0,=DMA5_4_28_29_DriverIRQHandler
    bx    r0
    .size DMA5_4_28_29_IRQHandler, . - DMA5_4_28_29_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_4_30_31_IRQHandler
    .type DMA5_4_30_31_IRQHandler, %function
DMA5_4_30_31_IRQHandler:
    ldr   r0,=DMA5_4_30_31_DriverIRQHandler
    bx    r0
    .size DMA5_4_30_31_IRQHandler, . - DMA5_4_30_31_IRQHandler


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
    def_irq_handler    Reserved16_IRQHandler
    def_irq_handler    Reserved17_IRQHandler
    def_irq_handler    Reserved18_IRQHandler
    def_irq_handler    Reserved19_IRQHandler
    def_irq_handler    Reserved20_IRQHandler
    def_irq_handler    Reserved21_IRQHandler
    def_irq_handler    Reserved22_IRQHandler
    def_irq_handler    Reserved23_IRQHandler
    def_irq_handler    CAN1_DriverIRQHandler
    def_irq_handler    CAN1_ERROR_DriverIRQHandler
    def_irq_handler    Reserved26_IRQHandler
    def_irq_handler    Reserved27_IRQHandler
    def_irq_handler    I3C1_DriverIRQHandler
    def_irq_handler    LPI2C1_DriverIRQHandler
    def_irq_handler    LPI2C2_DriverIRQHandler
    def_irq_handler    LPIT1_IRQHandler
    def_irq_handler    LPSPI1_DriverIRQHandler
    def_irq_handler    LPSPI2_DriverIRQHandler
    def_irq_handler    LPTMR1_IRQHandler
    def_irq_handler    LPUART1_DriverIRQHandler
    def_irq_handler    LPUART2_DriverIRQHandler
    def_irq_handler    Reserved37_IRQHandler
    def_irq_handler    Reserved38_IRQHandler
    def_irq_handler    Reserved39_IRQHandler
    def_irq_handler    Reserved40_IRQHandler
    def_irq_handler    Reserved41_IRQHandler
    def_irq_handler    Reserved42_IRQHandler
    def_irq_handler    V2X_FH_APCH0_IRQHandler
    def_irq_handler    V2X_FH_APHSM1_IRQHandler
    def_irq_handler    TPM1_IRQHandler
    def_irq_handler    TPM2_IRQHandler
    def_irq_handler    WDOG1_IRQHandler
    def_irq_handler    WDOG2_IRQHandler
    def_irq_handler    TRDC_MGR_A_IRQHandler
    def_irq_handler    SAI1_DriverIRQHandler
    def_irq_handler    Reserved51_IRQHandler
    def_irq_handler    Reserved52_IRQHandler
    def_irq_handler    Reserved53_IRQHandler
    def_irq_handler    CAN2_DriverIRQHandler
    def_irq_handler    CAN2_ERROR_DriverIRQHandler
    def_irq_handler    CAN3_DriverIRQHandler
    def_irq_handler    CAN3_ERROR_DriverIRQHandler
    def_irq_handler    CAN4_DriverIRQHandler
    def_irq_handler    CAN4_ERROR_DriverIRQHandler
    def_irq_handler    CAN5_DriverIRQHandler
    def_irq_handler    CAN5_ERROR_DriverIRQHandler
    def_irq_handler    FLEXIO1_DriverIRQHandler
    def_irq_handler    FLEXIO2_DriverIRQHandler
    def_irq_handler    FlexSPI1_DriverIRQHandler
    def_irq_handler    Reserved65_IRQHandler
    def_irq_handler    Reserved66_IRQHandler
    def_irq_handler    Reserved67_IRQHandler
    def_irq_handler    Reserved68_IRQHandler
    def_irq_handler    Reserved69_IRQHandler
    def_irq_handler    Reserved70_IRQHandler
    def_irq_handler    Reserved71_IRQHandler
    def_irq_handler    Reserved72_IRQHandler
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
    def_irq_handler    LPUART7_DriverIRQHandler
    def_irq_handler    LPUART8_DriverIRQHandler
    def_irq_handler    Reserved86_IRQHandler
    def_irq_handler    Reserved87_IRQHandler
    def_irq_handler    Reserved88_IRQHandler
    def_irq_handler    TPM3_IRQHandler
    def_irq_handler    TPM4_IRQHandler
    def_irq_handler    TPM5_IRQHandler
    def_irq_handler    TPM6_IRQHandler
    def_irq_handler    WDOG3_IRQHandler
    def_irq_handler    WDOG4_IRQHandler
    def_irq_handler    WDOG5_IRQHandler
    def_irq_handler    TMPSNS1_THR1_IRQHandler
    def_irq_handler    TMPSNS1_THR2_IRQHandler
    def_irq_handler    TMPSNS1_DRDY_IRQHandler
    def_irq_handler    TMPSNS2_THR1_IRQHandler
    def_irq_handler    TMPSNS2_THR2_IRQHandler
    def_irq_handler    TMPSNS2_DRDY_IRQHandler
    def_irq_handler    uSDHC1_DriverIRQHandler
    def_irq_handler    uSDHC2_DriverIRQHandler
    def_irq_handler    Reserved104_IRQHandler
    def_irq_handler    Reserved105_IRQHandler
    def_irq_handler    Reserved106_IRQHandler
    def_irq_handler    Reserved107_IRQHandler
    def_irq_handler    Reserved108_IRQHandler
    def_irq_handler    Reserved109_IRQHandler
    def_irq_handler    Reserved110_IRQHandler
    def_irq_handler    DMA3_ERROR_DriverIRQHandler
    def_irq_handler    DMA3_DriverIRQHandler
    def_irq_handler    DMA5_2_ERROR_DriverIRQHandler
    def_irq_handler    DMA5_2_0_1_DriverIRQHandler
    def_irq_handler    DMA5_2_2_3_DriverIRQHandler
    def_irq_handler    DMA5_2_4_5_DriverIRQHandler
    def_irq_handler    DMA5_2_6_7_DriverIRQHandler
    def_irq_handler    DMA5_2_8_9_DriverIRQHandler
    def_irq_handler    DMA5_2_10_11_DriverIRQHandler
    def_irq_handler    DMA5_2_12_13_DriverIRQHandler
    def_irq_handler    DMA5_2_14_15_DriverIRQHandler
    def_irq_handler    DMA5_2_16_17_DriverIRQHandler
    def_irq_handler    DMA5_2_18_19_DriverIRQHandler
    def_irq_handler    DMA5_2_20_21_DriverIRQHandler
    def_irq_handler    DMA5_2_22_23_DriverIRQHandler
    def_irq_handler    DMA5_2_24_25_DriverIRQHandler
    def_irq_handler    DMA5_2_26_27_DriverIRQHandler
    def_irq_handler    DMA5_2_28_29_DriverIRQHandler
    def_irq_handler    DMA5_2_30_31_DriverIRQHandler
    def_irq_handler    DMA5_2_32_33_DriverIRQHandler
    def_irq_handler    DMA5_2_34_35_DriverIRQHandler
    def_irq_handler    DMA5_2_36_37_DriverIRQHandler
    def_irq_handler    DMA5_2_38_39_DriverIRQHandler
    def_irq_handler    DMA5_2_40_41_DriverIRQHandler
    def_irq_handler    DMA5_2_42_43_DriverIRQHandler
    def_irq_handler    DMA5_2_44_45_DriverIRQHandler
    def_irq_handler    DMA5_2_46_47_DriverIRQHandler
    def_irq_handler    DMA5_2_48_49_DriverIRQHandler
    def_irq_handler    DMA5_2_50_51_DriverIRQHandler
    def_irq_handler    DMA5_2_52_53_DriverIRQHandler
    def_irq_handler    DMA5_2_54_55_DriverIRQHandler
    def_irq_handler    DMA5_2_56_57_DriverIRQHandler
    def_irq_handler    DMA5_2_58_59_DriverIRQHandler
    def_irq_handler    DMA5_2_60_61_DriverIRQHandler
    def_irq_handler    DMA5_2_62_63_DriverIRQHandler
    def_irq_handler    Reserved176_IRQHandler
    def_irq_handler    Reserved177_IRQHandler
    def_irq_handler    Reserved178_IRQHandler
    def_irq_handler    Reserved179_IRQHandler
    def_irq_handler    Reserved180_IRQHandler
    def_irq_handler    Reserved181_IRQHandler
    def_irq_handler    Reserved182_IRQHandler
    def_irq_handler    Reserved183_IRQHandler
    def_irq_handler    Reserved184_IRQHandler
    def_irq_handler    SAI2_DriverIRQHandler
    def_irq_handler    SAI3_DriverIRQHandler
    def_irq_handler    SAI4_DriverIRQHandler
    def_irq_handler    SAI5_DriverIRQHandler
    def_irq_handler    Reserved189_IRQHandler
    def_irq_handler    Reserved190_IRQHandler
    def_irq_handler    USB1_IRQHandler
    def_irq_handler    USB2_IRQHandler
    def_irq_handler    LPSPI5_DriverIRQHandler
    def_irq_handler    LPSPI6_DriverIRQHandler
    def_irq_handler    LPSPI7_DriverIRQHandler
    def_irq_handler    LPSPI8_DriverIRQHandler
    def_irq_handler    LPI2C5_DriverIRQHandler
    def_irq_handler    LPI2C6_DriverIRQHandler
    def_irq_handler    LPI2C7_DriverIRQHandler
    def_irq_handler    LPI2C8_DriverIRQHandler
    def_irq_handler    PDM_HWVAD_ERROR_IRQHandler
    def_irq_handler    PDM_HWVAD_EVENT_IRQHandler
    def_irq_handler    PDM_ERROR_IRQHandler
    def_irq_handler    PDM_EVENT_DriverIRQHandler
    def_irq_handler    Reserved205_IRQHandler
    def_irq_handler    Reserved206_IRQHandler
    def_irq_handler    uSDHC3_DriverIRQHandler
    def_irq_handler    Reserved208_IRQHandler
    def_irq_handler    Reserved209_IRQHandler
    def_irq_handler    Reserved210_IRQHandler
    def_irq_handler    Reserved211_IRQHandler
    def_irq_handler    Reserved212_IRQHandler
    def_irq_handler    Reserved213_IRQHandler
    def_irq_handler    Reserved214_IRQHandler
    def_irq_handler    ADC_ER_IRQHandler
    def_irq_handler    ADC_WD_IRQHandler
    def_irq_handler    ADC_EOC_IRQHandler
    def_irq_handler    Reserved218_IRQHandler
    def_irq_handler    Reserved219_IRQHandler
    def_irq_handler    Reserved220_IRQHandler
    def_irq_handler    MU5_A_IRQHandler
    def_irq_handler    MU6_A_IRQHandler
    def_irq_handler    MU7_B_IRQHandler
    def_irq_handler    MU8_B_IRQHandler
    def_irq_handler    Reserved225_IRQHandler
    def_irq_handler    Reserved226_IRQHandler
    def_irq_handler    Reserved227_IRQHandler
    def_irq_handler    Reserved228_IRQHandler
    def_irq_handler    Reserved229_IRQHandler
    def_irq_handler    DISP_IRQSTEER0_DriverIRQHandler
    def_irq_handler    DISP_IRQSTEER1_DriverIRQHandler
    def_irq_handler    DISP_IRQSTEER2_DriverIRQHandler
    def_irq_handler    DISP_IRQSTEER3_DriverIRQHandler
    def_irq_handler    DISP_IRQSTEER4_DriverIRQHandler
    def_irq_handler    DISP_IRQSTEER7_DriverIRQHandler
    def_irq_handler    Reserved236_IRQHandler
    def_irq_handler    ISI_IRQHandler
    def_irq_handler    Reserved238_IRQHandler
    def_irq_handler    Reserved239_IRQHandler
    def_irq_handler    IRQSTEER_0_DriverIRQHandler
    def_irq_handler    IRQSTEER_1_DriverIRQHandler
    def_irq_handler    IRQSTEER_2_DriverIRQHandler
    def_irq_handler    IRQSTEER_3_DriverIRQHandler
    def_irq_handler    IRQSTEER_4_DriverIRQHandler
    def_irq_handler    IRQSTEER_5_DriverIRQHandler
    def_irq_handler    IRQSTEER_6_DriverIRQHandler
    def_irq_handler    IRQSTEER_7_DriverIRQHandler
    def_irq_handler    IRQSTEER_8_DriverIRQHandler
    def_irq_handler    IRQSTEER_9_DriverIRQHandler
    def_irq_handler    MU1_A_IRQHandler
    def_irq_handler    MU1_B_IRQHandler
    def_irq_handler    MU2_A_IRQHandler
    def_irq_handler    MU2_B_IRQHandler
    def_irq_handler    MU3_A_IRQHandler
    def_irq_handler    MU3_B_IRQHandler
    def_irq_handler    MU4_A_IRQHandler
    def_irq_handler    MU4_B_IRQHandler
    def_irq_handler    MU5_B_IRQHandler
    def_irq_handler    MU6_B_IRQHandler
    def_irq_handler    MU7_A_IRQHandler
    def_irq_handler    MU8_A_IRQHandler
    def_irq_handler    MSGINTR1_IRQHandler
    def_irq_handler    MSGINTR2_IRQHandler
    def_irq_handler    Reserved264_IRQHandler
    def_irq_handler    Reserved265_IRQHandler
    def_irq_handler    Reserved266_IRQHandler
    def_irq_handler    Reserved267_IRQHandler
    def_irq_handler    Reserved268_IRQHandler
    def_irq_handler    Reserved269_IRQHandler
    def_irq_handler    Reserved270_IRQHandler
    def_irq_handler    Reserved271_IRQHandler
    def_irq_handler    Reserved272_IRQHandler
    def_irq_handler    Reserved273_IRQHandler
    def_irq_handler    Reserved274_IRQHandler
    def_irq_handler    Reserved275_IRQHandler
    def_irq_handler    Reserved276_IRQHandler
    def_irq_handler    Reserved277_IRQHandler
    def_irq_handler    Reserved278_IRQHandler
    def_irq_handler    Reserved279_IRQHandler
    def_irq_handler    Reserved280_IRQHandler
    def_irq_handler    Reserved281_IRQHandler
    def_irq_handler    DMA5_3_0_1_DriverIRQHandler
    def_irq_handler    DMA5_3_2_3_DriverIRQHandler
    def_irq_handler    DMA5_3_4_5_DriverIRQHandler
    def_irq_handler    DMA5_3_6_7_DriverIRQHandler
    def_irq_handler    DMA5_3_8_9_DriverIRQHandler
    def_irq_handler    DMA5_3_10_11_DriverIRQHandler
    def_irq_handler    DMA5_3_12_13_DriverIRQHandler
    def_irq_handler    DMA5_3_14_15_DriverIRQHandler
    def_irq_handler    DMA5_3_16_17_DriverIRQHandler
    def_irq_handler    DMA5_3_18_19_DriverIRQHandler
    def_irq_handler    DMA5_3_20_21_DriverIRQHandler
    def_irq_handler    DMA5_3_22_23_DriverIRQHandler
    def_irq_handler    DMA5_3_24_25_DriverIRQHandler
    def_irq_handler    DMA5_3_26_27_DriverIRQHandler
    def_irq_handler    DMA5_3_28_29_DriverIRQHandler
    def_irq_handler    DMA5_3_30_31_DriverIRQHandler
    def_irq_handler    DMA5_3_32_33_DriverIRQHandler
    def_irq_handler    DMA5_3_34_35_DriverIRQHandler
    def_irq_handler    DMA5_3_36_37_DriverIRQHandler
    def_irq_handler    DMA5_3_38_39_DriverIRQHandler
    def_irq_handler    DMA5_3_40_41_DriverIRQHandler
    def_irq_handler    DMA5_3_42_43_DriverIRQHandler
    def_irq_handler    DMA5_3_44_45_DriverIRQHandler
    def_irq_handler    DMA5_3_46_47_DriverIRQHandler
    def_irq_handler    DMA5_3_48_49_DriverIRQHandler
    def_irq_handler    DMA5_3_50_51_DriverIRQHandler
    def_irq_handler    DMA5_3_52_53_DriverIRQHandler
    def_irq_handler    DMA5_3_54_55_DriverIRQHandler
    def_irq_handler    DMA5_3_56_57_DriverIRQHandler
    def_irq_handler    DMA5_3_58_59_DriverIRQHandler
    def_irq_handler    DMA5_3_60_61_DriverIRQHandler
    def_irq_handler    DMA5_3_62_63_DriverIRQHandler
    def_irq_handler    Reserved314_IRQHandler
    def_irq_handler    Reserved315_IRQHandler
    def_irq_handler    Reserved316_IRQHandler
    def_irq_handler    Reserved317_IRQHandler
    def_irq_handler    Reserved318_IRQHandler
    def_irq_handler    Reserved319_IRQHandler
    def_irq_handler    Reserved320_IRQHandler
    def_irq_handler    Reserved321_IRQHandler
    def_irq_handler    Reserved322_IRQHandler
    def_irq_handler    Reserved323_IRQHandler
    def_irq_handler    Reserved324_IRQHandler
    def_irq_handler    Reserved325_IRQHandler
    def_irq_handler    Reserved326_IRQHandler
    def_irq_handler    Reserved327_IRQHandler
    def_irq_handler    Reserved328_IRQHandler
    def_irq_handler    Reserved329_IRQHandler
    def_irq_handler    Reserved330_IRQHandler
    def_irq_handler    Reserved331_IRQHandler
    def_irq_handler    Reserved332_IRQHandler
    def_irq_handler    Reserved333_IRQHandler
    def_irq_handler    Reserved334_IRQHandler
    def_irq_handler    Reserved335_IRQHandler
    def_irq_handler    Reserved336_IRQHandler
    def_irq_handler    Reserved337_IRQHandler
    def_irq_handler    Reserved338_IRQHandler
    def_irq_handler    Reserved339_IRQHandler
    def_irq_handler    Reserved340_IRQHandler
    def_irq_handler    Reserved341_IRQHandler
    def_irq_handler    Reserved342_IRQHandler
    def_irq_handler    Reserved343_IRQHandler
    def_irq_handler    Reserved344_IRQHandler
    def_irq_handler    Reserved345_IRQHandler
    def_irq_handler    Reserved346_IRQHandler
    def_irq_handler    Reserved347_IRQHandler
    def_irq_handler    Reserved348_IRQHandler
    def_irq_handler    Reserved349_IRQHandler
    def_irq_handler    Reserved350_IRQHandler
    def_irq_handler    Reserved351_IRQHandler
    def_irq_handler    Reserved352_IRQHandler
    def_irq_handler    Reserved353_IRQHandler
    def_irq_handler    Reserved354_IRQHandler
    def_irq_handler    Reserved355_IRQHandler
    def_irq_handler    Reserved356_IRQHandler
    def_irq_handler    Reserved357_IRQHandler
    def_irq_handler    Reserved358_IRQHandler
    def_irq_handler    Reserved359_IRQHandler
    def_irq_handler    Reserved360_IRQHandler
    def_irq_handler    Reserved361_IRQHandler
    def_irq_handler    Reserved362_IRQHandler
    def_irq_handler    Reserved363_IRQHandler
    def_irq_handler    Reserved364_IRQHandler
    def_irq_handler    Reserved365_IRQHandler
    def_irq_handler    Reserved366_IRQHandler
    def_irq_handler    Reserved367_IRQHandler
    def_irq_handler    Reserved368_IRQHandler
    def_irq_handler    Reserved369_IRQHandler
    def_irq_handler    Reserved370_IRQHandler
    def_irq_handler    Reserved371_IRQHandler
    def_irq_handler    Reserved372_IRQHandler
    def_irq_handler    Reserved373_IRQHandler
    def_irq_handler    Reserved374_IRQHandler
    def_irq_handler    Reserved375_IRQHandler
    def_irq_handler    Reserved376_IRQHandler
    def_irq_handler    DMA5_4_ERROR_DriverIRQHandler
    def_irq_handler    DMA5_4_0_1_DriverIRQHandler
    def_irq_handler    DMA5_4_2_3_DriverIRQHandler
    def_irq_handler    DMA5_4_4_5_DriverIRQHandler
    def_irq_handler    DMA5_4_6_7_DriverIRQHandler
    def_irq_handler    DMA5_4_8_9_DriverIRQHandler
    def_irq_handler    DMA5_4_10_11_DriverIRQHandler
    def_irq_handler    DMA5_4_12_13_DriverIRQHandler
    def_irq_handler    DMA5_4_14_15_DriverIRQHandler
    def_irq_handler    DMA5_4_16_17_DriverIRQHandler
    def_irq_handler    DMA5_4_18_19_DriverIRQHandler
    def_irq_handler    DMA5_4_20_21_DriverIRQHandler
    def_irq_handler    DMA5_4_22_23_DriverIRQHandler
    def_irq_handler    DMA5_4_24_25_DriverIRQHandler
    def_irq_handler    DMA5_4_26_27_DriverIRQHandler
    def_irq_handler    DMA5_4_28_29_DriverIRQHandler
    def_irq_handler    DMA5_4_30_31_DriverIRQHandler
    def_irq_handler    Reserved394_IRQHandler
    def_irq_handler    Reserved395_IRQHandler
    def_irq_handler    Reserved396_IRQHandler
    def_irq_handler    Reserved397_IRQHandler
    def_irq_handler    Reserved398_IRQHandler
    def_irq_handler    Reserved399_IRQHandler
    def_irq_handler    Reserved400_IRQHandler
    def_irq_handler    Reserved401_IRQHandler

    .end
