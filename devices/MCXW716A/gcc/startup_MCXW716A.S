/* ------------------------------------------------------------------------- */
/*  @file:    startup_MCXW716A.s                                             */
/*  @purpose: CMSIS Cortex-M33 Core Device Startup File                      */
/*            MCXW716A                                                       */
/*  @version: 1.0                                                            */
/*  @date:    2024-3-21                                                      */
/*  @build:   b240527                                                        */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright 1997-2016 Freescale Semiconductor, Inc.                         */
/* Copyright 2016-2024 NXP                                                   */
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
    .long   CTI_IRQHandler                                  /* Cross Trigger Interface interrupt*/
    .long   CMC0_IRQHandler                                 /* Core Mode Controller interrupt*/
    .long   DMA0_CH0_IRQHandler                             /* eDMA channel 0 error or transfer complete*/
    .long   DMA0_CH1_IRQHandler                             /* eDMA channel 1 error or transfer complete*/
    .long   DMA0_CH2_IRQHandler                             /* eDMA channel 2 error or transfer complete*/
    .long   DMA0_CH3_IRQHandler                             /* eDMA channel 3 error or transfer complete*/
    .long   DMA0_CH4_IRQHandler                             /* eDMA channel 4 error or transfer complete*/
    .long   DMA0_CH5_IRQHandler                             /* eDMA channel 5 error or transfer complete*/
    .long   DMA0_CH6_IRQHandler                             /* eDMA channel 6 error or transfer complete*/
    .long   DMA0_CH7_IRQHandler                             /* eDMA channel 7 error or transfer complete*/
    .long   DMA0_CH8_IRQHandler                             /* eDMA channel 8 error or transfer complete*/
    .long   DMA0_CH9_IRQHandler                             /* eDMA channel 9 error or transfer complete*/
    .long   DMA0_CH10_IRQHandler                            /* eDMA channel 10 error or transfer complete*/
    .long   DMA0_CH11_IRQHandler                            /* eDMA channel 11 error or transfer complete*/
    .long   DMA0_CH12_IRQHandler                            /* eDMA channel 12 error or transfer complete*/
    .long   DMA0_CH13_IRQHandler                            /* eDMA channel 13 error or transfer complete*/
    .long   DMA0_CH14_IRQHandler                            /* eDMA channel 14 error or transfer complete*/
    .long   DMA0_CH15_IRQHandler                            /* eDMA channel 15 error or transfer complete*/
    .long   EWM0_IRQHandler                                 /* External Watchdog Monitor 0 interrupt*/
    .long   MCM0_IRQHandler                                 /* Miscellaneous Control Module interrupt*/
    .long   MSCM0_IRQHandler                                /* Miscellaneous System Control Module interrupt*/
    .long   SPC0_IRQHandler                                 /* System Power Controller 0 interrupt*/
    .long   WUU0_IRQHandler                                 /* Wake-Up Unit 0 interrupt*/
    .long   WDOG0_IRQHandler                                /* Watchdog Timer 0 interrupt*/
    .long   WDOG1_IRQHandler                                /* Watchdog Timer 1 interrupt*/
    .long   SCG0_IRQHandler                                 /* System Clock Generator 0 interrupt*/
    .long   SFA0_IRQHandler                                 /* Singal Frequency Analyzer 0 interrupt*/
    .long   FMU0_IRQHandler                                 /* Flash Memory Unit 0 interrupt*/
    .long   ELE_CMD_IRQHandler                              /* EdgeLock enclave command interface interrupt*/
    .long   ELE_SECURE_IRQHandler                           /* EdgeLock enclave interrupt*/
    .long   ELE_NONSECURE_IRQHandler                        /* EdgeLock enclave non-secure interrupt*/
    .long   TRDC0_IRQHandler                                /* Trusted Resource Domain Controller 0 interrupt*/
    .long   RTC_Alarm_IRQHandler                            /* Real Time Clock 0 alarm interrupt*/
    .long   RTC_Seconds_IRQHandler                          /* Real Time Clock 0 seconds interrupt*/
    .long   LPTMR0_IRQHandler                               /* Low-Power Timer0 interrupt*/
    .long   LPTMR1_IRQHandler                               /* Low-Power Timer1 interrupt*/
    .long   LPIT0_IRQHandler                                /* Low-Power Periodic Interrupt Timer 0 interrupt*/
    .long   TPM0_IRQHandler                                 /* Timer / PWM Module 0 interrupt*/
    .long   TPM1_IRQHandler                                 /* Timer / PWM Module 1 interrupt*/
    .long   LPI2C0_IRQHandler                               /* Low-Power Inter Integrated Circuit 0 interrupt*/
    .long   LPI2C1_IRQHandler                               /* Low-Power Inter Integrated Circuit 1 interrupt*/
    .long   I3C0_IRQHandler                                 /* Improved Inter-Integrated Circuit 0 interrupt*/
    .long   LPSPI0_IRQHandler                               /* Low-Power Serial Peripheral Interface 0 interrupt*/
    .long   LPSPI1_IRQHandler                               /* Low-Power Serial Peripheral Interface 1 interrupt*/
    .long   LPUART0_IRQHandler                              /* Low-Power Universal Asynchronous Receiver/Transmitter 0 interrupt*/
    .long   LPUART1_IRQHandler                              /* Low-Power Universal Asynchronous Receiver/Transmitter 1 interrupt*/
    .long   FLEXIO0_IRQHandler                              /* Flexible Input/Output 0 interrupt*/
    .long   Reserved63_IRQHandler                           /* Reserved interrupt*/
    .long   RF_IMU0_IRQHandler                              /* Radio IMU interrupt 0 (msg_rdy_imu)*/
    .long   RF_IMU1_IRQHandler                              /* Radio IMU interrupt 1(msg_space_avail_imu)*/
    .long   RF_NBU_IRQHandler                               /* Radio NBU timeout interrupt*/
    .long   RF_FMU_IRQHandler                               /* Radio FMU interrupt*/
    .long   RF_WOR_IRQHandler                               /* Radio WOR RX FAIL interrupt*/
    .long   RF_802_15_4_IRQHandler                          /* Radio Frequency 2.4GHz - 802.15.4 Link Layer interrupt*/
    .long   RF_Generic_IRQHandler                           /* Radio Frequency 2.4 GHz - Generic Link Layer interrupt*/
    .long   RF_BRIC_IRQHandler                              /* Radio Frequency 2.4 GHz - BRIC interrupt*/
    .long   RF_LANT_SW_IRQHandler                           /* Radio Transceiver - Radio LANT_SW interrupt*/
    .long   RFMC_IRQHandler                                 /* RFMC interrupt*/
    .long   DSB_IRQHandler                                  /* Data Stream Buffer interrupt*/
    .long   GPIOA_INT0_IRQHandler                           /* General Purpose Input/Output A interrupt 0*/
    .long   GPIOA_INT1_IRQHandler                           /* General Purpose Input/Output A interrupt 1*/
    .long   GPIOB_INT0_IRQHandler                           /* General Purpose Input/Output B interrupt 0*/
    .long   GPIOB_INT1_IRQHandler                           /* General Purpose Input/Output B interrupt 1*/
    .long   GPIOC_INT0_IRQHandler                           /* General Purpose Input/Output C interrupt 0*/
    .long   GPIOC_INT1_IRQHandler                           /* General Purpose Input/Output C interrupt 1*/
    .long   GPIOD_INT0_IRQHandler                           /* General Purpose Input/Output D interrupt 0*/
    .long   GPIOD_INT1_IRQHandler                           /* General Purpose Input/Output D interrupt 1*/
    .long   PORTA_EFT_IRQHandler                            /* PortA EFT interrupt*/
    .long   PORTB_EFT_IRQHandler                            /* PortB EFT interrupt*/
    .long   PORTC_EFT_IRQHandler                            /* PortC EFT interrupt*/
    .long   PORTD_EFT_IRQHandler                            /* PortD EFT interrupt*/
    .long   ADC0_IRQHandler                                 /* Analog-to-Digital Converter 0 interrupt*/
    .long   LPCMP0_IRQHandler                               /* Low-Power Comparator 0 interrupt*/
    .long   LPCMP1_IRQHandler                               /* Low-Power Comparator 1 interrupt*/
    .long   VBAT_IRQHandler                                 /* Smart Power Switch Domain interrupt*/
    .long   Reserved91_IRQHandler                           /* Reserved interrupt*/
    .long   DefaultISR                                      /* 92*/
    .long   DefaultISR                                      /* 93*/
    .long   DefaultISR                                      /* 94*/
    .long   DefaultISR                                      /* 95*/
    .long   DefaultISR                                      /* 96*/
    .long   DefaultISR                                      /* 97*/
    .long   DefaultISR                                      /* 98*/
    .long   DefaultISR                                      /* 99*/
    .long   DefaultISR                                      /* 100*/
    .long   DefaultISR                                      /* 101*/
    .long   DefaultISR                                      /* 102*/
    .long   DefaultISR                                      /* 103*/
    .long   DefaultISR                                      /* 104*/
    .long   DefaultISR                                      /* 105*/
    .long   DefaultISR                                      /* 106*/
    .long   DefaultISR                                      /* 107*/
    .long   DefaultISR                                      /* 108*/
    .long   DefaultISR                                      /* 109*/
    .long   DefaultISR                                      /* 110*/
    .long   DefaultISR                                      /* 111*/
    .long   DefaultISR                                      /* 112*/
    .long   DefaultISR                                      /* 113*/
    .long   DefaultISR                                      /* 114*/
    .long   DefaultISR                                      /* 115*/
    .long   DefaultISR                                      /* 116*/
    .long   DefaultISR                                      /* 117*/
    .long   DefaultISR                                      /* 118*/
    .long   DefaultISR                                      /* 119*/
    .long   DefaultISR                                      /* 120*/
    .long   DefaultISR                                      /* 121*/
    .long   DefaultISR                                      /* 122*/
    .long   DefaultISR                                      /* 123*/
    .long   DefaultISR                                      /* 124*/
    .long   DefaultISR                                      /* 125*/
    .long   DefaultISR                                      /* 126*/
    .long   DefaultISR                                      /* 127*/
    .long   DefaultISR                                      /* 128*/
    .long   DefaultISR                                      /* 129*/
    .long   DefaultISR                                      /* 130*/
    .long   DefaultISR                                      /* 131*/
    .long   DefaultISR                                      /* 132*/
    .long   DefaultISR                                      /* 133*/
    .long   DefaultISR                                      /* 134*/
    .long   DefaultISR                                      /* 135*/
    .long   DefaultISR                                      /* 136*/
    .long   DefaultISR                                      /* 137*/
    .long   DefaultISR                                      /* 138*/
    .long   DefaultISR                                      /* 139*/
    .long   DefaultISR                                      /* 140*/
    .long   DefaultISR                                      /* 141*/
    .long   DefaultISR                                      /* 142*/
    .long   DefaultISR                                      /* 143*/
    .long   DefaultISR                                      /* 144*/
    .long   DefaultISR                                      /* 145*/
    .long   DefaultISR                                      /* 146*/
    .long   DefaultISR                                      /* 147*/
    .long   DefaultISR                                      /* 148*/
    .long   DefaultISR                                      /* 149*/
    .long   DefaultISR                                      /* 150*/
    .long   DefaultISR                                      /* 151*/
    .long   DefaultISR                                      /* 152*/
    .long   DefaultISR                                      /* 153*/
    .long   DefaultISR                                      /* 154*/
    .long   DefaultISR                                      /* 155*/
    .long   DefaultISR                                      /* 156*/
    .long   DefaultISR                                      /* 157*/
    .long   DefaultISR                                      /* 158*/
    .long   DefaultISR                                      /* 159*/
    .long   DefaultISR                                      /* 160*/
    .long   DefaultISR                                      /* 161*/
    .long   DefaultISR                                      /* 162*/
    .long   DefaultISR                                      /* 163*/
    .long   DefaultISR                                      /* 164*/
    .long   DefaultISR                                      /* 165*/
    .long   DefaultISR                                      /* 166*/
    .long   DefaultISR                                      /* 167*/
    .long   DefaultISR                                      /* 168*/
    .long   DefaultISR                                      /* 169*/
    .long   DefaultISR                                      /* 170*/
    .long   DefaultISR                                      /* 171*/
    .long   DefaultISR                                      /* 172*/
    .long   DefaultISR                                      /* 173*/
    .long   DefaultISR                                      /* 174*/
    .long   DefaultISR                                      /* 175*/
    .long   DefaultISR                                      /* 176*/
    .long   DefaultISR                                      /* 177*/
    .long   DefaultISR                                      /* 178*/
    .long   DefaultISR                                      /* 179*/
    .long   DefaultISR                                      /* 180*/
    .long   DefaultISR                                      /* 181*/
    .long   DefaultISR                                      /* 182*/
    .long   DefaultISR                                      /* 183*/
    .long   DefaultISR                                      /* 184*/
    .long   DefaultISR                                      /* 185*/
    .long   DefaultISR                                      /* 186*/
    .long   DefaultISR                                      /* 187*/
    .long   DefaultISR                                      /* 188*/
    .long   DefaultISR                                      /* 189*/
    .long   DefaultISR                                      /* 190*/
    .long   DefaultISR                                      /* 191*/
    .long   DefaultISR                                      /* 192*/
    .long   DefaultISR                                      /* 193*/
    .long   DefaultISR                                      /* 194*/
    .long   DefaultISR                                      /* 195*/
    .long   DefaultISR                                      /* 196*/
    .long   DefaultISR                                      /* 197*/
    .long   DefaultISR                                      /* 198*/
    .long   DefaultISR                                      /* 199*/
    .long   DefaultISR                                      /* 200*/
    .long   DefaultISR                                      /* 201*/
    .long   DefaultISR                                      /* 202*/
    .long   DefaultISR                                      /* 203*/
    .long   DefaultISR                                      /* 204*/
    .long   DefaultISR                                      /* 205*/
    .long   DefaultISR                                      /* 206*/
    .long   DefaultISR                                      /* 207*/
    .long   DefaultISR                                      /* 208*/
    .long   DefaultISR                                      /* 209*/
    .long   DefaultISR                                      /* 210*/
    .long   DefaultISR                                      /* 211*/
    .long   DefaultISR                                      /* 212*/
    .long   DefaultISR                                      /* 213*/
    .long   DefaultISR                                      /* 214*/
    .long   DefaultISR                                      /* 215*/
    .long   DefaultISR                                      /* 216*/
    .long   DefaultISR                                      /* 217*/
    .long   DefaultISR                                      /* 218*/
    .long   DefaultISR                                      /* 219*/
    .long   DefaultISR                                      /* 220*/
    .long   DefaultISR                                      /* 221*/
    .long   DefaultISR                                      /* 222*/
    .long   DefaultISR                                      /* 223*/
    .long   DefaultISR                                      /* 224*/
    .long   DefaultISR                                      /* 225*/
    .long   DefaultISR                                      /* 226*/
    .long   DefaultISR                                      /* 227*/
    .long   DefaultISR                                      /* 228*/
    .long   DefaultISR                                      /* 229*/
    .long   DefaultISR                                      /* 230*/
    .long   DefaultISR                                      /* 231*/
    .long   DefaultISR                                      /* 232*/
    .long   DefaultISR                                      /* 233*/
    .long   DefaultISR                                      /* 234*/
    .long   DefaultISR                                      /* 235*/
    .long   DefaultISR                                      /* 236*/
    .long   DefaultISR                                      /* 237*/
    .long   DefaultISR                                      /* 238*/
    .long   DefaultISR                                      /* 239*/
    .long   DefaultISR                                      /* 240*/
    .long   DefaultISR                                      /* 241*/
    .long   DefaultISR                                      /* 242*/
    .long   DefaultISR                                      /* 243*/
    .long   DefaultISR                                      /* 244*/
    .long   DefaultISR                                      /* 245*/
    .long   DefaultISR                                      /* 246*/
    .long   DefaultISR                                      /* 247*/
    .long   DefaultISR                                      /* 248*/
    .long   DefaultISR                                      /* 249*/
    .long   DefaultISR                                      /* 250*/
    .long   DefaultISR                                      /* 251*/
    .long   DefaultISR                                      /* 252*/
    .long   DefaultISR                                      /* 253*/
    .long   DefaultISR                                      /* 254*/
    .long   DefaultISR                                      /* 255*/

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
    cpsid   i                   /* Mask interrupts */
    .equ    VTOR, 0xE000ED08
    ldr     r0, =VTOR
    ldr     r1, =__isr_vector
    str     r1, [r0]
    ldr     r2, [r1]
    msr     msp, r2
    ldr     r0, =__StackLimit
    msr     msplim, r0

#if !defined(BYPASS_ECC_RAM_INIT)
    ldr     r0, =0x04000000
    ldr     r1, =.ram_init_ctcm01
    bics.w  r1, #0x10000000
    cmp     r0, r1
    bcc.n   .ram_init_done      /* Bypass ECC RAM initialization on RAM target, debugger will do the initialization */

.ram_init_ctcm01:               /* Initialize ctcm01 */
    ldr     r0, =0x4000000
    ldr     r1, =0x4004000
    ldr     r2, =0
    ldr     r3, =0
    ldr     r4, =0
    ldr     r5, =0
.loop01:
    stmia   r0!, {r2 - r5}
    cmp     r0, r1
    bcc.n   .loop01

.ram_init_stcm012:              /* Initialize stcm012 */
    ldr     r0, =0x20000000
    ldr     r1, =0x20010000
.loop012:
    stmia   r0!, {r2 - r5}
    cmp     r0, r1
    bcc.n   .loop012

.ram_init_stcm5:
    ldr     r0, =0x2001a000
    ldr     r1, =0x2001c000
.loop5:                         /* Initialize stcm5 */
    stmia   r0!, {r2 - r5}
    cmp     r0, r1
    bcc.n   .loop5

.ram_init_done:
#endif

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

#ifdef __STARTUP_CLEAR_SMU2
/*     This part of work usually is done in C library startup code. Otherwise,
 *     define this macro to enable it in this startup.
 *
 *     Loop to zero out SMU2 section used by the Host, which uses following symbols
 *     in linker script:
 *      __smu2_start__: start of SMU2 section. Must align to 4
 *      __smu2_end__: end of SMU2 section. Must align to 4
 */
    ldr r1, =__smu2_start__
    ldr r2, =__smu2_end__

    movs    r0, 0
.LC3:
    cmp     r1, r2
    itt    lt
    strlt   r0, [r1], #4
    blt    .LC3
#endif /* __STARTUP_CLEAR_SMU2 */

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
    .weak DMA0_CH0_IRQHandler
    .type DMA0_CH0_IRQHandler, %function
DMA0_CH0_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH0_IRQHandler, . - DMA0_CH0_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH1_IRQHandler
    .type DMA0_CH1_IRQHandler, %function
DMA0_CH1_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH1_IRQHandler, . - DMA0_CH1_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH2_IRQHandler
    .type DMA0_CH2_IRQHandler, %function
DMA0_CH2_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH2_IRQHandler, . - DMA0_CH2_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH3_IRQHandler
    .type DMA0_CH3_IRQHandler, %function
DMA0_CH3_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH3_IRQHandler, . - DMA0_CH3_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH4_IRQHandler
    .type DMA0_CH4_IRQHandler, %function
DMA0_CH4_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH4_IRQHandler, . - DMA0_CH4_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH5_IRQHandler
    .type DMA0_CH5_IRQHandler, %function
DMA0_CH5_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH5_IRQHandler, . - DMA0_CH5_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH6_IRQHandler
    .type DMA0_CH6_IRQHandler, %function
DMA0_CH6_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH6_IRQHandler, . - DMA0_CH6_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH7_IRQHandler
    .type DMA0_CH7_IRQHandler, %function
DMA0_CH7_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH7_IRQHandler, . - DMA0_CH7_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH8_IRQHandler
    .type DMA0_CH8_IRQHandler, %function
DMA0_CH8_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH8_IRQHandler, . - DMA0_CH8_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH9_IRQHandler
    .type DMA0_CH9_IRQHandler, %function
DMA0_CH9_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH9_IRQHandler, . - DMA0_CH9_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH10_IRQHandler
    .type DMA0_CH10_IRQHandler, %function
DMA0_CH10_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH10_IRQHandler, . - DMA0_CH10_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH11_IRQHandler
    .type DMA0_CH11_IRQHandler, %function
DMA0_CH11_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH11_IRQHandler, . - DMA0_CH11_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH12_IRQHandler
    .type DMA0_CH12_IRQHandler, %function
DMA0_CH12_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH12_IRQHandler, . - DMA0_CH12_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH13_IRQHandler
    .type DMA0_CH13_IRQHandler, %function
DMA0_CH13_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH13_IRQHandler, . - DMA0_CH13_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH14_IRQHandler
    .type DMA0_CH14_IRQHandler, %function
DMA0_CH14_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH14_IRQHandler, . - DMA0_CH14_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_CH15_IRQHandler
    .type DMA0_CH15_IRQHandler, %function
DMA0_CH15_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_CH15_IRQHandler, . - DMA0_CH15_IRQHandler

    .align 1
    .thumb_func
    .weak SFA0_IRQHandler
    .type SFA0_IRQHandler, %function
SFA0_IRQHandler:
    ldr   r0,=SFA0_DriverIRQHandler
    bx    r0
    .size SFA0_IRQHandler, . - SFA0_IRQHandler

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
    .weak I3C0_IRQHandler
    .type I3C0_IRQHandler, %function
I3C0_IRQHandler:
    ldr   r0,=I3C0_DriverIRQHandler
    bx    r0
    .size I3C0_IRQHandler, . - I3C0_IRQHandler

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
    .weak FLEXIO0_IRQHandler
    .type FLEXIO0_IRQHandler, %function
FLEXIO0_IRQHandler:
    ldr   r0,=FLEXIO0_DriverIRQHandler
    bx    r0
    .size FLEXIO0_IRQHandler, . - FLEXIO0_IRQHandler


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
    def_irq_handler    CTI_IRQHandler
    def_irq_handler    CMC0_IRQHandler
    def_irq_handler    DMA0_DriverIRQHandler
    def_irq_handler    EWM0_IRQHandler
    def_irq_handler    MCM0_IRQHandler
    def_irq_handler    MSCM0_IRQHandler
    def_irq_handler    SPC0_IRQHandler
    def_irq_handler    WUU0_IRQHandler
    def_irq_handler    WDOG0_IRQHandler
    def_irq_handler    WDOG1_IRQHandler
    def_irq_handler    SCG0_IRQHandler
    def_irq_handler    SFA0_DriverIRQHandler
    def_irq_handler    FMU0_IRQHandler
    def_irq_handler    ELE_CMD_IRQHandler
    def_irq_handler    ELE_SECURE_IRQHandler
    def_irq_handler    ELE_NONSECURE_IRQHandler
    def_irq_handler    TRDC0_IRQHandler
    def_irq_handler    RTC_Alarm_IRQHandler
    def_irq_handler    RTC_Seconds_IRQHandler
    def_irq_handler    LPTMR0_IRQHandler
    def_irq_handler    LPTMR1_IRQHandler
    def_irq_handler    LPIT0_IRQHandler
    def_irq_handler    TPM0_IRQHandler
    def_irq_handler    TPM1_IRQHandler
    def_irq_handler    LPI2C0_DriverIRQHandler
    def_irq_handler    LPI2C1_DriverIRQHandler
    def_irq_handler    I3C0_DriverIRQHandler
    def_irq_handler    LPSPI0_DriverIRQHandler
    def_irq_handler    LPSPI1_DriverIRQHandler
    def_irq_handler    LPUART0_DriverIRQHandler
    def_irq_handler    LPUART1_DriverIRQHandler
    def_irq_handler    FLEXIO0_DriverIRQHandler
    def_irq_handler    Reserved63_IRQHandler
    def_irq_handler    RF_IMU0_IRQHandler
    def_irq_handler    RF_IMU1_IRQHandler
    def_irq_handler    RF_NBU_IRQHandler
    def_irq_handler    RF_FMU_IRQHandler
    def_irq_handler    RF_WOR_IRQHandler
    def_irq_handler    RF_802_15_4_IRQHandler
    def_irq_handler    RF_Generic_IRQHandler
    def_irq_handler    RF_BRIC_IRQHandler
    def_irq_handler    RF_LANT_SW_IRQHandler
    def_irq_handler    RFMC_IRQHandler
    def_irq_handler    DSB_IRQHandler
    def_irq_handler    GPIOA_INT0_IRQHandler
    def_irq_handler    GPIOA_INT1_IRQHandler
    def_irq_handler    GPIOB_INT0_IRQHandler
    def_irq_handler    GPIOB_INT1_IRQHandler
    def_irq_handler    GPIOC_INT0_IRQHandler
    def_irq_handler    GPIOC_INT1_IRQHandler
    def_irq_handler    GPIOD_INT0_IRQHandler
    def_irq_handler    GPIOD_INT1_IRQHandler
    def_irq_handler    PORTA_EFT_IRQHandler
    def_irq_handler    PORTB_EFT_IRQHandler
    def_irq_handler    PORTC_EFT_IRQHandler
    def_irq_handler    PORTD_EFT_IRQHandler
    def_irq_handler    ADC0_IRQHandler
    def_irq_handler    LPCMP0_IRQHandler
    def_irq_handler    LPCMP1_IRQHandler
    def_irq_handler    VBAT_IRQHandler
    def_irq_handler    Reserved91_IRQHandler

    .end
