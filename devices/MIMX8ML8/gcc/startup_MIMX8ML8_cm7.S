/* ------------------------------------------------------------------------- */
/*  @file:    startup_MIMX8ML8_cm7.s                                         */
/*  @purpose: CMSIS Cortex-M7 Core Device Startup File                       */
/*            MIMX8ML8_cm7                                                   */
/*  @version: 5.0                                                            */
/*  @date:    2021-3-1                                                       */
/*  @build:   b231019                                                        */
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
    .long   Reserved16_IRQHandler                           /* xxx Interrupt 16*/
    .long   DAP_IRQHandler                                  /* DAP Interrupt*/
    .long   SDMA1_IRQHandler                                /* AND of all 48 SDMA1 interrupts (events) from all the channels*/
    .long   GPU3D_IRQHandler                                /* GPU3D Interrupt*/
    .long   SNVS_IRQHandler                                 /* ON-OFF button press shorter than 5 seconds (pulse event)*/
    .long   LCDIF1_IRQHandler                               /* LCDIF1 Interrupt*/
    .long   LCDIF2_IRQHandler                               /* LCDIF2 Interrupt*/
    .long   VPU_G1_IRQHandler                               /* VPU G1 Decoder Interrupt*/
    .long   VPU_G2_IRQHandler                               /* VPU G2 Decoder Interrupt*/
    .long   QOS_IRQHandler                                  /* QOS interrupt*/
    .long   WDOG3_IRQHandler                                /* Watchdog Timer reset*/
    .long   HS_CP1_IRQHandler                               /* HS Interrupt Request*/
    .long   APBHDMA_IRQHandler                              /* GPMI operation channel 0-3 description complete interrupt*/
    .long   ML_IRQHandler                                   /* Machine Learning Processor Interrupt*/
    .long   BCH_IRQHandler                                  /* BCH operation complete interrupt*/
    .long   GPMI_IRQHandler                                 /* GPMI operation TIMEOUT ERROR interrupt*/
    .long   ISI_IRQHandler                                  /* ISI Interrupt*/
    .long   MIPI_CSI1_IRQHandler                            /* MIPI CSI Interrupt*/
    .long   MIPI_DSI_IRQHandler                             /* MIPI DSI Interrupt*/
    .long   SNVS_Consolidated_IRQHandler                    /* SRTC Consolidated Interrupt. Non TZ.*/
    .long   SNVS_Security_IRQHandler                        /* SRTC Security Interrupt. TZ.*/
    .long   CSU_IRQHandler                                  /* CSU Interrupt Request. Indicates to the processor that one or more alarm inputs were asserted.*/
    .long   USDHC1_IRQHandler                               /* uSDHC1 Enhanced SDHC Interrupt Request*/
    .long   USDHC2_IRQHandler                               /* uSDHC2 Enhanced SDHC Interrupt Request*/
    .long   USDHC3_IRQHandler                               /* uSDHC3 Enhanced SDHC Interrupt Request*/
    .long   GPU2D_IRQHandler                                /* GPU2D Interrupt*/
    .long   UART1_IRQHandler                                /* UART-1 ORed interrupt*/
    .long   UART2_IRQHandler                                /* UART-2 ORed interrupt*/
    .long   UART3_IRQHandler                                /* UART-3 ORed interrupt*/
    .long   UART4_IRQHandler                                /* UART-4 ORed interrupt*/
    .long   VPU_IRQHandler                                  /* VPU Encoder Interrupt*/
    .long   ECSPI1_IRQHandler                               /* ECSPI1 interrupt request line to the core.*/
    .long   ECSPI2_IRQHandler                               /* ECSPI2 interrupt request line to the core.*/
    .long   ECSPI3_IRQHandler                               /* ECSPI3 interrupt request line to the core.*/
    .long   SDMA3_IRQHandler                                /* AND of all 48 SDMA3 interrupts (events) from all the channels*/
    .long   I2C1_IRQHandler                                 /* I2C-1 Interrupt*/
    .long   I2C2_IRQHandler                                 /* I2C-2 Interrupt*/
    .long   I2C3_IRQHandler                                 /* I2C-3 Interrupt*/
    .long   I2C4_IRQHandler                                 /* I2C-4 Interrupt*/
    .long   RDC_IRQHandler                                  /* RDC interrupt*/
    .long   USB1_IRQHandler                                 /* USB1 Interrupt*/
    .long   USB2_IRQHandler                                 /* USB2 Interrupt*/
    .long   ISI_CH1_IRQHandler                              /* ISI Camera Channel 1 Interrupt*/
    .long   HDMI_TX_IRQHandler                              /* HDMI TX Subsystem Interrupt*/
    .long   PDM_HWVAD_EVENT_IRQHandler                      /* Digital Microphone interface voice activity detector event interrupt*/
    .long   PDM_HWVAD_ERROR_IRQHandler                      /* Digital Microphone interface voice activity detector error interrupt*/
    .long   GPT6_IRQHandler                                 /* OR of GPT Rollover interrupt line, Input Capture 1 and 2 lines, Output Compare 1, 2, and 3 Interrupt lines*/
    .long   SCTR_IRQ0_IRQHandler                            /* System Counter Interrupt 0*/
    .long   SCTR_IRQ1_IRQHandler                            /* System Counter Interrupt 1*/
    .long   ANAMIX_IRQHandler                               /* TempSensor (Temperature alarm and criticl alarm).*/
    .long   I2S3_IRQHandler                                 /* SAI3 Receive / Transmit Interrupt*/
    .long   GPT5_IRQHandler                                 /* OR of GPT Rollover interrupt line, Input Capture 1 and 2 lines, Output Compare 1, 2, and 3 Interrupt lines*/
    .long   GPT4_IRQHandler                                 /* OR of GPT Rollover interrupt line, Input Capture 1 and 2 lines, Output Compare 1, 2, and 3 Interrupt lines*/
    .long   GPT3_IRQHandler                                 /* OR of GPT Rollover interrupt line, Input Capture 1 and 2 lines, Output Compare 1, 2, and 3 Interrupt lines*/
    .long   GPT2_IRQHandler                                 /* OR of GPT Rollover interrupt line, Input Capture 1 and 2 lines, Output Compare 1, 2, and 3 Interrupt lines*/
    .long   GPT1_IRQHandler                                 /* OR of GPT Rollover interrupt line, Input Capture 1 and 2 lines, Output Compare 1, 2, and 3 Interrupt lines*/
    .long   GPIO1_INT7_IRQHandler                           /* Active HIGH Interrupt from INT7 from GPIO*/
    .long   GPIO1_INT6_IRQHandler                           /* Active HIGH Interrupt from INT6 from GPIO*/
    .long   GPIO1_INT5_IRQHandler                           /* Active HIGH Interrupt from INT5 from GPIO*/
    .long   GPIO1_INT4_IRQHandler                           /* Active HIGH Interrupt from INT4 from GPIO*/
    .long   GPIO1_INT3_IRQHandler                           /* Active HIGH Interrupt from INT3 from GPIO*/
    .long   GPIO1_INT2_IRQHandler                           /* Active HIGH Interrupt from INT2 from GPIO*/
    .long   GPIO1_INT1_IRQHandler                           /* Active HIGH Interrupt from INT1 from GPIO*/
    .long   GPIO1_INT0_IRQHandler                           /* Active HIGH Interrupt from INT0 from GPIO*/
    .long   GPIO1_Combined_0_15_IRQHandler                  /* Combined interrupt indication for GPIO1 signal 0 throughout 15*/
    .long   GPIO1_Combined_16_31_IRQHandler                 /* Combined interrupt indication for GPIO1 signal 16 throughout 31*/
    .long   GPIO2_Combined_0_15_IRQHandler                  /* Combined interrupt indication for GPIO2 signal 0 throughout 15*/
    .long   GPIO2_Combined_16_31_IRQHandler                 /* Combined interrupt indication for GPIO2 signal 16 throughout 31*/
    .long   GPIO3_Combined_0_15_IRQHandler                  /* Combined interrupt indication for GPIO3 signal 0 throughout 15*/
    .long   GPIO3_Combined_16_31_IRQHandler                 /* Combined interrupt indication for GPIO3 signal 16 throughout 31*/
    .long   GPIO4_Combined_0_15_IRQHandler                  /* Combined interrupt indication for GPIO4 signal 0 throughout 15*/
    .long   GPIO4_Combined_16_31_IRQHandler                 /* Combined interrupt indication for GPIO4 signal 16 throughout 31*/
    .long   GPIO5_Combined_0_15_IRQHandler                  /* Combined interrupt indication for GPIO5 signal 0 throughout 15*/
    .long   GPIO5_Combined_16_31_IRQHandler                 /* Combined interrupt indication for GPIO5 signal 16 throughout 31*/
    .long   ISP1_IRQHandler                                 /* ISP 1 ISP Interrupts*/
    .long   ISP2_IRQHandler                                 /* ISP 2 ISP Interrupts*/
    .long   I2C5_IRQHandler                                 /* I2C-5 Interrupt*/
    .long   I2C6_IRQHandler                                 /* I2C-6 Interrupt*/
    .long   WDOG1_IRQHandler                                /* Watchdog Timer reset*/
    .long   WDOG2_IRQHandler                                /* Watchdog Timer reset*/
    .long   MIPI_CSI2_IRQHandler                            /* MIPI CSI 2 Interrupt*/
    .long   PWM1_IRQHandler                                 /* Cumulative interrupt line. OR of Rollover Interrupt line, Compare Interrupt line and FIFO Waterlevel crossing interrupt line.*/
    .long   PWM2_IRQHandler                                 /* Cumulative interrupt line. OR of Rollover Interrupt line, Compare Interrupt line and FIFO Waterlevel crossing interrupt line.*/
    .long   PWM3_IRQHandler                                 /* Cumulative interrupt line. OR of Rollover Interrupt line, Compare Interrupt line and FIFO Waterlevel crossing interrupt line.*/
    .long   PWM4_IRQHandler                                 /* Cumulative interrupt line. OR of Rollover Interrupt line, Compare Interrupt line and FIFO Waterlevel crossing interrupt line.*/
    .long   CCM_IRQ1_IRQHandler                             /* CCM Interrupt Request 1*/
    .long   CCM_IRQ2_IRQHandler                             /* CCM Interrupt Request 2*/
    .long   GPC_IRQHandler                                  /* GPC Interrupt Request 1*/
    .long   MU1_A53_IRQHandler                              /* Interrupt to A53 (A53,M7 MU)*/
    .long   SRC_IRQHandler                                  /* SRC interrupt request*/
    .long   I2S56_IRQHandler                                /* SAI5/6 Receive / Transmit Interrupt*/
    .long   RTIC_IRQHandler                                 /* RTIC Interrupt*/
    .long   CPU_PerformanceUnit_IRQHandler                  /* Performance Unit Interrupts from Cheetah (interrnally: PMUIRQ[n]*/
    .long   CPU_CTI_Trigger_IRQHandler                      /* CTI trigger outputs (internal: nCTIIRQ[n]*/
    .long   SRC_Combined_IRQHandler                         /* Combined CPU wdog interrupts (4x) out of SRC.*/
    .long   I2S1_IRQHandler                                 /* SAI1 Receive / Transmit Interrupt*/
    .long   I2S2_IRQHandler                                 /* SAI2 Receive / Transmit Interrupt*/
    .long   MU1_M7_IRQHandler                               /* Interrupt to M7 (A53, M7 MU)*/
    .long   DDR_PerformanceMonitor_IRQHandler               /* ddr Interrupt for performance monitor*/
    .long   DDR_IRQHandler                                  /* ddr Interrupt*/
    .long   DEWARP_IRQHandler                               /* Dewarp Interrupt*/
    .long   CPU_Error_AXI_IRQHandler                        /* CPU Error indicator for AXI transaction with a write response error condition*/
    .long   CPU_Error_L2RAM_IRQHandler                      /* CPU Error indicator for L2 RAM double-bit ECC error*/
    .long   SDMA2_IRQHandler                                /* AND of all 48 SDMA2 interrupts (events) from all the channels*/
    .long   SJC_IRQHandler                                  /* Interrupt triggered by SJC register*/
    .long   CAAM_IRQ0_IRQHandler                            /* CAAM interrupt queue for JQ*/
    .long   CAAM_IRQ1_IRQHandler                            /* CAAM interrupt queue for JQ*/
    .long   FlexSPI_IRQHandler                              /* FlexSPI Interrupt*/
    .long   TZASC_IRQHandler                                /* TZASC (PL380) interrupt*/
    .long   PDM_EVENT_IRQHandler                            /* Digital Microphone interface interrupt*/
    .long   PDM_ERROR_IRQHandler                            /* Digital Microphone interface error interrupt*/
    .long   I2S7_IRQHandler                                 /* SAI7 Receive / Transmit Interrupt*/
    .long   PERFMON1_IRQHandler                             /* General Interrupt*/
    .long   PERFMON2_IRQHandler                             /* General Interrupt*/
    .long   CAAM_IRQ2_IRQHandler                            /* CAAM interrupt queue for JQ*/
    .long   CAAM_ERROR_IRQHandler                           /* Recoverable error interrupt*/
    .long   HS_CP0_IRQHandler                               /* HS Interrupt Request*/
    .long   CM7_CTI_IRQHandler                              /* CTI trigger outputs from CM7 platform*/
    .long   ENET1_MAC0_Rx_Tx_Done1_IRQHandler               /* MAC 0 Receive / Trasmit Frame / Buffer Done*/
    .long   ENET1_MAC0_Rx_Tx_Done2_IRQHandler               /* MAC 0 Receive / Trasmit Frame / Buffer Done*/
    .long   ENET1_IRQHandler                                /* MAC 0 IRQ*/
    .long   ENET1_1588_Timer_IRQHandler                     /* MAC 0 1588 Timer Interrupt-synchronous*/
    .long   ASRC_IRQHandler                                 /* ASRC Interrupt*/
    .long   PCIE_CTRL1_0_IRQHandler                         /* Coming from GLUE logic, of set/reset FF, driven by PCIE signals, interrupt 0*/
    .long   PCIE_CTRL1_1_IRQHandler                         /* Coming from GLUE logic, of set/reset FF, driven by PCIE signals, interrupt 1*/
    .long   PCIE_CTRL1_2_IRQHandler                         /* Coming from GLUE logic, of set/reset FF, driven by PCIE signals, interrupt 2*/
    .long   PCIE_CTRL1_3_IRQHandler                         /* Coming from GLUE logic, of set/reset FF, driven by PCIE signals, interrupt 3*/
    .long   PCIE_EDMA_IRQHandler                            /* Channels [63:32] interrupts requests*/
    .long   AUDIO_XCVR0_IRQHandler                          /* eARC Interrupt 0*/
    .long   AUDIO_XCVR1_IRQHandler                          /* eARC Interrupt 1*/
    .long   AUD2HTX_IRQHandler                              /* Audio to HDMI TX Audio Link Master Interrupt*/
    .long   EDMA1_ERR_IRQHandler                            /* Audio Subsystem eDMA Error Interrupt*/
    .long   EDMA1_0_15_IRQHandler                           /* Audio Subsystem eDMA Channel Interrupts, Logical OR of channels [15:0]*/
    .long   EDMA1_16_31_IRQHandler                          /* Audio Subsystem eDMA Channel Interrupts, Logical OR of channels [31:16]*/
    .long   ENET_QOS_PMT_IRQHandler                         /* ENET QOS TSN Interrupt from PMT*/
    .long   ENET_QOS_IRQHandler                             /* ENET QOS TSN LPI RX exit/Host System/RX/TX Channels[4:0] Interrupt*/
    .long   MU2_A53_IRQHandler                              /* Interrupt to A53 (A53, Audio Processor MU)*/
    .long   MU2_AUDIO_IRQHandler                            /* Interrupt to Audio Processor (A53, Audio Processor MU)*/
    .long   MU3_M7_IRQHandler                               /* Interrupt to M7 (M7, Audio Processor MU)*/
    .long   MU3_AUDIO_IRQHandler                            /* Interrupt to Audio Processor (M7, Audio Processor MU)*/
    .long   PCIE_CTRL1_IRQHandler                           /* RC/EP message transaction Interrupt*/
    .long   PCIE_CTRL1_ERR_IRQHandler                       /* RC/EP PME Message and Error Interrupt*/
    .long   CAN_FD1_IRQHandler                              /* CAN-FD1 Interrupt from bus off/line error/RX warning/TX warning/wakeup/match in PN/timeout in PN/busoff done/FD error*/
    .long   CAN_FD1_ERROR_IRQHandler                        /* CAN-FD1 Interrupt from correctable error/non correctable error int host/ non correctable error int internal*/
    .long   CAN_FD2_IRQHandler                              /* CAN-FD2 Interrupt from bus off/line error/RX warning/TX warning/wakeup/match in PN/timeout in PN/busoff done/FD error*/
    .long   CAN_FD2_ERROR_IRQHandler                        /* CAN-FD2 Interrupt from correctable error/non correctable error int host/ non correctable error int internal*/
    .long   AUDIO_XCVR_IRQHandler                           /* eARC PHY - SPDIF wakeup interrupt*/
    .long   DDR_ERR_IRQHandler                              /* DRAM Controller Error Interrupt */
    .long   USB1_WAKEUP_IRQHandler                          /* USB-1 Wake-up Interrupt*/
    .long   USB2_WAKEUP_IRQHandler                          /* USB-2 Wake-up Interrupt*/
    .long   MECC_IRQHandler                                 /* OCRAM Memory ECC Interrupt*/
    .long   MECC_ERR_IRQHandler                             /* OCRAM Memory ECC Error Interrupt*/
    .long   MECC_S_IRQHandler                               /* OCRAM_S Memory ECC Interrupt*/
    .long   MECC_S_ERR_IRQHandler                           /* OCRAM_S Memory ECC Error Interrupt*/

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
    .weak Reserved16_IRQHandler
    .type Reserved16_IRQHandler, %function
Reserved16_IRQHandler:
    ldr   r0,=Reserved16_DriverIRQHandler
    bx    r0
    .size Reserved16_IRQHandler, . - Reserved16_IRQHandler

    .align 1
    .thumb_func
    .weak DAP_IRQHandler
    .type DAP_IRQHandler, %function
DAP_IRQHandler:
    ldr   r0,=DAP_DriverIRQHandler
    bx    r0
    .size DAP_IRQHandler, . - DAP_IRQHandler

    .align 1
    .thumb_func
    .weak SDMA1_IRQHandler
    .type SDMA1_IRQHandler, %function
SDMA1_IRQHandler:
    ldr   r0,=SDMA1_DriverIRQHandler
    bx    r0
    .size SDMA1_IRQHandler, . - SDMA1_IRQHandler

    .align 1
    .thumb_func
    .weak GPU3D_IRQHandler
    .type GPU3D_IRQHandler, %function
GPU3D_IRQHandler:
    ldr   r0,=GPU3D_DriverIRQHandler
    bx    r0
    .size GPU3D_IRQHandler, . - GPU3D_IRQHandler

    .align 1
    .thumb_func
    .weak SNVS_IRQHandler
    .type SNVS_IRQHandler, %function
SNVS_IRQHandler:
    ldr   r0,=SNVS_DriverIRQHandler
    bx    r0
    .size SNVS_IRQHandler, . - SNVS_IRQHandler

    .align 1
    .thumb_func
    .weak LCDIF1_IRQHandler
    .type LCDIF1_IRQHandler, %function
LCDIF1_IRQHandler:
    ldr   r0,=LCDIF1_DriverIRQHandler
    bx    r0
    .size LCDIF1_IRQHandler, . - LCDIF1_IRQHandler

    .align 1
    .thumb_func
    .weak LCDIF2_IRQHandler
    .type LCDIF2_IRQHandler, %function
LCDIF2_IRQHandler:
    ldr   r0,=LCDIF2_DriverIRQHandler
    bx    r0
    .size LCDIF2_IRQHandler, . - LCDIF2_IRQHandler

    .align 1
    .thumb_func
    .weak VPU_G1_IRQHandler
    .type VPU_G1_IRQHandler, %function
VPU_G1_IRQHandler:
    ldr   r0,=VPU_G1_DriverIRQHandler
    bx    r0
    .size VPU_G1_IRQHandler, . - VPU_G1_IRQHandler

    .align 1
    .thumb_func
    .weak VPU_G2_IRQHandler
    .type VPU_G2_IRQHandler, %function
VPU_G2_IRQHandler:
    ldr   r0,=VPU_G2_DriverIRQHandler
    bx    r0
    .size VPU_G2_IRQHandler, . - VPU_G2_IRQHandler

    .align 1
    .thumb_func
    .weak QOS_IRQHandler
    .type QOS_IRQHandler, %function
QOS_IRQHandler:
    ldr   r0,=QOS_DriverIRQHandler
    bx    r0
    .size QOS_IRQHandler, . - QOS_IRQHandler

    .align 1
    .thumb_func
    .weak WDOG3_IRQHandler
    .type WDOG3_IRQHandler, %function
WDOG3_IRQHandler:
    ldr   r0,=WDOG3_DriverIRQHandler
    bx    r0
    .size WDOG3_IRQHandler, . - WDOG3_IRQHandler

    .align 1
    .thumb_func
    .weak HS_CP1_IRQHandler
    .type HS_CP1_IRQHandler, %function
HS_CP1_IRQHandler:
    ldr   r0,=HS_CP1_DriverIRQHandler
    bx    r0
    .size HS_CP1_IRQHandler, . - HS_CP1_IRQHandler

    .align 1
    .thumb_func
    .weak APBHDMA_IRQHandler
    .type APBHDMA_IRQHandler, %function
APBHDMA_IRQHandler:
    ldr   r0,=APBHDMA_DriverIRQHandler
    bx    r0
    .size APBHDMA_IRQHandler, . - APBHDMA_IRQHandler

    .align 1
    .thumb_func
    .weak ML_IRQHandler
    .type ML_IRQHandler, %function
ML_IRQHandler:
    ldr   r0,=ML_DriverIRQHandler
    bx    r0
    .size ML_IRQHandler, . - ML_IRQHandler

    .align 1
    .thumb_func
    .weak BCH_IRQHandler
    .type BCH_IRQHandler, %function
BCH_IRQHandler:
    ldr   r0,=BCH_DriverIRQHandler
    bx    r0
    .size BCH_IRQHandler, . - BCH_IRQHandler

    .align 1
    .thumb_func
    .weak GPMI_IRQHandler
    .type GPMI_IRQHandler, %function
GPMI_IRQHandler:
    ldr   r0,=GPMI_DriverIRQHandler
    bx    r0
    .size GPMI_IRQHandler, . - GPMI_IRQHandler

    .align 1
    .thumb_func
    .weak ISI_IRQHandler
    .type ISI_IRQHandler, %function
ISI_IRQHandler:
    ldr   r0,=ISI_DriverIRQHandler
    bx    r0
    .size ISI_IRQHandler, . - ISI_IRQHandler

    .align 1
    .thumb_func
    .weak MIPI_CSI1_IRQHandler
    .type MIPI_CSI1_IRQHandler, %function
MIPI_CSI1_IRQHandler:
    ldr   r0,=MIPI_CSI1_DriverIRQHandler
    bx    r0
    .size MIPI_CSI1_IRQHandler, . - MIPI_CSI1_IRQHandler

    .align 1
    .thumb_func
    .weak MIPI_DSI_IRQHandler
    .type MIPI_DSI_IRQHandler, %function
MIPI_DSI_IRQHandler:
    ldr   r0,=MIPI_DSI_DriverIRQHandler
    bx    r0
    .size MIPI_DSI_IRQHandler, . - MIPI_DSI_IRQHandler

    .align 1
    .thumb_func
    .weak SNVS_Consolidated_IRQHandler
    .type SNVS_Consolidated_IRQHandler, %function
SNVS_Consolidated_IRQHandler:
    ldr   r0,=SNVS_Consolidated_DriverIRQHandler
    bx    r0
    .size SNVS_Consolidated_IRQHandler, . - SNVS_Consolidated_IRQHandler

    .align 1
    .thumb_func
    .weak SNVS_Security_IRQHandler
    .type SNVS_Security_IRQHandler, %function
SNVS_Security_IRQHandler:
    ldr   r0,=SNVS_Security_DriverIRQHandler
    bx    r0
    .size SNVS_Security_IRQHandler, . - SNVS_Security_IRQHandler

    .align 1
    .thumb_func
    .weak CSU_IRQHandler
    .type CSU_IRQHandler, %function
CSU_IRQHandler:
    ldr   r0,=CSU_DriverIRQHandler
    bx    r0
    .size CSU_IRQHandler, . - CSU_IRQHandler

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
    .weak USDHC3_IRQHandler
    .type USDHC3_IRQHandler, %function
USDHC3_IRQHandler:
    ldr   r0,=USDHC3_DriverIRQHandler
    bx    r0
    .size USDHC3_IRQHandler, . - USDHC3_IRQHandler

    .align 1
    .thumb_func
    .weak GPU2D_IRQHandler
    .type GPU2D_IRQHandler, %function
GPU2D_IRQHandler:
    ldr   r0,=GPU2D_DriverIRQHandler
    bx    r0
    .size GPU2D_IRQHandler, . - GPU2D_IRQHandler

    .align 1
    .thumb_func
    .weak UART1_IRQHandler
    .type UART1_IRQHandler, %function
UART1_IRQHandler:
    ldr   r0,=UART1_DriverIRQHandler
    bx    r0
    .size UART1_IRQHandler, . - UART1_IRQHandler

    .align 1
    .thumb_func
    .weak UART2_IRQHandler
    .type UART2_IRQHandler, %function
UART2_IRQHandler:
    ldr   r0,=UART2_DriverIRQHandler
    bx    r0
    .size UART2_IRQHandler, . - UART2_IRQHandler

    .align 1
    .thumb_func
    .weak UART3_IRQHandler
    .type UART3_IRQHandler, %function
UART3_IRQHandler:
    ldr   r0,=UART3_DriverIRQHandler
    bx    r0
    .size UART3_IRQHandler, . - UART3_IRQHandler

    .align 1
    .thumb_func
    .weak UART4_IRQHandler
    .type UART4_IRQHandler, %function
UART4_IRQHandler:
    ldr   r0,=UART4_DriverIRQHandler
    bx    r0
    .size UART4_IRQHandler, . - UART4_IRQHandler

    .align 1
    .thumb_func
    .weak VPU_IRQHandler
    .type VPU_IRQHandler, %function
VPU_IRQHandler:
    ldr   r0,=VPU_DriverIRQHandler
    bx    r0
    .size VPU_IRQHandler, . - VPU_IRQHandler

    .align 1
    .thumb_func
    .weak ECSPI1_IRQHandler
    .type ECSPI1_IRQHandler, %function
ECSPI1_IRQHandler:
    ldr   r0,=ECSPI1_DriverIRQHandler
    bx    r0
    .size ECSPI1_IRQHandler, . - ECSPI1_IRQHandler

    .align 1
    .thumb_func
    .weak ECSPI2_IRQHandler
    .type ECSPI2_IRQHandler, %function
ECSPI2_IRQHandler:
    ldr   r0,=ECSPI2_DriverIRQHandler
    bx    r0
    .size ECSPI2_IRQHandler, . - ECSPI2_IRQHandler

    .align 1
    .thumb_func
    .weak ECSPI3_IRQHandler
    .type ECSPI3_IRQHandler, %function
ECSPI3_IRQHandler:
    ldr   r0,=ECSPI3_DriverIRQHandler
    bx    r0
    .size ECSPI3_IRQHandler, . - ECSPI3_IRQHandler

    .align 1
    .thumb_func
    .weak SDMA3_IRQHandler
    .type SDMA3_IRQHandler, %function
SDMA3_IRQHandler:
    ldr   r0,=SDMA3_DriverIRQHandler
    bx    r0
    .size SDMA3_IRQHandler, . - SDMA3_IRQHandler

    .align 1
    .thumb_func
    .weak I2C1_IRQHandler
    .type I2C1_IRQHandler, %function
I2C1_IRQHandler:
    ldr   r0,=I2C1_DriverIRQHandler
    bx    r0
    .size I2C1_IRQHandler, . - I2C1_IRQHandler

    .align 1
    .thumb_func
    .weak I2C2_IRQHandler
    .type I2C2_IRQHandler, %function
I2C2_IRQHandler:
    ldr   r0,=I2C2_DriverIRQHandler
    bx    r0
    .size I2C2_IRQHandler, . - I2C2_IRQHandler

    .align 1
    .thumb_func
    .weak I2C3_IRQHandler
    .type I2C3_IRQHandler, %function
I2C3_IRQHandler:
    ldr   r0,=I2C3_DriverIRQHandler
    bx    r0
    .size I2C3_IRQHandler, . - I2C3_IRQHandler

    .align 1
    .thumb_func
    .weak I2C4_IRQHandler
    .type I2C4_IRQHandler, %function
I2C4_IRQHandler:
    ldr   r0,=I2C4_DriverIRQHandler
    bx    r0
    .size I2C4_IRQHandler, . - I2C4_IRQHandler

    .align 1
    .thumb_func
    .weak RDC_IRQHandler
    .type RDC_IRQHandler, %function
RDC_IRQHandler:
    ldr   r0,=RDC_DriverIRQHandler
    bx    r0
    .size RDC_IRQHandler, . - RDC_IRQHandler

    .align 1
    .thumb_func
    .weak USB1_IRQHandler
    .type USB1_IRQHandler, %function
USB1_IRQHandler:
    ldr   r0,=USB1_DriverIRQHandler
    bx    r0
    .size USB1_IRQHandler, . - USB1_IRQHandler

    .align 1
    .thumb_func
    .weak USB2_IRQHandler
    .type USB2_IRQHandler, %function
USB2_IRQHandler:
    ldr   r0,=USB2_DriverIRQHandler
    bx    r0
    .size USB2_IRQHandler, . - USB2_IRQHandler

    .align 1
    .thumb_func
    .weak ISI_CH1_IRQHandler
    .type ISI_CH1_IRQHandler, %function
ISI_CH1_IRQHandler:
    ldr   r0,=ISI_CH1_DriverIRQHandler
    bx    r0
    .size ISI_CH1_IRQHandler, . - ISI_CH1_IRQHandler

    .align 1
    .thumb_func
    .weak HDMI_TX_IRQHandler
    .type HDMI_TX_IRQHandler, %function
HDMI_TX_IRQHandler:
    ldr   r0,=HDMI_TX_DriverIRQHandler
    bx    r0
    .size HDMI_TX_IRQHandler, . - HDMI_TX_IRQHandler

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
    .weak GPT6_IRQHandler
    .type GPT6_IRQHandler, %function
GPT6_IRQHandler:
    ldr   r0,=GPT6_DriverIRQHandler
    bx    r0
    .size GPT6_IRQHandler, . - GPT6_IRQHandler

    .align 1
    .thumb_func
    .weak SCTR_IRQ0_IRQHandler
    .type SCTR_IRQ0_IRQHandler, %function
SCTR_IRQ0_IRQHandler:
    ldr   r0,=SCTR_IRQ0_DriverIRQHandler
    bx    r0
    .size SCTR_IRQ0_IRQHandler, . - SCTR_IRQ0_IRQHandler

    .align 1
    .thumb_func
    .weak SCTR_IRQ1_IRQHandler
    .type SCTR_IRQ1_IRQHandler, %function
SCTR_IRQ1_IRQHandler:
    ldr   r0,=SCTR_IRQ1_DriverIRQHandler
    bx    r0
    .size SCTR_IRQ1_IRQHandler, . - SCTR_IRQ1_IRQHandler

    .align 1
    .thumb_func
    .weak ANAMIX_IRQHandler
    .type ANAMIX_IRQHandler, %function
ANAMIX_IRQHandler:
    ldr   r0,=ANAMIX_DriverIRQHandler
    bx    r0
    .size ANAMIX_IRQHandler, . - ANAMIX_IRQHandler

    .align 1
    .thumb_func
    .weak I2S3_IRQHandler
    .type I2S3_IRQHandler, %function
I2S3_IRQHandler:
    ldr   r0,=I2S3_DriverIRQHandler
    bx    r0
    .size I2S3_IRQHandler, . - I2S3_IRQHandler

    .align 1
    .thumb_func
    .weak GPT5_IRQHandler
    .type GPT5_IRQHandler, %function
GPT5_IRQHandler:
    ldr   r0,=GPT5_DriverIRQHandler
    bx    r0
    .size GPT5_IRQHandler, . - GPT5_IRQHandler

    .align 1
    .thumb_func
    .weak GPT4_IRQHandler
    .type GPT4_IRQHandler, %function
GPT4_IRQHandler:
    ldr   r0,=GPT4_DriverIRQHandler
    bx    r0
    .size GPT4_IRQHandler, . - GPT4_IRQHandler

    .align 1
    .thumb_func
    .weak GPT3_IRQHandler
    .type GPT3_IRQHandler, %function
GPT3_IRQHandler:
    ldr   r0,=GPT3_DriverIRQHandler
    bx    r0
    .size GPT3_IRQHandler, . - GPT3_IRQHandler

    .align 1
    .thumb_func
    .weak GPT2_IRQHandler
    .type GPT2_IRQHandler, %function
GPT2_IRQHandler:
    ldr   r0,=GPT2_DriverIRQHandler
    bx    r0
    .size GPT2_IRQHandler, . - GPT2_IRQHandler

    .align 1
    .thumb_func
    .weak GPT1_IRQHandler
    .type GPT1_IRQHandler, %function
GPT1_IRQHandler:
    ldr   r0,=GPT1_DriverIRQHandler
    bx    r0
    .size GPT1_IRQHandler, . - GPT1_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO1_INT7_IRQHandler
    .type GPIO1_INT7_IRQHandler, %function
GPIO1_INT7_IRQHandler:
    ldr   r0,=GPIO1_INT7_DriverIRQHandler
    bx    r0
    .size GPIO1_INT7_IRQHandler, . - GPIO1_INT7_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO1_INT6_IRQHandler
    .type GPIO1_INT6_IRQHandler, %function
GPIO1_INT6_IRQHandler:
    ldr   r0,=GPIO1_INT6_DriverIRQHandler
    bx    r0
    .size GPIO1_INT6_IRQHandler, . - GPIO1_INT6_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO1_INT5_IRQHandler
    .type GPIO1_INT5_IRQHandler, %function
GPIO1_INT5_IRQHandler:
    ldr   r0,=GPIO1_INT5_DriverIRQHandler
    bx    r0
    .size GPIO1_INT5_IRQHandler, . - GPIO1_INT5_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO1_INT4_IRQHandler
    .type GPIO1_INT4_IRQHandler, %function
GPIO1_INT4_IRQHandler:
    ldr   r0,=GPIO1_INT4_DriverIRQHandler
    bx    r0
    .size GPIO1_INT4_IRQHandler, . - GPIO1_INT4_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO1_INT3_IRQHandler
    .type GPIO1_INT3_IRQHandler, %function
GPIO1_INT3_IRQHandler:
    ldr   r0,=GPIO1_INT3_DriverIRQHandler
    bx    r0
    .size GPIO1_INT3_IRQHandler, . - GPIO1_INT3_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO1_INT2_IRQHandler
    .type GPIO1_INT2_IRQHandler, %function
GPIO1_INT2_IRQHandler:
    ldr   r0,=GPIO1_INT2_DriverIRQHandler
    bx    r0
    .size GPIO1_INT2_IRQHandler, . - GPIO1_INT2_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO1_INT1_IRQHandler
    .type GPIO1_INT1_IRQHandler, %function
GPIO1_INT1_IRQHandler:
    ldr   r0,=GPIO1_INT1_DriverIRQHandler
    bx    r0
    .size GPIO1_INT1_IRQHandler, . - GPIO1_INT1_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO1_INT0_IRQHandler
    .type GPIO1_INT0_IRQHandler, %function
GPIO1_INT0_IRQHandler:
    ldr   r0,=GPIO1_INT0_DriverIRQHandler
    bx    r0
    .size GPIO1_INT0_IRQHandler, . - GPIO1_INT0_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO1_Combined_0_15_IRQHandler
    .type GPIO1_Combined_0_15_IRQHandler, %function
GPIO1_Combined_0_15_IRQHandler:
    ldr   r0,=GPIO1_Combined_0_15_DriverIRQHandler
    bx    r0
    .size GPIO1_Combined_0_15_IRQHandler, . - GPIO1_Combined_0_15_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO1_Combined_16_31_IRQHandler
    .type GPIO1_Combined_16_31_IRQHandler, %function
GPIO1_Combined_16_31_IRQHandler:
    ldr   r0,=GPIO1_Combined_16_31_DriverIRQHandler
    bx    r0
    .size GPIO1_Combined_16_31_IRQHandler, . - GPIO1_Combined_16_31_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO2_Combined_0_15_IRQHandler
    .type GPIO2_Combined_0_15_IRQHandler, %function
GPIO2_Combined_0_15_IRQHandler:
    ldr   r0,=GPIO2_Combined_0_15_DriverIRQHandler
    bx    r0
    .size GPIO2_Combined_0_15_IRQHandler, . - GPIO2_Combined_0_15_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO2_Combined_16_31_IRQHandler
    .type GPIO2_Combined_16_31_IRQHandler, %function
GPIO2_Combined_16_31_IRQHandler:
    ldr   r0,=GPIO2_Combined_16_31_DriverIRQHandler
    bx    r0
    .size GPIO2_Combined_16_31_IRQHandler, . - GPIO2_Combined_16_31_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO3_Combined_0_15_IRQHandler
    .type GPIO3_Combined_0_15_IRQHandler, %function
GPIO3_Combined_0_15_IRQHandler:
    ldr   r0,=GPIO3_Combined_0_15_DriverIRQHandler
    bx    r0
    .size GPIO3_Combined_0_15_IRQHandler, . - GPIO3_Combined_0_15_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO3_Combined_16_31_IRQHandler
    .type GPIO3_Combined_16_31_IRQHandler, %function
GPIO3_Combined_16_31_IRQHandler:
    ldr   r0,=GPIO3_Combined_16_31_DriverIRQHandler
    bx    r0
    .size GPIO3_Combined_16_31_IRQHandler, . - GPIO3_Combined_16_31_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO4_Combined_0_15_IRQHandler
    .type GPIO4_Combined_0_15_IRQHandler, %function
GPIO4_Combined_0_15_IRQHandler:
    ldr   r0,=GPIO4_Combined_0_15_DriverIRQHandler
    bx    r0
    .size GPIO4_Combined_0_15_IRQHandler, . - GPIO4_Combined_0_15_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO4_Combined_16_31_IRQHandler
    .type GPIO4_Combined_16_31_IRQHandler, %function
GPIO4_Combined_16_31_IRQHandler:
    ldr   r0,=GPIO4_Combined_16_31_DriverIRQHandler
    bx    r0
    .size GPIO4_Combined_16_31_IRQHandler, . - GPIO4_Combined_16_31_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO5_Combined_0_15_IRQHandler
    .type GPIO5_Combined_0_15_IRQHandler, %function
GPIO5_Combined_0_15_IRQHandler:
    ldr   r0,=GPIO5_Combined_0_15_DriverIRQHandler
    bx    r0
    .size GPIO5_Combined_0_15_IRQHandler, . - GPIO5_Combined_0_15_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO5_Combined_16_31_IRQHandler
    .type GPIO5_Combined_16_31_IRQHandler, %function
GPIO5_Combined_16_31_IRQHandler:
    ldr   r0,=GPIO5_Combined_16_31_DriverIRQHandler
    bx    r0
    .size GPIO5_Combined_16_31_IRQHandler, . - GPIO5_Combined_16_31_IRQHandler

    .align 1
    .thumb_func
    .weak ISP1_IRQHandler
    .type ISP1_IRQHandler, %function
ISP1_IRQHandler:
    ldr   r0,=ISP1_DriverIRQHandler
    bx    r0
    .size ISP1_IRQHandler, . - ISP1_IRQHandler

    .align 1
    .thumb_func
    .weak ISP2_IRQHandler
    .type ISP2_IRQHandler, %function
ISP2_IRQHandler:
    ldr   r0,=ISP2_DriverIRQHandler
    bx    r0
    .size ISP2_IRQHandler, . - ISP2_IRQHandler

    .align 1
    .thumb_func
    .weak I2C5_IRQHandler
    .type I2C5_IRQHandler, %function
I2C5_IRQHandler:
    ldr   r0,=I2C5_DriverIRQHandler
    bx    r0
    .size I2C5_IRQHandler, . - I2C5_IRQHandler

    .align 1
    .thumb_func
    .weak I2C6_IRQHandler
    .type I2C6_IRQHandler, %function
I2C6_IRQHandler:
    ldr   r0,=I2C6_DriverIRQHandler
    bx    r0
    .size I2C6_IRQHandler, . - I2C6_IRQHandler

    .align 1
    .thumb_func
    .weak WDOG1_IRQHandler
    .type WDOG1_IRQHandler, %function
WDOG1_IRQHandler:
    ldr   r0,=WDOG1_DriverIRQHandler
    bx    r0
    .size WDOG1_IRQHandler, . - WDOG1_IRQHandler

    .align 1
    .thumb_func
    .weak WDOG2_IRQHandler
    .type WDOG2_IRQHandler, %function
WDOG2_IRQHandler:
    ldr   r0,=WDOG2_DriverIRQHandler
    bx    r0
    .size WDOG2_IRQHandler, . - WDOG2_IRQHandler

    .align 1
    .thumb_func
    .weak MIPI_CSI2_IRQHandler
    .type MIPI_CSI2_IRQHandler, %function
MIPI_CSI2_IRQHandler:
    ldr   r0,=MIPI_CSI2_DriverIRQHandler
    bx    r0
    .size MIPI_CSI2_IRQHandler, . - MIPI_CSI2_IRQHandler

    .align 1
    .thumb_func
    .weak PWM1_IRQHandler
    .type PWM1_IRQHandler, %function
PWM1_IRQHandler:
    ldr   r0,=PWM1_DriverIRQHandler
    bx    r0
    .size PWM1_IRQHandler, . - PWM1_IRQHandler

    .align 1
    .thumb_func
    .weak PWM2_IRQHandler
    .type PWM2_IRQHandler, %function
PWM2_IRQHandler:
    ldr   r0,=PWM2_DriverIRQHandler
    bx    r0
    .size PWM2_IRQHandler, . - PWM2_IRQHandler

    .align 1
    .thumb_func
    .weak PWM3_IRQHandler
    .type PWM3_IRQHandler, %function
PWM3_IRQHandler:
    ldr   r0,=PWM3_DriverIRQHandler
    bx    r0
    .size PWM3_IRQHandler, . - PWM3_IRQHandler

    .align 1
    .thumb_func
    .weak PWM4_IRQHandler
    .type PWM4_IRQHandler, %function
PWM4_IRQHandler:
    ldr   r0,=PWM4_DriverIRQHandler
    bx    r0
    .size PWM4_IRQHandler, . - PWM4_IRQHandler

    .align 1
    .thumb_func
    .weak CCM_IRQ1_IRQHandler
    .type CCM_IRQ1_IRQHandler, %function
CCM_IRQ1_IRQHandler:
    ldr   r0,=CCM_IRQ1_DriverIRQHandler
    bx    r0
    .size CCM_IRQ1_IRQHandler, . - CCM_IRQ1_IRQHandler

    .align 1
    .thumb_func
    .weak CCM_IRQ2_IRQHandler
    .type CCM_IRQ2_IRQHandler, %function
CCM_IRQ2_IRQHandler:
    ldr   r0,=CCM_IRQ2_DriverIRQHandler
    bx    r0
    .size CCM_IRQ2_IRQHandler, . - CCM_IRQ2_IRQHandler

    .align 1
    .thumb_func
    .weak GPC_IRQHandler
    .type GPC_IRQHandler, %function
GPC_IRQHandler:
    ldr   r0,=GPC_DriverIRQHandler
    bx    r0
    .size GPC_IRQHandler, . - GPC_IRQHandler

    .align 1
    .thumb_func
    .weak MU1_A53_IRQHandler
    .type MU1_A53_IRQHandler, %function
MU1_A53_IRQHandler:
    ldr   r0,=MU1_A53_DriverIRQHandler
    bx    r0
    .size MU1_A53_IRQHandler, . - MU1_A53_IRQHandler

    .align 1
    .thumb_func
    .weak SRC_IRQHandler
    .type SRC_IRQHandler, %function
SRC_IRQHandler:
    ldr   r0,=SRC_DriverIRQHandler
    bx    r0
    .size SRC_IRQHandler, . - SRC_IRQHandler

    .align 1
    .thumb_func
    .weak I2S56_IRQHandler
    .type I2S56_IRQHandler, %function
I2S56_IRQHandler:
    ldr   r0,=I2S56_DriverIRQHandler
    bx    r0
    .size I2S56_IRQHandler, . - I2S56_IRQHandler

    .align 1
    .thumb_func
    .weak RTIC_IRQHandler
    .type RTIC_IRQHandler, %function
RTIC_IRQHandler:
    ldr   r0,=RTIC_DriverIRQHandler
    bx    r0
    .size RTIC_IRQHandler, . - RTIC_IRQHandler

    .align 1
    .thumb_func
    .weak CPU_PerformanceUnit_IRQHandler
    .type CPU_PerformanceUnit_IRQHandler, %function
CPU_PerformanceUnit_IRQHandler:
    ldr   r0,=CPU_PerformanceUnit_DriverIRQHandler
    bx    r0
    .size CPU_PerformanceUnit_IRQHandler, . - CPU_PerformanceUnit_IRQHandler

    .align 1
    .thumb_func
    .weak CPU_CTI_Trigger_IRQHandler
    .type CPU_CTI_Trigger_IRQHandler, %function
CPU_CTI_Trigger_IRQHandler:
    ldr   r0,=CPU_CTI_Trigger_DriverIRQHandler
    bx    r0
    .size CPU_CTI_Trigger_IRQHandler, . - CPU_CTI_Trigger_IRQHandler

    .align 1
    .thumb_func
    .weak SRC_Combined_IRQHandler
    .type SRC_Combined_IRQHandler, %function
SRC_Combined_IRQHandler:
    ldr   r0,=SRC_Combined_DriverIRQHandler
    bx    r0
    .size SRC_Combined_IRQHandler, . - SRC_Combined_IRQHandler

    .align 1
    .thumb_func
    .weak I2S1_IRQHandler
    .type I2S1_IRQHandler, %function
I2S1_IRQHandler:
    ldr   r0,=I2S1_DriverIRQHandler
    bx    r0
    .size I2S1_IRQHandler, . - I2S1_IRQHandler

    .align 1
    .thumb_func
    .weak I2S2_IRQHandler
    .type I2S2_IRQHandler, %function
I2S2_IRQHandler:
    ldr   r0,=I2S2_DriverIRQHandler
    bx    r0
    .size I2S2_IRQHandler, . - I2S2_IRQHandler

    .align 1
    .thumb_func
    .weak MU1_M7_IRQHandler
    .type MU1_M7_IRQHandler, %function
MU1_M7_IRQHandler:
    ldr   r0,=MU1_M7_DriverIRQHandler
    bx    r0
    .size MU1_M7_IRQHandler, . - MU1_M7_IRQHandler

    .align 1
    .thumb_func
    .weak DDR_PerformanceMonitor_IRQHandler
    .type DDR_PerformanceMonitor_IRQHandler, %function
DDR_PerformanceMonitor_IRQHandler:
    ldr   r0,=DDR_PerformanceMonitor_DriverIRQHandler
    bx    r0
    .size DDR_PerformanceMonitor_IRQHandler, . - DDR_PerformanceMonitor_IRQHandler

    .align 1
    .thumb_func
    .weak DDR_IRQHandler
    .type DDR_IRQHandler, %function
DDR_IRQHandler:
    ldr   r0,=DDR_DriverIRQHandler
    bx    r0
    .size DDR_IRQHandler, . - DDR_IRQHandler

    .align 1
    .thumb_func
    .weak DEWARP_IRQHandler
    .type DEWARP_IRQHandler, %function
DEWARP_IRQHandler:
    ldr   r0,=DEWARP_DriverIRQHandler
    bx    r0
    .size DEWARP_IRQHandler, . - DEWARP_IRQHandler

    .align 1
    .thumb_func
    .weak CPU_Error_AXI_IRQHandler
    .type CPU_Error_AXI_IRQHandler, %function
CPU_Error_AXI_IRQHandler:
    ldr   r0,=CPU_Error_AXI_DriverIRQHandler
    bx    r0
    .size CPU_Error_AXI_IRQHandler, . - CPU_Error_AXI_IRQHandler

    .align 1
    .thumb_func
    .weak CPU_Error_L2RAM_IRQHandler
    .type CPU_Error_L2RAM_IRQHandler, %function
CPU_Error_L2RAM_IRQHandler:
    ldr   r0,=CPU_Error_L2RAM_DriverIRQHandler
    bx    r0
    .size CPU_Error_L2RAM_IRQHandler, . - CPU_Error_L2RAM_IRQHandler

    .align 1
    .thumb_func
    .weak SDMA2_IRQHandler
    .type SDMA2_IRQHandler, %function
SDMA2_IRQHandler:
    ldr   r0,=SDMA2_DriverIRQHandler
    bx    r0
    .size SDMA2_IRQHandler, . - SDMA2_IRQHandler

    .align 1
    .thumb_func
    .weak SJC_IRQHandler
    .type SJC_IRQHandler, %function
SJC_IRQHandler:
    ldr   r0,=SJC_DriverIRQHandler
    bx    r0
    .size SJC_IRQHandler, . - SJC_IRQHandler

    .align 1
    .thumb_func
    .weak CAAM_IRQ0_IRQHandler
    .type CAAM_IRQ0_IRQHandler, %function
CAAM_IRQ0_IRQHandler:
    ldr   r0,=CAAM_IRQ0_DriverIRQHandler
    bx    r0
    .size CAAM_IRQ0_IRQHandler, . - CAAM_IRQ0_IRQHandler

    .align 1
    .thumb_func
    .weak CAAM_IRQ1_IRQHandler
    .type CAAM_IRQ1_IRQHandler, %function
CAAM_IRQ1_IRQHandler:
    ldr   r0,=CAAM_IRQ1_DriverIRQHandler
    bx    r0
    .size CAAM_IRQ1_IRQHandler, . - CAAM_IRQ1_IRQHandler

    .align 1
    .thumb_func
    .weak FlexSPI_IRQHandler
    .type FlexSPI_IRQHandler, %function
FlexSPI_IRQHandler:
    ldr   r0,=FlexSPI_DriverIRQHandler
    bx    r0
    .size FlexSPI_IRQHandler, . - FlexSPI_IRQHandler

    .align 1
    .thumb_func
    .weak TZASC_IRQHandler
    .type TZASC_IRQHandler, %function
TZASC_IRQHandler:
    ldr   r0,=TZASC_DriverIRQHandler
    bx    r0
    .size TZASC_IRQHandler, . - TZASC_IRQHandler

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
    .weak I2S7_IRQHandler
    .type I2S7_IRQHandler, %function
I2S7_IRQHandler:
    ldr   r0,=I2S7_DriverIRQHandler
    bx    r0
    .size I2S7_IRQHandler, . - I2S7_IRQHandler

    .align 1
    .thumb_func
    .weak PERFMON1_IRQHandler
    .type PERFMON1_IRQHandler, %function
PERFMON1_IRQHandler:
    ldr   r0,=PERFMON1_DriverIRQHandler
    bx    r0
    .size PERFMON1_IRQHandler, . - PERFMON1_IRQHandler

    .align 1
    .thumb_func
    .weak PERFMON2_IRQHandler
    .type PERFMON2_IRQHandler, %function
PERFMON2_IRQHandler:
    ldr   r0,=PERFMON2_DriverIRQHandler
    bx    r0
    .size PERFMON2_IRQHandler, . - PERFMON2_IRQHandler

    .align 1
    .thumb_func
    .weak CAAM_IRQ2_IRQHandler
    .type CAAM_IRQ2_IRQHandler, %function
CAAM_IRQ2_IRQHandler:
    ldr   r0,=CAAM_IRQ2_DriverIRQHandler
    bx    r0
    .size CAAM_IRQ2_IRQHandler, . - CAAM_IRQ2_IRQHandler

    .align 1
    .thumb_func
    .weak CAAM_ERROR_IRQHandler
    .type CAAM_ERROR_IRQHandler, %function
CAAM_ERROR_IRQHandler:
    ldr   r0,=CAAM_ERROR_DriverIRQHandler
    bx    r0
    .size CAAM_ERROR_IRQHandler, . - CAAM_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak HS_CP0_IRQHandler
    .type HS_CP0_IRQHandler, %function
HS_CP0_IRQHandler:
    ldr   r0,=HS_CP0_DriverIRQHandler
    bx    r0
    .size HS_CP0_IRQHandler, . - HS_CP0_IRQHandler

    .align 1
    .thumb_func
    .weak CM7_CTI_IRQHandler
    .type CM7_CTI_IRQHandler, %function
CM7_CTI_IRQHandler:
    ldr   r0,=CM7_CTI_DriverIRQHandler
    bx    r0
    .size CM7_CTI_IRQHandler, . - CM7_CTI_IRQHandler

    .align 1
    .thumb_func
    .weak ENET1_MAC0_Rx_Tx_Done1_IRQHandler
    .type ENET1_MAC0_Rx_Tx_Done1_IRQHandler, %function
ENET1_MAC0_Rx_Tx_Done1_IRQHandler:
    ldr   r0,=ENET1_MAC0_Rx_Tx_Done1_DriverIRQHandler
    bx    r0
    .size ENET1_MAC0_Rx_Tx_Done1_IRQHandler, . - ENET1_MAC0_Rx_Tx_Done1_IRQHandler

    .align 1
    .thumb_func
    .weak ENET1_MAC0_Rx_Tx_Done2_IRQHandler
    .type ENET1_MAC0_Rx_Tx_Done2_IRQHandler, %function
ENET1_MAC0_Rx_Tx_Done2_IRQHandler:
    ldr   r0,=ENET1_MAC0_Rx_Tx_Done2_DriverIRQHandler
    bx    r0
    .size ENET1_MAC0_Rx_Tx_Done2_IRQHandler, . - ENET1_MAC0_Rx_Tx_Done2_IRQHandler

    .align 1
    .thumb_func
    .weak ENET1_IRQHandler
    .type ENET1_IRQHandler, %function
ENET1_IRQHandler:
    ldr   r0,=ENET1_DriverIRQHandler
    bx    r0
    .size ENET1_IRQHandler, . - ENET1_IRQHandler

    .align 1
    .thumb_func
    .weak ENET1_1588_Timer_IRQHandler
    .type ENET1_1588_Timer_IRQHandler, %function
ENET1_1588_Timer_IRQHandler:
    ldr   r0,=ENET1_1588_Timer_DriverIRQHandler
    bx    r0
    .size ENET1_1588_Timer_IRQHandler, . - ENET1_1588_Timer_IRQHandler

    .align 1
    .thumb_func
    .weak ASRC_IRQHandler
    .type ASRC_IRQHandler, %function
ASRC_IRQHandler:
    ldr   r0,=ASRC_DriverIRQHandler
    bx    r0
    .size ASRC_IRQHandler, . - ASRC_IRQHandler

    .align 1
    .thumb_func
    .weak PCIE_CTRL1_0_IRQHandler
    .type PCIE_CTRL1_0_IRQHandler, %function
PCIE_CTRL1_0_IRQHandler:
    ldr   r0,=PCIE_CTRL1_0_DriverIRQHandler
    bx    r0
    .size PCIE_CTRL1_0_IRQHandler, . - PCIE_CTRL1_0_IRQHandler

    .align 1
    .thumb_func
    .weak PCIE_CTRL1_1_IRQHandler
    .type PCIE_CTRL1_1_IRQHandler, %function
PCIE_CTRL1_1_IRQHandler:
    ldr   r0,=PCIE_CTRL1_1_DriverIRQHandler
    bx    r0
    .size PCIE_CTRL1_1_IRQHandler, . - PCIE_CTRL1_1_IRQHandler

    .align 1
    .thumb_func
    .weak PCIE_CTRL1_2_IRQHandler
    .type PCIE_CTRL1_2_IRQHandler, %function
PCIE_CTRL1_2_IRQHandler:
    ldr   r0,=PCIE_CTRL1_2_DriverIRQHandler
    bx    r0
    .size PCIE_CTRL1_2_IRQHandler, . - PCIE_CTRL1_2_IRQHandler

    .align 1
    .thumb_func
    .weak PCIE_CTRL1_3_IRQHandler
    .type PCIE_CTRL1_3_IRQHandler, %function
PCIE_CTRL1_3_IRQHandler:
    ldr   r0,=PCIE_CTRL1_3_DriverIRQHandler
    bx    r0
    .size PCIE_CTRL1_3_IRQHandler, . - PCIE_CTRL1_3_IRQHandler

    .align 1
    .thumb_func
    .weak PCIE_EDMA_IRQHandler
    .type PCIE_EDMA_IRQHandler, %function
PCIE_EDMA_IRQHandler:
    ldr   r0,=PCIE_EDMA_DriverIRQHandler
    bx    r0
    .size PCIE_EDMA_IRQHandler, . - PCIE_EDMA_IRQHandler

    .align 1
    .thumb_func
    .weak AUDIO_XCVR0_IRQHandler
    .type AUDIO_XCVR0_IRQHandler, %function
AUDIO_XCVR0_IRQHandler:
    ldr   r0,=AUDIO_XCVR0_DriverIRQHandler
    bx    r0
    .size AUDIO_XCVR0_IRQHandler, . - AUDIO_XCVR0_IRQHandler

    .align 1
    .thumb_func
    .weak AUDIO_XCVR1_IRQHandler
    .type AUDIO_XCVR1_IRQHandler, %function
AUDIO_XCVR1_IRQHandler:
    ldr   r0,=AUDIO_XCVR1_DriverIRQHandler
    bx    r0
    .size AUDIO_XCVR1_IRQHandler, . - AUDIO_XCVR1_IRQHandler

    .align 1
    .thumb_func
    .weak AUD2HTX_IRQHandler
    .type AUD2HTX_IRQHandler, %function
AUD2HTX_IRQHandler:
    ldr   r0,=AUD2HTX_DriverIRQHandler
    bx    r0
    .size AUD2HTX_IRQHandler, . - AUD2HTX_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_ERR_IRQHandler
    .type EDMA1_ERR_IRQHandler, %function
EDMA1_ERR_IRQHandler:
    ldr   r0,=EDMA1_ERR_DriverIRQHandler
    bx    r0
    .size EDMA1_ERR_IRQHandler, . - EDMA1_ERR_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_0_15_IRQHandler
    .type EDMA1_0_15_IRQHandler, %function
EDMA1_0_15_IRQHandler:
    ldr   r0,=EDMA1_0_15_DriverIRQHandler
    bx    r0
    .size EDMA1_0_15_IRQHandler, . - EDMA1_0_15_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_16_31_IRQHandler
    .type EDMA1_16_31_IRQHandler, %function
EDMA1_16_31_IRQHandler:
    ldr   r0,=EDMA1_16_31_DriverIRQHandler
    bx    r0
    .size EDMA1_16_31_IRQHandler, . - EDMA1_16_31_IRQHandler

    .align 1
    .thumb_func
    .weak ENET_QOS_PMT_IRQHandler
    .type ENET_QOS_PMT_IRQHandler, %function
ENET_QOS_PMT_IRQHandler:
    ldr   r0,=ENET_QOS_PMT_DriverIRQHandler
    bx    r0
    .size ENET_QOS_PMT_IRQHandler, . - ENET_QOS_PMT_IRQHandler

    .align 1
    .thumb_func
    .weak ENET_QOS_IRQHandler
    .type ENET_QOS_IRQHandler, %function
ENET_QOS_IRQHandler:
    ldr   r0,=ENET_QOS_DriverIRQHandler
    bx    r0
    .size ENET_QOS_IRQHandler, . - ENET_QOS_IRQHandler

    .align 1
    .thumb_func
    .weak MU2_A53_IRQHandler
    .type MU2_A53_IRQHandler, %function
MU2_A53_IRQHandler:
    ldr   r0,=MU2_A53_DriverIRQHandler
    bx    r0
    .size MU2_A53_IRQHandler, . - MU2_A53_IRQHandler

    .align 1
    .thumb_func
    .weak MU2_AUDIO_IRQHandler
    .type MU2_AUDIO_IRQHandler, %function
MU2_AUDIO_IRQHandler:
    ldr   r0,=MU2_AUDIO_DriverIRQHandler
    bx    r0
    .size MU2_AUDIO_IRQHandler, . - MU2_AUDIO_IRQHandler

    .align 1
    .thumb_func
    .weak MU3_M7_IRQHandler
    .type MU3_M7_IRQHandler, %function
MU3_M7_IRQHandler:
    ldr   r0,=MU3_M7_DriverIRQHandler
    bx    r0
    .size MU3_M7_IRQHandler, . - MU3_M7_IRQHandler

    .align 1
    .thumb_func
    .weak MU3_AUDIO_IRQHandler
    .type MU3_AUDIO_IRQHandler, %function
MU3_AUDIO_IRQHandler:
    ldr   r0,=MU3_AUDIO_DriverIRQHandler
    bx    r0
    .size MU3_AUDIO_IRQHandler, . - MU3_AUDIO_IRQHandler

    .align 1
    .thumb_func
    .weak PCIE_CTRL1_IRQHandler
    .type PCIE_CTRL1_IRQHandler, %function
PCIE_CTRL1_IRQHandler:
    ldr   r0,=PCIE_CTRL1_DriverIRQHandler
    bx    r0
    .size PCIE_CTRL1_IRQHandler, . - PCIE_CTRL1_IRQHandler

    .align 1
    .thumb_func
    .weak PCIE_CTRL1_ERR_IRQHandler
    .type PCIE_CTRL1_ERR_IRQHandler, %function
PCIE_CTRL1_ERR_IRQHandler:
    ldr   r0,=PCIE_CTRL1_ERR_DriverIRQHandler
    bx    r0
    .size PCIE_CTRL1_ERR_IRQHandler, . - PCIE_CTRL1_ERR_IRQHandler

    .align 1
    .thumb_func
    .weak CAN_FD1_IRQHandler
    .type CAN_FD1_IRQHandler, %function
CAN_FD1_IRQHandler:
    ldr   r0,=CAN_FD1_DriverIRQHandler
    bx    r0
    .size CAN_FD1_IRQHandler, . - CAN_FD1_IRQHandler

    .align 1
    .thumb_func
    .weak CAN_FD1_ERROR_IRQHandler
    .type CAN_FD1_ERROR_IRQHandler, %function
CAN_FD1_ERROR_IRQHandler:
    ldr   r0,=CAN_FD1_ERROR_DriverIRQHandler
    bx    r0
    .size CAN_FD1_ERROR_IRQHandler, . - CAN_FD1_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak CAN_FD2_IRQHandler
    .type CAN_FD2_IRQHandler, %function
CAN_FD2_IRQHandler:
    ldr   r0,=CAN_FD2_DriverIRQHandler
    bx    r0
    .size CAN_FD2_IRQHandler, . - CAN_FD2_IRQHandler

    .align 1
    .thumb_func
    .weak CAN_FD2_ERROR_IRQHandler
    .type CAN_FD2_ERROR_IRQHandler, %function
CAN_FD2_ERROR_IRQHandler:
    ldr   r0,=CAN_FD2_ERROR_DriverIRQHandler
    bx    r0
    .size CAN_FD2_ERROR_IRQHandler, . - CAN_FD2_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak AUDIO_XCVR_IRQHandler
    .type AUDIO_XCVR_IRQHandler, %function
AUDIO_XCVR_IRQHandler:
    ldr   r0,=AUDIO_XCVR_DriverIRQHandler
    bx    r0
    .size AUDIO_XCVR_IRQHandler, . - AUDIO_XCVR_IRQHandler

    .align 1
    .thumb_func
    .weak DDR_ERR_IRQHandler
    .type DDR_ERR_IRQHandler, %function
DDR_ERR_IRQHandler:
    ldr   r0,=DDR_ERR_DriverIRQHandler
    bx    r0
    .size DDR_ERR_IRQHandler, . - DDR_ERR_IRQHandler

    .align 1
    .thumb_func
    .weak USB1_WAKEUP_IRQHandler
    .type USB1_WAKEUP_IRQHandler, %function
USB1_WAKEUP_IRQHandler:
    ldr   r0,=USB1_WAKEUP_DriverIRQHandler
    bx    r0
    .size USB1_WAKEUP_IRQHandler, . - USB1_WAKEUP_IRQHandler

    .align 1
    .thumb_func
    .weak USB2_WAKEUP_IRQHandler
    .type USB2_WAKEUP_IRQHandler, %function
USB2_WAKEUP_IRQHandler:
    ldr   r0,=USB2_WAKEUP_DriverIRQHandler
    bx    r0
    .size USB2_WAKEUP_IRQHandler, . - USB2_WAKEUP_IRQHandler

    .align 1
    .thumb_func
    .weak MECC_IRQHandler
    .type MECC_IRQHandler, %function
MECC_IRQHandler:
    ldr   r0,=MECC_DriverIRQHandler
    bx    r0
    .size MECC_IRQHandler, . - MECC_IRQHandler

    .align 1
    .thumb_func
    .weak MECC_ERR_IRQHandler
    .type MECC_ERR_IRQHandler, %function
MECC_ERR_IRQHandler:
    ldr   r0,=MECC_ERR_DriverIRQHandler
    bx    r0
    .size MECC_ERR_IRQHandler, . - MECC_ERR_IRQHandler

    .align 1
    .thumb_func
    .weak MECC_S_IRQHandler
    .type MECC_S_IRQHandler, %function
MECC_S_IRQHandler:
    ldr   r0,=MECC_S_DriverIRQHandler
    bx    r0
    .size MECC_S_IRQHandler, . - MECC_S_IRQHandler

    .align 1
    .thumb_func
    .weak MECC_S_ERR_IRQHandler
    .type MECC_S_ERR_IRQHandler, %function
MECC_S_ERR_IRQHandler:
    ldr   r0,=MECC_S_ERR_DriverIRQHandler
    bx    r0
    .size MECC_S_ERR_IRQHandler, . - MECC_S_ERR_IRQHandler


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
    def_irq_handler    Reserved16_DriverIRQHandler
    def_irq_handler    DAP_DriverIRQHandler
    def_irq_handler    SDMA1_DriverIRQHandler
    def_irq_handler    GPU3D_DriverIRQHandler
    def_irq_handler    SNVS_DriverIRQHandler
    def_irq_handler    LCDIF1_DriverIRQHandler
    def_irq_handler    LCDIF2_DriverIRQHandler
    def_irq_handler    VPU_G1_DriverIRQHandler
    def_irq_handler    VPU_G2_DriverIRQHandler
    def_irq_handler    QOS_DriverIRQHandler
    def_irq_handler    WDOG3_DriverIRQHandler
    def_irq_handler    HS_CP1_DriverIRQHandler
    def_irq_handler    APBHDMA_DriverIRQHandler
    def_irq_handler    ML_DriverIRQHandler
    def_irq_handler    BCH_DriverIRQHandler
    def_irq_handler    GPMI_DriverIRQHandler
    def_irq_handler    ISI_DriverIRQHandler
    def_irq_handler    MIPI_CSI1_DriverIRQHandler
    def_irq_handler    MIPI_DSI_DriverIRQHandler
    def_irq_handler    SNVS_Consolidated_DriverIRQHandler
    def_irq_handler    SNVS_Security_DriverIRQHandler
    def_irq_handler    CSU_DriverIRQHandler
    def_irq_handler    USDHC1_DriverIRQHandler
    def_irq_handler    USDHC2_DriverIRQHandler
    def_irq_handler    USDHC3_DriverIRQHandler
    def_irq_handler    GPU2D_DriverIRQHandler
    def_irq_handler    UART1_DriverIRQHandler
    def_irq_handler    UART2_DriverIRQHandler
    def_irq_handler    UART3_DriverIRQHandler
    def_irq_handler    UART4_DriverIRQHandler
    def_irq_handler    VPU_DriverIRQHandler
    def_irq_handler    ECSPI1_DriverIRQHandler
    def_irq_handler    ECSPI2_DriverIRQHandler
    def_irq_handler    ECSPI3_DriverIRQHandler
    def_irq_handler    SDMA3_DriverIRQHandler
    def_irq_handler    I2C1_DriverIRQHandler
    def_irq_handler    I2C2_DriverIRQHandler
    def_irq_handler    I2C3_DriverIRQHandler
    def_irq_handler    I2C4_DriverIRQHandler
    def_irq_handler    RDC_DriverIRQHandler
    def_irq_handler    USB1_DriverIRQHandler
    def_irq_handler    USB2_DriverIRQHandler
    def_irq_handler    ISI_CH1_DriverIRQHandler
    def_irq_handler    HDMI_TX_DriverIRQHandler
    def_irq_handler    PDM_HWVAD_EVENT_DriverIRQHandler
    def_irq_handler    PDM_HWVAD_ERROR_DriverIRQHandler
    def_irq_handler    GPT6_DriverIRQHandler
    def_irq_handler    SCTR_IRQ0_DriverIRQHandler
    def_irq_handler    SCTR_IRQ1_DriverIRQHandler
    def_irq_handler    ANAMIX_DriverIRQHandler
    def_irq_handler    I2S3_DriverIRQHandler
    def_irq_handler    GPT5_DriverIRQHandler
    def_irq_handler    GPT4_DriverIRQHandler
    def_irq_handler    GPT3_DriverIRQHandler
    def_irq_handler    GPT2_DriverIRQHandler
    def_irq_handler    GPT1_DriverIRQHandler
    def_irq_handler    GPIO1_INT7_DriverIRQHandler
    def_irq_handler    GPIO1_INT6_DriverIRQHandler
    def_irq_handler    GPIO1_INT5_DriverIRQHandler
    def_irq_handler    GPIO1_INT4_DriverIRQHandler
    def_irq_handler    GPIO1_INT3_DriverIRQHandler
    def_irq_handler    GPIO1_INT2_DriverIRQHandler
    def_irq_handler    GPIO1_INT1_DriverIRQHandler
    def_irq_handler    GPIO1_INT0_DriverIRQHandler
    def_irq_handler    GPIO1_Combined_0_15_DriverIRQHandler
    def_irq_handler    GPIO1_Combined_16_31_DriverIRQHandler
    def_irq_handler    GPIO2_Combined_0_15_DriverIRQHandler
    def_irq_handler    GPIO2_Combined_16_31_DriverIRQHandler
    def_irq_handler    GPIO3_Combined_0_15_DriverIRQHandler
    def_irq_handler    GPIO3_Combined_16_31_DriverIRQHandler
    def_irq_handler    GPIO4_Combined_0_15_DriverIRQHandler
    def_irq_handler    GPIO4_Combined_16_31_DriverIRQHandler
    def_irq_handler    GPIO5_Combined_0_15_DriverIRQHandler
    def_irq_handler    GPIO5_Combined_16_31_DriverIRQHandler
    def_irq_handler    ISP1_DriverIRQHandler
    def_irq_handler    ISP2_DriverIRQHandler
    def_irq_handler    I2C5_DriverIRQHandler
    def_irq_handler    I2C6_DriverIRQHandler
    def_irq_handler    WDOG1_DriverIRQHandler
    def_irq_handler    WDOG2_DriverIRQHandler
    def_irq_handler    MIPI_CSI2_DriverIRQHandler
    def_irq_handler    PWM1_DriverIRQHandler
    def_irq_handler    PWM2_DriverIRQHandler
    def_irq_handler    PWM3_DriverIRQHandler
    def_irq_handler    PWM4_DriverIRQHandler
    def_irq_handler    CCM_IRQ1_DriverIRQHandler
    def_irq_handler    CCM_IRQ2_DriverIRQHandler
    def_irq_handler    GPC_DriverIRQHandler
    def_irq_handler    MU1_A53_DriverIRQHandler
    def_irq_handler    SRC_DriverIRQHandler
    def_irq_handler    I2S56_DriverIRQHandler
    def_irq_handler    RTIC_DriverIRQHandler
    def_irq_handler    CPU_PerformanceUnit_DriverIRQHandler
    def_irq_handler    CPU_CTI_Trigger_DriverIRQHandler
    def_irq_handler    SRC_Combined_DriverIRQHandler
    def_irq_handler    I2S1_DriverIRQHandler
    def_irq_handler    I2S2_DriverIRQHandler
    def_irq_handler    MU1_M7_DriverIRQHandler
    def_irq_handler    DDR_PerformanceMonitor_DriverIRQHandler
    def_irq_handler    DDR_DriverIRQHandler
    def_irq_handler    DEWARP_DriverIRQHandler
    def_irq_handler    CPU_Error_AXI_DriverIRQHandler
    def_irq_handler    CPU_Error_L2RAM_DriverIRQHandler
    def_irq_handler    SDMA2_DriverIRQHandler
    def_irq_handler    SJC_DriverIRQHandler
    def_irq_handler    CAAM_IRQ0_DriverIRQHandler
    def_irq_handler    CAAM_IRQ1_DriverIRQHandler
    def_irq_handler    FlexSPI_DriverIRQHandler
    def_irq_handler    TZASC_DriverIRQHandler
    def_irq_handler    PDM_EVENT_DriverIRQHandler
    def_irq_handler    PDM_ERROR_DriverIRQHandler
    def_irq_handler    I2S7_DriverIRQHandler
    def_irq_handler    PERFMON1_DriverIRQHandler
    def_irq_handler    PERFMON2_DriverIRQHandler
    def_irq_handler    CAAM_IRQ2_DriverIRQHandler
    def_irq_handler    CAAM_ERROR_DriverIRQHandler
    def_irq_handler    HS_CP0_DriverIRQHandler
    def_irq_handler    CM7_CTI_DriverIRQHandler
    def_irq_handler    ENET1_MAC0_Rx_Tx_Done1_DriverIRQHandler
    def_irq_handler    ENET1_MAC0_Rx_Tx_Done2_DriverIRQHandler
    def_irq_handler    ENET1_DriverIRQHandler
    def_irq_handler    ENET1_1588_Timer_DriverIRQHandler
    def_irq_handler    ASRC_DriverIRQHandler
    def_irq_handler    PCIE_CTRL1_0_DriverIRQHandler
    def_irq_handler    PCIE_CTRL1_1_DriverIRQHandler
    def_irq_handler    PCIE_CTRL1_2_DriverIRQHandler
    def_irq_handler    PCIE_CTRL1_3_DriverIRQHandler
    def_irq_handler    PCIE_EDMA_DriverIRQHandler
    def_irq_handler    AUDIO_XCVR0_DriverIRQHandler
    def_irq_handler    AUDIO_XCVR1_DriverIRQHandler
    def_irq_handler    AUD2HTX_DriverIRQHandler
    def_irq_handler    EDMA1_ERR_DriverIRQHandler
    def_irq_handler    EDMA1_0_15_DriverIRQHandler
    def_irq_handler    EDMA1_16_31_DriverIRQHandler
    def_irq_handler    ENET_QOS_PMT_DriverIRQHandler
    def_irq_handler    ENET_QOS_DriverIRQHandler
    def_irq_handler    MU2_A53_DriverIRQHandler
    def_irq_handler    MU2_AUDIO_DriverIRQHandler
    def_irq_handler    MU3_M7_DriverIRQHandler
    def_irq_handler    MU3_AUDIO_DriverIRQHandler
    def_irq_handler    PCIE_CTRL1_DriverIRQHandler
    def_irq_handler    PCIE_CTRL1_ERR_DriverIRQHandler
    def_irq_handler    CAN_FD1_DriverIRQHandler
    def_irq_handler    CAN_FD1_ERROR_DriverIRQHandler
    def_irq_handler    CAN_FD2_DriverIRQHandler
    def_irq_handler    CAN_FD2_ERROR_DriverIRQHandler
    def_irq_handler    AUDIO_XCVR_DriverIRQHandler
    def_irq_handler    DDR_ERR_DriverIRQHandler
    def_irq_handler    USB1_WAKEUP_DriverIRQHandler
    def_irq_handler    USB2_WAKEUP_DriverIRQHandler
    def_irq_handler    MECC_DriverIRQHandler
    def_irq_handler    MECC_ERR_DriverIRQHandler
    def_irq_handler    MECC_S_DriverIRQHandler
    def_irq_handler    MECC_S_ERR_DriverIRQHandler

    .end
