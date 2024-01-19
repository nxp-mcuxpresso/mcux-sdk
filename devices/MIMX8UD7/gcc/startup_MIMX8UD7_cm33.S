/* ------------------------------------------------------------------------- */
/*  @file:    startup_MIMX8UD7_cm33.s                                        */
/*  @purpose: CMSIS Cortex-M33 Core Device Startup File                      */
/*            MIMX8UD7_cm33                                                  */
/*  @version: 5.0                                                            */
/*  @date:    2023-4-27                                                      */
/*  @build:   b230607                                                        */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright 1997-2016 Freescale Semiconductor, Inc.                         */
/* Copyright 2016-2023 NXP                                                   */
/* SPDX-License-Identifier: BSD-3-Clause                                     */
/*****************************************************************************/
/* Version: GCC for ARM Embedded Processors                                  */
/*****************************************************************************/
    .syntax unified
    .arch armv8-m.main

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
    .long   SecureFault_Handler                             /* Secure Fault Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   SVC_Handler                                     /* SVCall Handler*/
    .long   DebugMon_Handler                                /* Debug Monitor Handler*/
    .long   0                                               /* Reserved*/
    .long   PendSV_Handler                                  /* PendSV Handler*/
    .long   SysTick_Handler                                 /* SysTick Handler*/

                                                            /* External Interrupts*/
    .long   CTI0_IRQHandler                                 /* Cross Trigger Interface*/
    .long   DMA0_0_IRQHandler                               /* DMA0 Channel 0 Error or Transfer Complete*/
    .long   DMA0_1_IRQHandler                               /* DMA0 Channel 1 Error or Transfer Complete*/
    .long   DMA0_2_IRQHandler                               /* DMA0 Channel 2 Error or Transfer Complete*/
    .long   DMA0_3_IRQHandler                               /* DMA0 Channel 3 Error or Transfer Complete*/
    .long   DMA0_4_IRQHandler                               /* DMA0 Channel 4 Error or Transfer Complete*/
    .long   DMA0_5_IRQHandler                               /* DMA0 Channel 5 Error or Transfer Complete*/
    .long   DMA0_6_IRQHandler                               /* DMA0 Channel 6 Error or Transfer Complete*/
    .long   DMA0_7_IRQHandler                               /* DMA0 Channel 7 Error or Transfer Complete*/
    .long   DMA0_8_IRQHandler                               /* DMA0 Channel 8 Error or Transfer Complete*/
    .long   DMA0_9_IRQHandler                               /* DMA0 Channel 9 Error or Transfer Complete*/
    .long   DMA0_10_IRQHandler                              /* DMA0 Channel 10 Error or Transfer Complete*/
    .long   DMA0_11_IRQHandler                              /* DMA0 Channel 11 Error or Transfer Complete*/
    .long   DMA0_12_IRQHandler                              /* DMA0 Channel 12 Error or Transfer Complete*/
    .long   DMA0_13_IRQHandler                              /* DMA0 Channel 13 Error or Transfer Complete*/
    .long   DMA0_14_IRQHandler                              /* DMA0 Channel 14 Error or Transfer Complete*/
    .long   DMA0_15_IRQHandler                              /* DMA0 Channel 15 Error or Transfer Complete*/
    .long   DMA0_16_IRQHandler                              /* DMA0 Channel 16 Error or Transfer Complete*/
    .long   DMA0_17_IRQHandler                              /* DMA0 Channel 17 Error or Transfer Complete*/
    .long   DMA0_18_IRQHandler                              /* DMA0 Channel 18 Error or Transfer Complete*/
    .long   DMA0_19_IRQHandler                              /* DMA0 Channel 19 Error or Transfer Complete*/
    .long   DMA0_20_IRQHandler                              /* DMA0 Channel 20 Error or Transfer Complete*/
    .long   DMA0_21_IRQHandler                              /* DMA0 Channel 21 Error or Transfer Complete*/
    .long   DMA0_22_IRQHandler                              /* DMA0 Channel 22 Error or Transfer Complete*/
    .long   DMA0_23_IRQHandler                              /* DMA0 Channel 23 Error or Transfer Complete*/
    .long   DMA0_24_IRQHandler                              /* DMA0 Channel 24 Error or Transfer Complete*/
    .long   DMA0_25_IRQHandler                              /* DMA0 Channel 25 Error or Transfer Complete*/
    .long   DMA0_26_IRQHandler                              /* DMA0 Channel 26 Error or Transfer Complete*/
    .long   DMA0_27_IRQHandler                              /* DMA0 Channel 27 Error or Transfer Complete*/
    .long   DMA0_28_IRQHandler                              /* DMA0 Channel 28 Error or Transfer Complete*/
    .long   DMA0_29_IRQHandler                              /* DMA0 Channel 29 Error or Transfer Complete*/
    .long   DMA0_30_IRQHandler                              /* DMA0 Channel 30 Error or Transfer Complete*/
    .long   DMA0_31_IRQHandler                              /* DMA0 Channel 31 Error or Transfer Complete*/
    .long   DMA2_0_IRQHandler                               /* DMA2 Channel 0 Error or Transfer Complete*/
    .long   DMA2_1_IRQHandler                               /* DMA2 Channel 1 Error or Transfer Complete*/
    .long   DMA2_2_IRQHandler                               /* DMA2 Channel 2 Error or Transfer Complete*/
    .long   DMA2_3_IRQHandler                               /* DMA2 Channel 3 Error or Transfer Complete*/
    .long   DMA2_4_IRQHandler                               /* DMA2 Channel 4 Error or Transfer Complete*/
    .long   DMA2_5_IRQHandler                               /* DMA2 Channel 5 Error or Transfer Complete*/
    .long   DMA2_6_IRQHandler                               /* DMA2 Channel 6 Error or Transfer Complete*/
    .long   DMA2_7_IRQHandler                               /* DMA2 Channel 7 Error or Transfer Complete*/
    .long   DMA2_8_IRQHandler                               /* DMA2 Channel 8 Error or Transfer Complete*/
    .long   DMA2_9_IRQHandler                               /* DMA2 Channel 9 Error or Transfer Complete*/
    .long   DMA2_10_IRQHandler                              /* DMA2 Channel 10 Error or Transfer Complete*/
    .long   DMA2_11_IRQHandler                              /* DMA2 Channel 11 Error or Transfer Complete*/
    .long   DMA2_12_IRQHandler                              /* DMA2 Channel 12 Error or Transfer Complete*/
    .long   DMA2_13_IRQHandler                              /* DMA2 Channel 13 Error or Transfer Complete*/
    .long   DMA2_14_IRQHandler                              /* DMA2 Channel 14 Error or Transfer Complete*/
    .long   DMA2_15_IRQHandler                              /* DMA2 Channel 15 Error or Transfer Complete*/
    .long   DMA2_16_IRQHandler                              /* DMA2 Channel 16 Error or Transfer Complete*/
    .long   DMA2_17_IRQHandler                              /* DMA2 Channel 17 Error or Transfer Complete*/
    .long   DMA2_18_IRQHandler                              /* DMA2 Channel 18 Error or Transfer Complete*/
    .long   DMA2_19_IRQHandler                              /* DMA2 Channel 19 Error or Transfer Complete*/
    .long   DMA2_20_IRQHandler                              /* DMA2 Channel 20 Error or Transfer Complete*/
    .long   DMA2_21_IRQHandler                              /* DMA2 Channel 21 Error or Transfer Complete*/
    .long   DMA2_22_IRQHandler                              /* DMA2 Channel 22 Error or Transfer Complete*/
    .long   DMA2_23_IRQHandler                              /* DMA2 Channel 23 Error or Transfer Complete*/
    .long   DMA2_24_IRQHandler                              /* DMA2 Channel 24 Error or Transfer Complete*/
    .long   DMA2_25_IRQHandler                              /* DMA2 Channel 25 Error or Transfer Complete*/
    .long   DMA2_26_IRQHandler                              /* DMA2 Channel 26 Error or Transfer Complete*/
    .long   DMA2_27_IRQHandler                              /* DMA2 Channel 27 Error or Transfer Complete*/
    .long   DMA2_28_IRQHandler                              /* DMA2 Channel 28 Error or Transfer Complete*/
    .long   DMA2_29_IRQHandler                              /* DMA2 Channel 29 Error or Transfer Complete*/
    .long   DMA2_30_IRQHandler                              /* DMA2 Channel 30 Error or Transfer Complete*/
    .long   DMA2_31_IRQHandler                              /* DMA2 Channel 31 Error or Transfer Complete*/
    .long   CMC0_IRQHandler                                 /* Core Mode Controller 0*/
    .long   CMC2_IRQHandler                                 /* Core Mode Controller 2*/
    .long   uPower_IRQHandler                               /* uPower interrupt*/
    .long   WUU0_IRQHandler                                 /* Wake Up Unit 0*/
    .long   CGC0_IRQHandler                                 /* System Clock Generator for RT interrupt*/
    .long   CGC1_IRQHandler                                 /* Clock Generation and Control 1*/
    .long   CGC2_IRQHandler                                 /* Clock Generation and Control 2*/
    .long   SIM0_IRQHandler                                 /* System Integration Module 0*/
    .long   PMC_IRQHandler                                  /* Power Management Controller*/
    .long   MU0_A_IRQHandler                                /* Messaging Unit 0 - Side A (to communicate with A35core)*/
    .long   MU1_A_IRQHandler                                /* Messaging Unit 1 - Side A (to communicate with Fusion DSP)*/
    .long   MU2_A_IRQHandler                                /* Messaging Unit 2 - Side A (to communicate with HiFi4 DSP)*/
    .long   WDOG0_IRQHandler                                /* Watchdog 0 Interrupt*/
    .long   WDOG1_IRQHandler                                /* Watchdog 1 Interrupt*/
    .long   WDOG2_IRQHandler                                /* Watchdog 2 Interrupt*/
    .long   WDOG3_IRQHandler                                /* Watchdog 3 Interrupt*/
    .long   WDOG4_IRQHandler                                /* Watchdog 4 Interrupt*/
    .long   EWM_IRQHandler                                  /* External Watchdog Monitor Interrupt*/
    .long   CMC1_IRQHandler                                 /* Core Mode Controller 1*/
    .long   SNTCommandInterface_IRQHandler                  /* Sentinel command interface interrupt*/
    .long   SNTSecure_IRQHandler                            /* Sentinel secure interrupt*/
    .long   SNTNonSecure_IRQHandler                         /* Sentinel non-secure interrupt*/
    .long   BBNSM_IRQHandler                                /* Secure Non-Volatile Storage Consolidated Interrupt*/
    .long   TRDC_IRQHandler                                 /* Trusted Resource Domain Controller interrupt*/
    .long   XRDC_IRQHandler                                 /* Extended Rexource Domain Control*/
    .long   LPTMR0_IRQHandler                               /* Low Power Timer 0*/
    .long   LPTMR1_IRQHandler                               /* Low Power Timer 1*/
    .long   Reserved108_IRQHandler                          /* Reserved*/
    .long   Reserved109_IRQHandler                          /* Reserved*/
    .long   LPIT0_IRQHandler                                /* Low Power Periodic Interrupt Timer 0*/
    .long   TPM0_IRQHandler                                 /* Timer PWM module 0*/
    .long   TPM1_IRQHandler                                 /* Timer PWM module 1*/
    .long   TPM2_IRQHandler                                 /* Timer PWM module 2*/
    .long   TPM3_IRQHandler                                 /* Timer PWM module 3*/
    .long   TPM4_IRQHandler                                 /* Timer PWM module 4*/
    .long   Reserved116_IRQHandler                          /* Reserved*/
    .long   MRT0_IRQHandler                                 /* Multi-Rate Timer interrupt*/
    .long   FlexCAN_IRQHandler                              /* Flexible Controller Area Network interrupt*/
    .long   FLEXIO0_IRQHandler                              /* Flexible IO 0*/
    .long   LPI2C0_IRQHandler                               /* Low Power Inter-Integrated Circuit module 0*/
    .long   LPI2C1_IRQHandler                               /* Low Power Inter-Integrated Circuit module 1*/
    .long   LPI2C2_IRQHandler                               /* Low Power Inter-Integrated Circuit module 2*/
    .long   LPI2C3_IRQHandler                               /* Low Power Inter-Integrated Circuit module 3*/
    .long   LPSPI0_IRQHandler                               /* Low Power Serial Peripheral Interface 0*/
    .long   LPSPI1_IRQHandler                               /* Low Power Serial Peripheral Interface 1*/
    .long   LPSPI2_IRQHandler                               /* Low Power Serial Peripheral Interface 2*/
    .long   LPSPI3_IRQHandler                               /* Low Power Serial Peripheral Interface 3*/
    .long   LPUART0_IRQHandler                              /* Low Power UART 0*/
    .long   LPUART1_IRQHandler                              /* Low Power UART 1*/
    .long   LPUART2_IRQHandler                              /* Low Power UART 2*/
    .long   LPUART3_IRQHandler                              /* Low Power UART 3*/
    .long   USB0_IRQHandler                                 /* USB Interrupt from A7 subsystem*/
    .long   USBPHY0_IRQHandler                              /* USB PHY (used in conjunction with USB0)*/
    .long   USB1_IRQHandler                                 /* USB Interrupt from A7 subsystem*/
    .long   USBPHY1_IRQHandler                              /* USB PHY (used in conjunction with USB1)*/
    .long   PDM_EVENT_IRQHandler                            /* Digital Microphone interrupt*/
    .long   PDM_HWVAD_EVENT_IRQHandler                      /* Digital Microphone Voice Activity Detection interrupt*/
    .long   SAI0_IRQHandler                                 /* Serial Audio Interface 0*/
    .long   SAI1_IRQHandler                                 /* Serial Audio Interface 1*/
    .long   SAI2_IRQHandler                                 /* Serial Audio Interface 2*/
    .long   SAI3_IRQHandler                                 /* Serial Audio Interface 3*/
    .long   SAI6_IRQHandler                                 /* Serial Audio Interface 6*/
    .long   SAI7_IRQHandler                                 /* Serial Audio Interface 7*/
    .long   SPDIF_IRQHandler                                /* Sony/Phillips Digital Interface*/
    .long   DCNano_IRQHandler                               /* Display Control Nano interrupt*/
    .long   DSI_IRQHandler                                  /* DSI controller interrupt*/
    .long   GPU3D_IRQHandler                                /* Graphic Processor Unit 3D interrupt*/
    .long   GPU2D_IRQHandler                                /* Graphic Processor Unit 2D interrupt*/
    .long   GPIOA_INT0_IRQHandler                           /* General Purpose Input/Output A interrupt 0*/
    .long   GPIOA_INT1_IRQHandler                           /* General Purpose Input/Output A interrupt 1*/
    .long   GPIOB_INT0_IRQHandler                           /* General Purpose Input/Output B interrupt 0*/
    .long   GPIOB_INT1_IRQHandler                           /* General Purpose Input/Output B interrupt 1*/
    .long   GPIOC_INT0_IRQHandler                           /* General Purpose Input/Output C interrupt 0*/
    .long   GPIOC_INT1_IRQHandler                           /* General Purpose Input/Output C interrupt 1*/
    .long   GPIOD_INT0_IRQHandler                           /* General Purpose Input/Output D interrupt 0*/
    .long   GPIOD_INT1_IRQHandler                           /* General Purpose Input/Output D interrupt 1*/
    .long   GPIOE_INT0_IRQHandler                           /* General Purpose Input/Output E interrupt 0*/
    .long   GPIOE_INT1_IRQHandler                           /* General Purpose Input/Output E interrupt 1*/
    .long   GPIOF_INT0_IRQHandler                           /* General Purpose Input/Output F interrupt 0*/
    .long   GPIOF_INT1_IRQHandler                           /* General Purpose Input/Output F interrupt 1*/
    .long   Reserved161_IRQHandler                          /* Reserved*/
    .long   Reserved162_IRQHandler                          /* Reserved*/
    .long   Reserved163_IRQHandler                          /* Reserved*/
    .long   Reserved164_IRQHandler                          /* Reserved*/
    .long   Reserved165_IRQHandler                          /* Reserved*/
    .long   Reserved166_IRQHandler                          /* Reserved*/
    .long   ADC0_IRQHandler                                 /* Analog to Digital Convertor 0*/
    .long   ADC1_IRQHandler                                 /* Analog to Digital Convertor 1*/
    .long   CMP0_IRQHandler                                 /* Comparator 0*/
    .long   CMP1_IRQHandler                                 /* Comparator 1*/
    .long   DAC0_IRQHandler                                 /* Digital to Analog Convertor 0*/
    .long   DAC1_IRQHandler                                 /* Digital to Analog Convertor 1*/
    .long   FlexSPI0_IRQHandler                             /* FlexSPI controller interface interrupt 0*/
    .long   FlexSPI1_IRQHandler                             /* FlexSPI controller interface interrupt 1*/
    .long   FlexSPI2_IRQHandler                             /* FlexSPI controller interface interrupt 2*/
    .long   uSDHC0_IRQHandler                               /* ultra Secure Digital Host Controller interrupt 0*/
    .long   uSDHC1_IRQHandler                               /* ultra Secure Digital Host Controller interrupt 1*/
    .long   uSDHC2_IRQHandler                               /* ultra Secure Digital Host Controller interrupt 2*/
    .long   MDDR_IRQHandler                                 /* Multi-Port Double Data Rate*/
    .long   FLEXIO1_IRQHandler                              /* Flexible IO 1 interrupt*/
    .long   I3C0_IRQHandler                                 /* Improved Inter-Integrated Circuit 0 interrupt*/
    .long   I3C1_IRQHandler                                 /* Improved Inter-Integrated Circuit 1 interrupt*/
    .long   CASPER_IRQHandler                               /* Cryptographic Accelerator and Signal Processing Engine with RAM-sharing*/
    .long   PowerQuad_IRQHandler                            /* PowerQuad Digital Signal Co-Processor*/
    .long   EPDC_IRQHandler                                 /* Electronics Paper Display Controller interrupt*/
    .long   PXP_IRQHandler                                  /* Pixel Processor interrupt*/
    .long   CTI1_IRQHandler                                 /* Cross Trigger Interface*/
    .long   DMA1_0_IRQHandler                               /* DMA1 Channel 0 error or transfer complete*/
    .long   DMA1_1_IRQHandler                               /* DMA1 Channel 1 error or transfer complete*/
    .long   DMA1_2_IRQHandler                               /* DMA1 Channel 2 error or transfer complete*/
    .long   DMA1_3_IRQHandler                               /* DMA1 Channel 3 error or transfer complete*/
    .long   DMA1_4_IRQHandler                               /* DMA1 Channel 4 error or transfer complete*/
    .long   DMA1_5_IRQHandler                               /* DMA1 Channel 5 error or transfer complete*/
    .long   DMA1_6_IRQHandler                               /* DMA1 Channel 6 error or transfer complete*/
    .long   DMA1_7_IRQHandler                               /* DMA1 Channel 7 error or transfer complete*/
    .long   DefaultISR                                      /* 196*/
    .long   DefaultISR                                      /* 197*/

    .size    __isr_vector, . - __isr_vector

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
    ldr     R0, =__StackLimit
    msr     msplim, R0
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
    .weak DMA0_0_IRQHandler
    .type DMA0_0_IRQHandler, %function
DMA0_0_IRQHandler:
    mov   r0, #0
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_0_IRQHandler, . - DMA0_0_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_1_IRQHandler
    .type DMA0_1_IRQHandler, %function
DMA0_1_IRQHandler:
    mov   r0, #1
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_1_IRQHandler, . - DMA0_1_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_2_IRQHandler
    .type DMA0_2_IRQHandler, %function
DMA0_2_IRQHandler:
    mov   r0, #2
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_2_IRQHandler, . - DMA0_2_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_3_IRQHandler
    .type DMA0_3_IRQHandler, %function
DMA0_3_IRQHandler:
    mov   r0, #3
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_3_IRQHandler, . - DMA0_3_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_4_IRQHandler
    .type DMA0_4_IRQHandler, %function
DMA0_4_IRQHandler:
    mov   r0, #4
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_4_IRQHandler, . - DMA0_4_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_5_IRQHandler
    .type DMA0_5_IRQHandler, %function
DMA0_5_IRQHandler:
    mov   r0, #5
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_5_IRQHandler, . - DMA0_5_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_6_IRQHandler
    .type DMA0_6_IRQHandler, %function
DMA0_6_IRQHandler:
    mov   r0, #6
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_6_IRQHandler, . - DMA0_6_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_7_IRQHandler
    .type DMA0_7_IRQHandler, %function
DMA0_7_IRQHandler:
    mov   r0, #7
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_7_IRQHandler, . - DMA0_7_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_8_IRQHandler
    .type DMA0_8_IRQHandler, %function
DMA0_8_IRQHandler:
    mov   r0, #8
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_8_IRQHandler, . - DMA0_8_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_9_IRQHandler
    .type DMA0_9_IRQHandler, %function
DMA0_9_IRQHandler:
    mov   r0, #9
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_9_IRQHandler, . - DMA0_9_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_10_IRQHandler
    .type DMA0_10_IRQHandler, %function
DMA0_10_IRQHandler:
    mov   r0, #10
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_10_IRQHandler, . - DMA0_10_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_11_IRQHandler
    .type DMA0_11_IRQHandler, %function
DMA0_11_IRQHandler:
    mov   r0, #11
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_11_IRQHandler, . - DMA0_11_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_12_IRQHandler
    .type DMA0_12_IRQHandler, %function
DMA0_12_IRQHandler:
    mov   r0, #12
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_12_IRQHandler, . - DMA0_12_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_13_IRQHandler
    .type DMA0_13_IRQHandler, %function
DMA0_13_IRQHandler:
    mov   r0, #13
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_13_IRQHandler, . - DMA0_13_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_14_IRQHandler
    .type DMA0_14_IRQHandler, %function
DMA0_14_IRQHandler:
    mov   r0, #14
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_14_IRQHandler, . - DMA0_14_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_15_IRQHandler
    .type DMA0_15_IRQHandler, %function
DMA0_15_IRQHandler:
    mov   r0, #15
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_15_IRQHandler, . - DMA0_15_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_16_IRQHandler
    .type DMA0_16_IRQHandler, %function
DMA0_16_IRQHandler:
    mov   r0, #16
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_16_IRQHandler, . - DMA0_16_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_17_IRQHandler
    .type DMA0_17_IRQHandler, %function
DMA0_17_IRQHandler:
    mov   r0, #17
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_17_IRQHandler, . - DMA0_17_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_18_IRQHandler
    .type DMA0_18_IRQHandler, %function
DMA0_18_IRQHandler:
    mov   r0, #18
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_18_IRQHandler, . - DMA0_18_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_19_IRQHandler
    .type DMA0_19_IRQHandler, %function
DMA0_19_IRQHandler:
    mov   r0, #19
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_19_IRQHandler, . - DMA0_19_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_20_IRQHandler
    .type DMA0_20_IRQHandler, %function
DMA0_20_IRQHandler:
    mov   r0, #20
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_20_IRQHandler, . - DMA0_20_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_21_IRQHandler
    .type DMA0_21_IRQHandler, %function
DMA0_21_IRQHandler:
    mov   r0, #21
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_21_IRQHandler, . - DMA0_21_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_22_IRQHandler
    .type DMA0_22_IRQHandler, %function
DMA0_22_IRQHandler:
    mov   r0, #22
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_22_IRQHandler, . - DMA0_22_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_23_IRQHandler
    .type DMA0_23_IRQHandler, %function
DMA0_23_IRQHandler:
    mov   r0, #23
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_23_IRQHandler, . - DMA0_23_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_24_IRQHandler
    .type DMA0_24_IRQHandler, %function
DMA0_24_IRQHandler:
    mov   r0, #24
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_24_IRQHandler, . - DMA0_24_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_25_IRQHandler
    .type DMA0_25_IRQHandler, %function
DMA0_25_IRQHandler:
    mov   r0, #25
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_25_IRQHandler, . - DMA0_25_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_26_IRQHandler
    .type DMA0_26_IRQHandler, %function
DMA0_26_IRQHandler:
    mov   r0, #26
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_26_IRQHandler, . - DMA0_26_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_27_IRQHandler
    .type DMA0_27_IRQHandler, %function
DMA0_27_IRQHandler:
    mov   r0, #27
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_27_IRQHandler, . - DMA0_27_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_28_IRQHandler
    .type DMA0_28_IRQHandler, %function
DMA0_28_IRQHandler:
    mov   r0, #28
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_28_IRQHandler, . - DMA0_28_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_29_IRQHandler
    .type DMA0_29_IRQHandler, %function
DMA0_29_IRQHandler:
    mov   r0, #29
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_29_IRQHandler, . - DMA0_29_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_30_IRQHandler
    .type DMA0_30_IRQHandler, %function
DMA0_30_IRQHandler:
    mov   r0, #30
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_30_IRQHandler, . - DMA0_30_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_31_IRQHandler
    .type DMA0_31_IRQHandler, %function
DMA0_31_IRQHandler:
    mov   r0, #31
    ldr   r1,=DMA0_DriverIRQHandler
    bx    r1
    .size DMA0_31_IRQHandler, . - DMA0_31_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_0_IRQHandler
    .type DMA2_0_IRQHandler, %function
DMA2_0_IRQHandler:
    mov   r0, #0
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_0_IRQHandler, . - DMA2_0_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_1_IRQHandler
    .type DMA2_1_IRQHandler, %function
DMA2_1_IRQHandler:
    mov   r0, #1
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_1_IRQHandler, . - DMA2_1_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_2_IRQHandler
    .type DMA2_2_IRQHandler, %function
DMA2_2_IRQHandler:
    mov   r0, #2
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_2_IRQHandler, . - DMA2_2_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_3_IRQHandler
    .type DMA2_3_IRQHandler, %function
DMA2_3_IRQHandler:
    mov   r0, #3
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_3_IRQHandler, . - DMA2_3_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_4_IRQHandler
    .type DMA2_4_IRQHandler, %function
DMA2_4_IRQHandler:
    mov   r0, #4
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_4_IRQHandler, . - DMA2_4_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_5_IRQHandler
    .type DMA2_5_IRQHandler, %function
DMA2_5_IRQHandler:
    mov   r0, #5
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_5_IRQHandler, . - DMA2_5_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_6_IRQHandler
    .type DMA2_6_IRQHandler, %function
DMA2_6_IRQHandler:
    mov   r0, #6
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_6_IRQHandler, . - DMA2_6_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_7_IRQHandler
    .type DMA2_7_IRQHandler, %function
DMA2_7_IRQHandler:
    mov   r0, #7
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_7_IRQHandler, . - DMA2_7_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_8_IRQHandler
    .type DMA2_8_IRQHandler, %function
DMA2_8_IRQHandler:
    mov   r0, #8
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_8_IRQHandler, . - DMA2_8_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_9_IRQHandler
    .type DMA2_9_IRQHandler, %function
DMA2_9_IRQHandler:
    mov   r0, #9
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_9_IRQHandler, . - DMA2_9_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_10_IRQHandler
    .type DMA2_10_IRQHandler, %function
DMA2_10_IRQHandler:
    mov   r0, #10
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_10_IRQHandler, . - DMA2_10_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_11_IRQHandler
    .type DMA2_11_IRQHandler, %function
DMA2_11_IRQHandler:
    mov   r0, #11
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_11_IRQHandler, . - DMA2_11_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_12_IRQHandler
    .type DMA2_12_IRQHandler, %function
DMA2_12_IRQHandler:
    mov   r0, #12
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_12_IRQHandler, . - DMA2_12_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_13_IRQHandler
    .type DMA2_13_IRQHandler, %function
DMA2_13_IRQHandler:
    mov   r0, #13
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_13_IRQHandler, . - DMA2_13_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_14_IRQHandler
    .type DMA2_14_IRQHandler, %function
DMA2_14_IRQHandler:
    mov   r0, #14
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_14_IRQHandler, . - DMA2_14_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_15_IRQHandler
    .type DMA2_15_IRQHandler, %function
DMA2_15_IRQHandler:
    mov   r0, #15
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_15_IRQHandler, . - DMA2_15_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_16_IRQHandler
    .type DMA2_16_IRQHandler, %function
DMA2_16_IRQHandler:
    mov   r0, #16
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_16_IRQHandler, . - DMA2_16_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_17_IRQHandler
    .type DMA2_17_IRQHandler, %function
DMA2_17_IRQHandler:
    mov   r0, #17
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_17_IRQHandler, . - DMA2_17_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_18_IRQHandler
    .type DMA2_18_IRQHandler, %function
DMA2_18_IRQHandler:
    mov   r0, #18
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_18_IRQHandler, . - DMA2_18_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_19_IRQHandler
    .type DMA2_19_IRQHandler, %function
DMA2_19_IRQHandler:
    mov   r0, #19
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_19_IRQHandler, . - DMA2_19_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_20_IRQHandler
    .type DMA2_20_IRQHandler, %function
DMA2_20_IRQHandler:
    mov   r0, #20
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_20_IRQHandler, . - DMA2_20_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_21_IRQHandler
    .type DMA2_21_IRQHandler, %function
DMA2_21_IRQHandler:
    mov   r0, #21
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_21_IRQHandler, . - DMA2_21_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_22_IRQHandler
    .type DMA2_22_IRQHandler, %function
DMA2_22_IRQHandler:
    mov   r0, #22
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_22_IRQHandler, . - DMA2_22_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_23_IRQHandler
    .type DMA2_23_IRQHandler, %function
DMA2_23_IRQHandler:
    mov   r0, #23
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_23_IRQHandler, . - DMA2_23_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_24_IRQHandler
    .type DMA2_24_IRQHandler, %function
DMA2_24_IRQHandler:
    mov   r0, #24
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_24_IRQHandler, . - DMA2_24_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_25_IRQHandler
    .type DMA2_25_IRQHandler, %function
DMA2_25_IRQHandler:
    mov   r0, #25
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_25_IRQHandler, . - DMA2_25_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_26_IRQHandler
    .type DMA2_26_IRQHandler, %function
DMA2_26_IRQHandler:
    mov   r0, #26
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_26_IRQHandler, . - DMA2_26_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_27_IRQHandler
    .type DMA2_27_IRQHandler, %function
DMA2_27_IRQHandler:
    mov   r0, #27
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_27_IRQHandler, . - DMA2_27_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_28_IRQHandler
    .type DMA2_28_IRQHandler, %function
DMA2_28_IRQHandler:
    mov   r0, #28
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_28_IRQHandler, . - DMA2_28_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_29_IRQHandler
    .type DMA2_29_IRQHandler, %function
DMA2_29_IRQHandler:
    mov   r0, #29
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_29_IRQHandler, . - DMA2_29_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_30_IRQHandler
    .type DMA2_30_IRQHandler, %function
DMA2_30_IRQHandler:
    mov   r0, #30
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_30_IRQHandler, . - DMA2_30_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_31_IRQHandler
    .type DMA2_31_IRQHandler, %function
DMA2_31_IRQHandler:
    mov   r0, #31
    ldr   r1,=DMA2_DriverIRQHandler
    bx    r1
    .size DMA2_31_IRQHandler, . - DMA2_31_IRQHandler

    .align 1
    .thumb_func
    .weak FlexCAN_IRQHandler
    .type FlexCAN_IRQHandler, %function
FlexCAN_IRQHandler:
    ldr   r0,=CAN0_DriverIRQHandler
    bx    r0
    .size FlexCAN_IRQHandler, . - FlexCAN_IRQHandler

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
    .weak LPSPI2_IRQHandler
    .type LPSPI2_IRQHandler, %function
LPSPI2_IRQHandler:
    ldr   r0,=LPSPI2_DriverIRQHandler
    bx    r0
    .size LPSPI2_IRQHandler, . - LPSPI2_IRQHandler

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
    .weak PDM_HWVAD_EVENT_IRQHandler
    .type PDM_HWVAD_EVENT_IRQHandler, %function
PDM_HWVAD_EVENT_IRQHandler:
    ldr   r0,=PDM_HWVAD_EVENT_DriverIRQHandler
    bx    r0
    .size PDM_HWVAD_EVENT_IRQHandler, . - PDM_HWVAD_EVENT_IRQHandler

    .align 1
    .thumb_func
    .weak SAI0_IRQHandler
    .type SAI0_IRQHandler, %function
SAI0_IRQHandler:
    ldr   r0,=SAI0_DriverIRQHandler
    bx    r0
    .size SAI0_IRQHandler, . - SAI0_IRQHandler

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
    .weak SAI6_IRQHandler
    .type SAI6_IRQHandler, %function
SAI6_IRQHandler:
    ldr   r0,=SAI6_DriverIRQHandler
    bx    r0
    .size SAI6_IRQHandler, . - SAI6_IRQHandler

    .align 1
    .thumb_func
    .weak SAI7_IRQHandler
    .type SAI7_IRQHandler, %function
SAI7_IRQHandler:
    ldr   r0,=SAI7_DriverIRQHandler
    bx    r0
    .size SAI7_IRQHandler, . - SAI7_IRQHandler

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
    .weak FlexSPI0_IRQHandler
    .type FlexSPI0_IRQHandler, %function
FlexSPI0_IRQHandler:
    ldr   r0,=FlexSPI0_DriverIRQHandler
    bx    r0
    .size FlexSPI0_IRQHandler, . - FlexSPI0_IRQHandler

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
    .weak FlexSPI2_IRQHandler
    .type FlexSPI2_IRQHandler, %function
FlexSPI2_IRQHandler:
    ldr   r0,=FlexSPI2_DriverIRQHandler
    bx    r0
    .size FlexSPI2_IRQHandler, . - FlexSPI2_IRQHandler

    .align 1
    .thumb_func
    .weak uSDHC0_IRQHandler
    .type uSDHC0_IRQHandler, %function
uSDHC0_IRQHandler:
    ldr   r0,=uSDHC0_DriverIRQHandler
    bx    r0
    .size uSDHC0_IRQHandler, . - uSDHC0_IRQHandler

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
    .weak FLEXIO1_IRQHandler
    .type FLEXIO1_IRQHandler, %function
FLEXIO1_IRQHandler:
    ldr   r0,=FLEXIO1_DriverIRQHandler
    bx    r0
    .size FLEXIO1_IRQHandler, . - FLEXIO1_IRQHandler

    .align 1
    .thumb_func
    .weak I3C0_IRQHandler
    .type I3C0_IRQHandler, %function
I3C0_IRQHandler:
    ldr   r0,=I3C0_DriverIRQHandler
    bx    r0
    .size I3C0_IRQHandler, . - I3C0_IRQHandler

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
    .weak DMA1_0_IRQHandler
    .type DMA1_0_IRQHandler, %function
DMA1_0_IRQHandler:
    mov   r0, #0
    ldr   r1,=DMA1_DriverIRQHandler
    bx    r1
    .size DMA1_0_IRQHandler, . - DMA1_0_IRQHandler

    .align 1
    .thumb_func
    .weak DMA1_1_IRQHandler
    .type DMA1_1_IRQHandler, %function
DMA1_1_IRQHandler:
    mov   r0, #1
    ldr   r1,=DMA1_DriverIRQHandler
    bx    r1
    .size DMA1_1_IRQHandler, . - DMA1_1_IRQHandler

    .align 1
    .thumb_func
    .weak DMA1_2_IRQHandler
    .type DMA1_2_IRQHandler, %function
DMA1_2_IRQHandler:
    mov   r0, #2
    ldr   r1,=DMA1_DriverIRQHandler
    bx    r1
    .size DMA1_2_IRQHandler, . - DMA1_2_IRQHandler

    .align 1
    .thumb_func
    .weak DMA1_3_IRQHandler
    .type DMA1_3_IRQHandler, %function
DMA1_3_IRQHandler:
    mov   r0, #3
    ldr   r1,=DMA1_DriverIRQHandler
    bx    r1
    .size DMA1_3_IRQHandler, . - DMA1_3_IRQHandler

    .align 1
    .thumb_func
    .weak DMA1_4_IRQHandler
    .type DMA1_4_IRQHandler, %function
DMA1_4_IRQHandler:
    mov   r0, #4
    ldr   r1,=DMA1_DriverIRQHandler
    bx    r1
    .size DMA1_4_IRQHandler, . - DMA1_4_IRQHandler

    .align 1
    .thumb_func
    .weak DMA1_5_IRQHandler
    .type DMA1_5_IRQHandler, %function
DMA1_5_IRQHandler:
    mov   r0, #5
    ldr   r1,=DMA1_DriverIRQHandler
    bx    r1
    .size DMA1_5_IRQHandler, . - DMA1_5_IRQHandler

    .align 1
    .thumb_func
    .weak DMA1_6_IRQHandler
    .type DMA1_6_IRQHandler, %function
DMA1_6_IRQHandler:
    mov   r0, #6
    ldr   r1,=DMA1_DriverIRQHandler
    bx    r1
    .size DMA1_6_IRQHandler, . - DMA1_6_IRQHandler

    .align 1
    .thumb_func
    .weak DMA1_7_IRQHandler
    .type DMA1_7_IRQHandler, %function
DMA1_7_IRQHandler:
    mov   r0, #7
    ldr   r1,=DMA1_DriverIRQHandler
    bx    r1
    .size DMA1_7_IRQHandler, . - DMA1_7_IRQHandler


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
    def_irq_handler    SecureFault_Handler
    def_irq_handler    DebugMon_Handler
    def_irq_handler    CTI0_IRQHandler
    def_irq_handler    DMA0_DriverIRQHandler
    def_irq_handler    DMA2_DriverIRQHandler
    def_irq_handler    CMC0_IRQHandler
    def_irq_handler    CMC2_IRQHandler
    def_irq_handler    uPower_IRQHandler
    def_irq_handler    WUU0_IRQHandler
    def_irq_handler    CGC0_IRQHandler
    def_irq_handler    CGC1_IRQHandler
    def_irq_handler    CGC2_IRQHandler
    def_irq_handler    SIM0_IRQHandler
    def_irq_handler    PMC_IRQHandler
    def_irq_handler    MU0_A_IRQHandler
    def_irq_handler    MU1_A_IRQHandler
    def_irq_handler    MU2_A_IRQHandler
    def_irq_handler    WDOG0_IRQHandler
    def_irq_handler    WDOG1_IRQHandler
    def_irq_handler    WDOG2_IRQHandler
    def_irq_handler    WDOG3_IRQHandler
    def_irq_handler    WDOG4_IRQHandler
    def_irq_handler    EWM_IRQHandler
    def_irq_handler    CMC1_IRQHandler
    def_irq_handler    SNTCommandInterface_IRQHandler
    def_irq_handler    SNTSecure_IRQHandler
    def_irq_handler    SNTNonSecure_IRQHandler
    def_irq_handler    BBNSM_IRQHandler
    def_irq_handler    TRDC_IRQHandler
    def_irq_handler    XRDC_IRQHandler
    def_irq_handler    LPTMR0_IRQHandler
    def_irq_handler    LPTMR1_IRQHandler
    def_irq_handler    Reserved108_IRQHandler
    def_irq_handler    Reserved109_IRQHandler
    def_irq_handler    LPIT0_IRQHandler
    def_irq_handler    TPM0_IRQHandler
    def_irq_handler    TPM1_IRQHandler
    def_irq_handler    TPM2_IRQHandler
    def_irq_handler    TPM3_IRQHandler
    def_irq_handler    TPM4_IRQHandler
    def_irq_handler    Reserved116_IRQHandler
    def_irq_handler    MRT0_IRQHandler
    def_irq_handler    CAN0_DriverIRQHandler
    def_irq_handler    FLEXIO0_DriverIRQHandler
    def_irq_handler    LPI2C0_DriverIRQHandler
    def_irq_handler    LPI2C1_DriverIRQHandler
    def_irq_handler    LPI2C2_DriverIRQHandler
    def_irq_handler    LPI2C3_DriverIRQHandler
    def_irq_handler    LPSPI0_DriverIRQHandler
    def_irq_handler    LPSPI1_DriverIRQHandler
    def_irq_handler    LPSPI2_DriverIRQHandler
    def_irq_handler    LPSPI3_DriverIRQHandler
    def_irq_handler    LPUART0_DriverIRQHandler
    def_irq_handler    LPUART1_DriverIRQHandler
    def_irq_handler    LPUART2_DriverIRQHandler
    def_irq_handler    LPUART3_DriverIRQHandler
    def_irq_handler    USB0_IRQHandler
    def_irq_handler    USBPHY0_IRQHandler
    def_irq_handler    USB1_IRQHandler
    def_irq_handler    USBPHY1_IRQHandler
    def_irq_handler    PDM_EVENT_DriverIRQHandler
    def_irq_handler    PDM_HWVAD_EVENT_DriverIRQHandler
    def_irq_handler    SAI0_DriverIRQHandler
    def_irq_handler    SAI1_DriverIRQHandler
    def_irq_handler    SAI2_DriverIRQHandler
    def_irq_handler    SAI3_DriverIRQHandler
    def_irq_handler    SAI6_DriverIRQHandler
    def_irq_handler    SAI7_DriverIRQHandler
    def_irq_handler    SPDIF_DriverIRQHandler
    def_irq_handler    DCNano_IRQHandler
    def_irq_handler    DSI_IRQHandler
    def_irq_handler    GPU3D_IRQHandler
    def_irq_handler    GPU2D_IRQHandler
    def_irq_handler    GPIOA_INT0_IRQHandler
    def_irq_handler    GPIOA_INT1_IRQHandler
    def_irq_handler    GPIOB_INT0_IRQHandler
    def_irq_handler    GPIOB_INT1_IRQHandler
    def_irq_handler    GPIOC_INT0_IRQHandler
    def_irq_handler    GPIOC_INT1_IRQHandler
    def_irq_handler    GPIOD_INT0_IRQHandler
    def_irq_handler    GPIOD_INT1_IRQHandler
    def_irq_handler    GPIOE_INT0_IRQHandler
    def_irq_handler    GPIOE_INT1_IRQHandler
    def_irq_handler    GPIOF_INT0_IRQHandler
    def_irq_handler    GPIOF_INT1_IRQHandler
    def_irq_handler    Reserved161_IRQHandler
    def_irq_handler    Reserved162_IRQHandler
    def_irq_handler    Reserved163_IRQHandler
    def_irq_handler    Reserved164_IRQHandler
    def_irq_handler    Reserved165_IRQHandler
    def_irq_handler    Reserved166_IRQHandler
    def_irq_handler    ADC0_IRQHandler
    def_irq_handler    ADC1_IRQHandler
    def_irq_handler    CMP0_IRQHandler
    def_irq_handler    CMP1_IRQHandler
    def_irq_handler    DAC0_IRQHandler
    def_irq_handler    DAC1_IRQHandler
    def_irq_handler    FlexSPI0_DriverIRQHandler
    def_irq_handler    FlexSPI1_DriverIRQHandler
    def_irq_handler    FlexSPI2_DriverIRQHandler
    def_irq_handler    uSDHC0_DriverIRQHandler
    def_irq_handler    uSDHC1_DriverIRQHandler
    def_irq_handler    uSDHC2_DriverIRQHandler
    def_irq_handler    MDDR_IRQHandler
    def_irq_handler    FLEXIO1_DriverIRQHandler
    def_irq_handler    I3C0_DriverIRQHandler
    def_irq_handler    I3C1_DriverIRQHandler
    def_irq_handler    CASPER_IRQHandler
    def_irq_handler    PowerQuad_IRQHandler
    def_irq_handler    EPDC_IRQHandler
    def_irq_handler    PXP_IRQHandler
    def_irq_handler    CTI1_IRQHandler
    def_irq_handler    DMA1_DriverIRQHandler

    .end
