/* ------------------------------------------------------------------------- */
/*  @file:    startup_MIMXRT735S_cm33_core1.s                                */
/*  @purpose: CMSIS Cortex-M33 Core Device Startup File                      */
/*            MIMXRT735S_cm33_core1                                          */
/*  @version: 2.0                                                            */
/*  @date:    2024-5-28                                                      */
/*  @build:   b240626                                                        */
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

                                                            /* External Interrupts*/
    .long   Reserved16_IRQHandler                           /* Reserved interrupt 16*/
    .long   Reserved17_IRQHandler                           /* Reserved interrupt 17*/
    .long   Reserved18_IRQHandler                           /* Reserved interrupt 18*/
    .long   FRO2_IRQHandler                                 /* FRO: 300MHz FRO in VDD1 domain Async interrupt*/
    .long   GLIKEY4_IRQHandler                              /* GLIKEY: Interrupt*/
    .long   UTICK1_IRQHandler                               /* Micro-tick Timer*/
    .long   MRT1_IRQHandler                                 /* MRT: Ored Interrupt request*/
    .long   CTIMER5_IRQHandler                              /* CTIMER: Interrupt request*/
    .long   CTIMER6_IRQHandler                              /* CTIMER: Interrupt request*/
    .long   CTIMER7_IRQHandler                              /* CTIMER: Interrupt request*/
    .long   LPI2C15_IRQHandler                              /* LPI2C: Interrupt request*/
    .long   LP_FLEXCOMM17_IRQHandler                        /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM18_IRQHandler                        /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM19_IRQHandler                        /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM20_IRQHandler                        /* FLEXCOMM: Interrupt request*/
    .long   ADC_IRQHandler                                  /* ADC0: Interrupt request*/
    .long   SDADC_IRQHandler                                /* SDADC0: Interrupt request*/
    .long   GLIKEY1_IRQHandler                              /* GLIKEY: Interrupt*/
    .long   ACMP_IRQHandler                                 /* ACMP: interrupt request*/
    .long   PDM_EVENT_IRQHandler                            /* MIC: Interrupt request for read data or Error*/
    .long   HYPERVISOR_IRQHandler                           /* SECURE: Sense domain Hypervisor interrupt*/
    .long   SECURE_VIOLATION_IRQHandler                     /* SECURE: Sense domain Secure violation interrupt*/
    .long   PDM_HWVAD_EVENT_IRQHandler                      /* MIC: Hardware Voice Activity Detector interrupt or error interrupt*/
    .long   RTC1_ALARM_IRQHandler                           /* RTC: Alarm interrupt*/
    .long   RTC1_IRQHandler                                 /* RTC: wakeup interrupt to Sense domain*/
    .long   HIFI1_IRQHandler                                /* HIFI1: Interrupt request*/
    .long   MU1_B_IRQHandler                                /* MU1: MUB, CPU1 to CPU0*/
    .long   Reserved43_IRQHandler                           /* Reserved interrupt*/
    .long   MU3_A_IRQHandler                                /* MU3: MUA, CPU1 to HiFi1*/
    .long   PMC_IRQHandler                                  /* PMC: Sense domain Interrupt*/
    .long   OS_EVENT_IRQHandler                             /* OSEVENT: Event timer CPU1 Wakeup/interrupt*/
    .long   USDHC0_IRQHandler                               /* USDHC: Interrupt request*/
    .long   USDHC1_IRQHandler                               /* USDHC: Interrupt request*/
    .long   I3C2_IRQHandler                                 /* I3C: Interrupt Request*/
    .long   USB0_IRQHandler                                 /* USB: HSUSB Interrup request*/
    .long   USB1_IRQHandler                                 /* USB: eUSB Interrup request*/
    .long   WDT2_IRQHandler                                 /* WDT: Interrupt request*/
    .long   WDT3_IRQHandler                                 /* WDT: Interrupt request*/
    .long   USBPHY0_IRQHandler                              /* HSUSBPHY: UTM interrupt request*/
    .long   PMIC_IRQN_IRQHandler                            /* PMIC: External PMIC interrupt*/
    .long   I3C3_IRQHandler                                 /* I3C: Interrupt Request*/
    .long   FLEXIO_IRQHandler                               /* flexio: Interrupt request*/
    .long   Reserved58_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved59_IRQHandler                           /* Reserved interrupt*/
    .long   MIPI_IRQHandler                                 /* dsi: Interrupt request*/
    .long   EDMA2_CH0_IRQHandler                            /* edma2: Channel 0 interrupt*/
    .long   EDMA2_CH1_IRQHandler                            /* edma2: Channel 1 interrupt*/
    .long   EDMA2_CH2_IRQHandler                            /* edma2: Channel 2 interrupt*/
    .long   EDMA2_CH3_IRQHandler                            /* edma2: Channel 3 interrupt*/
    .long   EDMA2_CH4_IRQHandler                            /* edma2: Channel 4 interrupt*/
    .long   EDMA2_CH5_IRQHandler                            /* edma2: Channel 5 interrupt*/
    .long   EDMA2_CH6_IRQHandler                            /* edma2: Channel 6 interrupt*/
    .long   EDMA2_CH7_IRQHandler                            /* edma2: Channel 7 interrupt*/
    .long   EDMA3_CH0_IRQHandler                            /* edma3: Channel 0 interrupt*/
    .long   EDMA3_CH1_IRQHandler                            /* edma3: Channel 1 interrupt*/
    .long   EDMA3_CH2_IRQHandler                            /* edma3: Channel 2 interrupt*/
    .long   EDMA3_CH3_IRQHandler                            /* edma3: Channel 3 interrupt*/
    .long   EDMA3_CH4_IRQHandler                            /* edma3: Channel 4 interrupt*/
    .long   EDMA3_CH5_IRQHandler                            /* edma3: Channel 5 interrupt*/
    .long   EDMA3_CH6_IRQHandler                            /* edma3: Channel 6 interrupt*/
    .long   EDMA3_CH7_IRQHandler                            /* edma3: Channel 7 interrupt*/
    .long   GPIO80_IRQHandler                               /* rgpio8: Interupt request, channel 0*/
    .long   GPIO81_IRQHandler                               /* rgpio8: Interupt request, channel 1*/
    .long   GPIO90_IRQHandler                               /* rgpio9: Interupt request, channel 0*/
    .long   GPIO91_IRQHandler                               /* rgpio9: Interupt request, channel 1*/
    .long   GPIO100_IRQHandler                              /* rgpio10: Interupt request, channel 0*/
    .long   GPIO101_IRQHandler                              /* rgpio10: Interupt request, channel 1*/
    .long   Reserved83_IRQHandler                           /* Reserved interrupt 83*/
    .long   Reserved84_IRQHandler                           /* Reserved interrupt 84*/
    .long   PIN_INT0_IRQHandler                             /* pint1: Interupt request 0*/
    .long   PIN_INT1_IRQHandler                             /* pint1: Interupt request 1*/
    .long   PIN_INT2_IRQHandler                             /* pint1: Interupt request 2*/
    .long   PIN_INT3_IRQHandler                             /* pint1: Interupt request 3*/
    .long   SAI3_IRQHandler                                 /* sai3: TX/RX interrupt*/
    .long   XSPI2_IRQHandler                                /* xspi2: Ored interrupt*/
    .long   MMU2_IRQHandler                                 /* mmu2: Interrupt request*/
    .long   GDET2_IRQHandler                                /* gdet2_wrapper: Interrupt request*/
    .long   GDET3_IRQHandler                                /* gdet3_wrapper: Interrupt request*/
    .long   CDOG3_IRQHandler                                /* cdog3: Interrupt request*/
    .long   CDOG4_IRQHandler                                /* cdog4: Interrupt request*/
    .long   Reserved96_IRQHandler                           /* Reserved interrupt 96*/
    .long   CPU1_IRQHandler                                 /* CTI interrupt request*/
    .long   Reserved98_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved99_IRQHandler                           /* Reserved interrupt*/
    .long   Reserved100_IRQHandler                          /* Reserved interrupt 100*/
    .long   TEMPDET0_IRQHandler                             /* TEMPDET0: Temperature Detect Interrupt request 0*/
    .long   TEMPDET1_IRQHandler                             /* TEMPDET1: Temperature Detect Interrupt request 1*/
    .long   EZHV_IRQHandler                                 /* ezhv: Interrupt request*/
    .long   SLEEPCON1_IRQHandler                            /* SLEEPCON_SENSE CPU1 wakeup event*/
    .long   PVTS1_CPU1_IRQHandler                           /* PVTS1 CPU1 interrupt*/
    .long   Reserved106_IRQHandler                          /* Reserved interrupt 106*/
    .long   PVTS1_HIFI1_IRQHandler                          /* PVTS1 HIFI1 interrupt*/
    .long   Reserved108_IRQHandler                          /* Reserved interrupt 108*/

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
    .weak Reserved17_IRQHandler
    .type Reserved17_IRQHandler, %function
Reserved17_IRQHandler:
    ldr   r0,=Reserved17_DriverIRQHandler
    bx    r0
    .size Reserved17_IRQHandler, . - Reserved17_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved18_IRQHandler
    .type Reserved18_IRQHandler, %function
Reserved18_IRQHandler:
    ldr   r0,=Reserved18_DriverIRQHandler
    bx    r0
    .size Reserved18_IRQHandler, . - Reserved18_IRQHandler

    .align 1
    .thumb_func
    .weak FRO2_IRQHandler
    .type FRO2_IRQHandler, %function
FRO2_IRQHandler:
    ldr   r0,=FRO2_DriverIRQHandler
    bx    r0
    .size FRO2_IRQHandler, . - FRO2_IRQHandler

    .align 1
    .thumb_func
    .weak GLIKEY4_IRQHandler
    .type GLIKEY4_IRQHandler, %function
GLIKEY4_IRQHandler:
    ldr   r0,=GLIKEY4_DriverIRQHandler
    bx    r0
    .size GLIKEY4_IRQHandler, . - GLIKEY4_IRQHandler

    .align 1
    .thumb_func
    .weak UTICK1_IRQHandler
    .type UTICK1_IRQHandler, %function
UTICK1_IRQHandler:
    ldr   r0,=UTICK1_DriverIRQHandler
    bx    r0
    .size UTICK1_IRQHandler, . - UTICK1_IRQHandler

    .align 1
    .thumb_func
    .weak MRT1_IRQHandler
    .type MRT1_IRQHandler, %function
MRT1_IRQHandler:
    ldr   r0,=MRT1_DriverIRQHandler
    bx    r0
    .size MRT1_IRQHandler, . - MRT1_IRQHandler

    .align 1
    .thumb_func
    .weak CTIMER5_IRQHandler
    .type CTIMER5_IRQHandler, %function
CTIMER5_IRQHandler:
    ldr   r0,=CTIMER5_DriverIRQHandler
    bx    r0
    .size CTIMER5_IRQHandler, . - CTIMER5_IRQHandler

    .align 1
    .thumb_func
    .weak CTIMER6_IRQHandler
    .type CTIMER6_IRQHandler, %function
CTIMER6_IRQHandler:
    ldr   r0,=CTIMER6_DriverIRQHandler
    bx    r0
    .size CTIMER6_IRQHandler, . - CTIMER6_IRQHandler

    .align 1
    .thumb_func
    .weak CTIMER7_IRQHandler
    .type CTIMER7_IRQHandler, %function
CTIMER7_IRQHandler:
    ldr   r0,=CTIMER7_DriverIRQHandler
    bx    r0
    .size CTIMER7_IRQHandler, . - CTIMER7_IRQHandler

    .align 1
    .thumb_func
    .weak LPI2C15_IRQHandler
    .type LPI2C15_IRQHandler, %function
LPI2C15_IRQHandler:
    ldr   r0,=LPI2C15_DriverIRQHandler
    bx    r0
    .size LPI2C15_IRQHandler, . - LPI2C15_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM17_IRQHandler
    .type LP_FLEXCOMM17_IRQHandler, %function
LP_FLEXCOMM17_IRQHandler:
    ldr   r0,=LP_FLEXCOMM17_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM17_IRQHandler, . - LP_FLEXCOMM17_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM18_IRQHandler
    .type LP_FLEXCOMM18_IRQHandler, %function
LP_FLEXCOMM18_IRQHandler:
    ldr   r0,=LP_FLEXCOMM18_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM18_IRQHandler, . - LP_FLEXCOMM18_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM19_IRQHandler
    .type LP_FLEXCOMM19_IRQHandler, %function
LP_FLEXCOMM19_IRQHandler:
    ldr   r0,=LP_FLEXCOMM19_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM19_IRQHandler, . - LP_FLEXCOMM19_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM20_IRQHandler
    .type LP_FLEXCOMM20_IRQHandler, %function
LP_FLEXCOMM20_IRQHandler:
    ldr   r0,=LP_FLEXCOMM20_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM20_IRQHandler, . - LP_FLEXCOMM20_IRQHandler

    .align 1
    .thumb_func
    .weak ADC_IRQHandler
    .type ADC_IRQHandler, %function
ADC_IRQHandler:
    ldr   r0,=ADC_DriverIRQHandler
    bx    r0
    .size ADC_IRQHandler, . - ADC_IRQHandler

    .align 1
    .thumb_func
    .weak SDADC_IRQHandler
    .type SDADC_IRQHandler, %function
SDADC_IRQHandler:
    ldr   r0,=SDADC_DriverIRQHandler
    bx    r0
    .size SDADC_IRQHandler, . - SDADC_IRQHandler

    .align 1
    .thumb_func
    .weak GLIKEY1_IRQHandler
    .type GLIKEY1_IRQHandler, %function
GLIKEY1_IRQHandler:
    ldr   r0,=GLIKEY1_DriverIRQHandler
    bx    r0
    .size GLIKEY1_IRQHandler, . - GLIKEY1_IRQHandler

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
    .weak PDM_EVENT_IRQHandler
    .type PDM_EVENT_IRQHandler, %function
PDM_EVENT_IRQHandler:
    ldr   r0,=PDM_EVENT_DriverIRQHandler
    bx    r0
    .size PDM_EVENT_IRQHandler, . - PDM_EVENT_IRQHandler

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
    .weak SECURE_VIOLATION_IRQHandler
    .type SECURE_VIOLATION_IRQHandler, %function
SECURE_VIOLATION_IRQHandler:
    ldr   r0,=SECURE_VIOLATION_DriverIRQHandler
    bx    r0
    .size SECURE_VIOLATION_IRQHandler, . - SECURE_VIOLATION_IRQHandler

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
    .weak RTC1_ALARM_IRQHandler
    .type RTC1_ALARM_IRQHandler, %function
RTC1_ALARM_IRQHandler:
    ldr   r0,=RTC1_ALARM_DriverIRQHandler
    bx    r0
    .size RTC1_ALARM_IRQHandler, . - RTC1_ALARM_IRQHandler

    .align 1
    .thumb_func
    .weak RTC1_IRQHandler
    .type RTC1_IRQHandler, %function
RTC1_IRQHandler:
    ldr   r0,=RTC1_DriverIRQHandler
    bx    r0
    .size RTC1_IRQHandler, . - RTC1_IRQHandler

    .align 1
    .thumb_func
    .weak HIFI1_IRQHandler
    .type HIFI1_IRQHandler, %function
HIFI1_IRQHandler:
    ldr   r0,=HIFI1_DriverIRQHandler
    bx    r0
    .size HIFI1_IRQHandler, . - HIFI1_IRQHandler

    .align 1
    .thumb_func
    .weak MU1_B_IRQHandler
    .type MU1_B_IRQHandler, %function
MU1_B_IRQHandler:
    ldr   r0,=MU1_B_DriverIRQHandler
    bx    r0
    .size MU1_B_IRQHandler, . - MU1_B_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved43_IRQHandler
    .type Reserved43_IRQHandler, %function
Reserved43_IRQHandler:
    ldr   r0,=Reserved43_DriverIRQHandler
    bx    r0
    .size Reserved43_IRQHandler, . - Reserved43_IRQHandler

    .align 1
    .thumb_func
    .weak MU3_A_IRQHandler
    .type MU3_A_IRQHandler, %function
MU3_A_IRQHandler:
    ldr   r0,=MU3_A_DriverIRQHandler
    bx    r0
    .size MU3_A_IRQHandler, . - MU3_A_IRQHandler

    .align 1
    .thumb_func
    .weak PMC_IRQHandler
    .type PMC_IRQHandler, %function
PMC_IRQHandler:
    ldr   r0,=PMC_DriverIRQHandler
    bx    r0
    .size PMC_IRQHandler, . - PMC_IRQHandler

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
    .weak I3C2_IRQHandler
    .type I3C2_IRQHandler, %function
I3C2_IRQHandler:
    ldr   r0,=I3C2_DriverIRQHandler
    bx    r0
    .size I3C2_IRQHandler, . - I3C2_IRQHandler

    .align 1
    .thumb_func
    .weak USB0_IRQHandler
    .type USB0_IRQHandler, %function
USB0_IRQHandler:
    ldr   r0,=USB0_DriverIRQHandler
    bx    r0
    .size USB0_IRQHandler, . - USB0_IRQHandler

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
    .weak WDT2_IRQHandler
    .type WDT2_IRQHandler, %function
WDT2_IRQHandler:
    ldr   r0,=WDT2_DriverIRQHandler
    bx    r0
    .size WDT2_IRQHandler, . - WDT2_IRQHandler

    .align 1
    .thumb_func
    .weak WDT3_IRQHandler
    .type WDT3_IRQHandler, %function
WDT3_IRQHandler:
    ldr   r0,=WDT3_DriverIRQHandler
    bx    r0
    .size WDT3_IRQHandler, . - WDT3_IRQHandler

    .align 1
    .thumb_func
    .weak USBPHY0_IRQHandler
    .type USBPHY0_IRQHandler, %function
USBPHY0_IRQHandler:
    ldr   r0,=USBPHY0_DriverIRQHandler
    bx    r0
    .size USBPHY0_IRQHandler, . - USBPHY0_IRQHandler

    .align 1
    .thumb_func
    .weak PMIC_IRQN_IRQHandler
    .type PMIC_IRQN_IRQHandler, %function
PMIC_IRQN_IRQHandler:
    ldr   r0,=PMIC_IRQN_DriverIRQHandler
    bx    r0
    .size PMIC_IRQN_IRQHandler, . - PMIC_IRQN_IRQHandler

    .align 1
    .thumb_func
    .weak I3C3_IRQHandler
    .type I3C3_IRQHandler, %function
I3C3_IRQHandler:
    ldr   r0,=I3C3_DriverIRQHandler
    bx    r0
    .size I3C3_IRQHandler, . - I3C3_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXIO_IRQHandler
    .type FLEXIO_IRQHandler, %function
FLEXIO_IRQHandler:
    ldr   r0,=FLEXIO_DriverIRQHandler
    bx    r0
    .size FLEXIO_IRQHandler, . - FLEXIO_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved58_IRQHandler
    .type Reserved58_IRQHandler, %function
Reserved58_IRQHandler:
    ldr   r0,=Reserved58_DriverIRQHandler
    bx    r0
    .size Reserved58_IRQHandler, . - Reserved58_IRQHandler

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
    .weak MIPI_IRQHandler
    .type MIPI_IRQHandler, %function
MIPI_IRQHandler:
    ldr   r0,=MIPI_DriverIRQHandler
    bx    r0
    .size MIPI_IRQHandler, . - MIPI_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA2_CH0_IRQHandler
    .type EDMA2_CH0_IRQHandler, %function
EDMA2_CH0_IRQHandler:
    ldr   r0,=EDMA2_CH0_DriverIRQHandler
    bx    r0
    .size EDMA2_CH0_IRQHandler, . - EDMA2_CH0_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA2_CH1_IRQHandler
    .type EDMA2_CH1_IRQHandler, %function
EDMA2_CH1_IRQHandler:
    ldr   r0,=EDMA2_CH1_DriverIRQHandler
    bx    r0
    .size EDMA2_CH1_IRQHandler, . - EDMA2_CH1_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA2_CH2_IRQHandler
    .type EDMA2_CH2_IRQHandler, %function
EDMA2_CH2_IRQHandler:
    ldr   r0,=EDMA2_CH2_DriverIRQHandler
    bx    r0
    .size EDMA2_CH2_IRQHandler, . - EDMA2_CH2_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA2_CH3_IRQHandler
    .type EDMA2_CH3_IRQHandler, %function
EDMA2_CH3_IRQHandler:
    ldr   r0,=EDMA2_CH3_DriverIRQHandler
    bx    r0
    .size EDMA2_CH3_IRQHandler, . - EDMA2_CH3_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA2_CH4_IRQHandler
    .type EDMA2_CH4_IRQHandler, %function
EDMA2_CH4_IRQHandler:
    ldr   r0,=EDMA2_CH4_DriverIRQHandler
    bx    r0
    .size EDMA2_CH4_IRQHandler, . - EDMA2_CH4_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA2_CH5_IRQHandler
    .type EDMA2_CH5_IRQHandler, %function
EDMA2_CH5_IRQHandler:
    ldr   r0,=EDMA2_CH5_DriverIRQHandler
    bx    r0
    .size EDMA2_CH5_IRQHandler, . - EDMA2_CH5_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA2_CH6_IRQHandler
    .type EDMA2_CH6_IRQHandler, %function
EDMA2_CH6_IRQHandler:
    ldr   r0,=EDMA2_CH6_DriverIRQHandler
    bx    r0
    .size EDMA2_CH6_IRQHandler, . - EDMA2_CH6_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA2_CH7_IRQHandler
    .type EDMA2_CH7_IRQHandler, %function
EDMA2_CH7_IRQHandler:
    ldr   r0,=EDMA2_CH7_DriverIRQHandler
    bx    r0
    .size EDMA2_CH7_IRQHandler, . - EDMA2_CH7_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA3_CH0_IRQHandler
    .type EDMA3_CH0_IRQHandler, %function
EDMA3_CH0_IRQHandler:
    ldr   r0,=EDMA3_CH0_DriverIRQHandler
    bx    r0
    .size EDMA3_CH0_IRQHandler, . - EDMA3_CH0_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA3_CH1_IRQHandler
    .type EDMA3_CH1_IRQHandler, %function
EDMA3_CH1_IRQHandler:
    ldr   r0,=EDMA3_CH1_DriverIRQHandler
    bx    r0
    .size EDMA3_CH1_IRQHandler, . - EDMA3_CH1_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA3_CH2_IRQHandler
    .type EDMA3_CH2_IRQHandler, %function
EDMA3_CH2_IRQHandler:
    ldr   r0,=EDMA3_CH2_DriverIRQHandler
    bx    r0
    .size EDMA3_CH2_IRQHandler, . - EDMA3_CH2_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA3_CH3_IRQHandler
    .type EDMA3_CH3_IRQHandler, %function
EDMA3_CH3_IRQHandler:
    ldr   r0,=EDMA3_CH3_DriverIRQHandler
    bx    r0
    .size EDMA3_CH3_IRQHandler, . - EDMA3_CH3_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA3_CH4_IRQHandler
    .type EDMA3_CH4_IRQHandler, %function
EDMA3_CH4_IRQHandler:
    ldr   r0,=EDMA3_CH4_DriverIRQHandler
    bx    r0
    .size EDMA3_CH4_IRQHandler, . - EDMA3_CH4_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA3_CH5_IRQHandler
    .type EDMA3_CH5_IRQHandler, %function
EDMA3_CH5_IRQHandler:
    ldr   r0,=EDMA3_CH5_DriverIRQHandler
    bx    r0
    .size EDMA3_CH5_IRQHandler, . - EDMA3_CH5_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA3_CH6_IRQHandler
    .type EDMA3_CH6_IRQHandler, %function
EDMA3_CH6_IRQHandler:
    ldr   r0,=EDMA3_CH6_DriverIRQHandler
    bx    r0
    .size EDMA3_CH6_IRQHandler, . - EDMA3_CH6_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA3_CH7_IRQHandler
    .type EDMA3_CH7_IRQHandler, %function
EDMA3_CH7_IRQHandler:
    ldr   r0,=EDMA3_CH7_DriverIRQHandler
    bx    r0
    .size EDMA3_CH7_IRQHandler, . - EDMA3_CH7_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO80_IRQHandler
    .type GPIO80_IRQHandler, %function
GPIO80_IRQHandler:
    ldr   r0,=GPIO80_DriverIRQHandler
    bx    r0
    .size GPIO80_IRQHandler, . - GPIO80_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO81_IRQHandler
    .type GPIO81_IRQHandler, %function
GPIO81_IRQHandler:
    ldr   r0,=GPIO81_DriverIRQHandler
    bx    r0
    .size GPIO81_IRQHandler, . - GPIO81_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO90_IRQHandler
    .type GPIO90_IRQHandler, %function
GPIO90_IRQHandler:
    ldr   r0,=GPIO90_DriverIRQHandler
    bx    r0
    .size GPIO90_IRQHandler, . - GPIO90_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO91_IRQHandler
    .type GPIO91_IRQHandler, %function
GPIO91_IRQHandler:
    ldr   r0,=GPIO91_DriverIRQHandler
    bx    r0
    .size GPIO91_IRQHandler, . - GPIO91_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO100_IRQHandler
    .type GPIO100_IRQHandler, %function
GPIO100_IRQHandler:
    ldr   r0,=GPIO100_DriverIRQHandler
    bx    r0
    .size GPIO100_IRQHandler, . - GPIO100_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO101_IRQHandler
    .type GPIO101_IRQHandler, %function
GPIO101_IRQHandler:
    ldr   r0,=GPIO101_DriverIRQHandler
    bx    r0
    .size GPIO101_IRQHandler, . - GPIO101_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved83_IRQHandler
    .type Reserved83_IRQHandler, %function
Reserved83_IRQHandler:
    ldr   r0,=Reserved83_DriverIRQHandler
    bx    r0
    .size Reserved83_IRQHandler, . - Reserved83_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved84_IRQHandler
    .type Reserved84_IRQHandler, %function
Reserved84_IRQHandler:
    ldr   r0,=Reserved84_DriverIRQHandler
    bx    r0
    .size Reserved84_IRQHandler, . - Reserved84_IRQHandler

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
    .weak SAI3_IRQHandler
    .type SAI3_IRQHandler, %function
SAI3_IRQHandler:
    ldr   r0,=SAI3_DriverIRQHandler
    bx    r0
    .size SAI3_IRQHandler, . - SAI3_IRQHandler

    .align 1
    .thumb_func
    .weak XSPI2_IRQHandler
    .type XSPI2_IRQHandler, %function
XSPI2_IRQHandler:
    ldr   r0,=XSPI2_DriverIRQHandler
    bx    r0
    .size XSPI2_IRQHandler, . - XSPI2_IRQHandler

    .align 1
    .thumb_func
    .weak MMU2_IRQHandler
    .type MMU2_IRQHandler, %function
MMU2_IRQHandler:
    ldr   r0,=MMU2_DriverIRQHandler
    bx    r0
    .size MMU2_IRQHandler, . - MMU2_IRQHandler

    .align 1
    .thumb_func
    .weak GDET2_IRQHandler
    .type GDET2_IRQHandler, %function
GDET2_IRQHandler:
    ldr   r0,=GDET2_DriverIRQHandler
    bx    r0
    .size GDET2_IRQHandler, . - GDET2_IRQHandler

    .align 1
    .thumb_func
    .weak GDET3_IRQHandler
    .type GDET3_IRQHandler, %function
GDET3_IRQHandler:
    ldr   r0,=GDET3_DriverIRQHandler
    bx    r0
    .size GDET3_IRQHandler, . - GDET3_IRQHandler

    .align 1
    .thumb_func
    .weak CDOG3_IRQHandler
    .type CDOG3_IRQHandler, %function
CDOG3_IRQHandler:
    ldr   r0,=CDOG3_DriverIRQHandler
    bx    r0
    .size CDOG3_IRQHandler, . - CDOG3_IRQHandler

    .align 1
    .thumb_func
    .weak CDOG4_IRQHandler
    .type CDOG4_IRQHandler, %function
CDOG4_IRQHandler:
    ldr   r0,=CDOG4_DriverIRQHandler
    bx    r0
    .size CDOG4_IRQHandler, . - CDOG4_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved96_IRQHandler
    .type Reserved96_IRQHandler, %function
Reserved96_IRQHandler:
    ldr   r0,=Reserved96_DriverIRQHandler
    bx    r0
    .size Reserved96_IRQHandler, . - Reserved96_IRQHandler

    .align 1
    .thumb_func
    .weak CPU1_IRQHandler
    .type CPU1_IRQHandler, %function
CPU1_IRQHandler:
    ldr   r0,=CPU1_DriverIRQHandler
    bx    r0
    .size CPU1_IRQHandler, . - CPU1_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved98_IRQHandler
    .type Reserved98_IRQHandler, %function
Reserved98_IRQHandler:
    ldr   r0,=Reserved98_DriverIRQHandler
    bx    r0
    .size Reserved98_IRQHandler, . - Reserved98_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved99_IRQHandler
    .type Reserved99_IRQHandler, %function
Reserved99_IRQHandler:
    ldr   r0,=Reserved99_DriverIRQHandler
    bx    r0
    .size Reserved99_IRQHandler, . - Reserved99_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved100_IRQHandler
    .type Reserved100_IRQHandler, %function
Reserved100_IRQHandler:
    ldr   r0,=Reserved100_DriverIRQHandler
    bx    r0
    .size Reserved100_IRQHandler, . - Reserved100_IRQHandler

    .align 1
    .thumb_func
    .weak TEMPDET0_IRQHandler
    .type TEMPDET0_IRQHandler, %function
TEMPDET0_IRQHandler:
    ldr   r0,=TEMPDET0_DriverIRQHandler
    bx    r0
    .size TEMPDET0_IRQHandler, . - TEMPDET0_IRQHandler

    .align 1
    .thumb_func
    .weak TEMPDET1_IRQHandler
    .type TEMPDET1_IRQHandler, %function
TEMPDET1_IRQHandler:
    ldr   r0,=TEMPDET1_DriverIRQHandler
    bx    r0
    .size TEMPDET1_IRQHandler, . - TEMPDET1_IRQHandler

    .align 1
    .thumb_func
    .weak EZHV_IRQHandler
    .type EZHV_IRQHandler, %function
EZHV_IRQHandler:
    ldr   r0,=EZHV_DriverIRQHandler
    bx    r0
    .size EZHV_IRQHandler, . - EZHV_IRQHandler

    .align 1
    .thumb_func
    .weak SLEEPCON1_IRQHandler
    .type SLEEPCON1_IRQHandler, %function
SLEEPCON1_IRQHandler:
    ldr   r0,=SLEEPCON1_DriverIRQHandler
    bx    r0
    .size SLEEPCON1_IRQHandler, . - SLEEPCON1_IRQHandler

    .align 1
    .thumb_func
    .weak PVTS1_CPU1_IRQHandler
    .type PVTS1_CPU1_IRQHandler, %function
PVTS1_CPU1_IRQHandler:
    ldr   r0,=PVTS1_CPU1_DriverIRQHandler
    bx    r0
    .size PVTS1_CPU1_IRQHandler, . - PVTS1_CPU1_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved106_IRQHandler
    .type Reserved106_IRQHandler, %function
Reserved106_IRQHandler:
    ldr   r0,=Reserved106_DriverIRQHandler
    bx    r0
    .size Reserved106_IRQHandler, . - Reserved106_IRQHandler

    .align 1
    .thumb_func
    .weak PVTS1_HIFI1_IRQHandler
    .type PVTS1_HIFI1_IRQHandler, %function
PVTS1_HIFI1_IRQHandler:
    ldr   r0,=PVTS1_HIFI1_DriverIRQHandler
    bx    r0
    .size PVTS1_HIFI1_IRQHandler, . - PVTS1_HIFI1_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved108_IRQHandler
    .type Reserved108_IRQHandler, %function
Reserved108_IRQHandler:
    ldr   r0,=Reserved108_DriverIRQHandler
    bx    r0
    .size Reserved108_IRQHandler, . - Reserved108_IRQHandler


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
    def_irq_handler    Reserved16_DriverIRQHandler
    def_irq_handler    Reserved17_DriverIRQHandler
    def_irq_handler    Reserved18_DriverIRQHandler
    def_irq_handler    FRO2_DriverIRQHandler
    def_irq_handler    GLIKEY4_DriverIRQHandler
    def_irq_handler    UTICK1_DriverIRQHandler
    def_irq_handler    MRT1_DriverIRQHandler
    def_irq_handler    CTIMER5_DriverIRQHandler
    def_irq_handler    CTIMER6_DriverIRQHandler
    def_irq_handler    CTIMER7_DriverIRQHandler
    def_irq_handler    LPI2C15_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM17_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM18_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM19_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM20_DriverIRQHandler
    def_irq_handler    ADC_DriverIRQHandler
    def_irq_handler    SDADC_DriverIRQHandler
    def_irq_handler    GLIKEY1_DriverIRQHandler
    def_irq_handler    ACMP_DriverIRQHandler
    def_irq_handler    PDM_EVENT_DriverIRQHandler
    def_irq_handler    HYPERVISOR_DriverIRQHandler
    def_irq_handler    SECURE_VIOLATION_DriverIRQHandler
    def_irq_handler    PDM_HWVAD_EVENT_DriverIRQHandler
    def_irq_handler    RTC1_ALARM_DriverIRQHandler
    def_irq_handler    RTC1_DriverIRQHandler
    def_irq_handler    HIFI1_DriverIRQHandler
    def_irq_handler    MU1_B_DriverIRQHandler
    def_irq_handler    Reserved43_DriverIRQHandler
    def_irq_handler    MU3_A_DriverIRQHandler
    def_irq_handler    PMC_DriverIRQHandler
    def_irq_handler    OS_EVENT_DriverIRQHandler
    def_irq_handler    USDHC0_DriverIRQHandler
    def_irq_handler    USDHC1_DriverIRQHandler
    def_irq_handler    I3C2_DriverIRQHandler
    def_irq_handler    USB0_DriverIRQHandler
    def_irq_handler    USB1_DriverIRQHandler
    def_irq_handler    WDT2_DriverIRQHandler
    def_irq_handler    WDT3_DriverIRQHandler
    def_irq_handler    USBPHY0_DriverIRQHandler
    def_irq_handler    PMIC_IRQN_DriverIRQHandler
    def_irq_handler    I3C3_DriverIRQHandler
    def_irq_handler    FLEXIO_DriverIRQHandler
    def_irq_handler    Reserved58_DriverIRQHandler
    def_irq_handler    Reserved59_DriverIRQHandler
    def_irq_handler    MIPI_DriverIRQHandler
    def_irq_handler    EDMA2_CH0_DriverIRQHandler
    def_irq_handler    EDMA2_CH1_DriverIRQHandler
    def_irq_handler    EDMA2_CH2_DriverIRQHandler
    def_irq_handler    EDMA2_CH3_DriverIRQHandler
    def_irq_handler    EDMA2_CH4_DriverIRQHandler
    def_irq_handler    EDMA2_CH5_DriverIRQHandler
    def_irq_handler    EDMA2_CH6_DriverIRQHandler
    def_irq_handler    EDMA2_CH7_DriverIRQHandler
    def_irq_handler    EDMA3_CH0_DriverIRQHandler
    def_irq_handler    EDMA3_CH1_DriverIRQHandler
    def_irq_handler    EDMA3_CH2_DriverIRQHandler
    def_irq_handler    EDMA3_CH3_DriverIRQHandler
    def_irq_handler    EDMA3_CH4_DriverIRQHandler
    def_irq_handler    EDMA3_CH5_DriverIRQHandler
    def_irq_handler    EDMA3_CH6_DriverIRQHandler
    def_irq_handler    EDMA3_CH7_DriverIRQHandler
    def_irq_handler    GPIO80_DriverIRQHandler
    def_irq_handler    GPIO81_DriverIRQHandler
    def_irq_handler    GPIO90_DriverIRQHandler
    def_irq_handler    GPIO91_DriverIRQHandler
    def_irq_handler    GPIO100_DriverIRQHandler
    def_irq_handler    GPIO101_DriverIRQHandler
    def_irq_handler    Reserved83_DriverIRQHandler
    def_irq_handler    Reserved84_DriverIRQHandler
    def_irq_handler    PIN_INT0_DriverIRQHandler
    def_irq_handler    PIN_INT1_DriverIRQHandler
    def_irq_handler    PIN_INT2_DriverIRQHandler
    def_irq_handler    PIN_INT3_DriverIRQHandler
    def_irq_handler    SAI3_DriverIRQHandler
    def_irq_handler    XSPI2_DriverIRQHandler
    def_irq_handler    MMU2_DriverIRQHandler
    def_irq_handler    GDET2_DriverIRQHandler
    def_irq_handler    GDET3_DriverIRQHandler
    def_irq_handler    CDOG3_DriverIRQHandler
    def_irq_handler    CDOG4_DriverIRQHandler
    def_irq_handler    Reserved96_DriverIRQHandler
    def_irq_handler    CPU1_DriverIRQHandler
    def_irq_handler    Reserved98_DriverIRQHandler
    def_irq_handler    Reserved99_DriverIRQHandler
    def_irq_handler    Reserved100_DriverIRQHandler
    def_irq_handler    TEMPDET0_DriverIRQHandler
    def_irq_handler    TEMPDET1_DriverIRQHandler
    def_irq_handler    EZHV_DriverIRQHandler
    def_irq_handler    SLEEPCON1_DriverIRQHandler
    def_irq_handler    PVTS1_CPU1_DriverIRQHandler
    def_irq_handler    Reserved106_DriverIRQHandler
    def_irq_handler    PVTS1_HIFI1_DriverIRQHandler
    def_irq_handler    Reserved108_DriverIRQHandler

    .end
