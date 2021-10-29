/* ------------------------------------------------------------------------- */
/*  @file:    startup_MKV56F24.s                                             */
/*  @purpose: CMSIS Cortex-M7 Core Device Startup File                       */
/*            MKV56F24                                                       */
/*  @version: 0.3                                                            */
/*  @date:    2016-2-29                                                      */
/*  @build:   b190918                                                        */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright 1997-2016 Freescale Semiconductor, Inc.                         */
/* Copyright 2016-2019 NXP                                                   */
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
    .long   DMA0_DMA16_IRQHandler                           /* DMA channel 0/16 transfer complete*/
    .long   DMA1_DMA17_IRQHandler                           /* DMA channel 1/17 transfer complete*/
    .long   DMA2_DMA18_IRQHandler                           /* DMA channel 2/18 transfer complete*/
    .long   DMA3_DMA19_IRQHandler                           /* DMA channel 3/19 transfer complete*/
    .long   DMA4_DMA20_IRQHandler                           /* DMA channel 4/20 transfer complete*/
    .long   DMA5_DMA21_IRQHandler                           /* DMA channel 5/21 transfer complete*/
    .long   DMA6_DMA22_IRQHandler                           /* DMA channel 6/22 transfer complete*/
    .long   DMA7_DMA23_IRQHandler                           /* DMA channel 7/23 transfer complete*/
    .long   DMA8_DMA24_IRQHandler                           /* DMA channel 8/24 transfer complete*/
    .long   DMA9_DMA25_IRQHandler                           /* DMA channel 9/25 transfer complete*/
    .long   DMA10_DMA26_IRQHandler                          /* DMA channel 10/26 transfer complete*/
    .long   DMA11_DMA27_IRQHandler                          /* DMA channel 11/27 transfer complete*/
    .long   DMA12_DMA28_IRQHandler                          /* DMA channel 12/28 transfer complete*/
    .long   DMA13_DMA29_IRQHandler                          /* DMA channel 13/29 transfer complete*/
    .long   DMA14_DMA30_IRQHandler                          /* DMA channel 14/30 transfer complete*/
    .long   DMA15_DMA31_IRQHandler                          /* DMA channel 15/31 transfer complete*/
    .long   DMA_Error_IRQHandler                            /* DMA error interrupt channels 0-31*/
    .long   MCM_IRQHandler                                  /* MCM normal interrupt*/
    .long   FTFE_IRQHandler                                 /* FTFL command complete*/
    .long   Read_Collision_IRQHandler                       /* FTFL read collision*/
    .long   PMC_IRQHandler                                  /* PMC controller low-voltage detect, low-voltage warning*/
    .long   LLWU_IRQHandler                                 /* Low leakage wakeup*/
    .long   WDOG_EWM_IRQHandler                             /* Single interrupt vector for  WDOG and EWM*/
    .long   TRNG0_IRQHandler                                /* True randon number generator*/
    .long   I2C0_IRQHandler                                 /* Inter-integrated circuit 0*/
    .long   I2C1_IRQHandler                                 /* Inter-integrated circuit 1*/
    .long   SPI0_IRQHandler                                 /* Serial peripheral Interface 0*/
    .long   SPI1_IRQHandler                                 /* Serial peripheral Interface 1*/
    .long   UART5_RX_TX_IRQHandler                          /* UART5 receive/transmit interrupt*/
    .long   UART5_ERR_IRQHandler                            /* UART5 error interrupt*/
    .long   Reserved46_IRQHandler                           /* Reserved interrupt*/
    .long   UART0_RX_TX_IRQHandler                          /* UART0 receive/transmit interrupt*/
    .long   UART0_ERR_IRQHandler                            /* UART0 error interrupt*/
    .long   UART1_RX_TX_IRQHandler                          /* UART1 receive/transmit interrupt*/
    .long   UART1_ERR_IRQHandler                            /* UART1 error interrupt*/
    .long   UART2_RX_TX_IRQHandler                          /* UART2 receive/transmit interrupt*/
    .long   UART2_ERR_IRQHandler                            /* UART2 error interrupt*/
    .long   ADC0_IRQHandler                                 /* Analog-to-digital converter 0*/
    .long   HSADC_ERR_IRQHandler                            /* High speed analog-to-digital converter zero cross*/
    .long   HSADC0_CCA_IRQHandler                           /* High speed analog-to-digital converter 0 submodule A scan complete*/
    .long   CMP0_IRQHandler                                 /* Comparator 0*/
    .long   CMP1_IRQHandler                                 /* Comparator 1*/
    .long   FTM0_IRQHandler                                 /* FlexTimer module 0 fault, overflow and channels interrupt*/
    .long   FTM1_IRQHandler                                 /* FlexTimer module 1 fault, overflow and channels interrupt*/
    .long   UART3_RX_TX_IRQHandler                          /* UART3 receive/transmit interrupt*/
    .long   UART3_ERR_IRQHandler                            /* UART3 error interrupt*/
    .long   UART4_RX_TX_IRQHandler                          /* UART4 receive/transmit interrupt*/
    .long   UART4_ERR_IRQHandler                            /* UART4 error interrupt*/
    .long   PIT0_IRQHandler                                 /* Periodic interrupt timer channel 0*/
    .long   PIT1_IRQHandler                                 /* Periodic interrupt timer channel 1*/
    .long   PIT2_IRQHandler                                 /* Periodic interrupt timer channel 2*/
    .long   PIT3_IRQHandler                                 /* Periodic interrupt timer channel 3*/
    .long   PDB0_IRQHandler                                 /* Programmable delay block 0*/
    .long   FTM2_IRQHandler                                 /* FlexTimer module 2 fault, overflow and channels interrupt*/
    .long   XBARA_IRQHandler                                /* Inter-peripheral crossbar switch A*/
    .long   PDB1_IRQHandler                                 /* Programmable delay block 1*/
    .long   DAC0_IRQHandler                                 /* Digital-to-analog converter 0*/
    .long   MCG_IRQHandler                                  /* Multipurpose clock generator*/
    .long   LPTMR0_IRQHandler                               /* Low power timer interrupt*/
    .long   PORTA_IRQHandler                                /* Port A interrupt*/
    .long   PORTB_IRQHandler                                /* Port B interrupt*/
    .long   PORTC_IRQHandler                                /* Port C interrupt*/
    .long   PORTD_IRQHandler                                /* Port D interrupt*/
    .long   PORTE_IRQHandler                                /* Port E interrupt*/
    .long   SWI_IRQHandler                                  /* Software interrupt*/
    .long   SPI2_IRQHandler                                 /* Serial peripheral Interface 2*/
    .long   ENC_COMPARE_IRQHandler                          /* ENC Compare*/
    .long   ENC_HOME_IRQHandler                             /* ENC Home*/
    .long   ENC_WDOG_SAB_IRQHandler                         /* ENC Wdog/SAB*/
    .long   ENC_INDEX_IRQHandler                            /* ENC Index/Roll over/Roll Under*/
    .long   CMP2_IRQHandler                                 /* Comparator 2*/
    .long   FTM3_IRQHandler                                 /* FlexTimer module 3 fault, overflow and channels*/
    .long   Reserved88_IRQHandler                           /* Reserved interrupt*/
    .long   HSADC0_CCB_IRQHandler                           /* High speed analog-to-digital converter 0 submodule B scan complete*/
    .long   HSADC1_CCA_IRQHandler                           /* High speed analog-to-digital converter 1 submodule A scan complete*/
    .long   CAN0_ORed_Message_buffer_IRQHandler             /* Flex controller area network 0 message buffer*/
    .long   CAN0_Bus_Off_IRQHandler                         /* Flex controller area network 0 bus off*/
    .long   CAN0_Error_IRQHandler                           /* Flex controller area network 0 error*/
    .long   CAN0_Tx_Warning_IRQHandler                      /* Flex controller area network 0 transmit*/
    .long   CAN0_Rx_Warning_IRQHandler                      /* Flex controller area network 0 receive*/
    .long   CAN0_Wake_Up_IRQHandler                         /* Flex controller area network 0 wake up*/
    .long   PWM0_CMP0_IRQHandler                            /* Pulse width modulator 0 channel 0 compare*/
    .long   PWM0_RELOAD0_IRQHandler                         /* Pulse width modulator 0 channel 0 reload*/
    .long   PWM0_CMP1_IRQHandler                            /* Pulse width modulator 0 channel 1 compare*/
    .long   PWM0_RELOAD1_IRQHandler                         /* Pulse width modulator 0 channel 1 reload*/
    .long   PWM0_CMP2_IRQHandler                            /* Pulse width modulator 0 channel 2 compare*/
    .long   PWM0_RELOAD2_IRQHandler                         /* Pulse width modulator 0 channel 2 reload*/
    .long   PWM0_CMP3_IRQHandler                            /* Pulse width modulator 0 channel 3 compare*/
    .long   PWM0_RELOAD3_IRQHandler                         /* Pulse width modulator 0 channel 3 reload*/
    .long   PWM0_CAP_IRQHandler                             /* Pulse width modulator 0 capture*/
    .long   PWM0_RERR_IRQHandler                            /* Pulse width modulator 0 reload error*/
    .long   PWM0_FAULT_IRQHandler                           /* Pulse width modulator 0 fault*/
    .long   CMP3_IRQHandler                                 /* Comparator 3*/
    .long   HSADC1_CCB_IRQHandler                           /* High speed analog-to-digital converter 1 submodule B scan complete*/
    .long   CAN1_ORed_Message_buffer_IRQHandler             /* Flex controller area network 1 message buffer*/
    .long   CAN1_Bus_Off_IRQHandler                         /* Flex controller area network 1 bus off*/
    .long   CAN1_Error_IRQHandler                           /* Flex controller area network 1 error*/
    .long   CAN1_Tx_Warning_IRQHandler                      /* Flex controller area network 1 transmit*/
    .long   CAN1_Rx_Warning_IRQHandler                      /* Flex controller area network 1 receive*/
    .long   CAN1_Wake_Up_IRQHandler                         /* Flex controller area network 1 wake up*/
    .long   Reserved116_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved117_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved118_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved119_IRQHandler                          /* Reserved interrupt*/
    .long   PWM1_CMP0_IRQHandler                            /* Pulse width modulator 1 channel 0 compare*/
    .long   PWM1_RELOAD0_IRQHandler                         /* Pulse width modulator 1 channel 0 reload*/
    .long   PWM1_CMP1_IRQHandler                            /* Pulse width modulator 1 channel 1 compare*/
    .long   PWM1_RELOAD1_IRQHandler                         /* Pulse width modulator 1 channel 1 reload*/
    .long   PWM1_CMP2_IRQHandler                            /* Pulse width modulator 1 channel 2 compare*/
    .long   PWM1_RELOAD2_IRQHandler                         /* Pulse width modulator 1 channel 2 reload*/
    .long   PWM1_CMP3_IRQHandler                            /* Pulse width modulator 1 channel 3 compare*/
    .long   PWM1_RELOAD3_IRQHandler                         /* Pulse width modulator 1 channel 3 reload*/
    .long   PWM1_CAP_IRQHandler                             /* Pulse width modulator 1 capture*/
    .long   PWM1_RERR_IRQHandler                            /* Pulse width modulator 1 reload error*/
    .long   PWM1_FAULT_IRQHandler                           /* Pulse width modulator 1 fault*/
    .long   Reserved131_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved132_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved133_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved134_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved135_IRQHandler                          /* Reserved interrupt*/
    .long   Reserved136_IRQHandler                          /* Reserved interrupt*/
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
    .long   0xFFFFFFFF                                      /*  Reserved for user TRIM value*/

    .size    __isr_vector, . - __isr_vector

/* Flash Configuration */
    .section .FlashConfig, "a"
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFFFFFE

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
    .weak DMA0_DMA16_IRQHandler
    .type DMA0_DMA16_IRQHandler, %function
DMA0_DMA16_IRQHandler:
    ldr   r0,=DMA0_DMA16_DriverIRQHandler
    bx    r0
    .size DMA0_DMA16_IRQHandler, . - DMA0_DMA16_IRQHandler

    .align 1
    .thumb_func
    .weak DMA1_DMA17_IRQHandler
    .type DMA1_DMA17_IRQHandler, %function
DMA1_DMA17_IRQHandler:
    ldr   r0,=DMA1_DMA17_DriverIRQHandler
    bx    r0
    .size DMA1_DMA17_IRQHandler, . - DMA1_DMA17_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_DMA18_IRQHandler
    .type DMA2_DMA18_IRQHandler, %function
DMA2_DMA18_IRQHandler:
    ldr   r0,=DMA2_DMA18_DriverIRQHandler
    bx    r0
    .size DMA2_DMA18_IRQHandler, . - DMA2_DMA18_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_DMA19_IRQHandler
    .type DMA3_DMA19_IRQHandler, %function
DMA3_DMA19_IRQHandler:
    ldr   r0,=DMA3_DMA19_DriverIRQHandler
    bx    r0
    .size DMA3_DMA19_IRQHandler, . - DMA3_DMA19_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4_DMA20_IRQHandler
    .type DMA4_DMA20_IRQHandler, %function
DMA4_DMA20_IRQHandler:
    ldr   r0,=DMA4_DMA20_DriverIRQHandler
    bx    r0
    .size DMA4_DMA20_IRQHandler, . - DMA4_DMA20_IRQHandler

    .align 1
    .thumb_func
    .weak DMA5_DMA21_IRQHandler
    .type DMA5_DMA21_IRQHandler, %function
DMA5_DMA21_IRQHandler:
    ldr   r0,=DMA5_DMA21_DriverIRQHandler
    bx    r0
    .size DMA5_DMA21_IRQHandler, . - DMA5_DMA21_IRQHandler

    .align 1
    .thumb_func
    .weak DMA6_DMA22_IRQHandler
    .type DMA6_DMA22_IRQHandler, %function
DMA6_DMA22_IRQHandler:
    ldr   r0,=DMA6_DMA22_DriverIRQHandler
    bx    r0
    .size DMA6_DMA22_IRQHandler, . - DMA6_DMA22_IRQHandler

    .align 1
    .thumb_func
    .weak DMA7_DMA23_IRQHandler
    .type DMA7_DMA23_IRQHandler, %function
DMA7_DMA23_IRQHandler:
    ldr   r0,=DMA7_DMA23_DriverIRQHandler
    bx    r0
    .size DMA7_DMA23_IRQHandler, . - DMA7_DMA23_IRQHandler

    .align 1
    .thumb_func
    .weak DMA8_DMA24_IRQHandler
    .type DMA8_DMA24_IRQHandler, %function
DMA8_DMA24_IRQHandler:
    ldr   r0,=DMA8_DMA24_DriverIRQHandler
    bx    r0
    .size DMA8_DMA24_IRQHandler, . - DMA8_DMA24_IRQHandler

    .align 1
    .thumb_func
    .weak DMA9_DMA25_IRQHandler
    .type DMA9_DMA25_IRQHandler, %function
DMA9_DMA25_IRQHandler:
    ldr   r0,=DMA9_DMA25_DriverIRQHandler
    bx    r0
    .size DMA9_DMA25_IRQHandler, . - DMA9_DMA25_IRQHandler

    .align 1
    .thumb_func
    .weak DMA10_DMA26_IRQHandler
    .type DMA10_DMA26_IRQHandler, %function
DMA10_DMA26_IRQHandler:
    ldr   r0,=DMA10_DMA26_DriverIRQHandler
    bx    r0
    .size DMA10_DMA26_IRQHandler, . - DMA10_DMA26_IRQHandler

    .align 1
    .thumb_func
    .weak DMA11_DMA27_IRQHandler
    .type DMA11_DMA27_IRQHandler, %function
DMA11_DMA27_IRQHandler:
    ldr   r0,=DMA11_DMA27_DriverIRQHandler
    bx    r0
    .size DMA11_DMA27_IRQHandler, . - DMA11_DMA27_IRQHandler

    .align 1
    .thumb_func
    .weak DMA12_DMA28_IRQHandler
    .type DMA12_DMA28_IRQHandler, %function
DMA12_DMA28_IRQHandler:
    ldr   r0,=DMA12_DMA28_DriverIRQHandler
    bx    r0
    .size DMA12_DMA28_IRQHandler, . - DMA12_DMA28_IRQHandler

    .align 1
    .thumb_func
    .weak DMA13_DMA29_IRQHandler
    .type DMA13_DMA29_IRQHandler, %function
DMA13_DMA29_IRQHandler:
    ldr   r0,=DMA13_DMA29_DriverIRQHandler
    bx    r0
    .size DMA13_DMA29_IRQHandler, . - DMA13_DMA29_IRQHandler

    .align 1
    .thumb_func
    .weak DMA14_DMA30_IRQHandler
    .type DMA14_DMA30_IRQHandler, %function
DMA14_DMA30_IRQHandler:
    ldr   r0,=DMA14_DMA30_DriverIRQHandler
    bx    r0
    .size DMA14_DMA30_IRQHandler, . - DMA14_DMA30_IRQHandler

    .align 1
    .thumb_func
    .weak DMA15_DMA31_IRQHandler
    .type DMA15_DMA31_IRQHandler, %function
DMA15_DMA31_IRQHandler:
    ldr   r0,=DMA15_DMA31_DriverIRQHandler
    bx    r0
    .size DMA15_DMA31_IRQHandler, . - DMA15_DMA31_IRQHandler

    .align 1
    .thumb_func
    .weak DMA_Error_IRQHandler
    .type DMA_Error_IRQHandler, %function
DMA_Error_IRQHandler:
    ldr   r0,=DMA_Error_DriverIRQHandler
    bx    r0
    .size DMA_Error_IRQHandler, . - DMA_Error_IRQHandler

    .align 1
    .thumb_func
    .weak I2C0_IRQHandler
    .type I2C0_IRQHandler, %function
I2C0_IRQHandler:
    ldr   r0,=I2C0_DriverIRQHandler
    bx    r0
    .size I2C0_IRQHandler, . - I2C0_IRQHandler

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
    .weak SPI0_IRQHandler
    .type SPI0_IRQHandler, %function
SPI0_IRQHandler:
    ldr   r0,=SPI0_DriverIRQHandler
    bx    r0
    .size SPI0_IRQHandler, . - SPI0_IRQHandler

    .align 1
    .thumb_func
    .weak SPI1_IRQHandler
    .type SPI1_IRQHandler, %function
SPI1_IRQHandler:
    ldr   r0,=SPI1_DriverIRQHandler
    bx    r0
    .size SPI1_IRQHandler, . - SPI1_IRQHandler

    .align 1
    .thumb_func
    .weak UART5_RX_TX_IRQHandler
    .type UART5_RX_TX_IRQHandler, %function
UART5_RX_TX_IRQHandler:
    ldr   r0,=UART5_RX_TX_DriverIRQHandler
    bx    r0
    .size UART5_RX_TX_IRQHandler, . - UART5_RX_TX_IRQHandler

    .align 1
    .thumb_func
    .weak UART5_ERR_IRQHandler
    .type UART5_ERR_IRQHandler, %function
UART5_ERR_IRQHandler:
    ldr   r0,=UART5_ERR_DriverIRQHandler
    bx    r0
    .size UART5_ERR_IRQHandler, . - UART5_ERR_IRQHandler

    .align 1
    .thumb_func
    .weak UART0_RX_TX_IRQHandler
    .type UART0_RX_TX_IRQHandler, %function
UART0_RX_TX_IRQHandler:
    ldr   r0,=UART0_RX_TX_DriverIRQHandler
    bx    r0
    .size UART0_RX_TX_IRQHandler, . - UART0_RX_TX_IRQHandler

    .align 1
    .thumb_func
    .weak UART0_ERR_IRQHandler
    .type UART0_ERR_IRQHandler, %function
UART0_ERR_IRQHandler:
    ldr   r0,=UART0_ERR_DriverIRQHandler
    bx    r0
    .size UART0_ERR_IRQHandler, . - UART0_ERR_IRQHandler

    .align 1
    .thumb_func
    .weak UART1_RX_TX_IRQHandler
    .type UART1_RX_TX_IRQHandler, %function
UART1_RX_TX_IRQHandler:
    ldr   r0,=UART1_RX_TX_DriverIRQHandler
    bx    r0
    .size UART1_RX_TX_IRQHandler, . - UART1_RX_TX_IRQHandler

    .align 1
    .thumb_func
    .weak UART1_ERR_IRQHandler
    .type UART1_ERR_IRQHandler, %function
UART1_ERR_IRQHandler:
    ldr   r0,=UART1_ERR_DriverIRQHandler
    bx    r0
    .size UART1_ERR_IRQHandler, . - UART1_ERR_IRQHandler

    .align 1
    .thumb_func
    .weak UART2_RX_TX_IRQHandler
    .type UART2_RX_TX_IRQHandler, %function
UART2_RX_TX_IRQHandler:
    ldr   r0,=UART2_RX_TX_DriverIRQHandler
    bx    r0
    .size UART2_RX_TX_IRQHandler, . - UART2_RX_TX_IRQHandler

    .align 1
    .thumb_func
    .weak UART2_ERR_IRQHandler
    .type UART2_ERR_IRQHandler, %function
UART2_ERR_IRQHandler:
    ldr   r0,=UART2_ERR_DriverIRQHandler
    bx    r0
    .size UART2_ERR_IRQHandler, . - UART2_ERR_IRQHandler

    .align 1
    .thumb_func
    .weak UART3_RX_TX_IRQHandler
    .type UART3_RX_TX_IRQHandler, %function
UART3_RX_TX_IRQHandler:
    ldr   r0,=UART3_RX_TX_DriverIRQHandler
    bx    r0
    .size UART3_RX_TX_IRQHandler, . - UART3_RX_TX_IRQHandler

    .align 1
    .thumb_func
    .weak UART3_ERR_IRQHandler
    .type UART3_ERR_IRQHandler, %function
UART3_ERR_IRQHandler:
    ldr   r0,=UART3_ERR_DriverIRQHandler
    bx    r0
    .size UART3_ERR_IRQHandler, . - UART3_ERR_IRQHandler

    .align 1
    .thumb_func
    .weak UART4_RX_TX_IRQHandler
    .type UART4_RX_TX_IRQHandler, %function
UART4_RX_TX_IRQHandler:
    ldr   r0,=UART4_RX_TX_DriverIRQHandler
    bx    r0
    .size UART4_RX_TX_IRQHandler, . - UART4_RX_TX_IRQHandler

    .align 1
    .thumb_func
    .weak UART4_ERR_IRQHandler
    .type UART4_ERR_IRQHandler, %function
UART4_ERR_IRQHandler:
    ldr   r0,=UART4_ERR_DriverIRQHandler
    bx    r0
    .size UART4_ERR_IRQHandler, . - UART4_ERR_IRQHandler

    .align 1
    .thumb_func
    .weak SPI2_IRQHandler
    .type SPI2_IRQHandler, %function
SPI2_IRQHandler:
    ldr   r0,=SPI2_DriverIRQHandler
    bx    r0
    .size SPI2_IRQHandler, . - SPI2_IRQHandler

    .align 1
    .thumb_func
    .weak CAN0_ORed_Message_buffer_IRQHandler
    .type CAN0_ORed_Message_buffer_IRQHandler, %function
CAN0_ORed_Message_buffer_IRQHandler:
    ldr   r0,=CAN0_DriverIRQHandler
    bx    r0
    .size CAN0_ORed_Message_buffer_IRQHandler, . - CAN0_ORed_Message_buffer_IRQHandler

    .align 1
    .thumb_func
    .weak CAN0_Bus_Off_IRQHandler
    .type CAN0_Bus_Off_IRQHandler, %function
CAN0_Bus_Off_IRQHandler:
    ldr   r0,=CAN0_DriverIRQHandler
    bx    r0
    .size CAN0_Bus_Off_IRQHandler, . - CAN0_Bus_Off_IRQHandler

    .align 1
    .thumb_func
    .weak CAN0_Error_IRQHandler
    .type CAN0_Error_IRQHandler, %function
CAN0_Error_IRQHandler:
    ldr   r0,=CAN0_DriverIRQHandler
    bx    r0
    .size CAN0_Error_IRQHandler, . - CAN0_Error_IRQHandler

    .align 1
    .thumb_func
    .weak CAN0_Tx_Warning_IRQHandler
    .type CAN0_Tx_Warning_IRQHandler, %function
CAN0_Tx_Warning_IRQHandler:
    ldr   r0,=CAN0_DriverIRQHandler
    bx    r0
    .size CAN0_Tx_Warning_IRQHandler, . - CAN0_Tx_Warning_IRQHandler

    .align 1
    .thumb_func
    .weak CAN0_Rx_Warning_IRQHandler
    .type CAN0_Rx_Warning_IRQHandler, %function
CAN0_Rx_Warning_IRQHandler:
    ldr   r0,=CAN0_DriverIRQHandler
    bx    r0
    .size CAN0_Rx_Warning_IRQHandler, . - CAN0_Rx_Warning_IRQHandler

    .align 1
    .thumb_func
    .weak CAN0_Wake_Up_IRQHandler
    .type CAN0_Wake_Up_IRQHandler, %function
CAN0_Wake_Up_IRQHandler:
    ldr   r0,=CAN0_DriverIRQHandler
    bx    r0
    .size CAN0_Wake_Up_IRQHandler, . - CAN0_Wake_Up_IRQHandler

    .align 1
    .thumb_func
    .weak CAN1_ORed_Message_buffer_IRQHandler
    .type CAN1_ORed_Message_buffer_IRQHandler, %function
CAN1_ORed_Message_buffer_IRQHandler:
    ldr   r0,=CAN1_DriverIRQHandler
    bx    r0
    .size CAN1_ORed_Message_buffer_IRQHandler, . - CAN1_ORed_Message_buffer_IRQHandler

    .align 1
    .thumb_func
    .weak CAN1_Bus_Off_IRQHandler
    .type CAN1_Bus_Off_IRQHandler, %function
CAN1_Bus_Off_IRQHandler:
    ldr   r0,=CAN1_DriverIRQHandler
    bx    r0
    .size CAN1_Bus_Off_IRQHandler, . - CAN1_Bus_Off_IRQHandler

    .align 1
    .thumb_func
    .weak CAN1_Error_IRQHandler
    .type CAN1_Error_IRQHandler, %function
CAN1_Error_IRQHandler:
    ldr   r0,=CAN1_DriverIRQHandler
    bx    r0
    .size CAN1_Error_IRQHandler, . - CAN1_Error_IRQHandler

    .align 1
    .thumb_func
    .weak CAN1_Tx_Warning_IRQHandler
    .type CAN1_Tx_Warning_IRQHandler, %function
CAN1_Tx_Warning_IRQHandler:
    ldr   r0,=CAN1_DriverIRQHandler
    bx    r0
    .size CAN1_Tx_Warning_IRQHandler, . - CAN1_Tx_Warning_IRQHandler

    .align 1
    .thumb_func
    .weak CAN1_Rx_Warning_IRQHandler
    .type CAN1_Rx_Warning_IRQHandler, %function
CAN1_Rx_Warning_IRQHandler:
    ldr   r0,=CAN1_DriverIRQHandler
    bx    r0
    .size CAN1_Rx_Warning_IRQHandler, . - CAN1_Rx_Warning_IRQHandler

    .align 1
    .thumb_func
    .weak CAN1_Wake_Up_IRQHandler
    .type CAN1_Wake_Up_IRQHandler, %function
CAN1_Wake_Up_IRQHandler:
    ldr   r0,=CAN1_DriverIRQHandler
    bx    r0
    .size CAN1_Wake_Up_IRQHandler, . - CAN1_Wake_Up_IRQHandler


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
    def_irq_handler    DMA0_DMA16_DriverIRQHandler
    def_irq_handler    DMA1_DMA17_DriverIRQHandler
    def_irq_handler    DMA2_DMA18_DriverIRQHandler
    def_irq_handler    DMA3_DMA19_DriverIRQHandler
    def_irq_handler    DMA4_DMA20_DriverIRQHandler
    def_irq_handler    DMA5_DMA21_DriverIRQHandler
    def_irq_handler    DMA6_DMA22_DriverIRQHandler
    def_irq_handler    DMA7_DMA23_DriverIRQHandler
    def_irq_handler    DMA8_DMA24_DriverIRQHandler
    def_irq_handler    DMA9_DMA25_DriverIRQHandler
    def_irq_handler    DMA10_DMA26_DriverIRQHandler
    def_irq_handler    DMA11_DMA27_DriverIRQHandler
    def_irq_handler    DMA12_DMA28_DriverIRQHandler
    def_irq_handler    DMA13_DMA29_DriverIRQHandler
    def_irq_handler    DMA14_DMA30_DriverIRQHandler
    def_irq_handler    DMA15_DMA31_DriverIRQHandler
    def_irq_handler    DMA_Error_DriverIRQHandler
    def_irq_handler    MCM_IRQHandler
    def_irq_handler    FTFE_IRQHandler
    def_irq_handler    Read_Collision_IRQHandler
    def_irq_handler    PMC_IRQHandler
    def_irq_handler    LLWU_IRQHandler
    def_irq_handler    WDOG_EWM_IRQHandler
    def_irq_handler    TRNG0_IRQHandler
    def_irq_handler    I2C0_DriverIRQHandler
    def_irq_handler    I2C1_DriverIRQHandler
    def_irq_handler    SPI0_DriverIRQHandler
    def_irq_handler    SPI1_DriverIRQHandler
    def_irq_handler    UART5_RX_TX_DriverIRQHandler
    def_irq_handler    UART5_ERR_DriverIRQHandler
    def_irq_handler    Reserved46_IRQHandler
    def_irq_handler    UART0_RX_TX_DriverIRQHandler
    def_irq_handler    UART0_ERR_DriverIRQHandler
    def_irq_handler    UART1_RX_TX_DriverIRQHandler
    def_irq_handler    UART1_ERR_DriverIRQHandler
    def_irq_handler    UART2_RX_TX_DriverIRQHandler
    def_irq_handler    UART2_ERR_DriverIRQHandler
    def_irq_handler    ADC0_IRQHandler
    def_irq_handler    HSADC_ERR_IRQHandler
    def_irq_handler    HSADC0_CCA_IRQHandler
    def_irq_handler    CMP0_IRQHandler
    def_irq_handler    CMP1_IRQHandler
    def_irq_handler    FTM0_IRQHandler
    def_irq_handler    FTM1_IRQHandler
    def_irq_handler    UART3_RX_TX_DriverIRQHandler
    def_irq_handler    UART3_ERR_DriverIRQHandler
    def_irq_handler    UART4_RX_TX_DriverIRQHandler
    def_irq_handler    UART4_ERR_DriverIRQHandler
    def_irq_handler    PIT0_IRQHandler
    def_irq_handler    PIT1_IRQHandler
    def_irq_handler    PIT2_IRQHandler
    def_irq_handler    PIT3_IRQHandler
    def_irq_handler    PDB0_IRQHandler
    def_irq_handler    FTM2_IRQHandler
    def_irq_handler    XBARA_IRQHandler
    def_irq_handler    PDB1_IRQHandler
    def_irq_handler    DAC0_IRQHandler
    def_irq_handler    MCG_IRQHandler
    def_irq_handler    LPTMR0_IRQHandler
    def_irq_handler    PORTA_IRQHandler
    def_irq_handler    PORTB_IRQHandler
    def_irq_handler    PORTC_IRQHandler
    def_irq_handler    PORTD_IRQHandler
    def_irq_handler    PORTE_IRQHandler
    def_irq_handler    SWI_IRQHandler
    def_irq_handler    SPI2_DriverIRQHandler
    def_irq_handler    ENC_COMPARE_IRQHandler
    def_irq_handler    ENC_HOME_IRQHandler
    def_irq_handler    ENC_WDOG_SAB_IRQHandler
    def_irq_handler    ENC_INDEX_IRQHandler
    def_irq_handler    CMP2_IRQHandler
    def_irq_handler    FTM3_IRQHandler
    def_irq_handler    Reserved88_IRQHandler
    def_irq_handler    HSADC0_CCB_IRQHandler
    def_irq_handler    HSADC1_CCA_IRQHandler
    def_irq_handler    CAN0_DriverIRQHandler
    def_irq_handler    PWM0_CMP0_IRQHandler
    def_irq_handler    PWM0_RELOAD0_IRQHandler
    def_irq_handler    PWM0_CMP1_IRQHandler
    def_irq_handler    PWM0_RELOAD1_IRQHandler
    def_irq_handler    PWM0_CMP2_IRQHandler
    def_irq_handler    PWM0_RELOAD2_IRQHandler
    def_irq_handler    PWM0_CMP3_IRQHandler
    def_irq_handler    PWM0_RELOAD3_IRQHandler
    def_irq_handler    PWM0_CAP_IRQHandler
    def_irq_handler    PWM0_RERR_IRQHandler
    def_irq_handler    PWM0_FAULT_IRQHandler
    def_irq_handler    CMP3_IRQHandler
    def_irq_handler    HSADC1_CCB_IRQHandler
    def_irq_handler    CAN1_DriverIRQHandler
    def_irq_handler    Reserved116_IRQHandler
    def_irq_handler    Reserved117_IRQHandler
    def_irq_handler    Reserved118_IRQHandler
    def_irq_handler    Reserved119_IRQHandler
    def_irq_handler    PWM1_CMP0_IRQHandler
    def_irq_handler    PWM1_RELOAD0_IRQHandler
    def_irq_handler    PWM1_CMP1_IRQHandler
    def_irq_handler    PWM1_RELOAD1_IRQHandler
    def_irq_handler    PWM1_CMP2_IRQHandler
    def_irq_handler    PWM1_RELOAD2_IRQHandler
    def_irq_handler    PWM1_CMP3_IRQHandler
    def_irq_handler    PWM1_RELOAD3_IRQHandler
    def_irq_handler    PWM1_CAP_IRQHandler
    def_irq_handler    PWM1_RERR_IRQHandler
    def_irq_handler    PWM1_FAULT_IRQHandler
    def_irq_handler    Reserved131_IRQHandler
    def_irq_handler    Reserved132_IRQHandler
    def_irq_handler    Reserved133_IRQHandler
    def_irq_handler    Reserved134_IRQHandler
    def_irq_handler    Reserved135_IRQHandler
    def_irq_handler    Reserved136_IRQHandler

    .end
