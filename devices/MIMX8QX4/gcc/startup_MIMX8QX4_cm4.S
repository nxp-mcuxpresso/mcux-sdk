/* ------------------------------------------------------------------------- */
/*  @file:    startup_MIMX8QX4_cm4.s                                         */
/*  @purpose: CMSIS Cortex-M4 Core Device Startup File                       */
/*            MIMX8QX4_cm4                                                   */
/*  @version: 4.0                                                            */
/*  @date:    2020-6-19                                                      */
/*  @build:   b201113                                                        */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright 1997-2016 Freescale Semiconductor, Inc.                         */
/* Copyright 2016-2020 NXP                                                   */
/* All rights reserved.                                                      */
/*                                                                           */
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
#ifdef __STARTUP_CONFIG_DDR_ALIAS
    .long   Reset_Handler+0x80000000
#else
    .long   Reset_Handler                                   /* Reset Handler */
#endif
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
    .long   Reserved16_IRQHandler                           /* Reserved*/
    .long   Reserved17_IRQHandler                           /* Reserved*/
    .long   Reserved18_IRQHandler                           /* Reserved*/
    .long   Reserved19_IRQHandler                           /* Reserved*/
    .long   Reserved20_IRQHandler                           /* Reserved*/
    .long   M4_MCM_IRQHandler                               /* MCM IRQ*/
    .long   Reserved22_IRQHandler                           /* Reserved*/
    .long   Reserved23_IRQHandler                           /* Reserved*/
    .long   Reserved24_IRQHandler                           /* Reserved*/
    .long   Reserved25_IRQHandler                           /* Reserved*/
    .long   Reserved26_IRQHandler                           /* Reserved*/
    .long   Reserved27_IRQHandler                           /* Reserved*/
    .long   Reserved28_IRQHandler                           /* Reserved*/
    .long   Reserved29_IRQHandler                           /* Reserved*/
    .long   Reserved30_IRQHandler                           /* Reserved*/
    .long   Reserved31_IRQHandler                           /* Reserved*/
    .long   Reserved32_IRQHandler                           /* Reserved*/
    .long   Reserved33_IRQHandler                           /* Reserved*/
    .long   Reserved34_IRQHandler                           /* Reserved*/
    .long   M4_TPM_IRQHandler                               /* Timer PWM Module*/
    .long   Reserved36_IRQHandler                           /* Reserved*/
    .long   Reserved37_IRQHandler                           /* Reserved*/
    .long   M4_LPIT_IRQHandler                              /* Low-Power Periodic Interrupt Timer*/
    .long   Reserved39_IRQHandler                           /* Reserved*/
    .long   Reserved40_IRQHandler                           /* Reserved*/
    .long   M4_LPUART_IRQHandler                            /* Low Power UART*/
    .long   Reserved42_IRQHandler                           /* Reserved*/
    .long   M4_LPI2C_IRQHandler                             /* Low-Power I2C - Logical OR of master and slave interrupts*/
    .long   Reserved44_IRQHandler                           /* Reserved*/
    .long   M4_MU0_B0_IRQHandler                            /* Messaging Unit 0 (IPC with other subsystems) - Side B (local), Port 0, Logical OR of all general-purpose, TX, and RX interrupts*/
    .long   Reserved46_IRQHandler                           /* Reserved*/
    .long   Reserved47_IRQHandler                           /* Reserved*/
    .long   IRQSTEER_0_IRQHandler                           /* External interrupt 0*/
    .long   IRQSTEER_1_IRQHandler                           /* External interrupt 1*/
    .long   IRQSTEER_2_IRQHandler                           /* External interrupt 2*/
    .long   IRQSTEER_3_IRQHandler                           /* External interrupt 3*/
    .long   IRQSTEER_4_IRQHandler                           /* External interrupt 4*/
    .long   IRQSTEER_5_IRQHandler                           /* External interrupt 5*/
    .long   IRQSTEER_6_IRQHandler                           /* External interrupt 6*/
    .long   IRQSTEER_7_IRQHandler                           /* External interrupt 7*/
    .long   Reserved56_IRQHandler                           /* Reserved*/
    .long   Reserved57_IRQHandler                           /* Reserved*/
    .long   Reserved58_IRQHandler                           /* Reserved*/
    .long   Reserved59_IRQHandler                           /* Reserved*/
    .long   M4_MU0_B1_IRQHandler                            /* Messaging Unit 0 (IPC with other subsystems) - Side B (local), Port 1, Logical OR of all general-purpose, TX, and RX interrupts*/
    .long   M4_MU0_B2_IRQHandler                            /* Messaging Unit 0 (IPC with other subsystems) - Side B (local), Port 2, Logical OR of all general-purpose, TX, and RX interrupts*/
    .long   M4_MU0_B3_IRQHandler                            /* Messaging Unit 0 (IPC with other subsystems) - Side B (local), Port 3, Logical OR of all general-purpose, TX, and RX interrupts*/
    .long   Reserved63_IRQHandler                           /* Reserved*/
    .long   Reserved64_IRQHandler                           /* Reserved*/
    .long   M4_MU1_A_IRQHandler                             /* Messaging Unit 1 (IPC with System Controller) - Side A (MCU), Logical OR of all general-purpose, TX, and RX interrupts*/
    .long   M4_SW_IRQHandler                                /* Software interrupt (asserted/cleared via NVIC registers, INTISR[50] input tied low)*/
    .long   Reserved67_IRQHandler                           /* xxx Interrupt 67*/
    .long   Reserved68_IRQHandler                           /* xxx Interrupt 68*/
    .long   Reserved69_IRQHandler                           /* xxx Interrupt 69*/
    .long   Reserved70_IRQHandler                           /* xxx Interrupt 70*/
    .long   Reserved71_IRQHandler                           /* xxx Interrupt 71*/
    .long   Reserved72_IRQHandler                           /* xxx Interrupt 72*/
    .long   Reserved73_IRQHandler                           /* xxx Interrupt 73*/
    .long   Reserved74_IRQHandler                           /* xxx Interrupt 74*/
    .long   Reserved75_IRQHandler                           /* xxx Interrupt 75*/
    .long   Reserved76_IRQHandler                           /* xxx Interrupt 76*/
    .long   Reserved77_IRQHandler                           /* xxx Interrupt 77*/
    .long   Reserved78_IRQHandler                           /* xxx Interrupt 78*/
    .long   Reserved79_IRQHandler                           /* xxx Interrupt 79*/
    .long   Reserved80_IRQHandler                           /* xxx Interrupt 80*/
    .long   Reserved81_IRQHandler                           /* xxx Interrupt 81*/
    .long   Reserved82_IRQHandler                           /* xxx Interrupt 82*/
    .long   Reserved83_IRQHandler                           /* xxx Interrupt 83*/
    .long   Reserved84_IRQHandler                           /* xxx Interrupt 84*/
    .long   Reserved85_IRQHandler                           /* xxx Interrupt 85*/
    .long   Reserved86_IRQHandler                           /* xxx Interrupt 86*/
    .long   Reserved87_IRQHandler                           /* xxx Interrupt 87*/
    .long   Reserved88_IRQHandler                           /* xxx Interrupt 88*/
    .long   Reserved89_IRQHandler                           /* xxx Interrupt 89*/
    .long   Reserved90_IRQHandler                           /* xxx Interrupt 90*/
    .long   Reserved91_IRQHandler                           /* xxx Interrupt 91*/
    .long   Reserved92_IRQHandler                           /* xxx Interrupt 92*/
    .long   Reserved93_IRQHandler                           /* xxx Interrupt 93*/
    .long   Reserved94_IRQHandler                           /* xxx Interrupt 94*/
    .long   Reserved95_IRQHandler                           /* xxx Interrupt 95*/
    .long   Reserved96_IRQHandler                           /* xxx Interrupt 96*/
    .long   Reserved97_IRQHandler                           /* xxx Interrupt 97*/
    .long   Reserved98_IRQHandler                           /* xxx Interrupt 98*/
    .long   A35_NINTERRIRQ_IRQHandler                       /* Shared Int Source nINTERRIRQ from A35 Sub-System*/
    .long   A35_NEXTERRIRQ_IRQHandler                       /* Shared Int Source nEXTERRIRQ from A35 Sub-System*/
    .long   Reserved101_IRQHandler                          /* xxx Interrupt 101*/
    .long   Reserved102_IRQHandler                          /* xxx Interrupt 102*/
    .long   Reserved103_IRQHandler                          /* xxx Interrupt 103*/
    .long   Reserved104_IRQHandler                          /* xxx Interrupt 104*/
    .long   Reserved105_IRQHandler                          /* xxx Interrupt 105*/
    .long   Reserved106_IRQHandler                          /* xxx Interrupt 106*/
    .long   Reserved107_IRQHandler                          /* xxx Interrupt 107*/
    .long   Reserved108_IRQHandler                          /* xxx Interrupt 108*/
    .long   Reserved109_IRQHandler                          /* xxx Interrupt 109*/
    .long   Reserved110_IRQHandler                          /* xxx Interrupt 110*/
    .long   Reserved111_IRQHandler                          /* xxx Interrupt 111*/
    .long   Reserved112_IRQHandler                          /* xxx Interrupt 112*/
    .long   Reserved113_IRQHandler                          /* xxx Interrupt 113*/
    .long   Reserved114_IRQHandler                          /* xxx Interrupt 114*/
    .long   M4_INT_OUT0_IRQHandler                          /* Shared Int Source INT_OUT[0] from M4 Sub-System*/
    .long   M4_INT_OUT1_IRQHandler                          /* Shared Int Source INT_OUT[1] from M4 Sub-System*/
    .long   M4_INT_OUT2_IRQHandler                          /* Shared Int Source INT_OUT[2] from M4 Sub-System*/
    .long   M4_INT_OUT3_IRQHandler                          /* Shared Int Source INT_OUT[3] from M4 Sub-System*/
    .long   M4_INT_OUT4_IRQHandler                          /* Shared Int Source INT_OUT[4] from M4 Sub-System*/
    .long   M4_INT_OUT5_IRQHandler                          /* Shared Int Source INT_OUT[5] from M4 Sub-System*/
    .long   M4_INT_OUT6_IRQHandler                          /* Shared Int Source INT_OUT[6] from M4 Sub-System*/
    .long   M4_INT_OUT7_IRQHandler                          /* Shared Int Source INT_OUT[7] from M4 Sub-System*/
    .long   Reserved123_IRQHandler                          /* xxx Interrupt 123*/
    .long   Reserved124_IRQHandler                          /* xxx Interrupt 124*/
    .long   Reserved125_IRQHandler                          /* xxx Interrupt 125*/
    .long   Reserved126_IRQHandler                          /* xxx Interrupt 126*/
    .long   Reserved127_IRQHandler                          /* xxx Interrupt 127*/
    .long   Reserved128_IRQHandler                          /* xxx Interrupt 128*/
    .long   Reserved129_IRQHandler                          /* xxx Interrupt 129*/
    .long   Reserved130_IRQHandler                          /* xxx Interrupt 130*/
    .long   Reserved131_IRQHandler                          /* xxx Interrupt 131*/
    .long   Reserved132_IRQHandler                          /* xxx Interrupt 132*/
    .long   Reserved133_IRQHandler                          /* xxx Interrupt 133*/
    .long   Reserved134_IRQHandler                          /* xxx Interrupt 134*/
    .long   Reserved135_IRQHandler                          /* xxx Interrupt 135*/
    .long   Reserved136_IRQHandler                          /* xxx Interrupt 136*/
    .long   Reserved137_IRQHandler                          /* xxx Interrupt 137*/
    .long   Reserved138_IRQHandler                          /* xxx Interrupt 138*/
    .long   DISPLAY0_INT_OUT0_IRQHandler                    /* Shared Int Source INT_OUT[0] from Display0 Sub-System*/
    .long   DISPLAY0_INT_OUT1_IRQHandler                    /* Shared Int Source INT_OUT[1] from Display0 Sub-System*/
    .long   DISPLAY0_INT_OUT2_IRQHandler                    /* Shared Int Source INT_OUT[2] from Display0 Sub-System*/
    .long   DISPLAY0_INT_OUT3_IRQHandler                    /* Shared Int Source INT_OUT[3] from Display0 Sub-System*/
    .long   DISPLAY0_INT_OUT4_IRQHandler                    /* Shared Int Source INT_OUT[4] from Display0 Sub-System*/
    .long   DISPLAY0_INT_OUT5_IRQHandler                    /* Shared Int Source INT_OUT[5] from Display0 Sub-System*/
    .long   DISPLAY0_INT_OUT6_IRQHandler                    /* Shared Int Source INT_OUT[6] from Display0 Sub-System*/
    .long   DISPLAY0_INT_OUT7_IRQHandler                    /* Shared Int Source INT_OUT[7] from Display0 Sub-System*/
    .long   DISPLAY0_RESERVED_IRQHandler                    /* Shared Int Source Reserved from Display0 Sub-System*/
    .long   DISPLAY0_INT_OUT9_IRQHandler                    /* Shared Int Source INT_OUT[9] from Display0 Sub-System*/
    .long   DISPLAY0_INT_OUT10_IRQHandler                   /* Shared Int Source INT_OUT[10] from Display0 Sub-System*/
    .long   DISPLAY0_INT_OUT11_IRQHandler                   /* Shared Int Source INT_OUT[11] from Display0 Sub-System*/
    .long   DISPLAY0_INT_OUT12_IRQHandler                   /* Shared Int Source INT_OUT[12] from Display0 Sub-System*/
    .long   Reserved152_IRQHandler                          /* xxx Interrupt 152*/
    .long   Reserved153_IRQHandler                          /* xxx Interrupt 153*/
    .long   Reserved154_IRQHandler                          /* xxx Interrupt 154*/
    .long   Reserved155_IRQHandler                          /* xxx Interrupt 155*/
    .long   Reserved156_IRQHandler                          /* xxx Interrupt 156*/
    .long   Reserved157_IRQHandler                          /* xxx Interrupt 157*/
    .long   MIPI_DSI0_INT_OUT_IRQHandler                    /* Shared Int Source INT_OUT from MIPI_DSI0 Sub-System*/
    .long   MIPI_DSI1_INT_OUT_IRQHandler                    /* Shared Int Source INT_OUT from MIPI_DSI1 Sub-System*/
    .long   Reserved160_IRQHandler                          /* xxx Interrupt 160*/
    .long   LCD_MOD_INT_IRQHandler                          /* Shared Int Source INT_OUT from ADMA Sub-System*/
    .long   LCD_PWM_INT_IRQHandler                          /* Shared Int Source INT_OUT from ADMA Sub-System*/
    .long   GPU0_XAQ2_INTR_IRQHandler                       /* Shared Int Source xaq2_intr from GPU0 Sub-System*/
    .long   Reserved164_IRQHandler                          /* xxx Interrupt 164*/
    .long   ADMA_EDMA2_INT_IRQHandler                       /* Shared Int Source eDMA2_INT from ADMA Sub-System*/
    .long   ADMA_EDMA2_ERR_INT_IRQHandler                   /* Shared Int Source eDMA2_ERR_INT from ADMA Sub-System*/
    .long   ADMA_EDMA3_INT_IRQHandler                       /* Shared Int Source eDMA3_INT from ADMA Sub-System*/
    .long   ADMA_EDMA3_ERR_INT_IRQHandler                   /* Shared Int Source eDMA3_ERR_INT from ADMA Sub-System*/
    .long   Reserved169_IRQHandler                          /* xxx Interrupt 169*/
    .long   Reserved170_IRQHandler                          /* xxx Interrupt 170*/
    .long   Reserved171_IRQHandler                          /* xxx Interrupt 171*/
    .long   Reserved172_IRQHandler                          /* xxx Interrupt 172*/
    .long   Reserved173_IRQHandler                          /* xxx Interrupt 173*/
    .long   Reserved174_IRQHandler                          /* xxx Interrupt 174*/
    .long   Reserved175_IRQHandler                          /* xxx Interrupt 175*/
    .long   Reserved176_IRQHandler                          /* xxx Interrupt 176*/
    .long   Reserved177_IRQHandler                          /* xxx Interrupt 177*/
    .long   Reserved178_IRQHandler                          /* xxx Interrupt 178*/
    .long   LSIO_GPT0_INT_IRQHandler                        /* Shared Int Source GPT0_INT from LSIO Sub-System*/
    .long   LSIO_GPT1_INT_IRQHandler                        /* Shared Int Source GPT1_INT from LSIO Sub-System*/
    .long   LSIO_GPT2_INT_IRQHandler                        /* Shared Int Source GPT2_INT from LSIO Sub-System*/
    .long   LSIO_GPT3_INT_IRQHandler                        /* Shared Int Source GPT3_INT from LSIO Sub-System*/
    .long   LSIO_GPT4_INT_IRQHandler                        /* Shared Int Source GPT4_INT from LSIO Sub-System*/
    .long   LSIO_KPP_INT_IRQHandler                         /* Shared Int Source KPP_INT from LSIO Sub-System*/
    .long   Reserved185_IRQHandler                          /* xxx Interrupt 185*/
    .long   Reserved186_IRQHandler                          /* xxx Interrupt 186*/
    .long   Reserved187_IRQHandler                          /* xxx Interrupt 187*/
    .long   Reserved188_IRQHandler                          /* xxx Interrupt 188*/
    .long   Reserved189_IRQHandler                          /* xxx Interrupt 189*/
    .long   Reserved190_IRQHandler                          /* xxx Interrupt 190*/
    .long   LSIO_OCTASPI0_INT_IRQHandler                    /* Shared Int Source OctaSPI0_INT from LSIO Sub-System*/
    .long   LSIO_OCTASPI1_INT_IRQHandler                    /* Shared Int Source OctaSPI1_INT from LSIO Sub-System*/
    .long   LSIO_PWM0_INT_IRQHandler                        /* Shared Int Source PWM0_INT from LSIO Sub-System*/
    .long   LSIO_PWM1_INT_IRQHandler                        /* Shared Int Source PWM1_INT from LSIO Sub-System*/
    .long   LSIO_PWM2_INT_IRQHandler                        /* Shared Int Source PWM2_INT from LSIO Sub-System*/
    .long   LSIO_PWM3_INT_IRQHandler                        /* Shared Int Source PWM3_INT from LSIO Sub-System*/
    .long   LSIO_PWM4_INT_IRQHandler                        /* Shared Int Source PWM4_INT from LSIO Sub-System*/
    .long   LSIO_PWM5_INT_IRQHandler                        /* Shared Int Source PWM5_INT from LSIO Sub-System*/
    .long   LSIO_PWM6_INT_IRQHandler                        /* Shared Int Source PWM6_INT from LSIO Sub-System*/
    .long   LSIO_PWM7_INT_IRQHandler                        /* Shared Int Source PWM7_INT from LSIO Sub-System*/
    .long   HSIO_PCIEB_MSI_CTRL_INT_IRQHandler              /* Shared Int Source PCIeB_MSI_CTRL_INT from HSIO Sub-System*/
    .long   HSIO_PCIEB_CLK_REQ_INT_IRQHandler               /* Shared Int Source PCIeB_CLK_REQ_INT from HSIO Sub-System*/
    .long   HSIO_PCIEB_DMA_INT_IRQHandler                   /* Shared Int Source PCIeB_DMA_INT from HSIO Sub-System*/
    .long   HSIO_PCIEB_INT_D_IRQHandler                     /* Shared Int Source PCIeB_INT_D from HSIO Sub-System*/
    .long   HSIO_PCIEB_INT_C_IRQHandler                     /* Shared Int Source PCIeB_INT_C from HSIO Sub-System*/
    .long   HSIO_PCIEB_INT_B_IRQHandler                     /* Shared Int Source PCIeB_INT_B from HSIO Sub-System*/
    .long   HSIO_PCIEB_INT_A_IRQHandler                     /* Shared Int Source PCIeB_INT_A from HSIO Sub-System*/
    .long   HSIO_PCIEB_SMLH_REQ_RST_IRQHandler              /* Shared Int Source PCIeB_SMLH_REQ_RST from HSIO Sub-System*/
    .long   HSIO_PCIEB_GPIO_WAKEUP0_IRQHandler              /* Shared Int Source PCIeB_GPIO_WAKEUP[0] from HSIO Sub-System*/
    .long   HSIO_PCIEB_GPIO_WAKEUP1_IRQHandler              /* Shared Int Source PCIeB_GPIO_WAKEUP[1] from HSIO Sub-System*/
    .long   SCU_INT_OUT0_IRQHandler                         /* Shared Int Source INT_OUT[0] from SCU Sub-System*/
    .long   SCU_INT_OUT1_IRQHandler                         /* Shared Int Source INT_OUT[1] from SCU Sub-System*/
    .long   SCU_INT_OUT2_IRQHandler                         /* Shared Int Source INT_OUT[2] from SCU Sub-System*/
    .long   SCU_INT_OUT3_IRQHandler                         /* Shared Int Source INT_OUT[3] from SCU Sub-System*/
    .long   SCU_INT_OUT4_IRQHandler                         /* Shared Int Source INT_OUT[4] from SCU Sub-System*/
    .long   SCU_INT_OUT5_IRQHandler                         /* Shared Int Source INT_OUT[5] from SCU Sub-System*/
    .long   SCU_INT_OUT6_IRQHandler                         /* Shared Int Source INT_OUT[6] from SCU Sub-System*/
    .long   SCU_INT_OUT7_IRQHandler                         /* Shared Int Source INT_OUT[7] from SCU Sub-System*/
    .long   SCU_SYS_COUNT_INT0_IRQHandler                   /* Shared Int Source SYS_COUNT_INT0 from SCU Sub-System*/
    .long   SCU_SYS_COUNT_INT1_IRQHandler                   /* Shared Int Source SYS_COUNT_INT1 from SCU Sub-System*/
    .long   SCU_SYS_COUNT_INT2_IRQHandler                   /* Shared Int Source SYS_COUNT_INT2 from SCU Sub-System*/
    .long   SCU_SYS_COUNT_INT3_IRQHandler                   /* Shared Int Source SYS_COUNT_INT3 from SCU Sub-System*/
    .long   Reserved223_IRQHandler                          /* xxx Interrupt 223*/
    .long   Reserved224_IRQHandler                          /* xxx Interrupt 224*/
    .long   Reserved225_IRQHandler                          /* xxx Interrupt 225*/
    .long   Reserved226_IRQHandler                          /* xxx Interrupt 226*/
    .long   DRC_ECC_CORRECT_INT_IRQHandler                  /* Shared Int Source ECC_CORRECT_INT from DRC Sub-System*/
    .long   DRC_ECC_NCORRECT_INT_IRQHandler                 /* Shared Int Source ECC_NCORRECT_INT from DRC Sub-System*/
    .long   DRC_SBR_DONE_INT_IRQHandler                     /* Shared Int Source SBR_DONE_INT from DRC Sub-System*/
    .long   DRC_PERF_CNT_INT_IRQHandler                     /* Shared Int Source PERF_CNT_INT from DRC Sub-System*/
    .long   Reserved231_IRQHandler                          /* xxx Interrupt 231*/
    .long   Reserved232_IRQHandler                          /* xxx Interrupt 232*/
    .long   Reserved233_IRQHandler                          /* xxx Interrupt 233*/
    .long   Reserved234_IRQHandler                          /* xxx Interrupt 234*/
    .long   LSIO_GPIO_INT0_IRQHandler                       /* Shared Int Source GPIO_INT[0] from LSIO Sub-System*/
    .long   LSIO_GPIO_INT1_IRQHandler                       /* Shared Int Source GPIO_INT[1] from LSIO Sub-System*/
    .long   LSIO_GPIO_INT2_IRQHandler                       /* Shared Int Source GPIO_INT[2] from LSIO Sub-System*/
    .long   LSIO_GPIO_INT3_IRQHandler                       /* Shared Int Source GPIO_INT[3] from LSIO Sub-System*/
    .long   LSIO_GPIO_INT4_IRQHandler                       /* Shared Int Source GPIO_INT[4] from LSIO Sub-System*/
    .long   LSIO_GPIO_INT5_IRQHandler                       /* Shared Int Source GPIO_INT[5] from LSIO Sub-System*/
    .long   LSIO_GPIO_INT6_IRQHandler                       /* Shared Int Source GPIO_INT[6] from LSIO Sub-System*/
    .long   LSIO_GPIO_INT7_IRQHandler                       /* Shared Int Source GPIO_INT[7] from LSIO Sub-System*/
    .long   Reserved243_IRQHandler                          /* xxx Interrupt 243*/
    .long   Reserved244_IRQHandler                          /* xxx Interrupt 244*/
    .long   Reserved245_IRQHandler                          /* xxx Interrupt 245*/
    .long   Reserved246_IRQHandler                          /* xxx Interrupt 246*/
    .long   Reserved247_IRQHandler                          /* xxx Interrupt 247*/
    .long   Reserved248_IRQHandler                          /* xxx Interrupt 248*/
    .long   Reserved249_IRQHandler                          /* xxx Interrupt 249*/
    .long   Reserved250_IRQHandler                          /* xxx Interrupt 250*/
    .long   Reserved251_IRQHandler                          /* xxx Interrupt 251*/
    .long   Reserved252_IRQHandler                          /* xxx Interrupt 252*/
    .long   Reserved253_IRQHandler                          /* xxx Interrupt 253*/
    .long   Reserved254_IRQHandler                          /* xxx Interrupt 254*/
    .long   Reserved255_IRQHandler                          /* xxx Interrupt 255*/
    .long   Reserved256_IRQHandler                          /* xxx Interrupt 256*/
    .long   Reserved257_IRQHandler                          /* xxx Interrupt 257*/
    .long   Reserved258_IRQHandler                          /* xxx Interrupt 258*/
    .long   Reserved259_IRQHandler                          /* xxx Interrupt 259*/
    .long   Reserved260_IRQHandler                          /* xxx Interrupt 260*/
    .long   Reserved261_IRQHandler                          /* xxx Interrupt 261*/
    .long   Reserved262_IRQHandler                          /* xxx Interrupt 262*/
    .long   Reserved263_IRQHandler                          /* xxx Interrupt 263*/
    .long   Reserved264_IRQHandler                          /* xxx Interrupt 264*/
    .long   Reserved265_IRQHandler                          /* xxx Interrupt 265*/
    .long   Reserved266_IRQHandler                          /* xxx Interrupt 266*/
    .long   Reserved267_IRQHandler                          /* xxx Interrupt 267*/
    .long   Reserved268_IRQHandler                          /* xxx Interrupt 268*/
    .long   Reserved269_IRQHandler                          /* xxx Interrupt 269*/
    .long   Reserved270_IRQHandler                          /* xxx Interrupt 270*/
    .long   Reserved271_IRQHandler                          /* xxx Interrupt 271*/
    .long   Reserved272_IRQHandler                          /* xxx Interrupt 272*/
    .long   Reserved273_IRQHandler                          /* xxx Interrupt 273*/
    .long   Reserved274_IRQHandler                          /* xxx Interrupt 274*/
    .long   LSIO_MU0_INT_IRQHandler                         /* Shared Int Source MU0_INT from LSIO Sub-System*/
    .long   LSIO_MU1_INT_IRQHandler                         /* Shared Int Source MU1_INT from LSIO Sub-System*/
    .long   LSIO_MU2_INT_IRQHandler                         /* Shared Int Source MU2_INT from LSIO Sub-System*/
    .long   LSIO_MU3_INT_IRQHandler                         /* Shared Int Source MU3_INT from LSIO Sub-System*/
    .long   LSIO_MU4_INT_IRQHandler                         /* Shared Int Source MU4_INT from LSIO Sub-System*/
    .long   Reserved280_IRQHandler                          /* xxx Interrupt 280*/
    .long   Reserved281_IRQHandler                          /* xxx Interrupt 281*/
    .long   Reserved282_IRQHandler                          /* xxx Interrupt 282*/
    .long   LSIO_MU5_INT_A_IRQHandler                       /* Shared Int Source MU5_INT_A from LSIO Sub-System*/
    .long   LSIO_MU6_INT_A_IRQHandler                       /* Shared Int Source MU6_INT_A from LSIO Sub-System*/
    .long   LSIO_MU7_INT_A_IRQHandler                       /* Shared Int Source MU7_INT_A from LSIO Sub-System*/
    .long   LSIO_MU8_INT_A_IRQHandler                       /* Shared Int Source MU8_INT_A from LSIO Sub-System*/
    .long   LSIO_MU9_INT_A_IRQHandler                       /* Shared Int Source MU9_INT_A from LSIO Sub-System*/
    .long   LSIO_MU10_INT_A_IRQHandler                      /* Shared Int Source MU10_INT_A from LSIO Sub-System*/
    .long   LSIO_MU11_INT_A_IRQHandler                      /* Shared Int Source MU11_INT_A from LSIO Sub-System*/
    .long   LSIO_MU12_INT_A_IRQHandler                      /* Shared Int Source MU12_INT_A from LSIO Sub-System*/
    .long   LSIO_MU13_INT_A_IRQHandler                      /* Shared Int Source MU13_INT_A from LSIO Sub-System*/
    .long   Reserved292_IRQHandler                          /* xxx Interrupt 292*/
    .long   Reserved293_IRQHandler                          /* xxx Interrupt 293*/
    .long   Reserved294_IRQHandler                          /* xxx Interrupt 294*/
    .long   Reserved295_IRQHandler                          /* xxx Interrupt 295*/
    .long   Reserved296_IRQHandler                          /* xxx Interrupt 296*/
    .long   Reserved297_IRQHandler                          /* xxx Interrupt 297*/
    .long   Reserved298_IRQHandler                          /* xxx Interrupt 298*/
    .long   LSIO_MU5_INT_B_IRQHandler                       /* Shared Int Source MU5_INT_B from LSIO Sub-System*/
    .long   LSIO_MU6_INT_B_IRQHandler                       /* Shared Int Source MU6_INT_B from LSIO Sub-System*/
    .long   LSIO_MU7_INT_B_IRQHandler                       /* Shared Int Source MU7_INT_B from LSIO Sub-System*/
    .long   LSIO_MU8_INT_B_IRQHandler                       /* Shared Int Source MU8_INT_B from LSIO Sub-System*/
    .long   LSIO_MU9_INT_B_IRQHandler                       /* Shared Int Source MU9_INT_B from LSIO Sub-System*/
    .long   LSIO_MU10_INT_B_IRQHandler                      /* Shared Int Source MU10_INT_B from LSIO Sub-System*/
    .long   LSIO_MU11_INT_B_IRQHandler                      /* Shared Int Source MU11_INT_B from LSIO Sub-System*/
    .long   LSIO_MU12_INT_B_IRQHandler                      /* Shared Int Source MU12_INT_B from LSIO Sub-System*/
    .long   LSIO_MU13_INT_B_IRQHandler                      /* Shared Int Source MU13_INT_B from LSIO Sub-System*/
    .long   Reserved308_IRQHandler                          /* xxx Interrupt 308*/
    .long   Reserved309_IRQHandler                          /* xxx Interrupt 309*/
    .long   Reserved310_IRQHandler                          /* xxx Interrupt 310*/
    .long   Reserved311_IRQHandler                          /* xxx Interrupt 311*/
    .long   Reserved312_IRQHandler                          /* xxx Interrupt 312*/
    .long   Reserved313_IRQHandler                          /* xxx Interrupt 313*/
    .long   Reserved314_IRQHandler                          /* xxx Interrupt 314*/
    .long   ADMA_SPI0_INT_IRQHandler                        /* Shared Int Source SPI0_INT from ADMA Sub-System*/
    .long   ADMA_SPI1_INT_IRQHandler                        /* Shared Int Source SPI1_INT from ADMA Sub-System*/
    .long   ADMA_SPI2_INT_IRQHandler                        /* Shared Int Source SPI2_INT from ADMA Sub-System*/
    .long   ADMA_SPI3_INT_IRQHandler                        /* Shared Int Source SPI3_INT from ADMA Sub-System*/
    .long   ADMA_I2C0_INT_IRQHandler                        /* Shared Int Source I2C0_INT from ADMA Sub-System*/
    .long   ADMA_I2C1_INT_IRQHandler                        /* Shared Int Source I2C1_INT from ADMA Sub-System*/
    .long   ADMA_I2C2_INT_IRQHandler                        /* Shared Int Source I2C2_INT from ADMA Sub-System*/
    .long   ADMA_I2C3_INT_IRQHandler                        /* Shared Int Source I2C3_INT from ADMA Sub-System*/
    .long   Reserved323_IRQHandler                          /* xxx Interrupt 323*/
    .long   ADMA_UART0_INT_IRQHandler                       /* Shared Int Source UART0_INT from ADMA Sub-System*/
    .long   ADMA_UART1_INT_IRQHandler                       /* Shared Int Source UART1_INT from ADMA Sub-System*/
    .long   ADMA_UART2_INT_IRQHandler                       /* Shared Int Source UART2_INT from ADMA Sub-System*/
    .long   ADMA_UART3_INT_IRQHandler                       /* Shared Int Source UART3_INT from ADMA Sub-System*/
    .long   Reserved328_IRQHandler                          /* xxx Interrupt 328*/
    .long   Reserved329_IRQHandler                          /* xxx Interrupt 329*/
    .long   Reserved330_IRQHandler                          /* xxx Interrupt 330*/
    .long   CONNECTIVITY_USDHC0_INT_IRQHandler              /* Shared Int Source uSDHC0_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_USDHC1_INT_IRQHandler              /* Shared Int Source uSDHC1_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_USDHC2_INT_IRQHandler              /* Shared Int Source uSDHC2_INT from Connectivity Sub-System*/
    .long   ADMA_FLEXCAN0_INT_IRQHandler                    /* Shared Int Source FlexCAN0_INT from ADMA Sub-System*/
    .long   ADMA_FLEXCAN1_INT_IRQHandler                    /* Shared Int Source FlexCAN1_INT from ADMA Sub-System*/
    .long   ADMA_FLEXCAN2_INT_IRQHandler                    /* Shared Int Source FlexCAN2_INT from ADMA Sub-System*/
    .long   ADMA_FTM0_INT_IRQHandler                        /* Shared Int Source FTM0_INT from ADMA Sub-System*/
    .long   ADMA_FTM1_INT_IRQHandler                        /* Shared Int Source FTM1_INT from ADMA Sub-System*/
    .long   ADMA_ADC0_INT_IRQHandler                        /* Shared Int Source ADC0_INT from ADMA Sub-System*/
    .long   Reserved340_IRQHandler                          /* xxx Interrupt 340*/
    .long   ADMA_EXTERNAL_DMA_INT_0_IRQHandler              /* Shared Int Source EXTERNAL_DMA_INT_0 from ADMA Sub-System*/
    .long   ADMA_EXTERNAL_DMA_INT_1_IRQHandler              /* Shared Int Source EXTERNAL_DMA_INT_1 from ADMA Sub-System*/
    .long   ADMA_EXTERNAL_DMA_INT_2_IRQHandler              /* Shared Int Source EXTERNAL_DMA_INT_2 from ADMA Sub-System*/
    .long   ADMA_EXTERNAL_DMA_INT_3_IRQHandler              /* Shared Int Source EXTERNAL_DMA_INT_3 from ADMA Sub-System*/
    .long   ADMA_EXTERNAL_DMA_INT_4_IRQHandler              /* Shared Int Source EXTERNAL_DMA_INT_4 from ADMA Sub-System*/
    .long   ADMA_EXTERNAL_DMA_INT_5_IRQHandler              /* Shared Int Source EXTERNAL_DMA_INT_5 from ADMA Sub-System*/
    .long   Reserved347_IRQHandler                          /* xxx Interrupt 347*/
    .long   Reserved348_IRQHandler                          /* xxx Interrupt 348*/
    .long   Reserved349_IRQHandler                          /* xxx Interrupt 349*/
    .long   Reserved350_IRQHandler                          /* xxx Interrupt 350*/
    .long   Reserved351_IRQHandler                          /* xxx Interrupt 351*/
    .long   Reserved352_IRQHandler                          /* xxx Interrupt 352*/
    .long   Reserved353_IRQHandler                          /* xxx Interrupt 353*/
    .long   Reserved354_IRQHandler                          /* xxx Interrupt 354*/
    .long   CONNECTIVITY_ENET0_FRAME1_INT_IRQHandler        /* Shared Int Source ENET0_FRAME1_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_ENET0_FRAME2_INT_IRQHandler        /* Shared Int Source ENET0_FRAME2_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_ENET0_FRAME0_EVENT_INT_IRQHandler  /* Shared Int Source ENET0_FRAME0_EVENT_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_ENET0_TIMER_INT_IRQHandler         /* Shared Int Source ENET0_TIMER_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_ENET1_FRAME1_INT_IRQHandler        /* Shared Int Source ENET1_FRAME1_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_ENET1_FRAME2_INT_IRQHandler        /* Shared Int Source ENET1_FRAME2_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_ENET1_FRAME0_EVENT_INT_IRQHandler  /* Shared Int Source ENET1_FRAME0_EVENT_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_ENET1_TIMER_INT_IRQHandler         /* Shared Int Source ENET1_TIMER_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_DTCP_INT_IRQHandler                /* Shared Int Source DTCP_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_MLB_INT_IRQHandler                 /* Shared Int Source MLB_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_MLB_AHB_INT_IRQHandler             /* Shared Int Source MLB_AHB_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_USB_OTG_INT_IRQHandler             /* Shared Int Source USB_OTG_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_USB_HOST_INT_IRQHandler            /* Shared Int Source USB_HOST_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_UTMI_INT_IRQHandler                /* Shared Int Source UTMI_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_WAKEUP_INT_IRQHandler              /* Shared Int Source WAKEUP_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_USB3_INT_IRQHandler                /* Shared Int Source USB3_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_ND_FLASH_BCH_INT_IRQHandler        /* Shared Int Source ND_FLASH_BCH_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_ND_FLASH_GPMI_INT_IRQHandler       /* Shared Int Source ND_FLASH_GPMI_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_APBHDMA_IRQHandler                 /* Shared Int Source APBHDMA from Connectivity Sub-System*/
    .long   CONNECTIVITY_DMA_INT_IRQHandler                 /* Shared Int Source DMA_INT from Connectivity Sub-System*/
    .long   CONNECTIVITY_DMA_ERR_INT_IRQHandler             /* Shared Int Source DMA_ERR_INT from Connectivity Sub-System*/
    .long   Reserved376_IRQHandler                          /* xxx Interrupt 376*/
    .long   Reserved377_IRQHandler                          /* xxx Interrupt 377*/
    .long   Reserved378_IRQHandler                          /* xxx Interrupt 378*/
    .long   Reserved379_IRQHandler                          /* xxx Interrupt 379*/
    .long   Reserved380_IRQHandler                          /* xxx Interrupt 380*/
    .long   Reserved381_IRQHandler                          /* xxx Interrupt 381*/
    .long   Reserved382_IRQHandler                          /* xxx Interrupt 382*/
    .long   Reserved383_IRQHandler                          /* xxx Interrupt 383*/
    .long   Reserved384_IRQHandler                          /* xxx Interrupt 384*/
    .long   Reserved385_IRQHandler                          /* xxx Interrupt 385*/
    .long   Reserved386_IRQHandler                          /* xxx Interrupt 386*/
    .long   IMAGING_MSI_INT_IRQHandler                      /* Shared Int Source MSI_INT from Imaging Sub-System*/
    .long   Reserved388_IRQHandler                          /* xxx Interrupt 388*/
    .long   Reserved389_IRQHandler                          /* xxx Interrupt 389*/
    .long   Reserved390_IRQHandler                          /* xxx Interrupt 390*/
    .long   Reserved391_IRQHandler                          /* xxx Interrupt 391*/
    .long   Reserved392_IRQHandler                          /* xxx Interrupt 392*/
    .long   Reserved393_IRQHandler                          /* xxx Interrupt 393*/
    .long   Reserved394_IRQHandler                          /* xxx Interrupt 394*/
    .long   Reserved395_IRQHandler                          /* xxx Interrupt 395*/
    .long   IMAGING_PDMA_STREAM0_INT_IRQHandler             /* Shared Int Source PDMA_STREAM0_INT from Imaging Sub-System*/
    .long   IMAGING_PDMA_STREAM1_INT_IRQHandler             /* Shared Int Source PDMA_STREAM1_INT from Imaging Sub-System*/
    .long   IMAGING_PDMA_STREAM2_INT_IRQHandler             /* Shared Int Source PDMA_STREAM2_INT from Imaging Sub-System*/
    .long   IMAGING_PDMA_STREAM3_INT_IRQHandler             /* Shared Int Source PDMA_STREAM3_INT from Imaging Sub-System*/
    .long   IMAGING_PDMA_STREAM4_INT_IRQHandler             /* Shared Int Source PDMA_STREAM4_INT from Imaging Sub-System*/
    .long   IMAGING_PDMA_STREAM5_INT_IRQHandler             /* Shared Int Source PDMA_STREAM5_INT from Imaging Sub-System*/
    .long   IMAGING_PDMA_STREAM6_INT_IRQHandler             /* Shared Int Source PDMA_STREAM6_INT from Imaging Sub-System*/
    .long   IMAGING_PDMA_STREAM7_INT_IRQHandler             /* Shared Int Source PDMA_STREAM7_INT from Imaging Sub-System*/
    .long   IMAGING_MJPEG_ENC0_INT_IRQHandler               /* Shared Int Source MJPEG_ENC0_INT from Imaging Sub-System*/
    .long   IMAGING_MJPEG_ENC1_INT_IRQHandler               /* Shared Int Source MJPEG_ENC1_INT from Imaging Sub-System*/
    .long   IMAGING_MJPEG_ENC2_INT_IRQHandler               /* Shared Int Source MJPEG_ENC2_INT from Imaging Sub-System*/
    .long   IMAGING_MJPEG_ENC3_INT_IRQHandler               /* Shared Int Source MJPEG_ENC3_INT from Imaging Sub-System*/
    .long   IMAGING_MJPEG_DEC0_INT_IRQHandler               /* Shared Int Source MJPEG_DEC0_INT from Imaging Sub-System*/
    .long   IMAGING_MJPEG_DEC1_INT_IRQHandler               /* Shared Int Source MJPEG_DEC1_INT from Imaging Sub-System*/
    .long   IMAGING_MJPEG_DEC2_INT_IRQHandler               /* Shared Int Source MJPEG_DEC2_INT from Imaging Sub-System*/
    .long   IMAGING_MJPEG_DEC3_INT_IRQHandler               /* Shared Int Source MJPEG_DEC3_INT from Imaging Sub-System*/
    .long   Reserved412_IRQHandler                          /* xxx Interrupt 412*/
    .long   ADMA_SAI0_MOD_INT_IRQHandler                    /* Shared Int Source SAI0_MOD_INT from ADMA Sub-System*/
    .long   ADMA_SAI0_DMA_INT_IRQHandler                    /* Shared Int Source SAI0_DMA_INT from ADMA Sub-System*/
    .long   ADMA_SAI1_MOD_INT_IRQHandler                    /* Shared Int Source SAI1_MOD_INT from ADMA Sub-System*/
    .long   ADMA_SAI1_DMA_INT_IRQHandler                    /* Shared Int Source SAI1_DMA_INT from ADMA Sub-System*/
    .long   ADMA_SAI2_MOD_INT_IRQHandler                    /* Shared Int Source SAI2_MOD_INT from ADMA Sub-System*/
    .long   ADMA_SAI2_DMA_INT_IRQHandler                    /* Shared Int Source SAI2_DMA_INT from ADMA Sub-System*/
    .long   MIPI_CSI0_OUT_INT_IRQHandler                    /* Shared Int Source OUT_INT from MIPI_CSI0 Sub-System*/
    .long   Reserved420_IRQHandler                          /* xxx Interrupt 420*/
    .long   Reserved421_IRQHandler                          /* xxx Interrupt 421*/
    .long   ADMA_SAI3_MOD_INT_IRQHandler                    /* Shared Int Source SAI3_MOD_INT from ADMA Sub-System*/
    .long   ADMA_SAI3_DMA_INT_IRQHandler                    /* Shared Int Source SAI3_DMA_INT from ADMA Sub-System*/
    .long   Reserved424_IRQHandler                          /* xxx Interrupt 424*/
    .long   Reserved425_IRQHandler                          /* xxx Interrupt 425*/
    .long   Reserved426_IRQHandler                          /* xxx Interrupt 426*/
    .long   Reserved427_IRQHandler                          /* xxx Interrupt 427*/
    .long   ADMA_SAI4_MOD_INT_IRQHandler                    /* Shared Int Source SAI4_MOD_INT from ADMA Sub-System*/
    .long   ADMA_SAI4_DMA_INT_IRQHandler                    /* Shared Int Source SAI4_DMA_INT from ADMA Sub-System*/
    .long   ADMA_SAI5_MOD_INT_IRQHandler                    /* Shared Int Source SAI5_MOD_INT from ADMA Sub-System*/
    .long   ADMA_SAI5_DMA_INT_IRQHandler                    /* Shared Int Source SAI5_DMA_INT from ADMA Sub-System*/
    .long   Reserved432_IRQHandler                          /* xxx Interrupt 432*/
    .long   Reserved433_IRQHandler                          /* xxx Interrupt 433*/
    .long   Reserved434_IRQHandler                          /* xxx Interrupt 434*/
    .long   ADMA_SPI0_MOD_INT_IRQHandler                    /* Shared Int Source SPI0_MOD_INT from ADMA Sub-System*/
    .long   ADMA_SPI1_MOD_INT_IRQHandler                    /* Shared Int Source SPI1_MOD_INT from ADMA Sub-System*/
    .long   ADMA_SPI2_MOD_INT_IRQHandler                    /* Shared Int Source SPI2_MOD_INT from ADMA Sub-System*/
    .long   ADMA_SPI3_MOD_INT_IRQHandler                    /* Shared Int Source SPI3_MOD_INT from ADMA Sub-System*/
    .long   ADMA_I2C0_MOD_INT_IRQHandler                    /* Shared Int Source I2C0_MOD_INT from ADMA Sub-System*/
    .long   ADMA_I2C1_MOD_INT_IRQHandler                    /* Shared Int Source I2C1_MOD_INT from ADMA Sub-System*/
    .long   ADMA_I2C2_MOD_INT_IRQHandler                    /* Shared Int Source I2C2_MOD_INT from ADMA Sub-System*/
    .long   ADMA_I2C3_MOD_INT_IRQHandler                    /* Shared Int Source I2C3_MOD_INT from ADMA Sub-System*/
    .long   Reserved443_IRQHandler                          /* xxx Interrupt 443*/
    .long   ADMA_UART0_MOD_INT_IRQHandler                   /* Shared Int Source UART0_MOD_INT from ADMA Sub-System*/
    .long   ADMA_UART1_MOD_INT_IRQHandler                   /* Shared Int Source UART1_MOD_INT from ADMA Sub-System*/
    .long   ADMA_UART2_MOD_INT_IRQHandler                   /* Shared Int Source UART2_MOD_INT from ADMA Sub-System*/
    .long   ADMA_UART3_MOD_INT_IRQHandler                   /* Shared Int Source UART3_MOD_INT from ADMA Sub-System*/
    .long   Reserved448_IRQHandler                          /* xxx Interrupt 448*/
    .long   Reserved449_IRQHandler                          /* xxx Interrupt 449*/
    .long   Reserved450_IRQHandler                          /* xxx Interrupt 450*/
    .long   ADMA_FLEXCAN0_MOD_INT_IRQHandler                /* Shared Int Source FLEXCAN0_MOD_INT from ADMA Sub-System*/
    .long   ADMA_FLEXCAN1_MOD_INT_IRQHandler                /* Shared Int Source FLEXCAN1_MOD_INT from ADMA Sub-System*/
    .long   ADMA_FLEXCAN2_MOD_INT_IRQHandler                /* Shared Int Source FLEXCAN2_MOD_INT from ADMA Sub-System*/
    .long   ADMA_FTM0_MOD_INT_IRQHandler                    /* Shared Int Source FTM0_MOD_INT from ADMA Sub-System*/
    .long   ADMA_FTM1_MOD_INT_IRQHandler                    /* Shared Int Source FTM1_MOD_INT from ADMA Sub-System*/
    .long   ADMA_ADC0_MOD_INT_IRQHandler                    /* Shared Int Source ADC0_MOD_INT from ADMA Sub-System*/
    .long   Reserved457_IRQHandler                          /* xxx Interrupt 457*/
    .long   ADMA_FLEXCAN0_DMA_INT_IRQHandler                /* Shared Int Source FLEXCAN0_DMA_INT from ADMA Sub-System*/
    .long   ADMA_FLEXCAN1_DMA_INT_IRQHandler                /* Shared Int Source FLEXCAN1_DMA_INT from ADMA Sub-System*/
    .long   ADMA_FLEXCAN2_DMA_INT_IRQHandler                /* Shared Int Source FLEXCAN2_DMA_INT from ADMA Sub-System*/
    .long   ADMA_FTM0_DMA_INT_IRQHandler                    /* Shared Int Source FTM0_DMA_INT from ADMA Sub-System*/
    .long   ADMA_FTM1_DMA_INT_IRQHandler                    /* Shared Int Source FTM1_DMA_INT from ADMA Sub-System*/
    .long   ADMA_ADC0_DMA_INT_IRQHandler                    /* Shared Int Source ADC0_DMA_INT from ADMA Sub-System*/
    .long   Reserved464_IRQHandler                          /* xxx Interrupt 464*/
    .long   Reserved465_IRQHandler                          /* xxx Interrupt 465*/
    .long   Reserved466_IRQHandler                          /* xxx Interrupt 466*/
    .long   ADMA_EDMA0_INT_IRQHandler                       /* Shared Int Source eDMA0_INT from ADMA Sub-System*/
    .long   ADMA_EDMA0_ERR_INT_IRQHandler                   /* Shared Int Source eDMA0_ERR_INT from ADMA Sub-System*/
    .long   ADMA_EDMA1_INT_IRQHandler                       /* Shared Int Source eDMA1_INT from ADMA Sub-System*/
    .long   ADMA_EDMA1_ERR_INT_IRQHandler                   /* Shared Int Source eDMA1_ERR_INT from ADMA Sub-System*/
    .long   ADMA_ASRC0_INT1_IRQHandler                      /* Shared Int Source ASRC0_INT1 from ADMA Sub-System*/
    .long   ADMA_ASRC0_INT2_IRQHandler                      /* Shared Int Source ASRC0_INT2 from ADMA Sub-System*/
    .long   ADMA_DMA0_CH0_INT_IRQHandler                    /* Shared Int Source DMA0_CH0_INT from ADMA Sub-System*/
    .long   ADMA_DMA0_CH1_INT_IRQHandler                    /* Shared Int Source DMA0_CH1_INT from ADMA Sub-System*/
    .long   ADMA_DMA0_CH2_INT_IRQHandler                    /* Shared Int Source DMA0_CH2_INT from ADMA Sub-System*/
    .long   ADMA_DMA0_CH3_INT_IRQHandler                    /* Shared Int Source DMA0_CH3_INT from ADMA Sub-System*/
    .long   ADMA_DMA0_CH4_INT_IRQHandler                    /* Shared Int Source DMA0_CH4_INT from ADMA Sub-System*/
    .long   ADMA_DMA0_CH5_INT_IRQHandler                    /* Shared Int Source DMA0_CH5_INT from ADMA Sub-System*/
    .long   ADMA_ASRC1_INT1_IRQHandler                      /* Shared Int Source ASRC1_INT1 from ADMA Sub-System*/
    .long   ADMA_ASRC1_INT2_IRQHandler                      /* Shared Int Source ASRC1_INT2 from ADMA Sub-System*/
    .long   ADMA_DMA1_CH0_INT_IRQHandler                    /* Shared Int Source DMA1_CH0_INT from ADMA Sub-System*/
    .long   ADMA_DMA1_CH1_INT_IRQHandler                    /* Shared Int Source DMA1_CH1_INT from ADMA Sub-System*/
    .long   ADMA_DMA1_CH2_INT_IRQHandler                    /* Shared Int Source DMA1_CH2_INT from ADMA Sub-System*/
    .long   ADMA_DMA1_CH3_INT_IRQHandler                    /* Shared Int Source DMA1_CH3_INT from ADMA Sub-System*/
    .long   ADMA_DMA1_CH4_INT_IRQHandler                    /* Shared Int Source DMA1_CH4_INT from ADMA Sub-System*/
    .long   ADMA_DMA1_CH5_INT_IRQHandler                    /* Shared Int Source DMA1_CH5_INT from ADMA Sub-System*/
    .long   ADMA_ESAI0_INT_IRQHandler                       /* Shared Int Source ESAI0_INT from ADMA Sub-System*/
    .long   Reserved488_IRQHandler                          /* xxx Interrupt 488*/
    .long   Reserved489_IRQHandler                          /* xxx Interrupt 489*/
    .long   ADMA_GPT0_INT_IRQHandler                        /* Shared Int Source GPT0_INT from ADMA Sub-System*/
    .long   ADMA_GPT1_INT_IRQHandler                        /* Shared Int Source GPT1_INT from ADMA Sub-System*/
    .long   ADMA_GPT2_INT_IRQHandler                        /* Shared Int Source GPT2_INT from ADMA Sub-System*/
    .long   ADMA_GPT3_INT_IRQHandler                        /* Shared Int Source GPT3_INT from ADMA Sub-System*/
    .long   ADMA_GPT4_INT_IRQHandler                        /* Shared Int Source GPT4_INT from ADMA Sub-System*/
    .long   ADMA_GPT5_INT_IRQHandler                        /* Shared Int Source GPT5_INT from ADMA Sub-System*/
    .long   ADMA_SAI0_INT_IRQHandler                        /* Shared Int Source SAI0_INT from ADMA Sub-System*/
    .long   ADMA_SAI1_INT_IRQHandler                        /* Shared Int Source SAI1_INT from ADMA Sub-System*/
    .long   ADMA_SAI2_INT_IRQHandler                        /* Shared Int Source SAI2_INT from ADMA Sub-System*/
    .long   ADMA_SAI3_INT_IRQHandler                        /* Shared Int Source SAI3_INT from ADMA Sub-System*/
    .long   Reserved500_IRQHandler                          /* xxx Interrupt 500*/
    .long   Reserved501_IRQHandler                          /* xxx Interrupt 501*/
    .long   ADMA_SAI4_INT_IRQHandler                        /* Shared Int Source SAI4_INT from ADMA Sub-System*/
    .long   ADMA_SAI5_INT_IRQHandler                        /* Shared Int Source SAI5_INT from ADMA Sub-System*/
    .long   ADMA_SPDIF0_RX_INT_IRQHandler                   /* Shared Int Source SPDIF0_RX_INT from ADMA Sub-System*/
    .long   ADMA_SPDIF0_TX_INT_IRQHandler                   /* Shared Int Source SPDIF0_TX_INT from ADMA Sub-System*/
    .long   Reserved506_IRQHandler                          /* xxx Interrupt 506*/
    .long   Reserved507_IRQHandler                          /* xxx Interrupt 507*/
    .long   ADMA_ESAI0_MOD_INT_IRQHandler                   /* Shared Int Source ESAI0_MOD_INT from ADMA Sub-System*/
    .long   ADMA_ESAI0_DMA_INT_IRQHandler                   /* Shared Int Source ESAI0_DMA_INT from ADMA Sub-System*/
    .long   Reserved510_IRQHandler                          /* xxx Interrupt 510*/
    .long   Reserved511_IRQHandler                          /* xxx Interrupt 511*/
    .long   Reserved512_IRQHandler                          /* xxx Interrupt 512*/
    .long   Reserved513_IRQHandler                          /* xxx Interrupt 513*/
    .long   Reserved514_IRQHandler                          /* xxx Interrupt 514*/
    .long   ADMA_SPI0_DMA_RX_INT_IRQHandler                 /* Shared Int Source SPI0_DMA_RX_INT from ADMA Sub-System*/
    .long   ADMA_SPI0_DMA_TX_INT_IRQHandler                 /* Shared Int Source SPI0_DMA_TX_INT from ADMA Sub-System*/
    .long   ADMA_SPI1_DMA_RX_INT_IRQHandler                 /* Shared Int Source SPI1_DMA_RX_INT from ADMA Sub-System*/
    .long   ADMA_SPI1_DMA_TX_INT_IRQHandler                 /* Shared Int Source SPI1_DMA_TX_INT from ADMA Sub-System*/
    .long   ADMA_SPI2_DMA_RX_INT_IRQHandler                 /* Shared Int Source SPI2_DMA_RX_INT from ADMA Sub-System*/
    .long   ADMA_SPI2_DMA_TX_INT_IRQHandler                 /* Shared Int Source SPI2_DMA_TX_INT from ADMA Sub-System*/
    .long   ADMA_SPI3_DMA_RX_INT_IRQHandler                 /* Shared Int Source SPI3_DMA_RX_INT from ADMA Sub-System*/
    .long   ADMA_SPI3_DMA_TX_INT_IRQHandler                 /* Shared Int Source SPI3_DMA_TX_INT from ADMA Sub-System*/
    .long   ADMA_I2C0_DMA_RX_INT_IRQHandler                 /* Shared Int Source I2C0_DMA_RX_INT from ADMA Sub-System*/
    .long   ADMA_I2C0_DMA_TX_INT_IRQHandler                 /* Shared Int Source I2C0_DMA_TX_INT from ADMA Sub-System*/
    .long   ADMA_I2C1_DMA_RX_INT_IRQHandler                 /* Shared Int Source I2C1_DMA_RX_INT from ADMA Sub-System*/
    .long   ADMA_I2C1_DMA_TX_INT_IRQHandler                 /* Shared Int Source I2C1_DMA_TX_INT from ADMA Sub-System*/
    .long   ADMA_I2C2_DMA_RX_INT_IRQHandler                 /* Shared Int Source I2C2_DMA_RX_INT from ADMA Sub-System*/
    .long   ADMA_I2C2_DMA_TX_INT_IRQHandler                 /* Shared Int Source I2C2_DMA_TX_INT from ADMA Sub-System*/
    .long   ADMA_I2C3_DMA_RX_INT_IRQHandler                 /* Shared Int Source I2C3_DMA_RX_INT from ADMA Sub-System*/
    .long   ADMA_I2C3_DMA_TX_INT_IRQHandler                 /* Shared Int Source I2C3_DMA_TX_INT from ADMA Sub-System*/
    .long   Reserved531_IRQHandler                          /* xxx Interrupt 531*/
    .long   Reserved532_IRQHandler                          /* xxx Interrupt 532*/
    .long   ADMA_UART0_DMA_RX_INT_IRQHandler                /* Shared Int Source UART0_DMA_RX_INT from ADMA Sub-System*/
    .long   ADMA_UART0_DMA_TX_INT_IRQHandler                /* Shared Int Source UART0_DMA_TX_INT from ADMA Sub-System*/
    .long   ADMA_UART1_DMA_RX_INT_IRQHandler                /* Shared Int Source UART1_DMA_RX_INT from ADMA Sub-System*/
    .long   ADMA_UART1_DMA_TX_INT_IRQHandler                /* Shared Int Source UART1_DMA_TX_INT from ADMA Sub-System*/
    .long   ADMA_UART2_DMA_RX_INT_IRQHandler                /* Shared Int Source UART2_DMA_RX_INT from ADMA Sub-System*/
    .long   ADMA_UART2_DMA_TX_INT_IRQHandler                /* Shared Int Source UART2_DMA_TX_INT from ADMA Sub-System*/
    .long   ADMA_UART3_DMA_RX_INT_IRQHandler                /* Shared Int Source UART3_DMA_RX_INT from ADMA Sub-System*/
    .long   ADMA_UART3_DMA_TX_INT_IRQHandler                /* Shared Int Source UART3_DMA_TX_INT from ADMA Sub-System*/
    .long   Reserved541_IRQHandler                          /* xxx Interrupt 541*/
    .long   Reserved542_IRQHandler                          /* xxx Interrupt 542*/
    .long   Reserved543_IRQHandler                          /* xxx Interrupt 543*/
    .long   Reserved544_IRQHandler                          /* xxx Interrupt 544*/
    .long   Reserved545_IRQHandler                          /* xxx Interrupt 545*/
    .long   Reserved546_IRQHandler                          /* xxx Interrupt 546*/
    .long   SECURITY_MU1_A_INT_IRQHandler                   /* Shared Int Source MU1_A_INT from Security Sub-System*/
    .long   SECURITY_MU2_A_INT_IRQHandler                   /* Shared Int Source MU2_A_INT from Security Sub-System*/
    .long   SECURITY_MU3_A_INT_IRQHandler                   /* Shared Int Source MU3_A_INT from Security Sub-System*/
    .long   SECURITY_CAAM_INT0_IRQHandler                   /* Shared Int Source CAAM_INT0 from Security Sub-System*/
    .long   SECURITY_CAAM_INT1_IRQHandler                   /* Shared Int Source CAAM_INT1 from Security Sub-System*/
    .long   SECURITY_CAAM_INT2_IRQHandler                   /* Shared Int Source CAAM_INT2 from Security Sub-System*/
    .long   SECURITY_CAAM_INT3_IRQHandler                   /* Shared Int Source CAAM_INT3 from Security Sub-System*/
    .long   SECURITY_CAAM_RTIC_INT_IRQHandler               /* Shared Int Source CAAM_RTIC_INT from Security Sub-System*/
    .long   ADMA_SPDIF0_RX_MOD_INT_IRQHandler               /* Shared Int Source SPDIF0_RX_MOD_INT from ADMA Sub-System*/
    .long   ADMA_SPDIF0_RX_DMA_INT_IRQHandler               /* Shared Int Source SPDIF0_RX_DMA_INT from ADMA Sub-System*/
    .long   ADMA_SPDIF0_TX_MOD_INT_IRQHandler               /* Shared Int Source SPDIF0_TX_MOD_INT from ADMA Sub-System*/
    .long   ADMA_SPDIF0_TX_DMA_INT_IRQHandler               /* Shared Int Source SPDIF0_TX_DMA_INT from ADMA Sub-System*/
    .long   Reserved559_IRQHandler                          /* xxx Interrupt 559*/
    .long   Reserved560_IRQHandler                          /* xxx Interrupt 560*/
    .long   Reserved561_IRQHandler                          /* xxx Interrupt 561*/
    .long   Reserved562_IRQHandler                          /* xxx Interrupt 562*/
    .long   VPU_VPU_INT_0_IRQHandler                        /* Shared Int Source VPU_INT_0 from VPU Sub-System*/
    .long   VPU_VPU_INT_1_IRQHandler                        /* Shared Int Source VPU_INT_1 from VPU Sub-System*/
    .long   VPU_VPU_INT_2_IRQHandler                        /* Shared Int Source VPU_INT_2 from VPU Sub-System*/
    .long   VPU_VPU_INT_3_IRQHandler                        /* Shared Int Source VPU_INT_3 from VPU Sub-System*/
    .long   VPU_VPU_INT_4_IRQHandler                        /* Shared Int Source VPU_INT_4 from VPU Sub-System*/
    .long   Reserved568_IRQHandler                          /* xxx Interrupt 568*/
    .long   Reserved569_IRQHandler                          /* xxx Interrupt 569*/
    .long   Reserved570_IRQHandler                          /* xxx Interrupt 570*/
    .long   Reserved571_IRQHandler                          /* xxx Interrupt 571*/
    .long   Reserved572_IRQHandler                          /* xxx Interrupt 572*/
    .long   Reserved573_IRQHandler                          /* xxx Interrupt 573*/
    .long   Reserved574_IRQHandler                          /* xxx Interrupt 574*/
    .long   Reserved575_IRQHandler                          /* xxx Interrupt 575*/
    .long   Reserved576_IRQHandler                          /* xxx Interrupt 576*/
    .long   Reserved577_IRQHandler                          /* xxx Interrupt 577*/
    .long   Reserved578_IRQHandler                          /* xxx Interrupt 578*/
    .long   Reserved579_IRQHandler                          /* xxx Interrupt 579*/
    .long   M4_INTMUX_SOURCE_TPM_IRQHandler                 /* INTMUX Input source: TPM Interrupt*/
    .long   Reserved581_IRQHandler                          /* xxx Interrupt 581*/
    .long   Reserved582_IRQHandler                          /* xxx Interrupt 582*/
    .long   M4_INTMUX_SOURCE_LPIT_IRQHandler                /* INTMUX Input source: LPIT Interrupt*/
    .long   Reserved584_IRQHandler                          /* xxx Interrupt 584*/
    .long   Reserved585_IRQHandler                          /* xxx Interrupt 585*/
    .long   M4_INTMUX_SOURCE_LPUART_IRQHandler              /* INTMUX Input source: LPUART Interrupt*/
    .long   Reserved587_IRQHandler                          /* xxx Interrupt 587*/
    .long   M4_INTMUX_SOURCE_LPI2C_IRQHandler               /* INTMUX Input source: LPI2C Interrupt*/
    .long   Reserved589_IRQHandler                          /* xxx Interrupt 589*/
    .long   Reserved590_IRQHandler                          /* xxx Interrupt 590*/
    .long   Reserved591_IRQHandler                          /* xxx Interrupt 591*/
    .long   Reserved592_IRQHandler                          /* xxx Interrupt 592*/
    .long   Reserved593_IRQHandler                          /* xxx Interrupt 593*/
    .long   Reserved594_IRQHandler                          /* xxx Interrupt 594*/
    .long   Reserved595_IRQHandler                          /* xxx Interrupt 595*/
    .long   Reserved596_IRQHandler                          /* xxx Interrupt 596*/
    .long   Reserved597_IRQHandler                          /* xxx Interrupt 597*/
    .long   Reserved598_IRQHandler                          /* xxx Interrupt 598*/
    .long   Reserved599_IRQHandler                          /* xxx Interrupt 599*/
    .long   Reserved600_IRQHandler                          /* xxx Interrupt 600*/
    .long   Reserved601_IRQHandler                          /* xxx Interrupt 601*/
    .long   Reserved602_IRQHandler                          /* xxx Interrupt 602*/
    .long   Reserved603_IRQHandler                          /* xxx Interrupt 603*/
    .long   Reserved604_IRQHandler                          /* xxx Interrupt 604*/
    .long   Reserved605_IRQHandler                          /* xxx Interrupt 605*/
    .long   Reserved606_IRQHandler                          /* xxx Interrupt 606*/
    .long   M4_INTMUX_SOURCE_MU0_A3_IRQHandler              /* INTMUX Input source: MU0_A3 Interrupt*/
    .long   M4_INTMUX_SOURCE_MU0_A2_IRQHandler              /* INTMUX Input source: MU0_A2 Interrupt*/
    .long   M4_INTMUX_SOURCE_MU0_A1_IRQHandler              /* INTMUX Input source: MU0_A1 Interrupt*/
    .long   M4_INTMUX_SOURCE_MU0_A0_IRQHandler              /* INTMUX Input source: MU0_A0 Interrupt*/
    .long   DefaultISR                                      /* 611*/
    .long   DefaultISR                                      /* 612*/
    .long   DefaultISR                                      /* 613*/
    .long   DefaultISR                                      /* 614*/
    .long   DefaultISR                                      /* 615*/
    .long   DefaultISR                                      /* 616*/
    .long   DefaultISR                                      /* 617*/
    .long   DefaultISR                                      /* 618*/
    .long   DefaultISR                                      /* 619*/
    .long   DefaultISR                                      /* 620*/
    .long   DefaultISR                                      /* 621*/
    .long   DefaultISR                                      /* 622*/
    .long   DefaultISR                                      /* 623*/
    .long   DefaultISR                                      /* 624*/
    .long   DefaultISR                                      /* 625*/
    .long   DefaultISR                                      /* 626*/
    .long   DefaultISR                                      /* 627*/
    .long   DefaultISR                                      /* 628*/
    .long   DefaultISR                                      /* 629*/
    .long   DefaultISR                                      /* 630*/
    .long   DefaultISR                                      /* 631*/
    .long   DefaultISR                                      /* 632*/
    .long   DefaultISR                                      /* 633*/
    .long   DefaultISR                                      /* 634*/
    .long   DefaultISR                                      /* 635*/
    .long   DefaultISR                                      /* 636*/
    .long   DefaultISR                                      /* 637*/
    .long   DefaultISR                                      /* 638*/
    .long   DefaultISR                                      /* 639*/

    .size    __isr_vector, . - __isr_vector

    .text
    .thumb

/* Reset Handler */

    .thumb_func
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
#ifdef __STARTUP_CONFIG_DDR_ALIAS
    .equ    _MCM_PID, 0xE0080030
    ldr     r0, =_MCM_PID
    movs    r1, 0x7E
    str     r1, [r0]
    isb
    ldr     r0,=alias_start
    mov     pc,r0
alias_start:
#endif
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

#if 1
/* Here are two copies of loop implemenations. First one favors code size
 * and the second one favors performance. Default uses the first one.
 * Change to "#if 0" to use the second one */
.LC0:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC0
#else
    subs    r3, r2
    ble    .LC1
.LC0:
    subs    r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .LC0
.LC1:
#endif

/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __quickaccess_start__/__quickaccess_end__: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */
#if defined(FSL_SDK_DRIVER_QUICK_ACCESS_ENABLE) && FSL_SDK_DRIVER_QUICK_ACCESS_ENABLE
    ldr    r2, = __quickaccess_start__
    ldr    r3, = __quickaccess_end__
#if 1
.LC2:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC2
#else
    subs    r3, r2
    ble    .LC3
.LC2:
    subs    r3, #4
    ldr     r0, [r1, r3]
    str     r0, [r2, r3]
    bgt    .LC2
.LC3:
#endif
#endif /* FSL_SDK_DRIVER_QUICK_ACCESS_ENABLE */

/*      __resume_mem_start__/__resume_mem_end__: DDR address range that data should be
 *      retained during LPM. Both must be aligned to 4 bytes boundary.  */
#ifdef __STARTUP_INITIALIZE_RESUMEMEM
    ldr    r1, = __RDATA_ROM
    ldr    r2, = __resume_mem_start__
    ldr    r3, = __resume_mem_end__
#if 1
.LC4:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC4
#else
    subs    r3, r2
    ble    .LC5
.LC4:
    subs    r3, #4
    ldr     r0, [r1, r3]
    str     r0, [r2, r3]
    bgt    .LC4
.LC5:
#endif
#endif /* __STARTUP_INITIALIZE_RESUMEMEM */

#ifdef __STARTUP_INITIALIZE_NONCACHEDATA
    ldr    r1, =__NDATA_ROM
    ldr    r2, =__noncachedata_start__
    ldr    r3, =__noncachedata_init_end__
#if 1
.LC6:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC6
#else
    subs    r3, r2
    ble    .LC7
.LC6:
    subs    r3, #4
    ldr     r0, [r1, r3]
    str     r0, [r2, r3]
    bgt    .LC6
.LC7:
#endif
/* Add ncache section initializaiton */
    ldr r3, =__noncachedata_end__
    movs    r0, 0
.LC8:
    cmp     r2, r3
    itt    lt
    strlt   r0, [r2], #4
    blt    .LC8
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
.LC9:
    cmp     r1, r2
    itt    lt
    strlt   r0, [r1], #4
    blt    .LC9
#endif /* __STARTUP_CLEAR_BSS */

/* Add stack / heap initializaiton */
    movs    r0, 0
    ldr     r1, =__HeapBase
    ldr     r2, =__HeapLimit
.LC10:
    cmp     r1, r2
    itt     lt
    strlt   r0, [r1], #4
    blt     .LC10

    ldr     r1, =__StackLimit
    ldr     r2, =__StackTop
.LC11:
    cmp     r1, r2
    itt     lt
    strlt   r0, [r1], #4
    blt     .LC11

/*End of stack / heap initializaiton */
    cpsie   i               /* Unmask interrupts */
#ifndef __START
#define __START _start
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
    .weak M4_LPUART_IRQHandler
    .type M4_LPUART_IRQHandler, %function
M4_LPUART_IRQHandler:
    ldr   r0,=M4_LPUART_DriverIRQHandler
    bx    r0
    .size M4_LPUART_IRQHandler, . - M4_LPUART_IRQHandler

    .align 1
    .thumb_func
    .weak M4_LPI2C_IRQHandler
    .type M4_LPI2C_IRQHandler, %function
M4_LPI2C_IRQHandler:
    ldr   r0,=M4_LPI2C_DriverIRQHandler
    bx    r0
    .size M4_LPI2C_IRQHandler, . - M4_LPI2C_IRQHandler

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
    .weak MIPI_DSI0_INT_OUT_IRQHandler
    .type MIPI_DSI0_INT_OUT_IRQHandler, %function
MIPI_DSI0_INT_OUT_IRQHandler:
    ldr   r0,=MIPI_DSI0_INT_OUT_DriverIRQHandler
    bx    r0
    .size MIPI_DSI0_INT_OUT_IRQHandler, . - MIPI_DSI0_INT_OUT_IRQHandler

    .align 1
    .thumb_func
    .weak MIPI_DSI1_INT_OUT_IRQHandler
    .type MIPI_DSI1_INT_OUT_IRQHandler, %function
MIPI_DSI1_INT_OUT_IRQHandler:
    ldr   r0,=MIPI_DSI1_INT_OUT_DriverIRQHandler
    bx    r0
    .size MIPI_DSI1_INT_OUT_IRQHandler, . - MIPI_DSI1_INT_OUT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EDMA2_INT_IRQHandler
    .type ADMA_EDMA2_INT_IRQHandler, %function
ADMA_EDMA2_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EDMA2_INT_IRQHandler, . - ADMA_EDMA2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EDMA2_ERR_INT_IRQHandler
    .type ADMA_EDMA2_ERR_INT_IRQHandler, %function
ADMA_EDMA2_ERR_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EDMA2_ERR_INT_IRQHandler, . - ADMA_EDMA2_ERR_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EDMA3_INT_IRQHandler
    .type ADMA_EDMA3_INT_IRQHandler, %function
ADMA_EDMA3_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EDMA3_INT_IRQHandler, . - ADMA_EDMA3_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EDMA3_ERR_INT_IRQHandler
    .type ADMA_EDMA3_ERR_INT_IRQHandler, %function
ADMA_EDMA3_ERR_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EDMA3_ERR_INT_IRQHandler, . - ADMA_EDMA3_ERR_INT_IRQHandler

    .align 1
    .thumb_func
    .weak LSIO_OCTASPI0_INT_IRQHandler
    .type LSIO_OCTASPI0_INT_IRQHandler, %function
LSIO_OCTASPI0_INT_IRQHandler:
    ldr   r0,=LSIO_OCTASPI0_INT_DriverIRQHandler
    bx    r0
    .size LSIO_OCTASPI0_INT_IRQHandler, . - LSIO_OCTASPI0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak LSIO_OCTASPI1_INT_IRQHandler
    .type LSIO_OCTASPI1_INT_IRQHandler, %function
LSIO_OCTASPI1_INT_IRQHandler:
    ldr   r0,=LSIO_OCTASPI1_INT_DriverIRQHandler
    bx    r0
    .size LSIO_OCTASPI1_INT_IRQHandler, . - LSIO_OCTASPI1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak HSIO_PCIEB_DMA_INT_IRQHandler
    .type HSIO_PCIEB_DMA_INT_IRQHandler, %function
HSIO_PCIEB_DMA_INT_IRQHandler:
    ldr   r0,=HSIO_PCIEB_DMA_INT_DriverIRQHandler
    bx    r0
    .size HSIO_PCIEB_DMA_INT_IRQHandler, . - HSIO_PCIEB_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI0_INT_IRQHandler
    .type ADMA_SPI0_INT_IRQHandler, %function
ADMA_SPI0_INT_IRQHandler:
    ldr   r0,=ADMA_SPI0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI0_INT_IRQHandler, . - ADMA_SPI0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI1_INT_IRQHandler
    .type ADMA_SPI1_INT_IRQHandler, %function
ADMA_SPI1_INT_IRQHandler:
    ldr   r0,=ADMA_SPI1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI1_INT_IRQHandler, . - ADMA_SPI1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI2_INT_IRQHandler
    .type ADMA_SPI2_INT_IRQHandler, %function
ADMA_SPI2_INT_IRQHandler:
    ldr   r0,=ADMA_SPI2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI2_INT_IRQHandler, . - ADMA_SPI2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI3_INT_IRQHandler
    .type ADMA_SPI3_INT_IRQHandler, %function
ADMA_SPI3_INT_IRQHandler:
    ldr   r0,=ADMA_SPI3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI3_INT_IRQHandler, . - ADMA_SPI3_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C0_INT_IRQHandler
    .type ADMA_I2C0_INT_IRQHandler, %function
ADMA_I2C0_INT_IRQHandler:
    ldr   r0,=ADMA_I2C0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C0_INT_IRQHandler, . - ADMA_I2C0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C1_INT_IRQHandler
    .type ADMA_I2C1_INT_IRQHandler, %function
ADMA_I2C1_INT_IRQHandler:
    ldr   r0,=ADMA_I2C1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C1_INT_IRQHandler, . - ADMA_I2C1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C2_INT_IRQHandler
    .type ADMA_I2C2_INT_IRQHandler, %function
ADMA_I2C2_INT_IRQHandler:
    ldr   r0,=ADMA_I2C2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C2_INT_IRQHandler, . - ADMA_I2C2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C3_INT_IRQHandler
    .type ADMA_I2C3_INT_IRQHandler, %function
ADMA_I2C3_INT_IRQHandler:
    ldr   r0,=ADMA_I2C3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C3_INT_IRQHandler, . - ADMA_I2C3_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART0_INT_IRQHandler
    .type ADMA_UART0_INT_IRQHandler, %function
ADMA_UART0_INT_IRQHandler:
    ldr   r0,=ADMA_UART0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART0_INT_IRQHandler, . - ADMA_UART0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART1_INT_IRQHandler
    .type ADMA_UART1_INT_IRQHandler, %function
ADMA_UART1_INT_IRQHandler:
    ldr   r0,=ADMA_UART1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART1_INT_IRQHandler, . - ADMA_UART1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART2_INT_IRQHandler
    .type ADMA_UART2_INT_IRQHandler, %function
ADMA_UART2_INT_IRQHandler:
    ldr   r0,=ADMA_UART2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART2_INT_IRQHandler, . - ADMA_UART2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART3_INT_IRQHandler
    .type ADMA_UART3_INT_IRQHandler, %function
ADMA_UART3_INT_IRQHandler:
    ldr   r0,=ADMA_UART3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART3_INT_IRQHandler, . - ADMA_UART3_INT_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_USDHC0_INT_IRQHandler
    .type CONNECTIVITY_USDHC0_INT_IRQHandler, %function
CONNECTIVITY_USDHC0_INT_IRQHandler:
    ldr   r0,=CONNECTIVITY_USDHC0_INT_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_USDHC0_INT_IRQHandler, . - CONNECTIVITY_USDHC0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_USDHC1_INT_IRQHandler
    .type CONNECTIVITY_USDHC1_INT_IRQHandler, %function
CONNECTIVITY_USDHC1_INT_IRQHandler:
    ldr   r0,=CONNECTIVITY_USDHC1_INT_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_USDHC1_INT_IRQHandler, . - CONNECTIVITY_USDHC1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_USDHC2_INT_IRQHandler
    .type CONNECTIVITY_USDHC2_INT_IRQHandler, %function
CONNECTIVITY_USDHC2_INT_IRQHandler:
    ldr   r0,=CONNECTIVITY_USDHC2_INT_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_USDHC2_INT_IRQHandler, . - CONNECTIVITY_USDHC2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FLEXCAN0_INT_IRQHandler
    .type ADMA_FLEXCAN0_INT_IRQHandler, %function
ADMA_FLEXCAN0_INT_IRQHandler:
    ldr   r0,=ADMA_FLEXCAN0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FLEXCAN0_INT_IRQHandler, . - ADMA_FLEXCAN0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FLEXCAN1_INT_IRQHandler
    .type ADMA_FLEXCAN1_INT_IRQHandler, %function
ADMA_FLEXCAN1_INT_IRQHandler:
    ldr   r0,=ADMA_FLEXCAN1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FLEXCAN1_INT_IRQHandler, . - ADMA_FLEXCAN1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FLEXCAN2_INT_IRQHandler
    .type ADMA_FLEXCAN2_INT_IRQHandler, %function
ADMA_FLEXCAN2_INT_IRQHandler:
    ldr   r0,=ADMA_FLEXCAN2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FLEXCAN2_INT_IRQHandler, . - ADMA_FLEXCAN2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FTM0_INT_IRQHandler
    .type ADMA_FTM0_INT_IRQHandler, %function
ADMA_FTM0_INT_IRQHandler:
    ldr   r0,=ADMA_FTM0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FTM0_INT_IRQHandler, . - ADMA_FTM0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FTM1_INT_IRQHandler
    .type ADMA_FTM1_INT_IRQHandler, %function
ADMA_FTM1_INT_IRQHandler:
    ldr   r0,=ADMA_FTM1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FTM1_INT_IRQHandler, . - ADMA_FTM1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_ADC0_INT_IRQHandler
    .type ADMA_ADC0_INT_IRQHandler, %function
ADMA_ADC0_INT_IRQHandler:
    ldr   r0,=ADMA_ADC0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_ADC0_INT_IRQHandler, . - ADMA_ADC0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EXTERNAL_DMA_INT_0_IRQHandler
    .type ADMA_EXTERNAL_DMA_INT_0_IRQHandler, %function
ADMA_EXTERNAL_DMA_INT_0_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EXTERNAL_DMA_INT_0_IRQHandler, . - ADMA_EXTERNAL_DMA_INT_0_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EXTERNAL_DMA_INT_1_IRQHandler
    .type ADMA_EXTERNAL_DMA_INT_1_IRQHandler, %function
ADMA_EXTERNAL_DMA_INT_1_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EXTERNAL_DMA_INT_1_IRQHandler, . - ADMA_EXTERNAL_DMA_INT_1_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EXTERNAL_DMA_INT_2_IRQHandler
    .type ADMA_EXTERNAL_DMA_INT_2_IRQHandler, %function
ADMA_EXTERNAL_DMA_INT_2_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EXTERNAL_DMA_INT_2_IRQHandler, . - ADMA_EXTERNAL_DMA_INT_2_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EXTERNAL_DMA_INT_3_IRQHandler
    .type ADMA_EXTERNAL_DMA_INT_3_IRQHandler, %function
ADMA_EXTERNAL_DMA_INT_3_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EXTERNAL_DMA_INT_3_IRQHandler, . - ADMA_EXTERNAL_DMA_INT_3_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EXTERNAL_DMA_INT_4_IRQHandler
    .type ADMA_EXTERNAL_DMA_INT_4_IRQHandler, %function
ADMA_EXTERNAL_DMA_INT_4_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EXTERNAL_DMA_INT_4_IRQHandler, . - ADMA_EXTERNAL_DMA_INT_4_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EXTERNAL_DMA_INT_5_IRQHandler
    .type ADMA_EXTERNAL_DMA_INT_5_IRQHandler, %function
ADMA_EXTERNAL_DMA_INT_5_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EXTERNAL_DMA_INT_5_IRQHandler, . - ADMA_EXTERNAL_DMA_INT_5_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_ENET0_FRAME1_INT_IRQHandler
    .type CONNECTIVITY_ENET0_FRAME1_INT_IRQHandler, %function
CONNECTIVITY_ENET0_FRAME1_INT_IRQHandler:
    ldr   r0,=CONNECTIVITY_ENET0_FRAME1_INT_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_ENET0_FRAME1_INT_IRQHandler, . - CONNECTIVITY_ENET0_FRAME1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_ENET0_FRAME2_INT_IRQHandler
    .type CONNECTIVITY_ENET0_FRAME2_INT_IRQHandler, %function
CONNECTIVITY_ENET0_FRAME2_INT_IRQHandler:
    ldr   r0,=CONNECTIVITY_ENET0_FRAME2_INT_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_ENET0_FRAME2_INT_IRQHandler, . - CONNECTIVITY_ENET0_FRAME2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_ENET0_FRAME0_EVENT_INT_IRQHandler
    .type CONNECTIVITY_ENET0_FRAME0_EVENT_INT_IRQHandler, %function
CONNECTIVITY_ENET0_FRAME0_EVENT_INT_IRQHandler:
    ldr   r0,=CONNECTIVITY_ENET0_FRAME0_EVENT_INT_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_ENET0_FRAME0_EVENT_INT_IRQHandler, . - CONNECTIVITY_ENET0_FRAME0_EVENT_INT_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_ENET0_TIMER_INT_IRQHandler
    .type CONNECTIVITY_ENET0_TIMER_INT_IRQHandler, %function
CONNECTIVITY_ENET0_TIMER_INT_IRQHandler:
    ldr   r0,=CONNECTIVITY_ENET0_TIMER_INT_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_ENET0_TIMER_INT_IRQHandler, . - CONNECTIVITY_ENET0_TIMER_INT_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_ENET1_FRAME1_INT_IRQHandler
    .type CONNECTIVITY_ENET1_FRAME1_INT_IRQHandler, %function
CONNECTIVITY_ENET1_FRAME1_INT_IRQHandler:
    ldr   r0,=CONNECTIVITY_ENET1_FRAME1_INT_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_ENET1_FRAME1_INT_IRQHandler, . - CONNECTIVITY_ENET1_FRAME1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_ENET1_FRAME2_INT_IRQHandler
    .type CONNECTIVITY_ENET1_FRAME2_INT_IRQHandler, %function
CONNECTIVITY_ENET1_FRAME2_INT_IRQHandler:
    ldr   r0,=CONNECTIVITY_ENET1_FRAME2_INT_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_ENET1_FRAME2_INT_IRQHandler, . - CONNECTIVITY_ENET1_FRAME2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_ENET1_FRAME0_EVENT_INT_IRQHandler
    .type CONNECTIVITY_ENET1_FRAME0_EVENT_INT_IRQHandler, %function
CONNECTIVITY_ENET1_FRAME0_EVENT_INT_IRQHandler:
    ldr   r0,=CONNECTIVITY_ENET1_FRAME0_EVENT_INT_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_ENET1_FRAME0_EVENT_INT_IRQHandler, . - CONNECTIVITY_ENET1_FRAME0_EVENT_INT_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_ENET1_TIMER_INT_IRQHandler
    .type CONNECTIVITY_ENET1_TIMER_INT_IRQHandler, %function
CONNECTIVITY_ENET1_TIMER_INT_IRQHandler:
    ldr   r0,=CONNECTIVITY_ENET1_TIMER_INT_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_ENET1_TIMER_INT_IRQHandler, . - CONNECTIVITY_ENET1_TIMER_INT_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_APBHDMA_IRQHandler
    .type CONNECTIVITY_APBHDMA_IRQHandler, %function
CONNECTIVITY_APBHDMA_IRQHandler:
    ldr   r0,=CONNECTIVITY_APBHDMA_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_APBHDMA_IRQHandler, . - CONNECTIVITY_APBHDMA_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_DMA_INT_IRQHandler
    .type CONNECTIVITY_DMA_INT_IRQHandler, %function
CONNECTIVITY_DMA_INT_IRQHandler:
    ldr   r0,=CONNECTIVITY_DMA_INT_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_DMA_INT_IRQHandler, . - CONNECTIVITY_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak CONNECTIVITY_DMA_ERR_INT_IRQHandler
    .type CONNECTIVITY_DMA_ERR_INT_IRQHandler, %function
CONNECTIVITY_DMA_ERR_INT_IRQHandler:
    ldr   r0,=CONNECTIVITY_DMA_INT_DriverIRQHandler
    bx    r0
    .size CONNECTIVITY_DMA_ERR_INT_IRQHandler, . - CONNECTIVITY_DMA_ERR_INT_IRQHandler

    .align 1
    .thumb_func
    .weak IMAGING_PDMA_STREAM0_INT_IRQHandler
    .type IMAGING_PDMA_STREAM0_INT_IRQHandler, %function
IMAGING_PDMA_STREAM0_INT_IRQHandler:
    ldr   r0,=IMAGING_PDMA_STREAM0_INT_DriverIRQHandler
    bx    r0
    .size IMAGING_PDMA_STREAM0_INT_IRQHandler, . - IMAGING_PDMA_STREAM0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak IMAGING_PDMA_STREAM1_INT_IRQHandler
    .type IMAGING_PDMA_STREAM1_INT_IRQHandler, %function
IMAGING_PDMA_STREAM1_INT_IRQHandler:
    ldr   r0,=IMAGING_PDMA_STREAM1_INT_DriverIRQHandler
    bx    r0
    .size IMAGING_PDMA_STREAM1_INT_IRQHandler, . - IMAGING_PDMA_STREAM1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak IMAGING_PDMA_STREAM2_INT_IRQHandler
    .type IMAGING_PDMA_STREAM2_INT_IRQHandler, %function
IMAGING_PDMA_STREAM2_INT_IRQHandler:
    ldr   r0,=IMAGING_PDMA_STREAM2_INT_DriverIRQHandler
    bx    r0
    .size IMAGING_PDMA_STREAM2_INT_IRQHandler, . - IMAGING_PDMA_STREAM2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak IMAGING_PDMA_STREAM3_INT_IRQHandler
    .type IMAGING_PDMA_STREAM3_INT_IRQHandler, %function
IMAGING_PDMA_STREAM3_INT_IRQHandler:
    ldr   r0,=IMAGING_PDMA_STREAM3_INT_DriverIRQHandler
    bx    r0
    .size IMAGING_PDMA_STREAM3_INT_IRQHandler, . - IMAGING_PDMA_STREAM3_INT_IRQHandler

    .align 1
    .thumb_func
    .weak IMAGING_PDMA_STREAM4_INT_IRQHandler
    .type IMAGING_PDMA_STREAM4_INT_IRQHandler, %function
IMAGING_PDMA_STREAM4_INT_IRQHandler:
    ldr   r0,=IMAGING_PDMA_STREAM4_INT_DriverIRQHandler
    bx    r0
    .size IMAGING_PDMA_STREAM4_INT_IRQHandler, . - IMAGING_PDMA_STREAM4_INT_IRQHandler

    .align 1
    .thumb_func
    .weak IMAGING_PDMA_STREAM5_INT_IRQHandler
    .type IMAGING_PDMA_STREAM5_INT_IRQHandler, %function
IMAGING_PDMA_STREAM5_INT_IRQHandler:
    ldr   r0,=IMAGING_PDMA_STREAM5_INT_DriverIRQHandler
    bx    r0
    .size IMAGING_PDMA_STREAM5_INT_IRQHandler, . - IMAGING_PDMA_STREAM5_INT_IRQHandler

    .align 1
    .thumb_func
    .weak IMAGING_PDMA_STREAM6_INT_IRQHandler
    .type IMAGING_PDMA_STREAM6_INT_IRQHandler, %function
IMAGING_PDMA_STREAM6_INT_IRQHandler:
    ldr   r0,=IMAGING_PDMA_STREAM6_INT_DriverIRQHandler
    bx    r0
    .size IMAGING_PDMA_STREAM6_INT_IRQHandler, . - IMAGING_PDMA_STREAM6_INT_IRQHandler

    .align 1
    .thumb_func
    .weak IMAGING_PDMA_STREAM7_INT_IRQHandler
    .type IMAGING_PDMA_STREAM7_INT_IRQHandler, %function
IMAGING_PDMA_STREAM7_INT_IRQHandler:
    ldr   r0,=IMAGING_PDMA_STREAM7_INT_DriverIRQHandler
    bx    r0
    .size IMAGING_PDMA_STREAM7_INT_IRQHandler, . - IMAGING_PDMA_STREAM7_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI0_MOD_INT_IRQHandler
    .type ADMA_SAI0_MOD_INT_IRQHandler, %function
ADMA_SAI0_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_SAI0_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI0_MOD_INT_IRQHandler, . - ADMA_SAI0_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI0_DMA_INT_IRQHandler
    .type ADMA_SAI0_DMA_INT_IRQHandler, %function
ADMA_SAI0_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI0_DMA_INT_IRQHandler, . - ADMA_SAI0_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI1_MOD_INT_IRQHandler
    .type ADMA_SAI1_MOD_INT_IRQHandler, %function
ADMA_SAI1_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_SAI1_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI1_MOD_INT_IRQHandler, . - ADMA_SAI1_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI1_DMA_INT_IRQHandler
    .type ADMA_SAI1_DMA_INT_IRQHandler, %function
ADMA_SAI1_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI1_DMA_INT_IRQHandler, . - ADMA_SAI1_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI2_MOD_INT_IRQHandler
    .type ADMA_SAI2_MOD_INT_IRQHandler, %function
ADMA_SAI2_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_SAI2_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI2_MOD_INT_IRQHandler, . - ADMA_SAI2_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI2_DMA_INT_IRQHandler
    .type ADMA_SAI2_DMA_INT_IRQHandler, %function
ADMA_SAI2_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI2_DMA_INT_IRQHandler, . - ADMA_SAI2_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI3_MOD_INT_IRQHandler
    .type ADMA_SAI3_MOD_INT_IRQHandler, %function
ADMA_SAI3_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_SAI3_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI3_MOD_INT_IRQHandler, . - ADMA_SAI3_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI3_DMA_INT_IRQHandler
    .type ADMA_SAI3_DMA_INT_IRQHandler, %function
ADMA_SAI3_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI3_DMA_INT_IRQHandler, . - ADMA_SAI3_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI4_MOD_INT_IRQHandler
    .type ADMA_SAI4_MOD_INT_IRQHandler, %function
ADMA_SAI4_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_SAI4_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI4_MOD_INT_IRQHandler, . - ADMA_SAI4_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI4_DMA_INT_IRQHandler
    .type ADMA_SAI4_DMA_INT_IRQHandler, %function
ADMA_SAI4_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI4_DMA_INT_IRQHandler, . - ADMA_SAI4_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI5_MOD_INT_IRQHandler
    .type ADMA_SAI5_MOD_INT_IRQHandler, %function
ADMA_SAI5_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_SAI5_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI5_MOD_INT_IRQHandler, . - ADMA_SAI5_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI5_DMA_INT_IRQHandler
    .type ADMA_SAI5_DMA_INT_IRQHandler, %function
ADMA_SAI5_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI5_DMA_INT_IRQHandler, . - ADMA_SAI5_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI0_MOD_INT_IRQHandler
    .type ADMA_SPI0_MOD_INT_IRQHandler, %function
ADMA_SPI0_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_SPI0_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI0_MOD_INT_IRQHandler, . - ADMA_SPI0_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI1_MOD_INT_IRQHandler
    .type ADMA_SPI1_MOD_INT_IRQHandler, %function
ADMA_SPI1_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_SPI1_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI1_MOD_INT_IRQHandler, . - ADMA_SPI1_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI2_MOD_INT_IRQHandler
    .type ADMA_SPI2_MOD_INT_IRQHandler, %function
ADMA_SPI2_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_SPI2_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI2_MOD_INT_IRQHandler, . - ADMA_SPI2_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI3_MOD_INT_IRQHandler
    .type ADMA_SPI3_MOD_INT_IRQHandler, %function
ADMA_SPI3_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_SPI3_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI3_MOD_INT_IRQHandler, . - ADMA_SPI3_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C0_MOD_INT_IRQHandler
    .type ADMA_I2C0_MOD_INT_IRQHandler, %function
ADMA_I2C0_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_I2C0_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C0_MOD_INT_IRQHandler, . - ADMA_I2C0_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C1_MOD_INT_IRQHandler
    .type ADMA_I2C1_MOD_INT_IRQHandler, %function
ADMA_I2C1_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_I2C1_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C1_MOD_INT_IRQHandler, . - ADMA_I2C1_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C2_MOD_INT_IRQHandler
    .type ADMA_I2C2_MOD_INT_IRQHandler, %function
ADMA_I2C2_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_I2C2_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C2_MOD_INT_IRQHandler, . - ADMA_I2C2_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C3_MOD_INT_IRQHandler
    .type ADMA_I2C3_MOD_INT_IRQHandler, %function
ADMA_I2C3_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_I2C3_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C3_MOD_INT_IRQHandler, . - ADMA_I2C3_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART0_MOD_INT_IRQHandler
    .type ADMA_UART0_MOD_INT_IRQHandler, %function
ADMA_UART0_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_UART0_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART0_MOD_INT_IRQHandler, . - ADMA_UART0_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART1_MOD_INT_IRQHandler
    .type ADMA_UART1_MOD_INT_IRQHandler, %function
ADMA_UART1_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_UART1_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART1_MOD_INT_IRQHandler, . - ADMA_UART1_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART2_MOD_INT_IRQHandler
    .type ADMA_UART2_MOD_INT_IRQHandler, %function
ADMA_UART2_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_UART2_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART2_MOD_INT_IRQHandler, . - ADMA_UART2_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART3_MOD_INT_IRQHandler
    .type ADMA_UART3_MOD_INT_IRQHandler, %function
ADMA_UART3_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_UART3_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART3_MOD_INT_IRQHandler, . - ADMA_UART3_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FLEXCAN0_MOD_INT_IRQHandler
    .type ADMA_FLEXCAN0_MOD_INT_IRQHandler, %function
ADMA_FLEXCAN0_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_FLEXCAN0_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FLEXCAN0_MOD_INT_IRQHandler, . - ADMA_FLEXCAN0_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FLEXCAN1_MOD_INT_IRQHandler
    .type ADMA_FLEXCAN1_MOD_INT_IRQHandler, %function
ADMA_FLEXCAN1_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_FLEXCAN1_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FLEXCAN1_MOD_INT_IRQHandler, . - ADMA_FLEXCAN1_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FLEXCAN2_MOD_INT_IRQHandler
    .type ADMA_FLEXCAN2_MOD_INT_IRQHandler, %function
ADMA_FLEXCAN2_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_FLEXCAN2_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FLEXCAN2_MOD_INT_IRQHandler, . - ADMA_FLEXCAN2_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FTM0_MOD_INT_IRQHandler
    .type ADMA_FTM0_MOD_INT_IRQHandler, %function
ADMA_FTM0_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_FTM0_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FTM0_MOD_INT_IRQHandler, . - ADMA_FTM0_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FTM1_MOD_INT_IRQHandler
    .type ADMA_FTM1_MOD_INT_IRQHandler, %function
ADMA_FTM1_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_FTM1_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FTM1_MOD_INT_IRQHandler, . - ADMA_FTM1_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_ADC0_MOD_INT_IRQHandler
    .type ADMA_ADC0_MOD_INT_IRQHandler, %function
ADMA_ADC0_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_ADC0_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_ADC0_MOD_INT_IRQHandler, . - ADMA_ADC0_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FLEXCAN0_DMA_INT_IRQHandler
    .type ADMA_FLEXCAN0_DMA_INT_IRQHandler, %function
ADMA_FLEXCAN0_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FLEXCAN0_DMA_INT_IRQHandler, . - ADMA_FLEXCAN0_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FLEXCAN1_DMA_INT_IRQHandler
    .type ADMA_FLEXCAN1_DMA_INT_IRQHandler, %function
ADMA_FLEXCAN1_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FLEXCAN1_DMA_INT_IRQHandler, . - ADMA_FLEXCAN1_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FLEXCAN2_DMA_INT_IRQHandler
    .type ADMA_FLEXCAN2_DMA_INT_IRQHandler, %function
ADMA_FLEXCAN2_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FLEXCAN2_DMA_INT_IRQHandler, . - ADMA_FLEXCAN2_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FTM0_DMA_INT_IRQHandler
    .type ADMA_FTM0_DMA_INT_IRQHandler, %function
ADMA_FTM0_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FTM0_DMA_INT_IRQHandler, . - ADMA_FTM0_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_FTM1_DMA_INT_IRQHandler
    .type ADMA_FTM1_DMA_INT_IRQHandler, %function
ADMA_FTM1_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_FTM1_DMA_INT_IRQHandler, . - ADMA_FTM1_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_ADC0_DMA_INT_IRQHandler
    .type ADMA_ADC0_DMA_INT_IRQHandler, %function
ADMA_ADC0_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_ADC0_DMA_INT_IRQHandler, . - ADMA_ADC0_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EDMA0_INT_IRQHandler
    .type ADMA_EDMA0_INT_IRQHandler, %function
ADMA_EDMA0_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EDMA0_INT_IRQHandler, . - ADMA_EDMA0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EDMA0_ERR_INT_IRQHandler
    .type ADMA_EDMA0_ERR_INT_IRQHandler, %function
ADMA_EDMA0_ERR_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EDMA0_ERR_INT_IRQHandler, . - ADMA_EDMA0_ERR_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EDMA1_INT_IRQHandler
    .type ADMA_EDMA1_INT_IRQHandler, %function
ADMA_EDMA1_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EDMA1_INT_IRQHandler, . - ADMA_EDMA1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_EDMA1_ERR_INT_IRQHandler
    .type ADMA_EDMA1_ERR_INT_IRQHandler, %function
ADMA_EDMA1_ERR_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_EDMA1_ERR_INT_IRQHandler, . - ADMA_EDMA1_ERR_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_ASRC0_INT1_IRQHandler
    .type ADMA_ASRC0_INT1_IRQHandler, %function
ADMA_ASRC0_INT1_IRQHandler:
    ldr   r0,=ADMA_ASRC0_INT1_DriverIRQHandler
    bx    r0
    .size ADMA_ASRC0_INT1_IRQHandler, . - ADMA_ASRC0_INT1_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_ASRC0_INT2_IRQHandler
    .type ADMA_ASRC0_INT2_IRQHandler, %function
ADMA_ASRC0_INT2_IRQHandler:
    ldr   r0,=ADMA_ASRC0_INT2_DriverIRQHandler
    bx    r0
    .size ADMA_ASRC0_INT2_IRQHandler, . - ADMA_ASRC0_INT2_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_DMA0_CH0_INT_IRQHandler
    .type ADMA_DMA0_CH0_INT_IRQHandler, %function
ADMA_DMA0_CH0_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_DMA0_CH0_INT_IRQHandler, . - ADMA_DMA0_CH0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_DMA0_CH1_INT_IRQHandler
    .type ADMA_DMA0_CH1_INT_IRQHandler, %function
ADMA_DMA0_CH1_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_DMA0_CH1_INT_IRQHandler, . - ADMA_DMA0_CH1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_DMA0_CH2_INT_IRQHandler
    .type ADMA_DMA0_CH2_INT_IRQHandler, %function
ADMA_DMA0_CH2_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_DMA0_CH2_INT_IRQHandler, . - ADMA_DMA0_CH2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_DMA0_CH3_INT_IRQHandler
    .type ADMA_DMA0_CH3_INT_IRQHandler, %function
ADMA_DMA0_CH3_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_DMA0_CH3_INT_IRQHandler, . - ADMA_DMA0_CH3_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_DMA0_CH4_INT_IRQHandler
    .type ADMA_DMA0_CH4_INT_IRQHandler, %function
ADMA_DMA0_CH4_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_DMA0_CH4_INT_IRQHandler, . - ADMA_DMA0_CH4_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_DMA0_CH5_INT_IRQHandler
    .type ADMA_DMA0_CH5_INT_IRQHandler, %function
ADMA_DMA0_CH5_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_DMA0_CH5_INT_IRQHandler, . - ADMA_DMA0_CH5_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_ASRC1_INT1_IRQHandler
    .type ADMA_ASRC1_INT1_IRQHandler, %function
ADMA_ASRC1_INT1_IRQHandler:
    ldr   r0,=ADMA_ASRC1_INT1_DriverIRQHandler
    bx    r0
    .size ADMA_ASRC1_INT1_IRQHandler, . - ADMA_ASRC1_INT1_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_ASRC1_INT2_IRQHandler
    .type ADMA_ASRC1_INT2_IRQHandler, %function
ADMA_ASRC1_INT2_IRQHandler:
    ldr   r0,=ADMA_ASRC1_INT2_DriverIRQHandler
    bx    r0
    .size ADMA_ASRC1_INT2_IRQHandler, . - ADMA_ASRC1_INT2_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_DMA1_CH0_INT_IRQHandler
    .type ADMA_DMA1_CH0_INT_IRQHandler, %function
ADMA_DMA1_CH0_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_DMA1_CH0_INT_IRQHandler, . - ADMA_DMA1_CH0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_DMA1_CH1_INT_IRQHandler
    .type ADMA_DMA1_CH1_INT_IRQHandler, %function
ADMA_DMA1_CH1_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_DMA1_CH1_INT_IRQHandler, . - ADMA_DMA1_CH1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_DMA1_CH2_INT_IRQHandler
    .type ADMA_DMA1_CH2_INT_IRQHandler, %function
ADMA_DMA1_CH2_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_DMA1_CH2_INT_IRQHandler, . - ADMA_DMA1_CH2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_DMA1_CH3_INT_IRQHandler
    .type ADMA_DMA1_CH3_INT_IRQHandler, %function
ADMA_DMA1_CH3_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_DMA1_CH3_INT_IRQHandler, . - ADMA_DMA1_CH3_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_DMA1_CH4_INT_IRQHandler
    .type ADMA_DMA1_CH4_INT_IRQHandler, %function
ADMA_DMA1_CH4_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_DMA1_CH4_INT_IRQHandler, . - ADMA_DMA1_CH4_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_DMA1_CH5_INT_IRQHandler
    .type ADMA_DMA1_CH5_INT_IRQHandler, %function
ADMA_DMA1_CH5_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_DMA1_CH5_INT_IRQHandler, . - ADMA_DMA1_CH5_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_ESAI0_INT_IRQHandler
    .type ADMA_ESAI0_INT_IRQHandler, %function
ADMA_ESAI0_INT_IRQHandler:
    ldr   r0,=ADMA_ESAI0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_ESAI0_INT_IRQHandler, . - ADMA_ESAI0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_GPT0_INT_IRQHandler
    .type ADMA_GPT0_INT_IRQHandler, %function
ADMA_GPT0_INT_IRQHandler:
    ldr   r0,=ADMA_GPT0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_GPT0_INT_IRQHandler, . - ADMA_GPT0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_GPT1_INT_IRQHandler
    .type ADMA_GPT1_INT_IRQHandler, %function
ADMA_GPT1_INT_IRQHandler:
    ldr   r0,=ADMA_GPT1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_GPT1_INT_IRQHandler, . - ADMA_GPT1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_GPT2_INT_IRQHandler
    .type ADMA_GPT2_INT_IRQHandler, %function
ADMA_GPT2_INT_IRQHandler:
    ldr   r0,=ADMA_GPT2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_GPT2_INT_IRQHandler, . - ADMA_GPT2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_GPT3_INT_IRQHandler
    .type ADMA_GPT3_INT_IRQHandler, %function
ADMA_GPT3_INT_IRQHandler:
    ldr   r0,=ADMA_GPT3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_GPT3_INT_IRQHandler, . - ADMA_GPT3_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_GPT4_INT_IRQHandler
    .type ADMA_GPT4_INT_IRQHandler, %function
ADMA_GPT4_INT_IRQHandler:
    ldr   r0,=ADMA_GPT4_INT_DriverIRQHandler
    bx    r0
    .size ADMA_GPT4_INT_IRQHandler, . - ADMA_GPT4_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_GPT5_INT_IRQHandler
    .type ADMA_GPT5_INT_IRQHandler, %function
ADMA_GPT5_INT_IRQHandler:
    ldr   r0,=ADMA_GPT5_INT_DriverIRQHandler
    bx    r0
    .size ADMA_GPT5_INT_IRQHandler, . - ADMA_GPT5_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI0_INT_IRQHandler
    .type ADMA_SAI0_INT_IRQHandler, %function
ADMA_SAI0_INT_IRQHandler:
    ldr   r0,=ADMA_SAI0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI0_INT_IRQHandler, . - ADMA_SAI0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI1_INT_IRQHandler
    .type ADMA_SAI1_INT_IRQHandler, %function
ADMA_SAI1_INT_IRQHandler:
    ldr   r0,=ADMA_SAI1_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI1_INT_IRQHandler, . - ADMA_SAI1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI2_INT_IRQHandler
    .type ADMA_SAI2_INT_IRQHandler, %function
ADMA_SAI2_INT_IRQHandler:
    ldr   r0,=ADMA_SAI2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI2_INT_IRQHandler, . - ADMA_SAI2_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI3_INT_IRQHandler
    .type ADMA_SAI3_INT_IRQHandler, %function
ADMA_SAI3_INT_IRQHandler:
    ldr   r0,=ADMA_SAI3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI3_INT_IRQHandler, . - ADMA_SAI3_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI4_INT_IRQHandler
    .type ADMA_SAI4_INT_IRQHandler, %function
ADMA_SAI4_INT_IRQHandler:
    ldr   r0,=ADMA_SAI4_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI4_INT_IRQHandler, . - ADMA_SAI4_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SAI5_INT_IRQHandler
    .type ADMA_SAI5_INT_IRQHandler, %function
ADMA_SAI5_INT_IRQHandler:
    ldr   r0,=ADMA_SAI5_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SAI5_INT_IRQHandler, . - ADMA_SAI5_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPDIF0_RX_INT_IRQHandler
    .type ADMA_SPDIF0_RX_INT_IRQHandler, %function
ADMA_SPDIF0_RX_INT_IRQHandler:
    ldr   r0,=ADMA_SPDIF0_RX_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPDIF0_RX_INT_IRQHandler, . - ADMA_SPDIF0_RX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPDIF0_TX_INT_IRQHandler
    .type ADMA_SPDIF0_TX_INT_IRQHandler, %function
ADMA_SPDIF0_TX_INT_IRQHandler:
    ldr   r0,=ADMA_SPDIF0_TX_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPDIF0_TX_INT_IRQHandler, . - ADMA_SPDIF0_TX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_ESAI0_MOD_INT_IRQHandler
    .type ADMA_ESAI0_MOD_INT_IRQHandler, %function
ADMA_ESAI0_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_ESAI0_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_ESAI0_MOD_INT_IRQHandler, . - ADMA_ESAI0_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_ESAI0_DMA_INT_IRQHandler
    .type ADMA_ESAI0_DMA_INT_IRQHandler, %function
ADMA_ESAI0_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_ESAI0_DMA_INT_IRQHandler, . - ADMA_ESAI0_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI0_DMA_RX_INT_IRQHandler
    .type ADMA_SPI0_DMA_RX_INT_IRQHandler, %function
ADMA_SPI0_DMA_RX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI0_DMA_RX_INT_IRQHandler, . - ADMA_SPI0_DMA_RX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI0_DMA_TX_INT_IRQHandler
    .type ADMA_SPI0_DMA_TX_INT_IRQHandler, %function
ADMA_SPI0_DMA_TX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI0_DMA_TX_INT_IRQHandler, . - ADMA_SPI0_DMA_TX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI1_DMA_RX_INT_IRQHandler
    .type ADMA_SPI1_DMA_RX_INT_IRQHandler, %function
ADMA_SPI1_DMA_RX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI1_DMA_RX_INT_IRQHandler, . - ADMA_SPI1_DMA_RX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI1_DMA_TX_INT_IRQHandler
    .type ADMA_SPI1_DMA_TX_INT_IRQHandler, %function
ADMA_SPI1_DMA_TX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI1_DMA_TX_INT_IRQHandler, . - ADMA_SPI1_DMA_TX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI2_DMA_RX_INT_IRQHandler
    .type ADMA_SPI2_DMA_RX_INT_IRQHandler, %function
ADMA_SPI2_DMA_RX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI2_DMA_RX_INT_IRQHandler, . - ADMA_SPI2_DMA_RX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI2_DMA_TX_INT_IRQHandler
    .type ADMA_SPI2_DMA_TX_INT_IRQHandler, %function
ADMA_SPI2_DMA_TX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI2_DMA_TX_INT_IRQHandler, . - ADMA_SPI2_DMA_TX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI3_DMA_RX_INT_IRQHandler
    .type ADMA_SPI3_DMA_RX_INT_IRQHandler, %function
ADMA_SPI3_DMA_RX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI3_DMA_RX_INT_IRQHandler, . - ADMA_SPI3_DMA_RX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPI3_DMA_TX_INT_IRQHandler
    .type ADMA_SPI3_DMA_TX_INT_IRQHandler, %function
ADMA_SPI3_DMA_TX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPI3_DMA_TX_INT_IRQHandler, . - ADMA_SPI3_DMA_TX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C0_DMA_RX_INT_IRQHandler
    .type ADMA_I2C0_DMA_RX_INT_IRQHandler, %function
ADMA_I2C0_DMA_RX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C0_DMA_RX_INT_IRQHandler, . - ADMA_I2C0_DMA_RX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C0_DMA_TX_INT_IRQHandler
    .type ADMA_I2C0_DMA_TX_INT_IRQHandler, %function
ADMA_I2C0_DMA_TX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C0_DMA_TX_INT_IRQHandler, . - ADMA_I2C0_DMA_TX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C1_DMA_RX_INT_IRQHandler
    .type ADMA_I2C1_DMA_RX_INT_IRQHandler, %function
ADMA_I2C1_DMA_RX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C1_DMA_RX_INT_IRQHandler, . - ADMA_I2C1_DMA_RX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C1_DMA_TX_INT_IRQHandler
    .type ADMA_I2C1_DMA_TX_INT_IRQHandler, %function
ADMA_I2C1_DMA_TX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C1_DMA_TX_INT_IRQHandler, . - ADMA_I2C1_DMA_TX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C2_DMA_RX_INT_IRQHandler
    .type ADMA_I2C2_DMA_RX_INT_IRQHandler, %function
ADMA_I2C2_DMA_RX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C2_DMA_RX_INT_IRQHandler, . - ADMA_I2C2_DMA_RX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C2_DMA_TX_INT_IRQHandler
    .type ADMA_I2C2_DMA_TX_INT_IRQHandler, %function
ADMA_I2C2_DMA_TX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C2_DMA_TX_INT_IRQHandler, . - ADMA_I2C2_DMA_TX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C3_DMA_RX_INT_IRQHandler
    .type ADMA_I2C3_DMA_RX_INT_IRQHandler, %function
ADMA_I2C3_DMA_RX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C3_DMA_RX_INT_IRQHandler, . - ADMA_I2C3_DMA_RX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_I2C3_DMA_TX_INT_IRQHandler
    .type ADMA_I2C3_DMA_TX_INT_IRQHandler, %function
ADMA_I2C3_DMA_TX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA3_INT_DriverIRQHandler
    bx    r0
    .size ADMA_I2C3_DMA_TX_INT_IRQHandler, . - ADMA_I2C3_DMA_TX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART0_DMA_RX_INT_IRQHandler
    .type ADMA_UART0_DMA_RX_INT_IRQHandler, %function
ADMA_UART0_DMA_RX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART0_DMA_RX_INT_IRQHandler, . - ADMA_UART0_DMA_RX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART0_DMA_TX_INT_IRQHandler
    .type ADMA_UART0_DMA_TX_INT_IRQHandler, %function
ADMA_UART0_DMA_TX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART0_DMA_TX_INT_IRQHandler, . - ADMA_UART0_DMA_TX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART1_DMA_RX_INT_IRQHandler
    .type ADMA_UART1_DMA_RX_INT_IRQHandler, %function
ADMA_UART1_DMA_RX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART1_DMA_RX_INT_IRQHandler, . - ADMA_UART1_DMA_RX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART1_DMA_TX_INT_IRQHandler
    .type ADMA_UART1_DMA_TX_INT_IRQHandler, %function
ADMA_UART1_DMA_TX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART1_DMA_TX_INT_IRQHandler, . - ADMA_UART1_DMA_TX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART2_DMA_RX_INT_IRQHandler
    .type ADMA_UART2_DMA_RX_INT_IRQHandler, %function
ADMA_UART2_DMA_RX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART2_DMA_RX_INT_IRQHandler, . - ADMA_UART2_DMA_RX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART2_DMA_TX_INT_IRQHandler
    .type ADMA_UART2_DMA_TX_INT_IRQHandler, %function
ADMA_UART2_DMA_TX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART2_DMA_TX_INT_IRQHandler, . - ADMA_UART2_DMA_TX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART3_DMA_RX_INT_IRQHandler
    .type ADMA_UART3_DMA_RX_INT_IRQHandler, %function
ADMA_UART3_DMA_RX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART3_DMA_RX_INT_IRQHandler, . - ADMA_UART3_DMA_RX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_UART3_DMA_TX_INT_IRQHandler
    .type ADMA_UART3_DMA_TX_INT_IRQHandler, %function
ADMA_UART3_DMA_TX_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA2_INT_DriverIRQHandler
    bx    r0
    .size ADMA_UART3_DMA_TX_INT_IRQHandler, . - ADMA_UART3_DMA_TX_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPDIF0_RX_MOD_INT_IRQHandler
    .type ADMA_SPDIF0_RX_MOD_INT_IRQHandler, %function
ADMA_SPDIF0_RX_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_SPDIF0_RX_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPDIF0_RX_MOD_INT_IRQHandler, . - ADMA_SPDIF0_RX_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPDIF0_RX_DMA_INT_IRQHandler
    .type ADMA_SPDIF0_RX_DMA_INT_IRQHandler, %function
ADMA_SPDIF0_RX_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPDIF0_RX_DMA_INT_IRQHandler, . - ADMA_SPDIF0_RX_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPDIF0_TX_MOD_INT_IRQHandler
    .type ADMA_SPDIF0_TX_MOD_INT_IRQHandler, %function
ADMA_SPDIF0_TX_MOD_INT_IRQHandler:
    ldr   r0,=ADMA_SPDIF0_TX_MOD_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPDIF0_TX_MOD_INT_IRQHandler, . - ADMA_SPDIF0_TX_MOD_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ADMA_SPDIF0_TX_DMA_INT_IRQHandler
    .type ADMA_SPDIF0_TX_DMA_INT_IRQHandler, %function
ADMA_SPDIF0_TX_DMA_INT_IRQHandler:
    ldr   r0,=ADMA_EDMA0_INT_DriverIRQHandler
    bx    r0
    .size ADMA_SPDIF0_TX_DMA_INT_IRQHandler, . - ADMA_SPDIF0_TX_DMA_INT_IRQHandler

    .align 1
    .thumb_func
    .weak M4_INTMUX_SOURCE_TPM_IRQHandler
    .type M4_INTMUX_SOURCE_TPM_IRQHandler, %function
M4_INTMUX_SOURCE_TPM_IRQHandler:
    ldr   r0,=M4_INTMUX_SOURCE_TPM_DriverIRQHandler
    bx    r0
    .size M4_INTMUX_SOURCE_TPM_IRQHandler, . - M4_INTMUX_SOURCE_TPM_IRQHandler

    .align 1
    .thumb_func
    .weak M4_INTMUX_SOURCE_LPIT_IRQHandler
    .type M4_INTMUX_SOURCE_LPIT_IRQHandler, %function
M4_INTMUX_SOURCE_LPIT_IRQHandler:
    ldr   r0,=M4_INTMUX_SOURCE_LPIT_DriverIRQHandler
    bx    r0
    .size M4_INTMUX_SOURCE_LPIT_IRQHandler, . - M4_INTMUX_SOURCE_LPIT_IRQHandler

    .align 1
    .thumb_func
    .weak M4_INTMUX_SOURCE_LPUART_IRQHandler
    .type M4_INTMUX_SOURCE_LPUART_IRQHandler, %function
M4_INTMUX_SOURCE_LPUART_IRQHandler:
    ldr   r0,=M4_INTMUX_SOURCE_LPUART_DriverIRQHandler
    bx    r0
    .size M4_INTMUX_SOURCE_LPUART_IRQHandler, . - M4_INTMUX_SOURCE_LPUART_IRQHandler

    .align 1
    .thumb_func
    .weak M4_INTMUX_SOURCE_LPI2C_IRQHandler
    .type M4_INTMUX_SOURCE_LPI2C_IRQHandler, %function
M4_INTMUX_SOURCE_LPI2C_IRQHandler:
    ldr   r0,=M4_INTMUX_SOURCE_LPI2C_DriverIRQHandler
    bx    r0
    .size M4_INTMUX_SOURCE_LPI2C_IRQHandler, . - M4_INTMUX_SOURCE_LPI2C_IRQHandler

    .align 1
    .thumb_func
    .weak M4_INTMUX_SOURCE_MU0_A3_IRQHandler
    .type M4_INTMUX_SOURCE_MU0_A3_IRQHandler, %function
M4_INTMUX_SOURCE_MU0_A3_IRQHandler:
    ldr   r0,=M4_INTMUX_SOURCE_MU0_A3_DriverIRQHandler
    bx    r0
    .size M4_INTMUX_SOURCE_MU0_A3_IRQHandler, . - M4_INTMUX_SOURCE_MU0_A3_IRQHandler

    .align 1
    .thumb_func
    .weak M4_INTMUX_SOURCE_MU0_A2_IRQHandler
    .type M4_INTMUX_SOURCE_MU0_A2_IRQHandler, %function
M4_INTMUX_SOURCE_MU0_A2_IRQHandler:
    ldr   r0,=M4_INTMUX_SOURCE_MU0_A2_DriverIRQHandler
    bx    r0
    .size M4_INTMUX_SOURCE_MU0_A2_IRQHandler, . - M4_INTMUX_SOURCE_MU0_A2_IRQHandler

    .align 1
    .thumb_func
    .weak M4_INTMUX_SOURCE_MU0_A1_IRQHandler
    .type M4_INTMUX_SOURCE_MU0_A1_IRQHandler, %function
M4_INTMUX_SOURCE_MU0_A1_IRQHandler:
    ldr   r0,=M4_INTMUX_SOURCE_MU0_A1_DriverIRQHandler
    bx    r0
    .size M4_INTMUX_SOURCE_MU0_A1_IRQHandler, . - M4_INTMUX_SOURCE_MU0_A1_IRQHandler

    .align 1
    .thumb_func
    .weak M4_INTMUX_SOURCE_MU0_A0_IRQHandler
    .type M4_INTMUX_SOURCE_MU0_A0_IRQHandler, %function
M4_INTMUX_SOURCE_MU0_A0_IRQHandler:
    ldr   r0,=M4_INTMUX_SOURCE_MU0_A0_DriverIRQHandler
    bx    r0
    .size M4_INTMUX_SOURCE_MU0_A0_IRQHandler, . - M4_INTMUX_SOURCE_MU0_A0_IRQHandler


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
    def_irq_handler    M4_MCM_IRQHandler
    def_irq_handler    Reserved22_IRQHandler
    def_irq_handler    Reserved23_IRQHandler
    def_irq_handler    Reserved24_IRQHandler
    def_irq_handler    Reserved25_IRQHandler
    def_irq_handler    Reserved26_IRQHandler
    def_irq_handler    Reserved27_IRQHandler
    def_irq_handler    Reserved28_IRQHandler
    def_irq_handler    Reserved29_IRQHandler
    def_irq_handler    Reserved30_IRQHandler
    def_irq_handler    Reserved31_IRQHandler
    def_irq_handler    Reserved32_IRQHandler
    def_irq_handler    Reserved33_IRQHandler
    def_irq_handler    Reserved34_IRQHandler
    def_irq_handler    M4_TPM_IRQHandler
    def_irq_handler    Reserved36_IRQHandler
    def_irq_handler    Reserved37_IRQHandler
    def_irq_handler    M4_LPIT_IRQHandler
    def_irq_handler    Reserved39_IRQHandler
    def_irq_handler    Reserved40_IRQHandler
    def_irq_handler    M4_LPUART_DriverIRQHandler
    def_irq_handler    Reserved42_IRQHandler
    def_irq_handler    M4_LPI2C_DriverIRQHandler
    def_irq_handler    Reserved44_IRQHandler
    def_irq_handler    M4_MU0_B0_IRQHandler
    def_irq_handler    Reserved46_IRQHandler
    def_irq_handler    Reserved47_IRQHandler
    def_irq_handler    IRQSTEER_0_DriverIRQHandler
    def_irq_handler    IRQSTEER_1_DriverIRQHandler
    def_irq_handler    IRQSTEER_2_DriverIRQHandler
    def_irq_handler    IRQSTEER_3_DriverIRQHandler
    def_irq_handler    IRQSTEER_4_DriverIRQHandler
    def_irq_handler    IRQSTEER_5_DriverIRQHandler
    def_irq_handler    IRQSTEER_6_DriverIRQHandler
    def_irq_handler    IRQSTEER_7_DriverIRQHandler
    def_irq_handler    Reserved56_IRQHandler
    def_irq_handler    Reserved57_IRQHandler
    def_irq_handler    Reserved58_IRQHandler
    def_irq_handler    Reserved59_IRQHandler
    def_irq_handler    M4_MU0_B1_IRQHandler
    def_irq_handler    M4_MU0_B2_IRQHandler
    def_irq_handler    M4_MU0_B3_IRQHandler
    def_irq_handler    Reserved63_IRQHandler
    def_irq_handler    Reserved64_IRQHandler
    def_irq_handler    M4_MU1_A_IRQHandler
    def_irq_handler    M4_SW_IRQHandler
    def_irq_handler    Reserved67_IRQHandler
    def_irq_handler    Reserved68_IRQHandler
    def_irq_handler    Reserved69_IRQHandler
    def_irq_handler    Reserved70_IRQHandler
    def_irq_handler    Reserved71_IRQHandler
    def_irq_handler    Reserved72_IRQHandler
    def_irq_handler    Reserved73_IRQHandler
    def_irq_handler    Reserved74_IRQHandler
    def_irq_handler    Reserved75_IRQHandler
    def_irq_handler    Reserved76_IRQHandler
    def_irq_handler    Reserved77_IRQHandler
    def_irq_handler    Reserved78_IRQHandler
    def_irq_handler    Reserved79_IRQHandler
    def_irq_handler    Reserved80_IRQHandler
    def_irq_handler    Reserved81_IRQHandler
    def_irq_handler    Reserved82_IRQHandler
    def_irq_handler    Reserved83_IRQHandler
    def_irq_handler    Reserved84_IRQHandler
    def_irq_handler    Reserved85_IRQHandler
    def_irq_handler    Reserved86_IRQHandler
    def_irq_handler    Reserved87_IRQHandler
    def_irq_handler    Reserved88_IRQHandler
    def_irq_handler    Reserved89_IRQHandler
    def_irq_handler    Reserved90_IRQHandler
    def_irq_handler    Reserved91_IRQHandler
    def_irq_handler    Reserved92_IRQHandler
    def_irq_handler    Reserved93_IRQHandler
    def_irq_handler    Reserved94_IRQHandler
    def_irq_handler    Reserved95_IRQHandler
    def_irq_handler    Reserved96_IRQHandler
    def_irq_handler    Reserved97_IRQHandler
    def_irq_handler    Reserved98_IRQHandler
    def_irq_handler    A35_NINTERRIRQ_IRQHandler
    def_irq_handler    A35_NEXTERRIRQ_IRQHandler
    def_irq_handler    Reserved101_IRQHandler
    def_irq_handler    Reserved102_IRQHandler
    def_irq_handler    Reserved103_IRQHandler
    def_irq_handler    Reserved104_IRQHandler
    def_irq_handler    Reserved105_IRQHandler
    def_irq_handler    Reserved106_IRQHandler
    def_irq_handler    Reserved107_IRQHandler
    def_irq_handler    Reserved108_IRQHandler
    def_irq_handler    Reserved109_IRQHandler
    def_irq_handler    Reserved110_IRQHandler
    def_irq_handler    Reserved111_IRQHandler
    def_irq_handler    Reserved112_IRQHandler
    def_irq_handler    Reserved113_IRQHandler
    def_irq_handler    Reserved114_IRQHandler
    def_irq_handler    M4_INT_OUT0_IRQHandler
    def_irq_handler    M4_INT_OUT1_IRQHandler
    def_irq_handler    M4_INT_OUT2_IRQHandler
    def_irq_handler    M4_INT_OUT3_IRQHandler
    def_irq_handler    M4_INT_OUT4_IRQHandler
    def_irq_handler    M4_INT_OUT5_IRQHandler
    def_irq_handler    M4_INT_OUT6_IRQHandler
    def_irq_handler    M4_INT_OUT7_IRQHandler
    def_irq_handler    Reserved123_IRQHandler
    def_irq_handler    Reserved124_IRQHandler
    def_irq_handler    Reserved125_IRQHandler
    def_irq_handler    Reserved126_IRQHandler
    def_irq_handler    Reserved127_IRQHandler
    def_irq_handler    Reserved128_IRQHandler
    def_irq_handler    Reserved129_IRQHandler
    def_irq_handler    Reserved130_IRQHandler
    def_irq_handler    Reserved131_IRQHandler
    def_irq_handler    Reserved132_IRQHandler
    def_irq_handler    Reserved133_IRQHandler
    def_irq_handler    Reserved134_IRQHandler
    def_irq_handler    Reserved135_IRQHandler
    def_irq_handler    Reserved136_IRQHandler
    def_irq_handler    Reserved137_IRQHandler
    def_irq_handler    Reserved138_IRQHandler
    def_irq_handler    DISPLAY0_INT_OUT0_IRQHandler
    def_irq_handler    DISPLAY0_INT_OUT1_IRQHandler
    def_irq_handler    DISPLAY0_INT_OUT2_IRQHandler
    def_irq_handler    DISPLAY0_INT_OUT3_IRQHandler
    def_irq_handler    DISPLAY0_INT_OUT4_IRQHandler
    def_irq_handler    DISPLAY0_INT_OUT5_IRQHandler
    def_irq_handler    DISPLAY0_INT_OUT6_IRQHandler
    def_irq_handler    DISPLAY0_INT_OUT7_IRQHandler
    def_irq_handler    DISPLAY0_RESERVED_IRQHandler
    def_irq_handler    DISPLAY0_INT_OUT9_IRQHandler
    def_irq_handler    DISPLAY0_INT_OUT10_IRQHandler
    def_irq_handler    DISPLAY0_INT_OUT11_IRQHandler
    def_irq_handler    DISPLAY0_INT_OUT12_IRQHandler
    def_irq_handler    Reserved152_IRQHandler
    def_irq_handler    Reserved153_IRQHandler
    def_irq_handler    Reserved154_IRQHandler
    def_irq_handler    Reserved155_IRQHandler
    def_irq_handler    Reserved156_IRQHandler
    def_irq_handler    Reserved157_IRQHandler
    def_irq_handler    MIPI_DSI0_INT_OUT_DriverIRQHandler
    def_irq_handler    MIPI_DSI1_INT_OUT_DriverIRQHandler
    def_irq_handler    Reserved160_IRQHandler
    def_irq_handler    LCD_MOD_INT_IRQHandler
    def_irq_handler    LCD_PWM_INT_IRQHandler
    def_irq_handler    GPU0_XAQ2_INTR_IRQHandler
    def_irq_handler    Reserved164_IRQHandler
    def_irq_handler    ADMA_EDMA2_INT_DriverIRQHandler
    def_irq_handler    ADMA_EDMA3_INT_DriverIRQHandler
    def_irq_handler    Reserved169_IRQHandler
    def_irq_handler    Reserved170_IRQHandler
    def_irq_handler    Reserved171_IRQHandler
    def_irq_handler    Reserved172_IRQHandler
    def_irq_handler    Reserved173_IRQHandler
    def_irq_handler    Reserved174_IRQHandler
    def_irq_handler    Reserved175_IRQHandler
    def_irq_handler    Reserved176_IRQHandler
    def_irq_handler    Reserved177_IRQHandler
    def_irq_handler    Reserved178_IRQHandler
    def_irq_handler    LSIO_GPT0_INT_IRQHandler
    def_irq_handler    LSIO_GPT1_INT_IRQHandler
    def_irq_handler    LSIO_GPT2_INT_IRQHandler
    def_irq_handler    LSIO_GPT3_INT_IRQHandler
    def_irq_handler    LSIO_GPT4_INT_IRQHandler
    def_irq_handler    LSIO_KPP_INT_IRQHandler
    def_irq_handler    Reserved185_IRQHandler
    def_irq_handler    Reserved186_IRQHandler
    def_irq_handler    Reserved187_IRQHandler
    def_irq_handler    Reserved188_IRQHandler
    def_irq_handler    Reserved189_IRQHandler
    def_irq_handler    Reserved190_IRQHandler
    def_irq_handler    LSIO_OCTASPI0_INT_DriverIRQHandler
    def_irq_handler    LSIO_OCTASPI1_INT_DriverIRQHandler
    def_irq_handler    LSIO_PWM0_INT_IRQHandler
    def_irq_handler    LSIO_PWM1_INT_IRQHandler
    def_irq_handler    LSIO_PWM2_INT_IRQHandler
    def_irq_handler    LSIO_PWM3_INT_IRQHandler
    def_irq_handler    LSIO_PWM4_INT_IRQHandler
    def_irq_handler    LSIO_PWM5_INT_IRQHandler
    def_irq_handler    LSIO_PWM6_INT_IRQHandler
    def_irq_handler    LSIO_PWM7_INT_IRQHandler
    def_irq_handler    HSIO_PCIEB_MSI_CTRL_INT_IRQHandler
    def_irq_handler    HSIO_PCIEB_CLK_REQ_INT_IRQHandler
    def_irq_handler    HSIO_PCIEB_DMA_INT_DriverIRQHandler
    def_irq_handler    HSIO_PCIEB_INT_D_IRQHandler
    def_irq_handler    HSIO_PCIEB_INT_C_IRQHandler
    def_irq_handler    HSIO_PCIEB_INT_B_IRQHandler
    def_irq_handler    HSIO_PCIEB_INT_A_IRQHandler
    def_irq_handler    HSIO_PCIEB_SMLH_REQ_RST_IRQHandler
    def_irq_handler    HSIO_PCIEB_GPIO_WAKEUP0_IRQHandler
    def_irq_handler    HSIO_PCIEB_GPIO_WAKEUP1_IRQHandler
    def_irq_handler    SCU_INT_OUT0_IRQHandler
    def_irq_handler    SCU_INT_OUT1_IRQHandler
    def_irq_handler    SCU_INT_OUT2_IRQHandler
    def_irq_handler    SCU_INT_OUT3_IRQHandler
    def_irq_handler    SCU_INT_OUT4_IRQHandler
    def_irq_handler    SCU_INT_OUT5_IRQHandler
    def_irq_handler    SCU_INT_OUT6_IRQHandler
    def_irq_handler    SCU_INT_OUT7_IRQHandler
    def_irq_handler    SCU_SYS_COUNT_INT0_IRQHandler
    def_irq_handler    SCU_SYS_COUNT_INT1_IRQHandler
    def_irq_handler    SCU_SYS_COUNT_INT2_IRQHandler
    def_irq_handler    SCU_SYS_COUNT_INT3_IRQHandler
    def_irq_handler    Reserved223_IRQHandler
    def_irq_handler    Reserved224_IRQHandler
    def_irq_handler    Reserved225_IRQHandler
    def_irq_handler    Reserved226_IRQHandler
    def_irq_handler    DRC_ECC_CORRECT_INT_IRQHandler
    def_irq_handler    DRC_ECC_NCORRECT_INT_IRQHandler
    def_irq_handler    DRC_SBR_DONE_INT_IRQHandler
    def_irq_handler    DRC_PERF_CNT_INT_IRQHandler
    def_irq_handler    Reserved231_IRQHandler
    def_irq_handler    Reserved232_IRQHandler
    def_irq_handler    Reserved233_IRQHandler
    def_irq_handler    Reserved234_IRQHandler
    def_irq_handler    LSIO_GPIO_INT0_IRQHandler
    def_irq_handler    LSIO_GPIO_INT1_IRQHandler
    def_irq_handler    LSIO_GPIO_INT2_IRQHandler
    def_irq_handler    LSIO_GPIO_INT3_IRQHandler
    def_irq_handler    LSIO_GPIO_INT4_IRQHandler
    def_irq_handler    LSIO_GPIO_INT5_IRQHandler
    def_irq_handler    LSIO_GPIO_INT6_IRQHandler
    def_irq_handler    LSIO_GPIO_INT7_IRQHandler
    def_irq_handler    Reserved243_IRQHandler
    def_irq_handler    Reserved244_IRQHandler
    def_irq_handler    Reserved245_IRQHandler
    def_irq_handler    Reserved246_IRQHandler
    def_irq_handler    Reserved247_IRQHandler
    def_irq_handler    Reserved248_IRQHandler
    def_irq_handler    Reserved249_IRQHandler
    def_irq_handler    Reserved250_IRQHandler
    def_irq_handler    Reserved251_IRQHandler
    def_irq_handler    Reserved252_IRQHandler
    def_irq_handler    Reserved253_IRQHandler
    def_irq_handler    Reserved254_IRQHandler
    def_irq_handler    Reserved255_IRQHandler
    def_irq_handler    Reserved256_IRQHandler
    def_irq_handler    Reserved257_IRQHandler
    def_irq_handler    Reserved258_IRQHandler
    def_irq_handler    Reserved259_IRQHandler
    def_irq_handler    Reserved260_IRQHandler
    def_irq_handler    Reserved261_IRQHandler
    def_irq_handler    Reserved262_IRQHandler
    def_irq_handler    Reserved263_IRQHandler
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
    def_irq_handler    LSIO_MU0_INT_IRQHandler
    def_irq_handler    LSIO_MU1_INT_IRQHandler
    def_irq_handler    LSIO_MU2_INT_IRQHandler
    def_irq_handler    LSIO_MU3_INT_IRQHandler
    def_irq_handler    LSIO_MU4_INT_IRQHandler
    def_irq_handler    Reserved280_IRQHandler
    def_irq_handler    Reserved281_IRQHandler
    def_irq_handler    Reserved282_IRQHandler
    def_irq_handler    LSIO_MU5_INT_A_IRQHandler
    def_irq_handler    LSIO_MU6_INT_A_IRQHandler
    def_irq_handler    LSIO_MU7_INT_A_IRQHandler
    def_irq_handler    LSIO_MU8_INT_A_IRQHandler
    def_irq_handler    LSIO_MU9_INT_A_IRQHandler
    def_irq_handler    LSIO_MU10_INT_A_IRQHandler
    def_irq_handler    LSIO_MU11_INT_A_IRQHandler
    def_irq_handler    LSIO_MU12_INT_A_IRQHandler
    def_irq_handler    LSIO_MU13_INT_A_IRQHandler
    def_irq_handler    Reserved292_IRQHandler
    def_irq_handler    Reserved293_IRQHandler
    def_irq_handler    Reserved294_IRQHandler
    def_irq_handler    Reserved295_IRQHandler
    def_irq_handler    Reserved296_IRQHandler
    def_irq_handler    Reserved297_IRQHandler
    def_irq_handler    Reserved298_IRQHandler
    def_irq_handler    LSIO_MU5_INT_B_IRQHandler
    def_irq_handler    LSIO_MU6_INT_B_IRQHandler
    def_irq_handler    LSIO_MU7_INT_B_IRQHandler
    def_irq_handler    LSIO_MU8_INT_B_IRQHandler
    def_irq_handler    LSIO_MU9_INT_B_IRQHandler
    def_irq_handler    LSIO_MU10_INT_B_IRQHandler
    def_irq_handler    LSIO_MU11_INT_B_IRQHandler
    def_irq_handler    LSIO_MU12_INT_B_IRQHandler
    def_irq_handler    LSIO_MU13_INT_B_IRQHandler
    def_irq_handler    Reserved308_IRQHandler
    def_irq_handler    Reserved309_IRQHandler
    def_irq_handler    Reserved310_IRQHandler
    def_irq_handler    Reserved311_IRQHandler
    def_irq_handler    Reserved312_IRQHandler
    def_irq_handler    Reserved313_IRQHandler
    def_irq_handler    Reserved314_IRQHandler
    def_irq_handler    ADMA_SPI0_INT_DriverIRQHandler
    def_irq_handler    ADMA_SPI1_INT_DriverIRQHandler
    def_irq_handler    ADMA_SPI2_INT_DriverIRQHandler
    def_irq_handler    ADMA_SPI3_INT_DriverIRQHandler
    def_irq_handler    ADMA_I2C0_INT_DriverIRQHandler
    def_irq_handler    ADMA_I2C1_INT_DriverIRQHandler
    def_irq_handler    ADMA_I2C2_INT_DriverIRQHandler
    def_irq_handler    ADMA_I2C3_INT_DriverIRQHandler
    def_irq_handler    Reserved323_IRQHandler
    def_irq_handler    ADMA_UART0_INT_DriverIRQHandler
    def_irq_handler    ADMA_UART1_INT_DriverIRQHandler
    def_irq_handler    ADMA_UART2_INT_DriverIRQHandler
    def_irq_handler    ADMA_UART3_INT_DriverIRQHandler
    def_irq_handler    Reserved328_IRQHandler
    def_irq_handler    Reserved329_IRQHandler
    def_irq_handler    Reserved330_IRQHandler
    def_irq_handler    CONNECTIVITY_USDHC0_INT_DriverIRQHandler
    def_irq_handler    CONNECTIVITY_USDHC1_INT_DriverIRQHandler
    def_irq_handler    CONNECTIVITY_USDHC2_INT_DriverIRQHandler
    def_irq_handler    ADMA_FLEXCAN0_INT_DriverIRQHandler
    def_irq_handler    ADMA_FLEXCAN1_INT_DriverIRQHandler
    def_irq_handler    ADMA_FLEXCAN2_INT_DriverIRQHandler
    def_irq_handler    ADMA_FTM0_INT_DriverIRQHandler
    def_irq_handler    ADMA_FTM1_INT_DriverIRQHandler
    def_irq_handler    ADMA_ADC0_INT_DriverIRQHandler
    def_irq_handler    Reserved340_IRQHandler
    def_irq_handler    Reserved347_IRQHandler
    def_irq_handler    Reserved348_IRQHandler
    def_irq_handler    Reserved349_IRQHandler
    def_irq_handler    Reserved350_IRQHandler
    def_irq_handler    Reserved351_IRQHandler
    def_irq_handler    Reserved352_IRQHandler
    def_irq_handler    Reserved353_IRQHandler
    def_irq_handler    Reserved354_IRQHandler
    def_irq_handler    CONNECTIVITY_ENET0_FRAME1_INT_DriverIRQHandler
    def_irq_handler    CONNECTIVITY_ENET0_FRAME2_INT_DriverIRQHandler
    def_irq_handler    CONNECTIVITY_ENET0_FRAME0_EVENT_INT_DriverIRQHandler
    def_irq_handler    CONNECTIVITY_ENET0_TIMER_INT_DriverIRQHandler
    def_irq_handler    CONNECTIVITY_ENET1_FRAME1_INT_DriverIRQHandler
    def_irq_handler    CONNECTIVITY_ENET1_FRAME2_INT_DriverIRQHandler
    def_irq_handler    CONNECTIVITY_ENET1_FRAME0_EVENT_INT_DriverIRQHandler
    def_irq_handler    CONNECTIVITY_ENET1_TIMER_INT_DriverIRQHandler
    def_irq_handler    CONNECTIVITY_DTCP_INT_IRQHandler
    def_irq_handler    CONNECTIVITY_MLB_INT_IRQHandler
    def_irq_handler    CONNECTIVITY_MLB_AHB_INT_IRQHandler
    def_irq_handler    CONNECTIVITY_USB_OTG_INT_IRQHandler
    def_irq_handler    CONNECTIVITY_USB_HOST_INT_IRQHandler
    def_irq_handler    CONNECTIVITY_UTMI_INT_IRQHandler
    def_irq_handler    CONNECTIVITY_WAKEUP_INT_IRQHandler
    def_irq_handler    CONNECTIVITY_USB3_INT_IRQHandler
    def_irq_handler    CONNECTIVITY_ND_FLASH_BCH_INT_IRQHandler
    def_irq_handler    CONNECTIVITY_ND_FLASH_GPMI_INT_IRQHandler
    def_irq_handler    CONNECTIVITY_APBHDMA_DriverIRQHandler
    def_irq_handler    CONNECTIVITY_DMA_INT_DriverIRQHandler
    def_irq_handler    Reserved376_IRQHandler
    def_irq_handler    Reserved377_IRQHandler
    def_irq_handler    Reserved378_IRQHandler
    def_irq_handler    Reserved379_IRQHandler
    def_irq_handler    Reserved380_IRQHandler
    def_irq_handler    Reserved381_IRQHandler
    def_irq_handler    Reserved382_IRQHandler
    def_irq_handler    Reserved383_IRQHandler
    def_irq_handler    Reserved384_IRQHandler
    def_irq_handler    Reserved385_IRQHandler
    def_irq_handler    Reserved386_IRQHandler
    def_irq_handler    IMAGING_MSI_INT_IRQHandler
    def_irq_handler    Reserved388_IRQHandler
    def_irq_handler    Reserved389_IRQHandler
    def_irq_handler    Reserved390_IRQHandler
    def_irq_handler    Reserved391_IRQHandler
    def_irq_handler    Reserved392_IRQHandler
    def_irq_handler    Reserved393_IRQHandler
    def_irq_handler    Reserved394_IRQHandler
    def_irq_handler    Reserved395_IRQHandler
    def_irq_handler    IMAGING_PDMA_STREAM0_INT_DriverIRQHandler
    def_irq_handler    IMAGING_PDMA_STREAM1_INT_DriverIRQHandler
    def_irq_handler    IMAGING_PDMA_STREAM2_INT_DriverIRQHandler
    def_irq_handler    IMAGING_PDMA_STREAM3_INT_DriverIRQHandler
    def_irq_handler    IMAGING_PDMA_STREAM4_INT_DriverIRQHandler
    def_irq_handler    IMAGING_PDMA_STREAM5_INT_DriverIRQHandler
    def_irq_handler    IMAGING_PDMA_STREAM6_INT_DriverIRQHandler
    def_irq_handler    IMAGING_PDMA_STREAM7_INT_DriverIRQHandler
    def_irq_handler    IMAGING_MJPEG_ENC0_INT_IRQHandler
    def_irq_handler    IMAGING_MJPEG_ENC1_INT_IRQHandler
    def_irq_handler    IMAGING_MJPEG_ENC2_INT_IRQHandler
    def_irq_handler    IMAGING_MJPEG_ENC3_INT_IRQHandler
    def_irq_handler    IMAGING_MJPEG_DEC0_INT_IRQHandler
    def_irq_handler    IMAGING_MJPEG_DEC1_INT_IRQHandler
    def_irq_handler    IMAGING_MJPEG_DEC2_INT_IRQHandler
    def_irq_handler    IMAGING_MJPEG_DEC3_INT_IRQHandler
    def_irq_handler    Reserved412_IRQHandler
    def_irq_handler    ADMA_SAI0_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_EDMA0_INT_DriverIRQHandler
    def_irq_handler    ADMA_SAI1_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_SAI2_MOD_INT_DriverIRQHandler
    def_irq_handler    MIPI_CSI0_OUT_INT_IRQHandler
    def_irq_handler    Reserved420_IRQHandler
    def_irq_handler    Reserved421_IRQHandler
    def_irq_handler    ADMA_SAI3_MOD_INT_DriverIRQHandler
    def_irq_handler    Reserved424_IRQHandler
    def_irq_handler    Reserved425_IRQHandler
    def_irq_handler    Reserved426_IRQHandler
    def_irq_handler    Reserved427_IRQHandler
    def_irq_handler    ADMA_SAI4_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_EDMA1_INT_DriverIRQHandler
    def_irq_handler    ADMA_SAI5_MOD_INT_DriverIRQHandler
    def_irq_handler    Reserved432_IRQHandler
    def_irq_handler    Reserved433_IRQHandler
    def_irq_handler    Reserved434_IRQHandler
    def_irq_handler    ADMA_SPI0_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_SPI1_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_SPI2_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_SPI3_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_I2C0_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_I2C1_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_I2C2_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_I2C3_MOD_INT_DriverIRQHandler
    def_irq_handler    Reserved443_IRQHandler
    def_irq_handler    ADMA_UART0_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_UART1_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_UART2_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_UART3_MOD_INT_DriverIRQHandler
    def_irq_handler    Reserved448_IRQHandler
    def_irq_handler    Reserved449_IRQHandler
    def_irq_handler    Reserved450_IRQHandler
    def_irq_handler    ADMA_FLEXCAN0_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_FLEXCAN1_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_FLEXCAN2_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_FTM0_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_FTM1_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_ADC0_MOD_INT_DriverIRQHandler
    def_irq_handler    Reserved457_IRQHandler
    def_irq_handler    Reserved464_IRQHandler
    def_irq_handler    Reserved465_IRQHandler
    def_irq_handler    Reserved466_IRQHandler
    def_irq_handler    ADMA_ASRC0_INT1_DriverIRQHandler
    def_irq_handler    ADMA_ASRC0_INT2_DriverIRQHandler
    def_irq_handler    ADMA_ASRC1_INT1_DriverIRQHandler
    def_irq_handler    ADMA_ASRC1_INT2_DriverIRQHandler
    def_irq_handler    ADMA_ESAI0_INT_DriverIRQHandler
    def_irq_handler    Reserved488_IRQHandler
    def_irq_handler    Reserved489_IRQHandler
    def_irq_handler    ADMA_GPT0_INT_DriverIRQHandler
    def_irq_handler    ADMA_GPT1_INT_DriverIRQHandler
    def_irq_handler    ADMA_GPT2_INT_DriverIRQHandler
    def_irq_handler    ADMA_GPT3_INT_DriverIRQHandler
    def_irq_handler    ADMA_GPT4_INT_DriverIRQHandler
    def_irq_handler    ADMA_GPT5_INT_DriverIRQHandler
    def_irq_handler    ADMA_SAI0_INT_DriverIRQHandler
    def_irq_handler    ADMA_SAI1_INT_DriverIRQHandler
    def_irq_handler    ADMA_SAI2_INT_DriverIRQHandler
    def_irq_handler    ADMA_SAI3_INT_DriverIRQHandler
    def_irq_handler    Reserved500_IRQHandler
    def_irq_handler    Reserved501_IRQHandler
    def_irq_handler    ADMA_SAI4_INT_DriverIRQHandler
    def_irq_handler    ADMA_SAI5_INT_DriverIRQHandler
    def_irq_handler    ADMA_SPDIF0_RX_INT_DriverIRQHandler
    def_irq_handler    ADMA_SPDIF0_TX_INT_DriverIRQHandler
    def_irq_handler    Reserved506_IRQHandler
    def_irq_handler    Reserved507_IRQHandler
    def_irq_handler    ADMA_ESAI0_MOD_INT_DriverIRQHandler
    def_irq_handler    Reserved510_IRQHandler
    def_irq_handler    Reserved511_IRQHandler
    def_irq_handler    Reserved512_IRQHandler
    def_irq_handler    Reserved513_IRQHandler
    def_irq_handler    Reserved514_IRQHandler
    def_irq_handler    Reserved531_IRQHandler
    def_irq_handler    Reserved532_IRQHandler
    def_irq_handler    Reserved541_IRQHandler
    def_irq_handler    Reserved542_IRQHandler
    def_irq_handler    Reserved543_IRQHandler
    def_irq_handler    Reserved544_IRQHandler
    def_irq_handler    Reserved545_IRQHandler
    def_irq_handler    Reserved546_IRQHandler
    def_irq_handler    SECURITY_MU1_A_INT_IRQHandler
    def_irq_handler    SECURITY_MU2_A_INT_IRQHandler
    def_irq_handler    SECURITY_MU3_A_INT_IRQHandler
    def_irq_handler    SECURITY_CAAM_INT0_IRQHandler
    def_irq_handler    SECURITY_CAAM_INT1_IRQHandler
    def_irq_handler    SECURITY_CAAM_INT2_IRQHandler
    def_irq_handler    SECURITY_CAAM_INT3_IRQHandler
    def_irq_handler    SECURITY_CAAM_RTIC_INT_IRQHandler
    def_irq_handler    ADMA_SPDIF0_RX_MOD_INT_DriverIRQHandler
    def_irq_handler    ADMA_SPDIF0_TX_MOD_INT_DriverIRQHandler
    def_irq_handler    Reserved559_IRQHandler
    def_irq_handler    Reserved560_IRQHandler
    def_irq_handler    Reserved561_IRQHandler
    def_irq_handler    Reserved562_IRQHandler
    def_irq_handler    VPU_VPU_INT_0_IRQHandler
    def_irq_handler    VPU_VPU_INT_1_IRQHandler
    def_irq_handler    VPU_VPU_INT_2_IRQHandler
    def_irq_handler    VPU_VPU_INT_3_IRQHandler
    def_irq_handler    VPU_VPU_INT_4_IRQHandler
    def_irq_handler    Reserved568_IRQHandler
    def_irq_handler    Reserved569_IRQHandler
    def_irq_handler    Reserved570_IRQHandler
    def_irq_handler    Reserved571_IRQHandler
    def_irq_handler    Reserved572_IRQHandler
    def_irq_handler    Reserved573_IRQHandler
    def_irq_handler    Reserved574_IRQHandler
    def_irq_handler    Reserved575_IRQHandler
    def_irq_handler    Reserved576_IRQHandler
    def_irq_handler    Reserved577_IRQHandler
    def_irq_handler    Reserved578_IRQHandler
    def_irq_handler    Reserved579_IRQHandler
    def_irq_handler    M4_INTMUX_SOURCE_TPM_DriverIRQHandler
    def_irq_handler    Reserved581_IRQHandler
    def_irq_handler    Reserved582_IRQHandler
    def_irq_handler    M4_INTMUX_SOURCE_LPIT_DriverIRQHandler
    def_irq_handler    Reserved584_IRQHandler
    def_irq_handler    Reserved585_IRQHandler
    def_irq_handler    M4_INTMUX_SOURCE_LPUART_DriverIRQHandler
    def_irq_handler    Reserved587_IRQHandler
    def_irq_handler    M4_INTMUX_SOURCE_LPI2C_DriverIRQHandler
    def_irq_handler    Reserved589_IRQHandler
    def_irq_handler    Reserved590_IRQHandler
    def_irq_handler    Reserved591_IRQHandler
    def_irq_handler    Reserved592_IRQHandler
    def_irq_handler    Reserved593_IRQHandler
    def_irq_handler    Reserved594_IRQHandler
    def_irq_handler    Reserved595_IRQHandler
    def_irq_handler    Reserved596_IRQHandler
    def_irq_handler    Reserved597_IRQHandler
    def_irq_handler    Reserved598_IRQHandler
    def_irq_handler    Reserved599_IRQHandler
    def_irq_handler    Reserved600_IRQHandler
    def_irq_handler    Reserved601_IRQHandler
    def_irq_handler    Reserved602_IRQHandler
    def_irq_handler    Reserved603_IRQHandler
    def_irq_handler    Reserved604_IRQHandler
    def_irq_handler    Reserved605_IRQHandler
    def_irq_handler    Reserved606_IRQHandler
    def_irq_handler    M4_INTMUX_SOURCE_MU0_A3_DriverIRQHandler
    def_irq_handler    M4_INTMUX_SOURCE_MU0_A2_DriverIRQHandler
    def_irq_handler    M4_INTMUX_SOURCE_MU0_A1_DriverIRQHandler
    def_irq_handler    M4_INTMUX_SOURCE_MU0_A0_DriverIRQHandler

    .end
