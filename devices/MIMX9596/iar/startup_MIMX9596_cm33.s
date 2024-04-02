; -------------------------------------------------------------------------
;  @file:    startup_MIMX9596_cm33.s
;  @purpose: CMSIS Cortex-M33 Core Device Startup File
;            MIMX9596_cm33
;  @version: 1.0
;  @date:    2023-1-10
;  @build:   b231019
; -------------------------------------------------------------------------
;
; Copyright 1997-2016 Freescale Semiconductor, Inc.
; Copyright 2016-2023 NXP
; SPDX-License-Identifier: BSD-3-Clause
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__iar_init$$done:              ; The vector table is not needed
                      ; until after copy initialization is done

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler                                   ;NMI Handler
        DCD     HardFault_Handler                             ;Hard Fault Handler
        DCD     MemManage_Handler                             ;MPU Fault Handler
        DCD     BusFault_Handler                              ;Bus Fault Handler
        DCD     UsageFault_Handler                            ;Usage Fault Handler
__vector_table_0x1c
        DCD     SecureFault_Handler                           ;Secure Fault Handler
        DCD     0                                             ;Reserved
        DCD     0                                             ;Reserved
        DCD     0                                             ;Reserved
        DCD     SVC_Handler                                   ;SVCall Handler
        DCD     DebugMon_Handler                              ;Debug Monitor Handler
        DCD     0                                             ;Reserved
        DCD     PendSV_Handler                                ;PendSV Handler
        DCD     SysTick_Handler                               ;SysTick Handler

                                                              ;External Interrupts
        DCD     Reserved16_IRQHandler                         ;Reserved interrupt
        DCD     Reserved17_IRQHandler                         ;DAP interrupt
        DCD     Reserved18_IRQHandler                         ;CTI trigger outputs from CM7 platform
        DCD     Reserved19_IRQHandler                         ;CTI trigger outputs from CM33 platform
        DCD     Reserved20_IRQHandler                         ;CTI trigger outputs from CA55 platform
        DCD     Reserved21_IRQHandler                         ;Performance Unit Interrupts from CA55 platform
        DCD     Reserved22_IRQHandler                         ;ECC error from CA55 platform cache
        DCD     Reserved23_IRQHandler                         ;1-bit or 2-bit ECC or Parity error from CA55 platform cache
        DCD     CAN1_IRQHandler                               ;CAN1 interrupt
        DCD     CAN1_ERROR_IRQHandler                         ;CAN1 error interrupt
        DCD     Reserved26_IRQHandler                         ;General Purpose Input/Output 1 interrupt 0
        DCD     Reserved27_IRQHandler                         ;General Purpose Input/Output 1 interrupt 1
        DCD     I3C1_IRQHandler                               ;Improved Inter-Integrated Circuit 1 interrupt
        DCD     LPI2C1_IRQHandler                             ;Low Power Inter-Integrated Circuit module 1
        DCD     LPI2C2_IRQHandler                             ;Low Power Inter-Integrated Circuit module 2
        DCD     LPIT1_IRQHandler                              ;Low Power Periodic Interrupt Timer 1
        DCD     LPSPI1_IRQHandler                             ;Low Power Serial Peripheral Interface 1
        DCD     LPSPI2_IRQHandler                             ;Low Power Serial Peripheral Interface 2
        DCD     LPTMR1_IRQHandler                             ;Low Power Timer 1
        DCD     LPUART1_IRQHandler                            ;Low Power UART 1
        DCD     LPUART2_IRQHandler                            ;Low Power UART 2
        DCD     Reserved37_IRQHandler                         ;AONMIX Sentinel MU0 SideA interrupt
        DCD     Reserved38_IRQHandler                         ;AONMIX Sentinel MU1 SideA interrupt
        DCD     Reserved39_IRQHandler                         ;AONMIX Sentinel MU2 SideA interrupt
        DCD     Reserved40_IRQHandler                         ;AONMIX Sentinel MU3 SideA interrupt
        DCD     Reserved41_IRQHandler                         ;AONMIX Sentinel MU4 SideA interrupt
        DCD     Reserved42_IRQHandler                         ;AONMIX Sentinel MU5 SideA interrupt
        DCD     V2X_FH_APCH0_IRQHandler                       ;V2X-FH MU APCH0 (APP0) interrupt
        DCD     V2X_FH_APHSM1_IRQHandler                      ;V2X-FH MU APHSM1 (HSM1) interrupt
        DCD     TPM1_IRQHandler                               ;Timer PWM module 1
        DCD     TPM2_IRQHandler                               ;Timer PWM module 2
        DCD     WDOG1_IRQHandler                              ;Watchdog 1 Interrupt
        DCD     WDOG2_IRQHandler                              ;Watchdog 2 Interrupt
        DCD     TRDC_MGR_A_IRQHandler                         ;AONMIX TRDC transfer error interrupt
        DCD     SAI1_IRQHandler                               ;Serial Audio Interface 1
        DCD     Reserved51_IRQHandler                         ;AONMIX M33 PS Error
        DCD     Reserved52_IRQHandler                         ;AONMIX M33 TCM Error interrupt
        DCD     Reserved53_IRQHandler                         ;M7MIX ECC Multi-bit error
        DCD     CAN2_IRQHandler                               ;CAN2 interrupt
        DCD     CAN2_ERROR_IRQHandler                         ;CAN2 error interrupt
        DCD     CAN3_IRQHandler                               ;CAN3 interrupt
        DCD     CAN3_ERROR_IRQHandler                         ;CAN3 error interrupt
        DCD     CAN4_IRQHandler                               ;CAN4 interrupt
        DCD     CAN4_ERROR_IRQHandler                         ;CAN4 error interrupt
        DCD     CAN5_IRQHandler                               ;CAN5 interrupt
        DCD     CAN5_ERROR_IRQHandler                         ;CAN5 error interrupt
        DCD     FLEXIO1_IRQHandler                            ;Flexible IO 1 interrupt
        DCD     FLEXIO2_IRQHandler                            ;Flexible IO 2 interrupt
        DCD     FlexSPI1_IRQHandler                           ;FlexSPI controller interface interrupt 1
        DCD     Reserved65_IRQHandler                         ;General Purpose Input/Output 2 interrupt 0
        DCD     Reserved66_IRQHandler                         ;General Purpose Input/Output 2 interrupt 1
        DCD     Reserved67_IRQHandler                         ;General Purpose Input/Output 3 interrupt 0
        DCD     Reserved68_IRQHandler                         ;General Purpose Input/Output 3 interrupt 1
        DCD     Reserved69_IRQHandler                         ;General Purpose Input/Output 4 interrupt 0
        DCD     Reserved70_IRQHandler                         ;General Purpose Input/Output 4 interrupt 1
        DCD     Reserved71_IRQHandler                         ;General Purpose Input/Output 5 interrupt 0
        DCD     Reserved72_IRQHandler                         ;General Purpose Input/Output 5 interrupt 1
        DCD     I3C2_IRQHandler                               ;Improved Inter-Integrated Circuit 2 interrupt
        DCD     LPI2C3_IRQHandler                             ;Low Power Inter-Integrated Circuit module 3
        DCD     LPI2C4_IRQHandler                             ;Low Power Inter-Integrated Circuit module 4
        DCD     LPIT2_IRQHandler                              ;Low Power Periodic Interrupt Timer 2
        DCD     LPSPI3_IRQHandler                             ;Low Power Serial Peripheral Interface 3
        DCD     LPSPI4_IRQHandler                             ;Low Power Serial Peripheral Interface 4
        DCD     LPTMR2_IRQHandler                             ;Low Power Timer 2
        DCD     LPUART3_IRQHandler                            ;Low Power UART 3
        DCD     LPUART4_IRQHandler                            ;Low Power UART 4
        DCD     LPUART5_IRQHandler                            ;Low Power UART 5
        DCD     LPUART6_IRQHandler                            ;Low Power UART 6
        DCD     LPUART7_IRQHandler                            ;Low Power UART 7
        DCD     LPUART8_IRQHandler                            ;Low Power UART 8
        DCD     Reserved86_IRQHandler                         ;MTR Master error interrupt
        DCD     Reserved87_IRQHandler                         ;BBNSM Non-Secure interrupt
        DCD     Reserved88_IRQHandler                         ;System Counter compare interrupt
        DCD     TPM3_IRQHandler                               ;Timer PWM module 3
        DCD     TPM4_IRQHandler                               ;Timer PWM module 4
        DCD     TPM5_IRQHandler                               ;Timer PWM module 5
        DCD     TPM6_IRQHandler                               ;Timer PWM module 6
        DCD     WDOG3_IRQHandler                              ;Watchdog 3 Interrupt
        DCD     WDOG4_IRQHandler                              ;Watchdog 4 Interrupt
        DCD     WDOG5_IRQHandler                              ;Watchdog 5 Interrupt
        DCD     Reserved96_IRQHandler                         ;ANAMIX TempSensor non-secure interrupt from Threshold 1
        DCD     Reserved97_IRQHandler                         ;ANAMIX TempSensor non-secure interrupt from Threshold 2
        DCD     Reserved98_IRQHandler                         ;ANAMIX TempSensor non-secure interrupt from Threshold 3
        DCD     Reserved99_IRQHandler                         ;CORTEXAMIX TempSensor non-secure interrupt from Threshold 1
        DCD     Reserved100_IRQHandler                        ;CORTEXAMIX TempSensor non-secure interrupt from Threshold 2
        DCD     Reserved101_IRQHandler                        ;CORTEXAMIX TempSensor non-secure data ready interrupt
        DCD     uSDHC1_IRQHandler                             ;ultra Secure Digital Host Controller interrupt 1
        DCD     uSDHC2_IRQHandler                             ;ultra Secure Digital Host Controller interrupt 2
        DCD     Reserved104_IRQHandler                        ;MEGAMIX TRDC transfer error interrupt
        DCD     Reserved105_IRQHandler                        ;NIC_WRAPPER TRDC transfer error interrupt
        DCD     Reserved106_IRQHandler                        ;NOCMIX TRDC transfer error interrupt
        DCD     Reserved107_IRQHandler                        ;DRAM controller Performance Monitor Interrupt
        DCD     Reserved108_IRQHandler                        ;DRAM controller Critical Interrupt
        DCD     Reserved109_IRQHandler                        ;DRAM Phy Critical Interrupt
        DCD     Reserved110_IRQHandler                        ;Reserved
        DCD     DMA3_ERROR_IRQHandler                         ;eDMA1 error interrupt
        DCD     DMA3_0_IRQHandler                             ;eDMA1 channel 0 interrupt
        DCD     DMA3_1_IRQHandler                             ;eDMA1 channel 1 interrupt
        DCD     DMA3_2_IRQHandler                             ;eDMA1 channel 2 interrupt
        DCD     DMA3_3_IRQHandler                             ;eDMA1 channel 3 interrupt
        DCD     DMA3_4_IRQHandler                             ;eDMA1 channel 4 interrupt
        DCD     DMA3_5_IRQHandler                             ;eDMA1 channel 5 interrupt
        DCD     DMA3_6_IRQHandler                             ;eDMA1 channel 6 interrupt
        DCD     DMA3_7_IRQHandler                             ;eDMA1 channel 7 interrupt
        DCD     DMA3_8_IRQHandler                             ;eDMA1 channel 8 interrupt
        DCD     DMA3_9_IRQHandler                             ;eDMA1 channel 9 interrupt
        DCD     DMA3_10_IRQHandler                            ;eDMA1 channel 10 interrupt
        DCD     DMA3_11_IRQHandler                            ;eDMA1 channel 11 interrupt
        DCD     DMA3_12_IRQHandler                            ;eDMA1 channel 12 interrupt
        DCD     DMA3_13_IRQHandler                            ;eDMA1 channel 13 interrupt
        DCD     DMA3_14_IRQHandler                            ;eDMA1 channel 14 interrupt
        DCD     DMA3_15_IRQHandler                            ;eDMA1 channel 15 interrupt
        DCD     DMA3_16_IRQHandler                            ;eDMA1 channel 16 interrupt
        DCD     DMA3_17_IRQHandler                            ;eDMA1 channel 17 interrupt
        DCD     DMA3_18_IRQHandler                            ;eDMA1 channel 18 interrupt
        DCD     DMA3_19_IRQHandler                            ;eDMA1 channel 19 interrupt
        DCD     DMA3_20_IRQHandler                            ;eDMA1 channel 20 interrupt
        DCD     DMA3_21_IRQHandler                            ;eDMA1 channel 21 interrupt
        DCD     DMA3_22_IRQHandler                            ;eDMA1 channel 22 interrupt
        DCD     DMA3_23_IRQHandler                            ;eDMA1 channel 23 interrupt
        DCD     DMA3_24_IRQHandler                            ;eDMA1 channel 24 interrupt
        DCD     DMA3_25_IRQHandler                            ;eDMA1 channel 25 interrupt
        DCD     DMA3_26_IRQHandler                            ;eDMA1 channel 26 interrupt
        DCD     DMA3_27_IRQHandler                            ;eDMA1 channel 27 interrupt
        DCD     DMA3_28_IRQHandler                            ;eDMA1 channel 28 interrupt
        DCD     DMA3_29_IRQHandler                            ;eDMA1 channel 29 interrupt
        DCD     DMA3_30_IRQHandler                            ;eDMA1 channel 30 interrupt
        DCD     DMA4_ERROR_IRQHandler                         ;eDMA2 error interrupt
        DCD     DMA4_0_1_IRQHandler                           ;eDMA2 channel 0/1 interrupt
        DCD     DMA4_2_3_IRQHandler                           ;eDMA2 channel 2/3 interrupt
        DCD     DMA4_4_5_IRQHandler                           ;eDMA2 channel 4/5 interrupt
        DCD     DMA4_6_7_IRQHandler                           ;eDMA2 channel 6/7 interrupt
        DCD     DMA4_8_9_IRQHandler                           ;eDMA2 channel 8/9 interrupt
        DCD     DMA4_10_11_IRQHandler                         ;eDMA2 channel 10/11 interrupt
        DCD     DMA4_12_13_IRQHandler                         ;eDMA2 channel 12/13 interrupt
        DCD     DMA4_14_15_IRQHandler                         ;eDMA2 channel 14/15 interrupt
        DCD     DMA4_16_17_IRQHandler                         ;eDMA2 channel 16/17 interrupt
        DCD     DMA4_18_19_IRQHandler                         ;eDMA2 channel 18/19 interrupt
        DCD     DMA4_20_21_IRQHandler                         ;eDMA2 channel 20/21 interrupt
        DCD     DMA4_22_23_IRQHandler                         ;eDMA2 channel 22/23 interrupt
        DCD     DMA4_24_25_IRQHandler                         ;eDMA2 channel 24/25 interrupt
        DCD     DMA4_26_27_IRQHandler                         ;eDMA2 channel 26/27 interrupt
        DCD     DMA4_28_29_IRQHandler                         ;eDMA2 channel 28/29 interrupt
        DCD     DMA4_30_31_IRQHandler                         ;eDMA2 channel 30/31 interrupt
        DCD     DMA4_32_33_IRQHandler                         ;eDMA2 channel 32/33 interrupt
        DCD     DMA4_34_35_IRQHandler                         ;eDMA2 channel 34/35 interrupt
        DCD     DMA4_36_37_IRQHandler                         ;eDMA2 channel 36/37 interrupt
        DCD     DMA4_38_39_IRQHandler                         ;eDMA2 channel 38/39 interrupt
        DCD     DMA4_40_41_IRQHandler                         ;eDMA2 channel 40/41 interrupt
        DCD     DMA4_42_43_IRQHandler                         ;eDMA2 channel 42/43 interrupt
        DCD     DMA4_44_45_IRQHandler                         ;eDMA2 channel 44/45 interrupt
        DCD     DMA4_46_47_IRQHandler                         ;eDMA2 channel 46/47 interrupt
        DCD     DMA4_48_49_IRQHandler                         ;eDMA2 channel 48/49 interrupt
        DCD     DMA4_50_51_IRQHandler                         ;eDMA2 channel 50/51 interrupt
        DCD     DMA4_52_53_IRQHandler                         ;eDMA2 channel 52/53 interrupt
        DCD     DMA4_54_55_IRQHandler                         ;eDMA2 channel 54/55 interrupt
        DCD     DMA4_56_57_IRQHandler                         ;eDMA2 channel 56/57 interrupt
        DCD     DMA4_58_59_IRQHandler                         ;eDMA2 channel 58/59 interrupt
        DCD     DMA4_60_61_IRQHandler                         ;eDMA2 channel 60/61 interrupt
        DCD     DMA4_62_63_IRQHandler                         ;eDMA2 channel 62/63 interrupt
        DCD     Reserved176_IRQHandler                        ;Sentinel Group 1 reset source if no s500 reference clock is detected. Output synchronized to 32khz clk.
        DCD     Reserved177_IRQHandler                        ;Sentinel Group 2 reset source s500 reference clock is not detected or too slow. Output synchronized to ref1_clk.
        DCD     Reserved178_IRQHandler                        ;Sentinel Group 2 reset source s500 reference clock is not detected or too slow. Output synchronized to ref1_clk.
        DCD     Reserved179_IRQHandler                        ;JTAGSW DAP MDM-AP SRC reset source
        DCD     Reserved180_IRQHandler                        ;JTAGC SRC reset source
        DCD     Reserved181_IRQHandler                        ;CM33 SYSREQRST SRC reset source
        DCD     Reserved182_IRQHandler                        ;CM33 LOCKUP SRC reset source
        DCD     Reserved183_IRQHandler                        ;CM7 SYSREQRST SRC reset source
        DCD     Reserved184_IRQHandler                        ;CM7 LOCKUP SRC reset source
        DCD     SAI2_IRQHandler                               ;Serial Audio Interface 2
        DCD     SAI3_IRQHandler                               ;Serial Audio Interface 3
        DCD     SAI4_IRQHandler                               ;Serial Audio Interface 4
        DCD     SAI5_IRQHandler                               ;Serial Audio Interface 5
        DCD     Reserved189_IRQHandler                        ;USB-1 Wake-up Interrupt
        DCD     Reserved190_IRQHandler                        ;USB-2 Wake-up Interrupt
        DCD     USB1_IRQHandler                               ;USB-1 Interrupt
        DCD     USB2_IRQHandler                               ;USB-2 Interrupt
        DCD     LPSPI5_IRQHandler                             ;Low Power Serial Peripheral Interface 5
        DCD     LPSPI6_IRQHandler                             ;Low Power Serial Peripheral Interface 6
        DCD     LPSPI7_IRQHandler                             ;Low Power Serial Peripheral Interface 7
        DCD     LPSPI8_IRQHandler                             ;Low Power Serial Peripheral Interface 8
        DCD     LPI2C5_IRQHandler                             ;Low Power Inter-Integrated Circuit module 5
        DCD     LPI2C6_IRQHandler                             ;Low Power Inter-Integrated Circuit module 6
        DCD     LPI2C7_IRQHandler                             ;Low Power Inter-Integrated Circuit module 7
        DCD     LPI2C8_IRQHandler                             ;Low Power Inter-Integrated Circuit module 8
        DCD     PDM_HWVAD_ERROR_IRQHandler                    ;PDM interrupt
        DCD     PDM_HWVAD_EVENT_IRQHandler                    ;PDM interrupt
        DCD     PDM_ERROR_IRQHandler                          ;PDM interrupt
        DCD     PDM_EVENT_IRQHandler                          ;PDM interrupt
        DCD     Reserved205_IRQHandler                        ;AUDIO XCVR interrupt
        DCD     Reserved206_IRQHandler                        ;AUDIO XCVR interrupt
        DCD     uSDHC3_IRQHandler                             ;ultra Secure Digital Host Controller interrupt 3
        DCD     Reserved208_IRQHandler                        ;OCRAM MECC interrupt
        DCD     Reserved209_IRQHandler                        ;OCRAM MECC interrupt
        DCD     Reserved210_IRQHandler                        ;CM33 MCM interrupt
        DCD     Reserved211_IRQHandler                        ;ANAMIX SFA interrupt
        DCD     Reserved212_IRQHandler                        ;GIC700 Fault
        DCD     Reserved213_IRQHandler                        ;GIC700 Error
        DCD     Reserved214_IRQHandler                        ;GIC700 PMU Counter Overflow
        DCD     Reserved215_IRQHandler                        ;ADC interrupt
        DCD     Reserved216_IRQHandler                        ;ADC interrupt
        DCD     Reserved217_IRQHandler                        ;ADC interrupt
        DCD     Reserved218_IRQHandler                        ;s500 glue logic IRQ
        DCD     Reserved219_IRQHandler                        ;I3C1 wakeup irq after double sync
        DCD     Reserved220_IRQHandler                        ;I3C2 wakeup irq after double sync
        DCD     MU5_A_IRQHandler                              ;AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA
        DCD     MU6_A_IRQHandler                              ;AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA
        DCD     MU7_B_IRQHandler                              ;WAKEUPMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB
        DCD     MU8_B_IRQHandler                              ;WAKEUPMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB
        DCD     Reserved225_IRQHandler                        ;WAKEUPMIX XSPI Responder
        DCD     Reserved226_IRQHandler                        ;AONMIX FCCU Interrupt Reaction 0
        DCD     Reserved227_IRQHandler                        ;AONMIX FCCU Interrupt Reaction 1
        DCD     Reserved228_IRQHandler                        ;AONMIX FCCU Interrupt Reaction 2
        DCD     Reserved229_IRQHandler                        ;AONMIX STCU Selftest end Interrupt
        DCD     DISP_IRQSTEER0_IRQHandler                     ;DISPLAYMIX IRQSTEER 0
        DCD     DISP_IRQSTEER1_IRQHandler                     ;DISPLAYMIX IRQSTEER 1
        DCD     DISP_IRQSTEER2_IRQHandler                     ;DISPLAYMIX IRQSTEER 2
        DCD     DISP_IRQSTEER3_IRQHandler                     ;DISPLAYMIX IRQSTEER 3
        DCD     DISP_IRQSTEER4_IRQHandler                     ;DISPLAYMIX IRQSTEER 4
        DCD     DISP_IRQSTEER7_IRQHandler                     ;DISPLAYMIX IRQSTEER 7
        DCD     Reserved236_IRQHandler                        ;CAMERAMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA
        DCD     Reserved237_IRQHandler                        ;CAMERAMIX ISI interrupt Channel 0
        DCD     Reserved238_IRQHandler                        ;ISP Processing Interrupt - Context 0
        DCD     Reserved239_IRQHandler                        ;M7MIX MCM interrupt
        DCD     MU1_A_IRQHandler                              ;AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA
        DCD     MU1_B_IRQHandler                              ;AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB
        DCD     MU2_A_IRQHandler                              ;AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA
        DCD     MU2_B_IRQHandler                              ;AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB
        DCD     MU3_A_IRQHandler                              ;AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA
        DCD     MU3_B_IRQHandler                              ;AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB
        DCD     MU4_A_IRQHandler                              ;AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA
        DCD     MU4_B_IRQHandler                              ;AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB
        DCD     MU5_B_IRQHandler                              ;AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB
        DCD     MU6_B_IRQHandler                              ;AONMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUB
        DCD     MU7_A_IRQHandler                              ;WAKEUPMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA
        DCD     MU8_A_IRQHandler                              ;WAKEUPMIX MU Ored of all (tx,rx,gp,core,murip) interrupt to MUA
        DCD     MSGINTR1_IRQHandler                           ;MSGINTR Instance 1, Interrupt
        DCD     MSGINTR2_IRQHandler                           ;MSGINTR Instance 2, Interrupts
        DCD     Reserved254_IRQHandler                        ;V2X-FH MU APCH1 (APP1) interrupt
        DCD     Reserved255_IRQHandler                        ;V2X-FH MU APHSM2 (HSM2) interrupt
        DCD     Reserved256_IRQHandler                        ;CAMERAMIX TRDC transfer error interrupt
        DCD     Reserved257_IRQHandler                        ;DISPLAYMIX TRDC transfer error interrupt
        DCD     Reserved258_IRQHandler                        ;NETCMIX TRDC transfer error interrupt
        DCD     Reserved259_IRQHandler                        ;GPUMIX TRDC transfer error interrupt
        DCD     Reserved260_IRQHandler                        ;HSIOMIX TRDC transfer error interrupt
        DCD     Reserved261_IRQHandler                        ;VPUMIX TRDC transfer error interrupt
        DCD     Reserved262_IRQHandler                        ;AONMIX ERM Single bit corrected ECC Error
        DCD     Reserved263_IRQHandler                        ;M7MIX ERM Single bit corrected ECC Error
        DCD     Reserved264_IRQHandler                        ;WAKEUPMIX ERM Single bit corrected ECC Error
        DCD     Reserved265_IRQHandler                        ;NPUMIX ERM Single bit corrected ECC Error
        DCD     Reserved266_IRQHandler                        ;WAKEUPMIX ACP EDMA error interrupt
        DCD     Reserved267_IRQHandler                        ;OCRAM_C ECC multiple bit or address error
        DCD     Reserved268_IRQHandler                        ;CAMERAMIX Cortex-M0+ Cache write-buffer error
        DCD     Reserved269_IRQHandler                        ;CAMERAMIX Cortex-M0+ Cache data parity error
        DCD     Reserved270_IRQHandler                        ;V2X-FH MU APSHE (SHE) interrupt
        DCD     Reserved271_IRQHandler                        ;V2X-FH MU SCU/APDEBUG (DEBUG) interrupt
        DCD     DMA5_0_1_IRQHandler                           ;eDMA3 channel 0/1 interrupt
        DCD     DMA5_2_3_IRQHandler                           ;eDMA3 channel 2/3 interrupt
        DCD     DMA5_4_5_IRQHandler                           ;eDMA3 channel 4/5 interrupt
        DCD     DMA5_6_7_IRQHandler                           ;eDMA3 channel 6/7 interrupt
        DCD     DMA5_8_9_IRQHandler                           ;eDMA3 channel 8/9 interrupt
        DCD     DMA5_10_11_IRQHandler                         ;eDMA3 channel 10/11 interrupt
        DCD     DMA5_12_13_IRQHandler                         ;eDMA3 channel 12/13 interrupt
        DCD     DMA5_14_15_IRQHandler                         ;eDMA3 channel 14/15 interrupt
        DCD     DMA5_16_17_IRQHandler                         ;eDMA3 channel 16/17 interrupt
        DCD     DMA5_18_19_IRQHandler                         ;eDMA3 channel 18/19 interrupt
        DCD     DMA5_20_21_IRQHandler                         ;eDMA3 channel 20/21 interrupt
        DCD     DMA5_22_23_IRQHandler                         ;eDMA3 channel 22/23 interrupt
        DCD     DMA5_24_25_IRQHandler                         ;eDMA3 channel 24/25 interrupt
        DCD     DMA5_26_27_IRQHandler                         ;eDMA3 channel 26/27 interrupt
        DCD     DMA5_28_29_IRQHandler                         ;eDMA3 channel 28/29 interrupt
        DCD     DMA5_30_31_IRQHandler                         ;eDMA3 channel 30/31 interrupt
        DCD     DMA5_32_33_IRQHandler                         ;eDMA3 channel 32/33 interrupt
        DCD     DMA5_34_35_IRQHandler                         ;eDMA3 channel 34/35 interrupt
        DCD     DMA5_36_37_IRQHandler                         ;eDMA3 channel 36/37 interrupt
        DCD     DMA5_38_39_IRQHandler                         ;eDMA3 channel 38/39 interrupt
        DCD     DMA5_40_41_IRQHandler                         ;eDMA3 channel 40/41 interrupt
        DCD     DMA5_42_43_IRQHandler                         ;eDMA3 channel 42/43 interrupt
        DCD     DMA5_44_45_IRQHandler                         ;eDMA3 channel 44/45 interrupt
        DCD     DMA5_46_47_IRQHandler                         ;eDMA3 channel 46/47 interrupt
        DCD     DMA5_48_49_IRQHandler                         ;eDMA3 channel 48/49 interrupt
        DCD     DMA5_50_51_IRQHandler                         ;eDMA3 channel 50/51 interrupt
        DCD     DMA5_52_53_IRQHandler                         ;eDMA3 channel 52/53 interrupt
        DCD     DMA5_54_55_IRQHandler                         ;eDMA3 channel 54/55 interrupt
        DCD     DMA5_56_57_IRQHandler                         ;eDMA3 channel 56/57 interrupt
        DCD     DMA5_58_59_IRQHandler                         ;eDMA3 channel 58/59 interrupt
        DCD     DMA5_60_61_IRQHandler                         ;eDMA3 channel 60/61 interrupt
        DCD     DMA5_62_63_IRQHandler                         ;eDMA3 channel 62/63 interrupt
        DCD     Reserved304_IRQHandler                        ;GPUMIX GPU Interrupt
        DCD     Reserved305_IRQHandler                        ;GPUMIX Job Interrupt
        DCD     Reserved306_IRQHandler                        ;GPUMIX MMU Interrupt
        DCD     Reserved307_IRQHandler                        ;Reserved INTERRUPT
        DCD     Reserved308_IRQHandler                        ;Reserved interrupt
        DCD     Reserved309_IRQHandler                        ;Reserved interrupt
        DCD     Reserved310_IRQHandler                        ;Reserved interrupt
        DCD     Reserved311_IRQHandler                        ;Reserved interrupt
        DCD     Reserved312_IRQHandler                        ;Reserved interrupt
        DCD     Reserved313_IRQHandler                        ;Reserved interrupt
        DCD     Reserved314_IRQHandler                        ;Reserved interrupt
        DCD     Reserved315_IRQHandler                        ;Reserved interrupt
        DCD     Reserved316_IRQHandler                        ;Reserved interrupt
        DCD     Reserved317_IRQHandler                        ;Reserved interrupt
        DCD     Reserved318_IRQHandler                        ;Reserved interrupt
        DCD     Reserved319_IRQHandler                        ;Reserved interrupt
        DCD     Reserved320_IRQHandler                        ;NETC iEPRC PCI INT
        DCD     Reserved321_IRQHandler                        ;NETC iEPRC PCI INT
        DCD     Reserved322_IRQHandler                        ;PCIe Controller 1 INTA
        DCD     Reserved323_IRQHandler                        ;PCIe Controller 1 INTB
        DCD     Reserved324_IRQHandler                        ;PCIe Controller 1 INTC
        DCD     Reserved325_IRQHandler                        ;PCIe Controller 1 INTD
        DCD     Reserved326_IRQHandler                        ;PCIe interrupts
        DCD     Reserved327_IRQHandler                        ;PCIe Controller EDMA channel interrupt
        DCD     Reserved328_IRQHandler                        ;PCIe Controller 1 INTA
        DCD     Reserved329_IRQHandler                        ;PCIe Controller 1 INTB
        DCD     Reserved330_IRQHandler                        ;PCIe Controller 1 INTC
        DCD     Reserved331_IRQHandler                        ;PCIe Controller 1 INTD
        DCD     Reserved332_IRQHandler                        ;PCIe miscellaneous interrupts
        DCD     Reserved333_IRQHandler                        ;PCIe Controller EDMA channel interrupt
        DCD     Reserved334_IRQHandler                        ;Wakeup interrupt from CLKREQ#, WAKEUP#, BEACON_DET
        DCD     Reserved335_IRQHandler                        ;NPUMIX Functional interrupt
        DCD     Reserved336_IRQHandler                        ;DISPLAYMIX Real-time traffic TBU: Fault Handling RAS Interrupt for a contained error
        DCD     Reserved337_IRQHandler                        ;DISPLAYMIX Real-time traffic TBU: Error Handling RAS Interrupt for an uncontained error
        DCD     Reserved338_IRQHandler                        ;DISPLAYMIX Real-time traffic TBU: Critical Error Interrupt for an uncontainable error
        DCD     Reserved339_IRQHandler                        ;DISPLAYMIX Real-time traffic TBU: PMU Interrupt
        DCD     Reserved340_IRQHandler                        ;TCU Event queue, secure interrupt
        DCD     Reserved341_IRQHandler                        ;TCU Event queue, non-secure interrupt
        DCD     Reserved342_IRQHandler                        ;TCU SYNC complete, non-secure interrupt
        DCD     Reserved343_IRQHandler                        ;TCU SYNC complete, secure interrupt
        DCD     Reserved344_IRQHandler                        ;TCU global non-secure interrupt
        DCD     Reserved345_IRQHandler                        ;TCU global secure interrupt
        DCD     Reserved346_IRQHandler                        ;TCU fault handling RAS interrupt for a contained error
        DCD     Reserved347_IRQHandler                        ;TCU error recovery RAS interrupt for an uncontained error
        DCD     Reserved348_IRQHandler                        ;TCU critical error interrupt, for an uncontainable uncorrected error
        DCD     Reserved349_IRQHandler                        ;TCU PMU interrupt
        DCD     Reserved350_IRQHandler                        ;TCU Page Request Interface
        DCD     Reserved351_IRQHandler                        ;SRC GPC Low Power Handshake Gasket interrupt request for system management
        DCD     Reserved352_IRQHandler                        ;CAMERAMIX MU Ored of all
        DCD     Reserved353_IRQHandler                        ;CAMERAMIX MU Ored of all
        DCD     Reserved354_IRQHandler                        ;CAMERAMIX MU Ored of all
        DCD     Reserved355_IRQHandler                        ;CAMERAMIX MU Ored of all
        DCD     Reserved356_IRQHandler                        ;CAMERAMIX MU Ored of all
        DCD     Reserved357_IRQHandler                        ;CAMERAMIX MU Ored of all
        DCD     Reserved358_IRQHandler                        ;CAMERAMIX MU Ored of all
        DCD     Reserved359_IRQHandler                        ;CAMERAMIX MU Ored of all
        DCD     Reserved360_IRQHandler                        ;CAMERAMIX ISI interrupt Channel 1
        DCD     Reserved361_IRQHandler                        ;CAMERAMIX ISI interrupt Channel 2
        DCD     Reserved362_IRQHandler                        ;CAMERAMIX ISI interrupt Channel 3
        DCD     Reserved363_IRQHandler                        ;CAMERAMIX ISI interrupt Channel 4
        DCD     Reserved364_IRQHandler                        ;CAMERAMIX ISI interrupt Channel 5
        DCD     Reserved365_IRQHandler                        ;CAMERAMIX ISI interrupt Channel 6
        DCD     Reserved366_IRQHandler                        ;CAMERAMIX ISI interrupt Channel 7
        DCD     Reserved367_IRQHandler                        ;CAMERAMIX EDMA error interrupt
        DCD     Reserved368_IRQHandler                        ;CAMERAMIX EDMA channel 0 interrupt
        DCD     Reserved369_IRQHandler                        ;CAMERAMIX EDMA channel 2 interrupt
        DCD     Reserved370_IRQHandler                        ;CAMERAMIX EDMA channel 4 interrupt
        DCD     Reserved371_IRQHandler                        ;CAMERAMIX EDMA channel 6 interrupt
        DCD     Reserved372_IRQHandler                        ;CAMERAMIX EDMA channel 8 interrupt
        DCD     Reserved373_IRQHandler                        ;CAMERAMIX EDMA channel 10 interrupt
        DCD     Reserved374_IRQHandler                        ;CAMERAMIX EDMA channel 12 interrupt
        DCD     Reserved375_IRQHandler                        ;CAMERAMIX EDMA channel 14 interrupt
        DCD     Reserved376_IRQHandler                        ;CAMERAMIX EDMA channel 16 interrupt
        DCD     Reserved377_IRQHandler                        ;CAMERAMIX EDMA channel 18 interrupt
        DCD     Reserved378_IRQHandler                        ;CAMERAMIX EDMA channel 20 interrupt
        DCD     Reserved379_IRQHandler                        ;CAMERAMIX EDMA channel 22 interrupt
        DCD     Reserved380_IRQHandler                        ;CAMERAMIX EDMA channel 24 interrupt
        DCD     Reserved381_IRQHandler                        ;CAMERAMIX EDMA channel 26 interrupt
        DCD     Reserved382_IRQHandler                        ;CAMERAMIX EDMA channel 28 interrupt
        DCD     Reserved383_IRQHandler                        ;CAMERAMIX EDMA channel 30 interrupt
        DCD     Reserved384_IRQHandler                        ;CAMERAMIX CSI Formatting Unit 1: Buffer overflow
        DCD     Reserved385_IRQHandler                        ;CAMERAMIX CSI Formatting Unit 1: Interlaced Error
        DCD     Reserved386_IRQHandler                        ;CAMERAMIX CSI Formatting Unit 1: Pixel Data Type Error
        DCD     Reserved387_IRQHandler                        ;CAMERAMIX CSI Formatting Unit 2: Buffer overflow
        DCD     Reserved388_IRQHandler                        ;CAMERAMIX CSI Formatting Unit 2: Interlaced Error
        DCD     Reserved389_IRQHandler                        ;CAMERAMIX CSI Formatting Unit 2: Pixel Data Type Error
        DCD     Reserved390_IRQHandler                        ;CAMERAMIX CSI1
        DCD     Reserved391_IRQHandler                        ;CAMERAMIX CSI2
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size  EQU   __Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        CPSID   I               ; Mask interrupts
        LDR     R0, =0xE000ED08
        LDR     R1, =__vector_table
        STR     R1, [R0]
        LDR     R2, [R1]
        MSR     MSP, R2
        LDR     R0, =SystemInit
        BLX     R0
        CPSIE   I               ; Unmask interrupts
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B .

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B .

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B .

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B .

        PUBWEAK SecureFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SecureFault_Handler
        B .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B .

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B .

        PUBWEAK Reserved16_IRQHandler
        PUBWEAK Reserved17_IRQHandler
        PUBWEAK Reserved18_IRQHandler
        PUBWEAK Reserved19_IRQHandler
        PUBWEAK Reserved20_IRQHandler
        PUBWEAK Reserved21_IRQHandler
        PUBWEAK Reserved22_IRQHandler
        PUBWEAK Reserved23_IRQHandler
        PUBWEAK CAN1_IRQHandler
        PUBWEAK CAN1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_IRQHandler
        LDR     R0, =CAN1_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_ERROR_IRQHandler
        PUBWEAK CAN1_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_ERROR_IRQHandler
        LDR     R0, =CAN1_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved26_IRQHandler
        PUBWEAK Reserved27_IRQHandler
        PUBWEAK I3C1_IRQHandler
        PUBWEAK I3C1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I3C1_IRQHandler
        LDR     R0, =I3C1_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C1_IRQHandler
        PUBWEAK LPI2C1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C1_IRQHandler
        LDR     R0, =LPI2C1_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C2_IRQHandler
        PUBWEAK LPI2C2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C2_IRQHandler
        LDR     R0, =LPI2C2_DriverIRQHandler
        BX      R0

        PUBWEAK LPIT1_IRQHandler
        PUBWEAK LPSPI1_IRQHandler
        PUBWEAK LPSPI1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI1_IRQHandler
        LDR     R0, =LPSPI1_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI2_IRQHandler
        PUBWEAK LPSPI2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI2_IRQHandler
        LDR     R0, =LPSPI2_DriverIRQHandler
        BX      R0

        PUBWEAK LPTMR1_IRQHandler
        PUBWEAK LPUART1_IRQHandler
        PUBWEAK LPUART1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART1_IRQHandler
        LDR     R0, =LPUART1_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART2_IRQHandler
        PUBWEAK LPUART2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART2_IRQHandler
        LDR     R0, =LPUART2_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved37_IRQHandler
        PUBWEAK Reserved38_IRQHandler
        PUBWEAK Reserved39_IRQHandler
        PUBWEAK Reserved40_IRQHandler
        PUBWEAK Reserved41_IRQHandler
        PUBWEAK Reserved42_IRQHandler
        PUBWEAK V2X_FH_APCH0_IRQHandler
        PUBWEAK V2X_FH_APHSM1_IRQHandler
        PUBWEAK TPM1_IRQHandler
        PUBWEAK TPM2_IRQHandler
        PUBWEAK WDOG1_IRQHandler
        PUBWEAK WDOG2_IRQHandler
        PUBWEAK TRDC_MGR_A_IRQHandler
        PUBWEAK SAI1_IRQHandler
        PUBWEAK SAI1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI1_IRQHandler
        LDR     R0, =SAI1_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved51_IRQHandler
        PUBWEAK Reserved52_IRQHandler
        PUBWEAK Reserved53_IRQHandler
        PUBWEAK CAN2_IRQHandler
        PUBWEAK CAN2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_IRQHandler
        LDR     R0, =CAN2_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_ERROR_IRQHandler
        PUBWEAK CAN2_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_ERROR_IRQHandler
        LDR     R0, =CAN2_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_IRQHandler
        PUBWEAK CAN3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_IRQHandler
        LDR     R0, =CAN3_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_ERROR_IRQHandler
        PUBWEAK CAN3_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_ERROR_IRQHandler
        LDR     R0, =CAN3_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_IRQHandler
        PUBWEAK CAN4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_IRQHandler
        LDR     R0, =CAN4_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_ERROR_IRQHandler
        PUBWEAK CAN4_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_ERROR_IRQHandler
        LDR     R0, =CAN4_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_IRQHandler
        PUBWEAK CAN5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_IRQHandler
        LDR     R0, =CAN5_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_ERROR_IRQHandler
        PUBWEAK CAN5_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_ERROR_IRQHandler
        LDR     R0, =CAN5_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXIO1_IRQHandler
        PUBWEAK FLEXIO1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXIO1_IRQHandler
        LDR     R0, =FLEXIO1_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXIO2_IRQHandler
        PUBWEAK FLEXIO2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXIO2_IRQHandler
        LDR     R0, =FLEXIO2_DriverIRQHandler
        BX      R0

        PUBWEAK FlexSPI1_IRQHandler
        PUBWEAK FlexSPI1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FlexSPI1_IRQHandler
        LDR     R0, =FlexSPI1_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved65_IRQHandler
        PUBWEAK Reserved66_IRQHandler
        PUBWEAK Reserved67_IRQHandler
        PUBWEAK Reserved68_IRQHandler
        PUBWEAK Reserved69_IRQHandler
        PUBWEAK Reserved70_IRQHandler
        PUBWEAK Reserved71_IRQHandler
        PUBWEAK Reserved72_IRQHandler
        PUBWEAK I3C2_IRQHandler
        PUBWEAK I3C2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I3C2_IRQHandler
        LDR     R0, =I3C2_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C3_IRQHandler
        PUBWEAK LPI2C3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C3_IRQHandler
        LDR     R0, =LPI2C3_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C4_IRQHandler
        PUBWEAK LPI2C4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C4_IRQHandler
        LDR     R0, =LPI2C4_DriverIRQHandler
        BX      R0

        PUBWEAK LPIT2_IRQHandler
        PUBWEAK LPSPI3_IRQHandler
        PUBWEAK LPSPI3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI3_IRQHandler
        LDR     R0, =LPSPI3_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI4_IRQHandler
        PUBWEAK LPSPI4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI4_IRQHandler
        LDR     R0, =LPSPI4_DriverIRQHandler
        BX      R0

        PUBWEAK LPTMR2_IRQHandler
        PUBWEAK LPUART3_IRQHandler
        PUBWEAK LPUART3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART3_IRQHandler
        LDR     R0, =LPUART3_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART4_IRQHandler
        PUBWEAK LPUART4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART4_IRQHandler
        LDR     R0, =LPUART4_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART5_IRQHandler
        PUBWEAK LPUART5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART5_IRQHandler
        LDR     R0, =LPUART5_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART6_IRQHandler
        PUBWEAK LPUART6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART6_IRQHandler
        LDR     R0, =LPUART6_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART7_IRQHandler
        PUBWEAK LPUART7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART7_IRQHandler
        LDR     R0, =LPUART7_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART8_IRQHandler
        PUBWEAK LPUART8_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART8_IRQHandler
        LDR     R0, =LPUART8_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved86_IRQHandler
        PUBWEAK Reserved87_IRQHandler
        PUBWEAK Reserved88_IRQHandler
        PUBWEAK TPM3_IRQHandler
        PUBWEAK TPM4_IRQHandler
        PUBWEAK TPM5_IRQHandler
        PUBWEAK TPM6_IRQHandler
        PUBWEAK WDOG3_IRQHandler
        PUBWEAK WDOG4_IRQHandler
        PUBWEAK WDOG5_IRQHandler
        PUBWEAK Reserved96_IRQHandler
        PUBWEAK Reserved97_IRQHandler
        PUBWEAK Reserved98_IRQHandler
        PUBWEAK Reserved99_IRQHandler
        PUBWEAK Reserved100_IRQHandler
        PUBWEAK Reserved101_IRQHandler
        PUBWEAK uSDHC1_IRQHandler
        PUBWEAK uSDHC1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
uSDHC1_IRQHandler
        LDR     R0, =uSDHC1_DriverIRQHandler
        BX      R0

        PUBWEAK uSDHC2_IRQHandler
        PUBWEAK uSDHC2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
uSDHC2_IRQHandler
        LDR     R0, =uSDHC2_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved104_IRQHandler
        PUBWEAK Reserved105_IRQHandler
        PUBWEAK Reserved106_IRQHandler
        PUBWEAK Reserved107_IRQHandler
        PUBWEAK Reserved108_IRQHandler
        PUBWEAK Reserved109_IRQHandler
        PUBWEAK Reserved110_IRQHandler
        PUBWEAK DMA3_ERROR_IRQHandler
        PUBWEAK DMA3_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_ERROR_IRQHandler
        LDR     R0, =DMA3_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_0_IRQHandler
        PUBWEAK DMA3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_0_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_1_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_2_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_3_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_4_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_5_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_6_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_7_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_8_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_9_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_9_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_10_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_11_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_11_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_12_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_12_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_13_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_13_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_14_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_14_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_15_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_15_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_16_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_16_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_17_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_17_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_18_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_18_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_19_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_19_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_20_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_20_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_21_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_21_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_22_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_22_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_23_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_23_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_24_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_24_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_25_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_25_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_26_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_26_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_27_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_27_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_28_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_28_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_29_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_29_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_30_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_30_IRQHandler
        LDR     R0, =DMA3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_ERROR_IRQHandler
        PUBWEAK DMA4_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_ERROR_IRQHandler
        LDR     R0, =DMA4_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_0_1_IRQHandler
        PUBWEAK DMA4_0_1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_0_1_IRQHandler
        LDR     R0, =DMA4_0_1_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_2_3_IRQHandler
        PUBWEAK DMA4_2_3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_2_3_IRQHandler
        LDR     R0, =DMA4_2_3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_4_5_IRQHandler
        PUBWEAK DMA4_4_5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_4_5_IRQHandler
        LDR     R0, =DMA4_4_5_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_6_7_IRQHandler
        PUBWEAK DMA4_6_7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_6_7_IRQHandler
        LDR     R0, =DMA4_6_7_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_8_9_IRQHandler
        PUBWEAK DMA4_8_9_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_8_9_IRQHandler
        LDR     R0, =DMA4_8_9_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_10_11_IRQHandler
        PUBWEAK DMA4_10_11_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_10_11_IRQHandler
        LDR     R0, =DMA4_10_11_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_12_13_IRQHandler
        PUBWEAK DMA4_12_13_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_12_13_IRQHandler
        LDR     R0, =DMA4_12_13_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_14_15_IRQHandler
        PUBWEAK DMA4_14_15_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_14_15_IRQHandler
        LDR     R0, =DMA4_14_15_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_16_17_IRQHandler
        PUBWEAK DMA4_16_17_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_16_17_IRQHandler
        LDR     R0, =DMA4_16_17_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_18_19_IRQHandler
        PUBWEAK DMA4_18_19_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_18_19_IRQHandler
        LDR     R0, =DMA4_18_19_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_20_21_IRQHandler
        PUBWEAK DMA4_20_21_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_20_21_IRQHandler
        LDR     R0, =DMA4_20_21_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_22_23_IRQHandler
        PUBWEAK DMA4_22_23_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_22_23_IRQHandler
        LDR     R0, =DMA4_22_23_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_24_25_IRQHandler
        PUBWEAK DMA4_24_25_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_24_25_IRQHandler
        LDR     R0, =DMA4_24_25_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_26_27_IRQHandler
        PUBWEAK DMA4_26_27_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_26_27_IRQHandler
        LDR     R0, =DMA4_26_27_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_28_29_IRQHandler
        PUBWEAK DMA4_28_29_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_28_29_IRQHandler
        LDR     R0, =DMA4_28_29_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_30_31_IRQHandler
        PUBWEAK DMA4_30_31_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_30_31_IRQHandler
        LDR     R0, =DMA4_30_31_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_32_33_IRQHandler
        PUBWEAK DMA4_32_33_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_32_33_IRQHandler
        LDR     R0, =DMA4_32_33_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_34_35_IRQHandler
        PUBWEAK DMA4_34_35_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_34_35_IRQHandler
        LDR     R0, =DMA4_34_35_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_36_37_IRQHandler
        PUBWEAK DMA4_36_37_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_36_37_IRQHandler
        LDR     R0, =DMA4_36_37_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_38_39_IRQHandler
        PUBWEAK DMA4_38_39_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_38_39_IRQHandler
        LDR     R0, =DMA4_38_39_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_40_41_IRQHandler
        PUBWEAK DMA4_40_41_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_40_41_IRQHandler
        LDR     R0, =DMA4_40_41_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_42_43_IRQHandler
        PUBWEAK DMA4_42_43_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_42_43_IRQHandler
        LDR     R0, =DMA4_42_43_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_44_45_IRQHandler
        PUBWEAK DMA4_44_45_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_44_45_IRQHandler
        LDR     R0, =DMA4_44_45_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_46_47_IRQHandler
        PUBWEAK DMA4_46_47_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_46_47_IRQHandler
        LDR     R0, =DMA4_46_47_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_48_49_IRQHandler
        PUBWEAK DMA4_48_49_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_48_49_IRQHandler
        LDR     R0, =DMA4_48_49_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_50_51_IRQHandler
        PUBWEAK DMA4_50_51_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_50_51_IRQHandler
        LDR     R0, =DMA4_50_51_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_52_53_IRQHandler
        PUBWEAK DMA4_52_53_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_52_53_IRQHandler
        LDR     R0, =DMA4_52_53_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_54_55_IRQHandler
        PUBWEAK DMA4_54_55_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_54_55_IRQHandler
        LDR     R0, =DMA4_54_55_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_56_57_IRQHandler
        PUBWEAK DMA4_56_57_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_56_57_IRQHandler
        LDR     R0, =DMA4_56_57_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_58_59_IRQHandler
        PUBWEAK DMA4_58_59_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_58_59_IRQHandler
        LDR     R0, =DMA4_58_59_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_60_61_IRQHandler
        PUBWEAK DMA4_60_61_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_60_61_IRQHandler
        LDR     R0, =DMA4_60_61_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_62_63_IRQHandler
        PUBWEAK DMA4_62_63_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_62_63_IRQHandler
        LDR     R0, =DMA4_62_63_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved176_IRQHandler
        PUBWEAK Reserved177_IRQHandler
        PUBWEAK Reserved178_IRQHandler
        PUBWEAK Reserved179_IRQHandler
        PUBWEAK Reserved180_IRQHandler
        PUBWEAK Reserved181_IRQHandler
        PUBWEAK Reserved182_IRQHandler
        PUBWEAK Reserved183_IRQHandler
        PUBWEAK Reserved184_IRQHandler
        PUBWEAK SAI2_IRQHandler
        PUBWEAK SAI2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI2_IRQHandler
        LDR     R0, =SAI2_DriverIRQHandler
        BX      R0

        PUBWEAK SAI3_IRQHandler
        PUBWEAK SAI3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI3_IRQHandler
        LDR     R0, =SAI3_DriverIRQHandler
        BX      R0

        PUBWEAK SAI4_IRQHandler
        PUBWEAK SAI4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI4_IRQHandler
        LDR     R0, =SAI4_DriverIRQHandler
        BX      R0

        PUBWEAK SAI5_IRQHandler
        PUBWEAK SAI5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI5_IRQHandler
        LDR     R0, =SAI5_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved189_IRQHandler
        PUBWEAK Reserved190_IRQHandler
        PUBWEAK USB1_IRQHandler
        PUBWEAK USB2_IRQHandler
        PUBWEAK LPSPI5_IRQHandler
        PUBWEAK LPSPI5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI5_IRQHandler
        LDR     R0, =LPSPI5_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI6_IRQHandler
        PUBWEAK LPSPI6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI6_IRQHandler
        LDR     R0, =LPSPI6_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI7_IRQHandler
        PUBWEAK LPSPI7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI7_IRQHandler
        LDR     R0, =LPSPI7_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI8_IRQHandler
        PUBWEAK LPSPI8_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI8_IRQHandler
        LDR     R0, =LPSPI8_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C5_IRQHandler
        PUBWEAK LPI2C5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C5_IRQHandler
        LDR     R0, =LPI2C5_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C6_IRQHandler
        PUBWEAK LPI2C6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C6_IRQHandler
        LDR     R0, =LPI2C6_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C7_IRQHandler
        PUBWEAK LPI2C7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C7_IRQHandler
        LDR     R0, =LPI2C7_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C8_IRQHandler
        PUBWEAK LPI2C8_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C8_IRQHandler
        LDR     R0, =LPI2C8_DriverIRQHandler
        BX      R0

        PUBWEAK PDM_HWVAD_ERROR_IRQHandler
        PUBWEAK PDM_HWVAD_EVENT_IRQHandler
        PUBWEAK PDM_ERROR_IRQHandler
        PUBWEAK PDM_EVENT_IRQHandler
        PUBWEAK PDM_EVENT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PDM_EVENT_IRQHandler
        LDR     R0, =PDM_EVENT_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved205_IRQHandler
        PUBWEAK Reserved206_IRQHandler
        PUBWEAK uSDHC3_IRQHandler
        PUBWEAK uSDHC3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
uSDHC3_IRQHandler
        LDR     R0, =uSDHC3_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved208_IRQHandler
        PUBWEAK Reserved209_IRQHandler
        PUBWEAK Reserved210_IRQHandler
        PUBWEAK Reserved211_IRQHandler
        PUBWEAK Reserved212_IRQHandler
        PUBWEAK Reserved213_IRQHandler
        PUBWEAK Reserved214_IRQHandler
        PUBWEAK Reserved215_IRQHandler
        PUBWEAK Reserved216_IRQHandler
        PUBWEAK Reserved217_IRQHandler
        PUBWEAK Reserved218_IRQHandler
        PUBWEAK Reserved219_IRQHandler
        PUBWEAK Reserved220_IRQHandler
        PUBWEAK MU5_A_IRQHandler
        PUBWEAK MU6_A_IRQHandler
        PUBWEAK MU7_B_IRQHandler
        PUBWEAK MU8_B_IRQHandler
        PUBWEAK Reserved225_IRQHandler
        PUBWEAK Reserved226_IRQHandler
        PUBWEAK Reserved227_IRQHandler
        PUBWEAK Reserved228_IRQHandler
        PUBWEAK Reserved229_IRQHandler
        PUBWEAK DISP_IRQSTEER0_IRQHandler
        PUBWEAK DISP_IRQSTEER0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DISP_IRQSTEER0_IRQHandler
        LDR     R0, =DISP_IRQSTEER0_DriverIRQHandler
        BX      R0

        PUBWEAK DISP_IRQSTEER1_IRQHandler
        PUBWEAK DISP_IRQSTEER1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DISP_IRQSTEER1_IRQHandler
        LDR     R0, =DISP_IRQSTEER1_DriverIRQHandler
        BX      R0

        PUBWEAK DISP_IRQSTEER2_IRQHandler
        PUBWEAK DISP_IRQSTEER2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DISP_IRQSTEER2_IRQHandler
        LDR     R0, =DISP_IRQSTEER2_DriverIRQHandler
        BX      R0

        PUBWEAK DISP_IRQSTEER3_IRQHandler
        PUBWEAK DISP_IRQSTEER3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DISP_IRQSTEER3_IRQHandler
        LDR     R0, =DISP_IRQSTEER3_DriverIRQHandler
        BX      R0

        PUBWEAK DISP_IRQSTEER4_IRQHandler
        PUBWEAK DISP_IRQSTEER4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DISP_IRQSTEER4_IRQHandler
        LDR     R0, =DISP_IRQSTEER4_DriverIRQHandler
        BX      R0

        PUBWEAK DISP_IRQSTEER7_IRQHandler
        PUBWEAK DISP_IRQSTEER7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DISP_IRQSTEER7_IRQHandler
        LDR     R0, =DISP_IRQSTEER7_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved236_IRQHandler
        PUBWEAK Reserved237_IRQHandler
        PUBWEAK Reserved238_IRQHandler
        PUBWEAK Reserved239_IRQHandler
        PUBWEAK MU1_A_IRQHandler
        PUBWEAK MU1_B_IRQHandler
        PUBWEAK MU2_A_IRQHandler
        PUBWEAK MU2_B_IRQHandler
        PUBWEAK MU3_A_IRQHandler
        PUBWEAK MU3_B_IRQHandler
        PUBWEAK MU4_A_IRQHandler
        PUBWEAK MU4_B_IRQHandler
        PUBWEAK MU5_B_IRQHandler
        PUBWEAK MU6_B_IRQHandler
        PUBWEAK MU7_A_IRQHandler
        PUBWEAK MU8_A_IRQHandler
        PUBWEAK MSGINTR1_IRQHandler
        PUBWEAK MSGINTR2_IRQHandler
        PUBWEAK Reserved254_IRQHandler
        PUBWEAK Reserved255_IRQHandler
        PUBWEAK Reserved256_IRQHandler
        PUBWEAK Reserved257_IRQHandler
        PUBWEAK Reserved258_IRQHandler
        PUBWEAK Reserved259_IRQHandler
        PUBWEAK Reserved260_IRQHandler
        PUBWEAK Reserved261_IRQHandler
        PUBWEAK Reserved262_IRQHandler
        PUBWEAK Reserved263_IRQHandler
        PUBWEAK Reserved264_IRQHandler
        PUBWEAK Reserved265_IRQHandler
        PUBWEAK Reserved266_IRQHandler
        PUBWEAK Reserved267_IRQHandler
        PUBWEAK Reserved268_IRQHandler
        PUBWEAK Reserved269_IRQHandler
        PUBWEAK Reserved270_IRQHandler
        PUBWEAK Reserved271_IRQHandler
        PUBWEAK DMA5_0_1_IRQHandler
        PUBWEAK DMA5_0_1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_0_1_IRQHandler
        LDR     R0, =DMA5_0_1_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_2_3_IRQHandler
        PUBWEAK DMA5_2_3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_2_3_IRQHandler
        LDR     R0, =DMA5_2_3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_4_5_IRQHandler
        PUBWEAK DMA5_4_5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_4_5_IRQHandler
        LDR     R0, =DMA5_4_5_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_6_7_IRQHandler
        PUBWEAK DMA5_6_7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_6_7_IRQHandler
        LDR     R0, =DMA5_6_7_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_8_9_IRQHandler
        PUBWEAK DMA5_8_9_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_8_9_IRQHandler
        LDR     R0, =DMA5_8_9_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_10_11_IRQHandler
        PUBWEAK DMA5_10_11_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_10_11_IRQHandler
        LDR     R0, =DMA5_10_11_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_12_13_IRQHandler
        PUBWEAK DMA5_12_13_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_12_13_IRQHandler
        LDR     R0, =DMA5_12_13_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_14_15_IRQHandler
        PUBWEAK DMA5_14_15_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_14_15_IRQHandler
        LDR     R0, =DMA5_14_15_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_16_17_IRQHandler
        PUBWEAK DMA5_16_17_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_16_17_IRQHandler
        LDR     R0, =DMA5_16_17_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_18_19_IRQHandler
        PUBWEAK DMA5_18_19_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_18_19_IRQHandler
        LDR     R0, =DMA5_18_19_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_20_21_IRQHandler
        PUBWEAK DMA5_20_21_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_20_21_IRQHandler
        LDR     R0, =DMA5_20_21_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_22_23_IRQHandler
        PUBWEAK DMA5_22_23_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_22_23_IRQHandler
        LDR     R0, =DMA5_22_23_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_24_25_IRQHandler
        PUBWEAK DMA5_24_25_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_24_25_IRQHandler
        LDR     R0, =DMA5_24_25_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_26_27_IRQHandler
        PUBWEAK DMA5_26_27_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_26_27_IRQHandler
        LDR     R0, =DMA5_26_27_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_28_29_IRQHandler
        PUBWEAK DMA5_28_29_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_28_29_IRQHandler
        LDR     R0, =DMA5_28_29_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_30_31_IRQHandler
        PUBWEAK DMA5_30_31_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_30_31_IRQHandler
        LDR     R0, =DMA5_30_31_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_32_33_IRQHandler
        PUBWEAK DMA5_32_33_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_32_33_IRQHandler
        LDR     R0, =DMA5_32_33_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_34_35_IRQHandler
        PUBWEAK DMA5_34_35_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_34_35_IRQHandler
        LDR     R0, =DMA5_34_35_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_36_37_IRQHandler
        PUBWEAK DMA5_36_37_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_36_37_IRQHandler
        LDR     R0, =DMA5_36_37_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_38_39_IRQHandler
        PUBWEAK DMA5_38_39_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_38_39_IRQHandler
        LDR     R0, =DMA5_38_39_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_40_41_IRQHandler
        PUBWEAK DMA5_40_41_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_40_41_IRQHandler
        LDR     R0, =DMA5_40_41_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_42_43_IRQHandler
        PUBWEAK DMA5_42_43_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_42_43_IRQHandler
        LDR     R0, =DMA5_42_43_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_44_45_IRQHandler
        PUBWEAK DMA5_44_45_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_44_45_IRQHandler
        LDR     R0, =DMA5_44_45_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_46_47_IRQHandler
        PUBWEAK DMA5_46_47_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_46_47_IRQHandler
        LDR     R0, =DMA5_46_47_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_48_49_IRQHandler
        PUBWEAK DMA5_48_49_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_48_49_IRQHandler
        LDR     R0, =DMA5_48_49_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_50_51_IRQHandler
        PUBWEAK DMA5_50_51_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_50_51_IRQHandler
        LDR     R0, =DMA5_50_51_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_52_53_IRQHandler
        PUBWEAK DMA5_52_53_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_52_53_IRQHandler
        LDR     R0, =DMA5_52_53_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_54_55_IRQHandler
        PUBWEAK DMA5_54_55_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_54_55_IRQHandler
        LDR     R0, =DMA5_54_55_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_56_57_IRQHandler
        PUBWEAK DMA5_56_57_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_56_57_IRQHandler
        LDR     R0, =DMA5_56_57_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_58_59_IRQHandler
        PUBWEAK DMA5_58_59_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_58_59_IRQHandler
        LDR     R0, =DMA5_58_59_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_60_61_IRQHandler
        PUBWEAK DMA5_60_61_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_60_61_IRQHandler
        LDR     R0, =DMA5_60_61_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_62_63_IRQHandler
        PUBWEAK DMA5_62_63_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_62_63_IRQHandler
        LDR     R0, =DMA5_62_63_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved304_IRQHandler
        PUBWEAK Reserved305_IRQHandler
        PUBWEAK Reserved306_IRQHandler
        PUBWEAK Reserved307_IRQHandler
        PUBWEAK Reserved308_IRQHandler
        PUBWEAK Reserved309_IRQHandler
        PUBWEAK Reserved310_IRQHandler
        PUBWEAK Reserved311_IRQHandler
        PUBWEAK Reserved312_IRQHandler
        PUBWEAK Reserved313_IRQHandler
        PUBWEAK Reserved314_IRQHandler
        PUBWEAK Reserved315_IRQHandler
        PUBWEAK Reserved316_IRQHandler
        PUBWEAK Reserved317_IRQHandler
        PUBWEAK Reserved318_IRQHandler
        PUBWEAK Reserved319_IRQHandler
        PUBWEAK Reserved320_IRQHandler
        PUBWEAK Reserved321_IRQHandler
        PUBWEAK Reserved322_IRQHandler
        PUBWEAK Reserved323_IRQHandler
        PUBWEAK Reserved324_IRQHandler
        PUBWEAK Reserved325_IRQHandler
        PUBWEAK Reserved326_IRQHandler
        PUBWEAK Reserved327_IRQHandler
        PUBWEAK Reserved328_IRQHandler
        PUBWEAK Reserved329_IRQHandler
        PUBWEAK Reserved330_IRQHandler
        PUBWEAK Reserved331_IRQHandler
        PUBWEAK Reserved332_IRQHandler
        PUBWEAK Reserved333_IRQHandler
        PUBWEAK Reserved334_IRQHandler
        PUBWEAK Reserved335_IRQHandler
        PUBWEAK Reserved336_IRQHandler
        PUBWEAK Reserved337_IRQHandler
        PUBWEAK Reserved338_IRQHandler
        PUBWEAK Reserved339_IRQHandler
        PUBWEAK Reserved340_IRQHandler
        PUBWEAK Reserved341_IRQHandler
        PUBWEAK Reserved342_IRQHandler
        PUBWEAK Reserved343_IRQHandler
        PUBWEAK Reserved344_IRQHandler
        PUBWEAK Reserved345_IRQHandler
        PUBWEAK Reserved346_IRQHandler
        PUBWEAK Reserved347_IRQHandler
        PUBWEAK Reserved348_IRQHandler
        PUBWEAK Reserved349_IRQHandler
        PUBWEAK Reserved350_IRQHandler
        PUBWEAK Reserved351_IRQHandler
        PUBWEAK Reserved352_IRQHandler
        PUBWEAK Reserved353_IRQHandler
        PUBWEAK Reserved354_IRQHandler
        PUBWEAK Reserved355_IRQHandler
        PUBWEAK Reserved356_IRQHandler
        PUBWEAK Reserved357_IRQHandler
        PUBWEAK Reserved358_IRQHandler
        PUBWEAK Reserved359_IRQHandler
        PUBWEAK Reserved360_IRQHandler
        PUBWEAK Reserved361_IRQHandler
        PUBWEAK Reserved362_IRQHandler
        PUBWEAK Reserved363_IRQHandler
        PUBWEAK Reserved364_IRQHandler
        PUBWEAK Reserved365_IRQHandler
        PUBWEAK Reserved366_IRQHandler
        PUBWEAK Reserved367_IRQHandler
        PUBWEAK Reserved368_IRQHandler
        PUBWEAK Reserved369_IRQHandler
        PUBWEAK Reserved370_IRQHandler
        PUBWEAK Reserved371_IRQHandler
        PUBWEAK Reserved372_IRQHandler
        PUBWEAK Reserved373_IRQHandler
        PUBWEAK Reserved374_IRQHandler
        PUBWEAK Reserved375_IRQHandler
        PUBWEAK Reserved376_IRQHandler
        PUBWEAK Reserved377_IRQHandler
        PUBWEAK Reserved378_IRQHandler
        PUBWEAK Reserved379_IRQHandler
        PUBWEAK Reserved380_IRQHandler
        PUBWEAK Reserved381_IRQHandler
        PUBWEAK Reserved382_IRQHandler
        PUBWEAK Reserved383_IRQHandler
        PUBWEAK Reserved384_IRQHandler
        PUBWEAK Reserved385_IRQHandler
        PUBWEAK Reserved386_IRQHandler
        PUBWEAK Reserved387_IRQHandler
        PUBWEAK Reserved388_IRQHandler
        PUBWEAK Reserved389_IRQHandler
        PUBWEAK Reserved390_IRQHandler
        PUBWEAK Reserved391_IRQHandler
        PUBWEAK DefaultISR
        SECTION .text:CODE:REORDER:NOROOT(1)
Reserved16_IRQHandler
Reserved17_IRQHandler
Reserved18_IRQHandler
Reserved19_IRQHandler
Reserved20_IRQHandler
Reserved21_IRQHandler
Reserved22_IRQHandler
Reserved23_IRQHandler
CAN1_DriverIRQHandler
CAN1_ERROR_DriverIRQHandler
Reserved26_IRQHandler
Reserved27_IRQHandler
I3C1_DriverIRQHandler
LPI2C1_DriverIRQHandler
LPI2C2_DriverIRQHandler
LPIT1_IRQHandler
LPSPI1_DriverIRQHandler
LPSPI2_DriverIRQHandler
LPTMR1_IRQHandler
LPUART1_DriverIRQHandler
LPUART2_DriverIRQHandler
Reserved37_IRQHandler
Reserved38_IRQHandler
Reserved39_IRQHandler
Reserved40_IRQHandler
Reserved41_IRQHandler
Reserved42_IRQHandler
V2X_FH_APCH0_IRQHandler
V2X_FH_APHSM1_IRQHandler
TPM1_IRQHandler
TPM2_IRQHandler
WDOG1_IRQHandler
WDOG2_IRQHandler
TRDC_MGR_A_IRQHandler
SAI1_DriverIRQHandler
Reserved51_IRQHandler
Reserved52_IRQHandler
Reserved53_IRQHandler
CAN2_DriverIRQHandler
CAN2_ERROR_DriverIRQHandler
CAN3_DriverIRQHandler
CAN3_ERROR_DriverIRQHandler
CAN4_DriverIRQHandler
CAN4_ERROR_DriverIRQHandler
CAN5_DriverIRQHandler
CAN5_ERROR_DriverIRQHandler
FLEXIO1_DriverIRQHandler
FLEXIO2_DriverIRQHandler
FlexSPI1_DriverIRQHandler
Reserved65_IRQHandler
Reserved66_IRQHandler
Reserved67_IRQHandler
Reserved68_IRQHandler
Reserved69_IRQHandler
Reserved70_IRQHandler
Reserved71_IRQHandler
Reserved72_IRQHandler
I3C2_DriverIRQHandler
LPI2C3_DriverIRQHandler
LPI2C4_DriverIRQHandler
LPIT2_IRQHandler
LPSPI3_DriverIRQHandler
LPSPI4_DriverIRQHandler
LPTMR2_IRQHandler
LPUART3_DriverIRQHandler
LPUART4_DriverIRQHandler
LPUART5_DriverIRQHandler
LPUART6_DriverIRQHandler
LPUART7_DriverIRQHandler
LPUART8_DriverIRQHandler
Reserved86_IRQHandler
Reserved87_IRQHandler
Reserved88_IRQHandler
TPM3_IRQHandler
TPM4_IRQHandler
TPM5_IRQHandler
TPM6_IRQHandler
WDOG3_IRQHandler
WDOG4_IRQHandler
WDOG5_IRQHandler
Reserved96_IRQHandler
Reserved97_IRQHandler
Reserved98_IRQHandler
Reserved99_IRQHandler
Reserved100_IRQHandler
Reserved101_IRQHandler
uSDHC1_DriverIRQHandler
uSDHC2_DriverIRQHandler
Reserved104_IRQHandler
Reserved105_IRQHandler
Reserved106_IRQHandler
Reserved107_IRQHandler
Reserved108_IRQHandler
Reserved109_IRQHandler
Reserved110_IRQHandler
DMA3_ERROR_DriverIRQHandler
DMA3_DriverIRQHandler
DMA4_ERROR_DriverIRQHandler
DMA4_0_1_DriverIRQHandler
DMA4_2_3_DriverIRQHandler
DMA4_4_5_DriverIRQHandler
DMA4_6_7_DriverIRQHandler
DMA4_8_9_DriverIRQHandler
DMA4_10_11_DriverIRQHandler
DMA4_12_13_DriverIRQHandler
DMA4_14_15_DriverIRQHandler
DMA4_16_17_DriverIRQHandler
DMA4_18_19_DriverIRQHandler
DMA4_20_21_DriverIRQHandler
DMA4_22_23_DriverIRQHandler
DMA4_24_25_DriverIRQHandler
DMA4_26_27_DriverIRQHandler
DMA4_28_29_DriverIRQHandler
DMA4_30_31_DriverIRQHandler
DMA4_32_33_DriverIRQHandler
DMA4_34_35_DriverIRQHandler
DMA4_36_37_DriverIRQHandler
DMA4_38_39_DriverIRQHandler
DMA4_40_41_DriverIRQHandler
DMA4_42_43_DriverIRQHandler
DMA4_44_45_DriverIRQHandler
DMA4_46_47_DriverIRQHandler
DMA4_48_49_DriverIRQHandler
DMA4_50_51_DriverIRQHandler
DMA4_52_53_DriverIRQHandler
DMA4_54_55_DriverIRQHandler
DMA4_56_57_DriverIRQHandler
DMA4_58_59_DriverIRQHandler
DMA4_60_61_DriverIRQHandler
DMA4_62_63_DriverIRQHandler
Reserved176_IRQHandler
Reserved177_IRQHandler
Reserved178_IRQHandler
Reserved179_IRQHandler
Reserved180_IRQHandler
Reserved181_IRQHandler
Reserved182_IRQHandler
Reserved183_IRQHandler
Reserved184_IRQHandler
SAI2_DriverIRQHandler
SAI3_DriverIRQHandler
SAI4_DriverIRQHandler
SAI5_DriverIRQHandler
Reserved189_IRQHandler
Reserved190_IRQHandler
USB1_IRQHandler
USB2_IRQHandler
LPSPI5_DriverIRQHandler
LPSPI6_DriverIRQHandler
LPSPI7_DriverIRQHandler
LPSPI8_DriverIRQHandler
LPI2C5_DriverIRQHandler
LPI2C6_DriverIRQHandler
LPI2C7_DriverIRQHandler
LPI2C8_DriverIRQHandler
PDM_HWVAD_ERROR_IRQHandler
PDM_HWVAD_EVENT_IRQHandler
PDM_ERROR_IRQHandler
PDM_EVENT_DriverIRQHandler
Reserved205_IRQHandler
Reserved206_IRQHandler
uSDHC3_DriverIRQHandler
Reserved208_IRQHandler
Reserved209_IRQHandler
Reserved210_IRQHandler
Reserved211_IRQHandler
Reserved212_IRQHandler
Reserved213_IRQHandler
Reserved214_IRQHandler
Reserved215_IRQHandler
Reserved216_IRQHandler
Reserved217_IRQHandler
Reserved218_IRQHandler
Reserved219_IRQHandler
Reserved220_IRQHandler
MU5_A_IRQHandler
MU6_A_IRQHandler
MU7_B_IRQHandler
MU8_B_IRQHandler
Reserved225_IRQHandler
Reserved226_IRQHandler
Reserved227_IRQHandler
Reserved228_IRQHandler
Reserved229_IRQHandler
DISP_IRQSTEER0_DriverIRQHandler
DISP_IRQSTEER1_DriverIRQHandler
DISP_IRQSTEER2_DriverIRQHandler
DISP_IRQSTEER3_DriverIRQHandler
DISP_IRQSTEER4_DriverIRQHandler
DISP_IRQSTEER7_DriverIRQHandler
Reserved236_IRQHandler
Reserved237_IRQHandler
Reserved238_IRQHandler
Reserved239_IRQHandler
MU1_A_IRQHandler
MU1_B_IRQHandler
MU2_A_IRQHandler
MU2_B_IRQHandler
MU3_A_IRQHandler
MU3_B_IRQHandler
MU4_A_IRQHandler
MU4_B_IRQHandler
MU5_B_IRQHandler
MU6_B_IRQHandler
MU7_A_IRQHandler
MU8_A_IRQHandler
MSGINTR1_IRQHandler
MSGINTR2_IRQHandler
Reserved254_IRQHandler
Reserved255_IRQHandler
Reserved256_IRQHandler
Reserved257_IRQHandler
Reserved258_IRQHandler
Reserved259_IRQHandler
Reserved260_IRQHandler
Reserved261_IRQHandler
Reserved262_IRQHandler
Reserved263_IRQHandler
Reserved264_IRQHandler
Reserved265_IRQHandler
Reserved266_IRQHandler
Reserved267_IRQHandler
Reserved268_IRQHandler
Reserved269_IRQHandler
Reserved270_IRQHandler
Reserved271_IRQHandler
DMA5_0_1_DriverIRQHandler
DMA5_2_3_DriverIRQHandler
DMA5_4_5_DriverIRQHandler
DMA5_6_7_DriverIRQHandler
DMA5_8_9_DriverIRQHandler
DMA5_10_11_DriverIRQHandler
DMA5_12_13_DriverIRQHandler
DMA5_14_15_DriverIRQHandler
DMA5_16_17_DriverIRQHandler
DMA5_18_19_DriverIRQHandler
DMA5_20_21_DriverIRQHandler
DMA5_22_23_DriverIRQHandler
DMA5_24_25_DriverIRQHandler
DMA5_26_27_DriverIRQHandler
DMA5_28_29_DriverIRQHandler
DMA5_30_31_DriverIRQHandler
DMA5_32_33_DriverIRQHandler
DMA5_34_35_DriverIRQHandler
DMA5_36_37_DriverIRQHandler
DMA5_38_39_DriverIRQHandler
DMA5_40_41_DriverIRQHandler
DMA5_42_43_DriverIRQHandler
DMA5_44_45_DriverIRQHandler
DMA5_46_47_DriverIRQHandler
DMA5_48_49_DriverIRQHandler
DMA5_50_51_DriverIRQHandler
DMA5_52_53_DriverIRQHandler
DMA5_54_55_DriverIRQHandler
DMA5_56_57_DriverIRQHandler
DMA5_58_59_DriverIRQHandler
DMA5_60_61_DriverIRQHandler
DMA5_62_63_DriverIRQHandler
Reserved304_IRQHandler
Reserved305_IRQHandler
Reserved306_IRQHandler
Reserved307_IRQHandler
Reserved308_IRQHandler
Reserved309_IRQHandler
Reserved310_IRQHandler
Reserved311_IRQHandler
Reserved312_IRQHandler
Reserved313_IRQHandler
Reserved314_IRQHandler
Reserved315_IRQHandler
Reserved316_IRQHandler
Reserved317_IRQHandler
Reserved318_IRQHandler
Reserved319_IRQHandler
Reserved320_IRQHandler
Reserved321_IRQHandler
Reserved322_IRQHandler
Reserved323_IRQHandler
Reserved324_IRQHandler
Reserved325_IRQHandler
Reserved326_IRQHandler
Reserved327_IRQHandler
Reserved328_IRQHandler
Reserved329_IRQHandler
Reserved330_IRQHandler
Reserved331_IRQHandler
Reserved332_IRQHandler
Reserved333_IRQHandler
Reserved334_IRQHandler
Reserved335_IRQHandler
Reserved336_IRQHandler
Reserved337_IRQHandler
Reserved338_IRQHandler
Reserved339_IRQHandler
Reserved340_IRQHandler
Reserved341_IRQHandler
Reserved342_IRQHandler
Reserved343_IRQHandler
Reserved344_IRQHandler
Reserved345_IRQHandler
Reserved346_IRQHandler
Reserved347_IRQHandler
Reserved348_IRQHandler
Reserved349_IRQHandler
Reserved350_IRQHandler
Reserved351_IRQHandler
Reserved352_IRQHandler
Reserved353_IRQHandler
Reserved354_IRQHandler
Reserved355_IRQHandler
Reserved356_IRQHandler
Reserved357_IRQHandler
Reserved358_IRQHandler
Reserved359_IRQHandler
Reserved360_IRQHandler
Reserved361_IRQHandler
Reserved362_IRQHandler
Reserved363_IRQHandler
Reserved364_IRQHandler
Reserved365_IRQHandler
Reserved366_IRQHandler
Reserved367_IRQHandler
Reserved368_IRQHandler
Reserved369_IRQHandler
Reserved370_IRQHandler
Reserved371_IRQHandler
Reserved372_IRQHandler
Reserved373_IRQHandler
Reserved374_IRQHandler
Reserved375_IRQHandler
Reserved376_IRQHandler
Reserved377_IRQHandler
Reserved378_IRQHandler
Reserved379_IRQHandler
Reserved380_IRQHandler
Reserved381_IRQHandler
Reserved382_IRQHandler
Reserved383_IRQHandler
Reserved384_IRQHandler
Reserved385_IRQHandler
Reserved386_IRQHandler
Reserved387_IRQHandler
Reserved388_IRQHandler
Reserved389_IRQHandler
Reserved390_IRQHandler
Reserved391_IRQHandler
DefaultISR
        B DefaultISR

        END
