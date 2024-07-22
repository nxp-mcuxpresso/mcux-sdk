/* ------------------------------------------------------------------------- */
/*  @file:    startup_RW610.s                                                */
/*  @purpose: CMSIS Cortex-M33 Core Device Startup File                      */
/*            RW610                                                          */
/*  @version: 1.0                                                            */
/*  @date:    2021-3-16                                                      */
/*  @build:   b240311                                                        */
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
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
    .long   0x100000                                        /* Image length*/
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

                                                            /* External Interrupts*/
    .long   WDT0_IRQHandler                                 /* Windowed watchdog timer 0 (WDT0)(Cortex-M33 watchdog)*/
    .long   DMA0_IRQHandler                                 /* Direct memory access (DMA) controller 0 (secure or Cortex-M33 DMA)*/
    .long   GPIO_INTA_IRQHandler                            /* GPIO interrupt A*/
    .long   GPIO_INTB_IRQHandler                            /* GPIO interrupt B*/
    .long   PIN_INT0_IRQHandler                             /* Pin interrupt 0 or pattern match engine slice 0*/
    .long   PIN_INT1_IRQHandler                             /* Pin interrupt 1 or pattern match engine slice 1*/
    .long   PIN_INT2_IRQHandler                             /* Pin interrupt 2 or pattern match engine slice 2*/
    .long   PIN_INT3_IRQHandler                             /* Pin interrupt 3 or pattern match engine slice 3*/
    .long   UTICK_IRQHandler                                /* Micro-tick Timer (UTICK)*/
    .long   MRT_IRQHandler                                  /* Multi-Rate Timer (MRT). Global MRT interrupts*/
    .long   CTIMER0_IRQHandler                              /* Standard counter/timer CTIMER0*/
    .long   CTIMER1_IRQHandler                              /* Standard counter/timer CTIMER1*/
    .long   SCT0_IRQHandler                                 /* SCTimer/PWM*/
    .long   CTIMER3_IRQHandler                              /* Standard counter/timer CTIMER3*/
    .long   FLEXCOMM0_IRQHandler                            /* Flexcomm Interface 0 (USART, SPI, I2C, I2S)*/
    .long   FLEXCOMM1_IRQHandler                            /* Flexcomm Interface 1 (USART, SPI, I2C, I2S)*/
    .long   FLEXCOMM2_IRQHandler                            /* Flexcomm Interface 2 (USART, SPI, I2C, I2S)*/
    .long   FLEXCOMM3_IRQHandler                            /* Flexcomm Interface 3 (USART, SPI, I2C, I2S)*/
    .long   Reserved34_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved35_IRQHandler                           /* Reserved interrupt*/
    .long   FLEXCOMM14_IRQHandler                           /* Flexcomm Interface 14 (USART, SPI, I2C, I2S)*/
    .long   Reserved37_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved38_IRQHandler                           /* Reserved interrupt*/
    .long   GFMRT_IRQHandler                                /* Free Multi-rate timer (GFMRT). Global MRT interrupts*/
    .long   Reserved40_IRQHandler                           /* Reserved interrupt*/
    .long   DMIC_IRQHandler                                 /* Digital microphone (DMIC) and DMIC subsystem*/
    .long   WKDEEPSLEEP_IRQHandler                          /* Wake-up from deep sleep*/
    .long   HYPERVISOR_IRQHandler                           /* Hypervisor service software interrupt*/
    .long   SECUREVIOLATION_IRQHandler                      /* Secure violation*/
    .long   HWVAD_IRQHandler                                /* Hardware Voice Activity Detector*/
    .long   Reserved46_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved47_IRQHandler                           /* Reserved interrupt*/
    .long   RTC_IRQHandler                                  /* RTC alarm and wake-up*/
    .long   Reserved49_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved50_IRQHandler                           /* Reserved interrupt*/
    .long   PIN_INT4_IRQHandler                             /* Pin interrupt 4 or pattern match engine slice 4*/
    .long   PIN_INT5_IRQHandler                             /* Pin interrupt 5 or pattern match engine slice 5*/
    .long   PIN_INT6_IRQHandler                             /* Pin interrupt 6 or pattern match engine slice 6*/
    .long   PIN_INT7_IRQHandler                             /* Pin interrupt 7 or pattern match engine slice 7*/
    .long   CTIMER2_IRQHandler                              /* Standard counter/timer CTIMER2*/
    .long   CTIMER4_IRQHandler                              /* Standard counter/timer CTIMER4*/
    .long   OS_EVENT_TIMER_IRQHandler                       /* OS event timer 0*/
    .long   FLEXSPI_IRQHandler                              /* FLEXSPI interface*/
    .long   Reserved59_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved60_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved61_IRQHandler                           /* Reserved interrupt*/
    .long   SDIO_IRQHandler                                 /* The secure digital interface*/
    .long   SGPIO_INTA_IRQHandler                           /* Secure GPIO interrupt A*/
    .long   SGPIO_INTB_IRQHandler                           /* Secure GPIO interrupt B*/
    .long   Reserved65_IRQHandler                           /* Reserved interrupt*/
    .long   USB_IRQHandler                                  /* High-speed USB device/host*/
    .long   Reserved67_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved68_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved69_IRQHandler                           /* Reserved interrupt*/
    .long   DMA1_IRQHandler                                 /* DMA controller 1 (non-secure or HiFi 4 DMA)*/
    .long   PUF_IRQHandler                                  /* Physical Unclonable Function*/
    .long   POWERQUAD_IRQHandler                            /* PowerQuad math coprocessor*/
    .long   Reserved73_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved74_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved75_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved76_IRQHandler                           /* Reserved interrupt*/
    .long   LCD_IRQHandler                                  /* LCDIC*/
    .long   CAPTIMER_IRQHandler                             /* Capture timer*/
    .long   Reserved79_IRQHandler                           /* Reserved interrupt*/
    .long   W2MWKUP_DONE0_IRQHandler                        /* Wi-Fi to MCU, wakeup done 0*/
    .long   W2MWKUP_DONE1_IRQHandler                        /* Wi-Fi to MCU, wakeup done 1*/
    .long   W2MWKUP_DONE2_IRQHandler                        /* Wi-Fi to MCU, wakeup done 2*/
    .long   W2MWKUP_DONE3_IRQHandler                        /* Wi-Fi to MCU, wakeup done 3*/
    .long   W2MWKUP_DONE4_IRQHandler                        /* Wi-Fi to MCU, wakeup done 4*/
    .long   W2MWKUP_DONE5_IRQHandler                        /* Wi-Fi to MCU, wakeup done 5*/
    .long   W2MWKUP_DONE6_IRQHandler                        /* Wi-Fi to MCU, wakeup done 6*/
    .long   W2MWKUP_DONE7_IRQHandler                        /* Wi-Fi to MCU, wakeup done 7*/
    .long   W2MWKUP0_IRQHandler                             /* Wi-Fi to MCU, wakeup signal 0*/
    .long   W2MWKUP1_IRQHandler                             /* Wi-Fi to MCU, wakueup signal 1*/
    .long   WL_MCI_INT0_IRQHandler                          /* Wi-Fi to MCU interrupt 0*/
    .long   WL_MCI_INT1_IRQHandler                          /* Reserved for Wi-Fi to MCU*/
    .long   WL_MCI_INT2_IRQHandler                          /* Reserved for Wi-Fi to MCU*/
    .long   WL_MCI_INT3_IRQHandler                          /* Reserved for Wi-Fi to MCU*/
    .long   WL_MCI_INT4_IRQHandler                          /* Reserved for Wi-Fi to MCU*/
    .long   WL_MCI_INT5_IRQHandler                          /* Reserved for Wi-Fi to MCU*/
    .long   WL_MCI_INT6_IRQHandler                          /* Reserved for Wi-Fi to MCU*/
    .long   WL_MCI_INT7_IRQHandler                          /* Reserved for Wi-Fi to MCU*/
    .long   B2MWKUP_DONE0_IRQHandler                        /* Bluetooth LE/802.15.4 radio to MCU, wakeup done 0*/
    .long   B2MWKUP_DONE1_IRQHandler                        /* Bluetooth LE/802.15.4 radio to MCU, wakeup done 1*/
    .long   B2MWKUP_DONE2_IRQHandler                        /* Bluetooth LE/802.15.4 radio to MCU, wakeup done 2*/
    .long   B2MWKUP_DONE3_IRQHandler                        /* Bluetooth LE/802.15.4 radio to MCU, wakeup done 3*/
    .long   B2MWKUP_DONE4_IRQHandler                        /* Bluetooth LE/802.15.4 radio to MCU, wakeup done 4*/
    .long   B2MWKUP_DONE5_IRQHandler                        /* Bluetooth LE/802.15.4 radio to MCU, wakeup done 5*/
    .long   B2MWKUP_DONE6_IRQHandler                        /* Bluetooth LE/802.15.4 radio to MCU, wakeup done 6*/
    .long   B2MWKUP_DONE7_IRQHandler                        /* Bluetooth LE/802.15.4 radio to MCU, wakeup done 7*/
    .long   B2MWKUP0_IRQHandler                             /* Bluetooth LE/802.15.4 radio to MCU, wakeup signal 0*/
    .long   B2MWKUP1_IRQHandler                             /* Bluetooth LE/802.15.4 radio to MCU, wakeup signal 1*/
    .long   BLE_MCI_INT0_IRQHandler                         /* Bluetooth LE/802.15.4 radio to MCU interrupt 0*/
    .long   BLE_MCI_INT1_IRQHandler                         /* Reserved for Bluetooth LE/802.15.4 radio to MCU*/
    .long   BLE_MCI_INT2_IRQHandler                         /* Reserved for Bluetooth LE/802.15.4 radio to MCU*/
    .long   BLE_MCI_INT3_IRQHandler                         /* Reserved for Bluetooth LE/802.15.4 radio to MCU*/
    .long   BLE_MCI_INT4_IRQHandler                         /* Reserved for Bluetooth LE/802.15.4 radio to MCU*/
    .long   BLE_MCI_INT5_IRQHandler                         /* Reserved for Bluetooth LE/802.15.4 radio to MCU*/
    .long   BLE_MCI_INT6_IRQHandler                         /* Reserved for Bluetooth LE/802.15.4 radio to MCU*/
    .long   BLE_MCI_INT7_IRQHandler                         /* Reserved for Bluetooth LE/802.15.4 radio to MCU*/
    .long   PIN0_INT_IRQHandler                             /* From AON GPIO*/
    .long   PIN1_INT_IRQHandler                             /* From AON GPIO*/
    .long   ELS_IRQHandler                                  /* EdgeLock subsystem (ELS)*/
    .long   ELS_GDET_IRQHandler                             /* ELS IRQ line for GDET error*/
    .long   ELS_GDET_UM_IRQHandler                          /* ELS un-gated latched error*/
    .long   PKC_INT_IRQHandler                              /* Public key crypto-processor (PKC) interrupt*/
    .long   PKC_ERR_IRQHandler                              /* PKC error*/
    .long   CDOG_INT_IRQHandler                             /* Code watch dog timmer interrupt*/
    .long   GAU_DAC_IRQHandler                              /* General analog unit (GAU) digital to analog converter (DAC)*/
    .long   GAU_ACOMP_WKUP_IRQHandler                       /* GAU analog comparator (ACOMP) wake-up*/
    .long   GAU_ACOMP_IRQHandler                            /* GAU analog comparator*/
    .long   GAU_ADC1_IRQHandler                             /* GAU analog to digital converter 1 (ADC1)*/
    .long   GAU_ADC0_IRQHandler                             /* GAU analog to digital converter 0 (ADC0)*/
    .long   USIM_IRQHandler                                 /* Universal subscriber identity module (USIM) interface*/
    .long   OTP_IRQHandler                                  /* One time programmable (OTP) memory interrupt*/
    .long   ENET_IRQHandler                                 /* Etheret interrupt*/
    .long   ENET_TIMER_IRQHandler                           /* Ethernet timer interrupt*/
    .long   PMIP_IRQHandler                                 /* Power management IP (PMIP)*/
    .long   PMIP_CHANGE_IRQHandler                          /* PMIP change from 1 to 0*/
    .long   ITRC_IRQHandler                                 /* Intrusion and tamper response controller (ITRC) interrupt request*/
    .long   Reserved136_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved137_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved138_IRQHandler                          /* Reserved interrupt*/
    .long   TRNG_IRQHandler                                 /* TRNG interrupt request*/
    .long   ACC_C_INT_IRQHandler                            /* AHB memory access checker - Cortex-M33 code bus*/
    .long   ACC_S_INT_IRQHandler                            /* AHB memory access checker - Cortex-M33 sys bus*/
    .long   WACC_IRQHandler                                 /* Wi-Fi accessed during power off*/
    .long   BACC_IRQHandler                                 /* Bluetooth LE/802.15.4 radio accessed during power off*/
    .long   GDMA_IRQHandler                                 /* General purpose direct memory access (GDMA) interrupt*/

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
    ldr     r0, =__StackLimit
    msr     msplim, r0
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

.LC0:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC0

#ifdef __STARTUP_INITIALIZE_RAMFUNCTION
/* ram_function must directly follow __data_end__ */
    ldr     r2, =__ram_function_start__
    ldr     r3, =__ram_function_end__

.LC1:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC1
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
    .weak UTICK_IRQHandler
    .type UTICK_IRQHandler, %function
UTICK_IRQHandler:
    ldr   r0,=UTICK_DriverIRQHandler
    bx    r0
    .size UTICK_IRQHandler, . - UTICK_IRQHandler

    .align 1
    .thumb_func
    .weak MRT_IRQHandler
    .type MRT_IRQHandler, %function
MRT_IRQHandler:
    ldr   r0,=MRT_DriverIRQHandler
    bx    r0
    .size MRT_IRQHandler, . - MRT_IRQHandler

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
    .weak Reserved34_IRQHandler
    .type Reserved34_IRQHandler, %function
Reserved34_IRQHandler:
    ldr   r0,=Reserved34_DriverIRQHandler
    bx    r0
    .size Reserved34_IRQHandler, . - Reserved34_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved35_IRQHandler
    .type Reserved35_IRQHandler, %function
Reserved35_IRQHandler:
    ldr   r0,=Reserved35_DriverIRQHandler
    bx    r0
    .size Reserved35_IRQHandler, . - Reserved35_IRQHandler

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
    .weak Reserved37_IRQHandler
    .type Reserved37_IRQHandler, %function
Reserved37_IRQHandler:
    ldr   r0,=Reserved37_DriverIRQHandler
    bx    r0
    .size Reserved37_IRQHandler, . - Reserved37_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved38_IRQHandler
    .type Reserved38_IRQHandler, %function
Reserved38_IRQHandler:
    ldr   r0,=Reserved38_DriverIRQHandler
    bx    r0
    .size Reserved38_IRQHandler, . - Reserved38_IRQHandler

    .align 1
    .thumb_func
    .weak GFMRT_IRQHandler
    .type GFMRT_IRQHandler, %function
GFMRT_IRQHandler:
    ldr   r0,=GFMRT_DriverIRQHandler
    bx    r0
    .size GFMRT_IRQHandler, . - GFMRT_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved40_IRQHandler
    .type Reserved40_IRQHandler, %function
Reserved40_IRQHandler:
    ldr   r0,=Reserved40_DriverIRQHandler
    bx    r0
    .size Reserved40_IRQHandler, . - Reserved40_IRQHandler

    .align 1
    .thumb_func
    .weak DMIC_IRQHandler
    .type DMIC_IRQHandler, %function
DMIC_IRQHandler:
    ldr   r0,=DMIC_DriverIRQHandler
    bx    r0
    .size DMIC_IRQHandler, . - DMIC_IRQHandler

    .align 1
    .thumb_func
    .weak WKDEEPSLEEP_IRQHandler
    .type WKDEEPSLEEP_IRQHandler, %function
WKDEEPSLEEP_IRQHandler:
    ldr   r0,=WKDEEPSLEEP_DriverIRQHandler
    bx    r0
    .size WKDEEPSLEEP_IRQHandler, . - WKDEEPSLEEP_IRQHandler

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
    .weak HWVAD_IRQHandler
    .type HWVAD_IRQHandler, %function
HWVAD_IRQHandler:
    ldr   r0,=HWVAD_DriverIRQHandler
    bx    r0
    .size HWVAD_IRQHandler, . - HWVAD_IRQHandler

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
    .weak Reserved47_IRQHandler
    .type Reserved47_IRQHandler, %function
Reserved47_IRQHandler:
    ldr   r0,=Reserved47_DriverIRQHandler
    bx    r0
    .size Reserved47_IRQHandler, . - Reserved47_IRQHandler

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
    .weak Reserved49_IRQHandler
    .type Reserved49_IRQHandler, %function
Reserved49_IRQHandler:
    ldr   r0,=Reserved49_DriverIRQHandler
    bx    r0
    .size Reserved49_IRQHandler, . - Reserved49_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved50_IRQHandler
    .type Reserved50_IRQHandler, %function
Reserved50_IRQHandler:
    ldr   r0,=Reserved50_DriverIRQHandler
    bx    r0
    .size Reserved50_IRQHandler, . - Reserved50_IRQHandler

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
    .weak OS_EVENT_TIMER_IRQHandler
    .type OS_EVENT_TIMER_IRQHandler, %function
OS_EVENT_TIMER_IRQHandler:
    ldr   r0,=OS_EVENT_TIMER_DriverIRQHandler
    bx    r0
    .size OS_EVENT_TIMER_IRQHandler, . - OS_EVENT_TIMER_IRQHandler

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
    .weak Reserved59_IRQHandler
    .type Reserved59_IRQHandler, %function
Reserved59_IRQHandler:
    ldr   r0,=Reserved59_DriverIRQHandler
    bx    r0
    .size Reserved59_IRQHandler, . - Reserved59_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved60_IRQHandler
    .type Reserved60_IRQHandler, %function
Reserved60_IRQHandler:
    ldr   r0,=Reserved60_DriverIRQHandler
    bx    r0
    .size Reserved60_IRQHandler, . - Reserved60_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved61_IRQHandler
    .type Reserved61_IRQHandler, %function
Reserved61_IRQHandler:
    ldr   r0,=Reserved61_DriverIRQHandler
    bx    r0
    .size Reserved61_IRQHandler, . - Reserved61_IRQHandler

    .align 1
    .thumb_func
    .weak SDIO_IRQHandler
    .type SDIO_IRQHandler, %function
SDIO_IRQHandler:
    ldr   r0,=SDIO_DriverIRQHandler
    bx    r0
    .size SDIO_IRQHandler, . - SDIO_IRQHandler

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
    .weak Reserved65_IRQHandler
    .type Reserved65_IRQHandler, %function
Reserved65_IRQHandler:
    ldr   r0,=Reserved65_DriverIRQHandler
    bx    r0
    .size Reserved65_IRQHandler, . - Reserved65_IRQHandler

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
    .weak Reserved67_IRQHandler
    .type Reserved67_IRQHandler, %function
Reserved67_IRQHandler:
    ldr   r0,=Reserved67_DriverIRQHandler
    bx    r0
    .size Reserved67_IRQHandler, . - Reserved67_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved68_IRQHandler
    .type Reserved68_IRQHandler, %function
Reserved68_IRQHandler:
    ldr   r0,=Reserved68_DriverIRQHandler
    bx    r0
    .size Reserved68_IRQHandler, . - Reserved68_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved69_IRQHandler
    .type Reserved69_IRQHandler, %function
Reserved69_IRQHandler:
    ldr   r0,=Reserved69_DriverIRQHandler
    bx    r0
    .size Reserved69_IRQHandler, . - Reserved69_IRQHandler

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
    .weak Reserved73_IRQHandler
    .type Reserved73_IRQHandler, %function
Reserved73_IRQHandler:
    ldr   r0,=Reserved73_DriverIRQHandler
    bx    r0
    .size Reserved73_IRQHandler, . - Reserved73_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved74_IRQHandler
    .type Reserved74_IRQHandler, %function
Reserved74_IRQHandler:
    ldr   r0,=Reserved74_DriverIRQHandler
    bx    r0
    .size Reserved74_IRQHandler, . - Reserved74_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved75_IRQHandler
    .type Reserved75_IRQHandler, %function
Reserved75_IRQHandler:
    ldr   r0,=Reserved75_DriverIRQHandler
    bx    r0
    .size Reserved75_IRQHandler, . - Reserved75_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved76_IRQHandler
    .type Reserved76_IRQHandler, %function
Reserved76_IRQHandler:
    ldr   r0,=Reserved76_DriverIRQHandler
    bx    r0
    .size Reserved76_IRQHandler, . - Reserved76_IRQHandler

    .align 1
    .thumb_func
    .weak LCD_IRQHandler
    .type LCD_IRQHandler, %function
LCD_IRQHandler:
    ldr   r0,=LCD_DriverIRQHandler
    bx    r0
    .size LCD_IRQHandler, . - LCD_IRQHandler

    .align 1
    .thumb_func
    .weak CAPTIMER_IRQHandler
    .type CAPTIMER_IRQHandler, %function
CAPTIMER_IRQHandler:
    ldr   r0,=CAPTIMER_DriverIRQHandler
    bx    r0
    .size CAPTIMER_IRQHandler, . - CAPTIMER_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved79_IRQHandler
    .type Reserved79_IRQHandler, %function
Reserved79_IRQHandler:
    ldr   r0,=Reserved79_DriverIRQHandler
    bx    r0
    .size Reserved79_IRQHandler, . - Reserved79_IRQHandler

    .align 1
    .thumb_func
    .weak W2MWKUP_DONE0_IRQHandler
    .type W2MWKUP_DONE0_IRQHandler, %function
W2MWKUP_DONE0_IRQHandler:
    ldr   r0,=W2MWKUP_DONE0_DriverIRQHandler
    bx    r0
    .size W2MWKUP_DONE0_IRQHandler, . - W2MWKUP_DONE0_IRQHandler

    .align 1
    .thumb_func
    .weak W2MWKUP_DONE1_IRQHandler
    .type W2MWKUP_DONE1_IRQHandler, %function
W2MWKUP_DONE1_IRQHandler:
    ldr   r0,=W2MWKUP_DONE1_DriverIRQHandler
    bx    r0
    .size W2MWKUP_DONE1_IRQHandler, . - W2MWKUP_DONE1_IRQHandler

    .align 1
    .thumb_func
    .weak W2MWKUP_DONE2_IRQHandler
    .type W2MWKUP_DONE2_IRQHandler, %function
W2MWKUP_DONE2_IRQHandler:
    ldr   r0,=W2MWKUP_DONE2_DriverIRQHandler
    bx    r0
    .size W2MWKUP_DONE2_IRQHandler, . - W2MWKUP_DONE2_IRQHandler

    .align 1
    .thumb_func
    .weak W2MWKUP_DONE3_IRQHandler
    .type W2MWKUP_DONE3_IRQHandler, %function
W2MWKUP_DONE3_IRQHandler:
    ldr   r0,=W2MWKUP_DONE3_DriverIRQHandler
    bx    r0
    .size W2MWKUP_DONE3_IRQHandler, . - W2MWKUP_DONE3_IRQHandler

    .align 1
    .thumb_func
    .weak W2MWKUP_DONE4_IRQHandler
    .type W2MWKUP_DONE4_IRQHandler, %function
W2MWKUP_DONE4_IRQHandler:
    ldr   r0,=W2MWKUP_DONE4_DriverIRQHandler
    bx    r0
    .size W2MWKUP_DONE4_IRQHandler, . - W2MWKUP_DONE4_IRQHandler

    .align 1
    .thumb_func
    .weak W2MWKUP_DONE5_IRQHandler
    .type W2MWKUP_DONE5_IRQHandler, %function
W2MWKUP_DONE5_IRQHandler:
    ldr   r0,=W2MWKUP_DONE5_DriverIRQHandler
    bx    r0
    .size W2MWKUP_DONE5_IRQHandler, . - W2MWKUP_DONE5_IRQHandler

    .align 1
    .thumb_func
    .weak W2MWKUP_DONE6_IRQHandler
    .type W2MWKUP_DONE6_IRQHandler, %function
W2MWKUP_DONE6_IRQHandler:
    ldr   r0,=W2MWKUP_DONE6_DriverIRQHandler
    bx    r0
    .size W2MWKUP_DONE6_IRQHandler, . - W2MWKUP_DONE6_IRQHandler

    .align 1
    .thumb_func
    .weak W2MWKUP_DONE7_IRQHandler
    .type W2MWKUP_DONE7_IRQHandler, %function
W2MWKUP_DONE7_IRQHandler:
    ldr   r0,=W2MWKUP_DONE7_DriverIRQHandler
    bx    r0
    .size W2MWKUP_DONE7_IRQHandler, . - W2MWKUP_DONE7_IRQHandler

    .align 1
    .thumb_func
    .weak W2MWKUP0_IRQHandler
    .type W2MWKUP0_IRQHandler, %function
W2MWKUP0_IRQHandler:
    ldr   r0,=W2MWKUP0_DriverIRQHandler
    bx    r0
    .size W2MWKUP0_IRQHandler, . - W2MWKUP0_IRQHandler

    .align 1
    .thumb_func
    .weak W2MWKUP1_IRQHandler
    .type W2MWKUP1_IRQHandler, %function
W2MWKUP1_IRQHandler:
    ldr   r0,=W2MWKUP1_DriverIRQHandler
    bx    r0
    .size W2MWKUP1_IRQHandler, . - W2MWKUP1_IRQHandler

    .align 1
    .thumb_func
    .weak WL_MCI_INT0_IRQHandler
    .type WL_MCI_INT0_IRQHandler, %function
WL_MCI_INT0_IRQHandler:
    ldr   r0,=WL_MCI_INT0_DriverIRQHandler
    bx    r0
    .size WL_MCI_INT0_IRQHandler, . - WL_MCI_INT0_IRQHandler

    .align 1
    .thumb_func
    .weak WL_MCI_INT1_IRQHandler
    .type WL_MCI_INT1_IRQHandler, %function
WL_MCI_INT1_IRQHandler:
    ldr   r0,=WL_MCI_INT1_DriverIRQHandler
    bx    r0
    .size WL_MCI_INT1_IRQHandler, . - WL_MCI_INT1_IRQHandler

    .align 1
    .thumb_func
    .weak WL_MCI_INT2_IRQHandler
    .type WL_MCI_INT2_IRQHandler, %function
WL_MCI_INT2_IRQHandler:
    ldr   r0,=WL_MCI_INT2_DriverIRQHandler
    bx    r0
    .size WL_MCI_INT2_IRQHandler, . - WL_MCI_INT2_IRQHandler

    .align 1
    .thumb_func
    .weak WL_MCI_INT3_IRQHandler
    .type WL_MCI_INT3_IRQHandler, %function
WL_MCI_INT3_IRQHandler:
    ldr   r0,=WL_MCI_INT3_DriverIRQHandler
    bx    r0
    .size WL_MCI_INT3_IRQHandler, . - WL_MCI_INT3_IRQHandler

    .align 1
    .thumb_func
    .weak WL_MCI_INT4_IRQHandler
    .type WL_MCI_INT4_IRQHandler, %function
WL_MCI_INT4_IRQHandler:
    ldr   r0,=WL_MCI_INT4_DriverIRQHandler
    bx    r0
    .size WL_MCI_INT4_IRQHandler, . - WL_MCI_INT4_IRQHandler

    .align 1
    .thumb_func
    .weak WL_MCI_INT5_IRQHandler
    .type WL_MCI_INT5_IRQHandler, %function
WL_MCI_INT5_IRQHandler:
    ldr   r0,=WL_MCI_INT5_DriverIRQHandler
    bx    r0
    .size WL_MCI_INT5_IRQHandler, . - WL_MCI_INT5_IRQHandler

    .align 1
    .thumb_func
    .weak WL_MCI_INT6_IRQHandler
    .type WL_MCI_INT6_IRQHandler, %function
WL_MCI_INT6_IRQHandler:
    ldr   r0,=WL_MCI_INT6_DriverIRQHandler
    bx    r0
    .size WL_MCI_INT6_IRQHandler, . - WL_MCI_INT6_IRQHandler

    .align 1
    .thumb_func
    .weak WL_MCI_INT7_IRQHandler
    .type WL_MCI_INT7_IRQHandler, %function
WL_MCI_INT7_IRQHandler:
    ldr   r0,=WL_MCI_INT7_DriverIRQHandler
    bx    r0
    .size WL_MCI_INT7_IRQHandler, . - WL_MCI_INT7_IRQHandler

    .align 1
    .thumb_func
    .weak B2MWKUP_DONE0_IRQHandler
    .type B2MWKUP_DONE0_IRQHandler, %function
B2MWKUP_DONE0_IRQHandler:
    ldr   r0,=B2MWKUP_DONE0_DriverIRQHandler
    bx    r0
    .size B2MWKUP_DONE0_IRQHandler, . - B2MWKUP_DONE0_IRQHandler

    .align 1
    .thumb_func
    .weak B2MWKUP_DONE1_IRQHandler
    .type B2MWKUP_DONE1_IRQHandler, %function
B2MWKUP_DONE1_IRQHandler:
    ldr   r0,=B2MWKUP_DONE1_DriverIRQHandler
    bx    r0
    .size B2MWKUP_DONE1_IRQHandler, . - B2MWKUP_DONE1_IRQHandler

    .align 1
    .thumb_func
    .weak B2MWKUP_DONE2_IRQHandler
    .type B2MWKUP_DONE2_IRQHandler, %function
B2MWKUP_DONE2_IRQHandler:
    ldr   r0,=B2MWKUP_DONE2_DriverIRQHandler
    bx    r0
    .size B2MWKUP_DONE2_IRQHandler, . - B2MWKUP_DONE2_IRQHandler

    .align 1
    .thumb_func
    .weak B2MWKUP_DONE3_IRQHandler
    .type B2MWKUP_DONE3_IRQHandler, %function
B2MWKUP_DONE3_IRQHandler:
    ldr   r0,=B2MWKUP_DONE3_DriverIRQHandler
    bx    r0
    .size B2MWKUP_DONE3_IRQHandler, . - B2MWKUP_DONE3_IRQHandler

    .align 1
    .thumb_func
    .weak B2MWKUP_DONE4_IRQHandler
    .type B2MWKUP_DONE4_IRQHandler, %function
B2MWKUP_DONE4_IRQHandler:
    ldr   r0,=B2MWKUP_DONE4_DriverIRQHandler
    bx    r0
    .size B2MWKUP_DONE4_IRQHandler, . - B2MWKUP_DONE4_IRQHandler

    .align 1
    .thumb_func
    .weak B2MWKUP_DONE5_IRQHandler
    .type B2MWKUP_DONE5_IRQHandler, %function
B2MWKUP_DONE5_IRQHandler:
    ldr   r0,=B2MWKUP_DONE5_DriverIRQHandler
    bx    r0
    .size B2MWKUP_DONE5_IRQHandler, . - B2MWKUP_DONE5_IRQHandler

    .align 1
    .thumb_func
    .weak B2MWKUP_DONE6_IRQHandler
    .type B2MWKUP_DONE6_IRQHandler, %function
B2MWKUP_DONE6_IRQHandler:
    ldr   r0,=B2MWKUP_DONE6_DriverIRQHandler
    bx    r0
    .size B2MWKUP_DONE6_IRQHandler, . - B2MWKUP_DONE6_IRQHandler

    .align 1
    .thumb_func
    .weak B2MWKUP_DONE7_IRQHandler
    .type B2MWKUP_DONE7_IRQHandler, %function
B2MWKUP_DONE7_IRQHandler:
    ldr   r0,=B2MWKUP_DONE7_DriverIRQHandler
    bx    r0
    .size B2MWKUP_DONE7_IRQHandler, . - B2MWKUP_DONE7_IRQHandler

    .align 1
    .thumb_func
    .weak B2MWKUP0_IRQHandler
    .type B2MWKUP0_IRQHandler, %function
B2MWKUP0_IRQHandler:
    ldr   r0,=B2MWKUP0_DriverIRQHandler
    bx    r0
    .size B2MWKUP0_IRQHandler, . - B2MWKUP0_IRQHandler

    .align 1
    .thumb_func
    .weak B2MWKUP1_IRQHandler
    .type B2MWKUP1_IRQHandler, %function
B2MWKUP1_IRQHandler:
    ldr   r0,=B2MWKUP1_DriverIRQHandler
    bx    r0
    .size B2MWKUP1_IRQHandler, . - B2MWKUP1_IRQHandler

    .align 1
    .thumb_func
    .weak BLE_MCI_INT0_IRQHandler
    .type BLE_MCI_INT0_IRQHandler, %function
BLE_MCI_INT0_IRQHandler:
    ldr   r0,=BLE_MCI_INT0_DriverIRQHandler
    bx    r0
    .size BLE_MCI_INT0_IRQHandler, . - BLE_MCI_INT0_IRQHandler

    .align 1
    .thumb_func
    .weak BLE_MCI_INT1_IRQHandler
    .type BLE_MCI_INT1_IRQHandler, %function
BLE_MCI_INT1_IRQHandler:
    ldr   r0,=BLE_MCI_INT1_DriverIRQHandler
    bx    r0
    .size BLE_MCI_INT1_IRQHandler, . - BLE_MCI_INT1_IRQHandler

    .align 1
    .thumb_func
    .weak BLE_MCI_INT2_IRQHandler
    .type BLE_MCI_INT2_IRQHandler, %function
BLE_MCI_INT2_IRQHandler:
    ldr   r0,=BLE_MCI_INT2_DriverIRQHandler
    bx    r0
    .size BLE_MCI_INT2_IRQHandler, . - BLE_MCI_INT2_IRQHandler

    .align 1
    .thumb_func
    .weak BLE_MCI_INT3_IRQHandler
    .type BLE_MCI_INT3_IRQHandler, %function
BLE_MCI_INT3_IRQHandler:
    ldr   r0,=BLE_MCI_INT3_DriverIRQHandler
    bx    r0
    .size BLE_MCI_INT3_IRQHandler, . - BLE_MCI_INT3_IRQHandler

    .align 1
    .thumb_func
    .weak BLE_MCI_INT4_IRQHandler
    .type BLE_MCI_INT4_IRQHandler, %function
BLE_MCI_INT4_IRQHandler:
    ldr   r0,=BLE_MCI_INT4_DriverIRQHandler
    bx    r0
    .size BLE_MCI_INT4_IRQHandler, . - BLE_MCI_INT4_IRQHandler

    .align 1
    .thumb_func
    .weak BLE_MCI_INT5_IRQHandler
    .type BLE_MCI_INT5_IRQHandler, %function
BLE_MCI_INT5_IRQHandler:
    ldr   r0,=BLE_MCI_INT5_DriverIRQHandler
    bx    r0
    .size BLE_MCI_INT5_IRQHandler, . - BLE_MCI_INT5_IRQHandler

    .align 1
    .thumb_func
    .weak BLE_MCI_INT6_IRQHandler
    .type BLE_MCI_INT6_IRQHandler, %function
BLE_MCI_INT6_IRQHandler:
    ldr   r0,=BLE_MCI_INT6_DriverIRQHandler
    bx    r0
    .size BLE_MCI_INT6_IRQHandler, . - BLE_MCI_INT6_IRQHandler

    .align 1
    .thumb_func
    .weak BLE_MCI_INT7_IRQHandler
    .type BLE_MCI_INT7_IRQHandler, %function
BLE_MCI_INT7_IRQHandler:
    ldr   r0,=BLE_MCI_INT7_DriverIRQHandler
    bx    r0
    .size BLE_MCI_INT7_IRQHandler, . - BLE_MCI_INT7_IRQHandler

    .align 1
    .thumb_func
    .weak PIN0_INT_IRQHandler
    .type PIN0_INT_IRQHandler, %function
PIN0_INT_IRQHandler:
    ldr   r0,=PIN0_INT_DriverIRQHandler
    bx    r0
    .size PIN0_INT_IRQHandler, . - PIN0_INT_IRQHandler

    .align 1
    .thumb_func
    .weak PIN1_INT_IRQHandler
    .type PIN1_INT_IRQHandler, %function
PIN1_INT_IRQHandler:
    ldr   r0,=PIN1_INT_DriverIRQHandler
    bx    r0
    .size PIN1_INT_IRQHandler, . - PIN1_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ELS_IRQHandler
    .type ELS_IRQHandler, %function
ELS_IRQHandler:
    ldr   r0,=ELS_DriverIRQHandler
    bx    r0
    .size ELS_IRQHandler, . - ELS_IRQHandler

    .align 1
    .thumb_func
    .weak ELS_GDET_IRQHandler
    .type ELS_GDET_IRQHandler, %function
ELS_GDET_IRQHandler:
    ldr   r0,=ELS_GDET_DriverIRQHandler
    bx    r0
    .size ELS_GDET_IRQHandler, . - ELS_GDET_IRQHandler

    .align 1
    .thumb_func
    .weak ELS_GDET_UM_IRQHandler
    .type ELS_GDET_UM_IRQHandler, %function
ELS_GDET_UM_IRQHandler:
    ldr   r0,=ELS_GDET_UM_DriverIRQHandler
    bx    r0
    .size ELS_GDET_UM_IRQHandler, . - ELS_GDET_UM_IRQHandler

    .align 1
    .thumb_func
    .weak PKC_INT_IRQHandler
    .type PKC_INT_IRQHandler, %function
PKC_INT_IRQHandler:
    ldr   r0,=PKC_INT_DriverIRQHandler
    bx    r0
    .size PKC_INT_IRQHandler, . - PKC_INT_IRQHandler

    .align 1
    .thumb_func
    .weak PKC_ERR_IRQHandler
    .type PKC_ERR_IRQHandler, %function
PKC_ERR_IRQHandler:
    ldr   r0,=PKC_ERR_DriverIRQHandler
    bx    r0
    .size PKC_ERR_IRQHandler, . - PKC_ERR_IRQHandler

    .align 1
    .thumb_func
    .weak CDOG_INT_IRQHandler
    .type CDOG_INT_IRQHandler, %function
CDOG_INT_IRQHandler:
    ldr   r0,=CDOG_INT_DriverIRQHandler
    bx    r0
    .size CDOG_INT_IRQHandler, . - CDOG_INT_IRQHandler

    .align 1
    .thumb_func
    .weak GAU_DAC_IRQHandler
    .type GAU_DAC_IRQHandler, %function
GAU_DAC_IRQHandler:
    ldr   r0,=GAU_DAC_DriverIRQHandler
    bx    r0
    .size GAU_DAC_IRQHandler, . - GAU_DAC_IRQHandler

    .align 1
    .thumb_func
    .weak GAU_ACOMP_WKUP_IRQHandler
    .type GAU_ACOMP_WKUP_IRQHandler, %function
GAU_ACOMP_WKUP_IRQHandler:
    ldr   r0,=GAU_ACOMP_WKUP_DriverIRQHandler
    bx    r0
    .size GAU_ACOMP_WKUP_IRQHandler, . - GAU_ACOMP_WKUP_IRQHandler

    .align 1
    .thumb_func
    .weak GAU_ACOMP_IRQHandler
    .type GAU_ACOMP_IRQHandler, %function
GAU_ACOMP_IRQHandler:
    ldr   r0,=GAU_ACOMP_DriverIRQHandler
    bx    r0
    .size GAU_ACOMP_IRQHandler, . - GAU_ACOMP_IRQHandler

    .align 1
    .thumb_func
    .weak GAU_ADC1_IRQHandler
    .type GAU_ADC1_IRQHandler, %function
GAU_ADC1_IRQHandler:
    ldr   r0,=GAU_ADC1_DriverIRQHandler
    bx    r0
    .size GAU_ADC1_IRQHandler, . - GAU_ADC1_IRQHandler

    .align 1
    .thumb_func
    .weak GAU_ADC0_IRQHandler
    .type GAU_ADC0_IRQHandler, %function
GAU_ADC0_IRQHandler:
    ldr   r0,=GAU_ADC0_DriverIRQHandler
    bx    r0
    .size GAU_ADC0_IRQHandler, . - GAU_ADC0_IRQHandler

    .align 1
    .thumb_func
    .weak USIM_IRQHandler
    .type USIM_IRQHandler, %function
USIM_IRQHandler:
    ldr   r0,=USIM_DriverIRQHandler
    bx    r0
    .size USIM_IRQHandler, . - USIM_IRQHandler

    .align 1
    .thumb_func
    .weak OTP_IRQHandler
    .type OTP_IRQHandler, %function
OTP_IRQHandler:
    ldr   r0,=OTP_DriverIRQHandler
    bx    r0
    .size OTP_IRQHandler, . - OTP_IRQHandler

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
    .weak ENET_TIMER_IRQHandler
    .type ENET_TIMER_IRQHandler, %function
ENET_TIMER_IRQHandler:
    ldr   r0,=ENET_TIMER_DriverIRQHandler
    bx    r0
    .size ENET_TIMER_IRQHandler, . - ENET_TIMER_IRQHandler

    .align 1
    .thumb_func
    .weak PMIP_IRQHandler
    .type PMIP_IRQHandler, %function
PMIP_IRQHandler:
    ldr   r0,=PMIP_DriverIRQHandler
    bx    r0
    .size PMIP_IRQHandler, . - PMIP_IRQHandler

    .align 1
    .thumb_func
    .weak PMIP_CHANGE_IRQHandler
    .type PMIP_CHANGE_IRQHandler, %function
PMIP_CHANGE_IRQHandler:
    ldr   r0,=PMIP_CHANGE_DriverIRQHandler
    bx    r0
    .size PMIP_CHANGE_IRQHandler, . - PMIP_CHANGE_IRQHandler

    .align 1
    .thumb_func
    .weak ITRC_IRQHandler
    .type ITRC_IRQHandler, %function
ITRC_IRQHandler:
    ldr   r0,=ITRC_DriverIRQHandler
    bx    r0
    .size ITRC_IRQHandler, . - ITRC_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved136_IRQHandler
    .type Reserved136_IRQHandler, %function
Reserved136_IRQHandler:
    ldr   r0,=Reserved136_DriverIRQHandler
    bx    r0
    .size Reserved136_IRQHandler, . - Reserved136_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved137_IRQHandler
    .type Reserved137_IRQHandler, %function
Reserved137_IRQHandler:
    ldr   r0,=Reserved137_DriverIRQHandler
    bx    r0
    .size Reserved137_IRQHandler, . - Reserved137_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved138_IRQHandler
    .type Reserved138_IRQHandler, %function
Reserved138_IRQHandler:
    ldr   r0,=Reserved138_DriverIRQHandler
    bx    r0
    .size Reserved138_IRQHandler, . - Reserved138_IRQHandler

    .align 1
    .thumb_func
    .weak TRNG_IRQHandler
    .type TRNG_IRQHandler, %function
TRNG_IRQHandler:
    ldr   r0,=TRNG_DriverIRQHandler
    bx    r0
    .size TRNG_IRQHandler, . - TRNG_IRQHandler

    .align 1
    .thumb_func
    .weak ACC_C_INT_IRQHandler
    .type ACC_C_INT_IRQHandler, %function
ACC_C_INT_IRQHandler:
    ldr   r0,=ACC_C_INT_DriverIRQHandler
    bx    r0
    .size ACC_C_INT_IRQHandler, . - ACC_C_INT_IRQHandler

    .align 1
    .thumb_func
    .weak ACC_S_INT_IRQHandler
    .type ACC_S_INT_IRQHandler, %function
ACC_S_INT_IRQHandler:
    ldr   r0,=ACC_S_INT_DriverIRQHandler
    bx    r0
    .size ACC_S_INT_IRQHandler, . - ACC_S_INT_IRQHandler

    .align 1
    .thumb_func
    .weak WACC_IRQHandler
    .type WACC_IRQHandler, %function
WACC_IRQHandler:
    ldr   r0,=WACC_DriverIRQHandler
    bx    r0
    .size WACC_IRQHandler, . - WACC_IRQHandler

    .align 1
    .thumb_func
    .weak BACC_IRQHandler
    .type BACC_IRQHandler, %function
BACC_IRQHandler:
    ldr   r0,=BACC_DriverIRQHandler
    bx    r0
    .size BACC_IRQHandler, . - BACC_IRQHandler

    .align 1
    .thumb_func
    .weak GDMA_IRQHandler
    .type GDMA_IRQHandler, %function
GDMA_IRQHandler:
    ldr   r0,=GDMA_DriverIRQHandler
    bx    r0
    .size GDMA_IRQHandler, . - GDMA_IRQHandler


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
    def_irq_handler    WDT0_DriverIRQHandler
    def_irq_handler    DMA0_DriverIRQHandler
    def_irq_handler    GPIO_INTA_DriverIRQHandler
    def_irq_handler    GPIO_INTB_DriverIRQHandler
    def_irq_handler    PIN_INT0_DriverIRQHandler
    def_irq_handler    PIN_INT1_DriverIRQHandler
    def_irq_handler    PIN_INT2_DriverIRQHandler
    def_irq_handler    PIN_INT3_DriverIRQHandler
    def_irq_handler    UTICK_DriverIRQHandler
    def_irq_handler    MRT_DriverIRQHandler
    def_irq_handler    CTIMER0_DriverIRQHandler
    def_irq_handler    CTIMER1_DriverIRQHandler
    def_irq_handler    SCT0_DriverIRQHandler
    def_irq_handler    CTIMER3_DriverIRQHandler
    def_irq_handler    FLEXCOMM0_DriverIRQHandler
    def_irq_handler    FLEXCOMM1_DriverIRQHandler
    def_irq_handler    FLEXCOMM2_DriverIRQHandler
    def_irq_handler    FLEXCOMM3_DriverIRQHandler
    def_irq_handler    Reserved34_DriverIRQHandler
    def_irq_handler    Reserved35_DriverIRQHandler
    def_irq_handler    FLEXCOMM14_DriverIRQHandler
    def_irq_handler    Reserved37_DriverIRQHandler
    def_irq_handler    Reserved38_DriverIRQHandler
    def_irq_handler    GFMRT_DriverIRQHandler
    def_irq_handler    Reserved40_DriverIRQHandler
    def_irq_handler    DMIC_DriverIRQHandler
    def_irq_handler    WKDEEPSLEEP_DriverIRQHandler
    def_irq_handler    HYPERVISOR_DriverIRQHandler
    def_irq_handler    SECUREVIOLATION_DriverIRQHandler
    def_irq_handler    HWVAD_DriverIRQHandler
    def_irq_handler    Reserved46_DriverIRQHandler
    def_irq_handler    Reserved47_DriverIRQHandler
    def_irq_handler    RTC_DriverIRQHandler
    def_irq_handler    Reserved49_DriverIRQHandler
    def_irq_handler    Reserved50_DriverIRQHandler
    def_irq_handler    PIN_INT4_DriverIRQHandler
    def_irq_handler    PIN_INT5_DriverIRQHandler
    def_irq_handler    PIN_INT6_DriverIRQHandler
    def_irq_handler    PIN_INT7_DriverIRQHandler
    def_irq_handler    CTIMER2_DriverIRQHandler
    def_irq_handler    CTIMER4_DriverIRQHandler
    def_irq_handler    OS_EVENT_TIMER_DriverIRQHandler
    def_irq_handler    FLEXSPI_DriverIRQHandler
    def_irq_handler    Reserved59_DriverIRQHandler
    def_irq_handler    Reserved60_DriverIRQHandler
    def_irq_handler    Reserved61_DriverIRQHandler
    def_irq_handler    SDIO_DriverIRQHandler
    def_irq_handler    SGPIO_INTA_DriverIRQHandler
    def_irq_handler    SGPIO_INTB_DriverIRQHandler
    def_irq_handler    Reserved65_DriverIRQHandler
    def_irq_handler    USB_DriverIRQHandler
    def_irq_handler    Reserved67_DriverIRQHandler
    def_irq_handler    Reserved68_DriverIRQHandler
    def_irq_handler    Reserved69_DriverIRQHandler
    def_irq_handler    DMA1_DriverIRQHandler
    def_irq_handler    PUF_DriverIRQHandler
    def_irq_handler    POWERQUAD_DriverIRQHandler
    def_irq_handler    Reserved73_DriverIRQHandler
    def_irq_handler    Reserved74_DriverIRQHandler
    def_irq_handler    Reserved75_DriverIRQHandler
    def_irq_handler    Reserved76_DriverIRQHandler
    def_irq_handler    LCD_DriverIRQHandler
    def_irq_handler    CAPTIMER_DriverIRQHandler
    def_irq_handler    Reserved79_DriverIRQHandler
    def_irq_handler    W2MWKUP_DONE0_DriverIRQHandler
    def_irq_handler    W2MWKUP_DONE1_DriverIRQHandler
    def_irq_handler    W2MWKUP_DONE2_DriverIRQHandler
    def_irq_handler    W2MWKUP_DONE3_DriverIRQHandler
    def_irq_handler    W2MWKUP_DONE4_DriverIRQHandler
    def_irq_handler    W2MWKUP_DONE5_DriverIRQHandler
    def_irq_handler    W2MWKUP_DONE6_DriverIRQHandler
    def_irq_handler    W2MWKUP_DONE7_DriverIRQHandler
    def_irq_handler    W2MWKUP0_DriverIRQHandler
    def_irq_handler    W2MWKUP1_DriverIRQHandler
    def_irq_handler    WL_MCI_INT0_DriverIRQHandler
    def_irq_handler    WL_MCI_INT1_DriverIRQHandler
    def_irq_handler    WL_MCI_INT2_DriverIRQHandler
    def_irq_handler    WL_MCI_INT3_DriverIRQHandler
    def_irq_handler    WL_MCI_INT4_DriverIRQHandler
    def_irq_handler    WL_MCI_INT5_DriverIRQHandler
    def_irq_handler    WL_MCI_INT6_DriverIRQHandler
    def_irq_handler    WL_MCI_INT7_DriverIRQHandler
    def_irq_handler    B2MWKUP_DONE0_DriverIRQHandler
    def_irq_handler    B2MWKUP_DONE1_DriverIRQHandler
    def_irq_handler    B2MWKUP_DONE2_DriverIRQHandler
    def_irq_handler    B2MWKUP_DONE3_DriverIRQHandler
    def_irq_handler    B2MWKUP_DONE4_DriverIRQHandler
    def_irq_handler    B2MWKUP_DONE5_DriverIRQHandler
    def_irq_handler    B2MWKUP_DONE6_DriverIRQHandler
    def_irq_handler    B2MWKUP_DONE7_DriverIRQHandler
    def_irq_handler    B2MWKUP0_DriverIRQHandler
    def_irq_handler    B2MWKUP1_DriverIRQHandler
    def_irq_handler    BLE_MCI_INT0_DriverIRQHandler
    def_irq_handler    BLE_MCI_INT1_DriverIRQHandler
    def_irq_handler    BLE_MCI_INT2_DriverIRQHandler
    def_irq_handler    BLE_MCI_INT3_DriverIRQHandler
    def_irq_handler    BLE_MCI_INT4_DriverIRQHandler
    def_irq_handler    BLE_MCI_INT5_DriverIRQHandler
    def_irq_handler    BLE_MCI_INT6_DriverIRQHandler
    def_irq_handler    BLE_MCI_INT7_DriverIRQHandler
    def_irq_handler    PIN0_INT_DriverIRQHandler
    def_irq_handler    PIN1_INT_DriverIRQHandler
    def_irq_handler    ELS_DriverIRQHandler
    def_irq_handler    ELS_GDET_DriverIRQHandler
    def_irq_handler    ELS_GDET_UM_DriverIRQHandler
    def_irq_handler    PKC_INT_DriverIRQHandler
    def_irq_handler    PKC_ERR_DriverIRQHandler
    def_irq_handler    CDOG_INT_DriverIRQHandler
    def_irq_handler    GAU_DAC_DriverIRQHandler
    def_irq_handler    GAU_ACOMP_WKUP_DriverIRQHandler
    def_irq_handler    GAU_ACOMP_DriverIRQHandler
    def_irq_handler    GAU_ADC1_DriverIRQHandler
    def_irq_handler    GAU_ADC0_DriverIRQHandler
    def_irq_handler    USIM_DriverIRQHandler
    def_irq_handler    OTP_DriverIRQHandler
    def_irq_handler    ENET_DriverIRQHandler
    def_irq_handler    ENET_TIMER_DriverIRQHandler
    def_irq_handler    PMIP_DriverIRQHandler
    def_irq_handler    PMIP_CHANGE_DriverIRQHandler
    def_irq_handler    ITRC_DriverIRQHandler
    def_irq_handler    Reserved136_DriverIRQHandler
    def_irq_handler    Reserved137_DriverIRQHandler
    def_irq_handler    Reserved138_DriverIRQHandler
    def_irq_handler    TRNG_DriverIRQHandler
    def_irq_handler    ACC_C_INT_DriverIRQHandler
    def_irq_handler    ACC_S_INT_DriverIRQHandler
    def_irq_handler    WACC_DriverIRQHandler
    def_irq_handler    BACC_DriverIRQHandler
    def_irq_handler    GDMA_DriverIRQHandler

    .end
