/* ------------------------------------------------------------------------- */
/*  @file:    startup_MIMX8MN6_cm7.s                                         */
/*  @purpose: CMSIS Cortex-M7 Core Device Startup File                       */
/*            MIMX8MN6_cm7                                                   */
/*  @version: 2.0                                                            */
/*  @date:    2019-9-23                                                      */
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
    .long   GPR_IRQ_IRQHandler                              /* GPR Interrupt. Used to notify cores on exception condition while boot.*/
    .long   DAP_IRQHandler                                  /* DAP Interrupt*/
    .long   SDMA1_IRQHandler                                /* AND of all 48 SDMA1 interrupts (events) from all the channels*/
    .long   GPU3D_IRQHandler                                /* GPU3D Interrupt*/
    .long   SNVS_IRQHandler                                 /* ON-OFF button press shorter than 5 seconds (pulse event)*/
    .long   LCDIF_IRQHandler                                /* LCDIF Interrupt*/
    .long   SPDIF1_IRQHandler                               /* SPDIF1 RZX/TX Interrupt*/
    .long   Reserved23_IRQHandler                           /* Reserved Interrupt*/
    .long   Reserved24_IRQHandler                           /* Reserved Interrupt*/
    .long   QOS_IRQHandler                                  /* QOS interrupt*/
    .long   WDOG3_IRQHandler                                /* Watchdog Timer reset*/
    .long   HS_CP1_IRQHandler                               /* HS Interrupt Request*/
    .long   APBHDMA_IRQHandler                              /* GPMI operation channel 0-3 description complete interrupt*/
    .long   Reserved29_IRQHandler                           /* Reserved*/
    .long   BCH_IRQHandler                                  /* BCH operation complete interrupt*/
    .long   GPMI_IRQHandler                                 /* GPMI operation TIMEOUT ERROR interrupt*/
    .long   ISI_CH0_IRQHandler                              /* ISI Camera Channel 0 Interrupt*/
    .long   MIPI_CSI1_IRQHandler                            /* MIPI CSI Interrupt*/
    .long   MIPI_DSI_IRQHandler                             /* MIPI DSI Interrupt*/
    .long   SNVS_Consolidated_IRQHandler                    /* SRTC Consolidated Interrupt. Non TZ.*/
    .long   SNVS_Security_IRQHandler                        /* SRTC Security Interrupt. TZ.*/
    .long   CSU_IRQHandler                                  /* CSU Interrupt Request. Indicates to the processor that one or more alarm inputs were asserted.*/
    .long   USDHC1_IRQHandler                               /* uSDHC1 Enhanced SDHC Interrupt Request*/
    .long   USDHC2_IRQHandler                               /* uSDHC2 Enhanced SDHC Interrupt Request*/
    .long   USDHC3_IRQHandler                               /* uSDHC3 Enhanced SDHC Interrupt Request*/
    .long   Reserved41_IRQHandler                           /* Reserved Interrupt*/
    .long   UART1_IRQHandler                                /* UART-1 ORed interrupt*/
    .long   UART2_IRQHandler                                /* UART-2 ORed interrupt*/
    .long   UART3_IRQHandler                                /* UART-3 ORed interrupt*/
    .long   UART4_IRQHandler                                /* UART-4 ORed interrupt*/
    .long   Reserved46_IRQHandler                           /* Reserved Interrupt*/
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
    .long   Reserved57_IRQHandler                           /* Reserved Interrupt*/
    .long   ISI_CH1_IRQHandler                              /* ISI Camera Channel 1 Interrupt*/
    .long   ISI_CH2_IRQHandler                              /* ISI Camera Channel 2 Interrupt*/
    .long   PDM_HWVAD_EVENT_IRQHandler                      /* Digital Microphone interface voice activity detector event interrupt*/
    .long   PDM_HWVAD_ERROR_IRQHandler                      /* Digital Microphone interface voice activity detector error interrupt*/
    .long   GPT6_IRQHandler                                 /* OR of GPT Rollover interrupt line, Input Capture 1 and 2 lines, Output Compare 1, 2, and 3 Interrupt lines*/
    .long   SCTR_IRQ0_IRQHandler                            /* System Counter Interrupt 0*/
    .long   SCTR_IRQ1_IRQHandler                            /* System Counter Interrupt 1*/
    .long   TEMPMON_LOW_IRQHandler                          /* TempSensor (Temperature low alarm).*/
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
    .long   Reserved90_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved91_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved92_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved93_IRQHandler                           /* Reserved interrupt*/
    .long   WDOG1_IRQHandler                                /* Watchdog Timer reset*/
    .long   WDOG2_IRQHandler                                /* Watchdog Timer reset*/
    .long   Reserved96_IRQHandler                           /* Reserved interrupt*/
    .long   PWM1_IRQHandler                                 /* Cumulative interrupt line. OR of Rollover Interrupt line, Compare Interrupt line and FIFO Waterlevel crossing interrupt line.*/
    .long   PWM2_IRQHandler                                 /* Cumulative interrupt line. OR of Rollover Interrupt line, Compare Interrupt line and FIFO Waterlevel crossing interrupt line.*/
    .long   PWM3_IRQHandler                                 /* Cumulative interrupt line. OR of Rollover Interrupt line, Compare Interrupt line and FIFO Waterlevel crossing interrupt line.*/
    .long   PWM4_IRQHandler                                 /* Cumulative interrupt line. OR of Rollover Interrupt line, Compare Interrupt line and FIFO Waterlevel crossing interrupt line.*/
    .long   CCM_IRQ1_IRQHandler                             /* CCM Interrupt Request 1*/
    .long   CCM_IRQ2_IRQHandler                             /* CCM Interrupt Request 2*/
    .long   GPC_IRQHandler                                  /* GPC Interrupt Request 1*/
    .long   MU_A53_IRQHandler                               /* Interrupt to A53*/
    .long   SRC_IRQHandler                                  /* SRC interrupt request*/
    .long   I2S56_IRQHandler                                /* SAI5/6 Receive / Transmit Interrupt*/
    .long   RTIC_IRQHandler                                 /* RTIC Interrupt*/
    .long   CPU_PerformanceUnit_IRQHandler                  /* Performance Unit Interrupts from Cheetah (interrnally: PMUIRQ[n]*/
    .long   CPU_CTI_Trigger_IRQHandler                      /* CTI trigger outputs (internal: nCTIIRQ[n]*/
    .long   SRC_Combined_IRQHandler                         /* Combined CPU wdog interrupts (4x) out of SRC.*/
    .long   Reserved111_IRQHandler                          /* Reserved Interrupt*/
    .long   I2S2_IRQHandler                                 /* SAI2 Receive / Transmit Interrupt*/
    .long   MU_M7_IRQHandler                                /* Interrupt to M7*/
    .long   DDR_PerformanceMonitor_IRQHandler               /* ddr Interrupt for performance monitor*/
    .long   DDR_IRQHandler                                  /* ddr Interrupt*/
    .long   Reserved116_IRQHandler                          /* Reserved interrupt*/
    .long   CPU_Error_AXI_IRQHandler                        /* CPU Error indicator for AXI transaction with a write response error condition*/
    .long   CPU_Error_L2RAM_IRQHandler                      /* CPU Error indicator for L2 RAM double-bit ECC error*/
    .long   SDMA2_IRQHandler                                /* AND of all 48 SDMA2 interrupts (events) from all the channels*/
    .long   SJC_IRQHandler                                  /* Interrupt triggered by SJC register*/
    .long   CAAM_IRQ0_IRQHandler                            /* CAAM interrupt queue for JQ*/
    .long   CAAM_IRQ1_IRQHandler                            /* CAAM interrupt queue for JQ*/
    .long   QSPI_IRQHandler                                 /* QSPI Interrupt*/
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
    .long   Reserved139_IRQHandler                          /* Reserved Interrupt*/
    .long   Reserved140_IRQHandler                          /* Reserved Interrupt*/
    .long   Reserved141_IRQHandler                          /* Reserved Interrupt*/
    .long   ISI_CH3_IRQHandler                              /* ISI Camera Channel 3 Interrupt*/
    .long   Reserved143_IRQHandler                          /* Reserved Interrupt*/

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
    .weak SDMA1_IRQHandler
    .type SDMA1_IRQHandler, %function
SDMA1_IRQHandler:
    ldr   r0,=SDMA1_DriverIRQHandler
    bx    r0
    .size SDMA1_IRQHandler, . - SDMA1_IRQHandler

    .align 1
    .thumb_func
    .weak SPDIF1_IRQHandler
    .type SPDIF1_IRQHandler, %function
SPDIF1_IRQHandler:
    ldr   r0,=SPDIF1_DriverIRQHandler
    bx    r0
    .size SPDIF1_IRQHandler, . - SPDIF1_IRQHandler

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
    .weak I2S3_IRQHandler
    .type I2S3_IRQHandler, %function
I2S3_IRQHandler:
    ldr   r0,=I2S3_DriverIRQHandler
    bx    r0
    .size I2S3_IRQHandler, . - I2S3_IRQHandler

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
    .weak I2S2_IRQHandler
    .type I2S2_IRQHandler, %function
I2S2_IRQHandler:
    ldr   r0,=I2S2_DriverIRQHandler
    bx    r0
    .size I2S2_IRQHandler, . - I2S2_IRQHandler

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
    .weak QSPI_IRQHandler
    .type QSPI_IRQHandler, %function
QSPI_IRQHandler:
    ldr   r0,=QSPI_DriverIRQHandler
    bx    r0
    .size QSPI_IRQHandler, . - QSPI_IRQHandler

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
    .weak I2S7_IRQHandler
    .type I2S7_IRQHandler, %function
I2S7_IRQHandler:
    ldr   r0,=I2S7_DriverIRQHandler
    bx    r0
    .size I2S7_IRQHandler, . - I2S7_IRQHandler

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
    def_irq_handler    GPR_IRQ_IRQHandler
    def_irq_handler    DAP_IRQHandler
    def_irq_handler    SDMA1_DriverIRQHandler
    def_irq_handler    GPU3D_IRQHandler
    def_irq_handler    SNVS_IRQHandler
    def_irq_handler    LCDIF_IRQHandler
    def_irq_handler    SPDIF1_DriverIRQHandler
    def_irq_handler    Reserved23_IRQHandler
    def_irq_handler    Reserved24_IRQHandler
    def_irq_handler    QOS_IRQHandler
    def_irq_handler    WDOG3_IRQHandler
    def_irq_handler    HS_CP1_IRQHandler
    def_irq_handler    APBHDMA_DriverIRQHandler
    def_irq_handler    Reserved29_IRQHandler
    def_irq_handler    BCH_IRQHandler
    def_irq_handler    GPMI_IRQHandler
    def_irq_handler    ISI_CH0_IRQHandler
    def_irq_handler    MIPI_CSI1_IRQHandler
    def_irq_handler    MIPI_DSI_IRQHandler
    def_irq_handler    SNVS_Consolidated_IRQHandler
    def_irq_handler    SNVS_Security_IRQHandler
    def_irq_handler    CSU_IRQHandler
    def_irq_handler    USDHC1_DriverIRQHandler
    def_irq_handler    USDHC2_DriverIRQHandler
    def_irq_handler    USDHC3_DriverIRQHandler
    def_irq_handler    Reserved41_IRQHandler
    def_irq_handler    UART1_DriverIRQHandler
    def_irq_handler    UART2_DriverIRQHandler
    def_irq_handler    UART3_DriverIRQHandler
    def_irq_handler    UART4_DriverIRQHandler
    def_irq_handler    Reserved46_IRQHandler
    def_irq_handler    ECSPI1_DriverIRQHandler
    def_irq_handler    ECSPI2_DriverIRQHandler
    def_irq_handler    ECSPI3_DriverIRQHandler
    def_irq_handler    SDMA3_DriverIRQHandler
    def_irq_handler    I2C1_DriverIRQHandler
    def_irq_handler    I2C2_DriverIRQHandler
    def_irq_handler    I2C3_DriverIRQHandler
    def_irq_handler    I2C4_DriverIRQHandler
    def_irq_handler    RDC_IRQHandler
    def_irq_handler    USB1_IRQHandler
    def_irq_handler    Reserved57_IRQHandler
    def_irq_handler    ISI_CH1_IRQHandler
    def_irq_handler    ISI_CH2_IRQHandler
    def_irq_handler    PDM_HWVAD_EVENT_DriverIRQHandler
    def_irq_handler    PDM_HWVAD_ERROR_DriverIRQHandler
    def_irq_handler    GPT6_IRQHandler
    def_irq_handler    SCTR_IRQ0_IRQHandler
    def_irq_handler    SCTR_IRQ1_IRQHandler
    def_irq_handler    TEMPMON_LOW_IRQHandler
    def_irq_handler    I2S3_DriverIRQHandler
    def_irq_handler    GPT5_IRQHandler
    def_irq_handler    GPT4_IRQHandler
    def_irq_handler    GPT3_IRQHandler
    def_irq_handler    GPT2_IRQHandler
    def_irq_handler    GPT1_IRQHandler
    def_irq_handler    GPIO1_INT7_IRQHandler
    def_irq_handler    GPIO1_INT6_IRQHandler
    def_irq_handler    GPIO1_INT5_IRQHandler
    def_irq_handler    GPIO1_INT4_IRQHandler
    def_irq_handler    GPIO1_INT3_IRQHandler
    def_irq_handler    GPIO1_INT2_IRQHandler
    def_irq_handler    GPIO1_INT1_IRQHandler
    def_irq_handler    GPIO1_INT0_IRQHandler
    def_irq_handler    GPIO1_Combined_0_15_IRQHandler
    def_irq_handler    GPIO1_Combined_16_31_IRQHandler
    def_irq_handler    GPIO2_Combined_0_15_IRQHandler
    def_irq_handler    GPIO2_Combined_16_31_IRQHandler
    def_irq_handler    GPIO3_Combined_0_15_IRQHandler
    def_irq_handler    GPIO3_Combined_16_31_IRQHandler
    def_irq_handler    GPIO4_Combined_0_15_IRQHandler
    def_irq_handler    GPIO4_Combined_16_31_IRQHandler
    def_irq_handler    GPIO5_Combined_0_15_IRQHandler
    def_irq_handler    GPIO5_Combined_16_31_IRQHandler
    def_irq_handler    Reserved90_IRQHandler
    def_irq_handler    Reserved91_IRQHandler
    def_irq_handler    Reserved92_IRQHandler
    def_irq_handler    Reserved93_IRQHandler
    def_irq_handler    WDOG1_IRQHandler
    def_irq_handler    WDOG2_IRQHandler
    def_irq_handler    Reserved96_IRQHandler
    def_irq_handler    PWM1_IRQHandler
    def_irq_handler    PWM2_IRQHandler
    def_irq_handler    PWM3_IRQHandler
    def_irq_handler    PWM4_IRQHandler
    def_irq_handler    CCM_IRQ1_IRQHandler
    def_irq_handler    CCM_IRQ2_IRQHandler
    def_irq_handler    GPC_IRQHandler
    def_irq_handler    MU_A53_IRQHandler
    def_irq_handler    SRC_IRQHandler
    def_irq_handler    I2S56_DriverIRQHandler
    def_irq_handler    RTIC_IRQHandler
    def_irq_handler    CPU_PerformanceUnit_IRQHandler
    def_irq_handler    CPU_CTI_Trigger_IRQHandler
    def_irq_handler    SRC_Combined_IRQHandler
    def_irq_handler    Reserved111_IRQHandler
    def_irq_handler    I2S2_DriverIRQHandler
    def_irq_handler    MU_M7_IRQHandler
    def_irq_handler    DDR_PerformanceMonitor_IRQHandler
    def_irq_handler    DDR_IRQHandler
    def_irq_handler    Reserved116_IRQHandler
    def_irq_handler    CPU_Error_AXI_IRQHandler
    def_irq_handler    CPU_Error_L2RAM_IRQHandler
    def_irq_handler    SDMA2_DriverIRQHandler
    def_irq_handler    SJC_IRQHandler
    def_irq_handler    CAAM_IRQ0_IRQHandler
    def_irq_handler    CAAM_IRQ1_IRQHandler
    def_irq_handler    QSPI_DriverIRQHandler
    def_irq_handler    TZASC_IRQHandler
    def_irq_handler    PDM_EVENT_DriverIRQHandler
    def_irq_handler    PDM_ERROR_IRQHandler
    def_irq_handler    I2S7_DriverIRQHandler
    def_irq_handler    PERFMON1_IRQHandler
    def_irq_handler    PERFMON2_IRQHandler
    def_irq_handler    CAAM_IRQ2_IRQHandler
    def_irq_handler    CAAM_ERROR_IRQHandler
    def_irq_handler    HS_CP0_IRQHandler
    def_irq_handler    CM7_CTI_IRQHandler
    def_irq_handler    ENET1_MAC0_Rx_Tx_Done1_DriverIRQHandler
    def_irq_handler    ENET1_MAC0_Rx_Tx_Done2_DriverIRQHandler
    def_irq_handler    ENET1_DriverIRQHandler
    def_irq_handler    ENET1_1588_Timer_DriverIRQHandler
    def_irq_handler    ASRC_IRQHandler
    def_irq_handler    Reserved139_IRQHandler
    def_irq_handler    Reserved140_IRQHandler
    def_irq_handler    Reserved141_IRQHandler
    def_irq_handler    ISI_CH3_IRQHandler
    def_irq_handler    Reserved143_IRQHandler

    .end
