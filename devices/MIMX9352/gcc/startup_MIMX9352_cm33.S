/* ------------------------------------------------------------------------- */
/*  @file:    startup_MIMX9352_cm33.s                                        */
/*  @purpose: CMSIS Cortex-M33 Core Device Startup File                      */
/*            MIMX9352_cm33                                                  */
/*  @version: 1.0                                                            */
/*  @date:    2021-11-16                                                     */
/*  @build:   b220830                                                        */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright 1997-2016 Freescale Semiconductor, Inc.                         */
/* Copyright 2016-2022 NXP                                                   */
/* All rights reserved.                                                      */
/*                                                                           */
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
    .long   Reserved16_IRQHandler                           /* Exception condition notification while boot */
    .long   Reserved17_IRQHandler                           /* DAP interrupt */
    .long   Reserved18_IRQHandler                           /* Reserved interrupt */
    .long   Reserved19_IRQHandler                           /* CTI trigger outputs from CM33 platform */
    .long   Reserved20_IRQHandler                           /* CTI trigger outputs from CA55 platform */
    .long   Reserved21_IRQHandler                           /* Performance Unit Interrupts from CA55 platform */
    .long   Reserved22_IRQHandler                           /* ECC error from CA55 platform cache */
    .long   Reserved23_IRQHandler                           /* 1-bit or 2-bit ECC or Parity error from CA55 platform cache */
    .long   CAN1_IRQHandler                                 /* CAN1 interrupt*/
    .long   CAN1_ERROR_IRQHandler                           /* CAN1 error interrupt*/
    .long   Reserved26_IRQHandler                           /* General Purpose Input/Output 1 interrupt 0 */
    .long   Reserved27_IRQHandler                           /* General Purpose Input/Output 1 interrupt 1 */
    .long   I3C1_IRQHandler                                 /* Improved Inter-Integrated Circuit 1 interrupt */
    .long   LPI2C1_IRQHandler                               /* Low Power Inter-Integrated Circuit module 1 */
    .long   LPI2C2_IRQHandler                               /* Low Power Inter-Integrated Circuit module 2 */
    .long   LPIT1_IRQHandler                                /* Low Power Periodic Interrupt Timer 1 */
    .long   LPSPI1_IRQHandler                               /* Low Power Serial Peripheral Interface 1 */
    .long   LPSPI2_IRQHandler                               /* Low Power Serial Peripheral Interface 2 */
    .long   LPTMR1_IRQHandler                               /* Low Power Timer 1 */
    .long   LPUART1_IRQHandler                              /* Low Power UART 1 */
    .long   LPUART2_IRQHandler                              /* Low Power UART 2 */
    .long   MU1_A_IRQHandler                                /* Messaging Unit 1 - Side A (to communicate with M7 core) */
    .long   MU1_B_IRQHandler                                /* Messaging Unit 1 - Side B (to communicate with M33 core) */
    .long   MU2_A_IRQHandler                                /* Messaging Unit 2 - Side A (to communicate with M7 core) */
    .long   MU2_B_IRQHandler                                /* Messaging Unit 2 - Side B (to communicate with A55 core) */
    .long   Reserved41_IRQHandler                           /* Reserved interrupt */
    .long   Reserved42_IRQHandler                           /* Reserved interrupt */
    .long   Reserved43_IRQHandler                           /* Reserved interrupt */
    .long   Reserved44_IRQHandler                           /* Edgelock Trust MUA RX full interrupt */
    .long   Reserved45_IRQHandler                           /* Edgelock Trust MUA TX empty interrupt */
    .long   Reserved46_IRQHandler                           /* Edgelock Apps Core MUA RX full interrupt */
    .long   Reserved47_IRQHandler                           /* Edgelock Apps Core MUA TX empty interrupt */
    .long   Reserved48_IRQHandler                           /* Edgelock Realtime Core MUA RX full interrupt */
    .long   Reserved49_IRQHandler                           /* Edgelock Realtime Core MUA TX empty interrupt */
    .long   Reserved50_IRQHandler                           /* Edgelock secure interrupt */
    .long   Reserved51_IRQHandler                           /* Edgelock non-secure interrupt */
    .long   TPM1_IRQHandler                                 /* Timer PWM module 1 */
    .long   TPM2_IRQHandler                                 /* Timer PWM module 2 */
    .long   WDOG1_IRQHandler                                /* Watchdog 1 Interrupt */
    .long   WDOG2_IRQHandler                                /* Watchdog 2 Interrupt */
    .long   TRDC_IRQHandler                                 /* AONMIX TRDC transfer error interrupt */
    .long   Reserved57_IRQHandler                           /* Reserved interrupt */
    .long   Reserved58_IRQHandler                           /* Reserved interrupt */
    .long   Reserved59_IRQHandler                           /* Reserved interrupt */
    .long   Reserved60_IRQHandler                           /* Reserved interrupt */
    .long   SAI1_IRQHandler                                 /* Serial Audio Interface 1 */
    .long   Reserved62_IRQHandler                           /* M33 PS Tag/Data Parity Error */
    .long   Reserved63_IRQHandler                           /* M33 TCM ECC interrupt */
    .long   Reserved64_IRQHandler                           /* M33 TCM Error interrupt */
    .long   Reserved65_IRQHandler                           /* Reserved interrupt */
    .long   Reserved66_IRQHandler                           /* Reserved interrupt */
    .long   CAN2_IRQHandler                                 /* CAN2 interrupt*/
    .long   CAN2_ERROR_IRQHandler                           /* CAN2 error interrupt*/
    .long   FLEXIO1_IRQHandler                              /* Flexible IO 1 interrupt */
    .long   FLEXIO2_IRQHandler                              /* Flexible IO 2 interrupt */
    .long   FlexSPI1_IRQHandler                             /* FlexSPI controller interface interrupt 1 */
    .long   Reserved72_IRQHandler                           /* Reserved interrupt */
    .long   Reserved73_IRQHandler                           /* General Purpose Input/Output 2 interrupt 0 */
    .long   Reserved74_IRQHandler                           /* General Purpose Input/Output 2 interrupt 1 */
    .long   Reserved75_IRQHandler                           /* General Purpose Input/Output 3 interrupt 0 */
    .long   Reserved76_IRQHandler                           /* General Purpose Input/Output 3 interrupt 1 */
    .long   I3C2_IRQHandler                                 /* Improved Inter-Integrated Circuit 2 interrupt */
    .long   LPI2C3_IRQHandler                               /* Low Power Inter-Integrated Circuit module 3 */
    .long   LPI2C4_IRQHandler                               /* Low Power Inter-Integrated Circuit module 4 */
    .long   LPIT2_IRQHandler                                /* Low Power Periodic Interrupt Timer 2 */
    .long   LPSPI3_IRQHandler                               /* Low Power Serial Peripheral Interface 3 */
    .long   LPSPI4_IRQHandler                               /* Low Power Serial Peripheral Interface 4 */
    .long   LPTMR2_IRQHandler                               /* Low Power Timer 2 */
    .long   LPUART3_IRQHandler                              /* Low Power UART 3 */
    .long   LPUART4_IRQHandler                              /* Low Power UART 4 */
    .long   LPUART5_IRQHandler                              /* Low Power UART 5 */
    .long   LPUART6_IRQHandler                              /* Low Power UART 6 */
    .long   Reserved88_IRQHandler                           /* MTR Master error interrupt */
    .long   Reserved89_IRQHandler                           /* BBNSM Non-Secure interrupt */
    .long   Reserved90_IRQHandler                           /* System Counter compare interrupt */
    .long   TPM3_IRQHandler                                 /* Timer PWM module 3 */
    .long   TPM4_IRQHandler                                 /* Timer PWM module 4 */
    .long   TPM5_IRQHandler                                 /* Timer PWM module 5 */
    .long   TPM6_IRQHandler                                 /* Timer PWM module 6 */
    .long   WDOG3_IRQHandler                                /* Watchdog 3 Interrupt */
    .long   WDOG4_IRQHandler                                /* Watchdog 4 Interrupt */
    .long   WDOG5_IRQHandler                                /* Watchdog 5 Interrupt */
    .long   Reserved98_IRQHandler                           /* WAKEUPMIX TRDC transfer error interrupt */
    .long   Reserved99_IRQHandler                           /* TempSensor interrupt */
    .long   Reserved100_IRQHandler                          /* Reserved interrupt */
    .long   Reserved101_IRQHandler                          /* Reserved interrupt */
    .long   uSDHC1_IRQHandler                               /* ultra Secure Digital Host Controller interrupt 1 */
    .long   uSDHC2_IRQHandler                               /* ultra Secure Digital Host Controller interrupt 2 */
    .long   Reserved104_IRQHandler                          /* MEGAMIX TRDC transfer error interrupt */
    .long   Reserved105_IRQHandler                          /* NIC_WRAPPER TRDC transfer error interrupt */
    .long   Reserved106_IRQHandler                          /* DRAM controller Performance Monitor Interrupt */
    .long   Reserved107_IRQHandler                          /* DRAM controller Critical Interrupt */
    .long   Reserved108_IRQHandler                          /* DRAM Phy Critical Interrupt */
    .long   Reserved109_IRQHandler                          /* Reserved interrupt */
    .long   DMA3_ERROR_IRQHandler                           /* eDMA0 error interrupt */
    .long   DMA3_0_IRQHandler                               /* eDMA0 Channel 0 interrupt */
    .long   DMA3_1_IRQHandler                               /* eDMA0 Channel 1 interrupt */
    .long   DMA3_2_IRQHandler                               /* eDMA0 Channel 2 interrupt */
    .long   DMA3_3_IRQHandler                               /* eDMA0 Channel 3 interrupt */
    .long   DMA3_4_IRQHandler                               /* eDMA0 Channel 4 interrupt */
    .long   DMA3_5_IRQHandler                               /* eDMA0 Channel 5 interrupt */
    .long   DMA3_6_IRQHandler                               /* eDMA0 Channel 6 interrupt */
    .long   DMA3_7_IRQHandler                               /* eDMA0 Channel 7 interrupt */
    .long   DMA3_8_IRQHandler                               /* eDMA0 Channel 8 interrupt */
    .long   DMA3_9_IRQHandler                               /* eDMA0 Channel 9 interrupt */
    .long   DMA3_10_IRQHandler                              /* eDMA0 Channel 10 interrupt */
    .long   DMA3_11_IRQHandler                              /* eDMA0 Channel 11 interrupt */
    .long   DMA3_12_IRQHandler                              /* eDMA0 Channel 12 interrupt */
    .long   DMA3_13_IRQHandler                              /* eDMA0 Channel 13 interrupt */
    .long   DMA3_14_IRQHandler                              /* eDMA0 Channel 14 interrupt */
    .long   DMA3_15_IRQHandler                              /* eDMA0 Channel 15 interrupt */
    .long   DMA3_16_IRQHandler                              /* eDMA0 Channel 16 interrupt */
    .long   DMA3_17_IRQHandler                              /* eDMA0 Channel 17 interrupt */
    .long   DMA3_18_IRQHandler                              /* eDMA0 Channel 18 interrupt */
    .long   DMA3_19_IRQHandler                              /* eDMA0 Channel 19 interrupt */
    .long   DMA3_20_IRQHandler                              /* eDMA0 Channel 20 interrupt */
    .long   DMA3_21_IRQHandler                              /* eDMA0 Channel 21 interrupt */
    .long   DMA3_22_IRQHandler                              /* eDMA0 Channel 22 interrupt */
    .long   DMA3_23_IRQHandler                              /* eDMA0 Channel 23 interrupt */
    .long   DMA3_24_IRQHandler                              /* eDMA0 Channel 24 interrupt */
    .long   DMA3_25_IRQHandler                              /* eDMA0 Channel 25 interrupt */
    .long   DMA3_26_IRQHandler                              /* eDMA0 Channel 26 interrupt */
    .long   DMA3_27_IRQHandler                              /* eDMA0 Channel 27 interrupt */
    .long   DMA3_28_IRQHandler                              /* eDMA0 Channel 28 interrupt */
    .long   DMA3_29_IRQHandler                              /* eDMA0 Channel 29 interrupt */
    .long   DMA3_30_IRQHandler                              /* eDMA0 Channel 30 interrupt */
    .long   Reserved142_IRQHandler                          /* Reserved interrupt */
    .long   DMA4_ERROR_IRQHandler                           /* eDMA2 error interrupt */
    .long   DMA4_0_1_IRQHandler                             /* eDMA2 channel 0/1 interrupt */
    .long   DMA4_2_3_IRQHandler                             /* eDMA2 channel 2/3 interrupt */
    .long   DMA4_4_5_IRQHandler                             /* eDMA2 channel 4/5 interrupt */
    .long   DMA4_6_7_IRQHandler                             /* eDMA2 channel 6/7 interrupt */
    .long   DMA4_8_9_IRQHandler                             /* eDMA2 channel 8/9 interrupt */
    .long   DMA4_10_11_IRQHandler                           /* eDMA2 channel 10/11 interrupt */
    .long   DMA4_12_13_IRQHandler                           /* eDMA2 channel 12/13 interrupt */
    .long   DMA4_14_15_IRQHandler                           /* eDMA2 channel 14/15 interrupt */
    .long   DMA4_16_17_IRQHandler                           /* eDMA2 channel 16/17 interrupt */
    .long   DMA4_18_19_IRQHandler                           /* eDMA2 channel 18/19 interrupt */
    .long   DMA4_20_21_IRQHandler                           /* eDMA2 channel 20/21 interrupt */
    .long   DMA4_22_23_IRQHandler                           /* eDMA2 channel 22/23 interrupt */
    .long   DMA4_24_25_IRQHandler                           /* eDMA2 channel 24/25 interrupt */
    .long   DMA4_26_27_IRQHandler                           /* eDMA2 channel 26/27 interrupt */
    .long   DMA4_28_29_IRQHandler                           /* eDMA2 channel 28/29 interrupt */
    .long   DMA4_30_31_IRQHandler                           /* eDMA2 channel 30/31 interrupt */
    .long   DMA4_32_33_IRQHandler                           /* eDMA2 channel 32/33 interrupt */
    .long   DMA4_34_35_IRQHandler                           /* eDMA2 channel 34/35 interrupt */
    .long   DMA4_36_37_IRQHandler                           /* eDMA2 channel 36/37 interrupt */
    .long   DMA4_38_39_IRQHandler                           /* eDMA2 channel 38/39 interrupt */
    .long   DMA4_40_41_IRQHandler                           /* eDMA2 channel 40/41 interrupt */
    .long   DMA4_42_43_IRQHandler                           /* eDMA2 channel 42/43 interrupt */
    .long   DMA4_44_45_IRQHandler                           /* eDMA2 channel 44/45 interrupt */
    .long   DMA4_46_47_IRQHandler                           /* eDMA2 channel 46/47 interrupt */
    .long   DMA4_48_49_IRQHandler                           /* eDMA2 channel 48/49 interrupt */
    .long   DMA4_50_51_IRQHandler                           /* eDMA2 channel 50/51 interrupt */
    .long   DMA4_52_53_IRQHandler                           /* eDMA2 channel 52/53 interrupt */
    .long   DMA4_54_55_IRQHandler                           /* eDMA2 channel 54/55 interrupt */
    .long   DMA4_56_57_IRQHandler                           /* eDMA2 channel 56/57 interrupt */
    .long   DMA4_58_59_IRQHandler                           /* eDMA2 channel 58/59 interrupt */
    .long   DMA4_60_61_IRQHandler                           /* eDMA2 channel 60/61 interrupt */
    .long   DMA4_62_63_IRQHandler                           /* eDMA2 channel 62/63 interrupt */
    .long   Reserved176_IRQHandler                          /* Reserved interrupt */
    .long   Reserved177_IRQHandler                          /* Edgelock Group 1 reset source */
    .long   Reserved178_IRQHandler                          /* Edgelock Group 2 reset source */
    .long   Reserved179_IRQHandler                          /* Edgelock Group 2 reset source */
    .long   Reserved180_IRQHandler                          /* JTAGSW DAP MDM-AP SRC reset source */
    .long   Reserved181_IRQHandler                          /* JTAGC SRC reset source */
    .long   Reserved182_IRQHandler                          /* CM33 SYSREQRST SRC reset source */
    .long   Reserved183_IRQHandler                          /* CM33 LOCKUP SRC reset source */
    .long   Reserved184_IRQHandler                          /* Reserved interrupt */
    .long   Reserved185_IRQHandler                          /* Reserved interrupt */
    .long   SAI2_IRQHandler                                 /* Serial Audio Interface 2 */
    .long   SAI3_IRQHandler                                 /* Serial Audio Interface 3 */
    .long   ISI_IRQHandler                                  /* ISI interrupt */
    .long   Reserved189_IRQHandler                          /* PXP interrupt 0 */
    .long   Reserved190_IRQHandler                          /* PXP interrupt 1 */
    .long   CSI_IRQHandler                                  /* CSI interrupt */
    .long   Reserved192_IRQHandler                          /* LCDIF Sync Interrupt */
    .long   DSI_IRQHandler                                  /* MIPI DSI Interrupt Request */
    .long   Reserved194_IRQHandler                          /* Machine learning processor interrupt */
    .long   ENET_MAC0_Rx_Tx_Done1_IRQHandler                /* MAC 0 Receive / Trasmit Frame / Buffer Done*/
    .long   ENET_MAC0_Rx_Tx_Done2_IRQHandler                /* MAC 0 Receive / Trasmit Frame / Buffer Done*/
    .long   ENET_IRQHandler                                 /* MAC 0 IRQ*/
    .long   ENET_1588_IRQHandler                            /* MAC 0 1588 Timer Interrupt - synchronous*/
    .long   ENET_QOS_PMT_IRQHandler                         /* ENET QOS PMT interrupt */
    .long   ENET_QOS_IRQHandler                             /* ENET QOS interrupt */
    .long   Reserved201_IRQHandler                          /* Reserved interrupt */
    .long   Reserved202_IRQHandler                          /* Reserved interrupt */
    .long   Reserved203_IRQHandler                          /* USB-1 Wake-up Interrupt */
    .long   Reserved204_IRQHandler                          /* USB-2 Wake-up Interrupt */
    .long   Reserved205_IRQHandler                          /* General Purpose Input/Output 4 interrupt 0 */
    .long   Reserved206_IRQHandler                          /* General Purpose Input/Output 4 interrupt 1 */
    .long   LPSPI5_IRQHandler                               /* Low Power Serial Peripheral Interface 5 */
    .long   LPSPI6_IRQHandler                               /* Low Power Serial Peripheral Interface 6 */
    .long   LPSPI7_IRQHandler                               /* Low Power Serial Peripheral Interface 7 */
    .long   LPSPI8_IRQHandler                               /* Low Power Serial Peripheral Interface 8 */
    .long   LPI2C5_IRQHandler                               /* Low Power Inter-Integrated Circuit module 5 */
    .long   LPI2C6_IRQHandler                               /* Low Power Inter-Integrated Circuit module 6 */
    .long   LPI2C7_IRQHandler                               /* Low Power Inter-Integrated Circuit module 7 */
    .long   LPI2C8_IRQHandler                               /* Low Power Inter-Integrated Circuit module 8 */
    .long   PDM_HWVAD_ERROR_IRQHandler                      /* PDM interrupt */
    .long   PDM_HWVAD_EVENT_IRQHandler                      /* PDM interrupt */
    .long   PDM_ERROR_IRQHandler                            /* PDM interrupt */
    .long   PDM_EVENT_IRQHandler                            /* PDM interrupt */
    .long   Reserved219_IRQHandler                          /* AUDIO XCVR interrupt */
    .long   Reserved220_IRQHandler                          /* AUDIO XCVR interrupt */
    .long   uSDHC3_IRQHandler                               /* ultra Secure Digital Host Controller interrupt 3 */
    .long   Reserved222_IRQHandler                          /* OCRAM MECC interrupt */
    .long   Reserved223_IRQHandler                          /* OCRAM MECC interrupt */
    .long   Reserved224_IRQHandler                          /* HSIOMIX TRDC transfer error interrupt */
    .long   Reserved225_IRQHandler                          /* MEDIAMIX TRDC transfer error interrupt */
    .long   LPUART7_IRQHandler                              /* Low Power UART 7 */
    .long   LPUART8_IRQHandler                              /* Low Power UART 8 */
    .long   Reserved228_IRQHandler                          /* CM33 MCM interrupt */
    .long   Reserved229_IRQHandler                          /* SFA interrupt */
    .long   Reserved230_IRQHandler                          /* GIC600 INTERRUPT */
    .long   Reserved231_IRQHandler                          /* GIC600 INTERRUPT */
    .long   Reserved232_IRQHandler                          /* GIC600 INTERRUPT */
    .long   Reserved233_IRQHandler                          /* ADC interrupt */
    .long   Reserved234_IRQHandler                          /* ADC interrupt */
    .long   Reserved235_IRQHandler                          /* ADC interrupt */
    .long   Reserved236_IRQHandler                          /* Reserved interrupt */
    .long   Reserved237_IRQHandler                          /* I3C1 wakeup irq after double sync */
    .long   Reserved238_IRQHandler                          /* I3C2 wakeup irq after double sync */
    .long   Reserved239_IRQHandler                          /* Reserved interrupt */
    .long   Reserved240_IRQHandler                          /* Reserved interrupt */
    .long   Reserved241_IRQHandler                          /* Reserved interrupt */
    .long   Reserved242_IRQHandler                          /* Reserved interrupt */
    .long   Reserved243_IRQHandler                          /* Reserved interrupt */
    .long   Reserved244_IRQHandler                          /* Reserved interrupt */
    .long   Reserved245_IRQHandler                          /* Reserved interrupt */
    .long   Reserved246_IRQHandler                          /* Reserved interrupt */
    .long   Reserved247_IRQHandler                          /* Reserved interrupt */
    .long   Reserved248_IRQHandler                          /* Reserved interrupt */
    .long   Reserved249_IRQHandler                          /* Reserved interrupt */
    .long   Reserved250_IRQHandler                          /* Reserved interrupt */
    .long   Reserved251_IRQHandler                          /* Reserved interrupt */
    .long   Reserved252_IRQHandler                          /* Reserved interrupt */
    .long   Reserved253_IRQHandler                          /* Reserved interrupt */
    .long   Reserved254_IRQHandler                          /* Reserved interrupt */
    .long   Reserved255_IRQHandler                          /* Reserved interrupt */
    .long   Reserved256_IRQHandler                          /* Reserved interrupt */
    .long   Reserved257_IRQHandler                          /* Reserved interrupt */
    .long   Reserved258_IRQHandler                          /* Reserved interrupt */
    .long   Reserved259_IRQHandler                          /* Reserved interrupt */
    .long   Reserved260_IRQHandler                          /* Reserved interrupt */
    .long   Reserved261_IRQHandler                          /* Reserved interrupt */
    .long   Reserved262_IRQHandler                          /* Reserved interrupt */
    .long   Reserved263_IRQHandler                          /* Reserved interrupt */
    .long   Reserved264_IRQHandler                          /* Reserved interrupt */
    .long   Reserved265_IRQHandler                          /* Reserved interrupt */
    .long   Reserved266_IRQHandler                          /* Reserved interrupt */
    .long   Reserved267_IRQHandler                          /* Reserved interrupt */
    .long   Reserved268_IRQHandler                          /* Reserved interrupt */
    .long   Reserved269_IRQHandler                          /* Reserved interrupt */
    .long   Reserved270_IRQHandler                          /* Reserved interrupt */
    .long   Reserved271_IRQHandler                          /* Reserved interrupt */
    .long   Reserved272_IRQHandler                          /* Reserved interrupt */
    .long   Reserved273_IRQHandler                          /* Reserved interrupt */
    .long   Reserved274_IRQHandler                          /* Reserved interrupt */
    .long   Reserved275_IRQHandler                          /* Reserved interrupt */
    .long   Reserved276_IRQHandler                          /* Reserved interrupt */
    .long   Reserved277_IRQHandler                          /* Reserved interrupt */
    .long   Reserved278_IRQHandler                          /* Reserved interrupt */
    .long   Reserved279_IRQHandler                          /* Reserved interrupt */
    .long   Reserved280_IRQHandler                          /* Reserved interrupt */
    .long   Reserved281_IRQHandler                          /* Reserved interrupt */
    .long   Reserved282_IRQHandler                          /* Reserved interrupt */
    .long   Reserved283_IRQHandler                          /* Reserved interrupt */
    .long   Reserved284_IRQHandler                          /* ADC Asynchronous Interrupt */

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

/* Add stack / heap initializaiton */
    movs    r0, 0
    ldr     r1, =__HeapBase
    ldr     r2, =__HeapLimit
.LC3:
    cmp     r1, r2
    itt     lt
    strlt   r0, [r1], #4
    blt     .LC3

    ldr     r1, =__StackLimit
    ldr     r2, =__StackTop
.LC4:
    cmp     r1, r2
    itt     lt
    strlt   r0, [r1], #4
    blt     .LC4
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
    .weak FlexCAN_IRQHandler
    .type FlexCAN_IRQHandler, %function

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
    mov   r0, #0
    ldr   r1,=DMA3_DriverIRQHandler
    bx    r1
    .size DMA3_ERROR_IRQHandler, . - DMA3_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_0_IRQHandler
    .type DMA3_0_IRQHandler, %function
DMA3_0_IRQHandler:
    mov   r0, #0
    mov   r1, #0
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_0_IRQHandler, . - DMA3_0_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_1_IRQHandler
    .type DMA3_1_IRQHandler, %function
DMA3_1_IRQHandler:
    mov   r0, #0
    mov   r1, #1
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_1_IRQHandler, . - DMA3_1_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_2_IRQHandler
    .type DMA3_2_IRQHandler, %function
DMA3_2_IRQHandler:
    mov   r0, #0
    mov   r1, #2
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_2_IRQHandler, . - DMA3_2_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_3_IRQHandler
    .type DMA3_3_IRQHandler, %function
DMA3_3_IRQHandler:
    mov   r0, #0
    mov   r1, #3
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_3_IRQHandler, . - DMA3_3_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_4_IRQHandler
    .type DMA3_4_IRQHandler, %function
DMA3_4_IRQHandler:
    mov   r0, #0
    mov   r1, #4
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_4_IRQHandler, . - DMA3_4_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_5_IRQHandler
    .type DMA3_5_IRQHandler, %function
DMA3_5_IRQHandler:
    mov   r0, #0
    mov   r1, #5
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_5_IRQHandler, . - DMA3_5_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_6_IRQHandler
    .type DMA3_6_IRQHandler, %function
DMA3_6_IRQHandler:
    mov   r0, #0
    mov   r1, #6
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_6_IRQHandler, . - DMA3_6_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_7_IRQHandler
    .type DMA3_7_IRQHandler, %function
DMA3_7_IRQHandler:
    mov   r0, #0
    mov   r1, #7
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_7_IRQHandler, . - DMA3_7_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_8_IRQHandler
    .type DMA3_8_IRQHandler, %function
DMA3_8_IRQHandler:
    mov   r0, #0
    mov   r1, #8
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_8_IRQHandler, . - DMA3_8_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_9_IRQHandler
    .type DMA3_9_IRQHandler, %function
DMA3_9_IRQHandler:
    mov   r0, #0
    mov   r1, #9
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_9_IRQHandler, . - DMA3_9_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_10_IRQHandler
    .type DMA3_10_IRQHandler, %function
DMA3_10_IRQHandler:
    mov   r0, #0
    mov   r1, #10
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_10_IRQHandler, . - DMA3_10_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_11_IRQHandler
    .type DMA3_11_IRQHandler, %function
DMA3_11_IRQHandler:
    mov   r0, #0
    mov   r1, #11
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_11_IRQHandler, . - DMA3_11_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_12_IRQHandler
    .type DMA3_12_IRQHandler, %function
DMA3_12_IRQHandler:
    mov   r0, #0
    mov   r1, #12
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_12_IRQHandler, . - DMA3_12_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_13_IRQHandler
    .type DMA3_13_IRQHandler, %function
DMA3_13_IRQHandler:
    mov   r0, #0
    mov   r1, #13
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_13_IRQHandler, . - DMA3_13_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_14_IRQHandler
    .type DMA3_14_IRQHandler, %function
DMA3_14_IRQHandler:
    mov   r0, #0
    mov   r1, #14
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_14_IRQHandler, . - DMA3_14_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_15_IRQHandler
    .type DMA3_15_IRQHandler, %function
DMA3_15_IRQHandler:
    mov   r0, #0
    mov   r1, #15
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_15_IRQHandler, . - DMA3_15_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_16_IRQHandler
    .type DMA3_16_IRQHandler, %function
DMA3_16_IRQHandler:
    mov   r0, #0
    mov   r1, #16
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_16_IRQHandler, . - DMA3_16_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_17_IRQHandler
    .type DMA3_17_IRQHandler, %function
DMA3_17_IRQHandler:
    mov   r0, #0
    mov   r1, #17
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_17_IRQHandler, . - DMA3_17_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_18_IRQHandler
    .type DMA3_18_IRQHandler, %function
DMA3_18_IRQHandler:
    mov   r0, #0
    mov   r1, #18
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_18_IRQHandler, . - DMA3_18_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_19_IRQHandler
    .type DMA3_19_IRQHandler, %function
DMA3_19_IRQHandler:
    mov   r0, #0
    mov   r1, #19
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_19_IRQHandler, . - DMA3_19_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_20_IRQHandler
    .type DMA3_20_IRQHandler, %function
DMA3_20_IRQHandler:
    mov   r0, #0
    mov   r1, #20
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_20_IRQHandler, . - DMA3_20_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_21_IRQHandler
    .type DMA3_21_IRQHandler, %function
DMA3_21_IRQHandler:
    mov   r0, #0
    mov   r1, #21
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_21_IRQHandler, . - DMA3_21_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_22_IRQHandler
    .type DMA3_22_IRQHandler, %function
DMA3_22_IRQHandler:
    mov   r0, #0
    mov   r1, #22
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_22_IRQHandler, . - DMA3_22_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_23_IRQHandler
    .type DMA3_23_IRQHandler, %function
DMA3_23_IRQHandler:
    mov   r0, #0
    mov   r1, #23
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_23_IRQHandler, . - DMA3_23_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_24_IRQHandler
    .type DMA3_24_IRQHandler, %function
DMA3_24_IRQHandler:
    mov   r0, #0
    mov   r1, #24
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_24_IRQHandler, . - DMA3_24_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_25_IRQHandler
    .type DMA3_25_IRQHandler, %function
DMA3_25_IRQHandler:
    mov   r0, #0
    mov   r1, #25
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_25_IRQHandler, . - DMA3_25_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_26_IRQHandler
    .type DMA3_26_IRQHandler, %function
DMA3_26_IRQHandler:
    mov   r0, #0
    mov   r1, #26
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_26_IRQHandler, . - DMA3_26_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_27_IRQHandler
    .type DMA3_27_IRQHandler, %function
DMA3_27_IRQHandler:
    mov   r0, #0
    mov   r1, #27
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_27_IRQHandler, . - DMA3_27_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_28_IRQHandler
    .type DMA3_28_IRQHandler, %function
DMA3_28_IRQHandler:
    mov   r0, #0
    mov   r1, #28
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_28_IRQHandler, . - DMA3_28_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_29_IRQHandler
    .type DMA3_29_IRQHandler, %function
DMA3_29_IRQHandler:
    mov   r0, #0
    mov   r1, #29
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_29_IRQHandler, . - DMA3_29_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_30_IRQHandler
    .type DMA3_30_IRQHandler, %function
DMA3_30_IRQHandler:
    mov   r0, #0
    mov   r1, #30
    ldr   r2,=DMA3_DriverIRQHandler
    bx    r2
    .size DMA3_30_IRQHandler, . - DMA3_30_IRQHandler

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
    .weak DMA4_0_1_IRQHandler
    .type DMA4_0_1_IRQHandler, %function
DMA4_0_1_IRQHandler:
    ldr   r0,=DMA4_0_1_DriverIRQHandler
    bx    r0
    .size DMA4_0_1_IRQHandler, . - DMA4_0_1_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_2_3_IRQHandler
    .type DMA4_2_3_IRQHandler, %function
DMA4_2_3_IRQHandler:
    ldr   r0,=DMA4_2_3_DriverIRQHandler
    bx    r0
    .size DMA4_2_3_IRQHandler, . - DMA4_2_3_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_4_5_IRQHandler
    .type DMA4_4_5_IRQHandler, %function
DMA4_4_5_IRQHandler:
    ldr   r0,=DMA4_4_5_DriverIRQHandler
    bx    r0
    .size DMA4_4_5_IRQHandler, . - DMA4_4_5_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_6_7_IRQHandler
    .type DMA4_6_7_IRQHandler, %function
DMA4_6_7_IRQHandler:
    ldr   r0,=DMA4_6_7_DriverIRQHandler
    bx    r0
    .size DMA4_6_7_IRQHandler, . - DMA4_6_7_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_8_9_IRQHandler
    .type DMA4_8_9_IRQHandler, %function
DMA4_8_9_IRQHandler:
    ldr   r0,=DMA4_8_9_DriverIRQHandler
    bx    r0
    .size DMA4_8_9_IRQHandler, . - DMA4_8_9_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_10_11_IRQHandler
    .type DMA4_10_11_IRQHandler, %function
DMA4_10_11_IRQHandler:
    ldr   r0,=DMA4_10_11_DriverIRQHandler
    bx    r0
    .size DMA4_10_11_IRQHandler, . - DMA4_10_11_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_12_13_IRQHandler
    .type DMA4_12_13_IRQHandler, %function
DMA4_12_13_IRQHandler:
    ldr   r0,=DMA4_12_13_DriverIRQHandler
    bx    r0
    .size DMA4_12_13_IRQHandler, . - DMA4_12_13_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_14_15_IRQHandler
    .type DMA4_14_15_IRQHandler, %function
DMA4_14_15_IRQHandler:
    ldr   r0,=DMA4_14_15_DriverIRQHandler
    bx    r0
    .size DMA4_14_15_IRQHandler, . - DMA4_14_15_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_16_17_IRQHandler
    .type DMA4_16_17_IRQHandler, %function
DMA4_16_17_IRQHandler:
    ldr   r0,=DMA4_16_17_DriverIRQHandler
    bx    r0
    .size DMA4_16_17_IRQHandler, . - DMA4_16_17_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_18_19_IRQHandler
    .type DMA4_18_19_IRQHandler, %function
DMA4_18_19_IRQHandler:
    ldr   r0,=DMA4_18_19_DriverIRQHandler
    bx    r0
    .size DMA4_18_19_IRQHandler, . - DMA4_18_19_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_20_21_IRQHandler
    .type DMA4_20_21_IRQHandler, %function
DMA4_20_21_IRQHandler:
    ldr   r0,=DMA4_20_21_DriverIRQHandler
    bx    r0
    .size DMA4_20_21_IRQHandler, . - DMA4_20_21_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_22_23_IRQHandler
    .type DMA4_22_23_IRQHandler, %function
DMA4_22_23_IRQHandler:
    ldr   r0,=DMA4_22_23_DriverIRQHandler
    bx    r0
    .size DMA4_22_23_IRQHandler, . - DMA4_22_23_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_24_25_IRQHandler
    .type DMA4_24_25_IRQHandler, %function
DMA4_24_25_IRQHandler:
    ldr   r0,=DMA4_24_25_DriverIRQHandler
    bx    r0
    .size DMA4_24_25_IRQHandler, . - DMA4_24_25_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_26_27_IRQHandler
    .type DMA4_26_27_IRQHandler, %function
DMA4_26_27_IRQHandler:
    ldr   r0,=DMA4_26_27_DriverIRQHandler
    bx    r0
    .size DMA4_26_27_IRQHandler, . - DMA4_26_27_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_28_29_IRQHandler
    .type DMA4_28_29_IRQHandler, %function
DMA4_28_29_IRQHandler:
    ldr   r0,=DMA4_28_29_DriverIRQHandler
    bx    r0
    .size DMA4_28_29_IRQHandler, . - DMA4_28_29_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_30_31_IRQHandler
    .type DMA4_30_31_IRQHandler, %function
DMA4_30_31_IRQHandler:
    ldr   r0,=DMA4_30_31_DriverIRQHandler
    bx    r0
    .size DMA4_30_31_IRQHandler, . - DMA4_30_31_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_32_33_IRQHandler
    .type DMA4_32_33_IRQHandler, %function
DMA4_32_33_IRQHandler:
    ldr   r0,=DMA4_32_33_DriverIRQHandler
    bx    r0
    .size DMA4_32_33_IRQHandler, . - DMA4_32_33_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_34_35_IRQHandler
    .type DMA4_34_35_IRQHandler, %function
DMA4_34_35_IRQHandler:
    ldr   r0,=DMA4_34_35_DriverIRQHandler
    bx    r0
    .size DMA4_34_35_IRQHandler, . - DMA4_34_35_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_36_37_IRQHandler
    .type DMA4_36_37_IRQHandler, %function
DMA4_36_37_IRQHandler:
    ldr   r0,=DMA4_36_37_DriverIRQHandler
    bx    r0
    .size DMA4_36_37_IRQHandler, . - DMA4_36_37_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_38_39_IRQHandler
    .type DMA4_38_39_IRQHandler, %function
DMA4_38_39_IRQHandler:
    ldr   r0,=DMA4_38_39_DriverIRQHandler
    bx    r0
    .size DMA4_38_39_IRQHandler, . - DMA4_38_39_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_40_41_IRQHandler
    .type DMA4_40_41_IRQHandler, %function
DMA4_40_41_IRQHandler:
    ldr   r0,=DMA4_40_41_DriverIRQHandler
    bx    r0
    .size DMA4_40_41_IRQHandler, . - DMA4_40_41_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_42_43_IRQHandler
    .type DMA4_42_43_IRQHandler, %function
DMA4_42_43_IRQHandler:
    ldr   r0,=DMA4_42_43_DriverIRQHandler
    bx    r0
    .size DMA4_42_43_IRQHandler, . - DMA4_42_43_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_44_45_IRQHandler
    .type DMA4_44_45_IRQHandler, %function
DMA4_44_45_IRQHandler:
    ldr   r0,=DMA4_44_45_DriverIRQHandler
    bx    r0
    .size DMA4_44_45_IRQHandler, . - DMA4_44_45_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_46_47_IRQHandler
    .type DMA4_46_47_IRQHandler, %function
DMA4_46_47_IRQHandler:
    ldr   r0,=DMA4_46_47_DriverIRQHandler
    bx    r0
    .size DMA4_46_47_IRQHandler, . - DMA4_46_47_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_48_49_IRQHandler
    .type DMA4_48_49_IRQHandler, %function
DMA4_48_49_IRQHandler:
    ldr   r0,=DMA4_48_49_DriverIRQHandler
    bx    r0
    .size DMA4_48_49_IRQHandler, . - DMA4_48_49_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_50_51_IRQHandler
    .type DMA4_50_51_IRQHandler, %function
DMA4_50_51_IRQHandler:
    ldr   r0,=DMA4_50_51_DriverIRQHandler
    bx    r0
    .size DMA4_50_51_IRQHandler, . - DMA4_50_51_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_52_53_IRQHandler
    .type DMA4_52_53_IRQHandler, %function
DMA4_52_53_IRQHandler:
    ldr   r0,=DMA4_52_53_DriverIRQHandler
    bx    r0
    .size DMA4_52_53_IRQHandler, . - DMA4_52_53_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_54_55_IRQHandler
    .type DMA4_54_55_IRQHandler, %function
DMA4_54_55_IRQHandler:
    ldr   r0,=DMA4_54_55_DriverIRQHandler
    bx    r0
    .size DMA4_54_55_IRQHandler, . - DMA4_54_55_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_56_57_IRQHandler
    .type DMA4_56_57_IRQHandler, %function
DMA4_56_57_IRQHandler:
    ldr   r0,=DMA4_56_57_DriverIRQHandler
    bx    r0
    .size DMA4_56_57_IRQHandler, . - DMA4_56_57_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_58_59_IRQHandler
    .type DMA4_58_59_IRQHandler, %function
DMA4_58_59_IRQHandler:
    ldr   r0,=DMA4_58_59_DriverIRQHandler
    bx    r0
    .size DMA4_58_59_IRQHandler, . - DMA4_58_59_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_60_61_IRQHandler
    .type DMA4_60_61_IRQHandler, %function
DMA4_60_61_IRQHandler:
    ldr   r0,=DMA4_60_61_DriverIRQHandler
    bx    r0
    .size DMA4_60_61_IRQHandler, . - DMA4_60_61_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_62_63_IRQHandler
    .type DMA4_62_63_IRQHandler, %function
DMA4_62_63_IRQHandler:
    ldr   r0,=DMA4_62_63_DriverIRQHandler
    bx    r0
    .size DMA4_62_63_IRQHandler, . - DMA4_62_63_IRQHandler

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
    .weak ENET_MAC0_Rx_Tx_Done1_IRQHandler
    .type ENET_MAC0_Rx_Tx_Done1_IRQHandler, %function
ENET_MAC0_Rx_Tx_Done1_IRQHandler:
    ldr   r0,=ENET_MAC0_Rx_Tx_Done1_DriverIRQHandler
    bx    r0
    .size ENET_MAC0_Rx_Tx_Done1_IRQHandler, . - ENET_MAC0_Rx_Tx_Done1_IRQHandler

    .align 1
    .thumb_func
    .weak ENET_MAC0_Rx_Tx_Done2_IRQHandler
    .type ENET_MAC0_Rx_Tx_Done2_IRQHandler, %function
ENET_MAC0_Rx_Tx_Done2_IRQHandler:
    ldr   r0,=ENET_MAC0_Rx_Tx_Done2_DriverIRQHandler
    bx    r0
    .size ENET_MAC0_Rx_Tx_Done2_IRQHandler, . - ENET_MAC0_Rx_Tx_Done2_IRQHandler

    .align 1
    .thumb_func
    .weak ENET_IRQHandler
    .type ENET_IRQHandler, %function
ENET_IRQHandler:
    ldr   r0,=ENET_DriverIRQHandler
    bx    r0
    .size ENET_IRQHandler, . - ENET_IRQHandler

    .align 1
    .thumb_func
    .weak ENET_1588_IRQHandler
    .type ENET_1588_IRQHandler, %function
ENET_1588_IRQHandler:
    ldr   r0,=ENET_1588_DriverIRQHandler
    bx    r0
    .size ENET_1588_IRQHandler, . - ENET_1588_IRQHandler

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
    .weak PDM_HWVAD_ERROR_IRQHandler
    .type PDM_HWVAD_ERROR_IRQHandler, %function
PDM_HWVAD_ERROR_IRQHandler:
    ldr   r0,=PDM_HWVAD_ERROR_DriverIRQHandler
    bx    r0
    .size PDM_HWVAD_ERROR_IRQHandler, . - PDM_HWVAD_ERROR_IRQHandler

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
    .weak PDM_ERROR_IRQHandler
    .type PDM_ERROR_IRQHandler, %function
PDM_ERROR_IRQHandler:
    ldr   r0,=PDM_ERROR_DriverIRQHandler
    bx    r0
    .size PDM_ERROR_IRQHandler, . - PDM_ERROR_IRQHandler

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
    def_irq_handler    MU1_A_IRQHandler
    def_irq_handler    MU1_B_IRQHandler
    def_irq_handler    MU2_A_IRQHandler
    def_irq_handler    MU2_B_IRQHandler
    def_irq_handler    Reserved41_IRQHandler
    def_irq_handler    Reserved42_IRQHandler
    def_irq_handler    Reserved43_IRQHandler
    def_irq_handler    Reserved44_IRQHandler
    def_irq_handler    Reserved45_IRQHandler
    def_irq_handler    Reserved46_IRQHandler
    def_irq_handler    Reserved47_IRQHandler
    def_irq_handler    Reserved48_IRQHandler
    def_irq_handler    Reserved49_IRQHandler
    def_irq_handler    Reserved50_IRQHandler
    def_irq_handler    Reserved51_IRQHandler
    def_irq_handler    TPM1_IRQHandler
    def_irq_handler    TPM2_IRQHandler
    def_irq_handler    WDOG1_IRQHandler
    def_irq_handler    WDOG2_IRQHandler
    def_irq_handler    TRDC_IRQHandler
    def_irq_handler    Reserved57_IRQHandler
    def_irq_handler    Reserved58_IRQHandler
    def_irq_handler    Reserved59_IRQHandler
    def_irq_handler    Reserved60_IRQHandler
    def_irq_handler    SAI1_DriverIRQHandler
    def_irq_handler    Reserved62_IRQHandler
    def_irq_handler    Reserved63_IRQHandler
    def_irq_handler    Reserved64_IRQHandler
    def_irq_handler    Reserved65_IRQHandler
    def_irq_handler    Reserved66_IRQHandler
    def_irq_handler    CAN2_DriverIRQHandler
    def_irq_handler    CAN2_ERROR_DriverIRQHandler
    def_irq_handler    FLEXIO1_DriverIRQHandler
    def_irq_handler    FLEXIO2_DriverIRQHandler
    def_irq_handler    FlexSPI1_DriverIRQHandler
    def_irq_handler    Reserved72_IRQHandler
    def_irq_handler    Reserved73_IRQHandler
    def_irq_handler    Reserved74_IRQHandler
    def_irq_handler    Reserved75_IRQHandler
    def_irq_handler    Reserved76_IRQHandler
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
    def_irq_handler    Reserved89_IRQHandler
    def_irq_handler    Reserved90_IRQHandler
    def_irq_handler    TPM3_IRQHandler
    def_irq_handler    TPM4_IRQHandler
    def_irq_handler    TPM5_IRQHandler
    def_irq_handler    TPM6_IRQHandler
    def_irq_handler    WDOG3_IRQHandler
    def_irq_handler    WDOG4_IRQHandler
    def_irq_handler    WDOG5_IRQHandler
    def_irq_handler    Reserved98_IRQHandler
    def_irq_handler    Reserved99_IRQHandler
    def_irq_handler    Reserved100_IRQHandler
    def_irq_handler    Reserved101_IRQHandler
    def_irq_handler    uSDHC1_DriverIRQHandler
    def_irq_handler    uSDHC2_DriverIRQHandler
    def_irq_handler    Reserved104_IRQHandler
    def_irq_handler    Reserved105_IRQHandler
    def_irq_handler    Reserved106_IRQHandler
    def_irq_handler    Reserved107_IRQHandler
    def_irq_handler    Reserved108_IRQHandler
    def_irq_handler    Reserved109_IRQHandler
    def_irq_handler    DMA3_DriverIRQHandler
    def_irq_handler    Reserved142_IRQHandler
    def_irq_handler    DMA4_ERROR_DriverIRQHandler
    def_irq_handler    DMA4_0_1_DriverIRQHandler
    def_irq_handler    DMA4_2_3_DriverIRQHandler
    def_irq_handler    DMA4_4_5_DriverIRQHandler
    def_irq_handler    DMA4_6_7_DriverIRQHandler
    def_irq_handler    DMA4_8_9_DriverIRQHandler
    def_irq_handler    DMA4_10_11_DriverIRQHandler
    def_irq_handler    DMA4_12_13_DriverIRQHandler
    def_irq_handler    DMA4_14_15_DriverIRQHandler
    def_irq_handler    DMA4_16_17_DriverIRQHandler
    def_irq_handler    DMA4_18_19_DriverIRQHandler
    def_irq_handler    DMA4_20_21_DriverIRQHandler
    def_irq_handler    DMA4_22_23_DriverIRQHandler
    def_irq_handler    DMA4_24_25_DriverIRQHandler
    def_irq_handler    DMA4_26_27_DriverIRQHandler
    def_irq_handler    DMA4_28_29_DriverIRQHandler
    def_irq_handler    DMA4_30_31_DriverIRQHandler
    def_irq_handler    DMA4_32_33_DriverIRQHandler
    def_irq_handler    DMA4_34_35_DriverIRQHandler
    def_irq_handler    DMA4_36_37_DriverIRQHandler
    def_irq_handler    DMA4_38_39_DriverIRQHandler
    def_irq_handler    DMA4_40_41_DriverIRQHandler
    def_irq_handler    DMA4_42_43_DriverIRQHandler
    def_irq_handler    DMA4_44_45_DriverIRQHandler
    def_irq_handler    DMA4_46_47_DriverIRQHandler
    def_irq_handler    DMA4_48_49_DriverIRQHandler
    def_irq_handler    DMA4_50_51_DriverIRQHandler
    def_irq_handler    DMA4_52_53_DriverIRQHandler
    def_irq_handler    DMA4_54_55_DriverIRQHandler
    def_irq_handler    DMA4_56_57_DriverIRQHandler
    def_irq_handler    DMA4_58_59_DriverIRQHandler
    def_irq_handler    DMA4_60_61_DriverIRQHandler
    def_irq_handler    DMA4_62_63_DriverIRQHandler
    def_irq_handler    Reserved176_IRQHandler
    def_irq_handler    Reserved177_IRQHandler
    def_irq_handler    Reserved178_IRQHandler
    def_irq_handler    Reserved179_IRQHandler
    def_irq_handler    Reserved180_IRQHandler
    def_irq_handler    Reserved181_IRQHandler
    def_irq_handler    Reserved182_IRQHandler
    def_irq_handler    Reserved183_IRQHandler
    def_irq_handler    Reserved184_IRQHandler
    def_irq_handler    Reserved185_IRQHandler
    def_irq_handler    SAI2_DriverIRQHandler
    def_irq_handler    SAI3_DriverIRQHandler
    def_irq_handler    ISI_IRQHandler
    def_irq_handler    Reserved189_IRQHandler
    def_irq_handler    Reserved190_IRQHandler
    def_irq_handler    CSI_IRQHandler
    def_irq_handler    Reserved192_IRQHandler
    def_irq_handler    DSI_IRQHandler
    def_irq_handler    Reserved194_IRQHandler
    def_irq_handler    ENET_MAC0_Rx_Tx_Done1_DriverIRQHandler
    def_irq_handler    ENET_MAC0_Rx_Tx_Done2_DriverIRQHandler
    def_irq_handler    ENET_DriverIRQHandler
    def_irq_handler    ENET_1588_DriverIRQHandler
    def_irq_handler    ENET_QOS_PMT_IRQHandler
    def_irq_handler    ENET_QOS_DriverIRQHandler
    def_irq_handler    Reserved201_IRQHandler
    def_irq_handler    Reserved202_IRQHandler
    def_irq_handler    Reserved203_IRQHandler
    def_irq_handler    Reserved204_IRQHandler
    def_irq_handler    Reserved205_IRQHandler
    def_irq_handler    Reserved206_IRQHandler
    def_irq_handler    LPSPI5_DriverIRQHandler
    def_irq_handler    LPSPI6_DriverIRQHandler
    def_irq_handler    LPSPI7_DriverIRQHandler
    def_irq_handler    LPSPI8_DriverIRQHandler
    def_irq_handler    LPI2C5_DriverIRQHandler
    def_irq_handler    LPI2C6_DriverIRQHandler
    def_irq_handler    LPI2C7_DriverIRQHandler
    def_irq_handler    LPI2C8_DriverIRQHandler
    def_irq_handler    PDM_HWVAD_ERROR_DriverIRQHandler
    def_irq_handler    PDM_HWVAD_EVENT_DriverIRQHandler
    def_irq_handler    PDM_ERROR_DriverIRQHandler
    def_irq_handler    PDM_EVENT_DriverIRQHandler
    def_irq_handler    Reserved219_IRQHandler
    def_irq_handler    Reserved220_IRQHandler
    def_irq_handler    uSDHC3_DriverIRQHandler
    def_irq_handler    Reserved222_IRQHandler
    def_irq_handler    Reserved223_IRQHandler
    def_irq_handler    Reserved224_IRQHandler
    def_irq_handler    Reserved225_IRQHandler
    def_irq_handler    LPUART7_DriverIRQHandler
    def_irq_handler    LPUART8_DriverIRQHandler
    def_irq_handler    Reserved228_IRQHandler
    def_irq_handler    Reserved229_IRQHandler
    def_irq_handler    Reserved230_IRQHandler
    def_irq_handler    Reserved231_IRQHandler
    def_irq_handler    Reserved232_IRQHandler
    def_irq_handler    Reserved233_IRQHandler
    def_irq_handler    Reserved234_IRQHandler
    def_irq_handler    Reserved235_IRQHandler
    def_irq_handler    Reserved236_IRQHandler
    def_irq_handler    Reserved237_IRQHandler
    def_irq_handler    Reserved238_IRQHandler
    def_irq_handler    Reserved239_IRQHandler
    def_irq_handler    Reserved240_IRQHandler
    def_irq_handler    Reserved241_IRQHandler
    def_irq_handler    Reserved242_IRQHandler
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
    def_irq_handler    Reserved275_IRQHandler
    def_irq_handler    Reserved276_IRQHandler
    def_irq_handler    Reserved277_IRQHandler
    def_irq_handler    Reserved278_IRQHandler
    def_irq_handler    Reserved279_IRQHandler
    def_irq_handler    Reserved280_IRQHandler
    def_irq_handler    Reserved281_IRQHandler
    def_irq_handler    Reserved282_IRQHandler
    def_irq_handler    Reserved283_IRQHandler
    def_irq_handler    Reserved284_IRQHandler

    .end
