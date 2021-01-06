/* --------------------------------------------------------------------------*/
/* @file:    startup_MIMXRT685S_cm33.s                                                */
/* @purpose: CMSIS Cortex-M33 Core Device Startup File                       */
/*           MIMXRT685S_cm33                                                          */
/* @version: 2.0                                                      */
/* @date:    2019-11-12                                                         */
/* --------------------------------------------------------------------------*/
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
#if (__ARM_FEATURE_CMSE & 0x2)
    .long   0x180000                                        /* Image length*/
#else
    .long   _image_size                                     /* Image length*/
#endif
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   SVC_Handler                                     /* SVCall Handler*/
    .long   DebugMon_Handler                                /* Debug Monitor Handler*/
    .long   __isr_vector                                    /* Image load address*/
    .long   PendSV_Handler                                  /* PendSV Handler*/
    .long   SysTick_Handler                                 /* SysTick Handler*/

    /* External Interrupts */
    .long   WDT0_IRQHandler  /* Windowed watchdog timer 0 (CM33 watchdog) */
    .long   DMA0_IRQHandler  /* DMA controller 0 (secure or CM33 DMA) */
    .long   GPIO_INTA_IRQHandler  /* GPIO interrupt A */
    .long   GPIO_INTB_IRQHandler  /* GPIO interrupt B */
    .long   PIN_INT0_IRQHandler  /* Pin interrupt 0 or pattern match engine slice 0 int */
    .long   PIN_INT1_IRQHandler  /* Pin interrupt 1 or pattern match engine slice 1 int */
    .long   PIN_INT2_IRQHandler  /* Pin interrupt 2 or pattern match engine slice 2 int */
    .long   PIN_INT3_IRQHandler  /* Pin interrupt 3 or pattern match engine slice 3 int */
    .long   UTICK0_IRQHandler  /* Micro-tick Timer */
    .long   MRT0_IRQHandler  /* Multi-Rate Timer */
    .long   CTIMER0_IRQHandler  /* Standard counter/timer CTIMER0 */
    .long   CTIMER1_IRQHandler  /* Standard counter/timer CTIMER1 */
    .long   SCT0_IRQHandler  /* SCTimer/PWM */
    .long   CTIMER3_IRQHandler  /* Standard counter/timer CTIMER3 */
    .long   FLEXCOMM0_IRQHandler  /* Flexcomm Interface 0 (USART, SPI, I2C, I2S) */
    .long   FLEXCOMM1_IRQHandler  /* Flexcomm Interface 1 (USART, SPI, I2C, I2S) */
    .long   FLEXCOMM2_IRQHandler  /* Flexcomm Interface 2 (USART, SPI, I2C, I2S) */
    .long   FLEXCOMM3_IRQHandler  /* Flexcomm Interface 3 (USART, SPI, I2C, I2S) */
    .long   FLEXCOMM4_IRQHandler  /* Flexcomm Interface 4 (USART, SPI, I2C, I2S) */
    .long   FLEXCOMM5_IRQHandler  /* Flexcomm Interface 5 (USART, SPI, I2C, I2S) */
    .long   FLEXCOMM14_IRQHandler  /* Flexcomm Interface 14 (SPI only) */
    .long   FLEXCOMM15_IRQHandler  /* Flexcomm Interface 15 (I2C only) */
    .long   ADC0_IRQHandler  /* ADC0  */
    .long   Reserved39_IRQHandler  /* Reserved interrupt */
    .long   ACMP_IRQHandler  /* Analog comparator */
    .long   DMIC0_IRQHandler  /* Digital microphone and DMIC subsystem */
    .long   Reserved42_IRQHandler  /* Reserved interrupt */
    .long   HYPERVISOR_IRQHandler  /* Hypervisor */
    .long   SECUREVIOLATION_IRQHandler  /* Secure violation */
    .long   HWVAD0_IRQHandler  /* Hardware Voice Activity Detector */
    .long   Reserved46_IRQHandler  /* Reserved interrupt */
    .long   RNG_IRQHandler  /* Random number Generator */
    .long   RTC_IRQHandler  /* RTC alarm and wake-up */
    .long   DSPWAKE_IRQHandler  /* Wake-up from DSP */
    .long   MU_A_IRQHandler  /* Messaging Unit port A for CM33 */
    .long   PIN_INT4_IRQHandler  /* Pin interrupt 4 or pattern match engine slice 4 int */
    .long   PIN_INT5_IRQHandler  /* Pin interrupt 5 or pattern match engine slice 5 int */
    .long   PIN_INT6_IRQHandler  /* Pin interrupt 6 or pattern match engine slice 6 int */
    .long   PIN_INT7_IRQHandler  /* Pin interrupt 7 or pattern match engine slice 7 int */
    .long   CTIMER2_IRQHandler  /* Standard counter/timer CTIMER2 */
    .long   CTIMER4_IRQHandler  /* Standard counter/timer CTIMER4 */
    .long   OS_EVENT_IRQHandler  /* OS event timer */
    .long   FLEXSPI_IRQHandler  /* FLEXSPI interface */
    .long   FLEXCOMM6_IRQHandler  /* Flexcomm Interface 6 (USART, SPI, I2C, I2S) */
    .long   FLEXCOMM7_IRQHandler  /* Flexcomm Interface 7 (USART, SPI, I2C, I2S) */
    .long   USDHC0_IRQHandler  /* USDHC0 (Enhanced SDHC) interrupt request */
    .long   USDHC1_IRQHandler  /* USDHC1 (Enhanced SDHC) interrupt request */
    .long   SGPIO_INTA_IRQHandler  /* Secure GPIO interrupt A */
    .long   SGPIO_INTB_IRQHandler  /* Secure GPIO interrupt B */
    .long   I3C0_IRQHandler  /* I3C interface 0 */
    .long   USB_IRQHandler  /* High-speed USB device/host */
    .long   USB_WAKEUP_IRQHandler  /* USB Activity Wake-up Interrupt */
    .long   WDT1_IRQHandler  /* Windowed watchdog timer 1 (HiFi 4 watchdog) */
    .long   USBPHY_DCD_IRQHandler  /* USBPHY DCD */
    .long   DMA1_IRQHandler  /* DMA controller 1 (non-secure or HiFi 4 DMA) */
    .long   PUF_IRQHandler  /* Physical Unclonable Function */
    .long   POWERQUAD_IRQHandler  /* PowerQuad math coprocessor */
    .long   CASPER_IRQHandler  /* Casper cryptographic coprocessor */
    .long   PMC_PMIC_IRQHandler  /* Power management IC */
    .long   HASHCRYPT_IRQHandler  /* Hash-AES unit */

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
    .weak WDT0_IRQHandler
    .type WDT0_IRQHandler, %function
WDT0_IRQHandler:
    ldr   r0,=WDT0_DriverIRQHandler
    bx    r0
    .size WDT0_IRQHandler, . - WDT0_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_IRQHandler
    .type DMA0_IRQHandler, %function
DMA0_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_IRQHandler, . - DMA0_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO_INTA_IRQHandler
    .type GPIO_INTA_IRQHandler, %function
GPIO_INTA_IRQHandler:
    ldr   r0,=GPIO_INTA_DriverIRQHandler
    bx    r0
    .size GPIO_INTA_IRQHandler, . - GPIO_INTA_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO_INTB_IRQHandler
    .type GPIO_INTB_IRQHandler, %function
GPIO_INTB_IRQHandler:
    ldr   r0,=GPIO_INTB_DriverIRQHandler
    bx    r0
    .size GPIO_INTB_IRQHandler, . - GPIO_INTB_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT0_IRQHandler
    .type PIN_INT0_IRQHandler, %function
PIN_INT0_IRQHandler:
    ldr   r0,=PIN_INT0_DriverIRQHandler
    bx    r0
    .size PIN_INT0_IRQHandler, . - PIN_INT0_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT1_IRQHandler
    .type PIN_INT1_IRQHandler, %function
PIN_INT1_IRQHandler:
    ldr   r0,=PIN_INT1_DriverIRQHandler
    bx    r0
    .size PIN_INT1_IRQHandler, . - PIN_INT1_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT2_IRQHandler
    .type PIN_INT2_IRQHandler, %function
PIN_INT2_IRQHandler:
    ldr   r0,=PIN_INT2_DriverIRQHandler
    bx    r0
    .size PIN_INT2_IRQHandler, . - PIN_INT2_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT3_IRQHandler
    .type PIN_INT3_IRQHandler, %function
PIN_INT3_IRQHandler:
    ldr   r0,=PIN_INT3_DriverIRQHandler
    bx    r0
    .size PIN_INT3_IRQHandler, . - PIN_INT3_IRQHandler

    .align 1
    .thumb_func
    .weak UTICK0_IRQHandler
    .type UTICK0_IRQHandler, %function
UTICK0_IRQHandler:
    ldr   r0,=UTICK0_DriverIRQHandler
    bx    r0
    .size UTICK0_IRQHandler, . - UTICK0_IRQHandler

    .align 1
    .thumb_func
    .weak MRT0_IRQHandler
    .type MRT0_IRQHandler, %function
MRT0_IRQHandler:
    ldr   r0,=MRT0_DriverIRQHandler
    bx    r0
    .size MRT0_IRQHandler, . - MRT0_IRQHandler

    .align 1
    .thumb_func
    .weak CTIMER0_IRQHandler
    .type CTIMER0_IRQHandler, %function
CTIMER0_IRQHandler:
    ldr   r0,=CTIMER0_DriverIRQHandler
    bx    r0
    .size CTIMER0_IRQHandler, . - CTIMER0_IRQHandler

    .align 1
    .thumb_func
    .weak CTIMER1_IRQHandler
    .type CTIMER1_IRQHandler, %function
CTIMER1_IRQHandler:
    ldr   r0,=CTIMER1_DriverIRQHandler
    bx    r0
    .size CTIMER1_IRQHandler, . - CTIMER1_IRQHandler

    .align 1
    .thumb_func
    .weak SCT0_IRQHandler
    .type SCT0_IRQHandler, %function
SCT0_IRQHandler:
    ldr   r0,=SCT0_DriverIRQHandler
    bx    r0
    .size SCT0_IRQHandler, . - SCT0_IRQHandler

    .align 1
    .thumb_func
    .weak CTIMER3_IRQHandler
    .type CTIMER3_IRQHandler, %function
CTIMER3_IRQHandler:
    ldr   r0,=CTIMER3_DriverIRQHandler
    bx    r0
    .size CTIMER3_IRQHandler, . - CTIMER3_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM0_IRQHandler
    .type FLEXCOMM0_IRQHandler, %function
FLEXCOMM0_IRQHandler:
    ldr   r0,=FLEXCOMM0_DriverIRQHandler
    bx    r0
    .size FLEXCOMM0_IRQHandler, . - FLEXCOMM0_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM1_IRQHandler
    .type FLEXCOMM1_IRQHandler, %function
FLEXCOMM1_IRQHandler:
    ldr   r0,=FLEXCOMM1_DriverIRQHandler
    bx    r0
    .size FLEXCOMM1_IRQHandler, . - FLEXCOMM1_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM2_IRQHandler
    .type FLEXCOMM2_IRQHandler, %function
FLEXCOMM2_IRQHandler:
    ldr   r0,=FLEXCOMM2_DriverIRQHandler
    bx    r0
    .size FLEXCOMM2_IRQHandler, . - FLEXCOMM2_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM3_IRQHandler
    .type FLEXCOMM3_IRQHandler, %function
FLEXCOMM3_IRQHandler:
    ldr   r0,=FLEXCOMM3_DriverIRQHandler
    bx    r0
    .size FLEXCOMM3_IRQHandler, . - FLEXCOMM3_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM4_IRQHandler
    .type FLEXCOMM4_IRQHandler, %function
FLEXCOMM4_IRQHandler:
    ldr   r0,=FLEXCOMM4_DriverIRQHandler
    bx    r0
    .size FLEXCOMM4_IRQHandler, . - FLEXCOMM4_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM5_IRQHandler
    .type FLEXCOMM5_IRQHandler, %function
FLEXCOMM5_IRQHandler:
    ldr   r0,=FLEXCOMM5_DriverIRQHandler
    bx    r0
    .size FLEXCOMM5_IRQHandler, . - FLEXCOMM5_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM14_IRQHandler
    .type FLEXCOMM14_IRQHandler, %function
FLEXCOMM14_IRQHandler:
    ldr   r0,=FLEXCOMM14_DriverIRQHandler
    bx    r0
    .size FLEXCOMM14_IRQHandler, . - FLEXCOMM14_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM15_IRQHandler
    .type FLEXCOMM15_IRQHandler, %function
FLEXCOMM15_IRQHandler:
    ldr   r0,=FLEXCOMM15_DriverIRQHandler
    bx    r0
    .size FLEXCOMM15_IRQHandler, . - FLEXCOMM15_IRQHandler

    .align 1
    .thumb_func
    .weak ADC0_IRQHandler
    .type ADC0_IRQHandler, %function
ADC0_IRQHandler:
    ldr   r0,=ADC0_DriverIRQHandler
    bx    r0
    .size ADC0_IRQHandler, . - ADC0_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved39_IRQHandler
    .type Reserved39_IRQHandler, %function
Reserved39_IRQHandler:
    ldr   r0,=Reserved39_DriverIRQHandler
    bx    r0
    .size Reserved39_IRQHandler, . - Reserved39_IRQHandler

    .align 1
    .thumb_func
    .weak ACMP_IRQHandler
    .type ACMP_IRQHandler, %function
ACMP_IRQHandler:
    ldr   r0,=ACMP_DriverIRQHandler
    bx    r0
    .size ACMP_IRQHandler, . - ACMP_IRQHandler

    .align 1
    .thumb_func
    .weak DMIC0_IRQHandler
    .type DMIC0_IRQHandler, %function
DMIC0_IRQHandler:
    ldr   r0,=DMIC0_DriverIRQHandler
    bx    r0
    .size DMIC0_IRQHandler, . - DMIC0_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved42_IRQHandler
    .type Reserved42_IRQHandler, %function
Reserved42_IRQHandler:
    ldr   r0,=Reserved42_DriverIRQHandler
    bx    r0
    .size Reserved42_IRQHandler, . - Reserved42_IRQHandler

    .align 1
    .thumb_func
    .weak HYPERVISOR_IRQHandler
    .type HYPERVISOR_IRQHandler, %function
HYPERVISOR_IRQHandler:
    ldr   r0,=HYPERVISOR_DriverIRQHandler
    bx    r0
    .size HYPERVISOR_IRQHandler, . - HYPERVISOR_IRQHandler

    .align 1
    .thumb_func
    .weak SECUREVIOLATION_IRQHandler
    .type SECUREVIOLATION_IRQHandler, %function
SECUREVIOLATION_IRQHandler:
    ldr   r0,=SECUREVIOLATION_DriverIRQHandler
    bx    r0
    .size SECUREVIOLATION_IRQHandler, . - SECUREVIOLATION_IRQHandler

    .align 1
    .thumb_func
    .weak HWVAD0_IRQHandler
    .type HWVAD0_IRQHandler, %function
HWVAD0_IRQHandler:
    ldr   r0,=HWVAD0_DriverIRQHandler
    bx    r0
    .size HWVAD0_IRQHandler, . - HWVAD0_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved46_IRQHandler
    .type Reserved46_IRQHandler, %function
Reserved46_IRQHandler:
    ldr   r0,=Reserved46_DriverIRQHandler
    bx    r0
    .size Reserved46_IRQHandler, . - Reserved46_IRQHandler

    .align 1
    .thumb_func
    .weak RNG_IRQHandler
    .type RNG_IRQHandler, %function
RNG_IRQHandler:
    ldr   r0,=RNG_DriverIRQHandler
    bx    r0
    .size RNG_IRQHandler, . - RNG_IRQHandler

    .align 1
    .thumb_func
    .weak RTC_IRQHandler
    .type RTC_IRQHandler, %function
RTC_IRQHandler:
    ldr   r0,=RTC_DriverIRQHandler
    bx    r0
    .size RTC_IRQHandler, . - RTC_IRQHandler

    .align 1
    .thumb_func
    .weak DSPWAKE_IRQHandler
    .type DSPWAKE_IRQHandler, %function
DSPWAKE_IRQHandler:
    ldr   r0,=DSPWAKE_DriverIRQHandler
    bx    r0
    .size DSPWAKE_IRQHandler, . - DSPWAKE_IRQHandler

    .align 1
    .thumb_func
    .weak MU_A_IRQHandler
    .type MU_A_IRQHandler, %function
MU_A_IRQHandler:
    ldr   r0,=MU_A_DriverIRQHandler
    bx    r0
    .size MU_A_IRQHandler, . - MU_A_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT4_IRQHandler
    .type PIN_INT4_IRQHandler, %function
PIN_INT4_IRQHandler:
    ldr   r0,=PIN_INT4_DriverIRQHandler
    bx    r0
    .size PIN_INT4_IRQHandler, . - PIN_INT4_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT5_IRQHandler
    .type PIN_INT5_IRQHandler, %function
PIN_INT5_IRQHandler:
    ldr   r0,=PIN_INT5_DriverIRQHandler
    bx    r0
    .size PIN_INT5_IRQHandler, . - PIN_INT5_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT6_IRQHandler
    .type PIN_INT6_IRQHandler, %function
PIN_INT6_IRQHandler:
    ldr   r0,=PIN_INT6_DriverIRQHandler
    bx    r0
    .size PIN_INT6_IRQHandler, . - PIN_INT6_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT7_IRQHandler
    .type PIN_INT7_IRQHandler, %function
PIN_INT7_IRQHandler:
    ldr   r0,=PIN_INT7_DriverIRQHandler
    bx    r0
    .size PIN_INT7_IRQHandler, . - PIN_INT7_IRQHandler

    .align 1
    .thumb_func
    .weak CTIMER2_IRQHandler
    .type CTIMER2_IRQHandler, %function
CTIMER2_IRQHandler:
    ldr   r0,=CTIMER2_DriverIRQHandler
    bx    r0
    .size CTIMER2_IRQHandler, . - CTIMER2_IRQHandler

    .align 1
    .thumb_func
    .weak CTIMER4_IRQHandler
    .type CTIMER4_IRQHandler, %function
CTIMER4_IRQHandler:
    ldr   r0,=CTIMER4_DriverIRQHandler
    bx    r0
    .size CTIMER4_IRQHandler, . - CTIMER4_IRQHandler

    .align 1
    .thumb_func
    .weak OS_EVENT_IRQHandler
    .type OS_EVENT_IRQHandler, %function
OS_EVENT_IRQHandler:
    ldr   r0,=OS_EVENT_DriverIRQHandler
    bx    r0
    .size OS_EVENT_IRQHandler, . - OS_EVENT_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXSPI_IRQHandler
    .type FLEXSPI_IRQHandler, %function
FLEXSPI_IRQHandler:
    ldr   r0,=FLEXSPI_DriverIRQHandler
    bx    r0
    .size FLEXSPI_IRQHandler, . - FLEXSPI_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM6_IRQHandler
    .type FLEXCOMM6_IRQHandler, %function
FLEXCOMM6_IRQHandler:
    ldr   r0,=FLEXCOMM6_DriverIRQHandler
    bx    r0
    .size FLEXCOMM6_IRQHandler, . - FLEXCOMM6_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM7_IRQHandler
    .type FLEXCOMM7_IRQHandler, %function
FLEXCOMM7_IRQHandler:
    ldr   r0,=FLEXCOMM7_DriverIRQHandler
    bx    r0
    .size FLEXCOMM7_IRQHandler, . - FLEXCOMM7_IRQHandler

    .align 1
    .thumb_func
    .weak USDHC0_IRQHandler
    .type USDHC0_IRQHandler, %function
USDHC0_IRQHandler:
    ldr   r0,=USDHC0_DriverIRQHandler
    bx    r0
    .size USDHC0_IRQHandler, . - USDHC0_IRQHandler

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
    .weak SGPIO_INTA_IRQHandler
    .type SGPIO_INTA_IRQHandler, %function
SGPIO_INTA_IRQHandler:
    ldr   r0,=SGPIO_INTA_DriverIRQHandler
    bx    r0
    .size SGPIO_INTA_IRQHandler, . - SGPIO_INTA_IRQHandler

    .align 1
    .thumb_func
    .weak SGPIO_INTB_IRQHandler
    .type SGPIO_INTB_IRQHandler, %function
SGPIO_INTB_IRQHandler:
    ldr   r0,=SGPIO_INTB_DriverIRQHandler
    bx    r0
    .size SGPIO_INTB_IRQHandler, . - SGPIO_INTB_IRQHandler

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
    .weak USB_IRQHandler
    .type USB_IRQHandler, %function
USB_IRQHandler:
    ldr   r0,=USB_DriverIRQHandler
    bx    r0
    .size USB_IRQHandler, . - USB_IRQHandler

    .align 1
    .thumb_func
    .weak USB_WAKEUP_IRQHandler
    .type USB_WAKEUP_IRQHandler, %function
USB_WAKEUP_IRQHandler:
    ldr   r0,=USB_WAKEUP_DriverIRQHandler
    bx    r0
    .size USB_WAKEUP_IRQHandler, . - USB_WAKEUP_IRQHandler

    .align 1
    .thumb_func
    .weak WDT1_IRQHandler
    .type WDT1_IRQHandler, %function
WDT1_IRQHandler:
    ldr   r0,=WDT1_DriverIRQHandler
    bx    r0
    .size WDT1_IRQHandler, . - WDT1_IRQHandler

    .align 1
    .thumb_func
    .weak USBPHY_DCD_IRQHandler
    .type USBPHY_DCD_IRQHandler, %function
USBPHY_DCD_IRQHandler:
    ldr   r0,=USBPHY_DCD_DriverIRQHandler
    bx    r0
    .size USBPHY_DCD_IRQHandler, . - USBPHY_DCD_IRQHandler

    .align 1
    .thumb_func
    .weak DMA1_IRQHandler
    .type DMA1_IRQHandler, %function
DMA1_IRQHandler:
    ldr   r0,=DMA1_DriverIRQHandler
    bx    r0
    .size DMA1_IRQHandler, . - DMA1_IRQHandler

    .align 1
    .thumb_func
    .weak PUF_IRQHandler
    .type PUF_IRQHandler, %function
PUF_IRQHandler:
    ldr   r0,=PUF_DriverIRQHandler
    bx    r0
    .size PUF_IRQHandler, . - PUF_IRQHandler

    .align 1
    .thumb_func
    .weak POWERQUAD_IRQHandler
    .type POWERQUAD_IRQHandler, %function
POWERQUAD_IRQHandler:
    ldr   r0,=POWERQUAD_DriverIRQHandler
    bx    r0
    .size POWERQUAD_IRQHandler, . - POWERQUAD_IRQHandler

    .align 1
    .thumb_func
    .weak CASPER_IRQHandler
    .type CASPER_IRQHandler, %function
CASPER_IRQHandler:
    ldr   r0,=CASPER_DriverIRQHandler
    bx    r0
    .size CASPER_IRQHandler, . - CASPER_IRQHandler

    .align 1
    .thumb_func
    .weak PMC_PMIC_IRQHandler
    .type PMC_PMIC_IRQHandler, %function
PMC_PMIC_IRQHandler:
    ldr   r0,=PMC_PMIC_DriverIRQHandler
    bx    r0
    .size PMC_PMIC_IRQHandler, . - PMC_PMIC_IRQHandler

    .align 1
    .thumb_func
    .weak HASHCRYPT_IRQHandler
    .type HASHCRYPT_IRQHandler, %function
HASHCRYPT_IRQHandler:
    ldr   r0,=HASHCRYPT_DriverIRQHandler
    bx    r0
    .size HASHCRYPT_IRQHandler, . - HASHCRYPT_IRQHandler

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
                def_irq_handler     WDT0_DriverIRQHandler
                def_irq_handler     DMA0_DriverIRQHandler
                def_irq_handler     GPIO_INTA_DriverIRQHandler
                def_irq_handler     GPIO_INTB_DriverIRQHandler
                def_irq_handler     PIN_INT0_DriverIRQHandler
                def_irq_handler     PIN_INT1_DriverIRQHandler
                def_irq_handler     PIN_INT2_DriverIRQHandler
                def_irq_handler     PIN_INT3_DriverIRQHandler
                def_irq_handler     UTICK0_DriverIRQHandler
                def_irq_handler     MRT0_DriverIRQHandler
                def_irq_handler     CTIMER0_DriverIRQHandler
                def_irq_handler     CTIMER1_DriverIRQHandler
                def_irq_handler     SCT0_DriverIRQHandler
                def_irq_handler     CTIMER3_DriverIRQHandler
                def_irq_handler     FLEXCOMM0_DriverIRQHandler
                def_irq_handler     FLEXCOMM1_DriverIRQHandler
                def_irq_handler     FLEXCOMM2_DriverIRQHandler
                def_irq_handler     FLEXCOMM3_DriverIRQHandler
                def_irq_handler     FLEXCOMM4_DriverIRQHandler
                def_irq_handler     FLEXCOMM5_DriverIRQHandler
                def_irq_handler     FLEXCOMM14_DriverIRQHandler
                def_irq_handler     FLEXCOMM15_DriverIRQHandler
                def_irq_handler     ADC0_DriverIRQHandler
                def_irq_handler     Reserved39_DriverIRQHandler
                def_irq_handler     ACMP_DriverIRQHandler
                def_irq_handler     DMIC0_DriverIRQHandler
                def_irq_handler     Reserved42_DriverIRQHandler
                def_irq_handler     HYPERVISOR_DriverIRQHandler
                def_irq_handler     SECUREVIOLATION_DriverIRQHandler
                def_irq_handler     HWVAD0_DriverIRQHandler
                def_irq_handler     Reserved46_DriverIRQHandler
                def_irq_handler     RNG_DriverIRQHandler
                def_irq_handler     RTC_DriverIRQHandler
                def_irq_handler     DSPWAKE_DriverIRQHandler
                def_irq_handler     MU_A_DriverIRQHandler
                def_irq_handler     PIN_INT4_DriverIRQHandler
                def_irq_handler     PIN_INT5_DriverIRQHandler
                def_irq_handler     PIN_INT6_DriverIRQHandler
                def_irq_handler     PIN_INT7_DriverIRQHandler
                def_irq_handler     CTIMER2_DriverIRQHandler
                def_irq_handler     CTIMER4_DriverIRQHandler
                def_irq_handler     OS_EVENT_DriverIRQHandler
                def_irq_handler     FLEXSPI_DriverIRQHandler
                def_irq_handler     FLEXCOMM6_DriverIRQHandler
                def_irq_handler     FLEXCOMM7_DriverIRQHandler
                def_irq_handler     USDHC0_DriverIRQHandler
                def_irq_handler     USDHC1_DriverIRQHandler
                def_irq_handler     SGPIO_INTA_DriverIRQHandler
                def_irq_handler     SGPIO_INTB_DriverIRQHandler
                def_irq_handler     I3C0_DriverIRQHandler
                def_irq_handler     USB_DriverIRQHandler
                def_irq_handler     USB_WAKEUP_DriverIRQHandler
                def_irq_handler     WDT1_DriverIRQHandler
                def_irq_handler     USBPHY_DCD_DriverIRQHandler
                def_irq_handler     DMA1_DriverIRQHandler
                def_irq_handler     PUF_DriverIRQHandler
                def_irq_handler     POWERQUAD_DriverIRQHandler
                def_irq_handler     CASPER_DriverIRQHandler
                def_irq_handler     PMC_PMIC_DriverIRQHandler
                def_irq_handler     HASHCRYPT_DriverIRQHandler

    .end
