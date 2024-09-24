/* ------------------------------------------------------------------------- */
/*  @file:    startup_MIMXRT758S_cm33_core0.s                                */
/*  @purpose: CMSIS Cortex-M33 Core Device Startup File                      */
/*            MIMXRT758S_cm33_core0                                          */
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
    .long   UTICK0_IRQHandler                               /* Micro-tick Timer*/
    .long   MRT0_IRQHandler                                 /* MRT: Ored Interrupt request*/
    .long   CTIMER0_IRQHandler                              /* CTIMER: Interrupt request*/
    .long   CTIMER1_IRQHandler                              /* CTIMER: Interrupt request*/
    .long   SCT0_IRQHandler                                 /* SCT: Interrupt request*/
    .long   CTIMER3_IRQHandler                              /* CTIMER: Interrupt request*/
    .long   LP_FLEXCOMM0_IRQHandler                         /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM1_IRQHandler                         /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM2_IRQHandler                         /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM3_IRQHandler                         /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM4_IRQHandler                         /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM5_IRQHandler                         /* FLEXCOMM: Interrupt request*/
    .long   LPSPI14_IRQHandler                              /* LPSPI: Interrupt request*/
    .long   LPI2C15_IRQHandler                              /* LPI2C: Interrupt request*/
    .long   ADC_IRQHandler                                  /* ADC0: Interrupt request*/
    .long   SDADC_IRQHandler                                /* SDADC0: Interrupt request*/
    .long   ACMP_IRQHandler                                 /* ACMP: interrupt request*/
    .long   PDM_EVENT_IRQHandler                            /* MIC: Interrupt request for read data or Error*/
    .long   PDM_HWVAD_EVENT_IRQHandler                      /* MIC: Hardware Voice Activity Detector interrupt or error interrupt*/
    .long   HYPERVISOR_IRQHandler                           /* SECURE: Compute domain P-Bus Hypervisor interrupt*/
    .long   SECURE_VIOLATION_IRQHandler                     /* SECURE: Compute domain P-Bus Secure violation interrupt*/
    .long   SENSE_HYPERVISOR_IRQHandler                     /* Sense domain Hypervisor interrupt*/
    .long   SENSE_SECURE_VIOLATION_IRQHandler               /* Sense domain Secure violation interrupt*/
    .long   MEDIA_HYPERVISOR_IRQHandler                     /* Media domain Hypervisor interrupt*/
    .long   MEDIA_SECURE_VIOLATION_IRQHandler               /* Media domain Secure violation interrupt*/
    .long   RTC0_ALARM_IRQHandler                           /* RTC: Alarm interrupt*/
    .long   RTC0_IRQHandler                                 /* RTC: wakeup interrupt to Compute domain*/
    .long   Reserved44_IRQHandler                           /* Reserved interrupt*/
    .long   MU0_A_IRQHandler                                /* MU0: MUA, CPU0 to HiFi1*/
    .long   MU1_A_IRQHandler                                /* MU1: MUA, CPU0 to CPU1*/
    .long   Reserved47_IRQHandler                           /* Reserved interrupt*/
    .long   CTIMER2_IRQHandler                              /* CTIMER: Interrupt request*/
    .long   CTIMER4_IRQHandler                              /* CTIMER: Interrupt request*/
    .long   OS_EVENT_IRQHandler                             /* OSEVENT: Event timer CPU0 Wakeup/interrupt*/
    .long   LP_FLEXCOMM6_IRQHandler                         /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM7_IRQHandler                         /* FLEXCOMM: Interrupt request*/
    .long   USDHC0_IRQHandler                               /* USDHC: Interrupt request*/
    .long   USDHC1_IRQHandler                               /* USDHC: Interrupt request*/
    .long   I3C0_IRQHandler                                 /* I3C: Interrupt Request*/
    .long   USB0_IRQHandler                                 /* USB: HSUSB Interrup request*/
    .long   USB1_IRQHandler                                 /* USB: eUSB Interrup request*/
    .long   WDT0_IRQHandler                                 /* WDT: Interrupt request*/
    .long   WDT1_IRQHandler                                 /* WDT: Interrupt request*/
    .long   USBPHY0_IRQHandler                              /* HSUSBPHY: UTM interrupt request*/
    .long   PUF_IRQHandler                                  /* PUF: Interrupt Request*/
    .long   PMIC_IRQN_IRQHandler                            /* PMIC: External PMIC interrupt*/
    .long   LP_FLEXCOMM8_IRQHandler                         /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM9_IRQHandler                         /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM10_IRQHandler                        /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM11_IRQHandler                        /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM12_IRQHandler                        /* FLEXCOMM: Interrupt request*/
    .long   LP_FLEXCOMM13_IRQHandler                        /* FLEXCOMM: Interrupt request*/
    .long   LPSPI16_IRQHandler                              /* LPSPI: Interrupt request*/
    .long   I3C1_IRQHandler                                 /* I3C: Interrupt Request*/
    .long   FLEXIO_IRQHandler                               /* FLEXIO: Interrupt request*/
    .long   LCDIF_IRQHandler                                /* LCDIF: Interrupt request*/
    .long   VGPU_IRQHandler                                 /* VGPU: Interrupt from graphics core (Domain HCLK)*/
    .long   MIPI_IRQHandler                                 /* DSI: Interrupt request*/
    .long   EDMA0_CH0_IRQHandler                            /* EDMA: Channel 0 interrupt*/
    .long   EDMA0_CH1_IRQHandler                            /* EDMA: Channel 1 interrupt*/
    .long   EDMA0_CH2_IRQHandler                            /* EDMA: Channel 2 interrupt*/
    .long   EDMA0_CH3_IRQHandler                            /* EDMA: Channel 3 interrupt*/
    .long   EDMA0_CH4_IRQHandler                            /* EDMA: Channel 4 interrupt*/
    .long   EDMA0_CH5_IRQHandler                            /* EDMA: Channel 5 interrupt*/
    .long   EDMA0_CH6_IRQHandler                            /* EDMA: Channel 6 interrupt*/
    .long   EDMA0_CH7_IRQHandler                            /* EDMA: Channel 7 interrupt*/
    .long   EDMA0_CH8_IRQHandler                            /* EDMA: Channel 8 interrupt*/
    .long   EDMA0_CH9_IRQHandler                            /* EDMA: Channel 9 interrupt*/
    .long   EDMA0_CH10_IRQHandler                           /* EDMA: Channel 10 interrupt*/
    .long   EDMA0_CH11_IRQHandler                           /* EDMA: Channel 11 interrupt*/
    .long   EDMA0_CH12_IRQHandler                           /* EDMA: Channel 12 interrupt*/
    .long   EDMA0_CH13_IRQHandler                           /* EDMA: Channel 13 interrupt*/
    .long   EDMA0_CH14_IRQHandler                           /* EDMA: Channel 14 interrupt*/
    .long   EDMA0_CH15_IRQHandler                           /* EDMA: Channel 15 interrupt*/
    .long   EDMA1_CH0_IRQHandler                            /* EDMA: Channel 0 interrupt*/
    .long   EDMA1_CH1_IRQHandler                            /* EDMA: Channel 1 interrupt*/
    .long   EDMA1_CH2_IRQHandler                            /* EDMA: Channel 2 interrupt*/
    .long   EDMA1_CH3_IRQHandler                            /* EDMA: Channel 3 interrupt*/
    .long   EDMA1_CH4_IRQHandler                            /* EDMA: Channel 4 interrupt*/
    .long   EDMA1_CH5_IRQHandler                            /* EDMA: Channel 5 interrupt*/
    .long   EDMA1_CH6_IRQHandler                            /* EDMA: Channel 6 interrupt*/
    .long   EDMA1_CH7_IRQHandler                            /* EDMA: Channel 7 interrupt*/
    .long   EDMA1_CH8_IRQHandler                            /* EDMA: Channel 8 interrupt*/
    .long   EDMA1_CH9_IRQHandler                            /* EDMA: Channel 9 interrupt*/
    .long   EDMA1_CH10_IRQHandler                           /* EDMA: Channel 10 interrupt*/
    .long   EDMA1_CH11_IRQHandler                           /* EDMA: Channel 11 interrupt*/
    .long   EDMA1_CH12_IRQHandler                           /* EDMA: Channel 12 interrupt*/
    .long   EDMA1_CH13_IRQHandler                           /* EDMA: Channel 13 interrupt*/
    .long   EDMA1_CH14_IRQHandler                           /* EDMA: Channel 14 interrupt*/
    .long   EDMA1_CH15_IRQHandler                           /* EDMA: Channel 15 interrupt*/
    .long   GPIO00_IRQHandler                               /* GPIO: Interupt request, channel 0*/
    .long   GPIO01_IRQHandler                               /* GPIO: Interupt request, channel 1*/
    .long   GPIO10_IRQHandler                               /* GPIO: Interupt request, channel 0*/
    .long   GPIO11_IRQHandler                               /* GPIO: Interupt request, channel 1*/
    .long   GPIO20_IRQHandler                               /* GPIO: Interupt request, channel 0*/
    .long   GPIO21_IRQHandler                               /* GPIO: Interupt request, channel 1*/
    .long   GPIO30_IRQHandler                               /* GPIO: Interupt request, channel 0*/
    .long   GPIO31_IRQHandler                               /* GPIO: Interupt request, channel 1*/
    .long   GPIO40_IRQHandler                               /* GPIO: Interupt request, channel 0*/
    .long   GPIO41_IRQHandler                               /* GPIO: Interupt request, channel 1*/
    .long   GPIO50_IRQHandler                               /* GPIO: Interupt request, channel 0*/
    .long   GPIO51_IRQHandler                               /* GPIO: Interupt request, channel 1*/
    .long   GPIO60_IRQHandler                               /* GPIO: Interupt request, channel 0*/
    .long   GPIO61_IRQHandler                               /* GPIO: Interupt request, channel 1*/
    .long   GPIO70_IRQHandler                               /* GPIO: Interupt request, channel 0*/
    .long   GPIO71_IRQHandler                               /* GPIO: Interupt request, channel 1*/
    .long   PIN_INT0_IRQHandler                             /* PINT: Interupt request 0*/
    .long   PIN_INT1_IRQHandler                             /* PINT: Interupt request 1*/
    .long   PIN_INT2_IRQHandler                             /* PINT: Interupt request 2*/
    .long   PIN_INT3_IRQHandler                             /* PINT: Interupt request 3*/
    .long   PIN_INT4_IRQHandler                             /* PINT: Interupt request 4*/
    .long   PIN_INT5_IRQHandler                             /* PINT: Interupt request 5*/
    .long   PIN_INT6_IRQHandler                             /* PINT: Interupt request 6*/
    .long   PIN_INT7_IRQHandler                             /* PINT: Interupt request 7*/
    .long   SAI0_IRQHandler                                 /* SAI: TX/RX interrupt*/
    .long   SAI1_IRQHandler                                 /* SAI: TX/RX interrupt*/
    .long   SAI2_IRQHandler                                 /* SAI: TX/RX interrupt*/
    .long   XSPI0_IRQHandler                                /* xSPI: Ored interrupt*/
    .long   XSPI1_IRQHandler                                /* xSPI: Ored interrupt*/
    .long   XSPI2_IRQHandler                                /* xSPI: Ored interrupt*/
    .long   MMU0_IRQHandler                                 /* MMU: Interrupt request*/
    .long   MMU1_IRQHandler                                 /* MMU: Interrupt request*/
    .long   MMU2_IRQHandler                                 /* MMU: Interrupt request*/
    .long   Freqme_IRQHandler                               /* FREQME: Interrupt request*/
    .long   GDET0_IRQHandler                                /* GDET: Interrupt request*/
    .long   GDET1_IRQHandler                                /* GDET: Interrupt request*/
    .long   GDET2_IRQHandler                                /* GDET: Interrupt request*/
    .long   GDET3_IRQHandler                                /* GDET: Interrupt request*/
    .long   CDOG0_IRQHandler                                /* CDOG: Interrupt request*/
    .long   CDOG1_IRQHandler                                /* CDOG: Interrupt request*/
    .long   CDOG2_IRQHandler                                /* CDOG: Interrupt request*/
    .long   ITRC0_IRQHandler                                /* ITRC: Interrupt, cleared by software*/
    .long   ELS_IRQHandler                                  /* ELS Interrupt request*/
    .long   PKC_IRQHandler                                  /* PKC: Public Key Cryptography Interrutp*/
    .long   OSCCA_IRQHandler                                /* OSCCA: OSCCA Interrupt request*/
    .long   SLEEPCON0_IRQHandler                            /* WAKEUP: CPU0 wakeup event*/
    .long   CPU0_IRQHandler                                 /* CTI0: interrupt request*/
    .long   PMC_IRQHandler                                  /* PMC: Compute domain Interrupt*/
    .long   JPEGDEC_IRQHandler                              /* JPEGDEC: Ored Context 0-3 interrupt request*/
    .long   PNGDEC_IRQHandler                               /* PGNDEC: Interrut request*/
    .long   NPU_IRQHandler                                  /* NPU: Interrupt request*/
    .long   TRNG_IRQHandler                                 /* TRNG: interrupt*/
    .long   TEMPDET0_IRQHandler                             /* TEMPDET0: Interrupt request 0*/
    .long   TEMPDET1_IRQHandler                             /* TEMPDET1: Interrupt request 1*/
    .long   EZHV_IRQHandler                                 /* EZH-V: Interrupt request*/
    .long   GLIKEY0_IRQHandler                              /* GLIKEY: Interrupt*/
    .long   GLIKEY2_IRQHandler                              /* GLIKEY: Interrupt*/
    .long   GLIKEY3_IRQHandler                              /* GLIKEY: Interrupt*/
    .long   GLIKEY5_IRQHandler                              /* GLIKEY: Interrupt*/
    .long   PVTS0_CPU0_IRQHandler                           /* PVTS0 CPU0 interrupt*/
    .long   Reserved167_IRQHandler                          /* Reserved interrupt 167*/
    .long   PVTS0_HIFI4_IRQHandler                          /* PVTS0 HIFI4 interrupt*/
    .long   Reserved169_IRQHandler                          /* Reserved interrupt 169*/
    .long   FRO0_IRQHandler                                 /* FRO: 300MHz FRO in VDD2 domain Async interrupt*/
    .long   FRO1_IRQHandler                                 /* FRO: 192MHz FRO in VDD2 domain Async interrupt*/
    .long   FRO2_IRQHandler                                 /* FRO: 300MHz FRO in VDD1 domain Async interrupt*/
    .long   OCOTP_IRQHandler                                /* OCOTP warning and integrity error interrupt*/

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

#ifdef __STARTUP_INITIALIZE_NONCACHEDATA
    ldr    r2, =__noncachedata_start__
    ldr    r3, =__noncachedata_init_end__
#ifdef __PERFORMANCE_IMPLEMENTATION
/* Here are two copies of loop implementations. First one favors performance
 * and the second one favors code size. Default uses the second one.
 * Define macro "__PERFORMANCE_IMPLEMENTATION" in project to use the first one */
    subs    r3, r2
    ble    .LC6
.LC5:
    subs    r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .LC5
.LC6:
#else  /* code size implemenation */
.LC5:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC5
#endif
/* zero inited ncache section initialization */
    ldr r3, =__noncachedata_end__
    movs    r0,0
.LC7:
    cmp    r2,r3
    itt    lt
    strlt   r0,[r2],#4
    blt    .LC7
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
    .weak LP_FLEXCOMM0_IRQHandler
    .type LP_FLEXCOMM0_IRQHandler, %function
LP_FLEXCOMM0_IRQHandler:
    ldr   r0,=LP_FLEXCOMM0_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM0_IRQHandler, . - LP_FLEXCOMM0_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM1_IRQHandler
    .type LP_FLEXCOMM1_IRQHandler, %function
LP_FLEXCOMM1_IRQHandler:
    ldr   r0,=LP_FLEXCOMM1_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM1_IRQHandler, . - LP_FLEXCOMM1_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM2_IRQHandler
    .type LP_FLEXCOMM2_IRQHandler, %function
LP_FLEXCOMM2_IRQHandler:
    ldr   r0,=LP_FLEXCOMM2_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM2_IRQHandler, . - LP_FLEXCOMM2_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM3_IRQHandler
    .type LP_FLEXCOMM3_IRQHandler, %function
LP_FLEXCOMM3_IRQHandler:
    ldr   r0,=LP_FLEXCOMM3_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM3_IRQHandler, . - LP_FLEXCOMM3_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM4_IRQHandler
    .type LP_FLEXCOMM4_IRQHandler, %function
LP_FLEXCOMM4_IRQHandler:
    ldr   r0,=LP_FLEXCOMM4_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM4_IRQHandler, . - LP_FLEXCOMM4_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM5_IRQHandler
    .type LP_FLEXCOMM5_IRQHandler, %function
LP_FLEXCOMM5_IRQHandler:
    ldr   r0,=LP_FLEXCOMM5_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM5_IRQHandler, . - LP_FLEXCOMM5_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI14_IRQHandler
    .type LPSPI14_IRQHandler, %function
LPSPI14_IRQHandler:
    ldr   r0,=LPSPI14_DriverIRQHandler
    bx    r0
    .size LPSPI14_IRQHandler, . - LPSPI14_IRQHandler

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
    .weak PDM_HWVAD_EVENT_IRQHandler
    .type PDM_HWVAD_EVENT_IRQHandler, %function
PDM_HWVAD_EVENT_IRQHandler:
    ldr   r0,=PDM_HWVAD_EVENT_DriverIRQHandler
    bx    r0
    .size PDM_HWVAD_EVENT_IRQHandler, . - PDM_HWVAD_EVENT_IRQHandler

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
    .weak SENSE_HYPERVISOR_IRQHandler
    .type SENSE_HYPERVISOR_IRQHandler, %function
SENSE_HYPERVISOR_IRQHandler:
    ldr   r0,=SENSE_HYPERVISOR_DriverIRQHandler
    bx    r0
    .size SENSE_HYPERVISOR_IRQHandler, . - SENSE_HYPERVISOR_IRQHandler

    .align 1
    .thumb_func
    .weak SENSE_SECURE_VIOLATION_IRQHandler
    .type SENSE_SECURE_VIOLATION_IRQHandler, %function
SENSE_SECURE_VIOLATION_IRQHandler:
    ldr   r0,=SENSE_SECURE_VIOLATION_DriverIRQHandler
    bx    r0
    .size SENSE_SECURE_VIOLATION_IRQHandler, . - SENSE_SECURE_VIOLATION_IRQHandler

    .align 1
    .thumb_func
    .weak MEDIA_HYPERVISOR_IRQHandler
    .type MEDIA_HYPERVISOR_IRQHandler, %function
MEDIA_HYPERVISOR_IRQHandler:
    ldr   r0,=MEDIA_HYPERVISOR_DriverIRQHandler
    bx    r0
    .size MEDIA_HYPERVISOR_IRQHandler, . - MEDIA_HYPERVISOR_IRQHandler

    .align 1
    .thumb_func
    .weak MEDIA_SECURE_VIOLATION_IRQHandler
    .type MEDIA_SECURE_VIOLATION_IRQHandler, %function
MEDIA_SECURE_VIOLATION_IRQHandler:
    ldr   r0,=MEDIA_SECURE_VIOLATION_DriverIRQHandler
    bx    r0
    .size MEDIA_SECURE_VIOLATION_IRQHandler, . - MEDIA_SECURE_VIOLATION_IRQHandler

    .align 1
    .thumb_func
    .weak RTC0_ALARM_IRQHandler
    .type RTC0_ALARM_IRQHandler, %function
RTC0_ALARM_IRQHandler:
    ldr   r0,=RTC0_ALARM_DriverIRQHandler
    bx    r0
    .size RTC0_ALARM_IRQHandler, . - RTC0_ALARM_IRQHandler

    .align 1
    .thumb_func
    .weak RTC0_IRQHandler
    .type RTC0_IRQHandler, %function
RTC0_IRQHandler:
    ldr   r0,=RTC0_DriverIRQHandler
    bx    r0
    .size RTC0_IRQHandler, . - RTC0_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved44_IRQHandler
    .type Reserved44_IRQHandler, %function
Reserved44_IRQHandler:
    ldr   r0,=Reserved44_DriverIRQHandler
    bx    r0
    .size Reserved44_IRQHandler, . - Reserved44_IRQHandler

    .align 1
    .thumb_func
    .weak MU0_A_IRQHandler
    .type MU0_A_IRQHandler, %function
MU0_A_IRQHandler:
    ldr   r0,=MU0_A_DriverIRQHandler
    bx    r0
    .size MU0_A_IRQHandler, . - MU0_A_IRQHandler

    .align 1
    .thumb_func
    .weak MU1_A_IRQHandler
    .type MU1_A_IRQHandler, %function
MU1_A_IRQHandler:
    ldr   r0,=MU1_A_DriverIRQHandler
    bx    r0
    .size MU1_A_IRQHandler, . - MU1_A_IRQHandler

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
    .weak LP_FLEXCOMM6_IRQHandler
    .type LP_FLEXCOMM6_IRQHandler, %function
LP_FLEXCOMM6_IRQHandler:
    ldr   r0,=LP_FLEXCOMM6_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM6_IRQHandler, . - LP_FLEXCOMM6_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM7_IRQHandler
    .type LP_FLEXCOMM7_IRQHandler, %function
LP_FLEXCOMM7_IRQHandler:
    ldr   r0,=LP_FLEXCOMM7_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM7_IRQHandler, . - LP_FLEXCOMM7_IRQHandler

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
    .weak I3C0_IRQHandler
    .type I3C0_IRQHandler, %function
I3C0_IRQHandler:
    ldr   r0,=I3C0_DriverIRQHandler
    bx    r0
    .size I3C0_IRQHandler, . - I3C0_IRQHandler

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
    .weak WDT0_IRQHandler
    .type WDT0_IRQHandler, %function
WDT0_IRQHandler:
    ldr   r0,=WDT0_DriverIRQHandler
    bx    r0
    .size WDT0_IRQHandler, . - WDT0_IRQHandler

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
    .weak USBPHY0_IRQHandler
    .type USBPHY0_IRQHandler, %function
USBPHY0_IRQHandler:
    ldr   r0,=USBPHY0_DriverIRQHandler
    bx    r0
    .size USBPHY0_IRQHandler, . - USBPHY0_IRQHandler

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
    .weak PMIC_IRQN_IRQHandler
    .type PMIC_IRQN_IRQHandler, %function
PMIC_IRQN_IRQHandler:
    ldr   r0,=PMIC_IRQN_DriverIRQHandler
    bx    r0
    .size PMIC_IRQN_IRQHandler, . - PMIC_IRQN_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM8_IRQHandler
    .type LP_FLEXCOMM8_IRQHandler, %function
LP_FLEXCOMM8_IRQHandler:
    ldr   r0,=LP_FLEXCOMM8_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM8_IRQHandler, . - LP_FLEXCOMM8_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM9_IRQHandler
    .type LP_FLEXCOMM9_IRQHandler, %function
LP_FLEXCOMM9_IRQHandler:
    ldr   r0,=LP_FLEXCOMM9_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM9_IRQHandler, . - LP_FLEXCOMM9_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM10_IRQHandler
    .type LP_FLEXCOMM10_IRQHandler, %function
LP_FLEXCOMM10_IRQHandler:
    ldr   r0,=LP_FLEXCOMM10_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM10_IRQHandler, . - LP_FLEXCOMM10_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM11_IRQHandler
    .type LP_FLEXCOMM11_IRQHandler, %function
LP_FLEXCOMM11_IRQHandler:
    ldr   r0,=LP_FLEXCOMM11_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM11_IRQHandler, . - LP_FLEXCOMM11_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM12_IRQHandler
    .type LP_FLEXCOMM12_IRQHandler, %function
LP_FLEXCOMM12_IRQHandler:
    ldr   r0,=LP_FLEXCOMM12_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM12_IRQHandler, . - LP_FLEXCOMM12_IRQHandler

    .align 1
    .thumb_func
    .weak LP_FLEXCOMM13_IRQHandler
    .type LP_FLEXCOMM13_IRQHandler, %function
LP_FLEXCOMM13_IRQHandler:
    ldr   r0,=LP_FLEXCOMM13_DriverIRQHandler
    bx    r0
    .size LP_FLEXCOMM13_IRQHandler, . - LP_FLEXCOMM13_IRQHandler

    .align 1
    .thumb_func
    .weak LPSPI16_IRQHandler
    .type LPSPI16_IRQHandler, %function
LPSPI16_IRQHandler:
    ldr   r0,=LPSPI16_DriverIRQHandler
    bx    r0
    .size LPSPI16_IRQHandler, . - LPSPI16_IRQHandler

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
    .weak FLEXIO_IRQHandler
    .type FLEXIO_IRQHandler, %function
FLEXIO_IRQHandler:
    ldr   r0,=FLEXIO_DriverIRQHandler
    bx    r0
    .size FLEXIO_IRQHandler, . - FLEXIO_IRQHandler

    .align 1
    .thumb_func
    .weak LCDIF_IRQHandler
    .type LCDIF_IRQHandler, %function
LCDIF_IRQHandler:
    ldr   r0,=LCDIF_DriverIRQHandler
    bx    r0
    .size LCDIF_IRQHandler, . - LCDIF_IRQHandler

    .align 1
    .thumb_func
    .weak VGPU_IRQHandler
    .type VGPU_IRQHandler, %function
VGPU_IRQHandler:
    ldr   r0,=VGPU_DriverIRQHandler
    bx    r0
    .size VGPU_IRQHandler, . - VGPU_IRQHandler

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
    .weak EDMA0_CH0_IRQHandler
    .type EDMA0_CH0_IRQHandler, %function
EDMA0_CH0_IRQHandler:
    ldr   r0,=EDMA0_CH0_DriverIRQHandler
    bx    r0
    .size EDMA0_CH0_IRQHandler, . - EDMA0_CH0_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH1_IRQHandler
    .type EDMA0_CH1_IRQHandler, %function
EDMA0_CH1_IRQHandler:
    ldr   r0,=EDMA0_CH1_DriverIRQHandler
    bx    r0
    .size EDMA0_CH1_IRQHandler, . - EDMA0_CH1_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH2_IRQHandler
    .type EDMA0_CH2_IRQHandler, %function
EDMA0_CH2_IRQHandler:
    ldr   r0,=EDMA0_CH2_DriverIRQHandler
    bx    r0
    .size EDMA0_CH2_IRQHandler, . - EDMA0_CH2_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH3_IRQHandler
    .type EDMA0_CH3_IRQHandler, %function
EDMA0_CH3_IRQHandler:
    ldr   r0,=EDMA0_CH3_DriverIRQHandler
    bx    r0
    .size EDMA0_CH3_IRQHandler, . - EDMA0_CH3_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH4_IRQHandler
    .type EDMA0_CH4_IRQHandler, %function
EDMA0_CH4_IRQHandler:
    ldr   r0,=EDMA0_CH4_DriverIRQHandler
    bx    r0
    .size EDMA0_CH4_IRQHandler, . - EDMA0_CH4_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH5_IRQHandler
    .type EDMA0_CH5_IRQHandler, %function
EDMA0_CH5_IRQHandler:
    ldr   r0,=EDMA0_CH5_DriverIRQHandler
    bx    r0
    .size EDMA0_CH5_IRQHandler, . - EDMA0_CH5_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH6_IRQHandler
    .type EDMA0_CH6_IRQHandler, %function
EDMA0_CH6_IRQHandler:
    ldr   r0,=EDMA0_CH6_DriverIRQHandler
    bx    r0
    .size EDMA0_CH6_IRQHandler, . - EDMA0_CH6_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH7_IRQHandler
    .type EDMA0_CH7_IRQHandler, %function
EDMA0_CH7_IRQHandler:
    ldr   r0,=EDMA0_CH7_DriverIRQHandler
    bx    r0
    .size EDMA0_CH7_IRQHandler, . - EDMA0_CH7_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH8_IRQHandler
    .type EDMA0_CH8_IRQHandler, %function
EDMA0_CH8_IRQHandler:
    ldr   r0,=EDMA0_CH8_DriverIRQHandler
    bx    r0
    .size EDMA0_CH8_IRQHandler, . - EDMA0_CH8_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH9_IRQHandler
    .type EDMA0_CH9_IRQHandler, %function
EDMA0_CH9_IRQHandler:
    ldr   r0,=EDMA0_CH9_DriverIRQHandler
    bx    r0
    .size EDMA0_CH9_IRQHandler, . - EDMA0_CH9_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH10_IRQHandler
    .type EDMA0_CH10_IRQHandler, %function
EDMA0_CH10_IRQHandler:
    ldr   r0,=EDMA0_CH10_DriverIRQHandler
    bx    r0
    .size EDMA0_CH10_IRQHandler, . - EDMA0_CH10_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH11_IRQHandler
    .type EDMA0_CH11_IRQHandler, %function
EDMA0_CH11_IRQHandler:
    ldr   r0,=EDMA0_CH11_DriverIRQHandler
    bx    r0
    .size EDMA0_CH11_IRQHandler, . - EDMA0_CH11_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH12_IRQHandler
    .type EDMA0_CH12_IRQHandler, %function
EDMA0_CH12_IRQHandler:
    ldr   r0,=EDMA0_CH12_DriverIRQHandler
    bx    r0
    .size EDMA0_CH12_IRQHandler, . - EDMA0_CH12_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH13_IRQHandler
    .type EDMA0_CH13_IRQHandler, %function
EDMA0_CH13_IRQHandler:
    ldr   r0,=EDMA0_CH13_DriverIRQHandler
    bx    r0
    .size EDMA0_CH13_IRQHandler, . - EDMA0_CH13_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH14_IRQHandler
    .type EDMA0_CH14_IRQHandler, %function
EDMA0_CH14_IRQHandler:
    ldr   r0,=EDMA0_CH14_DriverIRQHandler
    bx    r0
    .size EDMA0_CH14_IRQHandler, . - EDMA0_CH14_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA0_CH15_IRQHandler
    .type EDMA0_CH15_IRQHandler, %function
EDMA0_CH15_IRQHandler:
    ldr   r0,=EDMA0_CH15_DriverIRQHandler
    bx    r0
    .size EDMA0_CH15_IRQHandler, . - EDMA0_CH15_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH0_IRQHandler
    .type EDMA1_CH0_IRQHandler, %function
EDMA1_CH0_IRQHandler:
    ldr   r0,=EDMA1_CH0_DriverIRQHandler
    bx    r0
    .size EDMA1_CH0_IRQHandler, . - EDMA1_CH0_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH1_IRQHandler
    .type EDMA1_CH1_IRQHandler, %function
EDMA1_CH1_IRQHandler:
    ldr   r0,=EDMA1_CH1_DriverIRQHandler
    bx    r0
    .size EDMA1_CH1_IRQHandler, . - EDMA1_CH1_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH2_IRQHandler
    .type EDMA1_CH2_IRQHandler, %function
EDMA1_CH2_IRQHandler:
    ldr   r0,=EDMA1_CH2_DriverIRQHandler
    bx    r0
    .size EDMA1_CH2_IRQHandler, . - EDMA1_CH2_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH3_IRQHandler
    .type EDMA1_CH3_IRQHandler, %function
EDMA1_CH3_IRQHandler:
    ldr   r0,=EDMA1_CH3_DriverIRQHandler
    bx    r0
    .size EDMA1_CH3_IRQHandler, . - EDMA1_CH3_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH4_IRQHandler
    .type EDMA1_CH4_IRQHandler, %function
EDMA1_CH4_IRQHandler:
    ldr   r0,=EDMA1_CH4_DriverIRQHandler
    bx    r0
    .size EDMA1_CH4_IRQHandler, . - EDMA1_CH4_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH5_IRQHandler
    .type EDMA1_CH5_IRQHandler, %function
EDMA1_CH5_IRQHandler:
    ldr   r0,=EDMA1_CH5_DriverIRQHandler
    bx    r0
    .size EDMA1_CH5_IRQHandler, . - EDMA1_CH5_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH6_IRQHandler
    .type EDMA1_CH6_IRQHandler, %function
EDMA1_CH6_IRQHandler:
    ldr   r0,=EDMA1_CH6_DriverIRQHandler
    bx    r0
    .size EDMA1_CH6_IRQHandler, . - EDMA1_CH6_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH7_IRQHandler
    .type EDMA1_CH7_IRQHandler, %function
EDMA1_CH7_IRQHandler:
    ldr   r0,=EDMA1_CH7_DriverIRQHandler
    bx    r0
    .size EDMA1_CH7_IRQHandler, . - EDMA1_CH7_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH8_IRQHandler
    .type EDMA1_CH8_IRQHandler, %function
EDMA1_CH8_IRQHandler:
    ldr   r0,=EDMA1_CH8_DriverIRQHandler
    bx    r0
    .size EDMA1_CH8_IRQHandler, . - EDMA1_CH8_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH9_IRQHandler
    .type EDMA1_CH9_IRQHandler, %function
EDMA1_CH9_IRQHandler:
    ldr   r0,=EDMA1_CH9_DriverIRQHandler
    bx    r0
    .size EDMA1_CH9_IRQHandler, . - EDMA1_CH9_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH10_IRQHandler
    .type EDMA1_CH10_IRQHandler, %function
EDMA1_CH10_IRQHandler:
    ldr   r0,=EDMA1_CH10_DriverIRQHandler
    bx    r0
    .size EDMA1_CH10_IRQHandler, . - EDMA1_CH10_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH11_IRQHandler
    .type EDMA1_CH11_IRQHandler, %function
EDMA1_CH11_IRQHandler:
    ldr   r0,=EDMA1_CH11_DriverIRQHandler
    bx    r0
    .size EDMA1_CH11_IRQHandler, . - EDMA1_CH11_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH12_IRQHandler
    .type EDMA1_CH12_IRQHandler, %function
EDMA1_CH12_IRQHandler:
    ldr   r0,=EDMA1_CH12_DriverIRQHandler
    bx    r0
    .size EDMA1_CH12_IRQHandler, . - EDMA1_CH12_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH13_IRQHandler
    .type EDMA1_CH13_IRQHandler, %function
EDMA1_CH13_IRQHandler:
    ldr   r0,=EDMA1_CH13_DriverIRQHandler
    bx    r0
    .size EDMA1_CH13_IRQHandler, . - EDMA1_CH13_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH14_IRQHandler
    .type EDMA1_CH14_IRQHandler, %function
EDMA1_CH14_IRQHandler:
    ldr   r0,=EDMA1_CH14_DriverIRQHandler
    bx    r0
    .size EDMA1_CH14_IRQHandler, . - EDMA1_CH14_IRQHandler

    .align 1
    .thumb_func
    .weak EDMA1_CH15_IRQHandler
    .type EDMA1_CH15_IRQHandler, %function
EDMA1_CH15_IRQHandler:
    ldr   r0,=EDMA1_CH15_DriverIRQHandler
    bx    r0
    .size EDMA1_CH15_IRQHandler, . - EDMA1_CH15_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO00_IRQHandler
    .type GPIO00_IRQHandler, %function
GPIO00_IRQHandler:
    ldr   r0,=GPIO00_DriverIRQHandler
    bx    r0
    .size GPIO00_IRQHandler, . - GPIO00_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO01_IRQHandler
    .type GPIO01_IRQHandler, %function
GPIO01_IRQHandler:
    ldr   r0,=GPIO01_DriverIRQHandler
    bx    r0
    .size GPIO01_IRQHandler, . - GPIO01_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO10_IRQHandler
    .type GPIO10_IRQHandler, %function
GPIO10_IRQHandler:
    ldr   r0,=GPIO10_DriverIRQHandler
    bx    r0
    .size GPIO10_IRQHandler, . - GPIO10_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO11_IRQHandler
    .type GPIO11_IRQHandler, %function
GPIO11_IRQHandler:
    ldr   r0,=GPIO11_DriverIRQHandler
    bx    r0
    .size GPIO11_IRQHandler, . - GPIO11_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO20_IRQHandler
    .type GPIO20_IRQHandler, %function
GPIO20_IRQHandler:
    ldr   r0,=GPIO20_DriverIRQHandler
    bx    r0
    .size GPIO20_IRQHandler, . - GPIO20_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO21_IRQHandler
    .type GPIO21_IRQHandler, %function
GPIO21_IRQHandler:
    ldr   r0,=GPIO21_DriverIRQHandler
    bx    r0
    .size GPIO21_IRQHandler, . - GPIO21_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO30_IRQHandler
    .type GPIO30_IRQHandler, %function
GPIO30_IRQHandler:
    ldr   r0,=GPIO30_DriverIRQHandler
    bx    r0
    .size GPIO30_IRQHandler, . - GPIO30_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO31_IRQHandler
    .type GPIO31_IRQHandler, %function
GPIO31_IRQHandler:
    ldr   r0,=GPIO31_DriverIRQHandler
    bx    r0
    .size GPIO31_IRQHandler, . - GPIO31_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO40_IRQHandler
    .type GPIO40_IRQHandler, %function
GPIO40_IRQHandler:
    ldr   r0,=GPIO40_DriverIRQHandler
    bx    r0
    .size GPIO40_IRQHandler, . - GPIO40_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO41_IRQHandler
    .type GPIO41_IRQHandler, %function
GPIO41_IRQHandler:
    ldr   r0,=GPIO41_DriverIRQHandler
    bx    r0
    .size GPIO41_IRQHandler, . - GPIO41_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO50_IRQHandler
    .type GPIO50_IRQHandler, %function
GPIO50_IRQHandler:
    ldr   r0,=GPIO50_DriverIRQHandler
    bx    r0
    .size GPIO50_IRQHandler, . - GPIO50_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO51_IRQHandler
    .type GPIO51_IRQHandler, %function
GPIO51_IRQHandler:
    ldr   r0,=GPIO51_DriverIRQHandler
    bx    r0
    .size GPIO51_IRQHandler, . - GPIO51_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO60_IRQHandler
    .type GPIO60_IRQHandler, %function
GPIO60_IRQHandler:
    ldr   r0,=GPIO60_DriverIRQHandler
    bx    r0
    .size GPIO60_IRQHandler, . - GPIO60_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO61_IRQHandler
    .type GPIO61_IRQHandler, %function
GPIO61_IRQHandler:
    ldr   r0,=GPIO61_DriverIRQHandler
    bx    r0
    .size GPIO61_IRQHandler, . - GPIO61_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO70_IRQHandler
    .type GPIO70_IRQHandler, %function
GPIO70_IRQHandler:
    ldr   r0,=GPIO70_DriverIRQHandler
    bx    r0
    .size GPIO70_IRQHandler, . - GPIO70_IRQHandler

    .align 1
    .thumb_func
    .weak GPIO71_IRQHandler
    .type GPIO71_IRQHandler, %function
GPIO71_IRQHandler:
    ldr   r0,=GPIO71_DriverIRQHandler
    bx    r0
    .size GPIO71_IRQHandler, . - GPIO71_IRQHandler

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
    .weak XSPI0_IRQHandler
    .type XSPI0_IRQHandler, %function
XSPI0_IRQHandler:
    ldr   r0,=XSPI0_DriverIRQHandler
    bx    r0
    .size XSPI0_IRQHandler, . - XSPI0_IRQHandler

    .align 1
    .thumb_func
    .weak XSPI1_IRQHandler
    .type XSPI1_IRQHandler, %function
XSPI1_IRQHandler:
    ldr   r0,=XSPI1_DriverIRQHandler
    bx    r0
    .size XSPI1_IRQHandler, . - XSPI1_IRQHandler

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
    .weak MMU0_IRQHandler
    .type MMU0_IRQHandler, %function
MMU0_IRQHandler:
    ldr   r0,=MMU0_DriverIRQHandler
    bx    r0
    .size MMU0_IRQHandler, . - MMU0_IRQHandler

    .align 1
    .thumb_func
    .weak MMU1_IRQHandler
    .type MMU1_IRQHandler, %function
MMU1_IRQHandler:
    ldr   r0,=MMU1_DriverIRQHandler
    bx    r0
    .size MMU1_IRQHandler, . - MMU1_IRQHandler

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
    .weak Freqme_IRQHandler
    .type Freqme_IRQHandler, %function
Freqme_IRQHandler:
    ldr   r0,=Freqme_DriverIRQHandler
    bx    r0
    .size Freqme_IRQHandler, . - Freqme_IRQHandler

    .align 1
    .thumb_func
    .weak GDET0_IRQHandler
    .type GDET0_IRQHandler, %function
GDET0_IRQHandler:
    ldr   r0,=GDET0_DriverIRQHandler
    bx    r0
    .size GDET0_IRQHandler, . - GDET0_IRQHandler

    .align 1
    .thumb_func
    .weak GDET1_IRQHandler
    .type GDET1_IRQHandler, %function
GDET1_IRQHandler:
    ldr   r0,=GDET1_DriverIRQHandler
    bx    r0
    .size GDET1_IRQHandler, . - GDET1_IRQHandler

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
    .weak CDOG0_IRQHandler
    .type CDOG0_IRQHandler, %function
CDOG0_IRQHandler:
    ldr   r0,=CDOG0_DriverIRQHandler
    bx    r0
    .size CDOG0_IRQHandler, . - CDOG0_IRQHandler

    .align 1
    .thumb_func
    .weak CDOG1_IRQHandler
    .type CDOG1_IRQHandler, %function
CDOG1_IRQHandler:
    ldr   r0,=CDOG1_DriverIRQHandler
    bx    r0
    .size CDOG1_IRQHandler, . - CDOG1_IRQHandler

    .align 1
    .thumb_func
    .weak CDOG2_IRQHandler
    .type CDOG2_IRQHandler, %function
CDOG2_IRQHandler:
    ldr   r0,=CDOG2_DriverIRQHandler
    bx    r0
    .size CDOG2_IRQHandler, . - CDOG2_IRQHandler

    .align 1
    .thumb_func
    .weak ITRC0_IRQHandler
    .type ITRC0_IRQHandler, %function
ITRC0_IRQHandler:
    ldr   r0,=ITRC0_DriverIRQHandler
    bx    r0
    .size ITRC0_IRQHandler, . - ITRC0_IRQHandler

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
    .weak PKC_IRQHandler
    .type PKC_IRQHandler, %function
PKC_IRQHandler:
    ldr   r0,=PKC_DriverIRQHandler
    bx    r0
    .size PKC_IRQHandler, . - PKC_IRQHandler

    .align 1
    .thumb_func
    .weak OSCCA_IRQHandler
    .type OSCCA_IRQHandler, %function
OSCCA_IRQHandler:
    ldr   r0,=OSCCA_DriverIRQHandler
    bx    r0
    .size OSCCA_IRQHandler, . - OSCCA_IRQHandler

    .align 1
    .thumb_func
    .weak SLEEPCON0_IRQHandler
    .type SLEEPCON0_IRQHandler, %function
SLEEPCON0_IRQHandler:
    ldr   r0,=SLEEPCON0_DriverIRQHandler
    bx    r0
    .size SLEEPCON0_IRQHandler, . - SLEEPCON0_IRQHandler

    .align 1
    .thumb_func
    .weak CPU0_IRQHandler
    .type CPU0_IRQHandler, %function
CPU0_IRQHandler:
    ldr   r0,=CPU0_DriverIRQHandler
    bx    r0
    .size CPU0_IRQHandler, . - CPU0_IRQHandler

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
    .weak JPEGDEC_IRQHandler
    .type JPEGDEC_IRQHandler, %function
JPEGDEC_IRQHandler:
    ldr   r0,=JPEGDEC_DriverIRQHandler
    bx    r0
    .size JPEGDEC_IRQHandler, . - JPEGDEC_IRQHandler

    .align 1
    .thumb_func
    .weak PNGDEC_IRQHandler
    .type PNGDEC_IRQHandler, %function
PNGDEC_IRQHandler:
    ldr   r0,=PNGDEC_DriverIRQHandler
    bx    r0
    .size PNGDEC_IRQHandler, . - PNGDEC_IRQHandler

    .align 1
    .thumb_func
    .weak NPU_IRQHandler
    .type NPU_IRQHandler, %function
NPU_IRQHandler:
    ldr   r0,=NPU_DriverIRQHandler
    bx    r0
    .size NPU_IRQHandler, . - NPU_IRQHandler

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
    .weak GLIKEY0_IRQHandler
    .type GLIKEY0_IRQHandler, %function
GLIKEY0_IRQHandler:
    ldr   r0,=GLIKEY0_DriverIRQHandler
    bx    r0
    .size GLIKEY0_IRQHandler, . - GLIKEY0_IRQHandler

    .align 1
    .thumb_func
    .weak GLIKEY2_IRQHandler
    .type GLIKEY2_IRQHandler, %function
GLIKEY2_IRQHandler:
    ldr   r0,=GLIKEY2_DriverIRQHandler
    bx    r0
    .size GLIKEY2_IRQHandler, . - GLIKEY2_IRQHandler

    .align 1
    .thumb_func
    .weak GLIKEY3_IRQHandler
    .type GLIKEY3_IRQHandler, %function
GLIKEY3_IRQHandler:
    ldr   r0,=GLIKEY3_DriverIRQHandler
    bx    r0
    .size GLIKEY3_IRQHandler, . - GLIKEY3_IRQHandler

    .align 1
    .thumb_func
    .weak GLIKEY5_IRQHandler
    .type GLIKEY5_IRQHandler, %function
GLIKEY5_IRQHandler:
    ldr   r0,=GLIKEY5_DriverIRQHandler
    bx    r0
    .size GLIKEY5_IRQHandler, . - GLIKEY5_IRQHandler

    .align 1
    .thumb_func
    .weak PVTS0_CPU0_IRQHandler
    .type PVTS0_CPU0_IRQHandler, %function
PVTS0_CPU0_IRQHandler:
    ldr   r0,=PVTS0_CPU0_DriverIRQHandler
    bx    r0
    .size PVTS0_CPU0_IRQHandler, . - PVTS0_CPU0_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved167_IRQHandler
    .type Reserved167_IRQHandler, %function
Reserved167_IRQHandler:
    ldr   r0,=Reserved167_DriverIRQHandler
    bx    r0
    .size Reserved167_IRQHandler, . - Reserved167_IRQHandler

    .align 1
    .thumb_func
    .weak PVTS0_HIFI4_IRQHandler
    .type PVTS0_HIFI4_IRQHandler, %function
PVTS0_HIFI4_IRQHandler:
    ldr   r0,=PVTS0_HIFI4_DriverIRQHandler
    bx    r0
    .size PVTS0_HIFI4_IRQHandler, . - PVTS0_HIFI4_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved169_IRQHandler
    .type Reserved169_IRQHandler, %function
Reserved169_IRQHandler:
    ldr   r0,=Reserved169_DriverIRQHandler
    bx    r0
    .size Reserved169_IRQHandler, . - Reserved169_IRQHandler

    .align 1
    .thumb_func
    .weak FRO0_IRQHandler
    .type FRO0_IRQHandler, %function
FRO0_IRQHandler:
    ldr   r0,=FRO0_DriverIRQHandler
    bx    r0
    .size FRO0_IRQHandler, . - FRO0_IRQHandler

    .align 1
    .thumb_func
    .weak FRO1_IRQHandler
    .type FRO1_IRQHandler, %function
FRO1_IRQHandler:
    ldr   r0,=FRO1_DriverIRQHandler
    bx    r0
    .size FRO1_IRQHandler, . - FRO1_IRQHandler

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
    .weak OCOTP_IRQHandler
    .type OCOTP_IRQHandler, %function
OCOTP_IRQHandler:
    ldr   r0,=OCOTP_DriverIRQHandler
    bx    r0
    .size OCOTP_IRQHandler, . - OCOTP_IRQHandler


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
    def_irq_handler    UTICK0_DriverIRQHandler
    def_irq_handler    MRT0_DriverIRQHandler
    def_irq_handler    CTIMER0_DriverIRQHandler
    def_irq_handler    CTIMER1_DriverIRQHandler
    def_irq_handler    SCT0_DriverIRQHandler
    def_irq_handler    CTIMER3_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM0_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM1_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM2_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM3_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM4_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM5_DriverIRQHandler
    def_irq_handler    LPSPI14_DriverIRQHandler
    def_irq_handler    LPI2C15_DriverIRQHandler
    def_irq_handler    ADC_DriverIRQHandler
    def_irq_handler    SDADC_DriverIRQHandler
    def_irq_handler    ACMP_DriverIRQHandler
    def_irq_handler    PDM_EVENT_DriverIRQHandler
    def_irq_handler    PDM_HWVAD_EVENT_DriverIRQHandler
    def_irq_handler    HYPERVISOR_DriverIRQHandler
    def_irq_handler    SECURE_VIOLATION_DriverIRQHandler
    def_irq_handler    SENSE_HYPERVISOR_DriverIRQHandler
    def_irq_handler    SENSE_SECURE_VIOLATION_DriverIRQHandler
    def_irq_handler    MEDIA_HYPERVISOR_DriverIRQHandler
    def_irq_handler    MEDIA_SECURE_VIOLATION_DriverIRQHandler
    def_irq_handler    RTC0_ALARM_DriverIRQHandler
    def_irq_handler    RTC0_DriverIRQHandler
    def_irq_handler    Reserved44_DriverIRQHandler
    def_irq_handler    MU0_A_DriverIRQHandler
    def_irq_handler    MU1_A_DriverIRQHandler
    def_irq_handler    Reserved47_DriverIRQHandler
    def_irq_handler    CTIMER2_DriverIRQHandler
    def_irq_handler    CTIMER4_DriverIRQHandler
    def_irq_handler    OS_EVENT_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM6_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM7_DriverIRQHandler
    def_irq_handler    USDHC0_DriverIRQHandler
    def_irq_handler    USDHC1_DriverIRQHandler
    def_irq_handler    I3C0_DriverIRQHandler
    def_irq_handler    USB0_DriverIRQHandler
    def_irq_handler    USB1_DriverIRQHandler
    def_irq_handler    WDT0_DriverIRQHandler
    def_irq_handler    WDT1_DriverIRQHandler
    def_irq_handler    USBPHY0_DriverIRQHandler
    def_irq_handler    PUF_DriverIRQHandler
    def_irq_handler    PMIC_IRQN_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM8_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM9_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM10_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM11_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM12_DriverIRQHandler
    def_irq_handler    LP_FLEXCOMM13_DriverIRQHandler
    def_irq_handler    LPSPI16_DriverIRQHandler
    def_irq_handler    I3C1_DriverIRQHandler
    def_irq_handler    FLEXIO_DriverIRQHandler
    def_irq_handler    LCDIF_DriverIRQHandler
    def_irq_handler    VGPU_DriverIRQHandler
    def_irq_handler    MIPI_DriverIRQHandler
    def_irq_handler    EDMA0_CH0_DriverIRQHandler
    def_irq_handler    EDMA0_CH1_DriverIRQHandler
    def_irq_handler    EDMA0_CH2_DriverIRQHandler
    def_irq_handler    EDMA0_CH3_DriverIRQHandler
    def_irq_handler    EDMA0_CH4_DriverIRQHandler
    def_irq_handler    EDMA0_CH5_DriverIRQHandler
    def_irq_handler    EDMA0_CH6_DriverIRQHandler
    def_irq_handler    EDMA0_CH7_DriverIRQHandler
    def_irq_handler    EDMA0_CH8_DriverIRQHandler
    def_irq_handler    EDMA0_CH9_DriverIRQHandler
    def_irq_handler    EDMA0_CH10_DriverIRQHandler
    def_irq_handler    EDMA0_CH11_DriverIRQHandler
    def_irq_handler    EDMA0_CH12_DriverIRQHandler
    def_irq_handler    EDMA0_CH13_DriverIRQHandler
    def_irq_handler    EDMA0_CH14_DriverIRQHandler
    def_irq_handler    EDMA0_CH15_DriverIRQHandler
    def_irq_handler    EDMA1_CH0_DriverIRQHandler
    def_irq_handler    EDMA1_CH1_DriverIRQHandler
    def_irq_handler    EDMA1_CH2_DriverIRQHandler
    def_irq_handler    EDMA1_CH3_DriverIRQHandler
    def_irq_handler    EDMA1_CH4_DriverIRQHandler
    def_irq_handler    EDMA1_CH5_DriverIRQHandler
    def_irq_handler    EDMA1_CH6_DriverIRQHandler
    def_irq_handler    EDMA1_CH7_DriverIRQHandler
    def_irq_handler    EDMA1_CH8_DriverIRQHandler
    def_irq_handler    EDMA1_CH9_DriverIRQHandler
    def_irq_handler    EDMA1_CH10_DriverIRQHandler
    def_irq_handler    EDMA1_CH11_DriverIRQHandler
    def_irq_handler    EDMA1_CH12_DriverIRQHandler
    def_irq_handler    EDMA1_CH13_DriverIRQHandler
    def_irq_handler    EDMA1_CH14_DriverIRQHandler
    def_irq_handler    EDMA1_CH15_DriverIRQHandler
    def_irq_handler    GPIO00_DriverIRQHandler
    def_irq_handler    GPIO01_DriverIRQHandler
    def_irq_handler    GPIO10_DriverIRQHandler
    def_irq_handler    GPIO11_DriverIRQHandler
    def_irq_handler    GPIO20_DriverIRQHandler
    def_irq_handler    GPIO21_DriverIRQHandler
    def_irq_handler    GPIO30_DriverIRQHandler
    def_irq_handler    GPIO31_DriverIRQHandler
    def_irq_handler    GPIO40_DriverIRQHandler
    def_irq_handler    GPIO41_DriverIRQHandler
    def_irq_handler    GPIO50_DriverIRQHandler
    def_irq_handler    GPIO51_DriverIRQHandler
    def_irq_handler    GPIO60_DriverIRQHandler
    def_irq_handler    GPIO61_DriverIRQHandler
    def_irq_handler    GPIO70_DriverIRQHandler
    def_irq_handler    GPIO71_DriverIRQHandler
    def_irq_handler    PIN_INT0_DriverIRQHandler
    def_irq_handler    PIN_INT1_DriverIRQHandler
    def_irq_handler    PIN_INT2_DriverIRQHandler
    def_irq_handler    PIN_INT3_DriverIRQHandler
    def_irq_handler    PIN_INT4_DriverIRQHandler
    def_irq_handler    PIN_INT5_DriverIRQHandler
    def_irq_handler    PIN_INT6_DriverIRQHandler
    def_irq_handler    PIN_INT7_DriverIRQHandler
    def_irq_handler    SAI0_DriverIRQHandler
    def_irq_handler    SAI1_DriverIRQHandler
    def_irq_handler    SAI2_DriverIRQHandler
    def_irq_handler    XSPI0_DriverIRQHandler
    def_irq_handler    XSPI1_DriverIRQHandler
    def_irq_handler    XSPI2_DriverIRQHandler
    def_irq_handler    MMU0_DriverIRQHandler
    def_irq_handler    MMU1_DriverIRQHandler
    def_irq_handler    MMU2_DriverIRQHandler
    def_irq_handler    Freqme_DriverIRQHandler
    def_irq_handler    GDET0_DriverIRQHandler
    def_irq_handler    GDET1_DriverIRQHandler
    def_irq_handler    GDET2_DriverIRQHandler
    def_irq_handler    GDET3_DriverIRQHandler
    def_irq_handler    CDOG0_DriverIRQHandler
    def_irq_handler    CDOG1_DriverIRQHandler
    def_irq_handler    CDOG2_DriverIRQHandler
    def_irq_handler    ITRC0_DriverIRQHandler
    def_irq_handler    ELS_DriverIRQHandler
    def_irq_handler    PKC_DriverIRQHandler
    def_irq_handler    OSCCA_DriverIRQHandler
    def_irq_handler    SLEEPCON0_DriverIRQHandler
    def_irq_handler    CPU0_DriverIRQHandler
    def_irq_handler    PMC_DriverIRQHandler
    def_irq_handler    JPEGDEC_DriverIRQHandler
    def_irq_handler    PNGDEC_DriverIRQHandler
    def_irq_handler    NPU_DriverIRQHandler
    def_irq_handler    TRNG_DriverIRQHandler
    def_irq_handler    TEMPDET0_DriverIRQHandler
    def_irq_handler    TEMPDET1_DriverIRQHandler
    def_irq_handler    EZHV_DriverIRQHandler
    def_irq_handler    GLIKEY0_DriverIRQHandler
    def_irq_handler    GLIKEY2_DriverIRQHandler
    def_irq_handler    GLIKEY3_DriverIRQHandler
    def_irq_handler    GLIKEY5_DriverIRQHandler
    def_irq_handler    PVTS0_CPU0_DriverIRQHandler
    def_irq_handler    Reserved167_DriverIRQHandler
    def_irq_handler    PVTS0_HIFI4_DriverIRQHandler
    def_irq_handler    Reserved169_DriverIRQHandler
    def_irq_handler    FRO0_DriverIRQHandler
    def_irq_handler    FRO1_DriverIRQHandler
    def_irq_handler    FRO2_DriverIRQHandler
    def_irq_handler    OCOTP_DriverIRQHandler

    .end
