/* ------------------------------------------------------------------------- */
/*  @file:    startup_MCIMX7U5_cm4.s                                         */
/*  @purpose: CMSIS Cortex-M4 Core Device Startup File                       */
/*            MCIMX7U5_cm4                                                   */
/*  @version: 7.0                                                            */
/*  @date:    2018-11-5                                                      */
/*  @build:   b200408                                                        */
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
    .long   CTI0_IRQHandler                                 /* Cross Trigger Interface for CM4*/
    .long   DMA0_0_4_IRQHandler                             /* DMA Channel 0, 4 Transfer Complete*/
    .long   DMA0_1_5_IRQHandler                             /* DMA Channel 1, 5 Transfer Complete*/
    .long   DMA0_2_6_IRQHandler                             /* DMA Channel 2, 6 Transfer Complete*/
    .long   DMA0_3_7_IRQHandler                             /* DMA Channel 3, 7 Transfer Complete*/
    .long   DMA0_8_12_IRQHandler                            /* DMA Channel 8, 12 Transfer Complete*/
    .long   DMA0_9_13_IRQHandler                            /* DMA Channel 9, 13 Transfer Complete*/
    .long   DMA0_10_14_IRQHandler                           /* DMA Channel 10, 14 Transfer Complete*/
    .long   DMA0_11_15_IRQHandler                           /* DMA Channel 11, 15 Transfer Complete*/
    .long   DMA0_16_20_IRQHandler                           /* DMA Channel 16, 20 Transfer Complete*/
    .long   DMA0_17_21_IRQHandler                           /* DMA Channel 17, 21 Transfer Complete*/
    .long   DMA0_18_22_IRQHandler                           /* DMA Channel 18, 22 Transfer Complete*/
    .long   DMA0_19_23_IRQHandler                           /* DMA Channel 19, 23 Transfer Complete*/
    .long   DMA0_24_28_IRQHandler                           /* DMA Channel 24, 28 Transfer Complete*/
    .long   DMA0_25_29_IRQHandler                           /* DMA Channel 25, 29 Transfer Complete*/
    .long   DMA0_26_30_IRQHandler                           /* DMA Channel 26, 30 Transfer Complete*/
    .long   DMA0_27_31_IRQHandler                           /* DMA Channel 27, 31 Transfer Complete*/
    .long   DMA0_Error_IRQHandler                           /* DMA Error Interrupt - All Channels*/
    .long   MCM0_IRQHandler                                 /* MCM Interrupt*/
    .long   EWM_IRQHandler                                  /* External Watchdog Monitor Interrupt*/
    .long   LLWU0_IRQHandler                                /* Low Leakage Wake Up*/
    .long   SIM_IRQHandler                                  /* System Integation Module*/
    .long   MU_A_IRQHandler                                 /* Messaging Unit - Side A*/
    .long   Reserved39_IRQHandler                           /* Secured JTAG Controller*/
    .long   Software1_IRQHandler                            /* Software Interrupt*/
    .long   Software2_IRQHandler                            /* Software Interrupt*/
    .long   WDOG0_IRQHandler                                /* Watchdog Interrupt*/
    .long   SCG0_IRQHandler                                 /* System Clock Generator for M4 domain*/
    .long   QSPI_IRQHandler                                 /* Quad Serial Peripheral Interface*/
    .long   LTC_IRQHandler                                  /* Low Power Trusted Cryptography*/
    .long   XRDC_IRQHandler                                 /* Extended Domain Resource Controller*/
    .long   SNVS_IRQHandler                                 /* Secure Non-Volatile Storage Consolidated Interrupt*/
    .long   TRNG0_IRQHandler                                /* Random Number Generator*/
    .long   LPIT0_IRQHandler                                /* Low Power Periodic Interrupt Timer*/
    .long   PMC0_IRQHandler                                 /* Power Management  Control interrupts for M4 domain*/
    .long   CMC0_IRQHandler                                 /* Core Mode Controller interrupts for M4 domain*/
    .long   LPTMR0_IRQHandler                               /* Low Power Timer*/
    .long   LPTMR1_IRQHandler                               /* Low Power Timer*/
    .long   TPM0_IRQHandler                                 /* Timer PWM module*/
    .long   TPM1_IRQHandler                                 /* Timer PWM module*/
    .long   TPM2_IRQHandler                                 /* Timer PWM module*/
    .long   TPM3_IRQHandler                                 /* Timer PWM module*/
    .long   FLEXIO0_IRQHandler                              /* Flexible IO*/
    .long   LPI2C0_IRQHandler                               /* Inter-integrated circuit 0*/
    .long   LPI2C1_IRQHandler                               /* Inter-integrated circuit 1*/
    .long   LPI2C2_IRQHandler                               /* Inter-integrated circuit 2*/
    .long   LPI2C3_IRQHandler                               /* Inter-integrated circuit 3*/
    .long   I2S0_IRQHandler                                 /* Serial Audio Interface 0*/
    .long   I2S1_IRQHandler                                 /* Serial Audio Interface 1*/
    .long   LPSPI0_IRQHandler                               /* Low Power Serial Peripheral Interface*/
    .long   LPSPI1_IRQHandler                               /* Low Power Serial Peripheral Interface*/
    .long   LPUART0_IRQHandler                              /* Low Power UART*/
    .long   LPUART1_IRQHandler                              /* Low Power UART*/
    .long   LPUART2_IRQHandler                              /* Low Power UART*/
    .long   LPUART3_IRQHandler                              /* Low Power UART*/
    .long   DPM_IRQHandler                                  /* Dynamic Process Monitor*/
    .long   PCTLA_IRQHandler                                /* Port A pin interrupt*/
    .long   PCTLB_IRQHandler                                /* Port B pin interrupt*/
    .long   ADC0_IRQHandler                                 /* Analog to Digital Convertor*/
    .long   ADC1_IRQHandler                                 /* Analog to Digital Convertor*/
    .long   CMP0_IRQHandler                                 /* Comparator*/
    .long   CMP1_IRQHandler                                 /* Comparator*/
    .long   DAC0_IRQHandler                                 /* Digital to Analog Convertor*/
    .long   DAC1_IRQHandler                                 /* Digital to Analog Convertor*/
    .long   WDOG1_IRQHandler                                /* Watchdog Interrupt from A7 subsystem*/
    .long   USB0_IRQHandler                                 /* USB 0 Interrupt from A7 subsystem*/
    .long   USB1_IRQHandler                                 /* USB 1 Interrupt from A7 subsystem*/
    .long   Reserved83_IRQHandler                           /* */
    .long   WDOG2_IRQHandler                                /* Watchdog Interrupt from A7 subsystem*/
    .long   USBPHY_IRQHandler                               /* USB PHY (used in conjunction with USBOTG1)*/
    .long   CMC1_IRQHandler                                 /* A7 resets*/
    .long   Reserved87_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved88_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved89_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved90_IRQHandler                           /* Reserved interrupt*/
    .long   GPU3D_IRQHandler                                /* Graphics Processing Unit 3D*/
    .long   GPU2D_IRQHandler                                /* Graphics Processing Unit 2D*/
    .long   Reserved93_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved94_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved95_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved96_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved97_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved98_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved99_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved100_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved101_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved102_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved103_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved104_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved105_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved106_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved107_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved108_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved109_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved110_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved111_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved112_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved113_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved114_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved115_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved116_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved117_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved118_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved119_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved120_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved121_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved122_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved123_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved124_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved125_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved126_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved127_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved128_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved129_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved130_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved131_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved132_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved133_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved134_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved135_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved136_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved137_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved138_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved139_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved140_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved141_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved142_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved143_IRQHandler                          /* Reserved interrupt*/

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
.LC2:
    cmp     r1, r2
    itt    lt
    strlt   r0, [r1], #4
    blt    .LC2
#endif /* __STARTUP_CLEAR_BSS */

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
    .weak DMA0_0_4_IRQHandler
    .type DMA0_0_4_IRQHandler, %function
DMA0_0_4_IRQHandler:
    ldr   r0,=DMA0_0_4_DriverIRQHandler
    bx    r0
    .size DMA0_0_4_IRQHandler, . - DMA0_0_4_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_1_5_IRQHandler
    .type DMA0_1_5_IRQHandler, %function
DMA0_1_5_IRQHandler:
    ldr   r0,=DMA0_1_5_DriverIRQHandler
    bx    r0
    .size DMA0_1_5_IRQHandler, . - DMA0_1_5_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_2_6_IRQHandler
    .type DMA0_2_6_IRQHandler, %function
DMA0_2_6_IRQHandler:
    ldr   r0,=DMA0_2_6_DriverIRQHandler
    bx    r0
    .size DMA0_2_6_IRQHandler, . - DMA0_2_6_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_3_7_IRQHandler
    .type DMA0_3_7_IRQHandler, %function
DMA0_3_7_IRQHandler:
    ldr   r0,=DMA0_3_7_DriverIRQHandler
    bx    r0
    .size DMA0_3_7_IRQHandler, . - DMA0_3_7_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_8_12_IRQHandler
    .type DMA0_8_12_IRQHandler, %function
DMA0_8_12_IRQHandler:
    ldr   r0,=DMA0_8_12_DriverIRQHandler
    bx    r0
    .size DMA0_8_12_IRQHandler, . - DMA0_8_12_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_9_13_IRQHandler
    .type DMA0_9_13_IRQHandler, %function
DMA0_9_13_IRQHandler:
    ldr   r0,=DMA0_9_13_DriverIRQHandler
    bx    r0
    .size DMA0_9_13_IRQHandler, . - DMA0_9_13_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_10_14_IRQHandler
    .type DMA0_10_14_IRQHandler, %function
DMA0_10_14_IRQHandler:
    ldr   r0,=DMA0_10_14_DriverIRQHandler
    bx    r0
    .size DMA0_10_14_IRQHandler, . - DMA0_10_14_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_11_15_IRQHandler
    .type DMA0_11_15_IRQHandler, %function
DMA0_11_15_IRQHandler:
    ldr   r0,=DMA0_11_15_DriverIRQHandler
    bx    r0
    .size DMA0_11_15_IRQHandler, . - DMA0_11_15_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_16_20_IRQHandler
    .type DMA0_16_20_IRQHandler, %function
DMA0_16_20_IRQHandler:
    ldr   r0,=DMA0_16_20_DriverIRQHandler
    bx    r0
    .size DMA0_16_20_IRQHandler, . - DMA0_16_20_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_17_21_IRQHandler
    .type DMA0_17_21_IRQHandler, %function
DMA0_17_21_IRQHandler:
    ldr   r0,=DMA0_17_21_DriverIRQHandler
    bx    r0
    .size DMA0_17_21_IRQHandler, . - DMA0_17_21_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_18_22_IRQHandler
    .type DMA0_18_22_IRQHandler, %function
DMA0_18_22_IRQHandler:
    ldr   r0,=DMA0_18_22_DriverIRQHandler
    bx    r0
    .size DMA0_18_22_IRQHandler, . - DMA0_18_22_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_19_23_IRQHandler
    .type DMA0_19_23_IRQHandler, %function
DMA0_19_23_IRQHandler:
    ldr   r0,=DMA0_19_23_DriverIRQHandler
    bx    r0
    .size DMA0_19_23_IRQHandler, . - DMA0_19_23_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_24_28_IRQHandler
    .type DMA0_24_28_IRQHandler, %function
DMA0_24_28_IRQHandler:
    ldr   r0,=DMA0_24_28_DriverIRQHandler
    bx    r0
    .size DMA0_24_28_IRQHandler, . - DMA0_24_28_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_25_29_IRQHandler
    .type DMA0_25_29_IRQHandler, %function
DMA0_25_29_IRQHandler:
    ldr   r0,=DMA0_25_29_DriverIRQHandler
    bx    r0
    .size DMA0_25_29_IRQHandler, . - DMA0_25_29_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_26_30_IRQHandler
    .type DMA0_26_30_IRQHandler, %function
DMA0_26_30_IRQHandler:
    ldr   r0,=DMA0_26_30_DriverIRQHandler
    bx    r0
    .size DMA0_26_30_IRQHandler, . - DMA0_26_30_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_27_31_IRQHandler
    .type DMA0_27_31_IRQHandler, %function
DMA0_27_31_IRQHandler:
    ldr   r0,=DMA0_27_31_DriverIRQHandler
    bx    r0
    .size DMA0_27_31_IRQHandler, . - DMA0_27_31_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_Error_IRQHandler
    .type DMA0_Error_IRQHandler, %function
DMA0_Error_IRQHandler:
    ldr   r0,=DMA0_Error_DriverIRQHandler
    bx    r0
    .size DMA0_Error_IRQHandler, . - DMA0_Error_IRQHandler

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
    .weak FLEXIO0_IRQHandler
    .type FLEXIO0_IRQHandler, %function
FLEXIO0_IRQHandler:
    ldr   r0,=FLEXIO0_DriverIRQHandler
    bx    r0
    .size FLEXIO0_IRQHandler, . - FLEXIO0_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C0_IRQHandler
    .type LPI2C0_IRQHandler, %function
LPI2C0_IRQHandler:
    ldr   r0,=LPI2C0_DriverIRQHandler
    bx    r0
    .size LPI2C0_IRQHandler, . - LPI2C0_IRQHandler

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
    .weak LPI2C3_IRQHandler
    .type LPI2C3_IRQHandler, %function
LPI2C3_IRQHandler:
    ldr   r0,=LPI2C3_DriverIRQHandler
    bx    r0
    .size LPI2C3_IRQHandler, . - LPI2C3_IRQHandler

    .align 1
    .thumb_func
    .weak I2S0_IRQHandler
    .type I2S0_IRQHandler, %function
I2S0_IRQHandler:
    ldr   r0,=I2S0_DriverIRQHandler
    bx    r0
    .size I2S0_IRQHandler, . - I2S0_IRQHandler

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
    .weak LPSPI0_IRQHandler
    .type LPSPI0_IRQHandler, %function
LPSPI0_IRQHandler:
    ldr   r0,=LPSPI0_DriverIRQHandler
    bx    r0
    .size LPSPI0_IRQHandler, . - LPSPI0_IRQHandler

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
    .weak LPUART0_IRQHandler
    .type LPUART0_IRQHandler, %function
LPUART0_IRQHandler:
    ldr   r0,=LPUART0_DriverIRQHandler
    bx    r0
    .size LPUART0_IRQHandler, . - LPUART0_IRQHandler

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
    .weak LPUART3_IRQHandler
    .type LPUART3_IRQHandler, %function
LPUART3_IRQHandler:
    ldr   r0,=LPUART3_DriverIRQHandler
    bx    r0
    .size LPUART3_IRQHandler, . - LPUART3_IRQHandler


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
    def_irq_handler    CTI0_IRQHandler
    def_irq_handler    DMA0_0_4_DriverIRQHandler
    def_irq_handler    DMA0_1_5_DriverIRQHandler
    def_irq_handler    DMA0_2_6_DriverIRQHandler
    def_irq_handler    DMA0_3_7_DriverIRQHandler
    def_irq_handler    DMA0_8_12_DriverIRQHandler
    def_irq_handler    DMA0_9_13_DriverIRQHandler
    def_irq_handler    DMA0_10_14_DriverIRQHandler
    def_irq_handler    DMA0_11_15_DriverIRQHandler
    def_irq_handler    DMA0_16_20_DriverIRQHandler
    def_irq_handler    DMA0_17_21_DriverIRQHandler
    def_irq_handler    DMA0_18_22_DriverIRQHandler
    def_irq_handler    DMA0_19_23_DriverIRQHandler
    def_irq_handler    DMA0_24_28_DriverIRQHandler
    def_irq_handler    DMA0_25_29_DriverIRQHandler
    def_irq_handler    DMA0_26_30_DriverIRQHandler
    def_irq_handler    DMA0_27_31_DriverIRQHandler
    def_irq_handler    DMA0_Error_DriverIRQHandler
    def_irq_handler    MCM0_IRQHandler
    def_irq_handler    EWM_IRQHandler
    def_irq_handler    LLWU0_IRQHandler
    def_irq_handler    SIM_IRQHandler
    def_irq_handler    MU_A_IRQHandler
    def_irq_handler    Reserved39_IRQHandler
    def_irq_handler    Software1_IRQHandler
    def_irq_handler    Software2_IRQHandler
    def_irq_handler    WDOG0_IRQHandler
    def_irq_handler    SCG0_IRQHandler
    def_irq_handler    QSPI_DriverIRQHandler
    def_irq_handler    LTC_IRQHandler
    def_irq_handler    XRDC_IRQHandler
    def_irq_handler    SNVS_IRQHandler
    def_irq_handler    TRNG0_IRQHandler
    def_irq_handler    LPIT0_IRQHandler
    def_irq_handler    PMC0_IRQHandler
    def_irq_handler    CMC0_IRQHandler
    def_irq_handler    LPTMR0_IRQHandler
    def_irq_handler    LPTMR1_IRQHandler
    def_irq_handler    TPM0_IRQHandler
    def_irq_handler    TPM1_IRQHandler
    def_irq_handler    TPM2_IRQHandler
    def_irq_handler    TPM3_IRQHandler
    def_irq_handler    FLEXIO0_DriverIRQHandler
    def_irq_handler    LPI2C0_DriverIRQHandler
    def_irq_handler    LPI2C1_DriverIRQHandler
    def_irq_handler    LPI2C2_DriverIRQHandler
    def_irq_handler    LPI2C3_DriverIRQHandler
    def_irq_handler    I2S0_DriverIRQHandler
    def_irq_handler    I2S1_DriverIRQHandler
    def_irq_handler    LPSPI0_DriverIRQHandler
    def_irq_handler    LPSPI1_DriverIRQHandler
    def_irq_handler    LPUART0_DriverIRQHandler
    def_irq_handler    LPUART1_DriverIRQHandler
    def_irq_handler    LPUART2_DriverIRQHandler
    def_irq_handler    LPUART3_DriverIRQHandler
    def_irq_handler    DPM_IRQHandler
    def_irq_handler    PCTLA_IRQHandler
    def_irq_handler    PCTLB_IRQHandler
    def_irq_handler    ADC0_IRQHandler
    def_irq_handler    ADC1_IRQHandler
    def_irq_handler    CMP0_IRQHandler
    def_irq_handler    CMP1_IRQHandler
    def_irq_handler    DAC0_IRQHandler
    def_irq_handler    DAC1_IRQHandler
    def_irq_handler    WDOG1_IRQHandler
    def_irq_handler    USB0_IRQHandler
    def_irq_handler    USB1_IRQHandler
    def_irq_handler    Reserved83_IRQHandler
    def_irq_handler    WDOG2_IRQHandler
    def_irq_handler    USBPHY_IRQHandler
    def_irq_handler    CMC1_IRQHandler
    def_irq_handler    Reserved87_IRQHandler
    def_irq_handler    Reserved88_IRQHandler
    def_irq_handler    Reserved89_IRQHandler
    def_irq_handler    Reserved90_IRQHandler
    def_irq_handler    GPU3D_IRQHandler
    def_irq_handler    GPU2D_IRQHandler
    def_irq_handler    Reserved93_IRQHandler
    def_irq_handler    Reserved94_IRQHandler
    def_irq_handler    Reserved95_IRQHandler
    def_irq_handler    Reserved96_IRQHandler
    def_irq_handler    Reserved97_IRQHandler
    def_irq_handler    Reserved98_IRQHandler
    def_irq_handler    Reserved99_IRQHandler
    def_irq_handler    Reserved100_IRQHandler
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
    def_irq_handler    Reserved115_IRQHandler
    def_irq_handler    Reserved116_IRQHandler
    def_irq_handler    Reserved117_IRQHandler
    def_irq_handler    Reserved118_IRQHandler
    def_irq_handler    Reserved119_IRQHandler
    def_irq_handler    Reserved120_IRQHandler
    def_irq_handler    Reserved121_IRQHandler
    def_irq_handler    Reserved122_IRQHandler
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
    def_irq_handler    Reserved139_IRQHandler
    def_irq_handler    Reserved140_IRQHandler
    def_irq_handler    Reserved141_IRQHandler
    def_irq_handler    Reserved142_IRQHandler
    def_irq_handler    Reserved143_IRQHandler

    .end
